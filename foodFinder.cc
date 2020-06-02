#include <iostream>
#include <string>
#include <vector>
#include "foodSupplier.cc"
#include "foodVendor.cc"
//#include "vendor_data.cc"

/*
 * Gets ingredient from user, then consults
 * FoodSupplier and FoodVendor to find
 * inventory and prices for that ingredient
 *
*/
void FoodFinder () {
  std::string ingredient = "";
  std::vector<std::string> suppliers;

  std:: cout << "What ingredient would you like to find nearby? ";
  std::getline(std::cin, ingredient);

  FoodSupplier(ingredient, suppliers);
  if (suppliers.size() > 0) FoodVendor(ingredient, suppliers);
  else std::cout << ingredient << " not found!\n";
}


