#include <iostream>
#include <unordered_map>
#include <set>
#include <stdint.h>
#include <algorithm>

class LFUCache {
public:
    LFUCache(uint32_t cap) : m_cap(cap),m_time(0) {}

    int get(int key) {
        if (m_cap <= 0 || m_caches.empty()) return -1;

        auto it = m_cache_maps.find(key);
        if (it == m_cache_maps.end()) return -1;

        Node n = *(it->second);
        ++n.count;
        n.time = ++m_time;
        m_caches.erase(it->second);
        auto ret = m_caches.emplace(std::move(n));
        if (!ret.second) return -1;

        it->second = ret.first;

        return n.value;
    }

    void set(int k, int v) {
        if (m_cap <= 0) return;

        auto it = m_cache_maps.find(k);
        if (it == m_cache_maps.end()) {
            if (m_cap <= m_caches.size())
            {
                m_cache_maps.erase(m_caches.begin()->key);
                m_caches.erase(m_caches.begin());
            }

            auto ret = m_caches.emplace(k, v, 1, ++m_time);
            if (!ret.second) return;

            m_cache_maps[k] = ret.first;
        } else {
            Node n = *(it->second);
            n.value = v;
            ++n.count;
            n.time = ++m_time;
            m_caches.erase(it->second);

            auto ret = m_caches.emplace(std::move(n));
            if (!ret.second) return;

            it->second = ret.first;
        }
    }

    void print() {
        std::cout << "-----------------begin-----------------" << std::endl;
        std::for_each(m_caches.begin(), m_caches.end(), [](const Node& n) { printf("Node(%d->%d|%d|%d)\n", n.key, n.value, n.count, n.time);});
        std::cout << "-----------------end-----------------" << std::endl;
    }

private:
    struct Node {
        int key;
        int value;
        int count;
        int time;
        Node() : key(0), value(0), count(0), time(0) {}
        Node(int key, int value, int cnt, int time) : key(key), value(value), count(cnt), time(time) {}

        bool operator<(const Node& other) const {
            return count == other.count ? time < other.time : count < other.count;
        }
    };

    typedef std::set<Node> CacheSet;
    typedef std::unordered_map<int, CacheSet::const_iterator> CacheMap;

    uint32_t m_cap;
    uint32_t m_time;
    CacheSet m_caches;
    CacheMap m_cache_maps;
};

int main(int argc, const char **argv) {
    LFUCache test(5);
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

