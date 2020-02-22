//#include <iostream>
//#include <string>
//#include <map>
//#include "ParkingLot.h"
//using namespace std;
//
//ParkingFloor::ParkingFloor(string name)
//{
//    this->name = name;
//}
//
//void ParkingFloor::addParkingSpot(ParkingSpot* spot)
//{
//    string spotNumber = spot->number;
//    if(spot->type == HANDICAPPED)
//        handicappedSpots.insert(pair<string, ParkingSpot*>(spotNumber, spot));
//    else if(spot->type == COMPACT)
//        compactSpots.insert(pair<string, ParkingSpot*>(spotNumber, spot));
//    else if(spot->type == LARGE)
//        largeSpots.insert(pair<string, ParkingSpot*>(spotNumber, spot));
//    else if(spot->type == BIKE)
//        motorbikeSpots.insert(pair<string, ParkingSpot*>(spotNumber, spot));
//    else if(spot->type == ELECTRIC)
//        electricSpots.insert(pair<string, ParkingSpot*>(spotNumber, spot));
//    else
//        cout<<"Wrong parking type selected \n";
//}
//
//void ParkingFloor::assignVehicleToSpot(Vehicle* vehicle, ParkingSpot* spot)
//{
//    spot->assignVehicle(vehicle);
//    //if(spot->type == HANDICAPPED)
//    //    updateDisplayBoardForHandicapped(spot);
//    //else if(spot->type == COMPACT)
//    //    updateDisplayBoardForCompact(spot);
//    //else if(spot->type == LARGE)
//    //    updateDisplayBoardForLarge(spot);
//    //else if(spot->type == BIKE)
//    //    updateDisplayBoardForMotorBike(spot);
//    //else if(spot->type == ELECTRIC)
//    //    updateDisplayBoardForElectric(spot);
//    //else
//    //    cout<<"Wrong parking type selected \n";
//}
//
//void ParkingFloor::freeSpot(ParkingSpot* spot)
//{
//    spot->removeVehicle();
//    if(spot->type == HANDICAPPED)
//        handi
//        
//    else if(spot->type == COMPACT)
//    else if(spot->type == LARGE)
//    else if(spot->type == BIKE)
//    else if(spot->type == ELECTRIC)
//
//}