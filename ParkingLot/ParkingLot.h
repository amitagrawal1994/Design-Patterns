#include <iostream>
#include <ctime>
#include<map>
using namespace std;

enum VehicleType 
{
  CAR, TRUCK, EBATTERY, VAN, MOTORBIKE
};

enum ParkingSpotType 
{
  HANDICAPPED, COMPACT, LARGE, BIKE, ELECTRIC
};

//enum AccountStatus 
//{
//  ACTIVE, BLOCKED, BANNED, COMPROMISED, ARCHIVED, UNKNOWN
//};

enum ParkingTicketStatus 
{
  ACTIVE, PAID, LOST
};

struct Location 
{
   string streetAddress;
   string city;
   string state;
   string zipCode;
   string country;
};

struct Person 
{
  string name;
  Location address;
  string email;
  string phone;
};

class Account 
{
  string userName;
  string password;
  //AccountStatus status;
  Person person;

  public:
    virtual bool resetPassword() = 0;
};

class ParkingSpot;
class ParkingTicket
{
    public:
        double ticketNumber;
        time_t  issuedAt;
        time_t payedAt;
        double payedAmount;
        static double count;
        ParkingTicketStatus status;
        ParkingSpot* parkingSpot;
};

class Vehicle
{
    protected:
        string licencenumber;

    public:
        ParkingTicket* ticket;
        VehicleType type;
        Vehicle();
        Vehicle(VehicleType type);
        void assignTicket(ParkingTicket* ticket);
};
class Car : public Vehicle{public: Car();};
class Truck : public Vehicle{public: Truck();};
class Electric : public Vehicle{public: Electric();};
class Van : public Vehicle{public: Van();};
class MotorBike : public Vehicle{public: MotorBike();};

class ParkingSpot
{
    public:
        string number;
        bool free;
        Vehicle* vehicle;
        ParkingSpotType type;
        ParkingSpot();
        ParkingSpot(ParkingSpotType type);
        bool assignVehicle(Vehicle* vehicle);
        void removeVehicle();
};
class HandicappedSpot : public ParkingSpot{public: HandicappedSpot(string number);};
class CompactSpot : public ParkingSpot{public: CompactSpot(string number);};
class LargeSpot : public ParkingSpot{public: LargeSpot(string number);};
class MotorBikeSpot : public ParkingSpot{public: MotorBikeSpot(string number);};
class ElectricSpot : public ParkingSpot{public: ElectricSpot(string number);};

class ParkingLot
{
  private:
    static ParkingLot* parkingLot;
    ParkingLot(){};
    int maxcompactSpotCount;
    int maxhandicappedSpotCount;
    int maxlargeSpotCount;
    int maxmotorbikeSpotCount;
    int maxelectricSpotCount;
    int compactSpotCount;
    int handicappedSpotCount;
    int largeSpotCount;
    int motorbikeSpotCount;
    int electricSpotCount;
    map<string,ParkingSpot*> handicappedSpots;
    map<string,ParkingSpot*> compactSpots;
    map<string,ParkingSpot*> largeSpots;
    map<string,ParkingSpot*> motorbikeSpots;
    map<string,ParkingSpot*> electricSpots;
    void assignVehicleToSpot(Vehicle* vehicle, ParkingSpot* spot);
    void freeSpot(ParkingSpot* spot);
    ParkingTicket* getTicketforParkingNumber(double parkingNumber);
    map<double, ParkingTicket*> activeTickets;
    ParkingSpot* getParkingSpotForVehicle(VehicleType type);
    bool isFull(VehicleType type);
    void incrementSpotCount(VehicleType type);
    void decrementSpotCount(ParkingSpotType type);
    //string name;
    //Location address;
    //ParkingRate parkingRate;
    //void addParkingFloor(ParkingFloor* parkingFloor);
    //void addEntrancePanel(EntrancePanel entrancePanel);
    //void addExitPanel(ExitPanel exitPanel);
    //map<string, EntrancePanel> entrancePanels;
    //map<string, ExitPanel> exitPanels;
    //map<string, ParkingFloor> parkingFloors;
  
  public:
    static ParkingLot* getInstance();
    void addParkingSpot(ParkingSpot* spot);
    ParkingTicket* getNewParkingTicket(Vehicle* vehicle);
    void processTicketforPayment(double ticketNumber);
};

//class ParkingDisplayBoard
//{
//  public:
//    string id;
//    HandicappedSpot handicappedFreeSpot;
//    CompactSpot compactFreeSpot;
//    LargeSpot largeFreeSpot;
//    MotorBikeSpot motorbikeFreeSpot;
//    ElectricSpot electricFreeSpot;
//    void showEmptySpotNumber();
//    void showMessage(string message);
//};

//class ParkingFloor
//{
//  public:
//    string name;
//    //ParkingDisplayBoard displayBoard;
//    map<string,ParkingSpot*> handicappedSpots;
//    map<string,ParkingSpot*> compactSpots;
//    map<string,ParkingSpot*> largeSpots;
//    map<string,ParkingSpot*> motorbikeSpots;
//    map<string,ParkingSpot*> electricSpots;
//
//    ParkingFloor();
//    ParkingFloor(string name);
//    void addParkingSpot(ParkingSpot* spot);
//    void assignVehicleToSpot(Vehicle* vehicle, ParkingSpot* spot);
//    void freeSpot(ParkingSpot* spot);
//    //void updateDisplayBoardForHandicapped(ParkingSpot* spot);
//    //void updateDisplayBoardForCompact(ParkingSpot* spot);
//    //void updateDisplayBoardForLarge(ParkingSpot* spot);
//    //void updateDisplayBoardForMotorBike(ParkingSpot* spot);
//    //void updateDisplayBoardForElectric(ParkingSpot* spot);
//};

//class CustomerInfoPanel;
//class EntrancePanel;
//class ExitPanel;
//
//class Admin : public Account
//{
//    public:
//        bool addParkingFloor(ParkingFloor floor);
//        bool addParkingSpot(string floorName, ParkingSpot* spot);
//        //bool addParkingDisplayBoard(string floorName, ParkingDisplayBoard displayBoard);
//        bool addCustomerInfoPanel(string floorName, CustomerInfoPanel infoPanel);
//        bool addEntrancePanel(EntrancePanel entrancePanel);
//        bool addExitPanel(ExitPanel exitPanel);
//};
//
//class ParkingAttendant : public Account 
//{
//    public:
//        bool processTicket(string TicketNumber);
//};