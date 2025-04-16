/*
347. Top K Frequent Elements

Given a non-empty array of integers, return the k most frequent elements.

Example 1:

Input: nums = [1,1,1,2,2,3], k = 2
Output: [1,2]
Example 2:

Input: nums = [1], k = 1
Output: [1]
Note:

You may assume k is always valid, 1 ≤ k ≤ number of unique elements.
Your algorithm's time complexity must be better than O(n log n), where n is the array's size.
It's guaranteed that the answer is unique, in other words the set of the top k frequent elements is unique.
You can return the answer in any order.



Explanation
1.	Frequency Count:
•	Use an unordered_map to count the frequency of each element in the array.
2.	Min-Heap:
•	Use a min-heap (priority queue) to keep track of the top K elements based on their frequency.
•	The heap stores pairs of {element, frequency}.
•	If the heap size exceeds k, remove the element with the smallest frequency.
3.	Extract Results:
•	Extract the elements from the heap and store them in the result vector.
4.	Output:
•	The result vector contains the top K frequent elements.
Example input
nums = {1, 1, 1, 2, 2, 3, 4, 4, 4, 4};
k = 2;

Example Output
Top 2 frequent elements: 1 4

*/


#include <vector>
#include <unordered_map>
#include <queue>
#include <iostream>
using namespace std;

vector<int> topKFrequentElements(const vector<int>& nums, int k) {
    // Step 1: Count the frequency of each element
    unordered_map<int, int> frequencyMap;
    for (int num : nums) {
        frequencyMap[num]++;
    }

    // Step 2: Use a min-heap to keep track of the top K elements
    auto compare = [](const pair<int, int>& a, const pair<int, int>& b) {
        return a.second > b.second; // Min-heap based on frequency
    };
    priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(compare)> minHeap(compare);

    for (const auto& entry : frequencyMap) {
        minHeap.push(entry);
        if (minHeap.size() > k) {
            minHeap.pop(); // Remove the least frequent element
        }
    }

    // Step 3: Extract the top K elements from the heap
    vector<int> result;
    while (!minHeap.empty()) {
        result.push_back(minHeap.top().first);
        minHeap.pop();
    }

    return result;
}

int main() {
    vector<int> nums = {1, 1, 1, 2, 2, 3, 4, 4, 4, 4};
    int k = 2;

    vector<int> result = topKFrequentElements(nums, k);

    cout << "Top " << k << " frequent elements: ";
    for (int num : result) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}
