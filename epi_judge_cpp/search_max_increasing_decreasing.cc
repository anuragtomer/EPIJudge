#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

enum SEQUENCE { INCREASING, DECREASING, PEAK };

SEQUENCE status(const vector<int>& A, int idx) {
  if (idx != 0 && idx != A.size() - 1) {
    if (A[idx] > A[idx - 1] && A[idx] > A[idx + 1])
      return PEAK;
    else
      return (A[idx] > A[idx - 1]) ? INCREASING : DECREASING;
  } else if (idx == 0)
    return (A[idx] > A[idx + 1]) ? PEAK : INCREASING;
  else
    return (A[idx] > A[idx - 1]) ? PEAK : DECREASING;
}

int SearchLargest(const vector<int>& A) {
  int lb = 0, ub = A.size() - 1;
  while (lb <= ub) {
    int mid = lb + (ub - lb) / 2;
    auto st = status(A, mid);
    if (st == PEAK)
      return mid;
    else if (st == INCREASING)
      lb = mid + 1;
    else
      ub = mid - 1;
  }
  return -1;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A"};
  return GenericTestMain(args, "search_max_increasing_decreasing.cc",
                         "search_max_increasing_decreasing.tsv", &SearchLargest,
                         DefaultComparator{}, param_names);
}