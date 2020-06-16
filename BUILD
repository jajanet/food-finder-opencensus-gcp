load("//opencensus:copts.bzl", "DEFAULT_COPTS", "TEST_COPTS")
load("@com_github_grpc_grpc//bazel:cc_grpc_library.bzl", "cc_grpc_library")


proto_library(
    name = "food_proto",
    srcs = ["food.proto"],
)

cc_proto_library(
    name = "food_cc_proto",
    deps = [":food_proto"],
)

cc_grpc_library(
    name = "food_cc_grpc",
    srcs = [":food_proto"],
    grpc_only = True,
    deps = [":food_cc_proto"],
)


cc_library(
    name = "foodAPI",
    srcs = ["foodAPI.cc"],
    hdrs = ["include/foodAPI.h"],
    copts = DEFAULT_COPTS,
    deps = [
        ":food_cc_grpc",
        ":food_cc_proto",
        "//opencensus/tags",
        "//opencensus/tags:context_util",
        "//opencensus/tags:with_tag_map",
        "//opencensus/trace",
        "//opencensus/trace:context_util",
        "//opencensus/trace:with_span",
        "@com_github_grpc_grpc//:grpc++",
        "@com_github_grpc_grpc//:grpc_opencensus_plugin",
        "@com_google_absl//absl/strings",
        "@com_google_absl//absl/time",
    ],
)

cc_library(
    name = "exporters",
    srcs = ["include/exporters.cc"],
    hdrs = ["include/exporters.h"],
    copts = DEFAULT_COPTS,
    deps = [
        "//opencensus/exporters/stats/stackdriver:stackdriver_exporter",
        "//opencensus/exporters/stats/stdout:stdout_exporter",
        "//opencensus/exporters/trace/stackdriver:stackdriver_exporter",
        "//opencensus/exporters/trace/stdout:stdout_exporter",
        "@com_google_absl//absl/strings",
    ],
)

cc_library(
    name = "metrics",
    srcs = ["include/metrics.cc"],
    hdrs = ["include/metrics.h"],
    copts = DEFAULT_COPTS,
    deps = [
        "@com_google_absl//absl/time",
        "@com_google_absl//absl/strings",
        "@com_github_grpc_grpc//:grpc++",
	"//opencensus/stats",
        "//opencensus/tags",
        "//opencensus/tags:context_util",
        "//opencensus/tags:with_tag_map",
        "//opencensus/trace",
        "//opencensus/trace:context_util",
        "//opencensus/trace:with_span",
        "@com_github_grpc_grpc//:grpc_opencensus_plugin",
    ]
)

cc_library(
    name = "simulatedProcessing",
    srcs = ["include/simulatedProcessing.cc"],
    hdrs = ["include/simulatedProcessing.h"],
    copts = DEFAULT_COPTS,
    deps = [
        "//opencensus/trace",
        "@com_google_absl//absl/time",
        "@com_google_absl//absl/strings",
        "@com_github_grpc_grpc//:grpc++",
    ],
)


cc_binary(
    name = "finder",
    srcs = [ "finder.cc", "include/finder.h" ],
    copts = DEFAULT_COPTS,
    deps = [
        ":simulatedProcessing",
	"foodAPI",
        ":exporters",
        ":metrics",
        ":food_cc_grpc",
        ":food_cc_proto",
        "//opencensus/tags",
        "//opencensus/tags:context_util",
        "//opencensus/tags:with_tag_map",
        "//opencensus/trace",
        "//opencensus/trace:context_util",
        "//opencensus/trace:with_span",
        "@com_github_grpc_grpc//:grpc++",
        "@com_github_grpc_grpc//:grpc_opencensus_plugin",
        "@com_google_absl//absl/strings",
        "@com_google_absl//absl/time",
    ]
)


cc_binary(
    name = "vendor",
    srcs = [ "vendor.cc", "include/vendor.h"],
    copts = DEFAULT_COPTS,
    deps = [
        ":simulatedProcessing",
        ":exporters",
        ":metrics",
        ":food_cc_grpc",
        ":food_cc_proto",
        "//opencensus/tags",
        "//opencensus/tags:context_util",
        "//opencensus/trace",
        "//opencensus/trace:context_util",
        "@com_github_grpc_grpc//:grpc++",
        "@com_github_grpc_grpc//:grpc_opencensus_plugin",
        "@com_google_absl//absl/strings",
    ],
)


cc_binary(
    name = "supplier",
    srcs = [ "supplier.cc", "include/supplier.h"],
    copts = DEFAULT_COPTS,
    deps = [
        ":simulatedProcessing",
        ":exporters",
        ":metrics",
        ":food_cc_grpc",
        ":food_cc_proto",
        "//opencensus/tags",
        "//opencensus/tags:context_util",
        "//opencensus/trace",
        "//opencensus/trace:context_util",
        "@com_github_grpc_grpc//:grpc++",
        "@com_github_grpc_grpc//:grpc_opencensus_plugin",
        "@com_google_absl//absl/strings",
    ],
)


