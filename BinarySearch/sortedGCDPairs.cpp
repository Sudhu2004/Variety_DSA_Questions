// https://leetcode.com/problems/sorted-gcd-pair-queries/

#include<bits/stdc++.h>

using namespace std;

class Solution {
public:
    
    vector<int> gcdValues(vector<int>& nums, vector<long long>& queries) {
        vector<long long> gcdCnt(50001, 0);

        for(auto it: nums) {
            for(int i=1; (i*i) <= it; i++) {
                if(it % i == 0) {
                    int x = i;
                    int y = it / i;

                    if(x == y) {
                        gcdCnt[x]++;
                    }
                    else {
                        gcdCnt[x]++;
                        gcdCnt[y]++;
                    }
                }
            }
        }

        for(int i=1; i<=50000; i++) {
            long long value = gcdCnt[i];
            gcdCnt[i] = (value * 1LL * (value - 1LL))/2LL;
        }

        for(int i=50000; i>=0; i--) {
            
            if(gcdCnt[i] > 0) {
                for(int j=1; (j*j) <= i; j++) {
                    if(i % j == 0) {
                        int x = j;
                        int y = i / j;

                        if(x == y && x != i) {
                            gcdCnt[x] -= gcdCnt[i];
                        }
                        else {
                            if(x != i)
                                gcdCnt[x] -= gcdCnt[i];
                            if(y != i)
                                gcdCnt[y] -= gcdCnt[i];
                        }
                    }
                }
            }
        }

        for(int i=1; i<=50000; i++) {
            gcdCnt[i] += gcdCnt[i-1];
        }

        vector<int> ans;

        for(auto it: queries) {
            long long val = it + 1;
            int lb = lower_bound(gcdCnt.begin(), gcdCnt.end(), val) - gcdCnt.begin();
            ans.push_back(lb);
        }
        return ans;
    }
};

void print(vector<int>& arr) {
    for(auto it: arr) cout << it << " ";
    cout << endl;
}
int main() {
    int n;
    cin >> n;
    vector<int> nums(n);
    vector<long long> queries(n);

    for(int i=0; i < n ; i++) {
        cin >> nums[i];
    }
    for(int i=0; i<n ;i++) {
        cin >> queries[i];
    }

    Solution obj;

    vector<int> ans = obj.gcdValues(nums, queries);
    print(ans);

    return 0;
}