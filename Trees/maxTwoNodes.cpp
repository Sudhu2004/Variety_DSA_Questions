// https://practice.geeksforgeeks.org/contest/gfg-weekly-170-rated-contest/problems

//{ Driver Code Starts
#include <bits/stdc++.h>
using namespace std;
  
class Matrix {
  public:
    template <class T>
    static void input(vector<vector<T>> &A, int n, int m) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                scanf("%d ", &A[i][j]);
            }
        }
    }

    template <class T>
    static void print(vector<vector<T>> &A) {
        for (int i = 0; i < A.size(); i++) {
            for (int j = 0; j < A[i].size(); j++) {
                cout << A[i][j] << " ";
            }
            cout << endl;
        }
    }
};

class Array {
  public:
    template <class T>
    static void input(vector<T> &A, int n) {
        for (int i = 0; i < n; i++) {
            scanf("%d ", &A[i]);
        }
    }

    template <class T>
    static void print(vector<T> &A) {
        for (int i = 0; i < A.size(); i++) {
            cout << A[i] << " ";
        }
        cout << endl;
    }
};


// } Driver Code Ends



// Euler Path:- An Euler Path is a path that goes through every edge of a graph
// exactly once

// An Euler circuit is an Euler path that begins and end at the same vertex

// Flattens the tree

class Solution {
  public:
    int timer = 0; 
    // The below will calculate the time for
    // which a node  was visited and left

    void dfs(int node, int parent,vector<int>& tin, vector<int>& tout, vector<int>& v, vector<int> adj[]) {
        
        tin[node] = ++timer;
        v.push_back(node);
        
        for(auto it: adj[node]) {
            if(it != parent)
                dfs(it, node, tin, tout, v, adj);
        }
        
        tout[node] = timer;
    }
    
    static bool comp(int val1, int val2) {
        return val1 > val2;
    }
    vector<vector<int>> twoMax(int n, int m, int rootServer, vector<vector<int>> &edges,
                               vector<int> &requests) {
        
        vector<int> adj[n+1];
        
        for(auto it: edges) {
            int u = it[0];
            int v = it[1];
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        
        vector<int> tin(n+1), tout(n+1);
        vector<int> aux(n+1);
        vector<int> v;
        
        dfs(rootServer, -1, tin, tout, v, adj);
        
        // the tin and tout provides the number the range of nodes
        // under the current node
        for(int i=1; i<=n ;i++) {
            aux[i] = v[i-1];
        }
        
        vector<pair<int,int>> prefix(n+2, {-1,-1});
        
        // the two large numbers prefix
        int f = -1, s = -1;
        // Prefix array construction
        for(int i = 1; i <= n; i++) {
            if(aux[i] > f) {
                s = f;
                f = aux[i];
            }
            else if(aux[i] > s) {
                s = aux[i];
            }
            prefix[i] = {f, s};
        }
        
        // Suffix array construction
        vector<pair<int,int>> suffix(n+2, {-1,-1});

        // the two large numbers suffix
        f = s = -1;
        for(int i = n; i >= 1; i--) {
            if(aux[i] > f) {
                s = f;
                f = aux[i];
            }
            else if(aux[i] > s) {
                s = aux[i];
            }
            suffix[i] = {f, s};
        }

        vector<vector<int>> ans;
        
        // based on tin and tout get the range and sort it
        // tin -1 => left side of the array
        // tout - 1 => rightside of the array

        for(auto val: requests) {
            int leftside = tin[val] - 1;
            int rightside = tout[val] + 1;
            vector<int> px;
            
            px.push_back(prefix[leftside].first);
            px.push_back(prefix[leftside].second);
            px.push_back(suffix[rightside].first);
            px.push_back(suffix[rightside].second);
            sort(px.begin(), px.end(), comp);
            
            ans.push_back({px[0], px[1]});
        }
        
        return ans;
    }
};


//{ Driver Code Starts.

int main() {
    int t;
    scanf("%d ", &t);
    while (t--) {

        int n;
        scanf("%d", &n);

        int m;
        scanf("%d", &m);

        int rootServer;
        scanf("%d", &rootServer);

        vector<vector<int>> adj(n - 1, vector<int>(2));
        Matrix::input(adj, n - 1, 2);

        vector<int> requests(m);
        Array::input(requests, m);

        Solution obj;
        vector<vector<int>> res = obj.twoMax(n, m, rootServer, adj, requests);

        Matrix::print(res);
    }
}

// } Driver Code Ends