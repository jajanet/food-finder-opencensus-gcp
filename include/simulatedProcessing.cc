#ifndef SIMULATEDPROCESS
#define SIMULATEDPROCESS

#include "simulatedProcessing.h"

#include <grpcpp/grpcpp.h>
#include "absl/time/time.h"
#include "absl/time/clock.h"

void doDelay() { // add delay from .1 to .6 sec
  int delay = rand() % 500 + 100;
  absl::SleepFor(absl::Milliseconds(delay));
}


grpc::Status randomlyFailedStatus() {
  return rand() % 6 != 0?
    grpc::Status::OK
    : grpc::Status(grpc::StatusCode::ABORTED, "Random fail");
}
#endif // SIMULATEDPROCESS
