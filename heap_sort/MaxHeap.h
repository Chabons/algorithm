#ifndef MAXHEAP_H
#define MAXHEAP_H

#include <stdint.h>
#include <stdlib.h>
#include <iostream>
#include <utility>
#include <new>

template <typename T>
class MaxHeap {
public:
    MaxHeap(uint32_t size = 1000);
    virtual ~MaxHeap();

    bool insert(const T&);
    void removeMax();
    T* getMax();
    bool isEmpty();
    bool isFull();
    void clear();

    void dump();

private:
    MaxHeap(const MaxHeap<T>&) = delete;
    MaxHeap<T>& operator=(const MaxHeap<T>&) = delete;
    void filterDown(uint32_t start);
    void filterUp(uint32_t start);

private:
    T* m_heaps;
    uint32_t m_size;
    uint32_t m_max_size;
};

template <typename T>
MaxHeap<T>::MaxHeap(uint32_t size) : m_size(0), m_max_size(size) {
    m_heaps = new(std::nothrow) T[m_max_size];
    if (m_heaps == nullptr) exit(-1);
}

template <typename T>
MaxHeap<T>::~MaxHeap() {
    if (m_heaps) delete[] m_heaps;
}

template <typename T>
void MaxHeap<T>::clear() {
    m_size = 0;
}

template <typename T>
bool MaxHeap<T>::isFull() {
    return m_size == m_max_size;
}

template <typename T>
bool MaxHeap<T>::isEmpty() {
    return m_size == 0;
}

template <typename T>
bool MaxHeap<T>::insert(const T& value) {
    if (isFull()) return false;

    m_heaps[m_size++] = std::move(value);
    filterUp(m_size - 1);

    return true;
}

template <typename T>
void MaxHeap<T>::filterUp(uint32_t start) {
    if (start >= m_size) return;

    while (start > 0) {
        uint32_t idx = (start - 1) / 2;
        if (m_heaps[idx] >= m_heaps[start]) break;

        std::swap(m_heaps[idx], m_heaps[start]);
        start = idx;
    }
}

template <typename T>
void MaxHeap<T>::filterDown(uint32_t start) {
    if (start >= m_size) return;

    uint32_t idx = 2 * start + 1;
    while (idx < m_size) {
        if (idx + 1 < m_size && m_heaps[idx + 1] > m_heaps[idx]) {
            ++idx;
        }
        if (m_heaps[idx] <= m_heaps[start]) break;

        std::swap(m_heaps[idx], m_heaps[start]);
        start = idx;
        idx = 2 * start + 1;
    }
}

template <typename T>
void MaxHeap<T>::removeMax() {
    if (isEmpty()) return;

    std::swap(m_heaps[0], m_heaps[--m_size]);
    filterDown(0);
}

template <typename T>
T* MaxHeap<T>::getMax() {
    if (isEmpty) return nullptr;

    return &m_heaps[0];
}

template <typename T>
void MaxHeap<T>::dump()
{
    if (!std::is_integral<T>::value) {
        return;
    }
    for (int i = 0; i < m_size; ++i) {
        std::cout<< m_heaps[i] << "\t";
    }
    std::cout << "\n" << std::endl;
}

#endif // MAXHEAP_H
