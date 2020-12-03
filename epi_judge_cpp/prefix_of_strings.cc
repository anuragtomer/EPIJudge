#include <vector>

#include "test_framework/generic_test.h"
using std::string;
using std::vector;
int match_string(string hay, string needle) {
  int i = 0;
  for (; i < hay.size() && i < needle.size(); ++i) {
    if (hay[i] < needle[i])
      return -1;
    else if (hay[i] > needle[i])
      return 1;
  }
  if (i == needle.size()) return 0;
  return -1;
}

int find_first(const vector<string>& strings, string prefix) {
  int lb = 0, ub = strings.size() - 1, result = -1;
  while (lb <= ub) {
    auto mid = lb + (ub - lb) / 2;
    int idx = match_string(strings[mid], prefix);
    if (idx == 0) {
      result = mid;
      ub = mid - 1;
    } else if (idx == 1) {
      ub = mid - 1;
    } else {
      lb = mid + 1;
    }
  }
  return result;
}

int find_last(const vector<string>& strings, int start, string prefix) {
  int lb = start, ub = strings.size() - 1, result = -1;
  while (lb <= ub) {
    auto mid = lb + (ub - lb) / 2;
    int idx = match_string(strings[mid], prefix);
    if (idx == 0) {
      result = mid;
      lb = mid + 1;
    } else if (idx == 1) {
      ub = mid - 1;
    } else {
      lb = mid + 1;
    }
  }
  return result;
}

vector<bool> PrefixOfStrings(const vector<string>& strings, string prefix) {
  auto beg = find_first(strings, prefix);
  vector<bool> result(strings.size(), false);
  if (beg == -1) return result;
  auto end = find_last(strings, beg, prefix);
  for (int i = beg; i <= end; ++i) {
    result[i] = true;
  }
  return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"strings", "prefix"};
  return GenericTestMain(args, "prefix_of_strings.cc", "prefix_of_strings.tsv",
                         &PrefixOfStrings, DefaultComparator{}, param_names);
}
