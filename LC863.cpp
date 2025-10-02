/*
863. All Nodes Distance K in Binary Tree
Given the root of a binary tree, the value of a target node target, and an integer k, return an array of the values of all nodes that have a distance k from the target node.

You can return the answer in any order.

 Input: root = [3,5,1,6,2,0,8,null,null,7,4], target = 5, k = 2
Output: [7,4,1]
Explanation: The nodes that are a distance 2 from the target node (with value 5) have values 7, 4, and 1.

*/

// Program 1, neat code
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    Solution() {
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);
    }

    void markParents(TreeNode* root, unordered_map<TreeNode*, TreeNode*>& parents) {
        std::queue<TreeNode*> Q;
        Q.push(root);

        while(!Q.empty()) {

            TreeNode* current = Q.front();
            Q.pop();

            if (current->left) {
                parents[current->left] = current;
                Q.push(current->left);
            }

            if (current->right) {
                parents[current->right] = current;
                Q.push(current->right);
            }
        }
    }

    vector<int> distanceK(TreeNode* root, TreeNode* target, int k) {
        std::vector<int> result;
        std::unordered_map<TreeNode*, TreeNode*> parents;
        
        markParents(root, parents);
        std::unordered_set<TreeNode *> visited;
        std::queue<std::pair<TreeNode *, int>> Q;
        Q.push({target, 0});
        visited.insert(target);

        while(!Q.empty()) {
            TreeNode* node = Q.front().first;
            int dist = Q.front().second;
            Q.pop();

            if (dist == k) {
                result.push_back(node->val);
            }

            if (dist > k)
                break;

            for (TreeNode* neighbour : {node->left, node->right, parents[node]}) {
                if (neighbour && visited.find(neighbour) == visited.end()) {
                    visited.insert(neighbour);
                    Q.push({neighbour, dist + 1});
                }
            }
        }
        
        return result;

    }
};


// Helper to build sample tree and test
int main() {
    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(5);
    root->right = new TreeNode(1);
    root->left->left = new TreeNode(6);
    root->left->right = new TreeNode(2);
    root->right->left = new TreeNode(0);
    root->right->right = new TreeNode(8);
    root->left->right->left = new TreeNode(7);
    root->left->right->right = new TreeNode(4);

    TreeNode* target = root->left; // Node with value 5
    int k = 2;

    vector<int> res = distanceK(root, target, k);
    for (int val : res) cout << val << " ";
    cout << endl;

    return 0;
}



// Solution 2: in an another way

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
        
        // step2: find the distance using above parentsMap
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
