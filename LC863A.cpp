/*
To find all nodes at distance k from a target node value in a binary tree, we treat the tree as an undirected graph and perform a 
Breadth-First Search (BFS) starting from the target node*/


#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <vector>
using namespace std;

struct Node {
    int val;
    Node* left;
    Node* right;
    Node(int x) : val(x), left(nullptr), right(nullptr) {}
};

// Step 1: Build parent map and locate target node
void buildParentMap(Node* root, unordered_map<Node*, Node*>& parentMap, unordered_map<int, Node*>& valToNode) {
    queue<Node*> Q;
    Q.push(root);
    valToNode[root->val] = root;

    while (!Q.empty() ) {
        Node* curr = Q.front();
        Q.pop();

        for (Node* node : {curr->left, curr->right}) {
            if (node) {
                Q.push(node);
                parentsMap[node] = curr;
                valToNode[node->value] = node;
            }
        }
    }
}

// Step 2: BFS from target node to find all nodes at distance k
vector<int> nodesAtDistanceK(Node* root, int targetVal, int k) {
    unordered_map<Node*, Node*> parentMap;
    unordered_map<int, Node*> valToNode;
    buildParentMap(root, parentMap, valToNode);

    if (valToNode.find(targetVal) == valToNode.end()) return {};

    Node* target = valToNode[targetVal];
    unordered_set<Node*> visited;
    queue<Node*> q;
    q.push(target);
    visited.insert(target);

    int currLevel = 0;
    while (!q.empty()) {
        int size = q.size();
        if (currLevel == k) break;

        for (int i = 0; i < size; ++i) {
            Node* curr = q.front(); q.pop();

            for (Node* neighbor : {curr->left, curr->right, parentMap[curr]}) {
                if (neighbor && !visited.count(neighbor)) {
                    visited.insert(neighbor);
                    q.push(neighbor);
                }
            }
        }
        currLevel++;
    }

    vector<int> result;
    while (!q.empty()) {
        result.push_back(q.front()->val);
        q.pop();
    }
    return result;
}

// Sample usage
int main() {
    Node* root = new Node(3);
    root->left = new Node(5);
    root->right = new Node(1);
    root->left->left = new Node(6);
    root->left->right = new Node(2);
    root->right->left = new Node(0);
    root->right->right = new Node(8);
    root->left->right->left = new Node(7);
    root->left->right->right = new Node(4);

    int target = 5, k = 2;
    vector<int> result = nodesAtDistanceK(root, target, k);

    cout << "Nodes at distance " << k << " from " << target << ": ";
    for (int val : result) cout << val << " ";
    cout << endl;

    return 0;
}