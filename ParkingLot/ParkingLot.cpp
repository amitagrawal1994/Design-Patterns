#include <iostream>
#include <string>
#include <map>
#include "ParkingLot.h"
using namespace std;

double ParkingTicket::count = 0; // set count to 0
ParkingLot* ParkingLot::parkingLot = NULL; //Singleton instance

/* function to return singleton instance of ParkingLot */
ParkingLot* ParkingLot::getInstance()
{
    if(parkingLot == NULL)
    {
        //return a new instance with all default values
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

/*function to get New parking ticket for a vechicle */
ParkingTicket* ParkingLot::getNewParkingTicket(Vehicle* vehicle)
{
    if(this->isFull(vehicle->type))
    {
        cout<<"All the parking spaces for this vehicle type is full \n";
        return NULL;
    }

    // find the free parking spot for this vehicle type
    ParkingSpot* parkingSpot = getParkingSpotForVehicle(vehicle->type);
    if(parkingSpot == NULL)
    {
        cout<<"Could not find suitable parking spot for vehicle type:"<<vehicle->type<<endl;
        return NULL;
    }
    // assign this vehicle to the newly found spot
    assignVehicleToSpot(vehicle,parkingSpot);

    // create a parking ticket for this vehicle
    ParkingTicket* parkingTicket = new ParkingTicket;
    parkingTicket->issuedAt = time(0);
    parkingTicket->ticketNumber = ParkingTicket::count++;
    parkingTicket->status = ACTIVE;
    parkingTicket->parkingSpot = parkingSpot;

    cout<<"\nAttributes of new parking ticket created:\nVehicle type: "<<vehicle->type<<"\nTicket number: "<<parkingTicket->ticketNumber<<"\nAssigned parking spot: "<<parkingTicket->parkingSpot->number<<endl;
    vehicle->assignTicket(parkingTicket);
    //parkingTicket->saveInDB();

    // move this ticket in active tickets
    this->incrementSpotCount(vehicle->type);
    this->activeTickets.insert(pair<double, ParkingTicket*>(parkingTicket->ticketNumber, parkingTicket));
    return parkingTicket;
}

/* function to check if all parking spots are full */
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
        //car can be adjusted in compact as well as large spots
        return (compactSpotCount + largeSpotCount) >= (maxcompactSpotCount + maxlargeSpotCount);
    }
    else if(type == EBATTERY)
    {
        //electric vehicle can be adjusted in electric, compact as well as large spots
        return (compactSpotCount + largeSpotCount + electricSpotCount) >= (maxcompactSpotCount + maxlargeSpotCount + maxelectricSpotCount);
    }
}

/* function to assign the given vehicle to the parking spot */
void ParkingLot::assignVehicleToSpot(Vehicle* vehicle, ParkingSpot* spot)
{
    spot->assignVehicle(vehicle);
}

/* function to process ticket at checkout */
void ParkingLot::processTicketforPayment(double ticketNumber)
{
    ParkingTicket* parkingTicket = getTicketforParkingNumber(ticketNumber);
    if(parkingTicket == NULL)
        return;   

    freeSpot(parkingTicket->parkingSpot);
    activeTickets.erase(ticketNumber);
}

/* function to get parking ticket for a given parking number */
ParkingTicket* ParkingLot::getTicketforParkingNumber(double parkingNumber)
{
    map<double, ParkingTicket*>::iterator ticketIterator;
    for(ticketIterator=activeTickets.begin(); ticketIterator != activeTickets.end(); ticketIterator++)
    {
        if(ticketIterator->first == parkingNumber)
            return ticketIterator->second;
    }
    return NULL;
}

