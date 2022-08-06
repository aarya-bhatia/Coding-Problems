#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "ListNode.hpp"

#include <cstdio>

void printList(ListNode<int> *head)
{
    while(head) { printf("%d ",head->data); head=head->next; }
    printf("\n");
}

TEST_CASE("simple list", "[list]")
{
    ListNode<int> *head = new ListNode<int>(nullptr,nullptr,1);
    ListNode<int> *n1 = head->insertAfter(2);
    ListNode<int> *n2 = n1->insertAfter(3);
    ListNode<int> *n3 = n2->insertAfter(4);
    
    REQUIRE(head->next == n1);
    REQUIRE(n1->next == n2);
    REQUIRE(n2->next == n3);
    REQUIRE(n3->next == nullptr);
    REQUIRE(n3->prev == n2);
    REQUIRE(n2->prev == n1);
    REQUIRE(n1->prev == head);
    REQUIRE(head->prev == nullptr);

    printList(head);
}
