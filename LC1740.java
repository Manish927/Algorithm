/*
1740. Find Distance in a Binary Tree
Given the root of a binary tree and two integers p and q, return the distance between the nodes of value p and value q in the tree.

The distance between two nodes is the number of edges on the path from one to the other.

Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 0
Output: 3
Explanation: There are 3 edges between 5 and 0: 5-3-1-0.

Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 7
Output: 2
Explanation: There are 2 edges between 5 and 7: 5-2-7.

Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 5
Output: 0
Explanation: The distance between a node and itself is 0.

*/

class Solution {
  public int bstDistance(TreeNode root, int node1, int node2) {
      if (root == null) return -1;
      TreeNode lca = lca(root, node1, node2);
      return getDistance(lca, node1) + getDistance(lca, node2);
  }

  private int getDistance(TreeNode src, int dest) {
      if (src.val == dest) return 0;
      TreeNode node = src.left;
      if (src.val < dest) {
          node = src.right;
      }
      return 1 + getDistance(node, dest);
  }

  private TreeNode lca(TreeNode root, int node1, int node2) {
      while (true) {
          if (root.val > node1 && root.val > node2) {
              root = root.left;
          } else if (root.val < node1 && root.val < node2) {
              root = root.right;
          } else {
              return root;
          }
      }
  }
}
