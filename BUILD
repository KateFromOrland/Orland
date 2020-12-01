load("//tensorflow:tensorflow.bzl", "if_not_windows", "tf_cc_test")
load("//tensorflow/lite:build_def.bzl", "tflite_cc_shared_object", "tflite_copts")
load("//tensorflow/lite:special_rules.bzl", "tflite_portable_test_suite")
load("//tensorflow:tensorflow.bzl", "get_compatible_with_portable")

package(
    default_visibility = ["//visibility:public"],
    licenses = ["notice"],  # Apache 2.0
)

exports_files(glob([
    "testdata/*.bin",
    "testdata/*.pb",
    "testdata/*.tflite",
    "testdata/*.csv",
    "models/testdata/*",
]))

config_setting(
    name = "gemmlowp_profiling",
    values = {
        "copt": "-DGEMMLOWP_PROFILING",
    },
)

config_setting(
    name = "mips",
    values = {
        "cpu": "mips",
    },
)

config_setting(
    name = "mips64",
    values = {
        "cpu": "mips64",
    },
)

config_setting(
    name = "tf_lite_static_memory",
    values = {
        "copt": "-DTF_LITE_STATIC_MEMORY",
        "cpu": "k8",
    },
)

TFLITE_DEFAULT_COPTS = if_not_windows([
    "-Wall",
    "-Wno-comment",
    "-Wno-extern-c-compat",
])

FRAMEWORK_LIB_HDRS = [
    "allocation.h",
    "context.h",
    "context_util.h",
    "core/macros.h",
    "core/subgraph.h",
    "error_reporter.h",
    "graph_info.h",
    "interpreter.h",
    "model.h",
    "model_builder.h",
    "interpreter_builder.h",
    "mutable_op_resolver.h",
    "op_resolver.h",
    "optional_debug_tools.h",
    "stderr_reporter.h",
]

exports_files(
    FRAMEWORK_LIB_HDRS,
    visibility = ["//tensorflow/lite/core/shims:__subpackages__"],
)

cc_library(
    name = "version",
    hdrs = ["version.h"],
    compatible_with = get_compatible_with_portable(),
    copts = TFLITE_DEFAULT_COPTS,
    # Note that we only use the header defines from :version_lib.
    deps = ["//tensorflow/core:version_lib"],
)

# TODO(b/128420794): Migrate clients to use :version directly.
alias(
    name = "schema_fbs_version",
    actual = ":version",
    # avoid_dep tells build_cleaner to not use schema_fbs_version.
    tags = ["avoid_dep"],
)

cc_library(
    name = "arena_planner",
    srcs = ["arena_planner.cc"],
    hdrs = ["arena_planner.h"],
    compatible_with = get_compatible_with_portable(),
    copts = TFLITE_DEFAULT_COPTS,
    deps = [
        ":graph_info",
        ":memory_planner",
        ":simple_memory_arena",
        ":util",
        "//tensorflow/lite/c:common",
    ],
)

cc_test(
    name = "arena_planner_test",
    size = "small",
    srcs = ["arena_planner_test.cc"],
    tags = [
        "tflite_not_portable_android",
    ],
    deps = [
        ":arena_planner",
        "//tensorflow/core:tflite_portable_logging",
        "//tensorflow/lite/testing:util",
        "@com_google_googletest//:gtest",
    ],
)

# Main library. No ops are included here.
# TODO(aselle): Resolve problems preventing C99 usage.
cc_library(
    name = "context",
    hdrs = ["context.h"],
    compatible_with = get_compatible_with_portable(),
    copts = TFLITE_DEFAULT_COPTS,
    deps = ["//tensorflow/lite/c:common"],
)

cc_library(
    name = "external_cpu_backend_context",
    srcs = ["external_cpu_backend_context.cc"],
    hdrs = ["external_cpu_backend_context.h"],
    compatible_with = get_compatible_with_portable(),
    copts = TFLITE_DEFAULT_COPTS,
    deps = [
        "//tensorflow/lite/c:common",
    ],
)

cc_library(
    name = "graph_info",
    hdrs = ["graph_info.h"],
    compatible_with = get_compatible_with_portable(),
    copts = TFLITE_DEFAULT_COPTS,
    deps = ["//tensorflow/lite/c:common"],
)

