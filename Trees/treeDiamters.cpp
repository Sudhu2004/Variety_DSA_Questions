// https://cses.fi/problemset/task/1132/

#include<bits/stdc++.h>

using namespace std;

vector<int> depth(200001);
vector<int> ans(200001);
vector<int> adj[200001];


// This function will calculate the max depth leaf away from the node
void eval_depth(int node, int parent) {
    
    int curr_depth = 0;
    for(auto it: adj[node]) {
        if(it != parent) {
            eval_depth(it, node);
            curr_depth =  max(curr_depth, 1 + depth[it]);
        }
    }

    depth[node] = curr_depth;
}

// This will update the answer
void solve(int node, int parent, int temp_ans) {
    vector<int> prefix, suffix;

    for(auto it: adj[node]) {
        if(it != parent) {
            prefix.push_back(depth[it]);
            suffix.push_back(depth[it]);
        }
    }
    // The prefix and suffix arrays represents 
    // the maximum distance accross the all the edges from `node`

    int n = prefix.size();
    for(int i=1; i < n ;i++) {
        prefix[i] = max(prefix[i],  prefix[i-1]);
    }
    for(int i = n - 2; i>=0 ;i--) {
        suffix[i] = max(suffix[i], suffix[i+1]);
    }

    int c_no = 0;
    for(auto it: adj[node]) {
        if(it == parent) continue;

        int op1 = (c_no == 0)? INT_MIN: prefix[c_no-1];
        int op2 = (c_no == n - 1)? INT_MIN: suffix[c_no + 1];
        int parentSum = 1 + max(temp_ans, max(op1, op2));

        solve(it, node, parentSum);
        c_no++;
    }
    // the temp ans is maximum distance the parent has on its side
    ans[node] = 1 + max(temp_ans, prefix.empty()?-1: prefix.back());
}
int main() {
    int n;
    cin >> n;

    for(int i=0 ;i<n-1; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    eval_depth(1, 0);
    solve(1, 0, -1);

    for(int i=1; i<=n ;i++) {
        cout << ans[i] << " ";
    }
    return 0;
}