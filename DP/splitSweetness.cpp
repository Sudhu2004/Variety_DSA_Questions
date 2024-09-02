//{ Driver Code Starts
#include <bits/stdc++.h>
using namespace std;

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


// https://practice.geeksforgeeks.org/contest/gfg-weekly-170-rated-contest/problems

// } Driver Code Ends

class Solution {
  public:
    bool f(int i, int target, int n, vector<int>& sweetness, vector<vector<int>> &dp) {
        
        if(i == n) {
            return target == 0; 
        }
        
        if(dp[i][target] != -1) return dp[i][target];
        
        
        bool notpick = f(i+1, target, n, sweetness, dp);
        bool pick = false;
        if(target - sweetness[i] >= 0)
            pick = f(i+1, target - sweetness[i], n, sweetness, dp);
        
        
        return dp[i][target] =  pick || notpick;
    }
    int isValid(int n, vector<int> &sweetness) {
    

        // Value of each num in sweetness has constraints such as
        // 1 <= sweetness[i] <= 1000;
        // if we do for totalsum then the values would go more thatn 1e9;

        // so we take totalsum/3 to find ans
        
        int totalSum = accumulate(sweetness.begin(), sweetness.end(), 0);
        if(totalSum % 3 != 0) return 0;
        
        int target = totalSum/3;
        vector<vector<int>> dp(n+1, vector<int>(target + 1, -1));
        
        return f(0, target, n, sweetness, dp);

    }
};


//{ Driver Code Starts.

int main() {
    int t;
    scanf("%d ", &t);
    while (t--) {

        int n;
        scanf("%d", &n);

        vector<int> sweetness(n);
        Array::input(sweetness, n);

        Solution obj;
        int res = obj.isValid(n, sweetness);

        cout << res << endl;
    }
}

// } Driver Code Ends