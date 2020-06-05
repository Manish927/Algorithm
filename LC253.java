253. Meetings Room II

Given an array meeting time intervals containing start and end time [[s1, e1], [s2,e2], ... ] (s1 < e1), 
find the minimum number of conference room required.

Example 1:
Input: 
Input = [[0,30],[5,10],[15,20]]
Output: 2

Example 2:
Input: 
Input = [[7,10],[2,4]]
Output: 1
*/

class Solution
{
  public int minimumMeetingRooms(Interval[] intervals)
  {
    if (intervals == null || intervals.length == 0)
      return 0;
      
    Arrays.sort(intervals, (t1, t2) -> (t1.start - t2.start));
    
    PriorityQueue<Integer> minHeap = new PriorityQueue<>();
    
    for (Interval i : intervals)
    {
      if (minHeap.size() > 0 && minHeap.peek() <= i.start)
      {
        minHeap.poll();
      }
      
      minHeap.offer(i.end);
    }
    
    return minHeap.size(); 
  }
}

