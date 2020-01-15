// Problem : https://www.interviewbit.com/problems/flip/
// Author  : The Philomath
// Date    : 15-01-2020

/**********************************************************************************
*   You are given a binary string(i.e. with characters 0 and 1) S consisting of characters S1, S2, …, SN.
*   In a single operation, you can choose two indices L and R such that 1 ≤ L ≤ R ≤ N and
*   flip the characters SL, SL+1, …, SR. By flipping, we mean change character 0 to 1 and vice-versa.
*
*   Your aim is to perform ATMOST one operation such that in final string number of 1s is maximised.
*   If you don’t want to perform the operation, return an empty array.
*   Else, return an array consisting of two elements denoting L and R.
*   If there are multiple solutions, return the lexicographically smallest pair of L and R.
*
*   Notes:
*
*   Pair (a, b) is lexicographically smaller than pair (c, d) if a < c or, if a == c and b < d.
*   For example,
*
*   S = 010
*
*   Pair of [L, R] | Final string
*   _______________|_____________
*   [1 1]          | 110
*   [1 2]          | 100
*   [1 3]          | 101
*   [2 2]          | 000
*   [2 3]          | 001
*
*   We see that two pairs [1, 1] and [1, 3] give same number of 1s in final string. So, we return [1, 1].
*
**********************************************************************************/
//Timeout
vector<int> Solution::flip(string A) {
    int sz = A.size();
    int zcount = 0;
    int ocount = 0;

    for(int i =0; i<sz; i++)
    {
        if(A[i] == '0') zcount++;
        else ocount++;
    }
    if(ocount == sz) return {};

    int max = 0;

    vector<int> ret(2,0);
    for(int i =0; i< sz; i++)
    {
        zcount = 0;
        ocount = 0;
        for(int j = i; j<sz; j++)
        {
            if(A[j] == '0') zcount++;
            else ocount++;
            if(max < zcount-ocount)
            {
                ret[0] = i + 1;
                ret[1] = j + 1;
                max = zcount-ocount;
            }
        }
    }
    return ret;
}
//Accepted
vector<int> Solution::flip(string A) {
    int sz = A.size();
    int zcount = 0;
    int ocount = 0;

    for(int i =0; i<sz; i++)
    {
        if(A[i] == '0') zcount++;
        else ocount++;
    }
    if(ocount == sz) return {};

    int max = 0;

    vector<int> ret(2,0);

    int maxOne = 0;
    int currOne = -1;
    int startIndex = 0;

    for(int i = 0; i<sz; i++)
    {
        if(A[i] == '0')
        {
            if(currOne < 0)
            {
                currOne = 0;
                startIndex = i + 1;
            }
            currOne++;
        }
        else currOne--;

        if(maxOne < currOne)
        {
            ret[0] = startIndex;
            ret[1] = i+1;
            maxOne = currOne;
        }
    }
    return ret;
}
