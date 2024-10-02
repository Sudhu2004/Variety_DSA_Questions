// https://leetcode.com/problems/binary-tree-cameras/description/
#include<bits/stdc++.h>

using namespace std;
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left),
 * right(right) {}
 * };
 */

struct TreeNode {
   int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left),
    right(right) {}
};
class Solution {
    map<pair<TreeNode*, pair<bool, bool>>, int> dp;

public:
    int solve(TreeNode* root, int cam, int parcam) {
        if (!root) {
            if (cam)
                return 1e4;
            return 0;
        }

        if (dp.find({root, {cam, parcam}}) != dp.end())
            return dp[{root, {cam, parcam}}];

        if (root->left == NULL && root->right == NULL) {
            if (cam) {
                return 1;
            } else {
                if (parcam) {
                    return 0;
                }
                return 1e4;
            }
        }

        if (cam) {
            return dp[{root, {cam, parcam}}] =
                       1 +
                       min(solve(root->left, 1, 1), solve(root->left, 0, 1)) +
                       min(solve(root->right, 1, 1), solve(root->right, 0, 1));
        } else {
            if (parcam) {
                return dp[{root, {cam, parcam}}] =
                           min(solve(root->left, 1, 0),
                               solve(root->left, 0, 0)) +
                           min(solve(root->right, 1, 0),
                               solve(root->right, 0, 0));
            } else {
                int op1 =
                    solve(root->left, 1, 0) +
                    min(solve(root->right, 1, 0), solve(root->right, 0, 0));
                int op2 = solve(root->right, 1, 0) +
                          min(solve(root->left, 1, 0), solve(root->left, 0, 0));
                return dp[{root, {cam, parcam}}] = min(op1, op2);
            }
        }
    }
    int minCameraCover(TreeNode* root) {
        dp.clear();

        return min(solve(root, 1, 0), solve(root, 0, 0));
    }
};