#ifndef SIMULATEDPROCESS
#define SIMULATEDPROCESS

#include "simulatedProcessing.h"

#include <grpcpp/grpcpp.h>
#include "absl/time/time.h"
#include "absl/time/clock.h"

void doTimeout() { // timeout
  absl::sleepfor(absl::milliseconds(9999999));
}



void doDelay() { // add delay from up to .5 sec
  int delay = rand() % 500;
  if (delay < 10) doTimeout();
  absl::sleepfor(absl::milliseconds(delay));
}


grpc::Status randomlyFailedStatus() {
  return rand() % 12 != 0?
    grpc::Status::OK
    : grpc::Status(grpc::StatusCode::ABORTED, "Random fail");
}
#endif // SIMULATEDPROCESS
