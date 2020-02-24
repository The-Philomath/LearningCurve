// Problem : https://leetcode.com/problems/merge-k-sorted-lists/
// Author  : The Philomath
// Date    : 24-02-2020

/**********************************************************************************
*
*    Merge k sorted linked lists and return it as one sorted list. Analyze and describe its complexity.
*
*    Example:
*
*    Input:
*    [
*      1->4->5,
*      1->3->4,
*      2->6
*    ]
*    Output: 1->1->2->3->4->4->5->6
*
**********************************************************************************/
class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {

        ListNode* root = NULL;
        ListNode* current = root;
        int sz = lists.size();
        if(sz == 0) return root;

        vector<pair<int,int>> vp;
        for(int i =0; i < sz; i++)
        {
            if(lists[i] != NULL)
            {
                vp.push_back(make_pair(lists[i]->val, i));
                lists[i] = lists[i]->next;
            }
        }

        auto comp = [](auto f, auto s){
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

            if(lists[topPair.second] != NULL)
            {
                pq.push(make_pair(lists[topPair.second]->val, topPair.second));
                lists[topPair.second] = lists[topPair.second]->next;
            }

        }

        return root;
    }
};
