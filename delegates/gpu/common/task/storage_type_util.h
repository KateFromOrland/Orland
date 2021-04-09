/* Copyright 2020 The TensorFlow Authors. All Rights Reserved.

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

#ifndef TENSORFLOW_LITE_DELEGATES_GPU_COMMON_TASK_STORAGE_TYPE_UTIL_H_
#define TENSORFLOW_LITE_DELEGATES_GPU_COMMON_TASK_STORAGE_TYPE_UTIL_H_

#include "tensorflow/lite/delegates/gpu/common/data_type.h"
#include "tensorflow/lite/delegates/gpu/common/gpu_info.h"
#include "tensorflow/lite/delegates/gpu/common/shape.h"
#include "tensorflow/lite/delegates/gpu/common/status.h"
#include "tensorflow/lite/delegates/gpu/common/task/tensor_desc.h"
#include "tensorflow/lite/delegates/gpu/common/task/tensor_linear_desc.h"

namespace tflite {
namespace gpu {

absl::Status CanCreateTensorWithShape(const GpuInfo& gpu_info,
                                      const BHWDC& shape,
                                      const TensorDescriptor& descriptor);

absl::Status CanCreateTensorWithShape(const GpuInfo& gpu_info,
                                      const BHWC& shape,
                                      const TensorDescriptor& descriptor);

absl::Status SelectBestStorageType(const GpuInfo& gpu_info, const BHWC& shape,
                                   TensorStorageType desired,
                                   DataType data_type, Layout layout,
                                   TensorStorageType* result);

LinearStorageType DeduceLinearStorageType(
    TensorStorageType tensor_storage_type);

}  // namespace gpu
}  // namespace tflite

#endif  // TENSORFLOW_LITE_DELEGATES_GPU_COMMON_TASK_STORAGE_TYPE_UTIL_H_
