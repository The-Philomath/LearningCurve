// Problem : https://leetcode.com/problems/longest-valid-parentheses/
// Author  : The Philomath
// Date    : 06-02-2020

/**********************************************************************************
*    Given a string containing just the characters '(' and ')',
*    find the length of the longest valid (well-formed) parentheses substring.
*
*    Example 1:
*
*    Input: "(()"
*    Output: 2
*    Explanation: The longest valid parentheses substring is "()"
**********************************************************************************/
int longestValidParentheses(string s) {
        stack<int> st;
        int lo = 0;
        int curr = 0;
        vector<int> vs(s.size(), 0);

        for(int i = 0; i < s.size(); i++)
        {
            if(s[i] == ')')
            {
                if(st.empty())
                {
                    vs[i] = 0;
                }
                else
                {
                    int t = st.top();
                    st.pop();
                    curr = i-t+1;
                    if(t>0)
                        curr += vs[t-1];
                    vs[i] = curr;
                    lo = max(lo, curr);
                }
            }
            else
            {
                st.push(i);
            }
        }
        lo = max(lo, curr);
        return lo;
    }
