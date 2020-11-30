#include <vector>

#include "test_framework/generic_test.h"
using std::priority_queue;
using std::vector;
class Queue {
 public:
  void push(int x) { max_heap.emplace(stk{x, current_timestamp++}); }

  void pop() {
    if (!max_heap.empty())
      max_heap.pop();
    else
      throw std::length_error("Empty stack");
  }

  int front() const { return (!max_heap.empty()) ? max_heap.top().value : -1; }

 private:
  int current_timestamp;
  struct stk {
    int value;
    int timestamp;
    bool operator>(const stk& that) const { return timestamp > that.timestamp; }
  };
  priority_queue<stk, vector<stk>, std::greater<>> max_heap;
};

vector<int> QueueUsingHeap(const vector<int>& A) {
  Queue q;
  vector<int> result;
  int i = 0;
  for (auto num : A) {
    q.push(num);
  }
  while (i < A.size()) {
    result.emplace_back(q.front());
    q.pop();
    ++i;
  }
  return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A"};
  return GenericTestMain(args, "queue_using_heap.cc", "queue_using_heap.tsv",
                         &QueueUsingHeap, DefaultComparator{}, param_names);
}
