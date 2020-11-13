#include <memory>

#include "list_node.h"
#include "test_framework/generic_test.h"
using std::shared_ptr;

int Length(const shared_ptr<ListNode<int>>& L) {
  shared_ptr<ListNode<int>> copy = L;
  int len = 1;
  while (copy->next) {
    len++;
    copy = copy->next;
  }
  return len;
}

shared_ptr<ListNode<int>> CyclicallyRightShiftList(shared_ptr<ListNode<int>> L,
                                                   int k) {
  int len = Length(L);
  if (len <= 1) return L;
  k = len - (k % len);
  if (k == 0 || k == len) return L;
  auto kahead = L;
  auto phead = L;
  while (k--) {
    kahead = kahead->next;
  }
  L = kahead;
  kahead->next = phead;
  while (phead->next != L) phead = phead->next;
  phead->next = nullptr;
  return L;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"L", "k"};
  return GenericTestMain(
      args, "list_cyclic_right_shift.cc", "list_cyclic_right_shift.tsv",
      &CyclicallyRightShiftList, DefaultComparator{}, param_names);
}
