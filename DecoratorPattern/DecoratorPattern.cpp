#include <iostream>
#include <string>
using namespace std;

/*
1. We have an object that requires the extension e. a window control that requires additional “optional” features like scrollbars, titlebar and statusbar.
2. Several objects that support the extension by “decoration”. Usually, those objects share a common interface, traits, or superclass, and sometimes, additional, intermediate super-classes .
3. The decorated object (class or prototype instantiation), and the decorator objects have one or several common features.
   In order to ensure that functionality, the decorated object & the decorators have a common interface, traits, or class inheritance.

   eg:
   There is a milkshake and you want to add toppings like chocolate, strawberry, chocochips etc.
   The cost will be addition of all the components i.e toppings decorates base milkshake
*/

//Top level product
struct Beverage
{
    //functions which wouyld get decorated
    virtual double cost() = 0;
    virtual string description() = 0;
};

// Concrete base class 1
class Milkshake : public Beverage
{
    public:
        double cost()
        {
            return 10;
        }

        string description()
        {
            return "Milkshake";
        }
};

// Concrete base class 2
class Thickshake : public Beverage
{
    public:
        double cost()
        {
            return 20;
        }

        string description()
        {
            return "Thickshake";
        }
};

//Decorator class - extends Beverage
class Toppings : public Beverage
{
    string description = "Toppings";    
};

//Concrete Decorator class - "is a" Beverage and "has a" Beverage
class Chocolate : public Toppings
{
    Beverage* beverage;
    public:
        Chocolate(Beverage* beverage)
        {
            this->beverage = beverage;
        }

        string description()
        {
            return "Chocolate+"+beverage->description(); // retuns its attribute + inherited attribute
        }

        double cost()
        {
            return (5 + beverage->cost()); // retuns its attribute + inherited attribute
        }
};

//Concrete Decorator class - "is a" Beverage and "has a" Beverage
class Strawberry : public Toppings
{
    Beverage* beverage;
    public:
        Strawberry(Beverage* beverage)
        {
            this->beverage = beverage;
        }

        string description()
        {
            return "Strawberry+"+beverage->description();
        }

        double cost()
        {
            return (8 + beverage->cost());
        }
};

//Concrete Decorator class - "is a" Beverage and "has a" Beverage
class Chocochips : public Toppings
{
    Beverage* beverage;
    public:
        Chocochips(Beverage* beverage)
        {
            this->beverage = beverage;
        }

        string description()
        {
            return "Chocochips+"+beverage->description();
        }

        double cost()
        {
            return (3 + beverage->cost());
        }
};

//Concrete Decorator class - "is a" Beverage and "has a" Beverage
class Icecream : public Toppings
{
    Beverage* beverage;
    public:
        Icecream(Beverage* beverage)
        {
            this->beverage = beverage;
        }

        string description()
        {
            return "Icecream+"+beverage->description();
        }

        double cost()
        {
            return (10 + beverage->cost());
        }
};

int main()
{
    Beverage* beverage = new Milkshake(); //create base concrete class
    beverage = new Strawberry(beverage); // Decorator no. 1
    beverage = new Chocochips(beverage); //Decorator no. 2
    cout<<beverage->description()<<" cost:"<<beverage->cost()<<endl;

    beverage = new Thickshake();
    beverage = new Chocolate(beverage);
    beverage = new Chocochips(beverage);
    beverage = new Icecream(beverage);
    cout<<beverage->description()<<" cost:"<<beverage->cost()<<endl;

    return 0;
}