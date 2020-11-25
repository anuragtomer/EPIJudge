#include <memory>
#include <queue>
#include <vector>

#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
#include "test_framework/timed_executor.h"
using std::cout;
using std::make_unique;
using std::queue;
using std::unique_ptr;
using test_framework::BinaryTreeSerializationTrait;

template <typename T>
struct BinaryTreeNode {
  T data;
  unique_ptr<BinaryTreeNode<T>> left, right;
  explicit BinaryTreeNode(T data) : data(data){};
};

void ConstructRightSiblingNoNext(BinaryTreeNode<int>* tree) {
  queue<BinaryTreeNode<int>*> currentLevel, nextLevel;
  if (tree != nullptr) currentLevel.push(tree);
  BinaryTreeNode<int>* prev = nullptr;
  while (!currentLevel.empty()) {
    auto current = currentLevel.front();
    currentLevel.pop();
    if (prev != nullptr) {
      if (prev->left == nullptr) prev->left = move(prev->right);
      prev->right = make_unique<BinaryTreeNode<int>>(current->data);
    }
    prev = current;
    if (current->left != nullptr) nextLevel.push(current->left.get());
    if (current->right != nullptr) nextLevel.push(current->right.get());
    if (currentLevel.empty()) {
      if (prev != nullptr) prev->right = nullptr;
      prev = nullptr;
      currentLevel = nextLevel;
      nextLevel = queue<BinaryTreeNode<int>*>();
    }
  }
  return;
}

namespace test_framework {
template <>
struct SerializationTrait<unique_ptr<BinaryTreeNode<int>>>
    : BinaryTreeSerializationTrait<unique_ptr<BinaryTreeNode<int>>, false> {};
}  // namespace test_framework

std::vector<std::vector<int>> ConstructRightSiblingNoNextWrapper(
    TimedExecutor& executor, unique_ptr<BinaryTreeNode<int>>& tree) {
  executor.Run([&] { ConstructRightSiblingNoNext(tree.get()); });
  std::vector<std::vector<int>> result;
  auto level_start = tree.get();
  while (level_start) {
    result.emplace_back();
    auto level_iter = level_start;
    while (level_iter) {
      result.back().push_back(level_iter->data);
      level_iter = level_iter->right.get();
    }
    while (level_start != nullptr && level_start->left == nullptr)
      level_start = level_start->right.get();
    level_start = level_start->left.get();
  }
  return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "tree"};
  return GenericTestMain(
      args, "tree_right_sibling_no_next.cc", "tree_right_sibling_no_next.tsv",
      &ConstructRightSiblingNoNextWrapper, DefaultComparator{}, param_names);
}
