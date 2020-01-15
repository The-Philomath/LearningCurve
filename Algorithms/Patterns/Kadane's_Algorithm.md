# Steps
Largest Sum Contiguous Subarray

Write an efficient program to find the sum of contiguous subarray within a one-dimensional array of numbers which has the largest sum.

Simple idea of the **Kadane’s algorithm** is to look for all positive contiguous segments of the array (`maxSum_curr` is used for this).
And keep track of maximum sum contiguous segment among all positive segments (`maxSum` is used for this).
Each time we get a positive sum compare it with `maxSum` and update `maxSum` if it is greater than `maxSum`

Initialize:

    maxSum = 0
    maxSum_curr = 0

Loop for each element of the array

  (a)

       maxSum_curr = maxSum_curr + a[i]

  (b)

      if(maxSum_curr < 0)
            maxSum_curr = 0

  (c)

      if(maxSum < maxSum_curr)
            maxSum = maxSum_curr
      return maxSum

This will only work if there is at least one positive element in array

#### Problems


### Authors

* **The Philomath**
