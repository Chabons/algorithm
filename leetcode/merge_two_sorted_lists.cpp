#include <stdio.h>

struct ListNode {
    int val;
    ListNode *next;
};

ListNode* mergerTwoList(ListNode* a, ListNode* b) {
    ListNode node {0,0};
    ListNode* tmp = &node;
    while(a && b) {
        if (a->val <= b->val) {
            tmp->next = a;
            a = a->next;
        } else {
            tmp->next = b;
            b = b->next;
        }

        tmp = tmp->next;
    }

    tmp->next = a ? a : b;

    return node.next;
}
