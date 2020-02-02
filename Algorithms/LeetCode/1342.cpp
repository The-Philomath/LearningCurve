// Problem : https://leetcode.com/contest/weekly-contest-174/problems/reduce-array-size-to-the-half/
// Author  : The Philomath
// Date    : 02-02-2020

/**********************************************************************************
*    Given an array arr.  You can choose a set of integers and remove all the occurrences of these integers in the array.
*    Return the minimum size of the set so that at least half of the integers of the array are removed.
*
*    Example 1:
*
*    Input: arr = [3,3,3,3,5,5,5,2,2,7]
*    Output: 2
*    Explanation: Choosing {3,7} will make the new array [5,5,5,2,2] which has size 5
*                 (i.e equal to half of the size of the old array).
*    Possible sets of size 2 are {3,5},{3,2},{5,2}.
*    Choosing set {2,7} is not possible as it will make the new array [3,3,3,3,5,5,5]
*    which has size greater than half of the size of the old array.
**********************************************************************************/


class Solution {
public:
    int minSetSize(vector<int>& arr) {
       std::map<int,int> mp;
        for(auto i:arr)
        {
            mp[i]++;
        }
        std::vector<int> v;
        for(auto i:mp)
        {
            v.push_back(i.second);
        }
        std::sort(v.begin(),v.end(), std::greater<int>());

        int sz = arr.size();
        int hsz = arr.size()/2;
        int count = 0;
        auto it = v.begin();
        while(sz > hsz)
        {
            sz = sz - *it;
            it++;
            count++;
        }
        return count;
    }
};
