#include <iostream>
#include <vector>
using namespace std;

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

// Solution class containing the splitListToParts function
class Solution {
public:
    vector<ListNode*> splitListToParts(ListNode* head, int k) {
        vector<ListNode*> ans(k);

        int size = 0;
        ListNode* curr = head;
        while(curr) {
            size++;
            curr = curr->next;
        }

        int parts = size / k;
        int remParts = size % k;
        curr = head;
        ListNode* prev = curr;

        for(int i = 0; i < k; i++) {
            ListNode* newPart = curr;

            int currsize = parts;
            if(remParts > 0) {
                remParts--;
                currsize++;
            }

            int j = 0;
            while(j < currsize) {
                prev = curr;
                if(curr != nullptr) {
                    curr = curr->next;
                }
                j++;
            }

            if(prev != nullptr) {
                prev->next = nullptr;
            }

            ans[i] = newPart;
        }

        return ans;
    }
};

// Helper function to create a linked list from a vector of values
ListNode* createLinkedList(const vector<int>& values) {
    if (values.empty()) return nullptr;
    ListNode* head = new ListNode(values[0]);
    ListNode* curr = head;
    for (int i = 1; i < values.size(); i++) {
        curr->next = new ListNode(values[i]);
        curr = curr->next;
    }
    return head;
}

// Helper function to print the linked list
void printList(ListNode* head) {
    if (!head) {
        cout << "nullptr";
    }
    while (head) {
        cout << head->val << " ";
        head = head->next;
    }
    cout << endl;
}

int main() {
    Solution sol;

    // Create a linked list with values from 1 to 10
    vector<int> values = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    ListNode* head = createLinkedList(values);

    // Number of parts to split into
    int k = 3;

    // Call the splitListToParts function
    vector<ListNode*> parts = sol.splitListToParts(head, k);

    // Print each part
    for (int i = 0; i < k; i++) {
        cout << "Part " << i + 1 << ": ";
        printList(parts[i]);
    }

    return 0;
}
    