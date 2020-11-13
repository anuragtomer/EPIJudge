#include <algorithm>
#include <cstdlib>
#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

vector<int> Multiply(vector<int> num1, vector<int> num2) {
  int n = num1.size(), m = num2.size();
  const bool isNegative = (num1.front() < 0) ^ (num2.front() < 0);
  num1.front() = abs(num1.front());
  num2.front() = abs(num2.front());
  vector<int> result(n + m, 0);

  for (int i = n - 1; i >= 0; --i) {
    for (int j = m - 1; j >= 0; --j) {
      result[i + j + 1] += num1[i] * num2[j];
      result[i + j] += result[i + j + 1] / 10;
      result[i + j + 1] %= 10;
    }
  }

  result = {find_if_not(begin(result), end(result),
                        [](int a) {
                          return a == 0;
                        }),  // begin for result. This is basically discarding
                             // 0's from beginning.
            end(result)};

  if (result.empty()) return {0};

  if (isNegative) result.front() *= -1;
  return result;
}

// vector<int> Multiply(vector<int> num1, vector<int> num2) {
//   int n = num1.size() - 1;
//   int m = num2.size() - 1;
//   int base = n + m + 1;
//   int i = 0;
//   int carry = 0;
//   bool negative = (num1[0] < 0) ^ (num2[0] < 0);
//   num1[0] = abs(num1[0]);  // < 0 ? num1[0] * -1 : num1[0];
//   num2[0] = abs(num2[0]);  // < 0 ? num2[0] * -1 : num2[0];
//   vector<int> result(base + 1, 0);
//   for (n = num1.size() - 1; n >= 0; --n) {
//     for (i = base, m = num2.size() - 1; m >= 0; --m) {
//       int mul = num1[n] * num2[m] + carry + result[i];
//       result[i] = mul % 10;
//       i--;
//       carry = mul / 10;
//     }
//     while (carry) {
//       result[i] += (carry % 10);
//       carry /= 10;
//       i--;
//     }
//     base--;
//   }
//   i = 0;
//   while (result[i] == 0) i++;
//   if (negative) {
//     result[i] *= -1;
//   }
//   vector<int> final_ans;
//   for (; i < result.size(); ++i) final_ans.push_back(result[i]);
//   if (final_ans.size() == 0) final_ans.push_back(0);
//   return final_ans;
// }

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"num1", "num2"};
  return GenericTestMain(args, "int_as_array_multiply.cc",
                         "int_as_array_multiply.tsv", &Multiply,
                         DefaultComparator{}, param_names);
}
