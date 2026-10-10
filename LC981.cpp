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
*/
