#include <iostream>
#include <string>

using namespace std;

/*
1. Prototype pattern involves creating new objects by copying existing objects. The object whose copies are made is called the prototype.
2. Prototype design pattern is used in scenarios where application needs to create a number of instances of a class, which has almost same state or differs very little.
3. In this design pattern, an instance of actual object (i.e. prototype) is created on starting, and thereafter whenever a new instance is required, this prototype is cloned to have another instance. 
4. The main advantage of this pattern is to have minimal instance creation process which is much costly than cloning process.
5. Formally, the pattern is defined as specify the kind of objects to create using a prototypical instance as a model and making copies of the prototype to create new objects.

e.g:
Lets say we operate a bread factory where the base bread is same but 10 varieties can be created just by changing 1 ingredient.
Also it produces thousands of bread. So in place of creating new breads everytime, we create a single prototype bread and copy it everytime.
*/
// one good example of this is maintaining birth register for all people who got birth in the hospital
// city, state, country and pin of place of birth will remain same. Just DOB and Name will be different.
// So we do not need extra memory for the variable which have to be shared.

//Prototype class
class PrototypeBread
{
    public:
        virtual PrototypeBread* clone() = 0;
        virtual void setBase(string base) = 0;
        virtual void setStore(string store) = 0;
        virtual void bakeBread() = 0;
};

//base prototype
class BaseBread : public PrototypeBread
{
    string base = "Normal";
    string* store;
    public:
        BaseBread(BaseBread* originalBread)
        {
            store = originalBread->store; //shallow copy - does not create a new memory location for pointers
        }

        BaseBread()
        {
        }

        PrototypeBread* clone()
        {
            return new BaseBread(this); //shallow copy - pointers will be pointing to same location - eg: default copy constructor
        }

        void setBase(string base)
        {
            this->base = base;
        }

        void setStore(string store)
        {
            this->store = new string;
            *(this->store) = store;
        }

        void bakeBread()
        {
            //here base will be unique to each obj but store will be common(pointing to same location)
            cout<<"Baking bread of base: "<<this->base<<" at store: "<<*(this->store)<<endl;
        }
};

int main()
{
    PrototypeBread* baseBread = new BaseBread;
    baseBread->setStore("Subway");
    baseBread->bakeBread();

    PrototypeBread* garlicBread = baseBread->clone(); // we are copying from existing object
    garlicBread->setBase("Garlic");
    garlicBread->bakeBread();

    PrototypeBread* honeyBread = baseBread->clone();
    honeyBread->setBase("Honey");
    honeyBread->bakeBread();

    return 0;
}