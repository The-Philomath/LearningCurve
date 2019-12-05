## About
Better understanding of placement new help in better memory handling and avoiding memory related issues. let's dig into it.


Syntax of a new expression
```cpp
new (placement_params) ( type ) initializer
```

In new expression if the placement_params are not NULL and an already allocated memory reference is provided then its known as a placement new.

**Example:-**
```cpp
#include <iostream>

class IntValue
{
    int val;
public:
    IntValue(int a):val(a)
    {
        std::cout << "IntValue constructor called" << std::endl;
    }
    ~IntValue()
    {
        std::cout << "IntValue destructor called" << std::endl;
    }
};

int main()
{
    int buff[20];
    IntValue *a = new(buff)IntValue(3); //Allocate an integer at the base address of buff array.

    system("pause");
    return 0;
}
```

**Never try to call delete on pointer which was allocated by placement new**

As it is not the responsibility of the pointer('a' in this example) to release the memory. We don't know for sure whether the source buffer was allocated from heap or stack.

**Output:-**

_IntValue constructor called_

We can see that the destructor is not getting called. So any resource which was allocated in the constructor will never get released. To release the resource we should explicitly call destructor.

```cpp
a->~IntValue();
```


### Authors

* **The Philomath**
