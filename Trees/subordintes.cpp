#include <bits/stdc++.h>
using namespace std;

void dfs(int node, vector<vector<int>>& adj, vector<int>& subordinates) {

    for(auto it: adj[node]) {
        dfs(it, adj, subordinates);
        subordinates[node] += subordinates[it] + 1;
    }
}
vector<int> getSubs(vector<int>& arr, int n) {
    vector<vector<int>> adj(n+2);

    int k = 2;
    for(auto it: arr) {
        adj[it].push_back(k++);
    }

    vector<int> subordinates(n+1, 0);
    dfs(1, adj, subordinates);
    vector<int> res(subordinates.begin() + 1, subordinates.end());
    return res;
}

void print(vector<int>& arr) {
    for(auto it: arr) {
        cout << it << " ";
    }
    cout << endl;
}

int main() {
    int n;

    cin >> n;

    vector<int> arr;

    for(int i = 0; i < n - 1; i++) {
        int temp = 0;
        cin >> temp;
        arr.push_back(temp);
    }

    vector<int> res = getSubs(arr, n);

    print(res);

    return 0;
}