cc_library(
    name = "memory_planner",
    hdrs = ["memory_planner.h"],
    compatible_with = get_compatible_with_portable(),
    copts = TFLITE_DEFAULT_COPTS,
    deps = ["//tensorflow/lite/c:common"],
)

cc_library(
    name = "simple_memory_arena",
    srcs = ["simple_memory_arena.cc"],
    hdrs = ["simple_memory_arena.h"],
    compatible_with = get_compatible_with_portable(),
    copts = TFLITE_DEFAULT_COPTS,
    deps = ["//tensorflow/lite/c:common"],
)

cc_library(
    name = "builtin_op_data",
    hdrs = ["builtin_op_data.h"],
    deps = ["//tensorflow/lite/c:common"],
)

cc_library(
    name = "kernel_api",
    hdrs = [
        "builtin_op_data.h",
        "builtin_ops.h",
        "context_util.h",
    ],
    compatible_with = get_compatible_with_portable(),
    deps = ["//tensorflow/lite/c:common"],
)

cc_library(
    name = "builtin_ops",
    hdrs = ["builtin_ops.h"],
    compatible_with = get_compatible_with_portable(),
)

exports_files(["builtin_ops.h"])

cc_library(
    name = "string",
    hdrs = [
        "string_type.h",
    ],
    compatible_with = get_compatible_with_portable(),
    copts = TFLITE_DEFAULT_COPTS,
)

cc_library(
    name = "allocation",
    srcs = [
        "allocation.cc",
    ] + select({
        "//tensorflow:android": [
            "mmap_allocation.cc",
        ],
        "//tensorflow:windows": [
            "mmap_allocation_disabled.cc",
        ],
        "//conditions:default": [
            "mmap_allocation.cc",
        ],
    }),
    hdrs = [
        "allocation.h",
    ],
    compatible_with = get_compatible_with_portable(),
    copts = TFLITE_DEFAULT_COPTS,
    deps = [
        ":string",
        "//tensorflow/lite/c:common",
        "//tensorflow/lite/core/api",
    ],
)

# The library that implements the full C++ API.
# See also 'framework' below, which is the corresponding public target.
cc_library(
    name = "framework_lib",
    hdrs = FRAMEWORK_LIB_HDRS,
    compatible_with = get_compatible_with_portable(),
    copts = tflite_copts() + TFLITE_DEFAULT_COPTS,
    visibility = [
        "//tensorflow/lite:__subpackages__",
    ],
    deps = [
        ":allocation",
        ":arena_planner",
        ":cc_api",
        ":external_cpu_backend_context",
        ":graph_info",
        ":kernel_api",
        ":macros",
        ":memory_planner",
        ":minimal_logging",
        ":mutable_op_resolver",
        ":optional_debug_tools",
        ":shared_library",
        ":simple_memory_arena",
        ":stderr_reporter",
        ":string",
        ":type_to_tflitetype",
        ":util",
        ":version",
        "//tensorflow/lite/c:common",
        "//tensorflow/lite/core/api",
        "//tensorflow/lite/core/api:verifier",
        "//tensorflow/lite/delegates:status",
        "//tensorflow/lite/experimental/resource",
        "//tensorflow/lite/kernels/internal:compatibility",
        "//tensorflow/lite/profiling:platform_profiler",
        "//tensorflow/lite/schema:schema_fbs",
        "//tensorflow/lite/schema:schema_utils",
    ],
    alwayslink = 1,  # Why?? TODO(b/161243354): eliminate this.
)

# The public target for the full C++ API.
# The deps listed here, other than ":framework_lib", are the interface dependencies
# (dependencies required by the header files).
# TODO(ahentz): investigate dependency on gemm_support requiring usage of tf_copts.
cc_library(
    name = "framework",
    srcs = [],
    hdrs = FRAMEWORK_LIB_HDRS,
    compatible_with = get_compatible_with_portable(),
    copts = tflite_copts() + TFLITE_DEFAULT_COPTS,
    deps = [
        ":allocation",
        ":arena_planner",
        ":cc_api",
        ":external_cpu_backend_context",
        ":framework_lib",
        ":graph_info",
        ":memory_planner",
        ":minimal_logging",
        ":simple_memory_arena",
        ":string",
        ":type_to_tflitetype",
        ":util",
        ":version",
        "//tensorflow/lite/c:common",
        "//tensorflow/lite/core/api",
        "//tensorflow/lite/core/api:verifier",
        "//tensorflow/lite/experimental/resource",
        "//tensorflow/lite/schema:schema_fbs",
    ],
)

