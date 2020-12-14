#include <random>
#include <vector>

#include "test_framework/generic_test.h"
using std::swap;
using std::vector;

// The numbering starts from one, i.e., if A = [3, 1, -1, 2] then
// FindKthLargest(1, A) returns 3, FindKthLargest(2, A) returns 2,
// FindKthLargest(3, A) returns 1, and FindKthLargest(4, A) returns -1.

int FindMedian(vector<int>* A_ptr) {
  // Your code here.
  return 0;
}

int FindMedianWrapper(vector<int>& A) { return FindMedian(&A); }

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A"};
  return GenericTestMain(args, "median_in_array.cc", "median_in_array.tsv",
                         &FindMedianWrapper, DefaultComparator{}, param_names);
}
