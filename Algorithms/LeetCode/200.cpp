// Problem : https://leetcode.com/problems/number-of-islands/
// Author  : The Philomath
// Date    : 03-03-2020

/**********************************************************************************
*
*    Given a 2d grid map of '1's (land) and '0's (water), count the number of islands.
*    An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically.
*    You may assume all four edges of the grid are all surrounded by water.
*
*    Example 1:
*
*    Input:
*    11110
*    11010
*    11000
*    00000
*
*    Output: 1
*
**********************************************************************************/
class Solution {
public:
    void mark(vector<vector<bool>>& visit, vector<vector<char>> & grid, int i, int j)
    {
        int r = grid.size();
        int c = grid[0].size();

        visit[i][j] = true;
        if(i+1 < r && (grid[i+1][j] == '1') && !visit[i+1][j])
        {
            mark(visit, grid, i+1, j);
        }
        if(i-1 >= 0 && (grid[i-1][j] == '1') && !visit[i-1][j])
        {
            mark(visit, grid, i-1, j);
        }
        if(j+1 < c && (grid[i][j+1] == '1') && !visit[i][j+1])
        {
            mark(visit, grid, i, j+1);
        }
        if(j-1 >= 0 && (grid[i][j-1] == '1') && !visit[i][j-1])
        {
            mark(visit, grid, i, j-1);
        }
    }

    int numIslands(vector<vector<char>>& grid) {
         int shapes = 0;
    if(grid.size() == 0) return 0;
    vector<vector<bool>> visit(grid.size(), vector<bool>(grid[0].size(), false));

    int r = grid.size();
    int c = grid[0].size();

    for(int i =0; i<r; i++)
    {
        for(int j =0; j< c; j++)
        {
            if(grid[i][j] == '1' && visit[i][j] == false)
            {
                mark(visit, grid, i, j);
                shapes++;
            }
        }
    }
    return shapes;
    }
};
