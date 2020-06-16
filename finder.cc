#ifndef FOODFINDER
#define FOODFINDER

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <memory>

#include "include/finder.h"
#include "include/foodAPI.h"
#include "include/exporters.h"

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
  static opencensus::trace::AlwaysSampler sampler;
  std:: cout << "\nWelcome to FoodFinder! Press Ctrl + C anytime you want "
             << "to quit this application. Enjoy!\n\n";
  int count = 0;
  while(true) {
    auto spanUserInput = opencensus::trace::Span::StartSpan(
		        "Finder Loop #" + std::to_string(count) + " (w/ input)",
			nullptr, {&sampler});
    std:: cout << "\n--------------------------------\n\n"
               << "What ingredient would you like to find? ";
    std::getline(std::cin, ingredient);
    auto spanFinder = opencensus::trace::Span::StartSpan(
		        "Finder Loop #" + std::to_string(count),
			&spanUserInput, {&sampler});
    spanFinder.AddAnnotation("\nLooking nearby for " + ingredient + "...\n");
    if(supplier.isSupplied(ingredient, suppliers, &spanFinder)) {
      vendor.getStockInfo(ingredient, suppliers, &spanFinder);
      suppliers = {};
    }
    spanUserInput.End();
    spanFinder.End();

    count++;
  }
}

int main() {
  // Register the OpenCensus gRPC plugin to enable stats and tracing in gRPC.
  grpc::RegisterOpenCensusPlugin();
  RegisterExporters();

  foodFinder();
}

#endif // FOODFINDER
