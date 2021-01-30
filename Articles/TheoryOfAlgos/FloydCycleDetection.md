## About

* Traverse linked list using two pointers.
* Move one pointer by one and another pointer by two.
* If these pointers meet at the same node then there is a loop. If pointers do not meet then linked list doesn’t have a loop.

```cpp
bool detectLoop(Node* list)
{
    Node *slow = list, *fast = list;

    while (slow && fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {
            return true;
        }
    }
    return false;
}
```

Happy Number

### Authors

* **The Philomath**
