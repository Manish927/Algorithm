/*146. LRU Cache
Design and implement a data structure for Least Recently Used (LRU) cache. It should support the following operations: get and put.
get(key) - Get the value (will always be positive) of the key if the key exists in the cache, otherwise return -1.
put(key, value) - Set or insert the value if the key is not already present. When the cache reached its capacity, it should invalidate the least recently used item before inserting a new item.
The cache is initialized with a positive capacity.
Follow up:
Could you do both operations in O(1) time complexity?
Example:
LRUCache cache = new LRUCache( 2 /* capacity */ );
/*
cache.put(1, 1);
cache.put(2, 2);
cache.get(1);       // returns 1
cache.put(3, 3);    // evicts key 2
cache.get(2);       // returns -1 (not found)
cache.put(4, 4);    // evicts key 1
cache.get(1);       // returns -1 (not found)
cache.get(3);       // returns 3
cache.get(4);       // returns 4*/

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache obj = new LRUCache(capacity);
 * int param_1 = obj.get(key);
 * obj.put(key,value);
 */

#include <list>
#include <unordered_map>
#include <utility>

class LRUCache {
    // Front = most recently used; back = least recently used.
    std::list<std::pair<int, int>> cache;
    std::unordered_map<int, decltype(cache)::iterator> hash_map;
    int capacity_;

public:
    explicit LRUCache(int capacity) : capacity_(capacity) {
        if (capacity > 0) {
            // Insertion happens before eviction: allow one extra entry.
            hash_map.reserve(static_cast<std::size_t>(capacity) + 1);
        }
    }

    int get(int key) {
        auto it = hash_map.find(key);
        if (it == hash_map.end()) {
            return -1;
        }

        cache.splice(cache.begin(), cache, it->second);
        return it->second->second;
    }

    void put(int key, int value) {
        if (capacity_ <= 0) {
            return;
        }

        auto [it, inserted] =
            hash_map.try_emplace(key, cache.end());

        if (!inserted) {
            // Existing key: update value and mark most recently used.
            it->second->second = value;
            cache.splice(cache.begin(), cache, it->second);
            return;
        }

        // New key: create its list node.
        try {
            cache.emplace_front(key, value);
        } catch (...) {
            // Remove the placeholder if list allocation fails.
            hash_map.erase(it);
            throw;
        }

        it->second = cache.begin();

        if (hash_map.size() >
            static_cast<std::size_t>(capacity_)) {
            hash_map.erase(cache.back().first);
            cache.pop_back();
        }
    }
};
