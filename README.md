# To Build:
`bazel build :all`

# To Run:
FoodSupplier Server

`./bazel-bin/supplier`

FoodVendor Server

`./bazel-bin/vendor`

FoodFinder Client

`./bazel-bin/finder`

# Current Progress
- Code implemented with the RPC standard (through gRPC), starter project spec baseline functionality, and a working bazel build

# TODO
- Add more tracing and metrics tracking
- Code cleanup with variables

# Other
Code based off of and has the same install prerequisites as https://github.com/census-instrumentation/opencensus-cpp/tree/master/examples/grpc
