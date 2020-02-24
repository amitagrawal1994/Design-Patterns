// Abstract factory is all about creating more than one products or 
// a set of related products in a single factory.
#include <iostream>
#include <string>
using namespace std;

#define interface struct

/* Factory to create a set of ingredients for a Pizza type */
interface IngredientCreatorFactory
{
    virtual void getPizzaBase() = 0;
    virtual void getCheese() = 0;
    virtual void getToppings() = 0;
};

/* Factory to get concrete products - interface between Pizza and Concrete Products*/
interface PizzaIngredientFactory
{
    virtual void createPizzaBase() = 0;
    virtual void createPizzaCheese() = 0;
    virtual void createPizzaTopping() = 0;
};

class ThinCrustPizzaBase : public IngredientCreatorFactory
{
    public:
        void getPizzaBase()
        {
            cout<<"Thin Crust Pizza Base has been selected\n";
        }

        void getCheese(){};
        void getToppings(){};
};

class ThickCrustPizzaBase : public IngredientCreatorFactory
{
    public:
        void getPizzaBase()
        {
            cout<<"Thick Crust Pizza Base has been selected\n";
        }

        void getCheese(){};
        void getToppings(){};
};

class CheddarCheese : public IngredientCreatorFactory
{
    public:
        void getCheese()
        {
            cout<<"Cheddar Cheese has been selected\n";
        }

        void getPizzaBase(){};
        void getToppings(){};
};

class ParmesanCheese : public IngredientCreatorFactory
{
    public:
        void getCheese()
        {
            cout<<"Parmesan Cheese has been selected\n";
        }

        void getPizzaBase(){};
        void getToppings(){};
};

class LightTopping : public IngredientCreatorFactory
{
    public:
        void getToppings()
        {
            cout<<"Light Toppings has been selected\n";
        }

        void getPizzaBase(){};
        void getCheese(){};
};

class HeavyTopping : public IngredientCreatorFactory
{
    public:
        void getToppings()
        {
            cout<<"Heavy Toppings has been selected\n";
        }

        void getPizzaBase(){};
        void getCheese(){};
};

class NYPizzaIngredient : public PizzaIngredientFactory
{
    public:
        void createPizzaBase()
        {
            IngredientCreatorFactory* nyPizzaBase = new ThinCrustPizzaBase();
            nyPizzaBase->getPizzaBase();
        }

        void createPizzaCheese()
        {
            IngredientCreatorFactory* nyPizzaCheese = new CheddarCheese();
            nyPizzaCheese->getCheese();
        }

        void createPizzaTopping()
        {
            IngredientCreatorFactory* nyPizzaTopping = new LightTopping();
            nyPizzaTopping->getToppings();
        }
};

class ChicagoPizzaIngredient : public PizzaIngredientFactory
{
    public:
        void createPizzaBase()
        {
            IngredientCreatorFactory* chicagoPizzaBase = new ThickCrustPizzaBase();
            chicagoPizzaBase->getPizzaBase();
        }

        void createPizzaCheese()
        {
            IngredientCreatorFactory* chicagoPizzaCheese = new ParmesanCheese();
            chicagoPizzaCheese->getCheese();
        }

        void createPizzaTopping()
        {
            IngredientCreatorFactory* chicagoPizzaTopping = new HeavyTopping();
            chicagoPizzaTopping->getToppings();
        }
};

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
            PizzaIngredientFactory* nyPizzaIngredientHandler = new NYPizzaIngredient();
            nyPizzaIngredientHandler->createPizzaBase();
            nyPizzaIngredientHandler->createPizzaCheese();
            nyPizzaIngredientHandler->createPizzaTopping();
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
            PizzaIngredientFactory* chicagoPizzaIngredientHandler = new ChicagoPizzaIngredient();
            chicagoPizzaIngredientHandler->createPizzaBase();
            chicagoPizzaIngredientHandler->createPizzaCheese();
            chicagoPizzaIngredientHandler->createPizzaTopping();
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