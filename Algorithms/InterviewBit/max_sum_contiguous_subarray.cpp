// Problem : https://www.interviewbit.com/problems/max-sum-contiguous-subarray/
// Author  : The Philomath
// Date    : 15-01-2020

/**********************************************************************************
*   Find the contiguous subarray within an array, A of length N which has the largest sum.
*
*   Input Format:
*
*   The first and the only argument contains an integer array, A.
*   Output Format:
*
*   Return an integer representing the maximum possible sum of the contiguous subarray.
*   Constraints:
*   1 <= N <= 1e6
*   -1000 <= A[i] <= 1000
*   For example:
*   Input 1:
*       A = [1, 2, 3, 4, -10]
*
*   Output 1:
*       10
*
*   Explanation 1:
*       The subarray [1, 2, 3, 4] has the maximum possible sum of 10.
*
**********************************************************************************/
int Solution::maxSubArray(const vector<int> &A) {
    // Do not write main() function.
    // Do not read input, instead use the arguments to the function.
    // Do not print the output, instead return values as specified
    // Still have a doubt. Checkout www.interviewbit.com/pages/sample_codes/ for more details
    int maximum =A[0];
    int max_now =A[0];
    for(int i =1; i< A.size(); i++)
    {
        if((max_now + A[i] > max_now) || (max_now +A[i] > 0))
        {
            if(max_now > 0)
          max_now = max_now + A[i];
          else
          max_now = A[i];
        }
        else
        {
            max_now = A[i];
        }
        maximum = max(max_now, maximum);
    }
    return maximum;
}
