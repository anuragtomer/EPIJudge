#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

int SearchK(const vector<int>& A, int k) {
  // Code here
  return -1;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A", "k"};
  return GenericTestMain(args, "search_k_in_rotated.cc",
                         "search_k_in_rotated.tsv", &SearchK,
                         DefaultComparator{}, param_names);
}