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

#ifndef TENSORFLOW_LITE_MICRO_EXAMPLES_NETWORK_TESTER_NETWORK_MODEL_H_
#define TENSORFLOW_LITE_MICRO_EXAMPLES_NETWORK_TESTER_NETWORK_MODEL_H_

const unsigned char network_model[] = {
    0x1c, 0x00, 0x00, 0x00, 0x54, 0x46, 0x4c, 0x33, 0x00, 0x00, 0x12, 0x00,
    0x1c, 0x00, 0x18, 0x00, 0x14, 0x00, 0x10, 0x00, 0x0c, 0x00, 0x08, 0x00,
    0x00, 0x00, 0x04, 0x00, 0x12, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00,
    0x48, 0x00, 0x00, 0x00, 0x2c, 0x01, 0x00, 0x00, 0x3c, 0x01, 0x00, 0x00,
    0x34, 0x06, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
    0x0c, 0x00, 0x00, 0x00, 0x08, 0x00, 0x0c, 0x00, 0x08, 0x00, 0x04, 0x00,
    0x08, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00,
    0x13, 0x00, 0x00, 0x00, 0x6d, 0x69, 0x6e, 0x5f, 0x72, 0x75, 0x6e, 0x74,
    0x69, 0x6d, 0x65, 0x5f, 0x76, 0x65, 0x72, 0x73, 0x69, 0x6f, 0x6e, 0x00,
    0x06, 0x00, 0x00, 0x00, 0xe0, 0x00, 0x00, 0x00, 0xd4, 0x00, 0x00, 0x00,
    0x84, 0x00, 0x00, 0x00, 0x2c, 0x00, 0x00, 0x00, 0x24, 0x00, 0x00, 0x00,
    0x04, 0x00, 0x00, 0x00, 0x92, 0xff, 0xff, 0xff, 0x04, 0x00, 0x00, 0x00,
    0x10, 0x00, 0x00, 0x00, 0x31, 0x2e, 0x35, 0x2e, 0x30, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x58, 0xff, 0xff, 0xff,
    0xb2, 0xff, 0xff, 0xff, 0x04, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00,
    0x0d, 0x52, 0x1b, 0x0f, 0xec, 0x2f, 0xee, 0x7f, 0x7f, 0xc4, 0x68, 0x08,
    0x19, 0x7f, 0x81, 0x81, 0x81, 0x7f, 0x49, 0x7f, 0x7c, 0x5f, 0xf5, 0x5b,
    0x97, 0x48, 0x81, 0x7f, 0x08, 0xe7, 0xba, 0x54, 0xf4, 0x1a, 0x81, 0x28,
    0x1d, 0x25, 0x7f, 0x3b, 0xda, 0xe0, 0x46, 0x82, 0x3e, 0x33, 0xaa, 0x8e,
    0xcf, 0xcc, 0x13, 0xeb, 0x7f, 0x81, 0xad, 0x92, 0x2a, 0x81, 0xf4, 0xb7,
    0x81, 0x8c, 0x2e, 0x91, 0x00, 0x00, 0x06, 0x00, 0x08, 0x00, 0x04, 0x00,
    0x06, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0xfc, 0xff, 0xff, 0xff, 0x04, 0x00, 0x04, 0x00,
    0x04, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x4d, 0x4c, 0x49, 0x52,
    0x20, 0x43, 0x6f, 0x6e, 0x76, 0x65, 0x72, 0x74, 0x65, 0x64, 0x2e, 0x00,
    0x01, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x00,
    0x18, 0x00, 0x14, 0x00, 0x10, 0x00, 0x0c, 0x00, 0x08, 0x00, 0x04, 0x00,
    0x0e, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00,
    0x78, 0x00, 0x00, 0x00, 0x7c, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00,
    0x04, 0x00, 0x00, 0x00, 0x6d, 0x61, 0x69, 0x6e, 0x00, 0x00, 0x00, 0x00,
    0x01, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x00,
    0x14, 0x00, 0x00, 0x00, 0x10, 0x00, 0x0c, 0x00, 0x0b, 0x00, 0x04, 0x00,
    0x0e, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02,
    0x24, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x10, 0x00,
    0x00, 0x00, 0x0c, 0x00, 0x08, 0x00, 0x04, 0x00, 0x0c, 0x00, 0x00, 0x00,
    0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
    0x01, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
    0x01, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0xbc, 0x03, 0x00, 0x00,
    0x78, 0x02, 0x00, 0x00, 0xa0, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00,
    0x62, 0xfc, 0xff, 0xff, 0x14, 0x00, 0x00, 0x00, 0x4c, 0x00, 0x00, 0x00,
    0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x70, 0x00, 0x00, 0x00,
    0x54, 0xfc, 0xff, 0xff, 0x10, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00,
    0x20, 0x00, 0x00, 0x00, 0x24, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
    0xfd, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00,
    0x01, 0x00, 0x00, 0x00, 0xb6, 0xdb, 0x56, 0x3c, 0x01, 0x00, 0x00, 0x00,
    0x36, 0x14, 0xda, 0x3f, 0x01, 0x00, 0x00, 0x00, 0x7d, 0xf5, 0xd1, 0xbf,
    0x2a, 0x00, 0x00, 0x00, 0x73, 0x65, 0x70, 0x61, 0x72, 0x61, 0x62, 0x6c,
    0x65, 0x30, 0x2f, 0x64, 0x65, 0x70, 0x74, 0x68, 0x77, 0x69, 0x73, 0x65,
    0x5f, 0x63, 0x6f, 0x6e, 0x76, 0x32, 0x64, 0x2f, 0x64, 0x65, 0x70, 0x74,
    0x68, 0x77, 0x69, 0x73, 0x65, 0x5f, 0x69, 0x6e, 0x74, 0x38, 0x00, 0x00,
    0x04, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00,
    0x04, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0xfa, 0xfc, 0xff, 0xff,
    0x28, 0x00, 0x00, 0x00, 0x8c, 0x01, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x09, 0xac, 0x01, 0x00, 0x00, 0x00, 0x00, 0x12, 0x00,
    0x18, 0x00, 0x14, 0x00, 0x10, 0x00, 0x0c, 0x00, 0x08, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x04, 0x00, 0x12, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00,
    0x10, 0x00, 0x00, 0x00, 0x90, 0x00, 0x00, 0x00, 0xd0, 0x00, 0x00, 0x00,
    0x10, 0x01, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x19, 0x95, 0xf7, 0x3b,
    0x6f, 0xa4, 0xab, 0x3b, 0xd3, 0x51, 0xf8, 0x3b, 0x1b, 0xf0, 0xbe, 0x3b,
    0x2b, 0x04, 0xfc, 0x3b, 0x7f, 0x5b, 0xcd, 0x3b, 0xed, 0xfc, 0xe4, 0x3b,
    0xcf, 0x2a, 0xca, 0x3b, 0xbc, 0x43, 0xef, 0x3b, 0x5d, 0x9e, 0x7e, 0x3b,
    0x7b, 0x0a, 0xb8, 0x3b, 0x92, 0x76, 0xe5, 0x3b, 0x81, 0xfb, 0xaf, 0x3b,
    0x0b, 0x9f, 0xdb, 0x3b, 0xe1, 0x5b, 0xdd, 0x3b, 0xe6, 0x0d, 0xd5, 0x3b,
    0x10, 0x00, 0x00, 0x00, 0xab, 0xf0, 0xc7, 0x3d, 0x26, 0x4d, 0x2a, 0x3f,
    0x90, 0x6a, 0x0e, 0x3f, 0x3b, 0x72, 0x3d, 0x3f, 0x23, 0x0c, 0x7a, 0x3f,
    0x50, 0x2b, 0x19, 0x3f, 0xf3, 0x32, 0x63, 0x3f, 0x79, 0x96, 0x48, 0x3f,
    0x35, 0x65, 0x6d, 0x3f, 0x75, 0x47, 0x8f, 0x3e, 0xfc, 0x5c, 0x15, 0x3f,
    0xa5, 0xab, 0x63, 0x3f, 0xe5, 0xc4, 0xaa, 0x3e, 0xcd, 0xe7, 0x59, 0x3f,
    0xdd, 0x14, 0xa0, 0x3e, 0x5c, 0x68, 0x0c, 0x3f, 0x10, 0x00, 0x00, 0x00,
    0xef, 0xa5, 0x75, 0xbf, 0x67, 0x8f, 0x8b, 0xbe, 0x2f, 0x61, 0x76, 0xbf,
    0xfb, 0x7c, 0xfb, 0xbd, 0xdf, 0x5a, 0x1c, 0xbe, 0xc8, 0xc0, 0x4b, 0xbf,
    0x1b, 0x0e, 0x15, 0xbf, 0xd7, 0x68, 0x2d, 0xbf, 0x89, 0x71, 0x43, 0xbf,
    0x20, 0xa1, 0xfc, 0xbe, 0x66, 0x9a, 0x36, 0xbf, 0x21, 0x2a, 0x61, 0xbf,
    0x8a, 0x9b, 0x2e, 0xbf, 0xe9, 0x7c, 0x47, 0xbf, 0x29, 0xa1, 0x5b, 0xbf,
    0xca, 0x63, 0x53, 0xbf, 0x26, 0x00, 0x00, 0x00, 0x73, 0x65, 0x70, 0x61,
    0x72, 0x61, 0x62, 0x6c, 0x65, 0x30, 0x2f, 0x64, 0x65, 0x70, 0x74, 0x68,
    0x77, 0x69, 0x73, 0x65, 0x5f, 0x63, 0x6f, 0x6e, 0x76, 0x32, 0x64, 0x2f,
    0x64, 0x65, 0x70, 0x74, 0x68, 0x77, 0x69, 0x73, 0x65, 0x32, 0x00, 0x00,
    0x04, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
    0x02, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0xce, 0xfe, 0xff, 0xff,
    0x20, 0x00, 0x00, 0x00, 0xf4, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x02, 0x14, 0x01, 0x00, 0x00, 0x0c, 0x00, 0x0c, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x04, 0x00, 0x0c, 0x00, 0x00, 0x00,
    0x08, 0x00, 0x00, 0x00, 0x8c, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x10, 0x00, 0x00, 0x00, 0xba, 0x5e, 0x78, 0x38, 0x38, 0x30, 0x2c, 0x38,
    0x0e, 0x1c, 0x79, 0x38, 0x9b, 0x8b, 0x3f, 0x38, 0x68, 0xd1, 0x7c, 0x38,
    0xbd, 0x02, 0x4e, 0x38, 0x69, 0xb7, 0x65, 0x38, 0x74, 0xcf, 0x4a, 0x38,
    0x97, 0x06, 0x70, 0x38, 0xb9, 0x6d, 0xff, 0x37, 0x5d, 0xa0, 0x38, 0x38,
    0x71, 0x31, 0x66, 0x38, 0xd3, 0x8a, 0x30, 0x38, 0xe7, 0x51, 0x5c, 0x38,
    0x27, 0x10, 0x5e, 0x38, 0x68, 0xbb, 0x55, 0x38, 0x26, 0x00, 0x00, 0x00,
    0x73, 0x65, 0x70, 0x61, 0x72, 0x61, 0x62, 0x6c, 0x65, 0x30, 0x2f, 0x64,
    0x65, 0x70, 0x74, 0x68, 0x77, 0x69, 0x73, 0x65, 0x5f, 0x63, 0x6f, 0x6e,
    0x76, 0x32, 0x64, 0x2f, 0x64, 0x65, 0x70, 0x74, 0x68, 0x77, 0x69, 0x73,
    0x65, 0x31, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x0e, 0x00, 0x18, 0x00, 0x14, 0x00, 0x13, 0x00, 0x0c, 0x00,
    0x08, 0x00, 0x04, 0x00, 0x0e, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00,
    0x58, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09,
    0x68, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x14, 0x00, 0x10, 0x00, 0x0c, 0x00,
    0x08, 0x00, 0x04, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00,
    0x1c, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x24, 0x00, 0x00, 0x00,
    0x01, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x3e, 0x68, 0x00, 0x3c,
    0x01, 0x00, 0x00, 0x00, 0xe9, 0xe6, 0x7f, 0x3f, 0x01, 0x00, 0x00, 0x00,
    0x70, 0xb8, 0x7f, 0xbf, 0x16, 0x00, 0x00, 0x00, 0x64, 0x61, 0x74, 0x61,
    0x30, 0x2f, 0x50, 0x6c, 0x61, 0x63, 0x65, 0x68, 0x6f, 0x6c, 0x64, 0x65,
    0x72, 0x5f, 0x69, 0x6e, 0x74, 0x38, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00,
    0x01, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00,
    0x10, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00,
    0x24, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0xd8, 0xff, 0xff, 0xff,
    0x06, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06,
    0x0c, 0x00, 0x0c, 0x00, 0x0b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00,
    0x0c, 0x00, 0x00, 0x00, 0x72, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x72,
    0x0c, 0x00, 0x10, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x08, 0x00, 0x04, 0x00,
    0x0c, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x04};
const unsigned int network_model_len = 1720;

#endif  // TENSORFLOW_LITE_MICRO_EXAMPLES_NETWORK_TESTER_NETWORK_MODEL_H_