# The key parts of the C++ API.  This target defines the TF Lite classes for
# loading models and interpreting them.
cc_library(
    name = "cc_api",
    srcs = [
        "core/subgraph.cc",
        "graph_info.cc",
        "interpreter.cc",
        "interpreter_builder.cc",
        "model_builder.cc",
    ],
    hdrs = [
        "core/subgraph.h",
        "graph_info.h",
        "interpreter.h",
        "interpreter_builder.h",
        "model.h",
        "model_builder.h",
    ],
    compatible_with = get_compatible_with_portable(),
    copts = tflite_copts() + TFLITE_DEFAULT_COPTS,
    visibility = [
        "//tensorflow/lite/core/shims:__subpackages__",
        "//tensorflow/lite/kernels:__subpackages__",
    ],
    deps = [
        ":allocation",
        ":arena_planner",
        ":external_cpu_backend_context",
        ":graph_info",
        ":kernel_api",
        ":macros",
        ":memory_planner",
        ":minimal_logging",
        ":mutable_op_resolver",
        ":shared_library",
        ":simple_memory_arena",
        ":stderr_reporter",
        ":string",
        ":type_to_tflitetype",
        ":util",
        ":version",
        "//tensorflow/lite/c:common",
        "//tensorflow/lite/core/api",
        "//tensorflow/lite/core/api:verifier",
        "//tensorflow/lite/delegates:status",
        "//tensorflow/lite/experimental/resource",
        "//tensorflow/lite/kernels/internal:compatibility",
        "//tensorflow/lite/profiling:platform_profiler",
        "//tensorflow/lite/schema:schema_fbs",
        "//tensorflow/lite/schema:schema_utils",
    ],
    alwayslink = 1,  # Why?? TODO(b/161243354): eliminate this.
)

cc_library(
    name = "optional_debug_tools",
    srcs = [
        "optional_debug_tools.cc",
    ],
    hdrs = ["optional_debug_tools.h"],
    compatible_with = get_compatible_with_portable(),
    copts = tflite_copts() + TFLITE_DEFAULT_COPTS,
    visibility = [
        "//visibility:public",
    ],
    deps = [
        ":macros",
        "//tensorflow/lite:cc_api",
        "//tensorflow/lite/c:common",
        "//tensorflow/lite/schema:schema_fbs",
    ],
)

cc_library(
    name = "error_reporter",
    hdrs = ["error_reporter.h"],
    compatible_with = get_compatible_with_portable(),
    copts = tflite_copts() + TFLITE_DEFAULT_COPTS,
    visibility = [
        "//visibility:public",
    ],
    deps = [
        "//tensorflow/lite:stderr_reporter",
        "//tensorflow/lite/core/api:error_reporter",
    ],
)

cc_library(
    name = "stderr_reporter",
    srcs = ["stderr_reporter.cc"],
    hdrs = ["stderr_reporter.h"],
    compatible_with = get_compatible_with_portable(),
    copts = tflite_copts() + TFLITE_DEFAULT_COPTS,
    visibility = [
        "//visibility:public",
    ],
    deps = [
        ":minimal_logging",
        "//tensorflow/lite/c:common",
        "//tensorflow/lite/core/api:error_reporter",
    ],
)

cc_library(
    name = "op_resolver",
    hdrs = ["op_resolver.h"],
    compatible_with = get_compatible_with_portable(),
    copts = tflite_copts() + TFLITE_DEFAULT_COPTS,
    visibility = [
        "//visibility:public",
    ],
    deps = [
        "//tensorflow/lite:mutable_op_resolver",
        "//tensorflow/lite/core/api:op_resolver",
    ],
)

