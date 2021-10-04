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

class LRUCache {
    
    std::list<pair<int, int>> cache;
    typedef unordered_map<int, list<pair<int, int>>::iterator> HashMapT;
    HashMapT hash_map;
    typedef HashMapT::iterator IteratorT;
    
    
    void refresh(int key, int value)
    {
        cache.erase(hash_map[key]);
        cache.push_front({key, value});
        hash_map[key] = cache.begin();
    }
    
    int capacity_;
public:
    LRUCache(int capacity) {
        capacity_ = capacity;
        hash_map.reserve(capacity);
    }
    
    int get(int key) {
        
        IteratorT iter = hash_map.find(key);
        
        if (iter != hash_map.end())
        {
            refresh(key, iter->second->second);
            return iter->second->second;
        }
        
        return -1;
    }
    
    void put(int key, int value) {
        
        IteratorT iter = hash_map.find(key);
        
        if (iter != hash_map.end())
        {
            refresh(key, value);
        }
        else
        {
            cache.push_front({key, value});
            hash_map[key] = cache.begin();
            
            if (hash_map.size() > capacity_)
            {
                hash_map.erase(cache.back().first);
                cache.pop_back();
            }
        }
    }
};
