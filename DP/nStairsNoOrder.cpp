// https://www.geeksforgeeks.org/problems/count-ways-to-nth-stairorder-does-not-matter5639/1
//{ Driver Code Starts
#include<bits/stdc++.h>
using namespace std;

// } Driver Code Ends
class Solution{
	public:
	    
	    int f(int n, vector<int>& dp) {
	        if(n <= 1) return 1;
	        
	        if(dp[n] != -1) return dp[n];
	        
            // 1 step does not matter
            // In taking two steps only we are not sure weather we reach end or not
	        return dp[n] = f(n-2, dp) + 1;
	    }
		int nthStair(int n){
		  // // Memoization
		  //  vector<int> dp(n+1, -1);
		  //  return f(n, dp);
		  
          // to reach sum of number of 2s and 1s to get n
		  return (n/2) + 1;
		  
		  // // Tabulation
		  //vector<int> dp(n+1, 0);
		  
		  //dp[0] = dp[1] = 1;
		  //for(int i=2; i<=n ;i++) {
		  //    dp[i] = 1 + dp[i-2] ;
		  //}
		  
		  //return dp[n];
		    
		}
};

//{ Driver Code Starts.
int main(){
	int tc;
	cin >> tc;
	while(tc--){
		int n;
		cin >> n;
		Solution ob;
		int ans  = ob.nthStair(n);
		cout << ans <<"\n";
	}
	return 0;
}
// } Driver Code Ends