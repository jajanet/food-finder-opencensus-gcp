#ifndef FOODVENDOR
#define FOODVENDOR

#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "include/vendor.h"
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

static opencensus::trace::AlwaysSampler sampler;

class VendorService final : public food::Vendor::Service {
  grpc::Status GetItemInfo (grpc::ServerContext *context,
                    const food::ItemStoreQuery* query,
                    food::ItemInfoReply* reply) {
  auto span = grpc::GetSpanFromServerContext(context);
  std::string store = query->store();
  std::string item = query->item();

  int stock = getVendorStock()[store][item];
  double price = getVendorPrices()[store][item];

  reply->set_price(price);
  reply->set_inventory(stock);
  
  doDelay();
  span.AddAnnotation("Checking price and stock for " + item
		  + " at " + store + "\n");
  span.End();

  return randomlyFailedStatus();
  }
};

void foodVendor(){
  const std::string port = "127.0.0.1:8889";

  // Register the OpenCensus gRPC plugin to enable stats and tracing in gRPC.
  grpc::RegisterOpenCensusPlugin();

  // Register the gRPC views (latency, error count, etc).
  grpc::RegisterOpenCensusViewsForExport();

  RegisterExporters();

  grpc::ServerBuilder builder;
  VendorService service;

  builder.AddListeningPort(port, grpc::InsecureServerCredentials());
  builder.RegisterService(&service);
  std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
  std::cout << "Server listening on [::]:" << port << "\n";
  server->Wait();

}

int main(){
  foodVendor();
}

std::map<std::string, std::map<std::string, double>> vendorPrices {
{"Trader Joes", {
  {"yeast", 4.49},
  {"flour", 1.71},
  {"sugar", 3.28},
  {"noodles", 4.19},
  {"chocolate", 2.12},
  {"salt", 3.99},
}},
{"Target", {
  {"yeast", 4.04},
  {"flour", 0.9},
  {"sugar", 4.23},
  {"noodles", 4.35},
  {"salt", 3.54},
}},
{"Kroger", {
  {"yeast", 2.0},
  {"flour", 2.49},
  {"noodles", 4.06},
  {"chocolate", 4.96},
  {"salt", 4.59}
}},
{"Aldi", {
  {"yeast", 3.49},
  {"flour", 4.6},
  {"sugar", 3.59},
  {"noodles", 0.73},
  {"chocolate", 4.13},
  {"salt", 4.8}
  }}
};

std::map<std::string, std::map<std::string, int>> vendorStock {
{"Trader Joes", {
  {"yeast", 34},
  {"flour", 55},
  {"sugar", 0},
  {"noodles", 69},
  {"chocolate", 7},
  {"salt", 34}
}},
{"Target", {
  {"yeast", 51},
  {"flour", 37},
  {"sugar", 48},
  {"noodles", 92},
  {"salt", 18}
}},
{"Kroger", {
  {"yeast", 33},
  {"flour", 5},
  {"noodles", 39},
  {"chocolate", 27},
  {"salt", 45}
}},
{"Aldi", {
  {"yeast", 21},
  {"flour", 7},
  {"sugar", 68},
  {"noodles", 99},
  {"chocolate", 42},
  {"salt", 1}
}},
};

std::map<std::string, std::map<std::string, double>> getVendorPrices () { return vendorPrices; }
std::map<std::string, std::map<std::string, int>> getVendorStock () { return vendorStock; }


#endif // FOODVENDOR
