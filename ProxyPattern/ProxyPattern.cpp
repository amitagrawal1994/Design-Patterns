#include <iostream>
#include <string>
using namespace std;

/*
1. We can use proxy when we may want to use a class that can perform as an interface to something else.
2. Proxy is heavily used to implement lazy loading related usecases where we do not want to create full object until it is actually needed.
3. A proxy can be used to add an additional security layer around the original object as well.

eg: Before actually accessing a website, proxy can check if the syntax/length of passwords/email is correct or not
*/

struct DrivingLicenseAuthority
{
    virtual void issueDrivingLicense() = 0;
};

class HyderabadDrivingAuthority : public DrivingLicenseAuthority
{
    public:
        void issueDrivingLicense()
        {
            cout<<"Driving license is being issued by Hyderabad Driving Authority"<<endl;
        }
};

class HyderabadProxy : public DrivingLicenseAuthority
{
    HyderabadDrivingAuthority* hydAuthority;
    int driverAge;

    public:
        HyderabadProxy(int driverAge = 20)
        {
            this->driverAge = driverAge;
            hydAuthority = new HyderabadDrivingAuthority;
        }

        void issueDrivingLicense()
        {
            if(driverAge > 18)
            {
                cout<<"Driver age: "<<driverAge<<" is greater than 18. Generating driver license"<<endl;
                hydAuthority->issueDrivingLicense();
            }
            else
            {
                cout<<"Driver age: "<<driverAge<<" is less than 18. Denying driver license"<<endl;
            }
        }
};

int main()
{
    DrivingLicenseAuthority* authority = new HyderabadProxy(15);
    authority->issueDrivingLicense();

    authority = new HyderabadProxy(26);
    authority->issueDrivingLicense();

    return 0;
}