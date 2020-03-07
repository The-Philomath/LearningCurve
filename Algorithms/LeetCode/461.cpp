// Problem : https://leetcode.com/problems/hamming-distance/
// Author  : The Philomath
// Date    : 07-03-2020

/**********************************************************************************
*
*    The Hamming distance between two integers is the number of positions at which the corresponding bits are different.
*
*    Given two integers x and y, calculate the Hamming distance.
*
*    Note:
*    0 ≤ x, y < 231.
*
*    Example:
*
*    Input: x = 1, y = 4
*
*    Output: 2
*
*    Explanation:
*    1   (0 0 0 1)
*    4   (0 1 0 0)
*       ↑   ↑
*
*    The above arrows point to positions where the corresponding bits are different.
*
**********************************************************************************/
class Solution {
public:
    int hammingDistance(int x, int y) {
        int z = x^y;
        int count = 0;
        while(z)
        {
            if(z & 1)
                count++;
            z = z>>1;
        }
        return count;
    }
};

// Using Bitset
class Solution {
public:
    int hammingDistance(int x, int y) {
        return bitset<32>(x^y).count();
    }
};
