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
#include "tensorflow/lite/delegates/nnapi/acceleration_test_util.h"

namespace tflite {

const constexpr char* NnapiAccelerationTestParams::kAccelerationTestConfig =
    R"(
## Every Test can be whitelisted or blacklisted using a regexp on its test_id

## Test_id
#
# The test_id is test_suite_name / test_name, this differs from the
# name used by the build because of the / separator instead of .
# Parameterized tests names are composed by the base test name / test / ordinal
# the ordinal is the position in the list of parameters generated by the
# cardinal product of all the different parameter sets

# Blacklist/Whitelist
# To blacklist an element simply add - before the test_id regex

## Rules evaluation
#
# Rules are checked in order, the first matching completes the browsing
# This can be useful to put more specific rules first and generic default
# ones below

## Test Arguments
#
# The test can be parameterized with the minimum Android SDK version
# to apply the acceleration validation for.
# If omitted will use 27

#test-id,min-android-sdk-version

# activations_test
QuantizedActivationsOpTest/Relu6Uint8
FloatActivationsOpTest/Softmax[13]D,29
QuantizedActivationsOpTest/Softmax[13]D.+nt8,29
FloatActivationsOpTest/Softmax\dD
QuantizedActivationsOpTest/Softmax\dD.+nt8
FloatActivationsOpTest/LogSoftmax,29
FloatActivationsOpTest/PRelu,29
LogisticOpTest/LogisticOpTest/Sigmoid(.+nt8)?/\d+
LogisticOpTest/LogisticOpTest/Sigmoid/\d+
TanhOpTest/TanhOpTest/Tanh(.+nt8)?/\d+,29
FloatActivationsOpTest/HardSwish
QuantizedActivationsOpTest/HardSwish
QuantizedActivationsOpTest/HardSwishBias

# add_test
FloatAddOpModel/.+
QuantizedAddOpModel/QuantizedTestsNoActivation.+nt8
QuantizedAddOpModel/QuantizedVariousInputShapes.+
QuantizedAddOpModel/QuantizedWithScalarBroadcast.+nt8
QuantizedAddOpModel/QuantizedWithMixedBroadcas.+nt8

# arg_min_max_test
# Only tests with ConstantAxis && OutputType == TensorType_INT32
# (element 4 and 6 in the test parameter list)
# Supported only from NNAPI 1.2
ArgMinMaxOpTest/ArgMinMaxOpTest/Get.+ArgFloat/[46],29
ArgMinMaxOpTest/ArgMinMaxOpTest/Get.+Arg.+nt8/[46],29
ArgMinMaxOpTest/ArgMinMaxOpTest/Get.+ArgInt/[46],29
ArgMinMaxOpTest/ArgMinMaxOpTest/Get.+ArgMulDimensions/[46],29
ArgMinMaxOpTest/ArgMinMaxOpTest/Get.+ArgNegativeAxis/[46],29
ArgMinMaxOpTest/ArgMinMaxOpTest/Get.+ArgOutput64/[46],29

# basic_rnn_test
RnnOpTest/BlackBoxTest

# batch_to_space_nd_test
BatchToSpaceNDOpTest/SimpleConstTest.*
BatchToSpaceNDOpTest/BatchOneConstTest.*

# bidirectional_sequence_lstm_test
# Only test with non quantized weights
LSTMOpTest/LSTMOpTest/BlackBoxTestNoCifgNoPeepholeNoProjectionNoClipping/0,29
# Only test with non quantized weights
LSTMOpTest/LSTMOpTest/BlackBoxTestMergedOutput/0,29
LSTMOpTest/BlackBoxTestNoCifgNoPeepholeNoProjectionNoClippingReverse,29
LSTMOpTest/BlackBoxTestWithCifgWithPeepholeNoProjectionNoClipping,29
LSTMOpTest/BlackBoxTestWithCifgWithPeepholeNoProjectionNoClippingReversed,29
LSTMOpTest/BlackBoxTestWithPeepholeWithProjectionNoClipping,29
LSTMOpTest/BlackBoxTestWithPeepholeWithProjectionNoClippingBatchMajor,29
# Only test with non quantized weights
LSTMOpTest/LSTMOpTest/BlackBoxTestWithAuxInputZeroAuxWeight/0,29
QuantizationOrNot/LSTMOpTest/BlackBoxTestNoCifgNoPeepholeNoProjectionNoClipping/0,29
QuantizationOrNot/LSTMOpTest/BlackBoxTestMergedOutput/0,29
QuantizationOrNot/LSTMOpTest/BlackBoxTestWithAuxInputZeroAuxWeight/0,29
LSTMOpTest/LSTMOpTest/BlackBoxTestWithAuxInput/0,29

# cast_test
CastOpModel/CastFloatToIn32
CastOpModel/CastInt32ToFloat,29
CastOpModel/CastFloatToUInt8,29
CastOpModel/CastUInt8ToFloat,29
CastOpModel/CastInt32ToUInt8,29
CastOpModel/CastUInt8ToInt32,29

# comparisons_test
ComparisonsTest/.+,29

# concatenation_test
ConcatenationOpTest/ThreeDimensionalOneInput
ConcatenationOpTest/OneTrivialInput
ConcatenationOpTest/TwoDimensionalOneInput
ConcatenationOpTest/TwoInputsTwoAxesNegativeAxes
ConcatenationOpTest/TwoInputsTwoAxesNegativeAxesNonQuantized
ConcatenationOpTest/FourInputs
ConcatenationOpTest/FourInputsQuantizedUint8
ConcatenationOpTest/FourInputsQuantizedInt8
ConcatenationOpTest/ThreeDimensionalNonQuantizedOneInput
ConcatenationOpTest/OneTrivialNonQuantizedInput
ConcatenationOpTest/TwoDimensionalNonQuantizedOneInput
ConcatenationOpTest/FourInputsQuantizedMixedRange,29
ConcatenationOpTest/FourInputsQuantizedMixedRangeClampingLogic,29

# conv_test
-ConvolutionOpTest/ConvolutionOpTest.SimplePerTensorTest/.+
ConvolutionOpTest/ConvolutionOpTest.SimpleTestFloatWithDilation/.+,29
ConvolutionOpTest/ConvolutionOpTest.SimpleTestLargeIrregularQuantized/.+,29
ConvolutionOpTest/ConvolutionOpTest.SimpleTestQuantizedOutputMultiplierGreaterThan1/.+,29
ConvolutionOpTest/ConvolutionOpTest.SimpleTestQuantizedWithDilation/.+,29
ConvolutionOpTest/ConvolutionOpTest.SimplePerChannelTest/.+,29
ConvolutionOpTest/ConvolutionOpTest/.+Hybrid.+,29/
ConvolutionOpTest/ConvolutionOpTest/.+/\d+


# depthwise_conv_test
.+ConvolutionOpTest/.+/\d+,29

# dequantize_test
DequantizeOpTest/Uint8

# depth_to_space_test
DepthToSpaceOpModel/Float32
DepthToSpaceOpModel/UInt8
DepthToSpaceOpModel/int8

# div_test
-FloatDivOpTest/WithBroadcast5D
FloatDivOpTest/.+

# elementwise_test
ElementWise/Abs
ElementWise/Sin,29
ElementWise/Log,29
ElementWise/Sqrt,29
ElementWise/Rsqrt,29
ElementWise/LogicalNot,29

# embedding_lookup_test
EmbeddingLookupOpTest/SimpleTest

# exp_test
ExpOpTest/FloatTest,29

# expand_dims_test
# Only constant tensors models
ExpandDimsOpTest/.+/1,29

# floor_test
FloorOpTest/.+

# fully_connected_test
FloatFullyConnectedOpTest/FloatFullyConnectedOpTest/SimpleTest/\d+
FloatFullyConnectedOpTest/FloatFullyConnectedOpTest/SimpleTest2/\d+
QuantizedFullyConnectedOpTest/QuantizedFullyConnectedOpTest/SimpleTestQuantized.+nt8/\d+,29
QuantizedFullyConnectedOpTest/QuantizedFullyConnectedOpTest/SimpleTestSingleBatchQuantizedInt8/\d+,29
QuantizedFullyConnectedOpTest/SimpleTestQuantizedOutputMultiplierGreaterThan1Uint8/\d+,29
QuantizedFullyConnectedOpTest/SimpleTestQuantizedOutputMultiplierGreaterThan1Int8/\d+,29
HybridFullyConnectedOpTest/SimpleTestQuantizedUint8,29
HybridFullyConnectedOpTest/SimpleTestQuantizedInt8,29
FloatFullyConnectedOpTest/FloatFullyConnectedOpTest/SimpleTest4DInput/\d+
QuantizedFullyConnectedOpTest/QuantizedFullyConnectedOpTest/SimpleTest4dInputQuantizedUint8/\d+
QuantizedFullyConnectedOpTest/QuantizedFullyConnectedOpTest/SimpleTest4dInputQuantizedOutputMultiplierGreaterThan1Uint8/\d+,29
FloatFullyConnectedOpTest/FloatFullyConnectedOpTest/BlackBoxTest/\d+

# gather_test
GatherOpTest/Shuffle,29
GatherOpTest/Test1DInput1DIndex,29
GatherOpTest/Test2DIndexWith2DResult,29
FloatGatherOpTest/Duplicate,29
FloatGatherOpTest/Slice,29
FloatGatherOpTest/Axis1,29
FloatGatherOpTest/Axis1Slice,29
FloatGatherOpTest/LastAxis,29
TypesGatherOpTest/Float32Int32,29
TypesGatherOpTest/Int32Int32,29
TypesGatherOpTest/Uint8Int32,29

# hashtable_lookup_test
# All test excepted the string one should be accelerated
-HashtableLookupOpTest/TestString
HashtableLookupOpTest/.+

# l2norm_test
L2NormOpTest/.+,29

# local_response_norm_test
LocalResponseNormOpTest/.+

# logical_test
LogicalTest/.+,29

# lsh_projection_test
-LSHProjectionOpTest2/Sparse3DInputs
LSHProjectionOpTest2/Sparse1DInputs,29
LSHProjectionOpTest2/.+

# Before the lstm because of clashing with matchers
# unidirectional_sequence_lstm_test
NoCifgNoPeepholeNoProjectionNoClippingUnidirectionalLstmTest/LstmBlackBoxTest,29
CifgPeepholeNoProjectionNoClippingUnidirectionalLstmTest/NonLayerNormLstmBlackBoxTest,29
# Only the two tests above, disabling all possible matches from the lstm tests
# coming after
-.+UnidirectionalLstmTest/.+

# lstm_test
-.+LstmTest/Hybrid.+Int8
-LSTMOpModel/InvalidTypeTest
.+LstmTest/.+,29

# maximum_minimum_test
MaxMinOpTest/.+nt8Test,29
MaximumOpTest/.+,29

# mul_test
FloatMulOpTest/.+

# neg_test
-NegOpModel/.+Int64
NegOpModel/.+,29

# pad_test
-PadOpTest/TooManyDimensions
-PadOpTest/UnequalDimensions
-PadOpTest/InvalidPadValue
# Zero height or width is not supported
-PadOpTest/Zero.+ConstImageStyleTest
# Dynamic tensors are not supported
-.*Pad.*OpTest/.+Dynamic.*Test
-QuantizedPad.*OpTest/.+ZeroNotInQuantizationRange
QuantizedPadOpTest/.+,29
QuantizedPadV2OpTest/.+,29
PadOpTest/.+,29

# pooling_test
FloatPoolingOpTest/L2PoolActivationRelu.*,29
FloatPoolingOpTest/.+
# Image is too big
-QuantizedPoolingOpTest/AveragePoolImageSize17
QuantizedPoolingOpTest/.+
QuantizedUInt8PoolingOpTest/.+

# pow_test
-PowOpModel/Simple
-PowOpModel/NegativeAndZeroValue
-PowOpModel/BroadcastTest
-PowOpModel/IntSingleIntegerExponentTest
PowOpModel/.+,29

# quant_basic_lstm_test
QuantizedLstmTest/BasicQuantizedLstmTest/29

# quantize_test
QuantizeOpTest/UINT8,29

# reduce_test
-Dynamic.+(Mean|Sum|Prod|Max|Min)OpTest/.+
-ConstUint8(Mean|Sum)OpTest/.+
ConstUint8(Max|Min)OpTest/.+,29
ConstUint8(Mean)OpTest/.+
Constint8(Mean|Max|Min)OpTest/.+
ConstFloat(Sum|Prod|Max|Min)OpTest/NotKeepDims,29
ConstFloat(Sum|Prod|Max|Min)OpTest/KeepDims,29
ConstFloat(Mean|Any)OpTest/NotKeepDims
ConstFloat(Mean|Any)OpTest/KeepDims
ConstFloat(Sum|Prod|Max|Min)OpTest/ScalarAxis,29

# reshape_test
# Acceleration would be only for the test with shape being a constant tensor
VariedShapeSpec/ReshapeOpTest/InvalidShape/1
VariedShapeSpec/ReshapeOpTest/RegularShapes/1
VariedShapeSpec/ReshapeOpTest/WithStretchDimension/1

# resize_bilinear_test
// Only models with constant size tensor are accelerated
ResizeBilinearOpTest/ResizeBilinearOpTest/.+/0,29

# resize_nearest_neighbor_test
// Only models with constant size tensor are accelerated
ResizeNearestNeighborOpTest/ResizeNearestNeighborOpTest/.+/0,29

# select_test
-SelectOpTest/SelectBool
-SelectOpTest.SelectInt16
-SelectOpTest/RankZero.+
-SelectOpTest/RankOne.+
SelectOpTest/.+,29

# slice_test
-SliceOpTest/SliceOpTest/IndexInt64/.+
-SliceOpTest/SliceOpTest/SliceString/.+
# Only constant tensors
SliceOpTest/SliceOpTest/.+/0,29

# softmax_test
SoftmaxOpTest/CompareWithTFminiBetaEq1
SoftmaxOpTest/CompareWithTFminiBetaNotEq1

# space_to_depth_test
SpaceToDepthOpModel/Float32
SpaceToDepthOpModel/Uint8
SpaceToDepthOpModel/int8

# split_test
-SplitOpTest/SplitOpTest/.+Int8/.+
# Only accelerated when axis is a constant tensor
SplitOpTest/SplitOpTest/.+/0,29

# squeeze_test
FloatSqueezeOpTest/.+,29

# sub_test
-FloatSubOpModel/WithBroadcast5D
FloatSubOpModel/.+
-QuantizedSubOpModel/.+Int16
-QuantizedSubOpModel/.+Int8
QuantizedSubOpModel/.+

# svdf_test
SVDFOpTest/BlackBoxTestRank1
SVDFOpTest/BlackBoxTestRank2

# tile_test
-TileTest/TileTest/Int64.+/.+
-TileTest/TileTest/Boolean.+/.+
# Const tensor only
TileTest/TileTest/.+/0,29

# topk_v2_test
-TopKV2OpTest/TopKV2OpTest/.+Int64/.+
# Const tensor only
TopKV2OpTest/TopKV2OpTest/.+/0,29

# transpose_test
# death test
-TransposeTest/Test6DInputTensor
-TransposeTest/5DDividedIntoTwo2Ds.*
-TransposeTest/Complex5DTest.*
-TransposeTest/.+DynamicTensor
TransposeTest/.+

# transpose_conv_test
-TransposeConvOpTest/TransposeConvOpTest.SimpleTestQuantizedPerChannelSingleChannel/0
-TransposeConvOpTest/TransposeConvOpTest.TestQuantizedPerChannelMultiChannel/0
# Const tensor only
TransposeConvOpTest/TransposeConvOpTest/.+/0,29

# unidirectional_sequence_rnn_test
UnidirectionalRNNOpTest/BlackBoxTest,29
UnidirectionalRNNOpTest.TimeMajorBlackBoxTest,29
)";

}  // namespace tflite
