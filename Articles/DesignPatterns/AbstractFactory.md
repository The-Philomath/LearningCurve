```cpp
class HotDrink{
    public:
    virtual ~HotDrink()= default;
    virtual void prepare(int volume)=0;
};

class Coffee: public HotDrink
{
    public:
    void prepare(int volume) override{
        std::cout<<"coffe prepared "<<volume<<"ml\n";
    }
};

class Tea: public HotDrink
{
    public:
    void prepare(int volume) override{
        std::cout<<"tea prepared "<<volume<<"ml\n";
    }
};

class HotDrinkFactory
{
    public:
    virtual std::unique_ptr<HotDrink> make() const =0;
};

class CoffeeFactory: public HotDrinkFactory{
    public:
    std::unique_ptr<HotDrink> make() const override{
        return std::make_unique<Coffee>();
    }
};

class TeaFactory: public HotDrinkFactory{
    public:
    std::unique_ptr<HotDrink> make() const override{
        return std::make_unique<Tea>();
    }
};

class DrinkFactory{
    std::map<std::string, std::unique_ptr<HotDrinkFactory>> hot_factories;
    public:
    DrinkFactory()
    {
        hot_factories["tea"] = std::make_unique<TeaFactory>();
        hot_factories["coffee"] = std::make_unique<CoffeeFactory>();
    }
    std::unique_ptr<HotDrink> make_drink(std::string drink_type)
    {
        auto drink = hot_factories[drink_type]->make();
        drink->prepare(200);
        return drink;
    }
};
std::unique_ptr<HotDrink> make_drink(std::string drink_type)
{
    std::unique_ptr<HotDrink> drink;
    if(drink_type == "tea")
    {
        drink = std::make_unique<Tea>();
        drink->prepare(200);
    }
    else
    {
        drink = std::make_unique<Coffee>();
        drink->prepare(50);
    }

    return drink;
}
int main()
{
    auto d = make_drink("tea");

    DrinkFactory df;
    df.make_drink("coffee");
    return 0;
}
```
