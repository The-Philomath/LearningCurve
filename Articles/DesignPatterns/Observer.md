## About

Observer defines a one to many relation. Once a subject's state changes all the observers are notified. It's a subscribe notify relation.

Here subject(observable) keep track of its observers and notify them by calling their update(field_changed) functions.
It can work either as a push or pull means either the subject send all information or after getting notification observer ask for the information.

One advantage of this pattern is that there is minimum coupling between subject and observer.
```cpp
template<typename T>
class observer{
    public:
    virtual void field_changed(
        T& source,
        const std::string field_name
    )=0;
};

template<typename T>
class observable{

    std::vector<observer<T> *> observers;

    public:  
    void notify(T& source, const std::string field_name){
        for(auto observer: observers)
        {
            observer->field_changed(source, field_name);
        }
    }

    void subscribe(observer<T>& ob)
    {
        observers.push_back(&ob);
    }
    void unsubscribe(observer<T>& ob)
    {
        std::erase(std::remove(observers.begin(), observers.end(), &ob),
             observers.end());
    }
};

class Person : public observable<Person>
{
    int age{0};
    public:
    Person(){}
    Person(int age):age(age){}

    int get_age() const{
        return age;
    }

    void set_age(int age){
        if(this->age == age) return;
        this->age = age;
        notify(*this, "age");
    }
};

class TrafficAdmin: public observer<Person>
{
    public:
    virtual void field_changed(Person &source, const std::string field_name) override
    {
        if(field_name == "age")
        {
            if(source.get_age()<17)
            {
                std::cout<<"can't drive man\n";
            }
        }
    }
};
int main()
{
    Person P;
    TrafficAdmin ta;
    P.subscribe(ta);
    P.set_age(10);
    return 0;
}
```
