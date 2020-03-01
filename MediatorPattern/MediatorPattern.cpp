#include <iostream>
#include <string>
#include <list>
using namespace std;

/*
1. Mediator promotes loose coupling by keeping objects from referring to each other explicitly, and it lets us vary their interaction independently.
2. Mediator helps to facilitate the interaction between objects in a manner in that objects are not aware of the existence of other objects. 
3. Objects depend only on a single mediator class instead of being coupled to dozens of other objects.
4. Used in multicasting/broadcasting.

e.g:
A great real world example of mediator pattern is traffic control room at airports. 
If all flights will have to interact with each other for finding which flight is going to land next, it will create a big mess.
Rather flights only send their status to the tower. These towers in turn send the signals to conform which airplane can take-off or land. 
We must note that these towers do not control the whole flight. They only enforce constraints in the terminal areas.

Another good example of mediator pattern is a chat application. In a chat application we can have several participants. 
It’s not a good idea to connect each participant to all the others because the number of connections would be really high. 
The best solution is to have a hub where all participants will connect; this hub is just the mediator class.
*/

class Person; //class to keep all the members of group

class GroupChatRoom //Abstract Mediator class
{
    public:
        virtual void sendMsg(string msg, Person* person) = 0;
        virtual void setGroupMember(Person* person) = 0;
};

class Person
{
    protected:
        GroupChatRoom* groupChatRoom; //Just need to know the mediator and not all the people in chatroom
    public:
        virtual void setGroupChatRoom(GroupChatRoom* chatRoom) = 0;
        virtual void getMsg(string msg) = 0;
        virtual void sendMsg(string msg) = 0;
};

class PersonX : public Person
{
    void setGroupChatRoom(GroupChatRoom* chatRoom)
    {
        groupChatRoom = chatRoom; //set the mediator
    }

    void getMsg(string msg)
    {
        cout<<"\t\t\t\tPersonX received message: "<<msg<<endl;
    }

    void sendMsg(string msg)
    {
        cout<<"\nPersonX sending message: "<<msg<<endl;
        this->groupChatRoom->sendMsg(msg,this); //send message through the mediator
    }
};

class PersonY : public Person
{
    void setGroupChatRoom(GroupChatRoom* chatRoom)
    {
        groupChatRoom = chatRoom;
    }

    void getMsg(string msg)
    {
        cout<<"\t\t\t\tPersonY received message: "<<msg<<endl;
    }

    void sendMsg(string msg)
    {
        cout<<"\nPersonY sending message: "<<msg<<endl;
        this->groupChatRoom->sendMsg(msg,this);
    }
};

class PersonZ : public Person
{
    void setGroupChatRoom(GroupChatRoom* chatRoom)
    {
        groupChatRoom = chatRoom;
    }

    void getMsg(string msg)
    {
        cout<<"\t\t\t\tPersonZ received message: "<<msg<<endl;
    }

    void sendMsg(string msg)
    {
        cout<<"\nPersonZ sending message: "<<msg<<endl;
        this->groupChatRoom->sendMsg(msg,this);
    }
};

class ChatRoom : public GroupChatRoom
{
    list<Person*> groupMembers; //keep the list of all group members
    public:
        void setGroupMember(Person* person)
        {
            groupMembers.push_back(person);
        }
        void sendMsg(string msg, Person* person)
        {
            list<Person*>::iterator itr;
            for(itr = groupMembers.begin(); itr != groupMembers.end(); itr++)
            {
                if(*itr != 0 && *itr != person) //Except the person who sent the message, send message to all other people in chat room
                {
                    (*itr)->getMsg(msg);
                }
            }
        }
};

int main()
{
    GroupChatRoom* chatRoom = new ChatRoom; //create a mediator

    //create the members of chat room
    Person* personX = new PersonX;
    Person* personY = new PersonY;
    Person* personZ = new PersonZ;

    //set the members of the chat room
    chatRoom->setGroupMember(personX);
    chatRoom->setGroupMember(personY);
    chatRoom->setGroupMember(personZ);

    //set the mediator. Can be done also through constructor when members are getting created.
    personX->setGroupChatRoom(chatRoom);
    personY->setGroupChatRoom(chatRoom);
    personZ->setGroupChatRoom(chatRoom);

    //broadcast message to group members
    personX->sendMsg("Hi this is Person X");
    personY->sendMsg("Hi this is Person Y");
    personZ->sendMsg("Hi this is Person Z");

    return 0;
}