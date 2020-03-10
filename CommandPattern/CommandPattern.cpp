#include <iostream>
using namespace std;

/*
1. The command pattern's intention is to decouple the consumers of an action and the object which knows how to perform the action.
2. The command pattern is equivalent of a callback function in procedural languages as we parametrize objects with an action to perform.
3. The similar approach is adapted into chain of responsibility pattern as well. 
   Only difference is that in command there is one request handler, and in chain of responsibility there can be many handlers for single request object.

e.g:
Remote system - User just presses a key to do something.
*/

// interface which contains function to be executed
struct Command
{
    virtual void execute()=0;
};

//Concrete class with product
class Fan
{
    public:
        void turnOn()
        {
            cout<<"Fan is turning ON\n";
        }
        void turnOff()
        {
            cout<<"Fan is turning OFF\n";
        }
};

//Concrete class with product
class TV
{
    public:
        void turnOn()
        {
            cout<<"TV is turning ON\n";
        }
        void turnOff()
        {
            cout<<"TV is turning OFF\n";
        }
};

// Class which implements an action
class FanOnCommand : public Command
{
    Fan* fan;
    public:
        FanOnCommand(Fan* fan)
        {
            this->fan = fan;
        }

        void execute()
        {
            fan->turnOn();
        }
};

// Class which implements an action
class FanOffCommand : public Command
{
    Fan* fan;
    public:
        FanOffCommand(Fan* fan)
        {
            this->fan = fan;
        }

        void execute()
        {
            fan->turnOff();
        }
};

// Class which implements an action
class TVOnCommand : public Command
{
    TV* tv;
    public:
        TVOnCommand(TV* tv)
        {
            this->tv = tv;
        }

        void execute()
        {
            tv->turnOn();
        }
};

// Class which implements an action
class TVOffCommand : public Command
{
    TV* tv;
    public:
        TVOffCommand(TV* tv)
        {
            this->tv = tv;
        }

        void execute()
        {
            tv->turnOff();
        }
};

// The handler class
class RemoteSystem
{
    Command* command;

    public:
        void setOperation(Command* command)
        {
            this->command = command;
        }

        void onButtonPressed()
        {
            command->execute();
        }
};

int main()
{
    Fan* fan=new Fan;
    TV* tv=new TV;

    Command* fanOn = new FanOnCommand(fan);
    Command* fanOff = new FanOffCommand(fan);

    Command* tvOn = new TVOnCommand(tv);
    Command* tvOff = new TVOffCommand(tv);

    RemoteSystem* remoteSystem = new RemoteSystem;

    //set the operation to be performed and then call onButtonPressed.
    //handler does not know how the Fan/TV is getting Switched On or Off
    remoteSystem->setOperation(fanOn);
    remoteSystem->onButtonPressed();

    remoteSystem->setOperation(fanOff);
    remoteSystem->onButtonPressed();

    remoteSystem->setOperation(tvOn);
    remoteSystem->onButtonPressed();

    remoteSystem->setOperation(tvOff);
    remoteSystem->onButtonPressed();

    return 0;
}