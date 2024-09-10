// https://leetcode.com/problems/reach-end-of-array-with-max-score/description/
#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    long long findMaximumScore(vector<int>& nums) {
        int n = nums.size();
        int i = 0;
        long long ans = 0;

        for(int j = 1; j < n; j++) {
            if(nums[j] >= nums[i]) {
                ans += 1LL * (j - i) * nums[i];
                i = j;
            } else if(j == n - 1) {
                ans += 1LL * (j - i) * nums[i];
            }
        }

        return ans;
    }
};

int main() {
    Solution sol;

    // Test case 1
    vector<int> nums1 = {1, 3, 1, 5};
    cout << "Test case 1 - Input: [1, 3, 1, 5]" << endl;
    cout << "Output: " << sol.findMaximumScore(nums1) << endl; // Expected Output: 7

    // Test case 2
    vector<int> nums2 = {4, 3, 1, 3, 2};
    cout << "Test case 2 - Input: [4, 3, 1, 3, 2]" << endl;
    cout << "Output: " << sol.findMaximumScore(nums2) << endl; // Expected Output: 16

    return 0;
}
