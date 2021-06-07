#include <stdio.h>
#include <algorithm>

struct ListNode {
    int val;
    ListNode *next;
};

ListNode* getIntersectionNode(ListNode* a, ListNode* b) {
    ListNode* ha = a;
    ListNode* hb = b;
    bool switch_a = false;
    bool switch_b = false;
    while (ha && hb) {
        if (ha == hb) break;

        ha = ha->next;
        hb = hb->next;
        if (ha == NULL && !switch_a) ha = b;
        if (hb == NULL && !switch_b) hb = a;
    }

    return ha;
}

int main(int argc, const char **argv) {

    return 0;
}
