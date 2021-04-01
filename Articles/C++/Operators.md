#### Pointer-to-Member Operators

`.*` and `->*`

The pointer-to-member operators return the value of a specific class member for the object specified on the left side of the expression. The right side must specify a member of the class.

```cpp
class test
{
    public:
    void tempfunc(){std::cout<<"here";}
    int var;
};

void(test::*ptr)() = &test::tempfunc;
int test::*mpt = &test::var;

int main()
{
    test obj;
    obj.*mpt = 20;
    (obj.*ptr)();  //"here"
    return 0;
}
```
The binary operator .* combines its first operand, which must be an object of class type, with its second operand, which must be a pointer-to-member type.

The binary operator ->* combines its first operand, which must be a pointer to an object of class type, with its second operand, which must be a pointer-to-member type.


https://docs.microsoft.com/en-us/cpp/cpp/pointer-to-member-operators-dot-star-and-star?view=msvc-160
