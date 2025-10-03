/*
82. Remove Duplicates from Sorted List II
Given the head of a sorted linked list, delete all nodes that have duplicate numbers, leaving only distinct numbers from the original list. Return the linked list sorted as well.

Input: head = [1,2,3,3,4,4,5]
Output: [1,2,5]

Input: head = [1,1,1,2,3]
Output: [2,3]

*/

#include <iostream>
using namespace std;

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        ListNode dummy(0);
        dummy.next = head;
        ListNode* prev = &dummy;

        while (head && head->next) {
            // Check if it's the start of duplicates
            if (head->val == head->next->val) {
                // Skip all nodes with current value
                while (head->next && head->val == head->next->val) {
                    head = head->next;
                }
                // Remove all duplicates
                prev->next = head->next;
            } else {
                // Move prev if current node is unique
                prev = prev->next;
            }
            head = head->next;
        }
        return dummy.next;
    }
};

// Helper function to print linked list
void printList(ListNode* node) {
    while (node) {
        cout << node->val << " ";
        node = node->next;
    }
    cout << endl;
}

int main() {
    // Example: 1 -> 2 -> 3 -> 3 -> 4 -> 4 -> 5
    ListNode* head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(3);
    head->next->next->next = new ListNode(3);
    head->next->next->next->next = new ListNode(4);
    head->next->next->next->next->next = new ListNode(4);
    head->next->next->next->next->next->next = new ListNode(5);

    cout << "Original list: ";
    printList(head);

    Solution sol;
    ListNode* result = sol.deleteDuplicates(head);

    cout << "List after removing duplicates: ";
    printList(result);

    return 0;
}