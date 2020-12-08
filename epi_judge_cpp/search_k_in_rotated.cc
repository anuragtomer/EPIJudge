#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

int SearchK(const vector<int>& A, int k) {
  int lb = 0, ub = A.size();
  while (lb < ub) {
    int mid = lb + (ub - lb) / 2;
    if (A[mid] == k) {
      return mid;
    }
    if (A[lb] <= A[mid]) {
      if (k >= A[lb] && k < A[mid])
        ub = mid;
      else
        lb = mid + 1;
    } else {
      if (k <= A[ub - 1] && k > A[mid])
        lb = mid + 1;
      else
        ub = mid;
    }
  }
  return -1;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A", "k"};
  return GenericTestMain(args, "search_k_in_rotated.cc",
                         "search_k_in_rotated.tsv", &SearchK,
                         DefaultComparator{}, param_names);
}
