#include <iostream>
using namespace std;

/*
1. The Chain of Responsibility is known as a behavioral pattern. 
2. The main objective of this pattern is that it avoids coupling the sender of the request to the receiver, giving more than one object the opportunity to handle the request.
3. This pattern is recommended when multiple objects can handle a request and the handler doesn’t have to be a specific object. Also, handler is determined at runtime.

e.g:
ATM machine can dispense notes of Rs 100, 200, 500 and 2000. If a request comes to dispense 4800, it should get dispensed as 
2 * 2000, 1 * 500, 1 * 200 and 1 * 100.
*/

int totalCash;

// Abstract class
class DispenseCash
{
    protected:
        DispenseCash* nextCashMachine;
        int capacity;
        virtual void passToNextChain(int amount)
        {
            this->nextCashMachine->dispenseCash(amount);
        }

    public:
        virtual void dispenseCash(int amount) = 0;
        virtual void setNextCashMachine(DispenseCash* nextCashMachine)
        {
            this->nextCashMachine = nextCashMachine;
        }

        virtual void setCapacity(int cashQuantity)
        {
            this->capacity = cashQuantity;
        }
};

//Concrete class which releases 2000 notes. 1st in chain
class Dispense2000notes : public DispenseCash
{
    public:
        void dispenseCash(int amount)
        {
            if(amount/2000 > this->capacity)
            {
                cout<<"Dispensing 2000 notes. Count: "<<this->capacity<<endl;
                totalCash = totalCash - (amount - this->capacity*2000);
                passToNextChain(amount - this->capacity*2000); //pass the logic to next chain
                this->capacity = 0;
            }
            else
            {
                int numberOfNotes = amount/2000;
                cout<<"Dispensing 2000 notes. Count: "<<numberOfNotes<<endl;
                this->capacity -= numberOfNotes;
                passToNextChain(amount-(numberOfNotes*2000));
            }
        }
};

//2nd in chain
class Dispense500notes : public DispenseCash
{
    public:
        void dispenseCash(int amount)
        {
            if(amount/500 > this->capacity)
            {
                cout<<"Dispensing 500 notes. Count: "<<this->capacity<<endl;
                passToNextChain(amount - this->capacity*500);
                this->capacity = 0;
            }
            else
            {
                int numberOfNotes = amount/500;
                cout<<"Dispensing 500 notes. Count: "<<numberOfNotes<<endl;
                this->capacity -= numberOfNotes;
                passToNextChain(amount-(numberOfNotes*500));
            }
        }
};

//3rd in chain
class Dispense200notes : public DispenseCash
{
    public:
        void dispenseCash(int amount)
        {
            if(amount/200 > this->capacity)
            {
                cout<<"Dispensing 200 notes. Count: "<<this->capacity<<endl;
                passToNextChain(amount - this->capacity*200);
                this->capacity = 0;
            }
            else
            {
                int numberOfNotes = amount/200;
                cout<<"Dispensing 200 notes. Count: "<<numberOfNotes<<endl;
                this->capacity -= numberOfNotes;
                passToNextChain(amount-(numberOfNotes*200));
            }
        }
};

//4th in chain
class Dispense100notes : public DispenseCash
{
    public:
        void dispenseCash(int amount)
        {
            if(amount/100 > this->capacity)
            {
                cout<<"Dispensing 100 notes. Count: "<<this->capacity<<endl;
                passToNextChain(amount - this->capacity*100);
                this->capacity = 0;
            }
            else
            {
                int numberOfNotes = amount/100;
                cout<<"Dispensing 100 notes. Count: "<<numberOfNotes<<endl;
                this->capacity -= numberOfNotes;
                passToNextChain(amount-(numberOfNotes*100));
            }
        }
};

int main()
{
    DispenseCash* dispense2000Cash = new Dispense2000notes;
    DispenseCash* dispense500Cash = new Dispense500notes;
    DispenseCash* dispense200Cash = new Dispense200notes;
    DispenseCash* dispense100Cash = new Dispense100notes;

    dispense2000Cash->setCapacity(10);
    totalCash = totalCash + (2000 * 10);
    dispense500Cash->setCapacity(100);
    totalCash = totalCash + (500 * 100);
    dispense200Cash->setCapacity(200);
    totalCash = totalCash + (200 * 200);
    dispense100Cash->setCapacity(100);
    totalCash = totalCash + (100 * 100);

    //Make the chain. 1st from 2000 -> 500 -> 200 -> 100
    dispense2000Cash->setNextCashMachine(dispense500Cash);
    dispense500Cash->setNextCashMachine(dispense200Cash);
    dispense200Cash->setNextCashMachine(dispense100Cash);

    int amount = 0;
    while(amount != -1)
    {
        cin>>amount;

        if(amount <= totalCash)
        {
            //trigger the withdrawal
            dispense2000Cash->dispenseCash(amount);
            totalCash = totalCash - amount;
        }
        else
        {
            cout<<"Not enough cash\n";
        }
    }
    
    return 0;
}