cc_library(
    name = "mutable_op_resolver",
    srcs = ["mutable_op_resolver.cc"],
    hdrs = ["mutable_op_resolver.h"],
    compatible_with = get_compatible_with_portable(),
    copts = tflite_copts() + TFLITE_DEFAULT_COPTS,
    visibility = [
        "//visibility:public",
    ],
    deps = [
        ":util",
        "//tensorflow/lite/core/api:op_resolver",
        "//tensorflow/lite/schema:schema_fbs",
    ],
)

cc_library(
    name = "string_util",
    srcs = ["string_util.cc"],
    hdrs = ["string_util.h"],
    compatible_with = get_compatible_with_portable(),
    copts = TFLITE_DEFAULT_COPTS,
    deps = [
        ":string",
        "//tensorflow/lite/c:common",
    ],
)

# Link this library to inject XNNPACK delegate to TFLite runtime automatically
# by utilizing the weak symbols if they're supported by the platform.
cc_library(
    name = "tflite_with_xnnpack",
    srcs = ["tflite_with_xnnpack.cc"],
    copts = tflite_copts() + TFLITE_DEFAULT_COPTS,
    linkstatic = True,
    deps = [
        "//tensorflow/lite/c:common",
        "//tensorflow/lite/delegates/xnnpack:xnnpack_delegate",
    ],
    alwayslink = 1,
)

# Enables applying XNNPACK delegate for float models in TFLite runtime.
# WARNING: This build flag is experimental and subject to change.
config_setting(
    name = "tflite_with_xnnpack_explicit_true",
    define_values = {"tflite_with_xnnpack": "true"},
)

config_setting(
    name = "tflite_with_xnnpack_explicit_false",
    define_values = {"tflite_with_xnnpack": "false"},
)

cc_library(
    name = "tflite_with_xnnpack_enabled",
    defines = ["TFLITE_BUILD_WITH_XNNPACK_DELEGATE"],
    visibility = ["//visibility:private"],
    deps = [
        "//tensorflow/lite/delegates/xnnpack:xnnpack_delegate",
    ],
)

cc_library(
    name = "tflite_with_xnnpack_default",
    compatible_with = get_compatible_with_portable(),
    visibility = ["//visibility:private"],
    # TODO(b/151246885): put ":tflite_with_xnnpack_enabled" to macos/windows
    # once we have a good testing coverage on these two platforms.
    deps = select({
        "//tensorflow:macos": [],
        "//tensorflow:windows": [],
        "//conditions:default": [],
    }),
)

cc_library(
    name = "tflite_with_xnnpack_optional",
    srcs = ["tflite_with_xnnpack_optional.cc"],
    hdrs = [
        "core/macros.h",
        "tflite_with_xnnpack_optional.h",
    ],
    compatible_with = get_compatible_with_portable(),
    copts = tflite_copts() + TFLITE_DEFAULT_COPTS,
    deps = [
        "//tensorflow/lite/c:common",
    ] + select({
        ":tflite_with_xnnpack_explicit_true": [
            "//tensorflow/lite/delegates/xnnpack:xnnpack_delegate_hdrs_only",
            ":tflite_with_xnnpack_enabled",
        ],
        ":tflite_with_xnnpack_explicit_false": [],
        "//conditions:default": [
            "//tensorflow/lite/delegates/xnnpack:xnnpack_delegate_hdrs_only",
            ":tflite_with_xnnpack_default",
        ],
    }),
)

cc_test(
    name = "string_util_test",
    size = "small",
    srcs = ["string_util_test.cc"],
    features = ["-dynamic_link_test_srcs"],  # see go/dynamic_link_test_srcs
    deps = [
        ":framework",
        ":string_util",
        "//tensorflow/lite/c:common",
        "//tensorflow/lite/testing:util",
        "@com_google_googletest//:gtest",
    ],
)

# Test main interpreter
cc_test(
    name = "interpreter_test",
    size = "small",
    srcs = [
        "interpreter_test.cc",
    ],
    features = ["-dynamic_link_test_srcs"],  # see go/dynamic_link_test_srcs
    tags = [
        "tflite_not_portable_ios",  # TODO(b/173711739)
        "tflite_smoke_test",
    ],
    deps = [
        ":builtin_op_data",
        ":external_cpu_backend_context",
        ":framework",
        ":string_util",
        ":util",
        ":version",
        "//tensorflow/lite/core/api",
        "//tensorflow/lite/kernels:builtin_ops",
        "//tensorflow/lite/kernels:cpu_backend_context",
        "//tensorflow/lite/kernels:kernel_util",
        "//tensorflow/lite/kernels/internal:compatibility",
        "//tensorflow/lite/schema:schema_fbs",
        "//tensorflow/lite/testing:util",
        "//third_party/eigen3",
        "@com_google_googletest//:gtest",
    ],
)

