#ifndef FOODAPI
#define FOODAPI

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <memory>

#include "include/foodAPI.h"
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

bool SupplierAPI::isSupplied(const std::string &ingredient,
	std::vector<std::string> &suppliers, opencensus::trace::Span *parent){
  grpc::ClientContext ctx;
  food::ItemQuery query;
  food::StoreReply reply;

  auto span = opencensus::trace::Span::StartSpan("SupplierCall", parent); 
  span.AddAnnotation("Calling supplier service for " + ingredient + "\n");
  
  // Set the search query
  query.set_item(ingredient);

  // Send the RPC.
  grpc::Status status = supplierStub->GetStores(&ctx, query, &reply);
  if (!status.ok()) {
    std::cout << "Error " << status.error_code() << ": \""
              << status.error_message() << "\"\n";
    opencensus::trace::GetCurrentSpan().SetStatus(
		    opencensus::trace::StatusCode::UNKNOWN, status.error_message());
    opencensus::trace::GetCurrentSpan().End();
  }
  else {
    span.AddAnnotation("Found " + std::to_string(reply.stores_size()) + " vendors:\n");
    if (reply.stores_size() == 0) span.AddAnnotation("No matches\n");
    // Add all stores from the RPC reply
    else {
      for (auto &store : reply.stores()) {
        suppliers.push_back(store);
        span.AddAnnotation(store);
      }
    }
  }
  span.End();

  return suppliers.size() > 0;
}


VendorAPI::VendorAPI() {
  vendorStub = food::Vendor::NewStub(
      grpc::CreateChannel("127.0.0.1:8889",
                          grpc::InsecureChannelCredentials()));
}

void VendorAPI::getStockInfo(const std::string &ingredient,
		const std::vector<std::string> &suppliers, opencensus::trace::Span *parent){
  auto span = opencensus::trace::Span::StartSpan("VendorCall", parent);
  span.AddAnnotation("Calling vendor service for " + ingredient);
  
  food::ItemStoreQuery query;
  query.set_item(ingredient);

  // Send the RPC for each store.
  for (auto &store : suppliers) {
    query.set_store(store);
    grpc::ClientContext ctx;
    food::ItemInfoReply reply;
    grpc::Status status = vendorStub->GetItemInfo(&ctx, query, &reply);
    if (!status.ok()) {
      std::cout << "Error " << status.error_code() << ": \""
                << status.error_message() << "\"\n";
      opencensus::trace::GetCurrentSpan().SetStatus(
		      opencensus::trace::StatusCode::UNKNOWN, status.error_message());
      opencensus::trace::GetCurrentSpan().End();
    }
    else // Print out info from stores from each RPC reply
      span.AddAnnotation(store + " - " + std::to_string(reply.inventory()) + " items for $"
              + std::to_string(reply.price()) + " each");
  }
  span.End();
}


#endif // FOODAPI
