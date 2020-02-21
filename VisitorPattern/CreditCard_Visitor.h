#include <iostream>
#include <string>

using namespace std;

class Visitor;

class CreditCardType
{
    public:
        virtual string getName() = 0;
        virtual void accept(Visitor* v) = 0;
};

class Visitor
{
    public:
        virtual void visitCreditCard(CreditCardType *card, string cardType) = 0;
};