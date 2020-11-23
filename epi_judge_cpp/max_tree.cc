#include <unordered_map>
#include <vector>

#include "binary_tree_node.h"
#include "test_framework/binary_tree_utils.h"
#include "test_framework/generic_test.h"

using std::make_unique;
using std::vector;

int findIndex(const vector<int>& nums) {
  int index = -1, i = 0;
  int max_num = INT_MIN;
  for (auto num : nums) {
    if (num > max_num) {
      max_num = num;
      index = i;
    }
    i++;
  }
  return index;
}

unique_ptr<BinaryTreeNode<int>> maxTree(const vector<int>& nums) {
  if (nums.empty()) return nullptr;
  int max_index = findIndex(nums);
  if (max_index == -1) return nullptr;
  vector<int> left = vector<int>(nums.begin(), nums.begin() + max_index);
  vector<int> right = vector<int>(nums.begin() + max_index + 1, nums.end());
  return make_unique<BinaryTreeNode<int>>(nums[max_index], maxTree(left),
                                          maxTree(right));
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"array"};
  return GenericTestMain(args, "max_tree.cc", "max_tree.tsv", &maxTree,
                         DefaultComparator{}, param_names);
}
