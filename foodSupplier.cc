#ifndef FOODSUPPLIER
#define FOODSUPPLIER

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include "foodSupplier.h"
//#include "doDelay.cc"

void FoodSupplier (std::string const& ingredient, std::vector<std::string>&suppliers) {
  std::cout << "Searching for " << ingredient << "...\n";
  auto vendorInfo = getVendorOfferings();

  for (auto &vendorPair : vendorInfo) {
    // doSyntheticDelay(vendorPair.first + "... ");
    if (vendorPair.second.find(ingredient) != vendorPair.second.end()) {
      suppliers.push_back(vendorPair.first);
    }
  }
  std::cout << "\n";
}

std::map<std::string, std::set<std::string>> vendorOfferings {
{"Trader Joes", {"yeast", "flour", "sugar", "noodles", "chocolate", "salt"}},
{"Target", {"yeast", "flour", "sugar", "noodles", "salt"}},
{"Kroger", {"yeast", "flour", "noodles", "chocolate", "salt"}},
{"Aldi", {"yeast", "flour", "sugar", "noodles", "chocolate", "salt"}}
};

std::map<std::string, std::set<std::string>> getVendorOfferings() { return vendorOfferings; }

#endif // FOODSUPPLIER
