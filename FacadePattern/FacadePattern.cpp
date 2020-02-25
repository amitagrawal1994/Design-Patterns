#include <iostream>
#include <string>
using namespace std;

/*
1. Facade does not reduce the complexity. It only hides it from external systems and clients. 
   So the primary beneficiary of facade patterns are client applications and other systems only.

2. It provides a simple interface to clients i.e. instead of presenting complex subsystems, we present one simplified interface to clients. 
   It can also help us to reduce the number of objects that a client needs to deal with.

3. A facade does not encapsulate the subsystem classes or interfaces. It just provides a simple interface (or layer) to make our life easier. 
   We are free to expose any functionality of the subsystem or the whole subsystem itself.

Eg: When we press key to boot up, it internally calls a bunch of subsystem calls to boot up.
User don't have to call each subsystem function to get initialized and boot up. Start button is a facade.
*/

#define interface struct

interface BootProcess
{
    virtual void initializeRAM() = 0;
    virtual void loadOStoRAM() = 0;
};

class WindowsBootProcess : public BootProcess
{
    public:
        void initializeRAM()
        {
            cout<<"RAM is being initialized for Windows\n";
        }
        void loadOStoRAM()
        {
            cout<<"OS is being loaded to RAM for Windows\n";
        }
};

class UbuntuBootProcess : public BootProcess
{
    public:
        void initializeRAM()
        {
            cout<<"RAM is being initialized for Ubuntu\n";
        }
        void loadOStoRAM()
        {
            cout<<"OS is being loaded to RAM for Ubuntu\n";
        }
};

void loadWindowsUI()
{
    cout<<"Loading the UI for windows\n";
}

void startProfiling()
{
    cout<<"Profiling has been started\n";
}

void startAppsOnBootup(string osType)
{
    if(osType == "Windows")
        cout<<"Loading the default apps on bootup for Windows\n";
    else if(osType == "Ubuntu")
        cout<<"Loading the default apps on bootup for Ubuntu\n";
}

class WindowsBootFacade //facade does not inherit anything
{
    public:
        void startWindows()
        {
            // all boot up functinality related to windows has been combined here
            BootProcess* windowsBoot = new WindowsBootProcess();
            windowsBoot->initializeRAM();
            windowsBoot->loadOStoRAM();
            loadWindowsUI();
            startAppsOnBootup("Windows");
        }
};

class UbuntuBootFacade
{
    public:
        void startUbuntu()
        {
            // all boot up functinality related to ubuntu has been combined here
            BootProcess* ubuntuBoot = new UbuntuBootProcess();
            ubuntuBoot->initializeRAM();
            ubuntuBoot->loadOStoRAM();
            startProfiling();
            startAppsOnBootup("Ubuntu");
        }
};

int main()
{
    WindowsBootFacade* windowsFacade = new WindowsBootFacade;
    windowsFacade->startWindows(); // Just one function call does the full bootup

    UbuntuBootFacade* ubuntuFacade = new UbuntuBootFacade;
    ubuntuFacade->startUbuntu(); // Just one function call does the full bootup

    return 0;
}
