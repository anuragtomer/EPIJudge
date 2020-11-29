#include <vector>

#include "test_framework/generic_test.h"
using std::greater;
using std::priority_queue;
using std::vector;
vector<int> KthLargestElement(vector<int>::const_iterator sequence_begin,
                              const vector<int>::const_iterator& sequence_end,
                              int k) {
  vector<int> result;
  std::priority_queue<int, vector<int>, std::greater<>> min_heap;
  int i = 1;
  while (sequence_begin != sequence_end && i < k - 1) {
    min_heap.emplace(*sequence_begin);
    sequence_begin = next(sequence_begin);
    i++;
  }
  if (sequence_begin != sequence_end) {
    min_heap.emplace(*sequence_begin);
    sequence_begin = next(sequence_begin);
  }
  while (sequence_begin != sequence_end) {
    result.emplace_back(min_heap.top());
    if (min_heap.top() < *sequence_begin) {
      min_heap.pop();
      min_heap.emplace(*sequence_begin);
    }
    sequence_begin = next(sequence_begin);
  }
  return result;
}

vector<int> KthLargestElementWrapper(const vector<int>& sequence, int k) {
  return KthLargestElement(cbegin(sequence), cend(sequence), k);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"sequence", "k"};
  return GenericTestMain(args, "kth_largest_element.cc",
                         "kth_largest_element.tsv", &KthLargestElementWrapper,
                         DefaultComparator{}, param_names);
}