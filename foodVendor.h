#ifndef FOODVENDOR_H
#define FOODVENDOR_H

#include <string>
#include <vector>
#include <map>


std::map<std::string, std::map<std::string, double>> getVendorPrices ();
std::map<std::string, std::map<std::string, int>> getVendorStock ();

void FoodVendor (std::string const& item, std::vector<std::string> &suppliers); 

#endif // FOODVENDOR_H
