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


// Supplier contructor
SupplierAPI::SupplierAPI() {
  // Create channels to send RPCs over to supplier server
  supplierStub = food::Supplier::NewStub(
      grpc::CreateChannel("127.0.0.1:8888",
                          grpc::InsecureChannelCredentials()));
}

// Return whether an ingredient is available and return relevant vendors
bool SupplierAPI::isSupplied(const std::string &ingredient,
	std::vector<std::string> &suppliers, opencensus::trace::Span *parent) {
  // Create needed RPC variables
  grpc::ClientContext ctx;
  food::StoreReply reply;
  // Create and set the search query
  food::ItemQuery query;
  query.set_item(ingredient);

  // Span used for tracing
  auto span = opencensus::trace::Span::StartSpan("SupplierCall", parent);
  span.AddAnnotation("Calling supplier service for " + ingredient + "\n");

  // Send the RPC.
  grpc::Status status = supplierStub->GetStores(&ctx, query, &reply);
  if (!status.ok()) {
    std::cout << "Error " << status.error_code() << ": \""
              << status.error_message() << "\"\n";
    span.SetStatus(opencensus::trace::StatusCode::UNKNOWN, status.error_message());
  }
  else {
    // Annotate and add relevant stores based on RPC reply
    if (reply.stores_size() == 0) {
	span.AddAnnotation("No matches\n");
    }
    else {
      span.AddAnnotation("Found " + std::to_string(reply.stores_size()) + " vendors:\n");
      for (auto &store : reply.stores()) {
        suppliers.push_back(store);
        span.AddAnnotation(store);
      }
    }
  }
  span.End(); // End span

  return suppliers.size() > 0;
}


VendorAPI::VendorAPI() {
  vendorStub = food::Vendor::NewStub(
      grpc::CreateChannel("127.0.0.1:8889",
                          grpc::InsecureChannelCredentials()));
}

void VendorAPI::getStockInfo(const std::string &ingredient,
		const std::vector<std::string> &suppliers, opencensus::trace::Span *parent) {
  food::ItemStoreQuery query;
  query.set_item(ingredient);

  auto span = opencensus::trace::Span::StartSpan("VendorCall", parent);
  span.AddAnnotation("Calling vendor service for " + ingredient);

  // Send the RPC for each store.
  for (auto &store : suppliers) {
    query.set_store(store);
    grpc::ClientContext ctx;
    food::ItemInfoReply reply;

    grpc::Status status = vendorStub->GetItemInfo(&ctx, query, &reply);
    if (!status.ok()) {
      std::cout << "Error " << status.error_code() << ": \""
                << status.error_message() << "\"\n";
      span.SetStatus(opencensus::trace::StatusCode::UNKNOWN, status.error_message());
    }
    else { // Annotate span with details from the current store referenced by the RPC call
      span.AddAnnotation(store + " - " + std::to_string(reply.inventory()) + " items for $"
              + std::to_string(reply.price()) + " each");
    }
  }
  span.End();
}


#endif // FOODAPI
