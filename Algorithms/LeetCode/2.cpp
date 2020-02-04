// Problem : https://leetcode.com/problems/linked-list-cycle/
// Author  : The Philomath
// Date    : 04-02-2020

/**********************************************************************************
*    You are given two non-empty linked lists representing two non-negative integers.
*    The digits are stored in reverse order and each of their nodes contain a single digit.
*    Add the two numbers and return it as a linked list.
*
*    You may assume the two numbers do not contain any leading zero, except the number 0 itself.
*
*    Example:
*
*    Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
*    Output: 7 -> 0 -> 8
*    Explanation: 342 + 465 = 807.
**********************************************************************************/
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        std::function<int(ListNode*)> func = [](ListNode * l) {
            int count = 0;
            while(l != NULL) {
                l=l->next; count++;
            }
            return count;
        };
        int len1 = func(l1);
        int len2 = func(l2);

        if(len1 < len2)
        {
            ListNode *big;
            big = l2;
            l2 = l1;
            l1 = big;
        }
        ListNode *big = l1;
        ListNode *temp = NULL;
        int carry = 0;
        while(l1 != NULL)
        {
            int val = (l2 != NULL) ? l2->val : 0;
            l1->val = l1->val + val + carry;
            carry = l1->val/10;
            l1->val = l1->val%10;
            if(l1->next == NULL) temp = l1;
            l1 = l1->next;
            if(l2 != NULL)
            l2 = l2->next;
        }

        if(carry)
        {
            ListNode *newNode = new ListNode(carry);
            temp->next = newNode;
        }
        return big;
    }
};
