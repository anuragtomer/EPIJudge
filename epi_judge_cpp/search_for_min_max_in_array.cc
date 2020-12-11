#include <vector>

#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
using std::max;
using std::min;
using std::minmax;
using std::pair;
using std::vector;
struct MinMax {
  int smallest, largest;
};

// MinMax MinMaxHelper(const vector<int>& A, int lb, int ub) {
//   if (lb + 1 == ub) {
//     if (A[lb] < A[ub]) return {A[lb], A[ub]};
//     return {A[ub], A[lb]};
//   }
//   if (lb == ub) return {A[lb], A[lb]};
//   int mid = lb + (ub - lb) / 2;
//   MinMax left = MinMaxHelper(A, lb, mid);
//   MinMax right = MinMaxHelper(A, mid + 1, ub);
//   return {left.smallest < right.smallest ? left.smallest : right.smallest,
//           left.largest > right.largest ? left.largest : right.largest};
// }

MinMax FindMinMax(const vector<int>& A) {
  // One way to do this:
  //   int min = INT_MAX, max = INT_MIN;
  //   for (auto num : A) {
  //     if (min > num) {
  //       min = num;
  //     }
  //     if (max < num) max = num;
  //   }
  //   return {min, max};

  // Another way:
  //   return MinMaxHelper(A, 0, A.size() - 1);

  // Book way:
  if (A.size() <= 1) return {A.front(), A.front()};
  pair<int, int> global_min_max = minmax(A[0], A[1]);
  for (int i = 2; i + 1 < A.size(); i += 2) {
    pair<int, int> local_min_max = minmax(A[i], A[i + 1]);
    global_min_max = {min(global_min_max.first, local_min_max.first),
                      max(global_min_max.second, local_min_max.second)};
  }
  if (A.size() % 2) {
    global_min_max = {min(global_min_max.first, A.back()),
                      max(global_min_max.second, A.back())};
  }
  return {global_min_max.first, global_min_max.second};
}
namespace test_framework {
template <>
struct SerializationTrait<MinMax> : UserSerTrait<MinMax, int, int> {};
}  // namespace test_framework

bool operator==(const MinMax& lhs, const MinMax& rhs) {
  return std::tie(lhs.smallest, lhs.largest) ==
         std::tie(rhs.smallest, rhs.largest);
}

std::ostream& operator<<(std::ostream& out, const MinMax& x) {
  return out << "min: " << x.smallest << ", max: " << x.largest;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A"};
  return GenericTestMain(args, "search_for_min_max_in_array.cc",
                         "search_for_min_max_in_array.tsv", &FindMinMax,
                         DefaultComparator{}, param_names);
}
