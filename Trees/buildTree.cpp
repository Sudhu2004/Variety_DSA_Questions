#include<bits/stdc++.h>

using namespace std;

class Node {
public:
    int data;
    Node* left;
    Node* right;

    Node(int val) {
        data = val;
        left = right = nullptr;
    }
};

Node* buildTreeBFS(vector<int>& arr, int n) {
    if(n == 0) return NULL;

    queue<Node*> q;
    int i = 0;
    Node* root = new Node(arr[i++]);
    q.push(root);
    

    while(i < n) {
        Node* curr = q.front();
        q.pop();

        if(i < n) {
            curr->left = new Node(arr[i++]);
            q.push(curr->left);
        }
        if(i < n) {
            curr->right = new Node(arr[i++]);
            q.push(curr->right);
        }
    }
    return root;
}

Node* buildTreeDFS(vector<int>& arr, int i, int n) {
    if(i >= n) return NULL;

    Node* root = new Node(arr[i]);

    root->left = buildTreeDFS(arr, 2*i + 1, n);
    root->right = buildTreeDFS(arr, 2*i + 2, n);

    return root;
}
void printInOrder(Node* root) {
    if(!root) return;

    cout << root->data << " ";
    printInOrder(root->left);
    printInOrder(root->right);
}
int main() {
    int n;
    cin >> n;
    vector<int> arr(n);
    
    for(int i=0 ;i<n ;i++) {
        cin >> arr[i];
    }

    // Node* root = buildTreeBFS(arr, n);
    Node* root = buildTreeDFS(arr, 0, n);
    printInOrder(root);

    return 0;
}