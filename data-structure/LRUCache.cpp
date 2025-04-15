/*
Here is an implementation of an LRU (Least Recently Used) Cache in C++ using a combination of std::unordered_map and std::list. This approach ensures O(1) time complexity for both get and put operations.

Explanation
1.	Data Structures:
•	std::list: Maintains the order of keys based on their usage. The most recently used key is at the front, and the least recently used key is at the back.
•	std::unordered_map: Maps keys to iterators pointing to their corresponding elements in the list for O(1) lookups.
2.	Operations:
•	get(int key):
•	If the key exists, move it to the front of the list (most recently used) and return its value.
•	If the key does not exist, return -1.
•	put(int key, int value):
•	If the key already exists, update its value and move it to the front.
•	If the key does not exist and the cache is full, remove the least recently used key (back of the list) before inserting the new key-value pair.
3.	Debugging:
•	The printCache() function is included to visualize the current state of the cache.
Example Output
For the above code, the output will be:

Cache after adding 3 elements: (3, 30) (2, 20) (1, 10) 
Cache after accessing key 2: (2, 20) (3, 30) (1, 10) 
Cache after adding key 4: (4, 40) (2, 20) (3, 30) 
Value for key 3: 30
Cache after accessing key 3: (3, 30) (4, 40) (2, 20) 
Cache after adding key 5: (5, 50) (3, 30) (4, 40) 


Complexity
•	Time Complexity:
•	get: O(1) (hash map lookup and list operations).
•	put: O(1) (hash map insertion/erasure and list operations).
•	Space Complexity: O(capacity) for storing the cache.

*/

#include <iostream>
#include <unordered_map>
#include <list>
using namespace std;

class LRUCache {
private:
    int capacity;
    list<pair<int, int>> cache; // Doubly linked list to store keys and values
    unordered_map<int, list<pair<int, int>>::iterator> cacheMap; // Hash map for O(1) lookups

public:
    LRUCache(int capacity) : capacity(capacity) {}

    // Get the value of the key if it exists, otherwise return -1
    int get(int key) {
        if (cacheMap.find(key) == cacheMap.end()) {
            return -1; // Key not found
        }

        // Move the accessed key-value pair to the front of the list
        auto it = cacheMap[key];
        int value = it->second;
        cache.erase(it);
        cache.push_front({key, value});
        cacheMap[key] = cache.begin();

        return value;
    }

    // Put a key-value pair into the cache
    void put(int key, int value) {
        // If the key already exists, update its value and move it to the front
        if (cacheMap.find(key) != cacheMap.end()) {
            auto it = cacheMap[key];
            cache.erase(it);
        } else if (cache.size() == capacity) {
            // If the cache is full, remove the least recently used item
            auto lru = cache.back();
            cacheMap.erase(lru.first);
            cache.pop_back();
        }

        // Insert the new key-value pair at the front
        cache.push_front({key, value});
        cacheMap[key] = cache.begin();
    }

    // Print the current state of the cache (for debugging)
    void printCache() {
        for (const auto& pair : cache) {
            cout << "(" << pair.first << ", " << pair.second << ") ";
        }
        cout << endl;
    }
};

int main() {
    LRUCache lru(3); // Create an LRU cache with capacity 3

    lru.put(1, 10);
    lru.put(2, 20);
    lru.put(3, 30);
    cout << "Cache after adding 3 elements: ";
    lru.printCache();

    lru.get(2); // Access key 2
    cout << "Cache after accessing key 2: ";
    lru.printCache();

    lru.put(4, 40); // Add key 4, which evicts the least recently used key (1)
    cout << "Cache after adding key 4: ";
    lru.printCache();

    cout << "Value for key 3: " << lru.get(3) << endl; // Access key 3
    cout << "Cache after accessing key 3: ";
    lru.printCache();

    lru.put(5, 50); // Add key 5, which evicts the least recently used key (2)
    cout << "Cache after adding key 5: ";
    lru.printCache();

    return 0;
}


