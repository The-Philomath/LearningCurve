// Problem : https://www.interviewbit.com/problems/binary-tree-from-inorder-and-postorder/
// Author  : The Philomath
// Date    : 03-12-2019

/********************************************************************************** 
* 
*    Given inorder and postorder traversal of a tree, construct the binary tree.
*
*    Note: You may assume that duplicates do not exist in the tree. 
*    Example :
*
*    Input : 
*        Inorder : [2, 1, 3]
*        Postorder : [2, 3, 1]
*
*    Return : 
*               1
*              / \
*             2   3
*
**********************************************************************************/

 TreeNode* buildTreeNodes(vector<int>& postorder, vector<int>& inorder, int &postI, vector<int>::iterator InB, vector<int>::iterator InE)
 {
     TreeNode* root = new TreeNode(postorder[postI]);
     auto it = find(InB, InE, postorder[postI]);
     root->right = (InE == it+1)? NULL : buildTreeNodes(postorder, inorder, --postI, it + 1, InE);
     root->left = (InB == it)? NULL : buildTreeNodes(postorder, inorder, --postI, InB, it);    
        
    return root;
 }
 TreeNode* Solution::buildTree(vector<int> &A, vector<int> &B)
 {
     int i = B.size() - 1;
     if(B.size() == 0) return NULL;
     return buildTreeNodes(B, A, i, A.begin(), A.end());
 }
