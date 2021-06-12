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

        auto it = m_caches.find(key);
    }

private:
    struct Node {
        int key;
        int value;
        int count;
        int time;
        Node() : key(0), value(0), count(0), time(0) {}
        Node(int key, int value, int cnt, int time) : key(key), value(value), count(cnt), time(time) {}
    };

    typedef std::unordered_map<int, Node> CacheMap;
    auto CacheCompare = [](const CacheMap::const_iterator& lv, const CacheMap::const_iterator& rv) -> bool { return lv->count == rv->count ? lv->time < rv->time : lv->count < rv->count;};
    typedef std::set<CacheMap::const_iterator, decltype(CacheCompare)> CacheSet(CacheCompare);

    uint32_t m_cap;
    uint32_t m_time;
    CacheMap m_caches;
    CacheSet m_cache_set;
};

int main(int argc, const char **argv) {

    return 0;
}

