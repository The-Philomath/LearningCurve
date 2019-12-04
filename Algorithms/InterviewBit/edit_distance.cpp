// Problem : https://www.interviewbit.com/problems/edit-distance/
// Author  : The Philomath
// Date    : 04-12-2019

/********************************************************************************** 
*
*    Given two strings A and B, find the minimum number of steps required to convert A to B. 
*    (each operation is counted as 1 step.)
*
*    You have the following 3 operations permitted on a word:
*
*    1. Insert a character
*    2. Delete a character
*    3. Replace a character
*
*    Examples:
*    Input 1:
*        A = "abad"
*        B = "abac"
*
*    Output 1:
*        1
*
*    Explanation 1:
*        Operation 1: Replace d with c.
*
*    Input 2:
*        A = "Anshuman"
*        B = "Antihuman"
*
*    Output 2:
*        2
*
*    Explanation 2:
*        => Operation 1: Replace s with t.
*        => Operation 2: Insert i.
**********************************************************************************/

int Solution::minDistance(string A, string B) {
        int len1 = A.size();
        int len2 = B.size();
        
        int dp[len1+1][len2+2];
        
        for(int i = 0; i<=len1; i++)
        {
            dp[i][0] = i;
        }
        for(int j = 0; j<=len2; j++)
        {
            dp[0][j] = j;
        }
        for(int i = 1; i<=len1; i++)
        {
            for(int j = 1; j<=len2; j++)
            {
                if(A[i-1] == B[j-1])
                {
                    dp[i][j] = dp[i-1][j-1];
                }
                else
                {
                    dp[i][j] = 1+min(min(dp[i-1][j-1], dp[i][j-1]), dp[i-1][j]);
                }
            }    
            
        }
        
        return dp[len1][len2];
}
