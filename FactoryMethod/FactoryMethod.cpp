#include <iostream>
#include <string>
using namespace std;

#define interface struct

// Pizza is the product here (producer side element)
interface Pizza
{
    virtual void prepare() = 0;
    virtual void bake() = 0;
    virtual void cut() = 0;
    virtual void box() = 0;
};

// Concrete implementation of product
class NYStyleCheesePizza : public Pizza
{
    public:
        void prepare()
        {
            cout<<"Preparing NY Style Cheese Pizza \n";
        }
        void bake()
        {
            cout<<"Baking NY Style Cheese Pizza \n";
        }
        void cut()
        {
            cout<<"Cutting NY Style Cheese Pizza \n";
        }
        void box()
        {
            cout<<"Putting NY Style Cheese Pizza in a box\n";
        }
};

// Concrete implementation of product
class ChicagoStyleCheesePizza : public Pizza
{
    public:
        void prepare()
        {
            cout<<"Preparing Chicago Style Cheese Pizza \n";
        }
        void bake()
        {
            cout<<"Baking Chicago Style Cheese Pizza \n";
        }
        void cut()
        {
            cout<<"Cutting Chicago Style Cheese Pizza \n";
        }
        void box()
        {
            cout<<"Putting Chicago Style Cheese Pizza in a box\n";
        }
};

// Creator
interface PizzaStoreFactory
{
    //factory method returns "product" which is pizza here
    virtual Pizza* createPizza() = 0;
    virtual void orderPizza() = 0;
};

//Concrete creator
class NYStoreFactory : public PizzaStoreFactory
{
    public:
    void orderPizza()
    {
        cout<<"Order placed for NY style cheese pizza\n";
        Pizza* pizza = this->createPizza();
    }

    private:
    Pizza* createPizza()
    {
        Pizza* nyPizza = new NYStyleCheesePizza();
        nyPizza->prepare();
        nyPizza->bake();
        nyPizza->cut();
        nyPizza->box();
    }
};

//Concrete creator
class ChicagoStoreFactory : public PizzaStoreFactory
{
    public:
    void orderPizza()
    {
        cout<<"Order placed for Chicago style cheese pizza\n";
        Pizza* pizza = this->createPizza();
    }

    private:
    Pizza* createPizza()
    {
        Pizza* chicagoPizza = new ChicagoStyleCheesePizza();
        chicagoPizza->prepare();
        chicagoPizza->bake();
        chicagoPizza->cut();
        chicagoPizza->box();
    }
};

int main()
{
    PizzaStoreFactory* nyPizzaFactory = new NYStoreFactory();
    PizzaStoreFactory* chicagoPizzaFactory = new ChicagoStoreFactory();
    nyPizzaFactory->orderPizza();
    chicagoPizzaFactory->orderPizza();
}