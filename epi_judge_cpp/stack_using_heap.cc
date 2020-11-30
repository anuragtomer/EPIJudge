#include <vector>

#include "test_framework/generic_test.h"
using std::priority_queue;
using std::vector;
class Stack {
 public:
  void push(int x) { max_heap.emplace(stk{x, current_timestamp++}); }

  void pop() {
    if (!max_heap.empty())
      max_heap.pop();
    else
      throw std::length_error("Empty stack");
  }

  int peek() const { return (!max_heap.empty()) ? max_heap.top().value : -1; }

 private:
  int current_timestamp;
  struct stk {
    int value;
    int timestamp;
    bool operator<(const stk& that) const { return timestamp < that.timestamp; }
  };
  priority_queue<stk, vector<stk>, std::less<>> max_heap;
};

vector<int> StackUsingHeap(const vector<int>& A) {
  Stack st;
  vector<int> result;
  int i = 0;
  for (auto num : A) {
    st.push(num);
  }
  while (i < A.size()) {
    result.emplace_back(st.peek());
    st.pop();
    ++i;
  }
  return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A"};
  return GenericTestMain(args, "stack_using_heap.cc", "stack_using_heap.tsv",
                         &StackUsingHeap, DefaultComparator{}, param_names);
}
