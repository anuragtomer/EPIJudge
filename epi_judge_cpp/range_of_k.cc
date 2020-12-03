#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

vector<vector<int>> RangeOfK(const vector<int>& A, int k) {
  // Enter code here.
  return {{}};
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A", "k"};
  return GenericTestMain(args, "range_of_k.cc", "range_of_k.tsv", &RangeOfK,
                         DefaultComparator{}, param_names);
}
