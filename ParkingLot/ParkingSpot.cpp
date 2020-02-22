#include <iostream>
#include <string>
#include "ParkingLot.h"
using namespace std;

ParkingSpot::ParkingSpot()
{}

ParkingSpot::ParkingSpot(ParkingSpotType type)
{
    this->type = type;
}

bool ParkingSpot::assignVehicle(Vehicle* vehicle)
{
    this->vehicle = vehicle;
    free = false;
}

void ParkingSpot::removeVehicle()
{
    this->vehicle = NULL;
    free = true;
}

bool ParkingSpot::isFree()
{
    return free;
}

HandicappedSpot::HandicappedSpot(string number)
{
    type = HANDICAPPED;
    free = true;
    this->number = number;
}

CompactSpot::CompactSpot(string number)
{
    type = COMPACT;
    free = true;
    this->number = number;
}

LargeSpot::LargeSpot(string number)
{
    type = LARGE;
    free = true;
    this->number = number;
}

MotorBikeSpot::MotorBikeSpot(string number)
{
    type = BIKE;
    free = true;
    this->number = number;
}

ElectricSpot::ElectricSpot(string number)
{
    type = ELECTRIC;
    free = true;
    this->number = number;
}