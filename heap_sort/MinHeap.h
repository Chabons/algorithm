#ifndef MINHEAP_H
#define MINHEAP_H

#include <stdlib.h>
#include <type_traits>
#include <iostream>
#include <new>
#include <utility>

template <typename T>
class MinHeap {
public:
    MinHeap(int size = 1000);
    virtual ~MinHeap();

    bool insert(const T& value);
    bool removeMin();
    T* getMin();
    bool isEmpty();
    bool isFull();
    void clear();

    void dump();

private:
    MinHeap<T>& operator=(const MinHeap<T>& ) = delete;
    MinHeap(const MinHeap<T>&) = delete;
    void filterDown(int start);
    void filterUp(int start); // 自下往上调整

private:
    T* m_heaps;
    int m_size;
    int m_max_size;
};


template <typename T>
MinHeap<T>::MinHeap(int size) : m_heaps(nullptr), m_size(0), m_max_size(size)
{
    m_heaps = new(std::nothrow) T[size];
    if (m_heaps == nullptr) exit(-1);
}

template <typename T>
MinHeap<T>::~MinHeap()
{
    delete[] m_heaps;
    m_heaps = nullptr;
    m_size = 0;
}


template <typename T>
void MinHeap<T>::clear()
{
    m_size = 0;
}


template <typename T>
void MinHeap<T>::filterDown(int start)
{
    if (start >= m_size || start < 0) return;

    int idx = 2 * start + 1;
    while (idx < m_size) {
        if (idx + 1 < m_size && m_heaps[idx] > m_heaps[idx + 1]) {
            idx++;
        }
        if (m_heaps[start] <= m_heaps[idx]) {
            break;
        }
        std::swap(m_heaps[start], m_heaps[idx]);
        start = idx;
        idx = 2 * start + 1;
    }
}

template <typename T>
void MinHeap<T>::filterUp(int start)
{
    if (start >= m_size || start < 0) return;

    while (start > 0) {
        int idx = (start - 1) / 2;
        if (m_heaps[start] >= m_heaps[idx]) {
            break;
        }

        std::swap(m_heaps[idx], m_heaps[start]);
        start = idx;
    }
}


template <typename T>
T* MinHeap<T>::getMin()
{
    if (isEmpty()) {
        return nullptr;
    }

    return &m_heaps[0];
}


template <typename T>
bool MinHeap<T>::insert(const T& value)
{
    if (isFull()) return false;

    m_heaps[m_size++] = value;

    filterUp(m_size - 1);

    return true;
}


template <typename T>
bool MinHeap<T>::isEmpty()
{
    return m_size == 0;
}


template <typename T>
bool MinHeap<T>::isFull()
{
    return m_size == m_max_size;
}


template <typename T>
bool MinHeap<T>::removeMin()
{
    if (isEmpty()) return false;

    T temp = m_heaps[0];
    m_heaps[0] = m_heaps[m_size - 1];
    --m_size;
    filterDown(0);

    return true;
}

template <typename T>
void MinHeap<T>::dump()
{
    if (!std::is_integral<T>::value) {
        return;
    }
    for (int i = 0; i < m_size; ++i) {
        std::cout<< m_heaps[i] << "\t";
    }
    std::cout << "\n" << std::endl;
}

#endif // MINHEAP_H
