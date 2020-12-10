#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

bool MatrixSearch(const vector<vector<int>>& A, int x) {
  int H = A.size(), W;
  if (H == 0) return false;
  W = A[0].size();
  for (int i = 0, j = W - 1; i < H && j >= 0;) {
    if (A[i][j] == x) return true;
    (x > A[i][j]) ? i++ : j--;
  }
  return false;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A", "x"};
  return GenericTestMain(args, "search_row_col_sorted_matrix.cc",
                         "search_row_col_sorted_matrix.tsv", &MatrixSearch,
                         DefaultComparator{}, param_names);
}
