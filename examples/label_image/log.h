/* Copyright 2017 The TensorFlow Authors. All Rights Reserved.

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

#ifndef TENSORFLOW_LITE_EXAMPLES_LABEL_IMAGE_LOG_H_
#define TENSORFLOW_LITE_EXAMPLES_LABEL_IMAGE_LOG_H_

#include <iostream>

namespace tflite {
namespace label_image {

class Log {
  std::stringstream stream_;
public:
  Log(const char *severity) {
      stream_ << severity << ": ";
  }
  std::stringstream& Stream() { return stream_; }
  ~Log() {
    std::cerr << stream_.str() << std::endl;
  }
};

#define LOG(severity) tflite::label_image::Log(#severity).Stream()

}  // namespace label_image
}  // namespace tflite

#endif  // TENSORFLOW_LITE_EXAMPLES_LABEL_IMAGE_LOG_H_
