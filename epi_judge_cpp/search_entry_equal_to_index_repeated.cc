#include <vector>

#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"
using std::vector;
int SearchEntryEqualToItsIndexRepeated(const vector<int>& A) {
  int lb = 0, ub = A.size() - 1;
  while (lb <= ub) {
    int mid = lb + (ub - lb) / 2;
    if (A[mid] == mid) {
      return mid;
    } else if (A[mid] < mid) {
      ub = mid - 1;
    } else {
      lb = mid + 1;
    }
  }
  return -1;
}

void SearchEntryEqualToItsIndexWrapper(TimedExecutor& executor,
                                       const vector<int>& A) {
  int result =
      executor.Run([&] { return SearchEntryEqualToItsIndexRepeated(A); });

  if (result != -1) {
    if (A[result] != result) {
      throw TestFailure("Entry does not equal to its index");
    }
  } else {
    for (int i = 0; i < A.size(); ++i) {
      if (A[i] == i) {
        throw TestFailure("There are entries which equal to its index");
      }
    }
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "A"};
  return GenericTestMain(args, "search_entry_equal_to_index_repeated.cc",
                         "search_entry_equal_to_index_repeated.tsv",
                         &SearchEntryEqualToItsIndexWrapper,
                         DefaultComparator{}, param_names);
}