# Steps
Its used to check whether an element have more number of occurrences than any other element.

Basic idea of the algorithm is that if we cancel out each occurrence of an element e with all the other elements that are different from e then e will exist till end if it have more number of occurrences than any other element.

If there is a candidate with more than TotalCandidate/2 then below algo will find out that candidate.

findCandidate(a[], size)
1.  Initialize index and count of majority element

     maj_index = 0, count = 1
2.  Loop for i = 1 to size – 1

    (a) If a[maj_index] == a[i]
          count++
    (b) Else
        count--;
    (c) If count == 0
          maj_index = i;
          count = 1
3.  Return a[maj_index]

#### Problems
[N/3_RepeatNumber](../../Algorithms/InterviewBit/N3_Repeat_Number.cpp)

[majorityElement](https://www.geeksforgeeks.org/majority-element/)

### Authors

* **The Philomath**
