// Problem : https://leetcode.com/problems/product-of-array-except-self/
// Author  : The Philomath
// Date    : 23-02-2020

/**********************************************************************************
*
*    Given an array nums of n integers where n > 1,
*    return an array output such that output[i] is equal to the product of all the elements of nums except nums[i].
*
*    Example:
*
*    Input:  [1,2,3,4]
*    Output: [24,12,8,6]
*    Note: Please solve it without division and in O(n).
*
*    Follow up:
*    Could you solve it with constant space complexity?
*    (The output array does not count as extra space for the purpose of space complexity analysis.)
*
**********************************************************************************/
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        vector<int> v(nums.size(), 0);
        int sz = nums.size();
        if(sz <= 1) return v;
        v[0] = 1;
        for(int i = 1; i < nums.size(); i++)
        {
            v[i] = v[i-1] * nums[i-1];
        }

        long prod = nums[sz-1];
        for(int i = sz - 2; i >= 0; i--)
        {
            v[i] = v[i] * prod;
            prod = prod * nums[i];
        }

        return v;
    }
};
