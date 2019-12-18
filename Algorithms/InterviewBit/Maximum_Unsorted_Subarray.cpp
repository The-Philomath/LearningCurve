// Problem : https://www.interviewbit.com/problems/maximum-unsorted-subarray/
// Author  : The Philomath
// Date    : 18-12-2019

/**********************************************************************************
*
*    You are given an array (zero indexed) of N non-negative integers, A0, A1 ,…, AN-1.
*    Find the minimum sub array Al, Al+1 ,…, Ar so if we sort(in ascending order) that sub array, then the whole array should get sorted.
*    If A is already sorted, output -1.
*
*    Example :
*
*    Input 1:
*    A = [1, 3, 2, 4, 5]
*    Return: [1, 2]
*
*    Input 2:
*    A = [1, 2, 3, 4, 5]
*    Return: [-1]
*    In the above example(Input 1), if we sort the subarray A1, A2, then whole array A should get sorted.
**********************************************************************************/
// Memory limit exceed
vector<int> Solution::subUnsort(vector<int> &A) {
    int n = A.size();
    vector<int> B(n);
    std::copy(A.begin(), A.end(), B.begin());
    std::sort(B.begin(), B.end());

    int start =0, end = n-1;
    while(start < n && A[start] == B[start]) start++;
    while(end >=0 && A[end] == B[end]) end--;

    if(start > end) return {-1};
    return {start,end};
}

// Accepted solution
vector<int> Solution::subUnsort(vector<int> &A) {
    int n = A.size();  
    int start =0, end = n-1;
    for(int i = 1; i< n; i++)
    {
        if(A[start] <= A[i] && start == i -1) start = i;
        else if(A[start] > A[i])
        {
            while(start >= 0 && A[start] > A[i]) start--;
        }
    }
    for(int i = n - 2; i >= 0; i--)
    {
        if(A[end] >= A[i] && end == i + 1) end = i;
        else if(A[end] < A[i])
        {
            while(end < n && A[end] < A[i]) end++;
        }
    }

    if(start >= end) return {-1};
    return {start + 1,end - 1};
}
