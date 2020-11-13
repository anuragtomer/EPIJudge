#include "list_node.h"
#include "test_framework/generic_test.h"
shared_ptr<ListNode<int>> EvenOddMerge(const shared_ptr<ListNode<int>>& L) {
  auto head1 = L, head2 = L->next;
  auto oddHead = head2, evenHead = head1;
  auto originalHead = L;
  while (head1 && head2) {
    head1->next = head2->next;
    if (head1->next) head1 = head1->next;
    if (head2->next) {
      head2->next = head1->next;
      head2 = head2->next;
    }
  }
  head1->next = oddHead;
  return originalHead;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"L"};
  return GenericTestMain(args, "even_odd_list_merge.cc",
                         "even_odd_list_merge.tsv", &EvenOddMerge,
                         DefaultComparator{}, param_names);
}
