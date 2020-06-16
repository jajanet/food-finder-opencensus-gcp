#ifndef SIMULATEDPROCESS
#define SIMULATEDPROCESS

#include "simulatedProcessing.h"

#include <grpcpp/grpcpp.h>
#include "absl/time/time.h"
#include "absl/time/clock.h"
#include "opencensus/trace/span.h"

void doTimeout(opencensus::trace::Span *parent) {
  auto span = opencensus::trace::Span::StartSpan("timeout", parent);
  absl::SleepFor(absl::Milliseconds(9999999));
}


void doDelay(opencensus::trace::Span *parent) { // add delay from up to .2 sec
  auto span = opencensus::trace::Span::StartSpan("fake_work", parent);
  
  int delay = rand() % 150;
  span.AddAnnotation("Delaying by " + std::to_string(delay) + " ms");
  absl::SleepFor(absl::Milliseconds(delay));
  
  if (delay < 3) doTimeout(&span);
  
  span.End();
}


grpc::Status randomlyFailedStatus() {
  return rand() % 12 != 0?
    grpc::Status::OK
    : grpc::Status(grpc::StatusCode::ABORTED, "Random fail");
}
#endif // SIMULATEDPROCESS
