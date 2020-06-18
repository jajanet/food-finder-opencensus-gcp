# Summary
Search for information on ingedients, such as available vendors and an ingredient's remaining stock and current price at those vendors. The ingredient and vendor information is currently stored metadata at their respective servers.

This Project that demostrates usage of:
- RCP server-client communication (gRPC)
- Tracing and monitoring (OpenCensus)
- Exporting traces and metrics (Stackdriver to Google Cloud Platform) 
- Building projects using Bazel with internal and external dependencies


# Requirements
## Prerequisites
See 'References' at the bottom of this README for installation needs, as Food Finder shares.


## Exporting
Food Finder uses Stackdriver for exporting. To see data exported to Google Cloud Platform (GCP), your code must be in a GCE VM instance and ran there; you also need to set your project ID in 'include/exporters.cc' to see your metrics and tracing sent to that project. Exporting to GCP setup is similar to the OpenCensus GRPC reference [1], i.e. you need to enable the GCP monitoring and tracing APIs with Service Account access.

Otherwise, stats and tracing only shows in the terminal and isn't recorded out of the box.


## Building
`bazel build :all`


## Running
FoodSupplier Server

`./bazel-bin/supplier`

FoodVendor Server

`./bazel-bin/vendor`

FoodFinder Client

`./bazel-bin/finder`


## Using
Enter ingredients to get vendor and ingredient information. Currently available ingredients: yeast, flour, sugar, noodles, chocolate, salt

### View Monitoring Data on GCP
Traces: https://console.cloud.google.com/traces/traces

Metrics (click on 'Metrics explorer'): https://console.cloud.google.com/monitoring


# Possible Future Changes
- Add more tracing and metrics tracking
- Code and dependency cleanup

# References
- https://github.com/census-instrumentation/opencensus-cpp/tree/master/examples/grpc [1]
- https://opencensus.io/quickstart/cpp/tracing/ [2]
- https://opencensus.io/quickstart/cpp/metrics/ [3]


