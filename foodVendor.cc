#ifndef FOODVENDOR
#define FOODVENDOR

#include <iostream>
#include <string>
#include <vector>
//#include "doDelay.cc"
#include <map>
#include "foodVendor.h"

void FoodVendor (std::string const& item, std::vector<std::string> const& suppliers) {
  auto stock = getVendorStock();
  auto prices = getVendorPrices();
  for (auto store : suppliers) {
    std::cout << store << " has " << stock[store][item] << " " <<
              item << " in stock for $" << prices[store][item] <<
              " each\n";
  }

}

std::map<std::string, std::map<std::string, double>> vendorPrices {
{"Trader Joes", {
  {"yeast", 4.49},
  {"flour", 1.71},
  {"sugar", 3.28},
  {"noodles", 4.19},
  {"chocolate", 2.12},
  {"salt", 3.99},
}},
{"Target", {
  {"yeast", 4.04},
  {"flour", 0.9},
  {"sugar", 4.23},
  {"noodles", 4.35},
  {"salt", 3.54},
}},
{"Kroger", {
  {"yeast", 2.0},
  {"flour", 2.49},
  {"noodles", 4.06},
  {"chocolate", 4.96},
  {"salt", 4.59}
}},
{"Aldi", {
  {"yeast", 3.49},
  {"flour", 4.6},
  {"sugar", 3.59},
  {"noodles", 0.73},
  {"chocolate", 4.13},
  {"salt", 4.8}
  }}
};

std::map<std::string, std::map<std::string, int>> vendorStock {
{"Trader Joes", {
  {"yeast", 34},
  {"flour", 55},
  {"sugar", 0},
  {"noodles", 69},
  {"chocolate", 7},
  {"salt", 34}
}},
{"Target", {
  {"yeast", 51},
  {"flour", 37},
  {"sugar", 48},
  {"noodles", 92},
  {"salt", 18}
}},
{"Kroger", {
  {"yeast", 33},
  {"flour", 5},
  {"noodles", 39},
  {"chocolate", 27},
  {"salt", 45}
}},
{"Aldi", {
  {"yeast", 21},
  {"flour", 7},
  {"sugar", 68},
  {"noodles", 99},
  {"chocolate", 42},
  {"salt", 1}
}},
};

std::map<std::string, std::map<std::string, double>> getVendorPrices () { return vendorPrices; }
std::map<std::string, std::map<std::string, int>> getVendorStock () { return vendorStock; }


#endif // FOODVENDOR
