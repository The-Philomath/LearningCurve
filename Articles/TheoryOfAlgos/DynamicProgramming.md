## About
Basics of dynamic programming confuses sometimes. lets make them clear.

In **Top Down approach** we break down the problem in subsets in a recursive function and get the solutions when recursion unwind. We store the result(memoize) of smallers problem and get the solution for bigger ones. 

Its like a tree having multiple similar nodes. If we know the solution of one of the node (say A). We can use it as the solution of node B which has a similar tree structure as of Node A.

Memoization array size depends on the recursion factors which varies on each recursion. like in a 0-1 knapsack the current remaining capacity and weights.

```cpp

// mem[weight.size()][cap +1] will be a vetor which we can take globally or pass as a reference

int knapsack(vector<vector<int>>& mem, vector<int>& weight, value<int>& value, int i, int cap) {
    if(cap < 0) return INT_MIN;
 
    if(i == weight.size()) return 0;
    
    // check if the value for (i, cap) has already been computed
    if(mem[i][cap] != null) return mem[i][cap];
    
    // do not take item i
    double skip = knapsack(i + 1, cap);
    // take item i
    double take = value[i] + knapsack(i + 1, cap - weight[i]);
    
    // memorize the value of (i, cap)
    mem[i][cap] = std::max(skip, take);
    return mem[i][cap];
}
```

In **Bottom Up approach** we start with smallest subproblem of main probleem and solve it. Next time we will take a bigger subproblem and solve that with help of already known solutions. That means we are redefining the problem set at every step. Its an iterative approach unlike Top Down which is a recursive approach.

How to define a subproblem:-
smallest subproblem can be the base case. Like considering there is only one element at a time in a min-max problem.
or considering there is only one weight for a 0-1 knapsack problem.
either we can choose that if our capacity allow or we can't.

```
    prob(0,cap) = {value0 if weight0≤cap 
                     0    else
```

So for all the weights 0,1,...n we can define any ith subproblem like

```
    prob(i, cap) = max { valuei + prob(i-1, cap-weighti)   if weighti≤cap && consider weight
                               prob(i-1, cap)              else don't consider weight
```

0-1 Knpsack solution

```cpp
int knapsack(vector<int>& value, vector<int>& weight, int cap ) {
    vector<vector<int>> prob (weight.size(), vector<int>(cap+1, 0));
    int n = weight.size();
    
    // base cases
    for(int i = 0; i <= cap; i++) {
        prob[0][i] = cap - weight[0] >= 0 ? value[0] : 0;
    }
    
    for(int i = 1; i < n; i++) {
        for(int j = 0; j <= cap; j++) {
            int yes = j - weight[i] >= 0 ? value[i] + prob[i - 1][cap - weight[i]] : INT_MIN;
            int no = prob[i - 1][j];
            prob[i][j] = max(yes, no);
        }
    }
    return prob[n - 1][cap];
}
```

Further Reference:- https://inginious.org/course/competitive-programming/dp-memory-reduction
### Authors

* **The Philomath**
