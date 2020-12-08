#include "test_framework/generic_test.h"

double SquareRoot(double x) {
  double lb = x >= 1.0 ? 1.0 : x, ub = x >= 1.0 ? x : 1.0;
  while (lb < ub) {
    double mid = lb + (ub - lb) * 0.5;
    double mid_sq = mid * mid;
    // The following commented lines don't work. It seems that epsilon should
    // actually be relative to the the value being compared. So, we create a
    // relative epsilon by multiplying the epsilon with value itself.
    // if ((mid_sq <= (x + (std::numeric_limits<double>::epsilon()))) &&
    //     (mid_sq >= (x - (std::numeric_limits<double>::epsilon()))))
    //   return mid;
    // if (mid_sq < (x - (std::numeric_limits<double>::epsilon())))
    if ((mid_sq <= (x + (x * std::numeric_limits<double>::epsilon()))) &&
        (mid_sq >= (x - (x * std::numeric_limits<double>::epsilon()))))
      return mid;
    if (mid_sq < (x - (x * std::numeric_limits<double>::epsilon())))
      lb = mid;
    else
      ub = mid;
  }
  return lb;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x"};
  return GenericTestMain(args, "real_square_root.cc", "real_square_root.tsv",
                         &SquareRoot, DefaultComparator{}, param_names);
}

/*
a < b:
a < (b - 0.00000b)

a > b:
a > (b + 0.00000b)
*/