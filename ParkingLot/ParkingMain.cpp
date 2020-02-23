#include <iostream>
#include <string>
#include <map>
#include "ParkingLot.h"
using namespace std;

int main()
{
    ParkingLot* parkingLotInstance = ParkingLot::getInstance();
    string parkingSpotNames[] = {"H1-1", "H2-1", "E1-1", "C1-1", "L1-1", "M1-1", "E1-2"};
    ParkingSpot* parkingSpotHandler = new HandicappedSpot(parkingSpotNames[0]);
    parkingLotInstance->addParkingSpot(parkingSpotHandler);

    parkingSpotHandler = new CompactSpot(parkingSpotNames[3]);
    parkingLotInstance->addParkingSpot(parkingSpotHandler);

    parkingSpotHandler = new LargeSpot(parkingSpotNames[4]);
    parkingLotInstance->addParkingSpot(parkingSpotHandler);

    parkingSpotHandler = new MotorBikeSpot(parkingSpotNames[5]);
    parkingLotInstance->addParkingSpot(parkingSpotHandler);

    parkingSpotHandler = new ElectricSpot(parkingSpotNames[6]);
    parkingLotInstance->addParkingSpot(parkingSpotHandler);

    parkingSpotHandler = new ElectricSpot(parkingSpotNames[2]);
    parkingLotInstance->addParkingSpot(parkingSpotHandler);

    parkingSpotHandler = new HandicappedSpot(parkingSpotNames[1]);
    parkingLotInstance->addParkingSpot(parkingSpotHandler);

    Vehicle* vehicleT1 = new Vehicle(TRUCK);
    Vehicle* vehicleC1 = new Vehicle(CAR);
    Vehicle* vehicleC2 = new Vehicle(CAR);
    Vehicle* vehicleB1 = new Vehicle(EBATTERY);
    Vehicle* vehicleB2 = new Vehicle(EBATTERY);
    Vehicle* vehicleV1 = new Vehicle(VAN);
    Vehicle* vehicleM1 = new Vehicle(MOTORBIKE);

    parkingLotInstance->getNewParkingTicket(vehicleB1);
    parkingLotInstance->getNewParkingTicket(vehicleB2);
    parkingLotInstance->getNewParkingTicket(vehicleC1);
    parkingLotInstance->getNewParkingTicket(vehicleC2);
    parkingLotInstance->getNewParkingTicket(vehicleM1);

    parkingLotInstance = ParkingLot::getInstance();
    parkingLotInstance->processTicketforPayment(3);
    parkingLotInstance->processTicketforPayment(0);
    parkingLotInstance->processTicketforPayment(4);
    parkingLotInstance->processTicketforPayment(2);
    parkingLotInstance->processTicketforPayment(1);
    return 0;
}