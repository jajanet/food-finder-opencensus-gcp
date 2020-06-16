#ifndef SIMULATEDPROCESS_H
#define SIMULATEDPROCESS_H

#include <grpcpp/grpcpp.h>
#include "opencensus/trace/span.h"

grpc::Status randomlyFailedStatus();
void doDelay(opencensus::trace::Span *parent);
void doTimeout(opencensus::trace::Span *parent);

#endif // SIMULATEDPROCESS_H
