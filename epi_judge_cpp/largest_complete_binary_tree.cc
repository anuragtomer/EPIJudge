// C++ implementation of the approach
#include <iostream>
using namespace std;

// Node structure of the tree
struct node {
  int data;
  struct node* left;
  struct node* right;
  node(int _data) {
    data = _data;
    left = nullptr;
    right = nullptr;
  }
};

// Structure for return type of
// function findPerfectBinaryTree
struct returnType {
  // To store if sub-tree is perfect or not
  bool isPerfect;

  // To store if sub-tree is complete or not
  bool isComplete;

  // size of the tree
  int size;

  // Root of biggest complete sub-tree
  node* rootTree;
};

// helper function that returns height
// of the tree given size
int getHeight(int size) { return ceil(log2(size + 1)); }

// Function to return the biggest
// complete binary sub-tree
returnType findCompleteBinaryTree(struct node* root) {
  returnType rt;
  if (!root) {
    rt.isPerfect = true;
    rt.isComplete = true;
    rt.size = 0;
    rt.rootTree = root;
    return rt;
  }

  returnType left = findCompleteBinaryTree(root->left);
  returnType right = findCompleteBinaryTree(root->right);

  if (left.isPerfect == true && right.isComplete == true &&
      getHeight(left.size) == getHeight(right.size)) {
    rt.isComplete = true;
    rt.isPerfect = right.isPerfect ? true : false;
    rt.size = left.size + right.size + 1;
    rt.rootTree = root;
    return rt;
  }

  if (left.isComplete == true && right.isPerfect == true &&
      getHeight(left.size) == getHeight(right.size) + 1) {
    rt.isComplete = true;
    rt.isPerfect = false;
    rt.size = left.size + right.size + 1;
    rt.rootTree = root;
    return rt;
  }

  rt.isComplete = false;
  rt.isPerfect = false;
  rt.size = max(left.size, right.size);
  rt.rootTree = left.size > right.size ? left.rootTree : right.rootTree;
  return rt;
}

// Function to print the inorder traversal of the tree
void inorderPrint(node* root) {
  if (root != NULL) {
    inorderPrint(root->left);
    cout << root->data << " ";
    inorderPrint(root->right);
  }
}

// Driver code
int main() {
  // Create the tree
  struct node* root = new node(50);
  root->left = new node(30);
  root->right = new node(60);
  root->left->left = new node(5);
  root->left->right = new node(20);
  root->right->left = new node(45);
  root->right->right = new node(70);
  root->right->left->left = new node(10);

  // Get the biggest sized complete binary sub-tree
  struct returnType ans = findCompleteBinaryTree(root);

  cout << "Size : " << ans.size << endl;

  // Print the inorder traversal of the found sub-tree
  cout << "Inorder Traversal : ";
  inorderPrint(ans.rootTree);

  return 0;
}
/*
// Declaring returnType that
  // needs to be returned
  returnType rt;

  // If root is NULL then it is considered as both
  // perfect and complete binary tree of size 0
  if (root == NULL) {
    rt.isPerfect = true;
    rt.isComplete = true;
    rt.size = 0;
    rt.rootTree = NULL;
    return rt;
  }

  // Recursive call for left and right child
  returnType lv = findCompleteBinaryTree(root->left);
  returnType rv = findCompleteBinaryTree(root->right);

  // CASE - A
  // If left sub-tree is perfect and right is complete and
  // there height is also same then sub-tree root
  // is also complete binary sub-tree with size equal to
  // sum of left and right subtrees plus one for current root
  if (lv.isPerfect == true && rv.isComplete == true &&
      getHeight(lv.size) == getHeight(rv.size)) {
    rt.isComplete = true;

    // If right sub-tree is perfect then
    // root is also perfect
    rt.isPerfect = (rv.isPerfect ? true : false);
    rt.size = lv.size + rv.size + 1;
    rt.rootTree = root;
    return rt;
  }

  // CASE - B
  // If left sub-tree is complete and right is perfect and the
  // height of left is greater than right by one then sub-tree root
  // is complete binary sub-tree with size equal to
  // sum of left and right subtrees plus one for current root.
  // But sub-tree cannot be perfect binary sub-tree.
  if (lv.isComplete == true && rv.isPerfect == true &&
      getHeight(lv.size) == getHeight(rv.size) + 1) {
    rt.isComplete = true;
    rt.isPerfect = false;
    rt.size = lv.size + rv.size + 1;
    rt.rootTree = root;
    return rt;
  }

  // CASE - C
  // Else this sub-tree cannot be a complete binary tree
  // and simply return the biggest sized complete sub-tree
  // found till now in the left or right sub-trees
  rt.isPerfect = false;
  rt.isComplete = false;
  rt.size = max(lv.size, rv.size);
  rt.rootTree = (lv.size > rv.size ? lv.rootTree : rv.rootTree);
  return rt;
*/