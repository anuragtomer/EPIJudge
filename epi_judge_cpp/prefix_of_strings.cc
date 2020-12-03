#include <vector>

#include "test_framework/generic_test.h"
using std::string;
using std::vector;

vector<bool> PrefixOfStrings(const vector<string>& strings, string prefix) {
  return {};
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"strings", "prefix"};
  return GenericTestMain(args, "prefix_of_strings.cc", "prefix_of_strings.tsv",
                         &PrefixOfStrings, DefaultComparator{}, param_names);
}
