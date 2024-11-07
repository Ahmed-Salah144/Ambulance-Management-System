#pragma once
#include "Defs.h"
#include "Patient.h"
#include "iostream"
using namespace std;
/////////////////////////////////////////////////////////////////////////////////////////////////
//	Forward Declarations
/////////////////////////////////////////////////////////////////////////////////////////////////

//class Patient;

//class Hospital;

/////////////////////////////////////////////////////////////////////////////////////////////////
class Car {

	/////////////////////////////////////////////////////////////////////////////////////////////////
	//	Constants
	/////////////////////////////////////////////////////////////////////////////////////////////////

	const int HID;						// Hospital ID to Which The Car Belongs

	const CarType carType;				// Normal/Special 

	const int carSpeed;					// The Number of Meters Moved in One Timestep

	int ID;								// Car ID

	static int totalNumberOfCars;		// For Unique ID Assignment

	/////////////////////////////////////////////////////////////////////////////////////////////////

	CarStatus carStatus;				// Ready/Assigned to a patient/Loaded with a patient

	int busytime;						// Total time a car is not free

	Patient* assignedPatient;			// Patient Assigned to Car at current timestep



public:

	Car(int hid,CarType cT,int speed);

	/////////////////////////////////////////////////////////////////////////////////////////////////
	//	Setters and Getters
	/////////////////////////////////////////////////////////////////////////////////////////////////

	int getHID() const { return HID; }

	int getBusyTime() const { return busytime; }

	Patient* getAssignedPatient() const { return assignedPatient; }

	CarType getCarType() const { return carType; }

	int getCarSpeed() const { return carSpeed; }

	CarStatus getCarStatus() const { return carStatus; }

	void setCarStatus(CarStatus status) { carStatus = status; }

	int getID() const { return ID; }

	/////////////////////////////////////////////////////////////////////////////////////////////////
};

ostream& operator<<(ostream& out, Car C)
{
	if (C.getCarStatus() == SC)
		out << "S";
	else
		out << "N";

	out << C.getID() << "_H" << C.getHID();
	if (C.getAssignedPatient() != nullptr)
		out << "_P" << *(C.getAssignedPatient());
	return out;
}