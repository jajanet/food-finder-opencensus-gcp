#ifndef METRICS_H
#define METRICS_H

#include <string>
#include <vector>
#include <cstdlib>
#include <memory>

#include <grpcpp/grpcpp.h>
#include <grpcpp/opencensus.h>

#include "opencensus/stats/stats.h"
#include "opencensus/stats/view_descriptor.h"
#include "opencensus/tags/context_util.h"
#include "opencensus/tags/tag_key.h"

/*
ABSL_CONST_INIT const absl::string_view kLatency = "custom/latency";
ABSL_CONST_INIT const absl::string_view kTraffic = "custom/traffic"; // rpc calls
ABSL_CONST_INIT const absl::string_view kErrors = "custom/errors";
ABSL_CONST_INIT const absl::string_view kSaturation = "custom/saturation";
*/
opencensus::stats::MeasureDouble LatencyMsMeasure();
opencensus::stats::MeasureInt64 TrafficMeasure();
opencensus::stats::MeasureInt64 ErrorsMeasure();
opencensus::stats::MeasureDouble SaturationMeasure();

opencensus::tags::TagKey LatencyMethodKey();
opencensus::tags::TagKey TrafficMethodKey();
opencensus::tags::TagKey ErrorsMethodKey();
opencensus::tags::TagKey SaturationMethodKey();

void RegisterLatencyView();
void RegisterTrafficView();
void RegisterErrorsView();
void RegisterSaturationView(); 

#endif // METRICS_H
