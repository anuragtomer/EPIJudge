#include <vector>

#include "test_framework/generic_test.h"
using std::priority_queue;
using std::vector;

auto comp = [](vector<int>::const_iterator& first,
               vector<int>::const_iterator& second) {
  return *first > *second;
};

vector<int> SortApproximatelySortedData(
    vector<int>::const_iterator sequence_begin,
    const vector<int>::const_iterator& sequence_end, int k) {
  priority_queue<vector<int>::const_iterator,
                 vector<vector<int>::const_iterator>, decltype(comp)>
      min_heap(comp);
  vector<int> result;
  while (sequence_begin != sequence_end) {
    min_heap.push(sequence_begin);
    sequence_begin = next(sequence_begin);
    if (min_heap.size() == k + 1) {
      result.push_back(*(min_heap.top()));
      min_heap.pop();
    }
  }
  while (!min_heap.empty()) {
    result.push_back(*(min_heap.top()));
    min_heap.pop();
  }
  return result;
}

vector<int> SortApproximatelySortedDataWrapper(const vector<int>& sequence,
                                               int k) {
  return SortApproximatelySortedData(cbegin(sequence), cend(sequence), k);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"sequence", "k"};
  return GenericTestMain(
      args, "sort_almost_sorted_array.cc", "sort_almost_sorted_array.tsv",
      &SortApproximatelySortedDataWrapper, DefaultComparator{}, param_names);
}
