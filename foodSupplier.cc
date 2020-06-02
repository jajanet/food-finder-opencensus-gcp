#include <iostream>
#include <string>
#include <vector>
#include "vendor_data.cc"

void FoodSupplier (std::string const& ingredient, std::vector<std::string>&suppliers) {
  std::cout << "Searching for " << ingredient << "...\n";
  auto vendorInfo = getVendorData();
  for (auto &vendorPair : vendorInfo) {
    if (vendorPair.second.find(ingredient) != vendorPair.second.end()) {
      suppliers.push_back(vendorPair.first);
    }
  }
}

