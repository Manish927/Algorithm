/*
993. Cousins in Binary Tree

In a binary tree, the root node is at depth 0, and children of each depth k node are at depth k+1.

Two nodes of a binary tree are cousins if they have the same depth, but have different parents.

We are given the root of a binary tree with unique values, and the values x and y of two different nodes in the tree.

Return true if and only if the nodes corresponding to the values x and y are cousins.

 

Example 1:

Input: root = [1,2,3,4], x = 4, y = 3
Output: false
Example 2:

Input: root = [1,2,3,null,4,null,5], x = 5, y = 4
Output: true
Example 3:

Input: root = [1,2,3,null,4], x = 2, y = 3
Output: false
*/

/**
 * Definition for a binary tree node.
 * public class TreeNode {
 *     int val;
 *     TreeNode left;
 *     TreeNode right;
 *     TreeNode() {}
 *     TreeNode(int val) { this.val = val; }
 *     TreeNode(int val, TreeNode left, TreeNode right) {
 *         this.val = val;
 *         this.left = left;
 *         this.right = right;
 *     }
 * }
 */
class Solution 
{
    TreeNode xParent = null;
    TreeNode yParent = null;
    int xDepth = -1;
    int yDepth = -1;
    
    public boolean isCousins(TreeNode root, int x, int y) {
        findDepthAndParent(root, x, y, 0, null);
        return xDepth == yDepth && xParent != yParent;
    }
    
    public void findDepthAndParent(TreeNode root, int x, int y, int depth, TreeNode parent)
    {
        if (root == null)
            return ;
        
        if (root.val == x)
        {
            xParent = parent;
            xDepth = depth;
        }
        else if (root.val == y)
        {
            yParent = parent;
            yDepth = depth;
        }
        else
        {
            findDepthAndParent(root.left, x, y, depth + 1, root);
            findDepthAndParent(root.right, x, y, depth + 1, root);
        }
    }
}
