#include <iostream>
#include <string>
#include <list>
using namespace std;

class StockChangeSubject;

class StockObserver
{
    public:
        virtual void update(StockChangeSubject*) = 0;
};

class StockChangeSubject
{
    list <StockObserver*> stockObserver;

    protected:
        float stockValue;

    public:
        virtual float getStockValue() = 0;
        virtual void setStockValue(float newStockValue) = 0;

        void attachObserver(StockObserver* observer)
        {
            stockObserver.push_back(observer);
        }

        void detachObserver(StockObserver* observer)
        {
            stockObserver.remove(observer);
        }

        void notifyObservers()
        {
            list <StockObserver*>::iterator observerIterator;
            for(observerIterator = stockObserver.begin(); observerIterator != stockObserver.end(); observerIterator++)
            {
                if(*observerIterator != 0)
                {
                    (*observerIterator)->update(this);
                }
            }
        }
};

class QualcommStockChange : public StockChangeSubject
{
    public:
        float getStockValue()
        {
            return stockValue;
        }

        void setStockValue(float newStockvalue)
        {
            stockValue = newStockvalue;
            notifyObservers();
        }
};

class GoogleStockChange : public StockChangeSubject
{
    public:
        float getStockValue()
        {
            return stockValue;
        }

        void setStockValue(float newStockvalue)
        {
            stockValue = newStockvalue;
            notifyObservers();
        }
};

class FbStockChange : public StockChangeSubject
{
    public:
        float getStockValue()
        {
            return stockValue;
        }

        void setStockValue(float newStockvalue)
        {
            stockValue = newStockvalue;
            notifyObservers();
        }
};

class ObserversInIndia : public StockObserver
{
    private:
        list <StockChangeSubject*> stockSubject;
    
    public:
        ObserversInIndia(StockChangeSubject* stockChangeSubject)
        {
            stockSubject.push_back(stockChangeSubject);
            stockChangeSubject->attachObserver(this);
        }

        ObserversInIndia(list <StockChangeSubject*> stockChangeSubject)
        {
            list <StockChangeSubject*>::iterator itrStockChange;
            for(itrStockChange=stockChangeSubject.begin(); itrStockChange != stockChangeSubject.end(); itrStockChange++)
            {
                stockSubject.push_back(*itrStockChange);
                (*itrStockChange)->attachObserver(this);
            }
        }

        void update(StockChangeSubject* specificStockSubject)
        {
            cout<<"Observers in India have been updated about the stock change: "<<specificStockSubject->getStockValue()<<endl;
        }
};

class ObserversInUSA : public StockObserver
{
    private:
        list <StockChangeSubject*> stockSubject;
    
    public:
        ObserversInUSA(StockChangeSubject* stockChangeSubject)
        {
            stockSubject.push_back(stockChangeSubject);
            stockChangeSubject->attachObserver(this);
        }

        ObserversInUSA(list <StockChangeSubject*> stockChangeSubject)
        {
            list <StockChangeSubject*>::iterator itrStockChange;
            for(itrStockChange=stockChangeSubject.begin(); itrStockChange != stockChangeSubject.end(); itrStockChange++)
            {
                stockSubject.push_back(*itrStockChange);
                (*itrStockChange)->attachObserver(this);
            }
        }

        void update(StockChangeSubject* specificStockSubject)
        {
            cout<<"Observers in USA have been updated about the stock change: "<<specificStockSubject->getStockValue()<<endl;
        }
};

int main()
{
    StockChangeSubject* qualcommSubject = new QualcommStockChange();
    StockChangeSubject* fbSubject = new FbStockChange();
    StockChangeSubject* googleSubject = new GoogleStockChange();

    list <StockChangeSubject*> indiaStockChangeSubject;
    indiaStockChangeSubject.push_back(qualcommSubject);
    indiaStockChangeSubject.push_back(fbSubject);
    indiaStockChangeSubject.push_back(googleSubject);
    StockObserver* indiaObserver = new ObserversInIndia(indiaStockChangeSubject);

    list <StockChangeSubject*> usaStockChangeSubject;
    usaStockChangeSubject.push_back(fbSubject);
    usaStockChangeSubject.push_back(googleSubject);
    StockObserver* usObserver = new ObserversInUSA(usaStockChangeSubject);

    qualcommSubject->setStockValue(100);
    fbSubject->setStockValue(50);
    googleSubject->setStockValue(300);

    return 0;
}