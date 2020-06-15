#ifndef SIMULATEDPROCESS_H
#define SIMULATEDPROCESS_H

#include <grpcpp/grpcpp.h>

grpc::Status randomlyFailedStatus();
void doDelay();
void doTimeout();
bool isSuccess();

#endif // SIMULATEDPROCESS_H
