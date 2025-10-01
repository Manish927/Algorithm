/*
863. All Nodes Distance K in Binary Tree
Given the root of a binary tree, the value of a target node target, and an integer k, return an array of the values of all nodes that have a distance k from the target node.

You can return the answer in any order.

 Input: root = [3,5,1,6,2,0,8,null,null,7,4], target = 5, k = 2
Output: [7,4,1]
Explanation: The nodes that are a distance 2 from the target node (with value 5) have values 7, 4, and 1.

*/

class Solution {
public:
    Solution() {
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);
    }

    vector<int> distanceK(TreeNode* root, TreeNode* target, int k) {
        std::unordered_map<TreeNode*, TreeNode*> parentsMap;
        std::queue<TreeNode*> Q;
        Q.push(root);
        std::unordered_map<TreeNode*, int> seen;
        int distance = 0;

        //Step1: Build the parents map using Breadth First Search
        while (!Q.empty()) {
			int sz = Q.size();
			for (int i=0; i < sz; ++i)
			{
				TreeNode* current = Q.front();
				Q.pop();

				if (current->left != nullptr) {
					Q.push(current->left);
					parentsMap[current->left] = current;
				}
				if (current->right != nullptr) {
					Q.push(current->right);
					parentsMap[current->right] = current;
				}
			}
        }

        Q.push(target);
        seen[target] = 1;

        while (!Q.empty() && distance < k) {
			int sz = Q.size();
            distance++;
            
			for (int i = 0; i < sz; ++i) {
				TreeNode* current = Q.front();
				Q.pop();

				if (current->left != nullptr && seen.find(current->left) == seen.end()) {
					Q.push(current->left);
					seen[current->left] = 1;
				}
				if (current->right != nullptr && seen.find(current->right) == seen.end()) {
					Q.push(current->right);
					seen[current->right] = 1;
				}

				if (parentsMap.find(current) != parentsMap.end() && seen.find(parentsMap[current]) == seen.end()) {
					Q.push(parentsMap[current]);
					seen[parentsMap[current]] = 1;
				}
			}
        }

        std::vector<int> result;
        while(!Q.empty()) {
            TreeNode* node = Q.front();
            Q.pop();
            result.push_back(node->val);
        }

        return result;
    }
}