#include <iostream>
#include <string>
using namespace std;

/*
1. Bridge pattern decouple an abstraction from its implementation so that the two can vary independently.
2. It is used mainly for implementing platform independence feature.
3. It adds one more method level redirection to achieve the objective.
4. Use bridge pattern to run-time binding of the implementation.
5. Use bridge pattern to map orthogonal class hierarchies
6. Bridge is designed up-front to let the abstraction and the implementation vary independently.

eg: Suppose there are Class car which generates different cars. Now cars have many attributes like color etc.
    So there has to be a Class color which generates different colors independent of Class car.
    Also, Class car composes Class color.
*/

#define interface struct

// This is the item to be composed
interface CarColor
{
    virtual void paintColor(string color) = 0;
};

class MetallicColor : public CarColor
{
    public:
        void paintColor(string color)
        {
            cout<<"Color type: "<<color<<" Metallic chosen\n";
        }
};

class MatteColor : public CarColor
{
    public:
        void paintColor(string color)
        {
            cout<<"Color type: "<<color<<" Matte chosen\n";
        }
};

//This is the class which composes
class CarManufacturer
{
    protected:
        CarColor* carColor; //Composition happened here
    public:
        void setColor(CarColor* color)
        {
            this->carColor = color; //bridge got created here
        }
        
        virtual void paintCar(string color) = 0;
};

class Hyundai : public CarManufacturer
{
    public:
        void paintCar(string color)
        {
            cout<<"Hyundai car painting started\n";
            carColor->paintColor(color);
        }
};

class Maruti : public CarManufacturer
{
    public:
        void paintCar(string color)
        {
            cout<<"Maruti car painting started\n";
            carColor->paintColor(color);
        }
};

int main()
{
    CarManufacturer* carManufacturer = new Hyundai();
    carManufacturer->setColor(new MetallicColor());
    carManufacturer->paintCar("Blue");

    carManufacturer = new Maruti();
    carManufacturer->setColor(new MatteColor());
    carManufacturer->paintCar("Red");

    return 0;
}