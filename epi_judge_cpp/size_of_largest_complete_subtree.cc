#include "binary_tree_node.h"
#include "test_framework/generic_test.h"

struct Status {
  bool perfect;
  bool complete;
  int size;
  BinaryTreeNode<int>* root;
};

int getHeight(int size) { return ceil(log2(size + 1)); }

Status largestCompleteSubtreeHelper(
    const unique_ptr<BinaryTreeNode<int>>& tree) {
  Status st;
  if (tree == nullptr) {
    st.complete = true;
    st.perfect = true;
    st.size = 0;
    st.root = tree.get();
    return st;
  }
  Status left, right;
  left = largestCompleteSubtreeHelper(tree->left);
  right = largestCompleteSubtreeHelper(tree->right);
  if (left.perfect && right.complete &&
      getHeight(left.size) == getHeight(right.size)) {
    st.complete = true;
    st.perfect = right.perfect;
    st.size = left.size + right.size + 1;
    st.root = tree.get();
    return st;
  }

  if (left.complete && right.perfect &&
      getHeight(left.size) == getHeight(right.size) + 1) {
    st.complete = true;
    st.perfect = false;
    st.size = left.size + right.size + 1;
    st.root = tree.get();
    return st;
  }

  st.complete = false;
  st.perfect = false;
  st.size = std::max(left.size, right.size);
  st.root = left.size >= right.size ? left.root : right.root;
  return st;
}

int largestCompleteSubtree(const unique_ptr<BinaryTreeNode<int>>& tree) {
  if (tree == nullptr) return 0;
  return largestCompleteSubtreeHelper(tree).size;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "size_of_largest_complete_subtree.cc",
                         "size_of_largest_complete_subtree.tsv",
                         &largestCompleteSubtree, DefaultComparator{},
                         param_names);
}
