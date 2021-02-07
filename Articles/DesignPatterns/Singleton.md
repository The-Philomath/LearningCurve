```cpp
class Singleton{
    int resource;
    public:
    static Singleton& get_obj()
    {
         static Singleton obj;
         return obj;
    }
    private:
    ~Singleton(){}
    Singleton() = default;
    Singleton(const Singleton &) = delete;
    Singleton(Singleton &&)= delete;
    Singleton& operator =(const Singleton &) = delete;
    Singleton& operator =(const Singleton &&) = delete;
};
```