# Test graph utils
cc_test(
    name = "graph_info_test",
    size = "small",
    srcs = ["graph_info_test.cc"],
    features = ["-dynamic_link_test_srcs"],  # see go/dynamic_link_test_srcs
    deps = [
        ":framework",
        "//tensorflow/lite/testing:util",
        "@com_google_googletest//:gtest",
    ],
)

# Test arena allocator
cc_test(
    name = "simple_memory_arena_test",
    size = "small",
    srcs = ["simple_memory_arena_test.cc"],
    features = ["-dynamic_link_test_srcs"],  # see go/dynamic_link_test_srcs
    deps = [
        ":simple_memory_arena",
        "//tensorflow/core:tflite_portable_logging",
        "//tensorflow/lite/testing:util",
        "@com_google_googletest//:gtest",
    ],
)

# Test model framework.
cc_test(
    name = "model_test",
    size = "small",
    srcs = ["model_test.cc"],
    data = [
        "testdata/0_subgraphs.bin",
        "testdata/2_subgraphs.bin",
        "testdata/add_shared_tensors.bin",
        "testdata/empty_model.bin",
        "testdata/multi_add_flex.bin",
        "testdata/segment_sum_invalid_buffer.bin",
        "testdata/sparse_tensor.bin",
        "testdata/test_min_runtime.bin",
        "testdata/test_model.bin",
        "testdata/test_model_broken.bin",
    ],
    tags = [
        "tflite_not_portable",
        "tflite_smoke_test",
    ],
    deps = [
        ":framework",
        "//tensorflow/lite/core/api",
        "//tensorflow/lite/kernels:builtin_ops",
        "//tensorflow/lite/testing:util",
        "@com_google_googletest//:gtest",
    ],
)

# Test model framework with the flex library linked into the target.
tf_cc_test(
    name = "model_flex_test",
    size = "small",
    srcs = ["model_flex_test.cc"],
    data = [
        "testdata/multi_add_flex.bin",
    ],
    tags = [
        "no_gpu",  # GPU + flex is not officially supported.
        "no_windows",  # TODO(b/116667551): No weak symbols with MSVC.
        "tflite_not_portable_android",
        "tflite_not_portable_ios",
    ],
    deps = [
        ":framework",
        "//tensorflow/lite/core/api",
        "//tensorflow/lite/delegates/flex:delegate",
        "//tensorflow/lite/kernels:builtin_ops",
        "//tensorflow/lite/testing:util",
        "@com_google_googletest//:gtest",
    ],
)

# Test model framework with the XNNPACK delegate.
cc_test(
    name = "model_xnnpack_test",
    size = "small",
    srcs = [
        "model_xnnpack_test.cc",
    ],
    data = [
        "testdata/multi_add.bin",
    ],
    tags = [
        "no_windows",  # No weak symbols with MSVC.
        "tflite_not_portable_android",
        "tflite_not_portable_ios",
        "tflite_smoke_test",
    ],
    deps = [
        ":framework",
        ":tflite_with_xnnpack",
        ":util",
        "//tensorflow/lite/c:common",
        "//tensorflow/lite/kernels:builtin_ops",
        "@com_google_googletest//:gtest_main",
    ],
)

# Test OpResolver.
cc_test(
    name = "mutable_op_resolver_test",
    size = "small",
    srcs = ["mutable_op_resolver_test.cc"],
    features = ["-dynamic_link_test_srcs"],  # see go/dynamic_link_test_srcs
    deps = [
        ":framework",
        "//tensorflow/lite/testing:util",
        "@com_google_googletest//:gtest",
    ],
)

cc_test(
    name = "stderr_reporter_test",
    srcs = ["stderr_reporter_test.cc"],
    deps = [
        ":stderr_reporter",
        "@com_google_googletest//:gtest_main",
    ],
)

