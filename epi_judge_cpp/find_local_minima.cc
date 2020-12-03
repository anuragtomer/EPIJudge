#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

bool is_local_minima(const vector<int>& A, int idx) {
  if (idx == 0 || idx == A.size() - 1) return false;
  if ((A[idx] < A[idx - 1]) && (A[idx] < A[idx + 1])) return true;
  return false;
}
vector<int> FindLocalMinima(const vector<int>& A) {
  int lb = 0, ub = A.size() - 1, result = -1;
  while (lb <= ub) {
    int mid = lb + (ub - lb) / 2;
    if (is_local_minima(A, mid)) {
      return {A[mid]};
    } else if (A[mid] < A[ub]) {
      ub = mid;
    } else if (A[mid] < A[lb]) {
      lb = mid;
    } else {
      lb = lb + 1;
    }
  }
  return {-1};
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A"};
  return GenericTestMain(args, "find_local_minima.cc", "find_local_minima.tsv",
                         &FindLocalMinima, InComparator{}, param_names);
}
