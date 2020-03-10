#include <iostream>
#include <string>
#include <map>

using namespace std;

/*
1. This pattern is most suitable in cases where you need to work with objects which form a tree like hierarchy. 
2. In that tree, each node/object (except root node) is either composite or leaf node. 
3. Implementing the composite pattern lets clients treat individual objects and compositions uniformly.
4. Adding new components can be easy and client code does not need to be changed since client deals with the new components through the component interface.
5. Composite hierarchy can be traversed with Iterator design pattern.
6. Visitor design pattern can apply an operation over a Composite.
7. Flyweight design pattern is often combined with Composite to implement shared leaf nodes.

e.g: Banking system, directory in file system, retail and inventory system
Here we will implememnt a school cluster
*/

class School;

// Interface to organize schools
struct SchoolCluster
{
    int studentCount; //total student counts rolled up till that school
    int schoolId;
    int schoolCount; //total schools under this school
    virtual void addSchool(SchoolCluster* school) = 0;
    virtual void deleteSchool(SchoolCluster* school) = 0;
    int countSchool()
    {
        cout<<"Getting school count from school: "<<this->schoolId<<". Count = "<<this->schoolCount<<endl;
        return this->schoolCount;
    }
    int countStudent()
    {
        cout<<"Getting student count from school: "<<this->schoolId<<". Count = "<<this->studentCount<<endl;
        return this->studentCount;
    }
};

//Concrete implementation of school
class School : public SchoolCluster
{
    map<int,SchoolCluster*> schoolList; //map of school with school ids

    public:
        School(int id, int count)
        {
            this->schoolId= id;
            this->studentCount = count;
            this->schoolCount = 0;
        }

        //add school will add the student count till now and update total schools by 1
        void addSchool(SchoolCluster* school)
        {
            if(schoolList.find(school->schoolId) == schoolList.end())
            {
                schoolList.insert(pair<int,SchoolCluster*>(school->schoolId,school));
                this->studentCount += school->studentCount;
                this->schoolCount += (school->schoolCount + 1);
                cout<<"Adding school with id: "<<school->schoolId<<" inside school with id: "<<this->schoolId<<endl;
            }
            else
            {
                cout<<"School with given school ID already exist\n";
            }
        }

        //delete school will delete the student count and subtract 1 from the school count
        void deleteSchool(SchoolCluster* school)
        {
            if(schoolList.find(school->schoolId) != schoolList.end())
            {
                schoolList.erase(school->schoolId);
                this->studentCount -= school->studentCount;
                this->schoolCount -= (school->schoolCount + 1);
                cout<<"Removing school with id: "<<school->schoolId<<" from school with id: "<<this->schoolId<<endl;
            }
            else
            {
                cout<<"School with given school ID does not exist\n";
            }
        }
};

int main()
{
    SchoolCluster* school1 = new School(1,100);
    SchoolCluster* school2 = new School(2,110);
    SchoolCluster* school3 = new School(3,120);
    SchoolCluster* school4 = new School(4,130);
    SchoolCluster* school5 = new School(5,140);
    SchoolCluster* school6 = new School(6,150);
    SchoolCluster* school7 = new School(7,160);
    SchoolCluster* school8 = new School(8,170);
    SchoolCluster* school9 = new School(9,100);
    SchoolCluster* school10 = new School(10,110);
    SchoolCluster* school11 = new School(11,120);
    SchoolCluster* school12 = new School(12,130);
    SchoolCluster* school13 = new School(13,140);
    SchoolCluster* school14 = new School(14,150);

    school11->addSchool(school12);
    school11->addSchool(school13);
    school11->addSchool(school14);
    school7->addSchool(school8);
    school7->addSchool(school9);
    school7->addSchool(school10);
    school6->addSchool(school11);
    school6->addSchool(school7);
    school3->addSchool(school4);
    school3->addSchool(school5);
    school2->addSchool(school3);
    school1->addSchool(school2);
    school1->addSchool(school6);

    cout<<endl<<endl;
    school11->countSchool();
    school11->countStudent();

    cout<<endl<<endl;
    school7->countSchool();
    school7->countStudent();

    cout<<endl<<endl;
    school6->countSchool();
    school6->countStudent();

    cout<<endl<<endl;
    school3->countSchool();
    school3->countStudent();

    cout<<endl<<endl;
    school2->countSchool();
    school2->countStudent();

    cout<<endl<<endl;
    school1->countSchool();
    school1->countStudent();

    school1->deleteSchool(school6);
    cout<<endl<<endl;
    school1->countSchool();
    school1->countStudent();
    return 0;
}