// Problem : https://www.interviewbit.com/problems/n3-repeat-number/
// Author  : The Philomath
// Date    : 10-01-2020

/**********************************************************************************
*    You’re given a read only array of n integers.
*    Find out if any integer occurs more than n/3 times in the array in linear time and constant additional space.
*
*    If so, return the integer. If not, return -1.
*
*    If there are multiple solutions, return any one.
*
*    Example :
*
*    Input : [1 2 3 1 1]
*    Output : 1
*    1 occurs 3 times which is more than 5/3 times.
*
**********************************************************************************/
// Solution based on Moore’s Voting Algorithm

int Solution::repeatedNumber(const vector<int> &A) {
    // Do not write main() function.
    // Do not read input, instead use the arguments to the function.
    // Do not print the output, instead return values as specified
    // Still have a doubt. Checkout www.interviewbit.com/pages/sample_codes/ for more details

        if(A.size() == 0) return -1;
        int count = 0;
        int count2 = 0;
        int maxElem = INT_MAX;
        int max2Elem = INT_MAX;
        for(int i =0; i<A.size(); i++)
        {
            if(A[i] == maxElem)
            {
                count++;
            }
            else if(A[i] == max2Elem)
            {
                count2++;
            }
            else if(count == 0)
            {
                count = 1;
                maxElem = A[i];
            }
            else if(count2 == 0)
            {
                count2 = 1;
                max2Elem = A[i];
            }
            else
            {
                count--;
                count2--;
            }
        }
        count = 0;
        count2 = 0;
        for(auto i:A)
        {
            if(i == maxElem)
            count++;
            else if(i == max2Elem)
            count2++;
        }

        if(count > (A.size()/3))
            return maxElem;
        else if(count2 > (A.size()/3))
            return max2Elem;
        return -1;
}
