#include "test_framework/generic_test.h"
using std::priority_queue;
using std::string;
using std::vector;
vector<string> TopK(int k, const vector<string>& input_stream) {
  auto cmp = [](const string& a, const string& b) {
    return a.size() >= b.size();
  };
  priority_queue<string, vector<string>, decltype(cmp)> min_heap(cmp);
  for (auto next_string : input_stream) {
    if (min_heap.size() == k) {
      string tp = min_heap.top();
      if (next_string.size() < tp.size()) continue;
    }
    min_heap.emplace(next_string);
    if (min_heap.size() > k) min_heap.pop();
  }
  vector<string> result;
  while (!min_heap.empty()) {
    result.emplace_back(min_heap.top());
    min_heap.pop();
  }
  return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"k", "strings"};
  return GenericTestMain(args, "top_k.cc", "top_k.tsv", &TopK,
                         UnorderedComparator{}, param_names);
}