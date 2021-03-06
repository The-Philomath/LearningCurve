// Problem : https://leetcode.com/problems/predict-the-winner/
// Author  : The Philomath
// Date    : 10-12-2019

/**********************************************************************************
*
* Given an array of scores that are non-negative integers.
* Player 1 picks one of the numbers from either end of the array followed by the player 2 and then player 1 and so on.
* Each time a player picks a number, that number will not be available for the next player.
* This continues until all the scores have been chosen. The player with the maximum score wins.

* Given an array of scores, predict whether player 1 is the winner. You can assume each player plays to maximize his score.

* Example 1:
* Input: [1, 5, 2]
* Output: False
* Explanation: Initially, player 1 can choose between 1 and 2.
* If he chooses 2 (or 1), then player 2 can choose from 1 (or 2) and 5.
* If player 2 chooses 5, then player 1 will be left with 1 (or 2).
* So, final score of player 1 is 1 + 2 = 3, and player 2 is 5.
* Hence, player 1 will never be the winner and you need to return False.
*
* Example 2:
* Input: [1, 5, 233, 7]
* Output: True
* Explanation: Player 1 first chooses 1. Then player 2 have to choose between 5 and 7.
* No matter which number player 2 choose, player 1 can choose 233.
* Finally, player 1 has more score (234) than player 2 (12), so you need to return True representing player1 can win.
*
************************************************************************************/

// Recursive Solution

int CheckWinner(vector<int>& nums, int start, int end) {
        if( start == end ) return nums[start];

        return max( nums[start] - CheckWinner(nums, start + 1, end),
                    nums[end] - CheckWinner(nums, start, end-1));
    }

bool PredictTheWinner(vector<int>& nums) {
        return CheckWinner(nums, 0, nums.size() - 1 ) >= 0;
    }

// Recursive memoization / DP Top Down

int CheckWinner(vector<vector<int>>& mem, vector<int>& nums, int start, int end){
        if(start == end) return nums[start];
        if(mem[start][end] != INT_MIN) return mem[start][end];

        mem[start][end] = std::max( nums[start] - CheckWinner(mem, nums, start + 1, end),
                         nums[end] - CheckWinner(mem, nums, start, end - 1));

        return mem[start][end];
    }

bool PredictTheWinner(vector<int>& nums) {
        vector<vector<int>> mem (nums.size(),vector<int>(nums.size(), INT_MIN));
        return CheckWinner(mem, nums, 0, nums.size() - 1 ) >= 0;
    }

// DP Bottom up Solution
// Smallest subproblem can be considered as there is only one element in array so the score of player 1 will be equal to that element.
// we can create bigger subproblem with the solution of this subproblem. considering the 2 elements(interval) at a time then 3 and so on upto n.
// let's consider subproblem with 2 elements at a time.
// We choose first one then the second person will choose another.
// if there are three elements and we choose first element then for the player 2 subproblem is a set of 2 and we already have a solution for that.
// so subtracting the choosen element from the solution of player2's subproblem will give us the solution.

//Further Reference: https://algorithms.tutorialhorizon.com/dynamic-programming-coin-in-a-line-game-problem/

bool PredictTheWinner(vector<int>& nums) {
        vector<vector<int>> mem (nums.size(),vector<int>(nums.size(), INT_MIN));

        for(int i = 0; i < nums.size(); i++)
        {
            mem[i][i] = nums[i];
        }
        for(int interval = 2; interval <= nums.size(); interval++)
        {
            for(int i = 0; j = interval - 1, j < nums.size(); i++, j++)
            {
                mem[i][j] = max(nums[i] - mem[i+1][j], nums[j] - mem[i][j-1]);
            }
        }

        return mem[0][nums.size()-1] >= 0;
    }
