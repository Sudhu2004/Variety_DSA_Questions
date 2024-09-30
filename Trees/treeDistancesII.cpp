// https://cses.fi/problemset/task/1133
#include<bits/stdc++.h>
#define ll long long
using namespace std;


vector<ll> adj[200001];
vector<ll> nodes(200001);
vector<ll> sums(200001);
vector<ll> ans(200001);

void getNodes(ll node, ll parent) {

    ll total = 0;
    ll totalSum = 0;
    for(auto it: adj[node]) {
        if(it != parent) {
            getNodes(it, node);
            total += nodes[it];
            totalSum += (sums[it] + nodes[it]);

        }
    }
    nodes[node] = 1 + total;
    sums[node] = totalSum;
}

void solve(ll node, ll parent, ll par_ans, ll& totalSize) {
    ans[node] = sums[node] + (par_ans + (totalSize - nodes[node]));

    for(auto it: adj[node]) {
        if(it != parent) {
            solve(it, node, ans[node] - (sums[it] + nodes[it]), totalSize);
        }
    }
}
int main() {
    ll n;
    cin >> n;

    for(int i=0; i<n-1; i++) {
        ll a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    getNodes(1, -1);
    solve(1, -1, 0, n);
    
    for(int i=1; i<=n ;i++) {
        cout << ans[i] << " ";
    }
    cout << endl;
    
    return 0;
}