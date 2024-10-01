#include<bits/stdc++.h>

using namespace std;


int main() {
    string s, t;
    getline(cin , s);
    getline(cin , t);
    
    int n = s.size();

    unordered_set<string> st;
    // indices (i,j) =>1 means a palindrome of range (i, j)
    // else => 0, then not
    vector<vector<bool>> dp(n, vector<bool>(n, false));
    
    // the movement of j is toward s 0 starting from i
    // and checking wether the chars are equal or not
    for(int i=0 ; i<n ;i++) {
        for(int j=i; j>=0 ;j--) {
            if(s[i] == s[j]) {
                if( i-j <= 2 || dp[i-1][j+1]) {
                    dp[i][j] = true;
                    st.insert(s.substr(j, i - j + 1));
                }
            }
        }
    }

    // // DP Table
    // for(int i=0 ;i<n ;i++) {
    //     for(int j=0 ;j <n ;j++) {
    //         cout << dp[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    // cout << endl;

    int ans = 0;
    for(auto patt: st) {
        int sz = patt.size();
        for(int i=0 ;i<=t.size() - sz; i++) {
            string news = t.substr(i, sz);
            if(news == patt) {
                ans = max(ans, sz);
                break;
            }
        }
    } 

    cout << ans << endl;
    return 0;
}