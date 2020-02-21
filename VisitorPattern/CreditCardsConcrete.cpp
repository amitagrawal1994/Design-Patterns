#include <iostream>
#include <string>
#include "CreditCard_Visitor.h"

using namespace std;

class BronzeCreditCard : public CreditCardType
{
    public:
        string getName()
        {
            return "Bronze";
        }

        void accept(Visitor* v)
        {
            v->visitCreditCard(this, "Bronze");
        }
};

class SilverCreditCard : public CreditCardType
{
    public:
        string getName()
        {
            return "Silver";
        }

        void accept(Visitor* v)
        {
            v->visitCreditCard(this, "Silver");
        }
};

class GoldCreditCard : public CreditCardType
{
    public:
        string getName()
        {
            return "Gold";
        }

        void accept(Visitor* v)
        {
            v->visitCreditCard(this, "Gold");
        }
};

class GasOffer : public Visitor
{
    void visitCreditCard(CreditCardType* card, string cardType)
    {
       if(cardType == "Bronze")
       {
           cout<<"GasOffer for Bronze class has been selected \n";
       } 
       if(cardType == "Silver")
       {
           cout<<"GasOffer for Silver class has been selected \n";
       } 
       if(cardType == "Gold")
       {
           cout<<"GasOffer for Gold class has been selected \n";
       } 
    }
};

class HotelOffer : public Visitor
{
    void visitCreditCard(CreditCardType* card, string cardType)
    {
       if(cardType == "Bronze")
       {
           cout<<"HotelOffer for Bronze class has been selected \n";
       } 
       if(cardType == "Silver")
       {
           cout<<"HotelOffer for Silver class has been selected \n";
       } 
       if(cardType == "Gold")
       {
           cout<<"HotelOffer for Gold class has been selected \n";
       } 
    }
};

int main()
{
    CreditCardType* bronze = new BronzeCreditCard;
    CreditCardType* silver = new SilverCreditCard;
    CreditCardType* gold = new GoldCreditCard;

    Visitor* hotelOffer = new HotelOffer;
    Visitor* gasOffer = new GasOffer;

    bronze->accept(hotelOffer);
    silver->accept(hotelOffer);
    gold->accept(hotelOffer);

    bronze->accept(gasOffer);
    silver->accept(gasOffer);
    gold->accept(gasOffer);

    return 0;
}