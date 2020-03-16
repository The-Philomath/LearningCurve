// Problem : https://www.interviewbit.com/problems/equal/
// Author  : The Philomath
// Date    : 16-03-2020

/**********************************************************************************
*
*    Given an array A of integers, find the index of values that satisfy A + B = C + D,
*    where A,B,C & D are integers values in the array
*
*    Note:
*
*    1) Return the indices `A1 B1 C1 D1`, so that
*       A[A1] + A[B1] = A[C1] + A[D1]
*       A1 < B1, C1 < D1
*       A1 < C1, B1 != D1, B1 != C1
*
*    2) If there are more than one solutions,
*       then return the tuple of values which are lexicographical smallest.
*
*    Assume we have two solutions
*    S1 : A1 B1 C1 D1 ( these are values of indices int the array )
*    S2 : A2 B2 C2 D2
*
*    S1 is lexicographically smaller than S2 iff
*      A1 < A2 OR
*      A1 = A2 AND B1 < B2 OR
*      A1 = A2 AND B1 = B2 AND C1 < C2 OR
*      A1 = A2 AND B1 = B2 AND C1 = C2 AND D1 < D2
*
**********************************************************************************/
vector<int> Solution::equal(vector<int> &A) {
    map<int, pair<int,int>>mp;
    vector<int> ret(4, INT_MAX);

    for(int i =0; i< A.size() -1; i++)
    for(int j = i+1; j< A.size(); j++)
    {
        int sum = A[i] + A[j];
        if(mp.find(sum) != mp.end())
        {
            if(((ret[0] > mp[sum].first) ||
               ((ret[0] == mp[sum].first) && (ret[1] > mp[sum].second)) ||
               ((ret[0] == mp[sum].first) && (ret[1] == mp[sum].second) && (ret[2] > i)) ||
               ((ret[0] == mp[sum].first) && (ret[1] == mp[sum].second) && (ret[2] == i) && (ret[3] > j)))
               && (mp[sum].first < i) && (mp[sum].second != i) && (mp[sum].second != j))
            {
                vector<int> temp = {mp[sum].first, mp[sum].second, i, j};
                ret = temp;
            }
        }
        else
        {
            mp[sum] = {i, j};
        }
    }
    if(ret[0] == INT_MAX) return {};
    return ret;
}
