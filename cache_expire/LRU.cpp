#include <stdio.h>
#include <iostream>
#include <stdint.h>
#include <list>
#include <unordered_map>
#include <algorithm>

class LRUCache {
public:
    LRUCache(uint32_t capacity) : m_capacity(capacity) {}

    int get(int key) {
        if (m_capacity <= 0 || m_cache_map.empty()) return -1;
        auto it = m_cache_map.find(key);
        if (it == m_cache_map.end()) return -1;

        m_cache_list.splice(m_cache_list.begin(), m_cache_list, it->second);
        it->second = m_cache_list.begin();

        return it->second->value;
    }

    void set(int key, int value) {
        auto it = m_cache_map.find(key);
        if (it == m_cache_map.end()) {
            if (m_cache_list.size() >= m_capacity) {
                m_cache_map.erase(m_cache_list.back().key);
                m_cache_list.pop_back();
            }

            m_cache_list.emplace_front(key, value);
            m_cache_map[key] = m_cache_list.begin();
        } else {
            it->second->value = value;
            m_cache_list.splice(m_cache_list.begin(), m_cache_list, it->second);
            it->second = m_cache_list.begin();
        }

    }

    void print() {
        std::cout << "-----------------begin-----------------" << std::endl;
        std::for_each(m_cache_list.begin(), m_cache_list.end(), [](const Node& n) { printf("Node(%d->%d)\n", n.key, n.value);});
        std::cout << "-----------------end-----------------" << std::endl;
    }
private:
    struct Node {
        int key;
        int value;
        Node() : key(0), value(0) {}
        Node(int key, int value) : key(key), value(value) {}
    };

    typedef std::list<Node> CacheList;
    typedef std::unordered_map<int , CacheList::iterator> CacheMap;

    uint32_t m_capacity;
    CacheList m_cache_list;
    CacheMap m_cache_map;

};

int main(int argc, const char **argv) {
    LRUCache test(5);
    test.set(1, 1);
    test.set(2, 2);
    test.set(3,3 );
    test.set(4,4);
    test.set(5,5);
    test.print();
    test.set(6,6);
    test.print();
    test.set(3,10);
    test.print();
    test.get(2);
    test.print();
    test.set(7,7);
    test.print();

    return 0;
}
