//{ Driver Code Starts
#include <bits/stdc++.h>
using namespace std;


// } Driver Code Ends
// User function Template for C++

class Solution {
  public:
    
    bool isSubstr(string s1, string s2) {
        int m = s1.size();
        int n = s2.size();
        int i = 0;
        // cout << s1 << " " << s2 << endl;
        while (i <= m - n) { 
            if (s2[0] == s1[i]) {
                int j = 0;
                while (i + j < m && j < n && s1[i + j] == s2[j]) {
                    j++;
                }
                if (j == n) return true;  
            }
            i++;  
        }
        
        return false; 
    }
    int minRepeats(string& s1, string& s2) {
        int m = s1.size();
        int n = s2.size();
        int cnt = (n + m - 1) / m; 

        string str = "";
        int ans = 0;
        
        while(ans <= cnt) {
            str += s1;
            ans++;
            if(isSubstr(str, s2)) {
                return ans;
            }
        }
        
        return -1;
    }
};

//{ Driver Code Starts.

int main() {
    int t;
    scanf("%d ", &t);
    while (t--) {
        string A, B;
        getline(cin, A);
        getline(cin, B);

        Solution ob;
        cout << ob.minRepeats(A, B) << endl;
    }
    return 0;
}
// } Driver Code Ends