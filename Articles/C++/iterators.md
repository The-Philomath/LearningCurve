## About
Iterators are the classes whose objects are used to iterates over the containers.

Just as templates make algorithm independent of the type of data stored, iterators make the algorithms independent of the type of container used. The iterators provide a generic representation of the process of moving through the values in a container.

Think of them in terms of ordinary pointers used to iterate over the arrays. Though pointers also have the same properties listed above, there is a difference between pointer and iterators. The difference is that iterators may be smart pointers.

Different algorithms have different requirements for iterators. A `find()` algorithm needs the ++ operator to be defined so the iterator can step through the container. It does not need write access but it needs read access.
```cpp
template<class InputIterator, class T>
InputIterator find(InputIterator first, InputIterator last, const T& value);
```
The `sort()` algorithm, on the other hand, requires random access so that it can swap the two non-adjacent elements.
```cpp
template<class RandomAccessIterator>
void sort(RandomAccessIterator first, RandomAccessIterator last);
```

**Iterator types:-**
Hierarchal order

    i) Input iterators
    ii) Output Iterators
    iii) Forward Iterators
    iv) Bidirectional iterators
    v) Random access Iterators

**Input Iterators**

Dereferencing an input iterator allows us to read a value from a container, but it does not allow us to alter the value. So algorithms that require an input iterator are algorithms that don't modify values of the container elements.

**Output Iterators**

Single-pass and write-only iterator.

**Forward Iterators**

A multi pass iterator can only go forward through a container one element at a time.

**Bidirectional Iterators**

A bidirectional iterator has all the features of a forward iterator and adds support for the two decrement operators (prefix and postfix).

**Random Access Iterator**

This type of iterator has all the features of a bidirectional iterator, plus it adds operations such as pointer addition that support random access and relational operations for those of a bidirectional iterators.

**const_iterator**

A const_iterator is equivalent to pointer to a constant. Iterator itself can change its value but not the underlying element.

#### References
[BogoToBogo](https://www.bogotobogo.com/cplusplus/stl3_iterators.php)

### Authors

* **The Philomath**
