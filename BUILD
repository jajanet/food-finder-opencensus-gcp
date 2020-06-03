cc_binary(
    name = "foodFinder",
    srcs = [ "foodFinder.cc" ],
    linkopts = ["-pthread"],
    deps = [
        ":foodSupplier",
        ":foodVendor",
        "@com_github_jupp0r_prometheus_cpp//pull",
        "@com_google_absl//absl/base:core_headers",
        "@com_google_absl//absl/memory",
        "@com_google_absl//absl/strings",
        "@io_opencensus_cpp//opencensus/exporters/stats/prometheus:prometheus_exporter",
        "@io_opencensus_cpp//opencensus/stats",
        "@io_opencensus_cpp//opencensus/tags",
     ],
#    linkshared=True
)

cc_library(    name = "foodSupplier",
    srcs = [ "foodSupplier.cc" ],
    hdrs = ["foodSupplier.h"]
)

cc_library(
    name = "foodVendor",
    srcs = [ "foodVendor.cc" ],
    hdrs = ["foodVendor.h"]
)


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
