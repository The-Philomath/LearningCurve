// Problem : https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iii/
// Author  : The Philomath
// Date    : 16-02-2020

/**********************************************************************************
*    Say you have an array for which the ith element is the price of a given stock on day i.
*
*    Design an algorithm to find the maximum profit. You may complete at most two transactions.
*
*    Note: You may not engage in multiple transactions at the same time (i.e., you must sell the stock before you buy again).
*
*    Example 1:
*
*    Input: [3,3,5,0,0,3,1,4]
*    Output: 6
*    Explanation: Buy on day 4 (price = 0) and sell on day 6 (price = 3), profit = 3-0 = 3.
*                 Then buy on day 7 (price = 1) and sell on day 8 (price = 4), profit = 4-1 = 3.
**********************************************************************************/
class Solution {
public:

   int maxProfit(vector<int>& prices) {

       int sz = prices.size();
       if(sz == 0) return 0;

       int start = 0;
       int end = 1;

       auto findMaxProfit = [&](int begin, int last){
           int ret = 0;
           start = begin-1;
           end = begin;
           int startemp = start;
           for(int i = begin; i < last; i++)
           {
               if(ret < prices[i] - prices[startemp])
               {
                   end = i;
                   start = startemp;
                   ret = prices[end] - prices[startemp];
               }
               if(prices[startemp] > prices[i]) startemp = i;
           }

           return ret;
       };
       /*Find max profit in whole array*/
       int profit = findMaxProfit(end, sz);
       int start1 = start;
       int end1 = end;

       /*
       Case 1:
       Now the second transaction could be from 0 to start position of first transaction or
       it could be from end to sizeof array -1
       */
       int mx = max(findMaxProfit(1, start1), findMaxProfit(end1 + 2, sz));


       start = end1-1;
       end = end1-2;
       int endtemp = start;
       int ret = 0;

       /*
       case 2:
       second transaction could be in between the start and end position of first transaction.
       That can oly be possible if there is a spike and fall in between the start and end.
       This spike would be less than end. And fall would be greater than begin
       so traversing array in reverse can give us the spike and fall.
       */
       for(int i = end; i > start1; i--)
       {
           if(ret < prices[i] - prices[endtemp])
           {
               end = i;
               start = endtemp;
               ret = prices[end] - prices[endtemp];
           }
           if(prices[start] > prices[i]) endtemp = i;
       }
       /*transaction 1 + max of case1 and case2*/
       return profit + max(mx,ret);
    }
};
