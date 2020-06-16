# Summary
Search for a ingredients to find available vendors and the ingredient's remaining stock and current price at those vendors. The ingredient and vendor information is currently stored metadata at their respective servers.

Available ingredients to search for (comma separated): yeast, flour, sugar, noodles, chocolate, salt


This Project that demostrates usage of:
- RCP server-client communication (gRPC)
- Tracing and monitoring (OpenCensus)
- Exporting tracing and monitoring (Stackdriver to Google Cloud Platoform) 


# Prerequisites
See other at the bottom of the README for installation needs.

To see data exported to Google Cloud Platform, set your project ID in include/exporters.cc. Otherwise, stats and tracing only shows in terminal


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
