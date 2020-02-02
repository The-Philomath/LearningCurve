// Problem : https://leetcode.com/contest/weekly-contest-174/problems/the-k-weakest-rows-in-a-matrix/
// Author  : The Philomath
// Date    : 02-02-2020

/**********************************************************************************
*    Given a m * n matrix mat of ones (representing soldiers) and zeros (representing civilians),
*    return the indexes of the k weakest rows in the matrix ordered from the weakest to the strongest.
*
*    A row i is weaker than row j, if the number of soldiers in row i is less than the number of soldiers in row j,
*    or they have the same number of soldiers but i is less than j.
*    Soldiers are always stand in the frontier of a row, that is, always ones may appear first and then zeros.
*
*
*
*    Example 1:
*
*    Input: mat =
*    [[1,1,0,0,0],
*     [1,1,1,1,0],
*     [1,0,0,0,0],
*     [1,1,0,0,0],
*     [1,1,1,1,1]],
*    k = 3
*    Output: [2,0,3]
*    Explanation:
*    The number of soldiers for each row is:
*    row 0 -> 2
*    row 1 -> 4
*    row 2 -> 1
*    row 3 -> 2
*    row 4 -> 5
*    Rows ordered from the weakest to the strongest are [2,0,3,1,4]
*
**********************************************************************************/
class Solution {
public:
    vector<int> kWeakestRows(vector<vector<int>>& mat, int k) {
        vector<pair<int, int>> ret;
        for(int i =0; i<mat.size(); i++)
        {
            ret.push_back(make_pair(std::accumulate(mat[i].begin(), mat[i].end(), 0), i));
        }
        std::sort(ret.begin(), ret.end());

        vector<int>r;
        for(int i=0;i<k;i++)
        {
            r.push_back(ret[i].second);
        }
        return r;
    }

};
