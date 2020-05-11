/*
94. Binary Tree Inorder Traversal
Given a binary tree, return the inorder traversal of its nodes' values.

Example:

Input: [1,null,2,3]
   1
    \
     2
    /
   3

Output: [1,3,2]
*/

//Approach 1: 'recursive'
class Solution 
{
    public List < Integer > inorderTraversal(TreeNode root) 
    {
        List < Integer > res = new ArrayList < > ();
        recursive(root, res);
        return res;
    }

    public void recursive(TreeNode root, List < Integer > res) {
        if (root != null) 
        {
            if (root.left != null) {
                recursive(root.left, res);
            }
            res.add(root.val);
            if (root.right != null) {
                recursive(root.right, res);
            }
        }
    }
}

//Approach 2: 'Iterating using stack'

public class Solution 
{
    public List < Integer > inorderTraversal(TreeNode root) 
    {
        List < Integer > res = new ArrayList < > ();
        Stack < TreeNode > stack = new Stack < > ();
        TreeNode curr = root;
        
        while (curr != null || !stack.isEmpty()) 
        {
            while (curr != null) {
                stack.push(curr);
                curr = curr.left;
            }
            curr = stack.pop();
            res.add(curr.val);
            curr = curr.right;
        }
        return res;
    }
}

//Approach 3: Morris Traversal
//In this method, we have to use a new data structure-Threaded Binary Tree

class Solution 
{
    public List < Integer > inorderTraversal(TreeNode root) 
    {
        List < Integer > res = new ArrayList < > ();
        TreeNode curr = root;
        TreeNode pre;
        
        while (curr != null) 
        {
            if (curr.left == null) {
                res.add(curr.val);
                curr = curr.right; // move to next right node
            } 
            else { // has a left subtree
                pre = curr.left;
                
                while (pre.right != null) { // find rightmost
                    pre = pre.right;
                }
                
                pre.right = curr; // put cur after the pre node
                TreeNode temp = curr; // store cur node
                curr = curr.left; // move cur to the top of the new tree
                temp.left = null; // original cur left be null, avoid infinite loops
            }
        }
        return res;
    }
}
