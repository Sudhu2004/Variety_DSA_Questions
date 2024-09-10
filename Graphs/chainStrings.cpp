//{ Driver Code Starts
// Initial Template for C++

#include <bits/stdc++.h>
using namespace std;


// } Driver Code Ends
// User function Template for C++

class DisjointSet {
    
    vector<int> parent, size;
public:
    DisjointSet(int n) {
        parent.resize(n + 1);
        size.resize(n + 1);
        for(int i=0 ;i<=n ;i++) {
            parent[i] = i;
            size[i] = 1;
        }
    }
    
    int findP(int node) {
        if(parent[node] != node)
            return parent[node] = findP(parent[node]);
            
        return parent[node];
    }
    
    void UnionBySize(int u, int v) {
        int ulp_u = findP(u);
        int ulp_v = findP(v);
        
        if(ulp_v == ulp_u) {
            return ;
        }
        
        if(size[ulp_v] >= size[ulp_u]) {
            parent[ulp_u] = ulp_v;
            size[ulp_v] += size[ulp_u];
        }
        else {
            parent[ulp_v] = ulp_u;
            size[ulp_u] += size[ulp_v];
        }
    }
};

class Solution {
  public:
    int isCircle(vector<string> &arr) {
        int n = arr.size();
        vector<int> indegree(26, 0), outdegree(26, 0);
        unordered_map<int,int> seen;
        
        DisjointSet ds(26);
        for(auto it: arr) {
            int size = it.size();
            int u = it[0] - 'a';
            int v = it[size - 1] - 'a';
            
            
            ds.UnionBySize(u, v);
            indegree[u]++;
            outdegree[v]++;
            seen[u] = seen[v] = 1;
        }
        
        int root = -1;
        for(auto it: seen) {
            int vertex = it.first;
            
            if(root == -1) {
                root = ds.findP(vertex);
            }
            else if(ds.findP(vertex) != root) return 0;
            
            if(indegree[vertex] != outdegree[vertex]) return 0;
        }
        return 1;
    }
};


//{ Driver Code Starts.
int main() {
    int t;
    cin >> t;
    while (t--) {
        int N;
        cin >> N;
        vector<string> A;
        string s;

        for (int i = 0; i < N; i++) {
            cin >> s;
            A.push_back(s);
        }

        Solution ob;
        cout << ob.isCircle(A) << endl;
    }
    return 0;
}
// } Driver Code Ends