#include "test_framework/generic_test.h"

double RealDivision(double x, double y) {
  // Code here.
  return 1.0;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x", "y"};
  return GenericTestMain(args, "real_division.cc", "real_division.tsv",
                         &RealDivision, DefaultComparator{}, param_names);
}
