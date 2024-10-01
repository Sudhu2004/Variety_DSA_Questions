// brute force approach is to use dp[nodes..][maxdist...]
// but the above exceeds memory

#include<bits/stdc++.h>

using namespace std;

vector<int> adj[200001];
vector<vector<int>> dp(200001, vector<int>(20, -1));

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

int jumps(int node, int jumpreq) { 
    if(node == -1 || jumpreq == 0) {
        return node;
    }

    for(int i=19; i>=0 ;i--) {
        if(jumpreq >= (1 << i)) {
            return jumps(dp[node][i], jumpreq - (1 << i));
        }
    }
}
void solve(int n,vector<vector<int>>& queries) {
    
    dfs(1, -1);
    for(auto it: queries) {
        int node = it[0];
        int dis = it[1];
        cout << jumps(node, dis) << endl;
    }
}
int main() {
    int n, q;
    cin >> n >> q;
    int j = 2;

    vector<vector<int>> queries;

    for(int i=0 ;i<n-1 ;i++) {
        int num;
        cin >> num;
        adj[j].push_back(num);
        adj[num].push_back(j);
        j++;
    }

    int maxdepth = INT_MIN;
    for(int i=0; i<q; i++) {
        int x, k;
        cin >> x >> k;
        queries.push_back({x , k});
    }
    
    solve(n, queries);

    return 0;
}