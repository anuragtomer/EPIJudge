#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

int SearchFirstOfK(const vector<int>& A, int k) {
  /* One solution using lower_bound.
  auto foundAt = lower_bound(A.begin(), A.end(), k);

  if (foundAt != A.end() && *foundAt == k)
    return foundAt - A.begin();
  else
    return -1;
        */
  // Writing our own lower bound
  int lb = 0, ub = A.size() - 1, result = -1;
  while (lb <= ub) {
    int mid = lb + (ub - lb) / 2;
    if (A[mid] > k)
      ub = mid - 1;
    else if (A[mid] == k) {
      result = mid;
      ub = mid - 1;
    } else
      lb = mid + 1;
  }
  return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A", "k"};
  return GenericTestMain(args, "search_first_key.cc", "search_first_key.tsv",
                         &SearchFirstOfK, DefaultComparator{}, param_names);
}
