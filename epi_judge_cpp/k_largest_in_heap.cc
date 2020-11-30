#include <vector>

#include "test_framework/generic_test.h"
using std::priority_queue;
using std::vector;
vector<int> KLargestInBinaryHeap(const vector<int>& A, int k) {
  if (A.size() == 0 || k == 0) return {};

  struct IndexAndValue {
    int index;
    int value;
  };

  auto comp = [](const IndexAndValue& first, const IndexAndValue& second) {
    return first.value < second.value;
  };

  priority_queue<IndexAndValue, vector<IndexAndValue>, decltype(comp)> max_heap(
      comp);
  vector<int> result;
  max_heap.emplace(IndexAndValue{0, A[0]});
  while (result.size() < k) {
    result.emplace_back(max_heap.top().value);
    int index = max_heap.top().index;
    max_heap.pop();
    if (2 * index + 1 < A.size()) {
      max_heap.emplace(IndexAndValue{2 * index + 1, A[2 * index + 1]});
      if (2 * index + 2 < A.size()) {
        max_heap.emplace(IndexAndValue{2 * index + 2, A[2 * index + 2]});
      }
    }
  }
  return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A", "k"};
  return GenericTestMain(args, "k_largest_in_heap.cc", "k_largest_in_heap.tsv",
                         &KLargestInBinaryHeap, UnorderedComparator{},
                         param_names);
}
