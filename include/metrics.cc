#ifndef METRICS
#define METRICS

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <memory>

#include <grpcpp/grpcpp.h>
#include <grpcpp/opencensus.h>

#include "absl/strings/string_view.h"
#include "absl/strings/str_cat.h"
#include "absl/time/clock.h"
#include "opencensus/stats/stats.h"
#include "opencensus/stats/aggregation.h"
#include "opencensus/stats/bucket_boundaries.h"
#include "opencensus/stats/view_descriptor.h"
#include "opencensus/tags/context_util.h"
#include "opencensus/tags/tag_key.h"

ABSL_CONST_INIT const absl::string_view kLatencyMeasureName = "custom/latency";

opencensus::stats::MeasureDouble LatencyMsMeasure() {
  static const auto measure = opencensus::stats::MeasureDouble::Register(
	        kLatencyMeasureName, "The latency in milliseconds", "ms");
	    return measure;
}

opencensus::tags::TagKey LatencyMethodKey() {
  return opencensus::tags::TagKey::Register("latency");
}

void RegisterLatencyView() {
  LatencyMsMeasure();
  opencensus::stats::ViewDescriptor()
    .set_name("foodfinder/latency")
    .set_description("The various methods' latencies in milliseconds")
    .set_measure(kLatencyMeasureName)
    .set_aggregation(opencensus::stats::Aggregation::Distribution(
        opencensus::stats::BucketBoundaries::Explicit(
                {0, 25, 50, 75, 100, 200, 400, 600,
			800, 1000, 2000, 4000, 6000})))
    .add_column(LatencyMethodKey())
    .RegisterForExport();
}


  absl::Time start = absl::Now();
  absl::Time end = absl::Now();
  double latency_ms = absl::ToDoubleMilliseconds(end - start);

  opencensus::stats::Record({{LatencyMsMeasure(), latency_ms}},
	                            {{LatencyMethodKey(), "name"}});


#endif // METRICS
