#ifndef FOODFINDER
#define FOODFINDER

#include <iostream>
#include <string>
#include <vector>
#include "foodSupplier.h"
#include "foodVendor.h"
#include "absl/strings/string_view.h"
#include "absl/time/clock.h"
#include "opencensus/exporters/stats/prometheus/prometheus_exporter.h"
#include "opencensus/stats/stats.h"
#include "opencensus/tags/tag_key.h"
#include "prometheus/exposer.h"
//#include "vendor_data.cc"

typedef void FoodAPI (std::string const& ingredient, std::vector<std::string>&suppliers);

namespace {

ABSL_CONST_INIT const absl::string_view kLatencyMeasureName = "repl/latency";
ABSL_CONST_INIT const absl::string_view kLineLengthsMeasureName =
    "repl/line_lengths";

// Treat Measures and TagKeys as singletons and initialize on
// demand in order to avoid initialization order issues.

opencensus::stats::MeasureDouble LatencyMsMeasure() {
  static const auto measure = opencensus::stats::MeasureDouble::Register(
      kLatencyMeasureName, "The latency in milliseconds", "ms");
  return measure;
}

opencensus::stats::MeasureInt64 LineLengthsMeasure() {
  static const auto measure = opencensus::stats::MeasureInt64::Register(
      kLineLengthsMeasureName, "The distributions of line lengths", "By");
  return measure;
}

opencensus::tags::TagKey MethodKey() {
  static const auto key = opencensus::tags::TagKey::Register("method");
  return key;
}

void RegisterViews() {
  // 1. Latency view
  // We need to register the measure before registering the view.
  LatencyMsMeasure();
  opencensus::stats::ViewDescriptor()
      .set_name("ocquickstart.io/latency")
      .set_description("The various methods' latencies in milliseconds")
      .set_measure(kLatencyMeasureName)
      .set_aggregation(opencensus::stats::Aggregation::Distribution(
          opencensus::stats::BucketBoundaries::Explicit(
              {0, 25, 50, 75, 100, 200, 400, 600, 800, 1000, 2000, 4000,
               6000})))
      .add_column(MethodKey())
      .RegisterForExport();

  // 2. Line lengths
  LineLengthsMeasure();
  opencensus::stats::ViewDescriptor()
      .set_name("ocquickstart.io/line_lengths")
      .set_description("The length of the lines read in")
      .set_measure(kLineLengthsMeasureName)
      .set_aggregation(opencensus::stats::Aggregation::Distribution(
          opencensus::stats::BucketBoundaries::Explicit(
              {0, 5, 10, 15, 20, 40, 60, 80, 100, 200, 400, 600, 800,
               1000})))
      .add_column(MethodKey())
      .RegisterForExport();

  // 3. Lines count: just a count aggregation on the line lengths measure
  opencensus::stats::ViewDescriptor()
      .set_name("ocquickstart.io/lines_in")
      .set_description("The number of lines read in")
      .set_measure(kLineLengthsMeasureName)
      .set_aggregation(opencensus::stats::Aggregation::Count())
      .add_column(MethodKey())
      .RegisterForExport();
}


std::string getLine() {
  absl::Time start = absl::Now();

  std::string input;

  // Get the line
  std::getline(std::cin, input);

  absl::Time end = absl::Now();
  double latency_ms = absl::ToDoubleMilliseconds(end - start);

  // Record both measures at once.
  opencensus::stats::Record({{LatencyMsMeasure(), latency_ms},
                             {LineLengthsMeasure(), input.length()}},
                            {{MethodKey(), "getLine"}});
  return input;
}

void callFoodAPI(FoodAPI api, std::string const& ingredient, std::vector<std::string>&suppliers) {
  absl::Time start = absl::Now();
  api(ingredient, suppliers);
  absl::Time end = absl::Now();
  double latency_ms = absl::ToDoubleMilliseconds(end - start);

  opencensus::stats::Record({{LatencyMsMeasure(), latency_ms}},
                            {{MethodKey(), "callFoodAPI"}});
}

} //namespace

/*
 * Gets ingredient from user, then consults
 * FoodSupplier and FoodVendor to find
 * inventory and prices for that ingredient
 *
*/
void FoodFinder () {
  // Firstly enable the Prometheus exporter
  auto exporter =
      std::make_shared<opencensus::exporters::stats::PrometheusExporter>();
  // Expose Prometheus on :8888
  prometheus::Exposer exposer("127.0.0.1:8888");
  exposer.RegisterCollectable(exporter);

  // Register the views to enable stats aggregation
  RegisterViews();

  std::vector<std::string> suppliers;
  while (1) {
  std:: cout << "What ingredient would you like to find nearby? ";
  std::string ingredient = getLine();

  callFoodAPI(FoodSupplier, ingredient, suppliers);
  if (suppliers.size() > 0) callFoodAPI(FoodVendor, ingredient, suppliers);
  else std::cout << ingredient << " not found!\n";

  suppliers = {};
  }

}

int main() {
  FoodFinder();
}

#endif // FOODFINDER
