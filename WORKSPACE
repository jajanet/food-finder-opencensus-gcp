load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

http_archive(
    name = "io_opencensus_cpp",
    strip_prefix = "opencensus-cpp-master",
    urls = ["https://github.com/census-instrumentation/opencensus-cpp/archive/master.zip"],
)

# OpenCensus depends on Abseil so we have to explicitly to pull it in.
# This is how diamond dependencies are prevented.
http_archive(
    name = "com_google_absl",
    strip_prefix = "abseil-cpp-master",
    urls = ["https://github.com/abseil/abseil-cpp/archive/master.zip"]
)

# OpenCensus depends on jupp0r/prometheus-cpp
http_archive(
    name = "com_github_jupp0r_prometheus_cpp",
    strip_prefix = "prometheus-cpp-master",
    urls = ["https://github.com/jupp0r/prometheus-cpp/archive/master.zip"],
)

load("@com_github_jupp0r_prometheus_cpp//bazel:repositories.bzl", "prometheus_cpp_repositories")

prometheus_cpp_repositories()
