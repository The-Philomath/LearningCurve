// Problem : https://leetcode.com/contest/weekly-contest-174/problems/maximum-product-of-splitted-binary-tree/
// Author  : The Philomath
// Date    : 02-02-2020

/**********************************************************************************
*    Given a binary tree root. Split the binary tree into two subtrees by removing 1 edge such that the product of the sums of the subtrees are maximized.
*    Since the answer may be too large, return it modulo 10^9 + 7.
*
*    Example 1:
*
*    Input: root = [1,2,3,4,5,6]
*    Output: 110
*    Explanation: Remove the red edge and get 2 binary trees with sum 11 and 10. Their product is 110 (11*10)
*    (see the link provided above)
**********************************************************************************/
int maxProduct(TreeNode* root) {

        int sum = 0;
        long getSum = 0;
        long ans = 0;
        std::function<int(TreeNode *)> total = [&](TreeNode *root){
            if(root == NULL) return 0;
            int rl = total(root->left);
            int rr = total(root->right);
            sum = root->val + rl + rr;
            if(getSum) {
                ans = max(ans, max((getSum - rl) * rl, (getSum - rr) * rr));
            }
            return sum;
        };

        getSum = total(root);
        total(root);
        return ans % 1000000007;
    }
