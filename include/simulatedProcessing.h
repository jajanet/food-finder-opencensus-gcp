#ifndef SIMULATEDPROCESS_H
#define SIMULATEDPROCESS_H

#include <grpcpp/grpcpp.h>

grpc::Status randomlyFailedStatus();
void doDelay();
bool isSuccess();

#endif // SIMULATEDPROCESS_H
