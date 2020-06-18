#ifndef SIMULATEDPROCESS
#define SIMULATEDPROCESS

#include "simulatedProcessing.h"

#include <grpcpp/grpcpp.h>
#include "absl/time/time.h"
#include "absl/time/clock.h"
#include "opencensus/trace/span.h"


// Add artificial delay
void doDelay(opencensus::trace::Span *parent) {
  auto span = opencensus::trace::Span::StartSpan("Fake work", parent);
  
  int delay = rand() % 150; // Add delay from up to .15 sec
  span.AddAnnotation("Delaying by " + std::to_string(delay) + " ms");
  absl::SleepFor(absl::Milliseconds(delay));
  
  // Small chance of doing timeout delay
  if (delay < 3) doTimeout(&span);
  
  span.End();
}


grpc::Status randomlyFailedStatus() {
  return rand() % 14 != 0
    ? grpc::Status::OK
    : grpc::Status(grpc::StatusCode::ABORTED, "Random fail");
}


void doTimeout(opencensus::trace::Span *parent) {
  auto span = opencensus::trace::Span::StartSpan("timeout", parent);
  // Timeout is set to 2 sec, so take longger
  absl::SleepFor(absl::Milliseconds(2500));
}

#endif // SIMULATEDPROCESS
