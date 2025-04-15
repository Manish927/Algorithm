/*
Explanation
1.	Data Structures:
•	std::list: Maintains the insertion order of key-value pairs.
•	std::unordered_map: Maps keys to iterators pointing to the corresponding elements in the list for O(1) lookups.
2.	Operations:
•	put: Inserts a new key-value pair or updates an existing one. If the key exists, the value is updated, and the key is moved to the end of the list.
•	get: Retrieves the value associated with a key. Throws an exception if the key is not found.
•	remove: Removes a key-value pair from both the list and the map.
•	containsKey: Checks if a key exists in the map.
•	print: Prints all key-value pairs in insertion order.
3.	Example Usage:
•	Insert key-value pairs: put("one", 1), put("two", 2).
•	Update a value: put("two", 22).
•	Remove a key: remove("one").
•	Check if a key exists: containsKey("three").
•	Get a value: get("three").
Output
For the above code, the output will be:
Initial map:
one: 1
two: 2
three: 3

After updating 'two':
one: 1
three: 3
two: 22

After removing 'one':
three: 3
two: 22

Contains 'three': Yes
Value of 'three': 3
*/

#include <iostream>
#include <unordered_map>
#include <list>
#include <utility>
using namespace std;

template <typename K, typename V>
class LinkedHashMap {
private:
    list<pair<K, V>> itemList; // Doubly linked list to maintain insertion order
    unordered_map<K, typename list<pair<K, V>>::iterator> itemMap; // Hash map for O(1) lookups

public:
    // Insert or update a key-value pair
    void put(const K& key, const V& value) {
        // If the key already exists, update its value and move it to the end
        if (itemMap.find(key) != itemMap.end()) {
            auto it = itemMap[key];
            it->second = value; // Update the value
            itemList.splice(itemList.end(), itemList, it); // Move to the end
        } else {
            // Insert a new key-value pair
            itemList.emplace_back(key, value);
            itemMap[key] = --itemList.end();
        }
    }

    // Get the value associated with a key
    V get(const K& key) {
        if (itemMap.find(key) == itemMap.end()) {
            throw out_of_range("Key not found");
        }
        return itemMap[key]->second;
    }

    // Remove a key-value pair
    void remove(const K& key) {
        if (itemMap.find(key) == itemMap.end()) {
            return; // Key does not exist
        }
        auto it = itemMap[key];
        itemList.erase(it); // Remove from the list
        itemMap.erase(key); // Remove from the map
    }

    // Check if the map contains a key
    bool containsKey(const K& key) {
        return itemMap.find(key) != itemMap.end();
    }

    // Print all key-value pairs in insertion order
    void print() {
        for (const auto& item : itemList) {
            cout << item.first << ": " << item.second << endl;
        }
    }
};

int main() {
    LinkedHashMap<string, int> linkedHashMap;

    // Insert key-value pairs
    linkedHashMap.put("one", 1);
    linkedHashMap.put("two", 2);
    linkedHashMap.put("three", 3);

    // Print the map
    cout << "Initial map:" << endl;
    linkedHashMap.print();

    // Update a value
    linkedHashMap.put("two", 22);
    cout << "\nAfter updating 'two':" << endl;
    linkedHashMap.print();

    // Remove a key
    linkedHashMap.remove("one");
    cout << "\nAfter removing 'one':" << endl;
    linkedHashMap.print();

    // Check if a key exists
    cout << "\nContains 'three': " << (linkedHashMap.containsKey("three") ? "Yes" : "No") << endl;

    // Get a value
    cout << "Value of 'three': " << linkedHashMap.get("three") << endl;

    return 0;
}
