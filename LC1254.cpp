/*
1254. Number of Closed Islands

Given a 2D grid consists of 0s (land) and 1s (water).  An island is a maximal 4-directionally connected group of 0s and a closed island is an island totally (all left, top, right, bottom) surrounded by 1s.

Return the number of closed islands.
*/

/*
Example 1:

Input: grid = [[1,1,1,1,1,1,1,0],[1,0,0,0,0,1,1,0],[1,0,1,0,1,1,1,0],[1,0,0,0,0,1,0,1],[1,1,1,1,1,1,1,0]]
Output: 2
Explanation: 
Islands in gray are closed because they are completely surrounded by water (group of 1s).
Example 2:



Input: grid = [[0,0,1,0,0],[0,1,0,1,0],[0,1,1,1,0]]
Output: 1
Example 3:

Input: grid = [[1,1,1,1,1,1,1],
               [1,0,0,0,0,0,1],
               [1,0,1,1,1,0,1],
               [1,0,1,0,1,0,1],
               [1,0,1,1,1,0,1],
               [1,0,0,0,0,0,1],
               [1,1,1,1,1,1,1]]
Output: 2
 */

#include <vector>
#include <queue>
#include <iostream>

using namespace std;


class Solution {
    const int directions[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

    /**
    * @brief Performs BFS to check if a land mass starting at (r, c) is a closed island.
    * * @param grid The 2D grid where '0' is land and '1' is water/visited.
    * @param start_r Starting row.
    * @param start_c Starting column.
    * @return true if the island is closed (does NOT touch the border), false otherwise.
    */
    bool bfs_is_closed(vector<vector<int>>& grid, int start_r, int start_c) {

        int R = grid.size();
        int C = grid[0].size();
        
        // A flag to track if any part of the island touches the border
        bool touches_border = false;

        // The queue stores pairs of {row, column} for BFS traversal
        queue<pair<int, int>> q;

        // Start BFS from the given cell
        q.push({start_r, start_c});
        // Mark the starting cell as visited (change '0' to '1')
        grid[start_r][start_c] = 1; 

        // Check if the starting cell itself is on the border
        if (start_r == 0 || start_r == R - 1 || start_c == 0 || start_c == C - 1) {
            touches_border = true;
        }

        while (!q.empty()) {
            pair<int, int> current = q.front();
            q.pop();
            int r = current.first;
            int c = current.second;

            // Explore neighbors
            for (int i = 0; i < 4; ++i) {
                int nr = r + directions[i][0];
                int nc = c + directions[i][1];

                // 1. Check if the neighbor is out of bounds
                if (nr < 0 || nr >= R || nc < 0 || nc >= C) {
                    // If a neighbor is out of bounds, the island touches the border
                    touches_border = true;
                    continue; // Move to the next neighbor
                }

                // 2. Check if the neighbor is unvisited land ('0')
                if (grid[nr][nc] == 0) {
                    // Mark as visited and enqueue
                    grid[nr][nc] = 1; 
                    q.push({nr, nc});

                    // 3. Check if the *newly added* neighbor is on the border
                    if (nr == 0 || nr == R - 1 || nc == 0 || nc == C - 1) {
                        touches_border = true;
                    }
                }
                // If the neighbor is water ('1'), we just skip it (it's the 'wall')
            }
        }
        
        // A closed island is one that DID NOT touch the border
        return !touches_border;
    }

public:
    int closedIsland(vector<vector<int>>& grid) {
        if (grid.empty() || grid[0].empty()) {
            return 0;
        }

        int R = grid.size();
        int C = grid[0].size();
        int closed_island_count = 0;
    
        // Iterate through every cell
        for (int r = 0; r < R; ++r) {
            for (int c = 0; c < C; ++c) {
                // Start BFS only on unvisited land ('0')
                if (grid[r][c] == 0) {
                    // If BFS confirms the island is closed, increment the count
                    if (bfs_is_closed(grid, r, c)) {
                        closed_island_count++;
                    }
                }
            }
        }

    return closed_island_count;
    }
};


int main() {

    Solution sol;
    // Example 1: 1 closed island
    vector<vector<int>> grid1 = {
        {1,1,1,1,1,1,1,0},
        {1,0,0,0,0,1,1,0},
        {1,0,1,0,1,1,1,0},
        {1,0,0,0,0,1,0,1},
        {1,1,1,1,1,1,1,1}
    };
    cout << "Closed islands in grid1: " << sol.closedIsland(grid1) << endl; // Expected: 1

    // Example 2: 2 closed islands
    vector<vector<int>> grid2 = {
        {0,0,1,1,0,1,0,0,1,0},
        {1,1,0,1,1,0,1,1,1,0},
        {1,0,1,1,1,0,0,1,1,0},
        {0,1,1,0,0,0,0,1,0,1},
        {0,0,0,0,0,0,1,1,1,0},
        {0,1,0,1,0,1,0,1,1,1},
        {1,0,1,0,1,1,0,0,0,1},
        {1,1,1,1,1,1,0,0,0,0},
        {1,1,1,0,0,1,0,1,0,1},
        {1,1,1,0,1,1,1,0,0,1}
    };
    cout << "Closed islands in grid2: " << sol.closedIsland(grid2) << endl; // Expected: 2

    // Example 3: 0 closed islands (all touch border)
    vector<vector<int>> grid3 = {
        {0,0,1,1},
        {0,1,1,0},
        {1,1,0,0},
        {1,0,0,1}
    };
    cout << "Closed islands in grid3: " << sol.closedIsland(grid3) << endl; // Expected: 0

    return 0;
}