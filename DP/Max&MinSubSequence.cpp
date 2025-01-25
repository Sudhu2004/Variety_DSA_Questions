#include<bits/stdc++.h>

using namespace std;


int f1(int i, vector<int>& arr,int m, vector<int>& dp) {

    if(i >= arr.size()) return 0;
    
    if(dp[i] != -1) return dp[i];
    int notpick = f1(i + 1, arr, m, dp);
    int pick = 0;
    for(int j = i; j<arr.size(); j++) {
        pick = max(pick, arr[j] + f1(j + m + 1, arr, m, dp));
    }

    return dp[i] = max(pick, notpick);
}


int f2(int i, vector<int>& arr,int m, vector<int>& dp) {

    if(i >= arr.size()) return 0;
    
    if(dp[i] != -1) return dp[i];

    int notpick = f2(i + 1, arr, m, dp);
    int pick = INT_MAX;
    for(int j = i; j<arr.size(); j++) {
        pick = min(pick, arr[j] + f2(j + m + 1, arr, m, dp));
    }

    return dp[i] = min(pick, notpick);
}


void getMaxAndMinSubSequence(vector<int>& arr,int m) {
    int n = arr.size();
    vector<int> dp(n, -1);
    int maxi =  f1(0, arr, m, dp);
    cout << maxi << endl;

    for(int i=0; i<n; i++) dp[i] = -1;
    
    int mini = f2(0, arr, m, dp);
    cout << mini << endl;
}
int main() {
    vector<int> arr = {3, 4, -2, 1, -2, 4, 6, -3, 5};
    int m = 2;
    getMaxAndMinSubSequence(arr, m);
}