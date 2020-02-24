// Problem : https://leetcode.com/problems/first-missing-positive/
// Author  : The Philomath
// Date    : 24-02-2020

/**********************************************************************************
*
*    Given an unsorted integer array, find the smallest missing positive integer.
*
*    Example 1:
*
*    Input: [1,2,0]
*    Output: 3
*    Example 2:
*
*    Input: [3,4,-1,1]
*    Output: 2
*    Example 3:
*
*    Input: [7,8,9,11,12]
*    Output: 1
*    Note:
*
*    Your algorithm should run in O(n) time and uses constant extra space.
*
**********************************************************************************/
class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        int sz = nums.size();
        if(sz == 0) return 1;
        for(int i = 0; i < sz; i++)
        {
            if(nums[i] < 0 || nums[i] > sz) nums[i] = 0;
        }

        for(int i = 0; i < sz; i++)
        {
            if(nums[i]%(sz + 1) != 0)
            {
                if(nums[nums[i] % (sz + 1) - 1] < (sz + 1))
                {
                    nums[nums[i] % (sz + 1) - 1] = nums[nums[i] % (sz + 1) - 1] + (sz + 1);
                }
            }
        }

        for(int i = 0; i < sz; i++)
        {
            if(nums[i] < (sz + 1))
                return i + 1;
        }

        return sz + 1;
    }
};
// Another trick:- we can set the number to negative instead of adding the sz+1

// Other solution which I liked
class Solution
{
public:
    int firstMissingPositive(int A[], int n)
    {
        for(int i = 0; i < n; ++ i)
            while(A[i] > 0 && A[i] <= n && A[A[i] - 1] != A[i])
                swap(A[i], A[A[i] - 1]);

        for(int i = 0; i < n; ++ i)
            if(A[i] != i + 1)
                return i + 1;

        return n + 1;
    }
};
