// Problem : https://leetcode.com/problems/linked-list-cycle/
// Author  : The Philomath
// Date    : 04-02-2020

/**********************************************************************************
*    Given a linked list, determine if it has a cycle in it.
*
*    To represent a cycle in the given linked list,
*    we use an integer pos which represents the position (0-indexed) in the linked list where tail connects to.
*    If pos is -1, then there is no cycle in the linked list.
*
*    Example 1:
*
*    Input: head = [3,2,0,-4], pos = 1
*    Output: true
*    Explanation: There is a cycle in the linked list, where tail connects to the second node.
**********************************************************************************/
//Iterative
class Solution {
public:
    bool hasCycle(ListNode *head) {
        ListNode* slow = head;
        ListNode* fast = head;
        if(slow == NULL || slow->next == NULL) return false;
        do
        {
            slow = slow->next;
            fast = fast->next->next;
        }while(slow != fast && fast != NULL && fast->next != NULL);

        if(slow == fast) return true;
        return false;
    }
};

//Recursive
class Solution {
public:
    bool hasCycle(ListNode *head) {

        if(head == NULL || head->next == NULL) return false;

        return hasCycleRecur(head, head->next);
    }
    bool hasCycleRecur(ListNode *slow, ListNode *fast)
    {
        if(fast == NULL || fast->next == NULL) return false;

        if(slow == fast) return true;
        return hasCycleRecur(slow->next, fast->next->next);
    }
};
