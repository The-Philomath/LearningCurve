// Problem : https://www.interviewbit.com/problems/maximum-absolute-difference/
// Author  : The Philomath
// Date    : 16-01-2020

/**********************************************************************************
*   You are given an array of N integers, A1, A2 ,…, AN. Return maximum value of f(i, j) for all 1 ≤ i, j ≤ N.
*   f(i, j) is defined as |A[i] - A[j]| + |i - j|, where |x| denotes absolute value of x.
*
*   For example,
*
*   A=[1, 3, -1]
*
*   f(1, 1) = f(2, 2) = f(3, 3) = 0
*   f(1, 2) = f(2, 1) = |1 - 3| + |1 - 2| = 3
*   f(1, 3) = f(3, 1) = |1 - (-1)| + |1 - 3| = 4
*   f(2, 3) = f(3, 2) = |3 - (-1)| + |2 - 3| = 5
*
*   So, we return 5.
*
**********************************************************************************/
//Timeout O(n2)
int Solution::maxArr(vector<int> &A) {

    int sz = A.size();
    int maxDiff = 0;
    for(int i =0; i<= sz; i++)
    {
        for(int j = i+1; j<sz; j++)
        {
            maxDiff = max(maxDiff, abs(A[i] - A[j]) + abs(i- j));
        }
    }
    return maxDiff;
}

//Accepted
int Solution::maxArr(vector<int> &A) {

    int sz = A.size();
    int maxDiff = 0;
    vector<int> B(sz,0);
    for(int i =0; i< sz; i++)
    {
        B[i] = A[i] - i;
        A[i] = A[i] + i;
    }
    if(sz <= 1) return 0;
    int maximum = max(A[0], A[1]);
    int minimum = min(A[0], A[1]);
    int maximumB = max(B[0], B[1]);
    int minimumB = min(B[0], B[1]);
    for(int i =0; i< sz; i++)
    {
        if(A[i] > maximum)
        {
            maximum = A[i];
        }
        else if (A[i] < minimum)
        {
            minimum = A[i];
        }
        if(B[i] > maximumB)
        {
            maximumB = B[i];
        }
        else if (B[i] < minimumB)
        {
            minimumB = B[i];
        }
    }

    return max(abs(maximum - minimum), abs(maximumB - minimumB));
}
// No need to create an extra array. we are just interested in the values.
int Solution::maxArr(vector<int> &A) {
    int sz = A.size();

    if(sz <= 1) return 0;
    int maximum = max(A[0], A[1] + 1);
    int minimum = min(A[0], A[1] + 1);
    int maximumB = max(A[0], A[1] - 1);
    int minimumB = min(A[0], A[1] - 1);

    for(int i = 2; i < sz; i++){
        maximum = max(maximum, A[i] + i);
        maximumB = max(maximumB, A[i] - i);
        minimum = min(minimum, A[i] + i);
        minimumB = min(minimumB, A[i] - i);
    }
  
    return max(abs(maximum - minimum), abs(maximumB - minimumB));
}
