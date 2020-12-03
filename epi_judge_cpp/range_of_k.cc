#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

int find_first_occurance(const vector<int>& A, const int& k) {
  int lb = 0, ub = A.size() - 1, result = -1;
  while (lb <= ub) {
    auto mid = lb + (ub - lb) / 2;
    if (A[mid] == k) {
      result = mid;
      ub = mid - 1;
    } else if (A[mid] < k) {
      lb = mid + 1;
    } else {
      ub = mid - 1;
    }
  }
  return result;
}

int find_last_occurance(const vector<int>& A, const int& begin, const int& k) {
  int lb = begin, ub = A.size() - 1, result = -1;
  while (lb <= ub) {
    auto mid = lb + (ub - lb) / 2;
    if (A[mid] == k) {
      result = mid;
      lb = mid + 1;
    } else if (A[mid] > k) {
      ub = mid - 1;
    } else {
      lb = mid + 1;
    }
  }
  return result;
}

vector<int> RangeOfK(const vector<int>& A, int k) {
  // short solution
  /*
  if (binary_search(A.begin(), A.end(), k) == true) {
    auto beg = lower_bound(A.begin(), A.end(), k);
    auto end = upper_bound(A.begin(), A.end(), k);
    return {static_cast<int>(beg - A.begin()),
            static_cast<int>(end - 1 - A.begin())};
  }
  return {-1, -1};
  */
  // long answer
  auto beg = find_first_occurance(A, k);
  if (beg == -1) return {-1, -1};
  auto end = find_last_occurance(A, beg, k);
  return {beg, end};
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A", "k"};
  return GenericTestMain(args, "range_of_k.cc", "range_of_k.tsv", &RangeOfK,
                         DefaultComparator{}, param_names);
}
