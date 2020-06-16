//#ifdef EXPORTER
//#define EXPORTER

#include "exporters.h"

#include <cstdlib>
#include <iostream>

#include "opencensus/exporters/stats/stackdriver/stackdriver_exporter.h"
#include "opencensus/exporters/stats/stdout/stdout_exporter.h"
#include "opencensus/exporters/trace/stackdriver/stackdriver_exporter.h"
#include "opencensus/exporters/trace/stdout/stdout_exporter.h"

// Only exporting to Google Cloud Platform using Stackdriver
void RegisterExporters() {
  // For debugging, register exporters that just write to stdout.
  opencensus::exporters::stats::StdoutExporter::Register();
  opencensus::exporters::trace::StdoutExporter::Register();
  
  // SET YOUR POROJECT ID HERE
  const char* project_id = "starter-project-j";

  opencensus::exporters::stats::StackdriverOptions stats_opts;
  stats_opts.project_id = project_id;
  opencensus::exporters::stats::StackdriverExporter::Register(
      std::move(stats_opts));

  opencensus::exporters::trace::StackdriverOptions trace_opts;
  trace_opts.project_id = project_id;
  opencensus::exporters::trace::StackdriverExporter::Register(
      std::move(trace_opts));

}

//#endif // EXPORTER
