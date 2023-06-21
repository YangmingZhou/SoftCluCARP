#ifndef VEHICLE_H
#define VEHICLE_H

#include "Params.h"

class Params ;

class Vehicle
{
private:
Params * params ;
public:
int depotNumber ;     
double maxRouteTime ;
double vehicleCapacity ;
Vehicle(int depotNumber,double maxRouteTime,double vehicleCapacity);
~Vehicle(void);
};

#endif
