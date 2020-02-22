#include <iostream>
#include <string>
#include <map>
#include "ParkingLot.h"
using namespace std;

ParkingLot* ParkingLot::parkingLot = NULL;

ParkingLot* ParkingLot::getInstance()
{
    if(parkingLot == NULL)
    {
        parkingLot = new ParkingLot;
        parkingLot->maxcompactSpotCount = 0;
        parkingLot->maxelectricSpotCount = 0;
        parkingLot->maxhandicappedSpotCount = 0;
        parkingLot->maxlargeSpotCount = 0;
        parkingLot->maxmotorbikeSpotCount = 0;
        parkingLot->compactSpotCount = 0;
        parkingLot->handicappedSpotCount = 0;
        parkingLot->electricSpotCount = 0;
        parkingLot->largeSpotCount = 0;
        parkingLot->motorbikeSpotCount = 0;
        cout<<"returning a new instance of ParkingLot \n";
        return parkingLot;
    }
    
    cout<<"returning an old instance of ParkingLot \n";
    return parkingLot;
}

ParkingTicket* ParkingLot::getNewParkingTicket(Vehicle* vehicle)
{
    if(this->isFull(vehicle->type))
    {
        cout<<"All the parking spaces for this vehicle type is full \n";
        return NULL;
    }

    ParkingTicket* parkingTicket = new ParkingTicket;
    cout<<"new parking ticket is created for vehicle type "<<vehicle->type<<endl;
    vehicle->assignTicket(parkingTicket);
    //parkingTicket->saveInDB();

    this->incrementSpotCount(vehicle->type);
    this->activeTickets.insert(pair<string, ParkingTicket*>(parkingTicket->ticketNumber, parkingTicket));
    return parkingTicket;
}

bool ParkingLot::isFull(VehicleType type)
{
    if(type == MOTORBIKE)
    {
        return motorbikeSpotCount >= maxmotorbikeSpotCount;
    }
    else if(type == TRUCK || type == VAN)
    {
        return largeSpotCount >= maxlargeSpotCount;
    }
    else if(type == CAR)
    {
        return (compactSpotCount + largeSpotCount) >= (maxcompactSpotCount + maxlargeSpotCount);
    }
    else if(type == EBATTERY)
    {
        return (compactSpotCount + largeSpotCount + electricSpotCount) >= (maxcompactSpotCount + maxlargeSpotCount + maxelectricSpotCount);
    }
}

void ParkingLot::assignVehicleToSpot(Vehicle* vehicle, ParkingSpot* spot)
{
    spot->assignVehicle(vehicle);
}

void ParkingLot::freeSpot(ParkingSpot* spot)
{
    spot->removeVehicle();
    if(spot->type == HANDICAPPED)
        handicappedSpotCount--;
    else if(spot->type == COMPACT)
        compactSpotCount--;
    else if(spot->type == LARGE)
        largeSpotCount--;
    else if(spot->type == BIKE)
        motorbikeSpotCount--;
    else if(spot->type == ELECTRIC)
        electricSpotCount--;
}

void ParkingLot::incrementSpotCount(VehicleType type)
{
    if(type == MOTORBIKE)
    {
        motorbikeSpotCount++;
        cout<<"spot count incremented for motorbike. Count = "<<motorbikeSpotCount<<endl;
    }
    else if(type == TRUCK || type == VAN)
    {
        largeSpotCount++;
        cout<<"spot count incremented for large vehicle. Count = "<<largeSpotCount<<endl;
    }
    else if(type == CAR)
    {
        if(compactSpotCount < maxcompactSpotCount)
        {
            compactSpotCount++;
            cout<<"spot count incremented for compact vehicle. Count = "<<compactSpotCount<<endl;
        }
        else
        {
            largeSpotCount++;
            cout<<"spot count incremented for large vehicle instead of compact. Count = "<<largeSpotCount<<endl;
        }
    }
    else if(type == EBATTERY)
    {
        if(electricSpotCount < maxelectricSpotCount)
        {
            electricSpotCount++;
            cout<<"spot count incremented for electric vehicle. Count = "<<electricSpotCount<<endl;
        }
        else if(compactSpotCount < maxcompactSpotCount)
        {
            compactSpotCount++;
            cout<<"spot count incremented for compact vehicle instead of electric. Count = "<<compactSpotCount<<endl;
        }
        else
        {
            largeSpotCount++;
            cout<<"spot count incremented for large vehicle instead of electric. Count = "<<largeSpotCount<<endl;
        }
    }
}

void ParkingLot::addParkingSpot(ParkingSpot* spot)
{
    string spotNumber = spot->number;
    if(spot->type == HANDICAPPED)
    {
        handicappedSpots.insert(pair<string, ParkingSpot*>(spotNumber, spot));
        maxhandicappedSpotCount++;
        cout<<"Max spot count incremented for handicapped vehicle. Count = "<<maxhandicappedSpotCount<<endl;
    }
    else if(spot->type == COMPACT)
    {
        compactSpots.insert(pair<string, ParkingSpot*>(spotNumber, spot));
        maxcompactSpotCount++;
        cout<<"Max spot count incremented for compact vehicle. Count = "<<maxcompactSpotCount<<endl;
    }
    else if(spot->type == LARGE)
    {
        largeSpots.insert(pair<string, ParkingSpot*>(spotNumber, spot));
        maxlargeSpotCount++;
        cout<<"Max spot count incremented for large vehicle. Count = "<<maxlargeSpotCount<<endl;
    }
    else if(spot->type == BIKE)
    {
        motorbikeSpots.insert(pair<string, ParkingSpot*>(spotNumber, spot));
        maxmotorbikeSpotCount++;
        cout<<"Max spot count incremented for motorbike vehicle. Count = "<<maxmotorbikeSpotCount<<endl;
    }
    else if(spot->type == ELECTRIC)
    {
        electricSpots.insert(pair<string, ParkingSpot*>(spotNumber, spot));
        maxelectricSpotCount++;
        cout<<"Max spot count incremented for electric vehicle. Count = "<<maxelectricSpotCount<<endl;
    }
    else
        cout<<"Wrong parking type selected \n";
}
