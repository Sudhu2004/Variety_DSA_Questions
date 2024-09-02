//{ Driver Code Starts
#include <bits/stdc++.h>
using namespace std;

// } Driver Code Ends

// https://practice.geeksforgeeks.org/contest/gfg-weekly-170-rated-contest/problems

class Solution {
  public:
    long long getMax(int n, int m, vector<vector<int>> &mat) {
        vector<vector<long long>> dp(n, vector<long long>(m, 0));
        
        // After storing the sum of all the rectangles at each cell
        // which is at the last cell diagnol of the rectangle in DP
        // It is easy to manipulate the data to get ANS
        dp[0][0] = mat[0][0];
        for(int i=1 ;i<m ;i++) {
            dp[0][i] = dp[0][i-1] + mat[0][i];
        }
        
        for(int i = 1; i<n ;i++) {
            dp[i][0] = dp[i-1][0] + mat[i][0];
        }
        
        for(int i=1; i<n ;i++) {
            for(int j=1; j<m ;j++) {
                dp[i][j] = mat[i][j] + dp[i-1][j] + dp[i][j-1] - dp[i-1][j-1];
            }
        }
        
        long long ans = 0;
        
        for(int i=1; i<n-1 ;i++) {
            for(int j=1; j<m-1 ;j++) {
                long long topleft = dp[i-1][j-1];
                long long topright = dp[i-1][m - 1] - dp[i-1][j];
                long long bottomleft = dp[n - 1][j-1] - dp[i][j-1];
                long long bottomright = dp[n-1][m-1] - dp[n-1][j] - dp[i][m-1] + dp[i][j];
                
                long long objective = topleft * bottomright + bottomleft * topright;
                
                ans = max(ans, objective);
            }
        }
        
        return ans;
    }
};


//{ Driver Code Starts.

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        vector<vector<int>> arr(n, vector<int>(m));
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                cin >> arr[i][j];

        Solution ob;
        cout << ob.getMax(n, m, arr) << endl;
    }
}
// } Driver Code Ends