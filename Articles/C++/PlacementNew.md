##About
Better understanding of placement new help in better memory handling and avoiding memory related issues. let's dig into it.


Syntax of a new expression
```cpp
new (placement_params) ( type ) initializer
```

In new expression if the placement_params are not NULL and an already allocated memory reference is povided then its known as a placement new.

