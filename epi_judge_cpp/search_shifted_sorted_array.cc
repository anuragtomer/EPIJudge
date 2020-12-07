#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

int SearchSmallest(const vector<int>& A) {
  int lb = 0, ub = A.size() - 1;
  if (A[lb] <= A[ub]) return lb;

  while (lb < ub) {
    int mid = lb + (ub - lb) / 2;
    if (A[mid] > A[ub]) {  // it should be greater that both left and right.
      lb = mid + 1;
    } else {  // It should be less than both right and left.
      ub = mid;
    }
  }
  return lb;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A"};
  return GenericTestMain(args, "search_shifted_sorted_array.cc",
                         "search_shifted_sorted_array.tsv", &SearchSmallest,
                         DefaultComparator{}, param_names);
}
