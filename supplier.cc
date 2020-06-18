#ifndef FOODSUPPLIER
#define FOODSUPPLIER

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <cstdlib>
#include <memory>

#include "include/supplier.h"
#include "include/metrics.h"
#include "include/exporters.h"
#include "include/simulatedProcessing.h"
#include "food.grpc.pb.h"
#include "food.pb.h"
#include <grpcpp/grpcpp.h>
#include <grpcpp/opencensus.h>

#include "absl/strings/escaping.h"
#include "absl/strings/numbers.h"
#include "absl/strings/str_cat.h"
#include "opencensus/stats/stats.h"
#include "opencensus/tags/context_util.h"
#include "opencensus/tags/tag_map.h"
#include "opencensus/trace/context_util.h"
#include "opencensus/trace/sampler.h"
#include "opencensus/trace/span.h"
#include "opencensus/trace/trace_config.h"


class SupplierService final : public food::Supplier::Service {
  // Return stores with an ingredient
  grpc::Status GetStores(grpc::ServerContext *context,
                    const food::ItemQuery* query,
                    food::StoreReply* reply) override {

    // Track to create latency metrics
    absl::Time start = absl::Now();

    // Add to existing span given by the context the client sent
    auto span = grpc::GetSpanFromServerContext(context);
    span.AddAttribute("Supplier", "red");
    span.AddAnnotation("Getting stores");
    doDelay(&span);

    auto vendorInfo = getVendorOfferings(); // Metadata

    // Find relevant stores and add to the reply as neccessary
    for (auto &vendorPair : vendorInfo) {
      if (vendorPair.second.find(query->item()) != vendorPair.second.end()) {
        reply->add_stores(vendorPair.first);
      }
    }

    span.AddAnnotation("Request for " + query->item());
    std::cout << "Testing: " << span.context().ToString() << "\n";
    absl::Time end = absl::Now();
    double latency_ms = absl::ToDoubleMilliseconds(end - start);

    opencensus::stats::Record({{LatencyMsMeasure(), latency_ms}},
	                            {{LatencyMethodKey(), "name"}});
    return randomlyFailedStatus();
  }
};

void foodSupplier() {
  const std::string port = "127.0.0.1:8888";

  // Register OpenCensus gRPC plugin to enable stats and tracing in gRPC.
  grpc::RegisterOpenCensusPlugin();

  // Register the gRPC views (latency, error count, etc).
  grpc::RegisterOpenCensusViewsForExport();

  RegisterExporters();
  RegisterLatencyView();

  SupplierService service;
  grpc::ServerBuilder builder;

  builder.AddListeningPort(port, grpc::InsecureServerCredentials());
  builder.RegisterService(&service);
  std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
  std::cout << "Server listening on [::]:" << port << "\n";
  server->Wait();
}

int main() {
  foodSupplier();
}

std::map<std::string, std::set<std::string>> vendorOfferings {
	{"Trader Joes",
		{"yeast", "flour", "sugar", "noodles", "chocolate", "salt"}},
	{"Target",
		{"yeast", "flour", "sugar", "noodles", "salt"}},
	{"Kroger",
		{"yeast", "flour", "noodles", "chocolate", "salt"}},
	{"Aldi",
		{"yeast", "flour", "sugar", "noodles", "chocolate", "salt"}}
};

std::map<std::string, std::set<std::string>> getVendorOfferings() { return vendorOfferings; }

#endif // FOODSUPPLIER
