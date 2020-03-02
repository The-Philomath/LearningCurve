// Problem : https://leetcode.com/problems/validate-binary-tree-nodes/
// Author  : The Philomath
// Date    : 02-03-2020

/**********************************************************************************
*
*    You have n binary tree nodes numbered from 0 to n - 1 where node i has two children leftChild[i] and rightChild[i],
*    return true if and only if all the given nodes form exactly one valid binary tree.
*
*    If node i has no left child then leftChild[i] will equal -1, similarly for the right child.
*
*    Note that the nodes have no values and that we only use the node numbers in this problem.
*
*    Example:
*    Input: n = 4, leftChild = [1,-1,3,-1], rightChild = [2,3,-1,-1]
*    Output: false
**********************************************************************************/
class Solution {
public:

    bool validateBinaryTreeNodes(int n, vector<int>& leftChild, vector<int>& rightChild) {

        queue<int> q;
        q.push(0);
        set<int> nodes;
        nodes.insert(0);

        int i =0;
        while(i< leftChild.size())
        {
            if(q.empty()) return false;
            q.pop();
            if(leftChild[i] != -1)
            {
                auto ret = nodes.insert(leftChild[i]);
                if(ret.second == false)
                    return false;

                q.push(leftChild[i]);
            }

            if(rightChild[i] != -1)
            {
                auto ret = nodes.insert(rightChild[i]);
                if(ret.second == false)
                    return false;
                q.push(rightChild[i]);
            }
            i++;
        }

        return q.empty();
    }
};
