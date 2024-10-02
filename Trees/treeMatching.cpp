// https://cses.fi/problemset/task/1130/
#include<bits/stdc++.h>

using namespace std;

void solve(int node, int parent,vector<int> adj[], vector<vector<int>>& dp) {
    vector<int> prefix, suffix;
    dp[node][0] = dp[node][1] = 0;
    bool leaf = true;

    for(auto it: adj[node]) {
        if(it != parent) {
            leaf = false;
            solve(it, node, adj, dp); // at start go to all nodes until child
        }
    }

    // if leaf is met then return
    if(leaf) return;

    // the below code first executes from the nearest child node from the root;
    
    // the below shows all max( possible values of it being picked or not)
    for(auto it: adj[node]) {
        if(it != parent) {
            prefix.push_back(max(dp[it][0], dp[it][1]));
        }
    }
    suffix = prefix;
    for(int i=1; i<=prefix.size() ;i++) {
        prefix[i] += prefix[i-1];
    }
    for(int i = suffix.size() - 2; i >=0 ;i--) {
        suffix[i] += suffix[i + 1];
    }

    int c_no = 0;
    dp[node][0] = suffix[0]; // if the curr node is not picked
    for(auto it: adj[node]) {
        if(it == parent) continue;

        int leftside = (c_no == 0)? 0: prefix[c_no - 1];
        int rightside = (c_no == (suffix.size() - 1))? 0: suffix[c_no + 1];
        // leftnodesmax + curr_node + rightnodemax
        dp[node][1] = max(dp[node][1], 1 + leftside + rightside + dp[it][0]);
        c_no++;
    }
}
int getSets(int n, vector<vector<int>>& edges) {
    vector<int> adj[n+1];
    for(auto it: edges) {
        int u = it[0];
        int v = it[1];
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<int> vis(n + 1, 0);
    int u = edges[0][0], v = edges[0][1];

    vector<vector<int>> dp(n+1, vector<int>(2));
    // Apart from parent of `node`
    // dp[node][1] -> that an edges is picked involing node in it
    // dp[node][0] -> that any edge is not picked involving node in it 
    solve(1, 0, adj, dp);
    return max(dp[1][0], dp[1][1]); // usually 1 is considered starting
}
int main() {
    int n;
    cin >> n;
    vector<vector<int>> edges;

    for(int i=0 ;i<n-1; i++) {
        int a, b;
        cin >> a >> b;
        edges.push_back({a, b});
    }

    
    cout << getSets(n, edges) << endl;
    return 0;
}