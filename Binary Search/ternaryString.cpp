// https://codeforces.com/problemset/problem/1354/B

#include<iostream>
#include<unordered_map>
#include<string>
using namespace std;


int getAns(string s, int n) {
    unordered_map<int,int> mpp;
    mpp[1] = -1;
    mpp[2] = -1;
    mpp[3] = -1;
    int i = 0; 
    int ans = 2000000;
    while(i < n) {
        if(mpp[1] != -1 && mpp[2] != -1 && mpp[3] != -1) {
            int maxi = max(mpp[1], max(mpp[2], mpp[3]));
            int mini = min(mpp[1], min(mpp[2], mpp[3]));

            int temp = maxi - mini + 1;
            ans = min(ans, temp);
        }
        mpp[s[i] - '0'] = i;
        i++;
    }
    if(mpp[1] != -1 && mpp[2] != -1 && mpp[3] != -1) {
        int maxi = max(mpp[1], max(mpp[2], mpp[3]));
        int mini = min(mpp[1], min(mpp[2], mpp[3]));

        int temp = maxi - mini + 1;
        ans = min(ans, temp);
    }

        // cout << "Map: " << endl;
        // for(auto it: mpp) {
        //     cout << it.first << " - > " << it.second << endl;
        // }

    return ans == 2000000?0: ans;
}
int main() {
    int t; 
    cin >> t;

    while(t--) {
        string s;
        cin >> s;

        int n = s.size();
        cout << getAns(s, n) << endl;
    }

    return 0;
}