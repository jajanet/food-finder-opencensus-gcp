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
    hdrs = ["foodAPI.h"],
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
    srcs = ["exporters.cc"],
    hdrs = ["exporters.h"],
    copts = DEFAULT_COPTS,
    deps = [
        "//opencensus/exporters/stats/stackdriver:stackdriver_exporter",
        "//opencensus/exporters/stats/stdout:stdout_exporter",
        "//opencensus/exporters/trace/ocagent:ocagent_exporter",
        "//opencensus/exporters/trace/stackdriver:stackdriver_exporter",
        "//opencensus/exporters/trace/stdout:stdout_exporter",
        "@com_google_absl//absl/strings",
    ],
)


cc_binary(
    name = "foodFinder",
    srcs = [ "foodFinder.cc", "foodFinder.h" ],
    copts = DEFAULT_COPTS,
    deps = [
        ":foodAPI",
        ":exporters",
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
    name = "foodVendor",
    srcs = [ "foodVendor.cc", "foodVendor.h"],
    copts = DEFAULT_COPTS,
    deps = [
        ":exporters",
        ":food_cc_grpc",
        ":food_cc_proto",
        "//opencensus/exporters/stats/prometheus:prometheus_exporter",
        "//opencensus/tags",
        "//opencensus/tags:context_util",
        "//opencensus/trace",
        "//opencensus/trace:context_util",
        "@com_github_grpc_grpc//:grpc++",
        "@com_github_grpc_grpc//:grpc_opencensus_plugin",
        "@com_github_jupp0r_prometheus_cpp//pull",
        "@com_google_absl//absl/strings",
    ],
)


cc_binary(
    name = "foodSupplier",
    srcs = [ "foodSupplier.cc", "foodSupplier.h"],
    copts = DEFAULT_COPTS,
    deps = [
        ":exporters",
        ":food_cc_grpc",
        ":food_cc_proto",
        "//opencensus/exporters/stats/prometheus:prometheus_exporter",
        "//opencensus/tags",
        "//opencensus/tags:context_util",
        "//opencensus/trace",
        "//opencensus/trace:context_util",
        "@com_github_grpc_grpc//:grpc++",
        "@com_github_grpc_grpc//:grpc_opencensus_plugin",
        "@com_github_jupp0r_prometheus_cpp//pull",
        "@com_google_absl//absl/strings",
    ],
)


'''
cc_library(
    name = "foodVendor",
    srcs = [ "foodVendor.cc" ],
    hdrs = ["foodVendor.h"]
)
'''

'''cc_binary(
    name = "simulate.so",
    srcs = [ "doDelay.cc" ],
    linkshared=True
)

cc_binary(
    name = "vendors.so",
    srcs = [ "vendor_data.cc", "vendor_data.h" ],
    linkshared=True
)

cc_import(
  name = "vendorData",
  shared_library = "vendors.so"
)

cc_import(
  name = "simulate",
  shared_library = "simulate.so"
)
cc_library(
    name = "simulate",
    srcs = [ "doDelay.cc" ],
)

cc_library(
    name = "vendorData",
    srcs = [ "vendor_data.cc", "vendor_data.h" ],
)

'''
