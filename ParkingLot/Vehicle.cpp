#include <iostream>
#include "ParkingLot.h"
#include <string>
using namespace std;

Vehicle::Vehicle()
{}

Vehicle::Vehicle(VehicleType type)
{
    this->type = type;
}

void Vehicle::assignTicket(ParkingTicket* ticket)
{
    this->ticket = ticket;
}

Car::Car()
{
    type = CAR;
}

Truck::Truck()
{
    type = TRUCK;
}

Electric::Electric()
{
    type = EBATTERY;
}

Van::Van()
{
    type = VAN;
}

MotorBike::MotorBike()
{
    type = MOTORBIKE;
}