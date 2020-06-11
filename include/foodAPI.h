#ifndef FOODAPI_H
#define FOODAPI_H

#include <string>
#include <vector>

#include "food.grpc.pb.h"
#include "food.pb.h"

class SupplierAPI {
  public:
    SupplierAPI();
    bool isSupplied(const std::string &ingredient, std::vector<std::string> &suppliers);

  private:
    std::unique_ptr<food::Supplier::Stub> supplierStub;
};


class VendorAPI {
  public:
    VendorAPI();
    void getStockInfo(const std::string &ingredient, const std::vector<std::string> &suppliers);

  private:
    std::unique_ptr<food::Vendor::Stub> vendorStub;
};


#endif // FOODAPI
