#include <vector>

#include "test_framework/generic_test.h"
using std::greater;
using std::priority_queue;
using std::vector;

struct IteratorCurrentAndEnd {
  vector<int>::const_iterator current;
  vector<int>::const_iterator end;
  bool operator>(IteratorCurrentAndEnd& that) const {
    return *current > *that.current;
  }
};

vector<int> MergeSortedArrays(const vector<vector<int>>& sorted_arrays) {
  /* One way to do it.
int sz = sorted_arrays.size();
vector<int> pointers(sz, 0);
vector<int> result;
int total_size = 0;
for (auto& sorted_array : sorted_arrays) total_size += sorted_array.size();
int min = INT_MAX, min_i = -1;
while (result.size() < total_size) {
min_i = -1;
min = INT_MAX;
for (int i = 0; i < sz; ++i) {
if (pointers[i] >= sorted_arrays[i].size()) continue;
if (min > sorted_arrays[i][pointers[i]]) {
  min = sorted_arrays[i][pointers[i]];
  min_i = i;
}
}
result.push_back(min);
++pointers[min_i];
}
return result;
*/
  // Another way of doing the same thing using heaps. This is faster.
  priority_queue<IteratorCurrentAndEnd, vector<IteratorCurrentAndEnd>,
                 greater<>>
      min_heap;
  for (auto& sorted_array : sorted_arrays) {
    min_heap.emplace(
        IteratorCurrentAndEnd{sorted_array.cbegin(), sorted_array.cend()});
  }
  vector<int> result;
  while (!min_heap.empty()) {
    auto min_array = min_heap.top();
    min_heap.pop();
    if (min_array.current != min_array.end) {
      result.push_back(*min_array.current);
      min_heap.emplace(
          IteratorCurrentAndEnd{next(min_array.current), min_array.end});
    }
  }
  return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"sorted_arrays"};
  return GenericTestMain(args, "sorted_arrays_merge.cc",
                         "sorted_arrays_merge.tsv", &MergeSortedArrays,
                         DefaultComparator{}, param_names);
}
