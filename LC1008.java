/*
1008. Construct Binary Search Tree from Preorder Traversal
Return the root node of a binary search tree that matches the given preorder traversal.

(Recall that a binary search tree is a binary tree where for every node, 
any descendant of node.left has a value < node.val, and any descendant of node.right has a value > node.val.  
Also recall that a preorder traversal displays the value of the node first, then traverses node.left, then traverses node.right.)

It's guaranteed that for the given test cases there is always possible to find a binary search tree with the given requirements.

Example 1:

Input: [8,5,1,7,10,12]
Output: [8,5,10,1,7,null,12]

*/

/**
 * Definition for a binary tree node.
 * public class TreeNode {
 *     int val;
 *     TreeNode left;
 *     TreeNode right;
 *     TreeNode(int x) { val = x; }
 * }
 */
 
class Solution {
    
    TreeNode createNode(int val)
    {
        TreeNode node = new TreeNode(val);
        node.left = null;
        node.right = null;
        return node;
    }
    
    int create_bst(int[] preorder, int n, int pos, TreeNode curr_node, int left, int right)
    {
        if (pos == n || preorder[pos] < left || preorder[pos] > right)
        {
            return pos;
        }

        if (preorder[pos] < curr_node.val)
        {
            curr_node.left = createNode(preorder[pos]);
            ++pos;
            pos = create_bst(preorder, n, pos, curr_node.left, left, curr_node.val - 1);
        }

        if (pos == n || preorder[pos] < left || preorder[pos] > right)
        {
            return pos;
        }


        curr_node.right = createNode(preorder[pos]);
        ++pos;
        pos = create_bst(preorder, n, pos, curr_node.right, curr_node.val + 1, right);

        return pos;
    }
    
    public TreeNode bstFromPreorder(int[] preorder) {
         int totalElem = preorder.length;

        if (totalElem == 0)
        {
            return null;
        }

        TreeNode root = createNode(preorder[0]);

        if (totalElem == 1)
            return root;

        create_bst(preorder, totalElem, 1, root, Integer.MIN_VALUE, Integer.MAX_VALUE);

        return root;
    }
}
