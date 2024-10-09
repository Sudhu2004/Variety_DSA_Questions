// https://leetcode.com/problems/construct-2d-grid-matching-graph-layout/description/

#include<bits/stdc++.h>

using namespace std;

void print(vector<vector<int>>& mat) {
    int m = mat.size();
    int n = mat[0].size();

    for(int i=0; i<m ;i++) {
        for(int j=0; j<n; j++) {
            cout << mat[i][j] << " ";
        }
        cout << endl;
    }
}


class Solution {
public:
    vector<int> bfs(int src, int dest, int n, vector<int> adj[]) {
        vector<int> dist(n, -1), from(n, -1);
        queue<int> q;
        q.push(src);
        dist[src] = 0;
        while(!q.empty()) {
            int u = q.front();
            q.pop();

            for(auto v: adj[u]) {
               if(dist[v] == -1) {
                    dist[v] = dist[u] + 1;
                    from[v] = u;
                    q.push(v);
               }
            }
        }

        return from;
    }
    vector<int> getPath(int src, int dest,int n, vector<int> adj[]) {
        vector<int> from = bfs(src, dest, n, adj), path;
        int node = dest;
        while(node != -1) {
            path.push_back(node);
            node = from[node];
        }
        reverse(path.begin(), path.end());
        return path;
    }

    vector<vector<int>> handle1Dim(int n, vector<int> adj[]) {
        int src = -1, dest = -1;
        for(int i=0; i<n ;i++) {
            if(adj[i].size() > 1) continue;
            if(src == -1) src = i;
            else if(dest == -1) dest = i;
        }
        if(dest == -1) return {};
        vector<int> path = getPath(src, dest, n, adj);
        return {path};
    }

    
    vector<vector<int>> constructGridLayout(int n, vector<vector<int>>& edges) {
        if(edges.size() == 1) return edges;

        vector<int> adj[n];
        for(auto it: edges) {
            int u = it[0];
            int v = it[1];
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        
        vector<vector<int>> ans = handle1Dim(n, adj);
        if(!ans.empty()) return ans;

        vector<int> corners;
        for(int i=0; i<n ;i++) {
            if(adj[i].size() > 2) continue;
            corners.push_back(i);
        }

        vector<int> pathSizes = {
            static_cast<int>(getPath(corners[0], corners[1], n, adj).size()),
            static_cast<int>(getPath(corners[0], corners[2], n, adj).size()),
            static_cast<int>(getPath(corners[0], corners[3], n, adj).size()),
        };

        int minInd = min_element(pathSizes.begin(), pathSizes.end()) - pathSizes.begin();
        int cols = pathSizes[minInd];
        int rows = n/cols;

        ans = vector<vector<int>>(rows, vector<int>(cols, -1));
        ans[0] = getPath(corners[0], corners[minInd+1], n, adj);

        for(int r =0 ; r < rows - 1; r++) {
            for(int c = 0; c < cols; c++) {
                set<int> neighbors;
                if(r > 0) neighbors.insert(ans[r-1][c]);
                if(c > 0) neighbors.insert(ans[r][c-1]);
                if(c + 1 < cols) neighbors.insert(ans[r][c+1]);

                int u = ans[r][c];
                for(int v: adj[u]) {
                    if(!neighbors.count(v)) {
                        ans[r+1][c] = v;
                        break;
                    }
                }
            }
        }

        return ans;
    }
};

int main() {
    int n;
    cin >> n;
    vector<vector<int>> edges;

    for(int i=0; i<n ;i++) {
        int u, v;
        cin >> u >>v;
        edges.push_back({u, v});
    }

    Solution obj;

    vector<vector<int>> ans = obj.constructGridLayout(n, edges);
    print(ans); 
    return 0;
}