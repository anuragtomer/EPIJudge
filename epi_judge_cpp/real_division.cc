#include "test_framework/generic_test.h"

#define PRECISION 6

enum comparison { LESS, EQ, GTR };

template <class T>
comparison compare(const T& x, const T& y) {
  if (x > (y + (y * std::numeric_limits<T>::epsilon()))) return GTR;
  if (x < (y - (y * std::numeric_limits<T>::epsilon()))) return LESS;
  return EQ;
}

template <class T, class U>
void returnQuotient(T& x, const T& y, U& quotient) {
  while (compare(x, y) == GTR || compare(x, y) == EQ) {
    x -= y;
    ++quotient;
  }
}

double RealDivision(double x, double y) {
  double quotient = 0.0;
  // Try to use multiplication by 2 here.
  returnQuotient(x, y, quotient);
  if (x == 0) return quotient;
  int decimal_places = 0;
  double mantissa = 0.0;
  double factor = 0.1;
  while (decimal_places < PRECISION && x != 0) {
    x = x * 10;
    int local_mantissa = 0;
    returnQuotient(x, y, local_mantissa);
    mantissa += (local_mantissa * factor);
    ++decimal_places;
    factor *= 0.1;
  }
  return quotient + mantissa;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x", "y"};
  return GenericTestMain(args, "real_division.cc", "real_division.tsv",
                         &RealDivision, DefaultComparator{}, param_names);
}
