#include <iostream>
#include <string>
using namespace std;

/*
1. This pattern defines a set of related algorithm and encapsulate them in separated classes, and allows client to choose any algorithm at run time.
2. It allows to add new algorithm without modifying existing algorithms or context class, which uses algorithm or strategies
3. Strategy pattern is based upon Open Closed design principle of SOLID principals.

eg: You have many social media apps. At runtime can need to choose which social media app you want to use.
    If in future new social media comes, you can add without modifying what you have now.
*/

#define interface struct

interface SocialMediaStrategy
{
    virtual void connectTo() = 0; //The function has to be shared among all classes inheriting
};

// Concrete social media
class FacebookSocialMedia : public SocialMediaStrategy
{
    public:
        void connectTo()
        {
            cout<<"Connection being established for Facebook\n";
        }
};

class TwitterSocialMedia : public SocialMediaStrategy
{
    public:
        void connectTo()
        {
            cout<<"Connection being established for Twitter\n";
        }
};

class InstagramSocialMedia : public SocialMediaStrategy
{
    public:
        void connectTo()
        {
            cout<<"Connection being established for Instagram\n";
        }
};

//Handler to call the correct startegy
interface SocialMediaContext
{
    SocialMediaStrategy* socialMediaStrategy;

    SocialMediaContext(SocialMediaStrategy* strategy)
    {
        this->socialMediaStrategy = strategy;
    }

    void executeStartegy()
    {
        cout<<"Strategy is being executed\n";
        socialMediaStrategy->connectTo();
    }
};

int main()
{
    SocialMediaStrategy* strategy = new FacebookSocialMedia;
    SocialMediaContext* context = new SocialMediaContext(strategy); // pass the startegy wanted to be executed at runtime
    context->executeStartegy();

    strategy = new TwitterSocialMedia;
    context = new SocialMediaContext(strategy);
    context->executeStartegy();

    strategy = new InstagramSocialMedia;
    context = new SocialMediaContext(strategy);
    context->executeStartegy();
     //Similarly we can add strategies at runtime

    return 0;
}