cc_library(
    name = "util",
    srcs = ["util.cc"],
    hdrs = ["util.h"],
    compatible_with = get_compatible_with_portable(),
    copts = TFLITE_DEFAULT_COPTS + tflite_copts(),
    deps = [
        ":kernel_api",
        "//tensorflow/lite/c:common",
        "//tensorflow/lite/schema:schema_fbs",
    ],
)

cc_test(
    name = "util_test",
    size = "small",
    srcs = ["util_test.cc"],
    features = ["-dynamic_link_test_srcs"],  # see go/dynamic_link_test_srcs
    deps = [
        ":util",
        "//tensorflow/lite/c:common",
        "//tensorflow/lite/schema:schema_fbs",
        "@com_google_googletest//:gtest",
    ],
)

cc_library(
    name = "minimal_logging",
    srcs = [
        "minimal_logging.cc",
    ] + select({
        "//tensorflow:android": [
            "minimal_logging_android.cc",
        ],
        "//tensorflow:ios": [
            "minimal_logging_ios.cc",
        ],
        "//tensorflow:macos": [
            "minimal_logging_default.cc",
        ],
        "//conditions:default": [
            "minimal_logging_default.cc",
        ],
    }),
    hdrs = ["minimal_logging.h"],
    compatible_with = get_compatible_with_portable(),
    copts = TFLITE_DEFAULT_COPTS + tflite_copts(),
    linkopts = select({
        "//tensorflow:android": ["-llog"],
        "//conditions:default": [],
    }),
    visibility = [
        "//tensorflow/lite:__subpackages__",
    ],
)

cc_library(
    name = "type_to_tflitetype",
    hdrs = [
        "portable_type_to_tflitetype.h",
    ] + select({
        ":tf_lite_static_memory": [],
        "//conditions:default": [
            "type_to_tflitetype.h",
        ],
    }),
    compatible_with = get_compatible_with_portable(),
    deps = ["//tensorflow/lite/c:common"],
)

cc_test(
    name = "type_to_tflitetype_test",
    size = "small",
    srcs = ["type_to_tflitetype_test.cc"],
    deps = [
        ":type_to_tflitetype",
        "@com_google_googletest//:gtest_main",
    ],
)

cc_test(
    name = "minimal_logging_test",
    size = "small",
    srcs = ["minimal_logging_test.cc"],
    tags = [
        "tflite_not_portable_ios",  # TODO(b/173711739)
    ],
    deps = [
        ":minimal_logging",
        "@com_google_googletest//:gtest",
    ],
)

cc_library(
    name = "shared_library",
    hdrs = ["shared_library.h"],
    compatible_with = get_compatible_with_portable(),
    linkopts = if_not_windows(["-ldl"]),
)

cc_library(
    name = "macros",
    hdrs = ["core/macros.h"],
    compatible_with = get_compatible_with_portable(),
)

cc_library(
    name = "stateful_error_reporter",
    hdrs = ["stateful_error_reporter.h"],
    compatible_with = get_compatible_with_portable(),
    deps = ["//tensorflow/lite/core/api"],
)

# Shared lib target for convenience, pulls in the core runtime and builtin ops.
# Note: This target is not yet finalized, and the exact set of exported (C/C++)
# APIs is subject to change. The output library name is platform dependent:
#   - Linux/Android: `libtensorflowlite.so`
#   - Mac: `libtensorflowlite.dylib`
#   - Windows: `tensorflowlite.dll`
tflite_cc_shared_object(
    name = "tensorflowlite",
    # Until we have more granular symbol export for the C++ API on Windows,
    # export all symbols.
    features = ["windows_export_all_symbols"],
    linkopts = select({
        "//tensorflow:macos": [
            "-Wl,-exported_symbols_list,$(location //tensorflow/lite:tflite_exported_symbols.lds)",
        ],
        "//tensorflow:windows": [],
        "//conditions:default": [
            "-Wl,-z,defs",
            "-Wl,--version-script,$(location //tensorflow/lite:tflite_version_script.lds)",
        ],
    }),
    per_os_targets = True,
    deps = [
        ":framework",
        ":tflite_exported_symbols.lds",
        ":tflite_version_script.lds",
        "//tensorflow/lite/kernels:builtin_ops_all_linked",
    ],
)

tflite_portable_test_suite()
