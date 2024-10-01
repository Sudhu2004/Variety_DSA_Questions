#include<bits/stdc++.h>

using namespace std;

vector<int> adj[200001];
vector<vector<int>> dp(200001, vector<int>(21, -1));
vector<int> lvl(200001);

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

    for(int i=1; i<20; i++) {
        if(dp[node][i-1] != -1) {
            dp[node][i] = dp[dp[node][i-1]][i-1];
        }
        else {
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

    for(int i=19; i>=0; i--) {
        if(node == -1 || reqJumps == 0) 
            break;

        if(reqJumps >= (1<<i)) {
            reqJumps -= (1<<i);
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

    if( u == v) return u;
    
    for(int i=19; i>=0 ;i--) {
        if(dp[u][i] != dp[v][i]) {
            u = dp[u][i];
            v = dp[v][i];
        }
    }

    return jumps(v, 1);
}
void solve(int n, vector<vector<int>>& queries) {
    dfs(1, -1);
    lvls(1, -1, 0);
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