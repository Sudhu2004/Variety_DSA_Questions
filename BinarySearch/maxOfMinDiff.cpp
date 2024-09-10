// https://leetcode.com/problems/maximize-score-of-numbers-in-ranges/description/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define ll long long

class Solution {
public:
    // If the number is the minimum then no other number should 
    // be min
    bool check(vector<int>& start, int d, ll mid) {
        ll p = start[0];
        int n = start.size();

        for(int i = 1; i < n; i++) {
            //since the first number is smallest
            // the next number should exist in the range
            if(p + mid >= start[i] && p + mid <= start[i] + d) {
                p += mid;
            }
            // if not get the new range
            else if(p + mid < start[i]) {
                p = start[i];
            }
            // else there exists a number lesser than mid
            else {
                return false;
            }
        }

        return true;
    }

    // the number can exist anywhere
    // so we have to do BS between 0 -> 1e12 (given range)
    
    int maxPossibleScore(vector<int>& start, int d) {
        ll low = 0, high = 1e12;

        sort(start.begin(), start.end());
        ll ans = 0;

        while(low <= high) {
            ll mid = (low + high) / 2;

            if(check(start, d, mid)) {
                ans = mid;
                low = mid + 1;
            }
            else {
                high = mid - 1;
            }
        }

        return ans;
    }
};

int main() {
    Solution sol;

    // Sample input
    vector<int> start = {6,0,3};
    int d = 2;

    // Call the function and print the result
    int result = sol.maxPossibleScore(start, d);
    cout << "The maximum possible score is: " << result << endl;

    return 0;
}
