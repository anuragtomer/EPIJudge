#include <vector>

#include "binary_tree_node.h"
#include "test_framework/generic_test.h"
using std::stack;
using std::vector;

vector<int> PreorderTraversal(const unique_ptr<BinaryTreeNode<int>>& tree) {
  vector<int> result;
  stack<BinaryTreeNode<int>*> st;
  st.emplace(tree.get());
  while (!st.empty()) {
    auto curr = st.top();
    st.pop();
    if (curr != nullptr) {
      result.emplace_back(curr->data);
      st.emplace(curr->right.get());
      st.emplace(curr->left.get());
    }
  }
  return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "tree_preorder.cc", "tree_preorder.tsv",
                         &PreorderTraversal, DefaultComparator{}, param_names);
}
