#ifndef FOODAPI
#define FOODAPI

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <memory>

#include "foodAPI.h"
#include "food.grpc.pb.h"
#include "food.pb.h"
#include <grpcpp/grpcpp.h>
#include <grpcpp/opencensus.h>

#include "absl/strings/str_cat.h"
#include "absl/time/clock.h"
#include "opencensus/stats/aggregation.h"
#include "opencensus/stats/bucket_boundaries.h"
#include "opencensus/stats/view_descriptor.h"
#include "opencensus/tags/context_util.h"
#include "opencensus/trace/context_util.h"
#include "opencensus/trace/sampler.h"
#include "opencensus/trace/trace_config.h"

SupplierAPI::SupplierAPI() {
  // Create channels to send RPCs over to supplier server
  supplierStub = food::Supplier::NewStub(
      grpc::CreateChannel("127.0.0.1:8888",
                          grpc::InsecureChannelCredentials()));
}

bool SupplierAPI::isSupplied(const std::string &ingredient, std::vector<std::string> &suppliers){
  grpc::ClientContext ctx;
  food::ItemQuery query;
  food::StoreReply reply;

  // Set the search query
  query.set_item(ingredient);

  // Send the RPC.
  grpc::Status status = supplierStub->GetStores(&ctx, query, &reply);
  if (!status.ok()) {
    std::cout << "Error " << status.error_code() << ": \""
              << status.error_message() << "\"\n";
  }
  else {
    if (reply.stores_size() == 0) std::cout << "No matches near you :(\n";
    // Add all stores from the RPC reply
    else {
      std::cout << "Found " << ingredient << " at the following stores:\n";
      for (auto &store : reply.stores()) {
        suppliers.push_back(store);
        std::cout << store << "\n";
      }
    }
  }

  return suppliers.size() > 0;
}



VendorAPI::VendorAPI() {
  vendorStub = food::Vendor::NewStub(
      grpc::CreateChannel("127.0.0.1:8889",
                          grpc::InsecureChannelCredentials()));
}

void VendorAPI::getStockInfo(const std::string &ingredient, const std::vector<std::string> &suppliers){
  food::ItemStoreQuery query;

  query.set_item(ingredient);

  std::cout << "\nGetting " << ingredient << " info from relevant stores...\n\n";

  // Send the RPC for each store.
  for (auto &store : suppliers) {
    query.set_store(store);
    grpc::ClientContext ctx;
    food::ItemInfoReply reply;
    grpc::Status status = vendorStub->GetItemInfo(&ctx, query, &reply);
    if (!status.ok()) {
      std::cout << "Error " << status.error_code() << ": \""
                << status.error_message() << "\"\n";
      return;
    }
    // Print out info from stores from each RPC reply
    std::cout << store << " has " << reply.inventory() << " in stock for $"
              << reply.price() << " each\n";
  }
}


#endif // FOODAPI
