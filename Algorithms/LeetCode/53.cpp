// Problem : https://leetcode.com/problems/maximum-subarray/
// Author  : The Philomath
// Date    : 15-01-2020

/**********************************************************************************
*   Given an integer array nums, find the contiguous subarray (containing at least one number)
*   which has the largest sum and return its sum.
*
*   Example:
*
*   Input: [-2,1,-3,4,-1,2,1,-5,4],
*   Output: 6
*   Explanation: [4,-1,2,1] has the largest sum = 6.
*
**********************************************************************************/
int maxSubArray(vector<int>& nums) {

        int maxSum = nums[0];
        int currSum = nums[0];
        for(int i = 1; i<nums.size(); i++)
        {
            currSum = max (currSum+nums[i], nums[i]);
            if(maxSum < currSum)
                maxSum = currSum;

        }
        return maxSum;
  }
