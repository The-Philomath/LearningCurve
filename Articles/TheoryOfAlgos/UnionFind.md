Union and Find algorithms used on the disjoint sets.

**Disjoint Sets**

Subsets which do not have any element in common are the Disjoint sets.
One element out of a subset will act as an id for the subset.

**Union**

If we have to perform an operation `Union(A,B)` then A and B joined/merged to same subset. id of one of the subset A or B becomes the id of subset formed after Union operation.

```cpp
void union(vector<int> Arr ,int A ,int B)
{
    int Id_A = getId(Arr, A);       
    int Id_B = getId(Arr, B);  
    Arr[ Id_A ] = Id_B ;       //setting id of getId(A) as getId(B).
}
```
**Find**

`Find(A)` checks whether A is a part of a subset(say X) or not. If id of subset X is same as the id of subset to which A belongs then we can say that A is the part of subset X.

```cpp
bool find(int A, int B)
{
    return (getId(Arr, A) == getId(Arr, B));       //if A and B have same Id, means they belongs to same subset.
}
```

**MakeSet(x)**

There is one more operation i.e. MakeSet. If there is no set at all, it will create the set.

```cpp
//Arr stores which element belong to which subset by storing id of a subset at the elements's index.
//we should initialize all elements of vector Arr with its index.
//It means each element belongs to a subset of single element with id as self.
void initialize(vector<int>& Arr)
{
  for(int i = 0; i < Arr.size(); i++)
  {
    Arr[ i ] = i ;
  }
}

int getId(vector<int>& Arr, int i)
{
  while(i != Arr[i])
  {
    Arr[i] = Arr[Arr[i]]; // compressig the tree. It will flatten the tree and help to reduce the
                          // time consumed in further find operations. parent of all searched nodes got updated
    i = Arr[i];
  }
  return i;
}
```
A better approach would be [Weighted-Union Find](https://www.hackerearth.com/practice/notes/disjoint-set-union-union-find/)

----
**Uses**

**Kruskal’s Algorithm:**
Sort the edges in the given graph G by length and examine them from shortest to longest.
Put each edge into the current forest if it doesn’t form a cycle with the edges chosen so far.

The initial step in Kruskal is to sort edges on weight. It takes time O(|E| log |E|) to sort. Then, for each edge, we need to test if it connects two different components. If it does, we will insert the edge, merging the two components into one; if it doesn’t (the two endpoints are in the same component), then we will skip this edge and go on to the next edge. So, to do this efficiently we need a data structure that can support the basic operations of (a) determining if two nodes are in the same component, and (b) merging two components together.

* Union-Find is used to determine the connected components in a graph.

#### References
[cmu lectures](https://www.cs.cmu.edu/~avrim/451f13/lectures/lect0912.pdf)

### Authors

* **The Philomath**
