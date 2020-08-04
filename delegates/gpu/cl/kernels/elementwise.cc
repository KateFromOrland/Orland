/* Copyright 2019 The TensorFlow Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

#include "tensorflow/lite/delegates/gpu/cl/kernels/elementwise.h"

#include <string>

#include "absl/strings/str_cat.h"
#include "absl/strings/substitute.h"
#include "tensorflow/lite/delegates/gpu/cl/kernels/util.h"
#include "tensorflow/lite/delegates/gpu/cl/storage_type_util.h"

namespace tflite {
namespace gpu {
namespace cl {
namespace {
std::string GetOneInputCode(const OperationType& op_type,
                            CalculationsPrecision precision,
                            const std::string& input0) {
  std::string result;
  switch (op_type) {
    case OperationType::ABS:
      result = "$0 = fabs($0);\n";
      break;
    case OperationType::COS:
      result = "$0 = cos($0);\n";
      break;
    case OperationType::COPY:
      // No op as inout_value will be copied to dest automatically.
      result = "\n";
      break;
    case OperationType::ELU:
      result = "$0.x = $0.x < (FLT)(0.0f) ? exp($0.x) - (FLT)(1.0f) : $0.x;\n";
      result += "$0.y = $0.y < (FLT)(0.0f) ? exp($0.y) - (FLT)(1.0f) : $0.y;\n";
      result += "$0.z = $0.z < (FLT)(0.0f) ? exp($0.z) - (FLT)(1.0f) : $0.z;\n";
      result += "$0.w = $0.w < (FLT)(0.0f) ? exp($0.w) - (FLT)(1.0f) : $0.w;\n";
      break;
    case OperationType::EXP:
      result = "$0 = exp($0);\n";
      break;
    case OperationType::HARD_SWISH:
      result =
          "$0 *= clamp($0 * (FLT)(0.16666667f) + (FLT)(0.5f), (FLT4)(0.0f), "
          "(FLT4)(1.0f));\n";
      break;
    case OperationType::LOG:
      result = "$0 = log($0);\n";
      break;
    case OperationType::RSQRT:
      result = "$0 = (FLT4)(1.0f) / sqrt($0);\n";
      break;
    case OperationType::SIGMOID:
      if (precision != CalculationsPrecision::F32) {
        result =
            "$0.x = convert_half(native_recip(1.0f + "
            "native_exp(convert_float(-$0.x))));\n";
        result +=
            "$0.y = convert_half(native_recip(1.0f + "
            "native_exp(convert_float(-$0.y))));\n";
        result +=
            "$0.z = convert_half(native_recip(1.0f + "
            "native_exp(convert_float(-$0.z))));\n";
        result +=
            "$0.w = convert_half(native_recip(1.0f + "
            "native_exp(convert_float(-$0.w))));\n";
      } else {
        result = "$0 = (FLT4)(1.0f) / ((FLT4)(1.0f) + exp(-($0)));\n";
      }
      break;
    case OperationType::SIN:
      result = "$0 = sin($0);\n";
      break;
    case OperationType::SQRT:
      result = "$0 = sqrt($0);\n";
      break;
    case OperationType::SQUARE:
      result = "$0 *= $0;\n";
      break;
    case OperationType::TANH:
      result = "$0 = tanh($0);\n";
      break;
    default:
      return "Unknown operation type;\n";
  }
  return absl::Substitute(result, input0);
}

std::string GetTwoInputCode(const OperationType& op_type,
                            const std::string& input0,
                            const std::string& input1) {
  std::string result;
  switch (op_type) {
    case OperationType::ADD:
      result += "$0 += $1;\n";
      break;
    case OperationType::DIV:
      result += "$0 /= $1;\n";
      break;
    case OperationType::MAXIMUM:
      result += "$0 = max($0, $1);\n";
      break;
    case OperationType::MINIMUM:
      result += "$0 = min($0, $1);\n";
      break;
    case OperationType::MUL:
      result += "$0 *= $1;\n";
      break;
    case OperationType::POW:
      result += "$0 = pow($0, $1);\n";
      break;
    case OperationType::SQUARED_DIFF:
      result += "$0 -= $1;\n";
      result += "$0 *= $0;\n";
      break;
    case OperationType::SUB:
      result += "$0 -= $1;\n";
      break;
    default:
      return "Unknown operation type;\n";
  }
  return absl::Substitute(result, input0, input1);
}
}  // namespace

GPUOperation CreateElementwiseOneInput(const OperationDef& definition,
                                       const OperationType& op_type) {
  GPUOperation op(definition);
  op.elementwise_ = true;
  op.code_ = GetOneInputCode(op_type, definition.precision, "in_out_value");
  return op;
}

GPUOperation CreateElementwiseOneRuntimeOneScalar(
    const CreationContext& creation_context, const OperationDef& definition,
    const OperationType& op_type, float scalar_parameter) {
  GPUOperation op(definition);
  op.elementwise_ = true;
  if (definition.precision == CalculationsPrecision::F32) {
    op.args_.AddFloat("scalar", scalar_parameter);
  } else {
    op.args_.AddHalf("scalar", half(scalar_parameter));
  }
  op.code_ = GetTwoInputCode(op_type, "in_out_value", "args.scalar");
  return op;
}

absl::Status CreateElementwiseTwoInput(
    const CreationContext& creation_context, const OperationDef& definition,
    const OperationType& op_type,
    const tflite::gpu::Tensor<Linear, DataType::FLOAT32>& constant_tensor,
    GPUOperation* result) {
  const BHWC shape = BHWC(1, 1, 1, constant_tensor.shape.v);
  TensorStorageType storage_type =
      SelectBestStorageType(*creation_context.context, *creation_context.device,
                            shape, definition.GetPrimaryStorageType(),
                            definition.GetDataType(), Layout::HWC);
  TensorDescriptor desc{definition.GetDataType(), storage_type, Layout::HWC};
  Tensor gpu_tensor;
  RETURN_IF_ERROR(CreateTensor(*creation_context.context,
                               *creation_context.device, shape, desc,
                               &gpu_tensor));
  RETURN_IF_ERROR(
      gpu_tensor.WriteData(creation_context.queue, constant_tensor));

  *result = GPUOperation(definition);
  result->elementwise_ = true;
  result->args_.AddObject("second_tensor", AccessType::READ,
                          absl::make_unique<Tensor>(std::move(gpu_tensor)),
                          absl::make_unique<TensorDescriptor>(desc));
  const std::string s_coord = shape.c == 1 ? "0" : "S_COORD";
  result->code_ = absl::StrCat(
      "FLT4 second_val = args.second_tensor.Read(0, 0, ", s_coord, ");\n");
  if (shape.c == 1) {
    result->code_ += "  second_val.y = second_val.x;\n";
    result->code_ += "  second_val.z = second_val.x;\n";
    result->code_ += "  second_val.w = second_val.x;\n";
  }
  result->code_ += GetTwoInputCode(op_type, "in_out_value", "second_val");
  return absl::OkStatus();
}

absl::Status CreateElementwiseTwoInput(
    const CreationContext& creation_context, const OperationDef& definition,
    const OperationType& op_type,
    const tflite::gpu::Tensor<HWC, DataType::FLOAT32>& constant_tensor,
    GPUOperation* result) {
  const BHWC shape = BHWC(1, constant_tensor.shape.h, constant_tensor.shape.w,
                          constant_tensor.shape.c);
  TensorStorageType storage_type =
      SelectBestStorageType(*creation_context.context, *creation_context.device,
                            shape, definition.GetPrimaryStorageType(),
                            definition.GetDataType(), Layout::HWC);
  TensorDescriptor desc{definition.GetDataType(), storage_type, Layout::HWC};
  Tensor gpu_tensor;
  RETURN_IF_ERROR(CreateTensor(*creation_context.context,
                               *creation_context.device, shape, desc,
                               &gpu_tensor));
  RETURN_IF_ERROR(
      gpu_tensor.WriteData(creation_context.queue, constant_tensor));

  *result = GPUOperation(definition);
  result->elementwise_ = true;
  result->args_.AddObject("second_tensor", AccessType::READ,
                          absl::make_unique<Tensor>(std::move(gpu_tensor)),
                          absl::make_unique<TensorDescriptor>(desc));
  const std::string x_coord = shape.w == 1 ? "0" : "X_COORD";
  const std::string y_coord = shape.h == 1 ? "0" : "Y_COORD";
  const std::string s_coord = shape.c == 1 ? "0" : "S_COORD";
  result->code_ = absl::StrCat("FLT4 second_val = args.second_tensor.Read(",
                               x_coord, ", ", y_coord, ", ", s_coord, ");\n");
  if (shape.c == 1) {
    result->code_ += "  second_val.y = second_val.x;\n";
    result->code_ += "  second_val.z = second_val.x;\n";
    result->code_ += "  second_val.w = second_val.x;\n";
  }
  result->code_ += GetTwoInputCode(op_type, "in_out_value", "second_val");

  return absl::OkStatus();
}

GPUOperation CreateElementwiseTwoInput(const OperationDef& definition,
                                       const OperationType& op_type,
                                       const BHWC& shape) {
  GPUOperation op(definition);
  op.elementwise_ = true;
  auto src_desc = definition.src_tensors[1];
  if (definition.IsBatchSupported()) {
    src_desc.SetStateVar("BatchedWidth", "true");
  }
  op.AddSrcTensor("second_tensor", src_desc);
  const std::string x_coord = shape.w == 1 ? "0" : "X_COORD";
  const std::string y_coord = shape.h == 1 ? "0" : "Y_COORD";
  const std::string s_coord = shape.c == 1 ? "0" : "S_COORD";
  op.code_ = absl::StrCat("FLT4 second_val = args.second_tensor.Read(", x_coord,
                          ", ", y_coord, ", ", s_coord, ");\n");
  if (shape.c == 1) {
    op.code_ += "  second_val.y = second_val.x;\n";
    op.code_ += "  second_val.z = second_val.x;\n";
    op.code_ += "  second_val.w = second_val.x;\n";
  }
  op.code_ += GetTwoInputCode(op_type, "in_out_value", "second_val");
  return op;
}

}  // namespace cl
}  // namespace gpu
}  // namespace tflite
