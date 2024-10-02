// https://codeforces.com/problemset/problem/461/B

#include<bits/stdc++.h>
#define ll long long

using namespace std;
vector<ll> adj[200001];
vector<ll> blackcolor(200001);
vector<ll> dp_white(200001), dp_black(200001);


int dfs(int node, int n) {
    int mod = 1000000007;

    // dp_black[node]: Number of ways to construct a tree rooted at `node` with `node` being black
    // dp_white[node]: Number of ways to construct a tree rooted at `node` with `node` being white

    if (blackcolor[node]) {
        dp_black[node] = 1;  // If the node is black, dp_black[node] starts with 1
    } else {
        dp_white[node] = 1;  // If the node is not black, dp_white[node] starts with 1
    }

    for (int child : adj[node]) {
        dfs(child, n);

        // Update dp_black[node] - considering the node is black
        dp_black[node] = ((dp_black[node] * dp_white[child]) % mod +   // node black, child white
                          (dp_black[node] * dp_black[child]) % mod +   // node black, child black
                          (dp_white[node] * dp_black[child]) % mod) % mod; // node white, child black

        // Update dp_white[node] - considering the node is white
        dp_white[node] = ((dp_white[node] * dp_black[child]) % mod +   // node white, child black
                          (dp_white[node] * dp_white[child]) % mod) % mod; // node white, child white
    }

    return dp_black[node];  // Return the number of ways with the root node being black
}


ll solve(ll n) {
    return dfs(0, -1);
}
int main() {
    ll n;
    cin >> n;

    for(int i=0; i<n-1; i++) {
        ll num;
        cin >> num;
        adj[num].push_back(i+1);
    }

    for(int i=0; i<n; i++) {
        ll num;
        cin >> num;
        blackcolor[i] = num;
    }

    cout << solve(n) << endl; 

    return 0;
}