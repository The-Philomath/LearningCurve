// Problem : https://leetcode.com/problems/construct-binary-tree-from-inorder-and-postorder-traversal/
// Author  : The Philomath
// Date    : 03-12-2019

/********************************************************************************** 
*
*    106. Construct Binary Tree from Inorder and Postorder Traversal
*
*    Given inorder and postorder traversal of a tree, construct the binary tree.
*
*    Note:
*    You may assume that duplicates do not exist in the tree.
*
*    For example, given
*
*    inorder = [9,3,15,20,7]
*    postorder = [9,15,7,20,3]
*    Return the following binary tree:
*
*        3
*       / \
*      9  20
*        /  \
*       15   7
**********************************************************************************/

class Solution {
public:

     TreeNode* buildTreeNodes(vector<int>& postorder, vector<int>& inorder, int &postI, vector<int>::iterator InB, vector<int>::iterator InE)
    {
        TreeNode* root = new TreeNode(postorder[postI]);
        auto it = find(InB, InE, postorder[postI]);
        root->right = (InE == it+1)? NULL : buildTreeNodes(postorder, inorder, --postI, it + 1, InE);
        root->left = (InB == it)? NULL : buildTreeNodes(postorder, inorder, --postI, InB, it);
        
        
        return root;
    }
     TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        int i = postorder.size() - 1;
        if(postorder.size() == 0) return NULL;
        return buildTreeNodes(postorder, inorder, i, inorder.begin(), inorder.end());
    }
};
