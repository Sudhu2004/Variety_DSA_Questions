// https://cses.fi/problemset/task/1688
#include<bits/stdc++.h>

using namespace std;
vector<int> adj[200001];
vector<vector<int>> dp(200001, vector<int>(21, -1));
vector<int> lvl(200001);

void markLevels(int node, int parent,int level) {
    lvl[node] = level;
    for(auto it: adj[node]) {
        if(it != parent) {
            markLevels(it, node, level + 1);
        }
    }
}

void dfs(int node, int parent) {
    dp[node][0] = parent;

    // always starts from 1 because 
    // need to check weather there are any nodes beyond parent
    for(int i=1; i<20; i++) {
        if(dp[node][i-1] != -1) {
            dp[node][i] = dp[dp[node][i-1]][i-1];
        }
        else {
            dp[node][i] = -1;
        }
    }
    
    for(auto it: adj[node]) {
        if(it != parent) dfs(it, node);
    }
}

int jumps(int node, int reqjumps) {
    
    // recursive
    for(int i=19;i>=0 ;i--) {
        if(node == -1 || reqjumps == 0) break;

        if(reqjumps >= (1<<i)) {
            reqjumps -= (1<<i);
            node = dp[node][i];
        }
    }
    return node;
}


// LOG^2(N) 
int LCA(int u, int v) {

    // making sure that u'th level is greater than v
    if(lvl[u] < lvl[v]) {
        swap(u, v);
    }

    u = jumps(u, lvl[u] - lvl[v]);

    int low = 0, high = lvl[u];

    // always != because at some point they become equal
    while(low < high) {
        int mid = (low + high)/2;
        int x1 = jumps(u, mid);
        int x2 = jumps(v, mid);

        if(x1 == x2) {
            high = mid;
        }
        else {
            low = mid + 1;
        }
    } 
    // if in case low is actually 0, than `u` is the node LCA 
    // and alsop making jump for others
    return jumps(u, low);
}

void solve(int n, vector<vector<int>>& queries) {
    markLevels(1, -1, 0);
    dfs(1, -1);

    for(auto it: queries) {
        int u = it[0];
        int v = it[1];
        cout << LCA(u, v) << endl;
    }
}
int main() {
    int n, q;
    vector<vector<int>> queries;
    cin >> n >> q;
    int j = 2;
    for(int i=0; i<n-1; i++) {
        int temp;
        cin >> temp;
        adj[j].push_back(temp);
        adj[temp].push_back(j);
        j++;
    }

    for(int i=0 ;i<q; i++) {
        int x, y;
        cin >> x >> y;
        queries.push_back({x, y});
    }
    solve(n, queries);

    return 0;
}