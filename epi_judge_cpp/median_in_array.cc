#include <random>
#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

template <typename Compare>
int partition(vector<int>* A_ptr, int left, int right, int pivot_index,
              Compare comp) {
  vector<int>& A = *A_ptr;
  int pivot_value = A[pivot_index];
  int new_pivot_index = left;
  std::swap(A[right], A[pivot_index]);
  right--;
  for (int i = left; i <= right; ++i) {
    if (comp(A[i], pivot_value)) {
      std::swap(A[i], A[new_pivot_index++]);
    }
  }
  std::swap(A[right + 1], A[new_pivot_index]);
  return new_pivot_index;
}

int FindKth(int k, vector<int>* A_ptr) {
  vector<int>& A = *A_ptr;
  int left = 0, right = A.size() - 1;
  std::default_random_engine gen((std::random_device())());
  while (left <= right) {
    int pivot_index = std::uniform_int_distribution<int>{left, right}(gen);
    int new_pivot_index =
        partition(&A, left, right, pivot_index, std::less<int>());
    if (new_pivot_index == k - 1)
      return A[new_pivot_index];
    else if (new_pivot_index > k - 1)
      right = new_pivot_index - 1;
    else
      left = new_pivot_index + 1;
  }
  assert(false);
  return -1;
}

float FindMedian(vector<int>* A_ptr) {
  vector<int>& A = *A_ptr;
  size_t sz = A.size();
  int k = sz / 2;
  int right = FindKth(k + 1, &A);
  if (sz % 2 == 1)
    return static_cast<float>(right);
  else {
    int left = FindKth(k, &A);
    return 0.5 * static_cast<float>(left + right);
  }
}

float FindMedianWrapper(vector<int>& A) { return FindMedian(&A); }

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A"};
  return GenericTestMain(args, "median_in_array.cc", "median_in_array.tsv",
                         &FindMedianWrapper, DefaultComparator{}, param_names);
}
