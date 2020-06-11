#ifndef FOODFINDER_H
#define FOODFINDER_H

#include <iostream>
#include <vector>

bool isSupplied(const std::string &ingredient, std::vector<std::string> &suppliers);

void getStockInfo(const std::string &ingredient, const std::vector<std::string> &suppliers);

void foodFinder();


#endif // FOODFINDER_H
