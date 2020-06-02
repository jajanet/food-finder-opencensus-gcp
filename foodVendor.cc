#include <iostream>
#include <string>
#include <vector>
#include <any>
//#include "vendor_data.cc"

void FoodVendor (std::string const& ingredient, std::vector<std::string> const& suppliers) {
  auto vendorInfo = getVendorData();
  for (auto supplier : suppliers) {
    auto ingredientData = vendorInfo[supplier][ingredient];
    std::cout << supplier << " has " << std::any_cast<int>(ingredientData["inventory"]) << " " <<
              ingredient << " in stock for $" << std::any_cast<double>(ingredientData["price"]) <<
              " each\n";
  }

}

