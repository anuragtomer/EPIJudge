#include <memory>
#include <vector>

#include "binary_tree_node.h"
#include "test_framework/generic_test.h"
using std::stack;
using std::unique_ptr;
using std::vector;

vector<int> InorderTraversal(const unique_ptr<BinaryTreeNode<int>>& tree) {
  stack<BinaryTreeNode<int>*> st;
  vector<int> result;
  auto current = tree.get();
  while (current || !st.empty()) {
    if (current) {
      // Going down left.
      st.emplace(current);
      current = current->left.get();
    } else {
      // Up and Right
      current = st.top();
      st.pop();
      result.emplace_back(current->data);
      current = current->right.get();
    }
  }
  return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "tree_inorder.cc", "tree_inorder.tsv",
                         &InorderTraversal, DefaultComparator{}, param_names);
}
