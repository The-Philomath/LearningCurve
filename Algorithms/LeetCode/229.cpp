// Problem : https://leetcode.com/problems/majority-element-ii/
// Author  : The Philomath
// Date    : 10-01-2020

/**********************************************************************************
*    Given an integer array of size n, find all elements that appear more than ⌊ n/3 ⌋ times.
*
*    Note: The algorithm should run in linear time and in O(1) space.
*
*    Example 1:
*
*    Input: [3,2,3]
*    Output: [3]
*
**********************************************************************************/
vector<int> majorityElement(vector<int>& nums) {
        if(nums.size() == 0) return {};
        int count = 0;
        int count2 = 0;
        int maxElem = INT_MAX;
        int max2Elem = INT_MAX;
        for(int i = 0; i < nums.size(); i++)
        {
            if(nums[i] == maxElem)
            {
                count++;
            }
            else if(nums[i] == max2Elem)
            {
                count2++;
            }
            else if(count == 0)
            {
                count = 1;
                maxElem =nums[i];
            }
            else if(count2 == 0)
            {
                count2 = 1;
                max2Elem = nums[i];
            }
            else
            {
                count--;
                count2--;
            }
        }
        count = 0;
        count2 = 0;
        for(auto i:nums)
        {
            if(i == maxElem)
                count++;
            else if(i == max2Elem)
                count2++;
        }

        vector<int> ret;
        if(count > (nums.size()/3))
            ret.push_back(maxElem);
        if(count2 > (nums.size()/3))
            ret.push_back(max2Elem);
        return ret;
    }
