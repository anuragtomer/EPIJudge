#include <vector>

#include "test_framework/generic_test.h"
using std::greater;
using std::less;
using std::priority_queue;
using std::vector;

void balance(priority_queue<int, vector<int>, greater<>>& min_heap,
             priority_queue<int, vector<int>, less<>>& max_heap,
             bool is_min_heap_larger) {
  if (is_min_heap_larger) {
    auto top_elem = min_heap.top();
    min_heap.pop();
    max_heap.emplace(top_elem);
  } else {
    auto top_elem = max_heap.top();
    max_heap.pop();
    min_heap.emplace(top_elem);
  }
}

vector<double> OnlineMedian(vector<int>::const_iterator sequence_begin,
                            const vector<int>::const_iterator& sequence_end) {
  std::priority_queue<int, vector<int>, greater<>> min_heap;
  std::priority_queue<int, vector<int>, less<>> max_heap;
  vector<double> result;
  min_heap.emplace(*sequence_begin);
  sequence_begin = next(sequence_begin);
  result.emplace_back(min_heap.top());
  while (sequence_begin != sequence_end) {
    // Push new element
    if (*sequence_begin < min_heap.top()) {
      max_heap.emplace(*sequence_begin);
    } else {
      min_heap.emplace(*sequence_begin);
    }

    // Compute median
    if (abs(static_cast<long>(min_heap.size()) -
            static_cast<long>(max_heap.size())) > 1) {
      balance(min_heap, max_heap, min_heap.size() > max_heap.size());
    }
    if (min_heap.size() == max_heap.size()) {
      result.push_back((static_cast<double>(min_heap.top()) +
                        static_cast<double>(max_heap.top())) /
                       2);
    } else {
      max_heap.size() > min_heap.size() ? result.push_back(max_heap.top())
                                        : result.push_back(min_heap.top());
    }
    sequence_begin = next(sequence_begin);
  }
  return result;
}

vector<double> OnlineMedianWrapper(const vector<int>& sequence) {
  return OnlineMedian(cbegin(sequence), cend(sequence));
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"sequence"};
  return GenericTestMain(args, "online_median.cc", "online_median.tsv",
                         &OnlineMedianWrapper, DefaultComparator{},
                         param_names);
}
