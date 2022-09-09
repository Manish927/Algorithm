/*
 684. Redundant Connection

In this problem, a tree is an undirected graph that is connected and has no cycles.

You are given a graph that started as a tree with n nodes labeled from 1 to n, with one additional edge added. The added edge has two different vertices chosen from 1 to n, and was not an edge that already existed. The graph is represented as an array edges of length n where edges[i] = [ai, bi] indicates that there is an edge between nodes ai and bi in the graph.

Return an edge that can be removed so that the resulting graph is a tree of n nodes. If there are multiple answers, return the answer that occurs last in the input.

 Input: edges = [[1,2],[1,3],[2,3]]
Output: [2,3]

Input: edges = [[1,2],[2,3],[3,4],[1,4],[1,5]]
Output: [1,4]

Constraints:

n == edges.length
3 <= n <= 1000
edges[i].length == 2
1 <= ai < bi <= edges.length
ai != bi
There are no repeated edges.
The given graph is connected.

*/

class Solution {
    
    int[] parent;
    
    //Time O(n)
    // Space: O(n)
    public int[] findRedundantConnection(int[][] edges) {
        int n = edges.length;
        parent = new int[n + 1];
        
        //make each node the parent of itself
        for (int i = 0; i <= n; i++) {
            parent[i] = i;
        }
        
        for (int[] edge : edges) {
            if (find(edge[0]) == find(edge[1]))
                return edge;  // redundant
            
            union(edge[0], edge[1]);
            
        }
        
        return null;
    }
    
    int find(int node) {
        while(parent[node] != node) {
            node = parent[node];
        }
        
        return node;
    }
    
    void union(int i, int j) {
        int iRoot = find(i);
        int jRoot = find(j);
        
        if (iRoot != jRoot) {
            parent[jRoot] = iRoot;
        }
    }
}
