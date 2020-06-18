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
  static opencensus::trace::AlwaysSampler sampler;
  std::string ingredient = "";
  std::vector<std::string> suppliers;

  // Initialize API classes to create channels to connect to
  SupplierAPI supplier;
  VendorAPI vendor;
  
  std:: cout << "\nWelcome to FoodFinder! Press Ctrl + C anytime you want to "
             << "quit. Valid ingredients are found in ./README.md. Enjoy!\n\n";

  int count = 0; // Use count variable to track individual cycles
  while (true) {
    auto spanUserInput = opencensus::trace::Span::StartSpan(
		        "Finder Loop #" + std::to_string(count) + " (input)",
			nullptr, {&sampler}); // Span to time user input too

    std::getline(std::cin, ingredient);

    auto spanFinder = opencensus::trace::Span::StartSpan(
		        "Finder Loop #" + std::to_string(count),
			&spanUserInput, {&sampler});
    spanFinder.AddAnnotation("\nLooking nearby for " + ingredient + "...\n");

    // Only call vendor if the inputted ingredient is supplied
    if (supplier.isSupplied(ingredient, suppliers, &spanFinder)) {
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
