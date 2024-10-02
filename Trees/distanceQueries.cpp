// https://cses.fi/problemset/result/10685441/
#include<bits/stdc++.h>
#define IOS ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);

using namespace std;

vector<int> adj[200005];
int dp[200005][21];
vector<int> lvl(200005);

void lvls(int node, int parent, int level) {
    lvl[node] = level;
    for(auto it: adj[node]) {
        if(it != parent) {
            lvls(it, node, level + 1);
        }
    }
}

void dfs(int node, int parent) {
    dp[node][0] = parent;

    for(int i = 1; i < 20; i++) {
        if(dp[node][i-1] != -1) {
            dp[node][i] = dp[dp[node][i-1]][i-1];
        } else {
            dp[node][i] = -1;
        }
    }

    for(auto it: adj[node]) {
        if(it != parent) {
            dfs(it, node);
        }
    }
}

int jumps(int node, int reqJumps) {
    for(int i = 19; i >= 0; i--) {
        if(node == -1 || reqJumps == 0) 
            break;

        if(reqJumps >= (1 << i)) {
            reqJumps -= (1 << i);
            node = dp[node][i];
        }
    }
    return node;
}

int LCA(int u, int v) {
    if(lvl[u] < lvl[v]) {
        swap(u, v);
    }

    u = jumps(u, lvl[u] - lvl[v]);

    if(u == v) return u;
    
    for(int i = 19; i >= 0; i--) {
        if(dp[u][i] != dp[v][i]) {
            u = dp[u][i];
            v = dp[v][i];
        }
    }

    return jumps(v, 1);
}

void solve(int n, vector<vector<int>>& queries) {
    lvls(1, -1, 0);
    dfs(1, -1);

    for(auto it: queries) {
        int u = it[0];
        int v = it[1];
        int x = LCA(u, v);
        int ans = (lvl[u] - lvl[x]) + (lvl[v] - lvl[x]);
        cout << ans << endl;
    }
}

int main() {
    IOS;
    
    int n, q;
    cin >> n >> q;

    for(int i = 0; i < n-1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<vector<int>> queries(q, vector<int>(2));
    for(int i = 0; i < q; i++) {
        cin >> queries[i][0] >> queries[i][1];
    }

    solve(n, queries);

    return 0;
}
