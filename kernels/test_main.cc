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
#include <vector>

#include <gtest/gtest.h>
#include "tensorflow/lite/kernels/test_delegate_providers.h"
#include "tensorflow/lite/kernels/test_util.h"
#include "tensorflow/lite/testing/util.h"
#include "tensorflow/lite/tools/command_line_flags.h"

namespace {

void InitKernelTest(int* argc, char** argv) {
  tflite::KernelTestDelegateProviders* const delegate_providers =
      tflite::KernelTestDelegateProviders::Get();
  delegate_providers->InitFromCmdlineArgs(argc, const_cast<const char**>(argv));

  if (delegate_providers->ConstParams().Get<bool>("use_nnapi")) {
    // In Android Q, the NNAPI delegate avoids delegation if the only device
    // is the reference CPU. However, for testing purposes, we still want
    // delegation coverage, so force use of this reference path.
    const auto opt_name = "nnapi_accelerator_name";
    std::string accelerator_name =
        delegate_providers->ConstParams().Get<std::string>(opt_name);
    delegate_providers->MutableParams()->Set<std::string>(
        opt_name, accelerator_name.empty() ? "nnapi-reference"
                                           : accelerator_name.c_str());
  }
}

}  // namespace

int main(int argc, char** argv) {
  ::tflite::LogToStderr();
  InitKernelTest(&argc, argv);
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
