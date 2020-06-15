/*
787. Cheapest Flights Within K Stops

There are n cities connected by m flights. Each flight starts from city u and arrives at v with a price w.

Now given all the cities and flights, together with starting city src and the destination dst, 
your task is to find the cheapest price from src to dst with up to k stops. If there is no such route, output -1.

Example 1:
Input: 
n = 3, edges = [[0,1,100],[1,2,100],[0,2,500]]
src = 0, dst = 2, k = 1
Output: 200
Explanation: 
The graph looks like this:


The cheapest price from city 0 to city 2 with at most 1 stop costs 200, as marked red in the picture.
Example 2:
Input: 
n = 3, edges = [[0,1,100],[1,2,100],[0,2,500]]
src = 0, dst = 2, k = 0
Output: 500
Explanation: 
The graph looks like this:


The cheapest price from city 0 to city 2 with at most 0 stop costs 500, as marked blue in the picture.
*/

class Solution {
public:
    Solution()
    {
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);
        cout.tie(NULL);
    }
    
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int K) 
    {    
        int ans = INT_MAX;
        unordered_map<int, vector<pair<int, int>> > schedules;
        
        for(auto flight: flights)            
            schedules[flight[0]].emplace_back(flight[1], flight[2]);
         
        queue<pair<int, int>> q{{{src, 0}}};
        
        for(int step = 0; !q.empty() && step <= K+1; step++)
        {
            for(int size = q.size(); size-->0;)
            {
                auto [target, cost] = q.front();
                q.pop();
                
                if(target == dst) 
                {
                    ans = min(ans, cost);
                    continue;
                }
                
                for(auto& next: schedules[target])
                {
                    if(cost + next.second > ans ) 
                        continue;
                    if(step == K + 1 && next.first != dst) 
                        continue;
                    
                    q.emplace(next.first, cost + next.second);
                }
            }
        }
        return ans==INT_MAX? -1: ans;        
    }
};
