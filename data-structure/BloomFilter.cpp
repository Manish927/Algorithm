/*
A Bloom filter is a probabilistic data structure used to test whether an element is a member of a set. It is space-efficient and allows for false positives but no false negatives. Below is a simple implementation of a Bloom filter in C++

This implementation uses multiple hash functions to insert and query elements in a fixed-size bit array.


Explanation
1.	Bit Array:
•	The bitArray is a fixed-size vector of bool values, initialized to false.
2.	Hash Functions:
•	Multiple hash functions are simulated using std::hash combined with a unique salt (to_string(i)).
3.	Insert Operation:
•	For each hash function, compute the hash value of the element, modulo the size of the bit array.
•	Set the corresponding bit in the bitArray to true.
4.	Contains Operation:
•	For each hash function, compute the hash value of the element.
•	If any corresponding bit in the bitArray is false, the element is definitely not in the set.
•	If all bits are true, the element might be in the set (false positives are possible).
5.	Main Function:
•	Demonstrates inserting and querying elements in the Bloom filter.
---
Example Output
Contains 'apple': Yes
Contains 'banana': Yes
Contains 'grape': No

Key Improvements

1.	Optimal Bit Array Size:
•	Dynamically calculates the size of the bit array based on the expected number of elements and desired false positive rate.
2.	Optimal Number of Hash Functions:
•	Dynamically calculates the number of hash functions for the given parameters.
3.	Double Hashing:
•	Uses two hash functions to generate multiple hash values, reducing the need for multiple independent hash functions.
4.	Compact Bit Array:
•	Uses uint8_t for compact storage, reducing memory usage.

NOTES:
Use of Better Hash Functions
•	Instead of relying on std::hash, use multiple independent hash functions to reduce collisions.
•	A common approach is to use a combination of two hash functions (h1 and h2) to generate multiple hash values:

  
  */

#include <iostream>
#include <vector>
#include <cmath>
#include <functional>
using namespace std;

class BloomFilter {
private:
    vector<uint8_t> bitArray; // Compact bit array
    int size;                // Size of the bit array
    int numHashFunctions;    // Number of hash functions
    hash<string> h1;         // First hash function
    hash<string> h2;         // Second hash function

    // Generate the i-th hash value using double hashing
    size_t hash_i(const string& element, int i) const {
        return (h1(element) + i * h2(element)) % size;
    }

public:
    // Constructor to initialize the Bloom filter
    BloomFilter(int n, double p) {
        // Calculate optimal size of the bit array
        size = ceil(-(n * log(p)) / (log(2) * log(2)));
        bitArray.resize((size + 7) / 8, 0); // Use uint8_t for compact storage

        // Calculate optimal number of hash functions
        numHashFunctions = round((size / n) * log(2));
    }

    // Insert an element into the Bloom filter
    void insert(const string& element) {
        for (int i = 0; i < numHashFunctions; ++i) {
            size_t hashValue = hash_i(element, i);
            bitArray[hashValue / 8] |= (1 << (hashValue % 8)); // Set the bit
        }
    }

    // Query if an element might be in the Bloom filter
    bool contains(const string& element) const {
        for (int i = 0; i < numHashFunctions; ++i) {
            size_t hashValue = hash_i(element, i);
            if (!(bitArray[hashValue / 8] & (1 << (hashValue % 8)))) {
                return false; // Definitely not in the set
            }
        }
        return true; // Might be in the set
    }
};

int main() {
    // Create a Bloom filter for 1000 elements with a 1% false positive rate
    BloomFilter bloomFilter(1000, 0.01);

    // Insert elements into the Bloom filter
    bloomFilter.insert("apple");
    bloomFilter.insert("banana");
    bloomFilter.insert("cherry");

    // Query elements
    cout << "Contains 'apple': " << (bloomFilter.contains("apple") ? "Yes" : "No") << endl;
    cout << "Contains 'banana': " << (bloomFilter.contains("banana") ? "Yes" : "No") << endl;
    cout << "Contains 'grape': " << (bloomFilter.contains("grape") ? "Yes" : "No") << endl;

    return 0;
}
