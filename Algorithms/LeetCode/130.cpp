// Problem : https://leetcode.com/problems/surrounded-regions/
// Author  : The Philomath
// Date    : 05-03-2020

/**********************************************************************************
*
*    Given a 2D board containing 'X' and 'O' (the letter O), capture all regions surrounded by 'X'.
*
*    A region is captured by flipping all 'O's into 'X's in that surrounded region.
*
*    Example:
*
*    X X X X
*    X O O X
*    X X O X
*    X O X X
*    After running your function, the board should be:
*
*    X X X X
*    X X X X
*    X X X X
*    X O X X
*    Explanation:
*
*    Surrounded regions shouldn’t be on the border, which means that any 'O' on the border of the board are not flipped to 'X'.
*    Any 'O' that is not on the border and it is not connected to an 'O' on the border will be flipped to 'X'.
*    Two cells are connected if they are adjacent cells connected horizontally or vertically.
*
**********************************************************************************/
class Solution {
public:
    void markBoundaryOs(vector<vector<char>>& board, int i, int j)
    {
        board[i][j] = 'M';
        vector<vector<int>> neighbours = {{i-1, j},
                                          {i, j-1},
                                          {i+1, j},
                                          {i, j+1}};
        int r = board.size();
        int c = board[0].size();

        for(int i =0; i<4; i++)
        {
            int neighR = neighbours[i][0];
            int neighC = neighbours[i][1];

            if(neighR >= 0 && neighR < r && neighC >= 0 && neighC < c && board[neighR][neighC] == 'O')
            {
                markBoundaryOs(board, neighR, neighC);
            }
        }
    }

    void solve(vector<vector<char>>& board) {

        int r = board.size();
        if(r == 0) return;
        int c = board[0].size();
        if(c == 0) return;

        for(int i = 0; i < r; i++)
        {
            if(board[i][0] == 'O')
                markBoundaryOs(board, i, 0);
            if(board[i][c-1] == 'O')
                markBoundaryOs(board, i, c-1);
        }

        for(int j = 0; j < c; j++)
        {
            if(board[0][j] == 'O')
                markBoundaryOs(board, 0, j);
            if(board[r-1][j] == 'O')
                markBoundaryOs(board, r-1, j);
        }

        for(int i = 0; i < r; i++)
        {
            for(int j = 0; j < c; j++)
            {
                if(board[i][j] == 'O') board[i][j] = 'X';
                else if(board[i][j] == 'M') board[i][j] = 'O';
            }
        }
    }
};
