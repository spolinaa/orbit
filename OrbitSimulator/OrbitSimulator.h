#pragma once
#include <vector>
#include "vec.cpp"
using namespace std;

const double G = 6.67408 * pow(10.0, -11), //gravitational constant, m^3 / (kg * sec^2)
   EarthMass = 5.9742 * pow(10.0, 24), //Earth's mass, kg
   EarthRadius = 6378100, //radius of the Earth, m
   ZeroCelsius = 273.15, //absolute zero
   AtmosphereBoundary = 6523100, //end of atmosphere, m
   SeaLevelAirDensity = 1.225; // kg / m^3
const double g = G * EarthMass / pow(EarthRadius, 2); //Acceleration of gravity.

//rotation vector
struct Rotation
{
    double rotationAroundX, rotationAroundY, rotationAroundZ;
};

typedef vec Orient; //orientation vector
typedef vec Position; //position vector
//typedef Rotation RotationSpeed; //rotation speed vector

//starting position, orientation, speed and moment of inertia
struct ShipPosition
{
    Position position;
    Orient orientation;
    vec speedFirst;
    Rotation moment;
};

//user's commands
struct PartOfFlightPlan
{
    double delayTime; //delay time (must be a multiple of the size of quant)
    double impulseValue; //fuel mass flow rate
    Rotation rotateValue; //moment of inertia
};

//ship parameters
struct ShipParams
{
    double shipEdgeLength; //edge length
    double shipMass; //ship mass without fuel
    double fuelMass; //fuel mass
    Rotation maxRotation; //maximum moment of inertia
    double maxFuelUsagePerSec; //maximum fuel mass flow rate
    double impulsePerFuel; //specific impulse of the engine
    std::vector<PartOfFlightPlan> flightPlan; //an array of commands
    double maxHeating; //maximum heating
};

struct Quants
{
    int numberOfQuants; //number of time intervals
    double quantSizeOfSec; //size of interval (sec)
};

//return values of position and speed at each time interval
struct ReturnValues
{
    Position position;
    vec speed;
    double overload;
};

std::vector <ReturnValues> computeFlightPlan(ShipPosition initialPosition,
                                             ShipParams shipParams,
                                             Quants quants);
