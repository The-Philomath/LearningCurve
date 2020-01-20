// Problem : https://leetcode.com/problems/longest-palindromic-substring/
// Author  : The Philomath
// Date    : 18-01-2020

/**********************************************************************************
*    Given a string s, find the longest palindromic substring in s.
*    You may assume that the maximum length of s is 1000.
*
*    Example 1:
*
*    Input: "babad"
*    Output: "bab"
*    Note: "aba" is also a valid answer.
*
**********************************************************************************/

class Solution {
public:
    string longestPalindrome(string s) {
        string ret = "";
        int sz = s.size();
        if(sz == 0) return ret;
        ret = ret + s[0];
        for(int i = 1; i< sz; i++)
        {
            int k = i;
            int j = -1;
            if(s[i] == s[i-1])
            {
                j = i-1;
                while(i+1< sz && s[i + 1] == s[i]) i++;
            }
            else if(i-2 >= 0 && s[i] == s[i-2]) j = i-2;
            if(j != -1)
            {
                while(i< sz && j >= 0 && s[i] == s[j])
                {
                    i++;
                    j--;
                }
                i--;
                string temp = s.substr(j+1, i-j);
                i = k;
                if(temp.size() > ret.size())
                    ret = temp;

            }
        }

        return ret;
    }
};
