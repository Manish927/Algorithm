/*
297. Serialize and Deserialize Binary Tree

Serialization is the process of converting a data structure or object into a sequence of bits so 
that it can be stored in a file or memory buffer, or transmitted across a network connection link 
to be reconstructed later in the same or another computer environment.

Design an algorithm to serialize and deserialize a binary tree. 
There is no restriction on how your serialization/deserialization algorithm should work. 
You just need to ensure that a binary tree can be serialized to a string and this string can be 
deserialized to the original tree structure.

Example: 

You may serialize the following tree:

    1
   / \
  2   3
     / \
    4   5

as "[1,2,3,null,null,4,5]"
Clarification: The above format is the same as how LeetCode serializes a binary tree. 
You do not necessarily need to follow this format, so please be creative and come up with different approaches yourself.

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Codec {
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) 
    {
        std::queue<TreeNode*> Q;
        
        Q.push(root);
        std::string serialized;
        
        while (!Q.empty())
        {
            TreeNode* top = Q.front();
            
            if (top == NULL)
            {
                serialized.append("NULL ");
                Q.pop();
            }
            else
            {
                serialized.append(std::to_string(top->val) + " ");
                Q.pop();
                Q.push(top->left);
                Q.push(top->right);
            }
        }
        
        serialized.pop_back();
        return serialized;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) 
    {
        std::vector<std::string> nodes;
        std::queue<TreeNode* > Q;
        int i = 1;
        
        std::istringstream ss(data);
        
        while(ss)
        {
            std::string node;
            ss >> node;
            nodes.push_back(node);
        }
        
        if (nodes.front() == "NULL")
            return NULL;
        
        TreeNode* node = new TreeNode(std::stoi(nodes.front()));
        Q.push(node);
        
        while (!Q.empty() && i < nodes.size())
        {
            TreeNode* next = Q.front();
            Q.pop();
            
            if (nodes[i] == "NULL")
                next->left = NULL;
            else
            {
                next->left = new TreeNode(std::stoi(nodes[i]));
                Q.push(next->left);
            }
            
            i++;
            
            if (nodes[i] == "NULL")
                next->right = NULL;
            else
            {
                next->right = new TreeNode(stoi(nodes[i]));
                Q.push(next->right);
            }
            
            i++;
        }
        
        return node;
    }
};

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.deserialize(codec.serialize(root));