/* function to free the parking spot */
void ParkingLot::freeSpot(ParkingSpot* spot)
{
    spot->removeVehicle();
    if(spot->type == HANDICAPPED)
    {
        handicappedSpotCount--;
        cout<<"Occupied spot count decremented for handicapped. Count = "<<handicappedSpotCount<<endl;
    }
    else if(spot->type == COMPACT)
    {
        compactSpotCount--;
        cout<<"Occupied spot count decremented for compact. Count = "<<compactSpotCount<<endl;
    }
    else if(spot->type == LARGE)
    {
        largeSpotCount--;
        cout<<"Occupied spot count decremented for large. Count = "<<largeSpotCount<<endl;
    }
    else if(spot->type == BIKE)
    {
        motorbikeSpotCount--;
        cout<<"Occupied spot count decremented for motorbike. Count = "<<motorbikeSpotCount<<endl;
    }
    else if(spot->type == ELECTRIC)
    {
        electricSpotCount--;
        cout<<"Occupied spot count decremented for electric. Count = "<<electricSpotCount<<endl;
    }
}

void ParkingLot::incrementSpotCount(VehicleType type)
{
    if(type == MOTORBIKE)
    {
        motorbikeSpotCount++;
        cout<<"Occupied spot count incremented for motorbike. Count = "<<motorbikeSpotCount<<endl;
    }
    else if(type == TRUCK || type == VAN)
    {
        largeSpotCount++;
        cout<<"Occupied spot count incremented for large vehicle. Count = "<<largeSpotCount<<endl;
    }
    else if(type == CAR)
    {
        //car will be adjusted in compact first and then large spot
        if(compactSpotCount < maxcompactSpotCount)
        {
            compactSpotCount++;
            cout<<"Occupied spot count incremented for compact vehicle. Count = "<<compactSpotCount<<endl;
        }
        else
        {
            largeSpotCount++;
            cout<<"Occupied spot count incremented for large vehicle instead of compact. Count = "<<largeSpotCount<<endl;
        }
    }
    else if(type == EBATTERY)
    {
        //electric vehicle will be adjusted in electric first and then compact and then large spot
        if(electricSpotCount < maxelectricSpotCount)
        {
            electricSpotCount++;
            cout<<"Occupied spot count incremented for electric vehicle. Count = "<<electricSpotCount<<endl;
        }
        else if(compactSpotCount < maxcompactSpotCount)
        {
            compactSpotCount++;
            cout<<"Occupied spot count incremented for compact vehicle instead of electric. Count = "<<compactSpotCount<<endl;
        }
        else
        {
            largeSpotCount++;
            cout<<"Occupied spot count incremented for large vehicle instead of electric. Count = "<<largeSpotCount<<endl;
        }
    }
}

/* function to find the correct parking spot for the vehicle type */
ParkingSpot* ParkingLot::getParkingSpotForVehicle(VehicleType type)
{
    map<string, ParkingSpot*>::iterator spotIterator;
    if(type == MOTORBIKE)
    {
        for(spotIterator=motorbikeSpots.begin(); spotIterator != motorbikeSpots.end(); spotIterator++)
        {
            if(spotIterator->second->free)
                return spotIterator->second;
        }
    }
    else if(type == TRUCK || type == VAN)
    {
        for(spotIterator=largeSpots.begin(); spotIterator != largeSpots.end(); spotIterator++)
        {
            if(spotIterator->second->free)
                return spotIterator->second;
        }
    }
    else if(type == CAR)
    {
        for(spotIterator=compactSpots.begin(); spotIterator != compactSpots.end(); spotIterator++)
        {
            if(spotIterator->second->free)
                return spotIterator->second;
        }
        for(spotIterator=largeSpots.begin(); spotIterator != largeSpots.end(); spotIterator++)
        {
            if(spotIterator->second->free)
                return spotIterator->second;
        }
    }
    else if(type == EBATTERY)
    {
        for(spotIterator=electricSpots.begin(); spotIterator != electricSpots.end(); spotIterator++)
        {
            if(spotIterator->second->free)
                return spotIterator->second;
        }
        for(spotIterator=compactSpots.begin(); spotIterator != compactSpots.end(); spotIterator++)
        {
            if(spotIterator->second->free)
                return spotIterator->second;
        }
        for(spotIterator=largeSpots.begin(); spotIterator != largeSpots.end(); spotIterator++)
        {
            if(spotIterator->second->free)
                return spotIterator->second;
        }
    }
    return NULL;
}

/* function to add new parking spots */
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