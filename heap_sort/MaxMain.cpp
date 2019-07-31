#include "MaxHeap.h"

int main(int argc, const char **argv) {
    MaxHeap<int> min_heap(10);
    min_heap.insert(10);
    min_heap.insert(7);
    min_heap.insert(8);
    min_heap.insert(1);
    min_heap.insert(4);
    min_heap.insert(2);
    min_heap.dump();
    min_heap.removeMax();
    min_heap.dump();
    return 0;
}
