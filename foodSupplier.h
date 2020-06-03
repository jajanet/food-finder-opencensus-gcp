#ifndef FOODSUPPLIER_H
#define FOODSUPPLIER_H

#include <string>
#include <vector>
#include <map>
#include <set>

std::map<std::string, std::set<std::string>> getVendorOfferings();

void FoodSupplier (std::string const& ingredient, std::vector<std::string>&suppliers);

#endif // FOODSUPPLIER_H
