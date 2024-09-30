// https://codeforces.com/contest/161/problem/D

#include<bits/stdc++.h>

using namespace std;

vector<int> adj[50001];
vector<vector<int>> dp1(50001, vector<int>(501));
vector<vector<int>> dp2(50001, vector<int>(501));


// This function will calculate the the number of nodes
// at a distance `dis` under the node including the ndoe

void dfs(int node, int parent,int& k) {

    for(auto it: adj[node]) {
        if(it != parent) {
            dfs(it, node, k);
        }
    }

    dp1[node][0] = 1;

    for(int dis = 1; dis <= k; dis++) {
        dp1[node][dis] = 0;
        for(auto it: adj[node]) {
            if(it != parent) {
                dp1[node][dis] += dp1[it][dis - 1];
            }
        }
    }
}


// This will update the dp2 with dp1 so that 
// the parent's distance apart from the nodes are also calculated
void solve(int node, int parent,int& k) {
    for(int dis = 0; dis <= k ;dis++) {
        dp2[node][dis] = dp1[node][dis];
    }

    if(parent != 0) {
        // since parent is the only node at distance 1
        dp2[node][1] += dp2[parent][0];

        // formula = dp2[node][dis] = dp2[parent][dis - 1] - dp1[node][dis - 2];
        for(int dis = 2; dis <=k ;dis++) {
            dp2[node][dis] += dp2[parent][dis - 1];
            dp2[node][dis] -= dp1[node][dis - 2];
        }
    }

    for(auto it: adj[node]) {
        if(it != parent) {
            solve(it, node, k);
        }
    }
}

int main() {
    int n, k;
    cin >> n >> k;

    for(int i=0 ;i<n-1; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    // updates dp1
    dfs(1, 0, k);

    // updates dp2
    solve(1, 0, k);
    long long sum = 0LL;
    for(int i=1; i<=n ;i++) {
        sum += dp2[i][k];
    }

    cout << sum/2LL << endl;

    return 0;
}