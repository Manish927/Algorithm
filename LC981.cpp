/* 
Question: Time Based Key-Value Store
Design a data structure that stores multiple values for each key at different timestamps.
Implement:
- set(key, value, timestamp): Store the value for the key at the given timestamp.
- get(key, timestamp): Return the value with the largest stored timestamp ≤ the requested timestamp. Return "" if no qualifying value exists.
Assumption: Timestamps supplied to set() are strictly increasing, as required by LeetCode 981.
Solution
Use an unordered_map to associate each key with a sorted vector of timestamped values. Append during set(), and binary-search during get().
The following complete C++20 program includes a driver with test cases: 

g++ -std=c++20 -Wall -Wextra -pedantic time_map.cpp -o time_map
./time_map
*/


#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

class TimeMap {
    struct Record {
        int timestamp;
        std::string value;
    };

    std::unordered_map<std::string, std::vector<Record>> history_;

public:
    void set(const std::string& key,
             const std::string& value,
             int timestamp) {
        history_[key].push_back({timestamp, value});
    }

    std::string get(const std::string& key, int timestamp) const {
        const auto it = history_.find(key);

        if (it == history_.end()) {
            return "";
        }

        const auto& records = it->second;

        // Search the half-open range [left, right).
        std::size_t left = 0;
        std::size_t right = records.size();

        // Find the first record whose timestamp exceeds the query.
        while (left < right) {
            const auto middle = left + (right - left) / 2;

            if (records[middle].timestamp <= timestamp) {
                left = middle + 1;
            } else {
                right = middle;
            }
        }

        // No timestamp was <= the query.
        if (left == 0) {
            return "";
        }

        return records[left - 1].value;
    }
};

int main() {
    TimeMap store;
    int passed = 0;
    int total = 0;

    auto check = [&](const std::string& name,
                     const std::string& actual,
                     const std::string& expected) {
        ++total;
        const bool success = actual == expected;

        if (success) {
            ++passed;
        }

        std::cout << (success ? "[PASS] " : "[FAIL] ")
                  << name
                  << " | expected: \"" << expected
                  << "\", actual: \"" << actual << "\"\n";
    };

    // Test 1: Empty store.
    check("Empty store", store.get("foo", 1), "");

    store.set("foo", "bar", 1);

    // Tests 2–4: Before, at, and after the first timestamp.
    check("Before first timestamp", store.get("foo", 0), "");
    check("Exact first timestamp", store.get("foo", 1), "bar");
    check("After first timestamp", store.get("foo", 3), "bar");

    store.set("foo", "bar2", 4);

    // Tests 5–7: Historical lookup and latest value.
    check("Between timestamps", store.get("foo", 3), "bar");
    check("Exact second timestamp", store.get("foo", 4), "bar2");
    check("After latest timestamp", store.get("foo", 5), "bar2");

    // Test 8: Missing key in a populated store.
    check("Missing key", store.get("unknown", 5), "");

    // Add another key. All set timestamps remain strictly increasing.
    store.set("AAPL", "100", 6);
    store.set("AAPL", "105", 10);
    store.set("AAPL", "110", 15);

    // Tests 9–14: Independent key and multiple historical records.
    check("Second key before first update", store.get("AAPL", 5), "");
    check("Second key exact first update", store.get("AAPL", 6), "100");
    check("Second key between updates", store.get("AAPL", 9), "100");
    check("Second key exact middle update", store.get("AAPL", 10), "105");
    check("Second key before final update", store.get("AAPL", 14), "105");
    check("Second key latest value", store.get("AAPL", 20), "110");

    // Test 15: Updates to another key do not affect foo.
    check("Keys remain independent", store.get("foo", 20), "bar2");

    std::cout << "\nResult: " << passed << "/" << total
              << " tests passed.\n";

    return passed == total ? 0 : 1;
}
