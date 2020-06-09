#ifndef FOODFINDER
#define FOODFINDER

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <memory>

#include "foodFinder.h"
#include "foodAPI.h"
#include "exporters.h"

#include <grpcpp/grpcpp.h>
#include <grpcpp/opencensus.h>

#include "absl/strings/str_cat.h"
#include "absl/time/clock.h"
#include "opencensus/stats/aggregation.h"
#include "opencensus/stats/bucket_boundaries.h"
#include "opencensus/stats/view_descriptor.h"
#include "opencensus/tags/context_util.h"
#include "opencensus/trace/context_util.h"
#include "opencensus/trace/sampler.h"
#include "opencensus/trace/trace_config.h"


void foodFinder() {
  // The client Span ends when ctx falls out of scope.
  std::string ingredient = "";
  std::vector<std::string> suppliers;
  SupplierAPI supplier;
  VendorAPI vendor;
  std:: cout << "\nWelcome to FoodFinder! Press Ctrl + C anytime you want "
             << "to quit this application. Enjoy!\n\n";

  while(true) {
    std:: cout << "\n--------------------------------\n\n"
               << "What ingredient would you like to find? ";
    std::getline(std::cin, ingredient);
    std::cout << "\nLooking nearby...\n";

    if(supplier.isSupplied(ingredient, suppliers)) {
      vendor.getStockInfo(ingredient, suppliers);
      suppliers = {};
    }

  }
}

int main() {
  // Register the OpenCensus gRPC plugin to enable stats and tracing in gRPC.
  grpc::RegisterOpenCensusPlugin();
  RegisterExporters();

  foodFinder();
      /*/ Disable tracing any further RPCs (which will be sent by exporters).
  opencensus::trace::TraceConfig::SetCurrentTraceParams(
      {128, 128, 128, 128, opencensus::trace::ProbabilitySampler(0.0)});
  */
}

#endif // FOODFINDER
