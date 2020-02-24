// Problem : https://www.interviewbit.com/problems/merge-k-sorted-lists/
// Author  : The Philomath
// Date    : 24-02-2020

/**********************************************************************************
*
*    Merge k sorted linked lists and return it as one sorted list.
*
*    Example:
*
*    1 -> 10 -> 20
*    4 -> 11 -> 13
*    3 -> 8 -> 9
*
*    will result in
*
*    1 -> 3 -> 4 -> 8 -> 9 -> 10 -> 11 -> 13 -> 20
*
**********************************************************************************/
ListNode* Solution::mergeKLists(vector<ListNode*> &A) {
    // Do not write main() function.
    // Do not read input, instead use the arguments to the function.
    // Do not print the output, instead return values as specified
    // Still have a doubt. Checkout www.interviewbit.com/pages/sample_codes/ for more details

        ListNode* root = NULL;
        ListNode* current = root;
        int sz = A.size();
        if(sz == 0) return root;

        vector<pair<int,int>> vp;
        for(int i =0; i < sz; i++)
        {
            if(A[i] != NULL)
            {
                vp.push_back(make_pair(A[i]->val, i));
                A[i] = A[i]->next;
            }
        }

        auto comp = [](const pair<int,int>& f, const pair<int,int>& s){
            return f.first > s.first;
        };

        priority_queue<pair<int,int>, vector<pair<int,int>>, decltype(comp)> pq (vp.begin(), vp.end(), comp);

        while(!pq.empty())
        {
            pair<int,int> topPair = pq.top();
            ListNode *temp = new ListNode(topPair.first);
            if(root == NULL)
            {
                root = temp;
            }
            else
                current->next = temp;
            current = temp;
            pq.pop();

            if(A[topPair.second] != NULL)
            {
                pq.push(make_pair(A[topPair.second]->val, topPair.second));
                A[topPair.second] = A[topPair.second]->next;
            }

        }

        return root;
}
