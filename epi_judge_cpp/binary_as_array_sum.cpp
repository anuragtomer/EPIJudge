#include <iostream>
#include <vector>

#include "test_framework/generic_test.h"
using std::cout;
using std::vector;

vector<int> APlusB(vector<int> A, vector<int> B) {
  vector<int> C;
  int i = A.size() - 1, j = B.size() - 1;
  int k = std::max(i, j) + 1;
  int carry = 0;
  C.resize(k);
  k--;
  for (; i >= 0 && j >= 0; --i, --j) {
    C[k] = A[i] + B[j] + carry;
    carry = C[k] >= 2;
    C[k] %= 2;
    --k;
  }
  while (i >= 0) {
    C[k] = A[i] + carry;
    carry = C[k] >= 2;
    C[k] %= 2;
    --k;
    --i;
  }

  while (j >= 0) {
    C[k] = B[j] + carry;
    carry = C[k] >= 2;
    C[k] %= 2;
    --k;
    --j;
  }
  if (carry) {
    C.insert(C.begin(), 1);
  }
  return C;
}

int main() {
  vector<int> A = {1, 1, 1, 1};
  vector<int> B = {1, 1, 1, 1};
  vector<int> C = APlusB(A, B);
  for (auto num : C) cout << num << " ";
  return 0;
}
