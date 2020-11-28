#include <vector>

#include "test_framework/generic_test.h"
using std::greater;
using std::priority_queue;
using std::vector;
struct IteratorBeginAndEnd {
  vector<int>::const_iterator current;
  vector<int>::const_iterator end;
  bool operator>(IteratorBeginAndEnd& that) const {
    return *current > *that.current;
  }
};

vector<int> MergeSortedArrays(vector<vector<int>> sorted_subarrays) {
  priority_queue<IteratorBeginAndEnd, vector<IteratorBeginAndEnd>, greater<>>
      min_heap;
  for (auto& sorted_subarray :
       sorted_subarrays) {  // Why non-reference subarray fails??
    min_heap.push(
        IteratorBeginAndEnd{sorted_subarray.cbegin(), sorted_subarray.cend()});
  }
  vector<int> result;
  while (!min_heap.empty()) {
    auto smallest = min_heap.top();
    min_heap.pop();
    if (smallest.current != smallest.end) {
      result.push_back(*smallest.current);
      min_heap.emplace(
          IteratorBeginAndEnd{next(smallest.current), smallest.end});
    }
  }
  return result;
}

vector<int> SortKIncreasingDecreasingArray(const vector<int>& A) {
  vector<vector<int>> sorted_subarrays;
  typedef enum { INCREASING, DECREASING } SubarrayType;
  SubarrayType subarray_type = INCREASING;
  int start_idx = 0;
  for (int i = 1; i <= A.size(); ++i) {
    if ((i == A.size()) || (A[i - 1] < A[i] && subarray_type == DECREASING) ||
        (A[i - 1] >= A[i] && subarray_type == INCREASING)) {
      if (subarray_type == INCREASING) {
        // std::cout << "Increasing sequence:\nStart: "
        //           << *(A.cbegin() + start_idx);
        // std::cout << ", End: " << *(A.cbegin() + i);
        sorted_subarrays.emplace_back(A.cbegin() + start_idx, A.cbegin() + i);
      } else {
        // std::cout << "Decreasing sequence:\nStart: "
        //           << *(A.crbegin() + A.size() - i);
        // std::cout << ", End: " << *(A.crbegin() + A.size() - start_idx);
        sorted_subarrays.emplace_back(A.crbegin() + A.size() - i,
                                      A.crbegin() + A.size() - start_idx);
      }
      start_idx = i;
      subarray_type = (subarray_type == INCREASING ? DECREASING : INCREASING);
    }
  }
  // using std::cout;
  // cout << "Printing sorted Arrays:";
  // for (auto sorted_subarray : sorted_subarrays) {
  //   cout << "\nArray: ";
  //   for (auto num : sorted_subarray) {
  //     cout << num << " ";
  //   }
  // }
  return MergeSortedArrays(sorted_subarrays);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A"};
  return GenericTestMain(args, "sort_increasing_decreasing_array.cc",
                         "sort_increasing_decreasing_array.tsv",
                         &SortKIncreasingDecreasingArray, DefaultComparator{},
                         param_names);
}
