#include "test_framework/generic_test.h"

int SquareRoot(int k) {
  int lb = 1, ub = k;
  while (lb <= ub) {
    int mid = lb + (ub - lb) / 2;
    if (mid == k / mid) return mid;
    if (mid < k / mid)
      lb = mid + 1;
    else
      ub = mid - 1;
  }
  return lb - 1;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"k"};
  return GenericTestMain(args, "int_square_root.cc", "int_square_root.tsv",
                         &SquareRoot, DefaultComparator{}, param_names);
}
