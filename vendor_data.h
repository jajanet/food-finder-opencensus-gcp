#include <string>
#include <vector>
#include <map>
#include <any>

std::map<std::string, std::map<std::string, std::map<std::string, std::any>>> vendorData {
{"Trader Joes", {
  {"yeast", {{"price", 4.49}, {"inventory", 34}}},
  {"flour", {{"price", 1.71}, {"inventory", 55}}},
  {"sugar", {{"price", 3.28}, {"inventory", 0}}},
  {"noodles", {{"price", 4.19}, {"inventory", 69}}},
  {"chocolate", {{"price", 2.12}, {"inventory", 7}}},
  {"salt", {{"price", 3.99}, {"inventory", 34}}}
}},
{"Target", {
  {"yeast", {{"price", 4.04}, {"inventory", 51}}},
  {"flour", {{"price", 0.9}, {"inventory", 37}}},
  {"sugar", {{"price", 4.23}, {"inventory", 48}}},
  {"noodles", {{"price", 4.35}, {"inventory", 92}}},
  {"salt", {{"price", 3.54}, {"inventory", 18}}}
}},
{"Kroger", {
  {"yeast", {{"price", 2.0}, {"inventory", 60}}},
  {"flour", {{"price", 2.49}, {"inventory", 24}}},
  {"noodles", {{"price", 4.06}, {"inventory", 29}}},
  {"chocolate", {{"price", 4.96}, {"inventory", 86}}},
  {"salt", {{"price", 4.59}, {"inventory", 62}}}
}},
{"Aldi", {
  {"yeast", {{"price", 3.49}, {"inventory", 68}}},
  {"flour", {{"price", 4.6}, {"inventory", 88}}},
  {"sugar", {{"price", 3.59}, {"inventory", 77}}},
  {"noodles", {{"price", 0.73}, {"inventory", 87}}},
  {"chocolate", {{"price", 4.13}, {"inventory", 20}}},
  {"salt", {{"price", 4.8}, {"inventory", 85}}}
  }}
};

