// Problem : https://leetcode.com/problems/3sum/
// Author  : The Philomath
// Date    : 03-01-2020

/**********************************************************************************
*    Given an array nums of n integers, are there elements a, b, c in nums such that a + b + c = 0?
*    Find all unique triplets in the array which gives the sum of zero.
*
*    Note:
*
*    The solution set must not contain duplicate triplets.
*
*    Example:
*    Given array nums = [-1, 0, 1, 2, -1, -4],
*
*    A solution set is:
*    [
*        [-1, 0, 1],
*        [-1, -1, 2]
*    ]
*
**********************************************************************************/

vector<vector<int>> threeSum(vector<int>& nums) {

        vector<vector<int>> ret;

        int sz = nums.size();
        sort(nums.begin(), nums.end());
        for(int i = 0; i < sz - 2; i++)
        {
            if (nums[i] > 0) break;
            if (i > 0 && nums[i] == nums[i - 1]) continue;
            int j = i + 1;
            int k = sz - 1;
            while(j < k)
            {
                if(nums[i] + nums[j] + nums[k] == 0)
                {
                    ret.push_back({nums[i], nums[j], nums[k]});
                    while(j<k && nums[j] == nums[j+1])j++;
                    while(j<k && nums[k] == nums[k-1])k--;
                    j++;
                    k--;
                }
                else if(nums[i] + nums[j] + nums[k] > 0) k--;
                else
                    j++;
            }
        }
        return ret;
  }
