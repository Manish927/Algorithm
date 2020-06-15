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



class SnapshotArray {
    std::vector<std::vector<pair<int, int>>> snapShotBuffer;
    int snap_id = 0;
public:
    SnapshotArray(int length) 
    {
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);
        snapShotBuffer.resize(length);
    }
    
    void set(int index, int val) 
    {
        auto& idx_record = snapShotBuffer[index];
        
        if (!idx_record.empty() && idx_record.back().second == snap_id)
        {
            idx_record.back().first = val;
        }
        else
            idx_record.push_back({val, snap_id});
    }
    
    int snap() 
    {
        snap_id++;
        return snap_id - 1;
    }
    
    int get(int index, int snap_id)
    {
        auto& idx_recs = snapShotBuffer[index];
        
        if (idx_recs.empty())
            return 0;
        
        if (snap_id < idx_recs[0].second)
            return 0;
        
        
        int left = 0;
        int right = idx_recs.size();
        
        while (right - left > 1)
        {
            int middle = (left + right) / 2;
            
            if (idx_recs[middle].second <= snap_id)
                left = middle;
            else
                right = middle;
        }
        
        return idx_recs[left].first;
    }
};
