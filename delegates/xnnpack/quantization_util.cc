/* Copyright 2021 The TensorFlow Authors. All Rights Reserved.

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

#include "tensorflow/lite/delegates/xnnpack/quantization_util.h"

#include <algorithm>
#include <limits>

#include <fp16.h>
#include "tensorflow/lite/kernels/internal/optimized/optimized_ops.h"
#include "tensorflow/lite/kernels/internal/types.h"

namespace tflite {
namespace xnnpack {

void DequantizeFloat16(const uint16_t *packed_fp16_data, float *unpacked_fp32_data,
                       size_t tensor_elements) {
  for (size_t i = 0; i < tensor_elements; ++i) {
    unpacked_fp32_data[i] = fp16_ieee_to_fp32_value(packed_fp16_data[i]);
  }
}

void DequantizeInt8(const int8_t *packed_s8_data, float *unpacked_fp32_data,
                    const RuntimeShape& tensor_shape,
                    int32_t zero_point, double scale) {
  DequantizationParams op_params;
  op_params.zero_point = zero_point;
  op_params.scale = scale;
  optimized_ops::Dequantize(op_params,
                            tensor_shape,
                            packed_s8_data,
                            tensor_shape,
                            unpacked_fp32_data);
}

}  // namespace xnnpack
}  // namespace tflite
