/*
1146. Snapshot Array

Implement a SnapshotArray that supports the following interface:

SnapshotArray(int length) initializes an array-like data structure with the given length.  Initially, each element equals 0.
void set(index, val) sets the element at the given index to be equal to val.
int snap() takes a snapshot of the array and returns the snap_id: the total number of times we called snap() minus 1.
int get(index, snap_id) returns the value at the given index, at the time we took the snapshot with the given snap_id
 

Example 1:

Input: ["SnapshotArray","set","snap","set","get"]
[[3],[0,5],[],[0,6],[0,0]]
Output: [null,null,0,null,5]
Explanation: 
SnapshotArray snapshotArr = new SnapshotArray(3); // set the length to be 3
snapshotArr.set(0,5);  // Set array[0] = 5
snapshotArr.snap();  // Take a snapshot, return snap_id = 0
snapshotArr.set(0,6);
snapshotArr.get(0,0);  // Get the value of array[0] with snap_id = 0, return 5

*/



#include <vector>

class SnapshotArray {
    struct Record {
        int snapshotId;
        int value;
    };

    std::vector<std::vector<Record>> history_;
    int currentSnapshotId_ = 0;

public:
    explicit SnapshotArray(int length) : history_(length) {}

    void set(int index, int value) {
        auto& records = history_[index];

        // Keep only the latest update within the current snapshot.
        if (!records.empty() &&
            records.back().snapshotId == currentSnapshotId_) {
            records.back().value = value;
        } else {
            records.push_back({currentSnapshotId_, value});
        }
    }

    int snap() {
        return currentSnapshotId_++;
    }

    int get(int index, int snapshotId) const {
        const auto& records = history_[index];

        // Find the first record with snapshotId > the requested ID.
        std::size_t left = 0;
        std::size_t right = records.size();

        while (left < right) {
            const auto middle = left + (right - left) / 2;

            if (records[middle].snapshotId <= snapshotId) {
                left = middle + 1;
            } else {
                right = middle;
            }
        }

        // The preceding record is the latest qualifying update.
        return left == 0 ? 0 : records[left - 1].value;
    }
};
