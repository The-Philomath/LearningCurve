A factory can be implemented in a number of ways. This is how to define it as inner factory.

```cpp
class Point{
   int x, y;
   Point(int x, int y):x(x),y(y){}
   public:
   class PointFactory{
       PointFactory(){}
       public:
       static Point getSimplePoint(int x, int y)
       {
           return {x, y};
       }
       static Point getComplexPoint(int x, int y)
       {
           return {x+90, y+90};
       }
   };
};
int main()
{
    auto p = Point::PointFactory::getSimplePoint(3,4);
    return 0;
}
```
