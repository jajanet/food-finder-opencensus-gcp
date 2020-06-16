#ifndef METRICS
#define METRICS

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <memory>

#include <grpcpp/grpcpp.h>
#include <grpcpp/opencensus.h>
#include "metrics.h"

#include "absl/strings/string_view.h"
#include "absl/strings/str_cat.h"
#include "absl/time/clock.h"
#include "opencensus/stats/stats.h"
#include "opencensus/stats/aggregation.h"
#include "opencensus/stats/bucket_boundaries.h"
#include "opencensus/stats/view_descriptor.h"
#include "opencensus/tags/context_util.h"
#include "opencensus/tags/tag_key.h"

ABSL_CONST_INIT const absl::string_view kLatency = "custom/latency";
ABSL_CONST_INIT const absl::string_view kTraffic = "custom/traffic"; // rpc calls
ABSL_CONST_INIT const absl::string_view kErrors = "custom/errors";
ABSL_CONST_INIT const absl::string_view kSaturation = "custom/saturation";

opencensus::stats::MeasureDouble LatencyMsMeasure() {
  static const auto measure = opencensus::stats::MeasureDouble::Register(
	        kLatency, "Latency (milliseconds)", "ms");
	    return measure;
}
opencensus::stats::MeasureInt64 TrafficMeasure() {
  static const auto measure = opencensus::stats::MeasureInt64::Register(
	        kTraffic, "Aggregate RPC calls", "By");
	    return measure;
}
opencensus::stats::MeasureInt64 ErrorsMeasure() {
  static const auto measure = opencensus::stats::MeasureInt64::Register(
	        kErrors, "Aggregate Errors", "By");
	    return measure;
}
opencensus::stats::MeasureDouble SaturationMeasure() {
  static const auto measure = opencensus::stats::MeasureDouble::Register(
	        kSaturation, "Current System Load", "By");
	    return measure;
}


opencensus::tags::TagKey LatencyMethodKey() {
  return opencensus::tags::TagKey::Register("latency");
}

opencensus::tags::TagKey TrafficMethodKey() {
  return opencensus::tags::TagKey::Register("traffic");
}

opencensus::tags::TagKey ErrorsMethodKey() {
  return opencensus::tags::TagKey::Register("errors");
}

opencensus::tags::TagKey SaturationMethodKey() {
  return opencensus::tags::TagKey::Register("saturation");
}

void RegisterLatencyView() {
  LatencyMsMeasure();
  opencensus::stats::ViewDescriptor()
    .set_name("food/latency")
    .set_description("The various methods' latencies in milliseconds")
    .set_measure(kLatency)
    .set_aggregation(opencensus::stats::Aggregation::Distribution(
        opencensus::stats::BucketBoundaries::Explicit(
                {0, 25, 50, 75, 100, 200, 400, 600,
			800, 1000, 2000, 4000, 6000})))
    .add_column(LatencyMethodKey())
    .RegisterForExport();
}

void RegisterTrafficView() {
  TrafficMeasure();
  opencensus::stats::ViewDescriptor()
    .set_name("foodfinder/traffic")
    .set_description("Number of calls made so far")
    .set_measure(kTraffic)
    .set_aggregation(opencensus::stats::Aggregation::Distribution(
        opencensus::stats::BucketBoundaries::Explicit(
                {0, 25, 50, 75, 100, 200, 400, 600, 800, 1000})))
    .add_column(TrafficMethodKey())
    .RegisterForExport();
}

void RegisterErrorsView() {
  ErrorsMeasure();
  opencensus::stats::ViewDescriptor()
    .set_name("foodfinder/errors")
    .set_description("Errors thrown so far")
    .set_measure(kErrors)
    .set_aggregation(opencensus::stats::Aggregation::Distribution(
        opencensus::stats::BucketBoundaries::Explicit(
                {0, 25, 50, 75, 100, 200, 400, 600, 800, 1000})))
    .add_column(ErrorsMethodKey())
    .RegisterForExport();
}

void RegisterSaturationView() {
  SaturationMeasure();
  opencensus::stats::ViewDescriptor()
    .set_name("foodfinder/saturation")
    .set_description("The various methods' latencies in milliseconds")
    .set_measure(kSaturation)
    .set_aggregation(opencensus::stats::Aggregation::Distribution(
        opencensus::stats::BucketBoundaries::Explicit(
                {0, .1, .2, .3, .4, .5, .6, .7, .8, .9, 1})))
    .add_column(SaturationMethodKey())
    .RegisterForExport();
}

/*
  absl::Time start = absl::Now();
  absl::Time end = absl::Now();
  double latency_ms = absl::ToDoubleMilliseconds(end - start);

  opencensus::stats::Record({{LatencyMsMeasure(), latency_ms}},
	                            {{LatencyMethodKey(), "name"}});

*/ // this is for actually recording latency

#endif // METRICS
