#include <string>
#include <vector>

#include "binary_tree_node.h"
#include "test_framework/generic_test.h"
#include "test_framework/timed_executor.h"
using std::string;
using std::vector;

unique_ptr<BinaryTreeNode<int>> ReconstructPostorderHelper(
    const vector<int*>& postorder, int* subtree_index) {
  int& current_index = *subtree_index;
  int* current_value = postorder[current_index];
  current_index--;
  if (current_value == nullptr) return nullptr;
  auto right = ReconstructPostorderHelper(postorder, subtree_index);
  auto left = ReconstructPostorderHelper(postorder, subtree_index);
  return std::make_unique<BinaryTreeNode<int>>(*current_value, move(left),
                                               move(right));
}

unique_ptr<BinaryTreeNode<int>> ReconstructPostorder(
    const vector<int*>& postorder) {
  int subtree_index = postorder.size() - 1;
  return ReconstructPostorderHelper(postorder, &subtree_index);
}

unique_ptr<BinaryTreeNode<int>> ReconstructPostorderWrapper(
    TimedExecutor& executor, const vector<string>& postorder) {
  vector<int> values;
  vector<int*> ptrs;
  values.reserve(postorder.size());
  for (auto& s : postorder) {
    if (s == "null") {
      ptrs.push_back(nullptr);
    } else {
      int i = std::stoi(s);
      values.push_back(i);
      ptrs.push_back(&values.back());
    }
  }

  return executor.Run([&] { return ReconstructPostorder(ptrs); });
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "postorder"};
  return GenericTestMain(args, "tree_from_postorder_with_null.cc",
                         "tree_from_postorder_with_null.tsv",
                         &ReconstructPostorderWrapper, DefaultComparator{},
                         param_names);
}
