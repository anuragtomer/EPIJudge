#include <random>
#include <vector>

#include "test_framework/generic_test.h"
using std::swap;
using std::vector;

// The numbering starts from one, i.e., if A = [3, 1, -1, 2] then
// FindKthLargest(1, A) returns 3, FindKthLargest(2, A) returns 2,
// FindKthLargest(3, A) returns 1, and FindKthLargest(4, A) returns -1.

template <typename Compare>
int partition(int left, int right, int pivot_idx, Compare comp,
              vector<int>* A_ptr) {
  vector<int>& A = *A_ptr;
  int pivot_value = A[pivot_idx];
  int new_pivot_idx = left;
  swap(A[pivot_idx], A[right]);
  for (int i = left; i < right; ++i) {
    if (comp(A[i], pivot_value)) {
      swap(A[i], A[new_pivot_idx++]);
    }
  }
  swap(A[right], A[new_pivot_idx]);
  return new_pivot_idx;
}

template <typename Compare>
int FindKth(int k, Compare comp, vector<int>* A_ptr) {
  vector<int>& A = *A_ptr;
  int left = 0, right = A.size() - 1;
  std::default_random_engine gen((std::random_device())());
  while (left <= right) {
    int pivot_idx = std::uniform_int_distribution<int>{left, right}(gen);
    int new_pivot_idx = partition(left, right, pivot_idx, comp, &A);
    if (new_pivot_idx == k - 1)
      return A[new_pivot_idx];
    else if (new_pivot_idx > k - 1)
      right = new_pivot_idx - 1;
    else
      left = new_pivot_idx + 1;
  }
  return -1;
}

int FindKthLargest(int k, vector<int>* A_ptr) {
  return FindKth(k, std::greater<int>(), A_ptr);
}

int FindKthLargestWrapper(int k, vector<int>& A) {
  return FindKthLargest(k, &A);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"k", "A"};
  return GenericTestMain(args, "kth_largest_in_array.cc",
                         "kth_largest_in_array.tsv", &FindKthLargestWrapper,
                         DefaultComparator{}, param_names);
}
