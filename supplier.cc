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
#include "include/exporters.h"
#include "include/simulatedProcessing.h"
#include "food.grpc.pb.h"
#include "food.pb.h"
#include <grpcpp/grpcpp.h>
#include <grpcpp/opencensus.h>

#include "absl/strings/escaping.h"
#include "absl/strings/numbers.h"
#include "absl/strings/str_cat.h"
#include "opencensus/exporters/stats/prometheus/prometheus_exporter.h"
#include "opencensus/stats/stats.h"
#include "opencensus/tags/context_util.h"
#include "opencensus/tags/tag_map.h"
#include "opencensus/trace/context_util.h"
#include "opencensus/trace/sampler.h"
#include "opencensus/trace/span.h"
#include "opencensus/trace/trace_config.h"
#include "prometheus/exposer.h"

class SupplierService final : public food::Supplier::Service {
  grpc::Status GetStores (grpc::ServerContext *context,
                    const food::ItemQuery* query,
                    food::StoreReply* reply) {

    opencensus::trace::Span span = grpc::GetSpanFromServerContext(context);
    span.AddAttribute("Supplier", "red");
    span.AddAnnotation("Getting stores.");
    doDelay();

    auto vendorInfo = getVendorOfferings();

    for (auto &vendorPair : vendorInfo) {
      if (vendorPair.second.find(query->item()) != vendorPair.second.end()) {
        reply->add_stores(vendorPair.first);
      }
    }
    std::cout << "Request for " << query->item() << "\n";
    return randomlyFailedStatus;
  }
};

void foodSupplier(){
  const std::string port = "127.0.0.1:8888";

  // Register the OpenCensus gRPC plugin to enable stats and tracing in gRPC.
  grpc::RegisterOpenCensusPlugin();

  // Register the gRPC views (latency, error count, etc).
  grpc::RegisterOpenCensusViewsForExport();

  RegisterExporters();

  // Keep a shared pointer to the Prometheus exporter.
  auto exporter =
      std::make_shared<opencensus::exporters::stats::PrometheusExporter>();

  // Expose a Prometheus endpoint.
  prometheus::Exposer exposer("127.0.0.1:8080");
  exposer.RegisterCollectable(exporter);

  grpc::ServerBuilder builder;
  SupplierService service;

  builder.AddListeningPort(port, grpc::InsecureServerCredentials());
  builder.RegisterService(&service);
  std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
  std::cout << "Server listening on [::]:" << port << "\n";
  server->Wait();

}

int main(){
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
