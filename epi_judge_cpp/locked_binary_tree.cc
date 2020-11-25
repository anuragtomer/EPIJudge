#include <memory>

using std::shared_ptr;

class BinaryTreeNode {
 public:
  bool IsLocked() const { return locked_; }

  bool Lock() {
    if (numLockedDescendants_ > 0 || locked_) return false;
    for (auto iter = parent_; iter != nullptr; iter = iter->parent_) {
      if (iter->locked_) return false;
    }
    locked_ = true;
    for (auto iter = parent_; iter != nullptr; iter = iter->parent_) {
      ++iter->numLockedDescendants_;
    }
    return locked_;
  }

  void Unlock() {
    if (locked_) {
      locked_ = false;
      for (auto iter = parent_; iter != nullptr; iter = iter->parent_) {
        --(iter->numLockedDescendants_);
      }
    }
  }

 private:
  shared_ptr<BinaryTreeNode> parent_, left_, right_;
  bool locked_ = false;
  int numLockedDescendants_ = 0;
};
