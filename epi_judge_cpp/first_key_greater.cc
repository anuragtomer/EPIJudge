#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

int SearchFirstGreaterThanK(const vector<int>& A, int k) {
  int lb = 0, ub = A.size() - 1, result = -1;
  while (lb <= ub) {
    int mid = lb + (ub - lb) / 2;
    if (A[mid] > k) {
      result = mid;
      ub = mid - 1;
    } else if (A[mid] <= k) {
      lb = mid + 1;
    }
  }
  return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A", "k"};
  return GenericTestMain(args, "first_key_greater.cc", "first_key_greater.tsv",
                         &SearchFirstGreaterThanK, DefaultComparator{},
                         param_names);
}
