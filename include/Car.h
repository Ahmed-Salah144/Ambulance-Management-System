#ifndef CAR_H
#define CAR_H

#include "Patient.h"
#include<cassert>
using namespace std;

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

	//CarStatus carStatus;				// Ready/Assigned to a patient/Loaded with a patient

	int busyTime;						// Total time a car is not free

	int outTime;						// Total time a car is not free

	int checkupTime;

	Patient* assignedPatient;			// Patient Assigned to Car at current timestep



public:

	Car(int hid,CarType cT,int speed);

	/////////////////////////////////////////////////////////////////////////////////////////////////
	//	Setters and Getters
	/////////////////////////////////////////////////////////////////////////////////////////////////

	int getHID() const { 
		//assert(HID <= 250);
		return HID;
	}

	int getBusyTime() const { return busyTime; }

	void setBusyTime(int t){ busyTime=t; }

	int getOutTime() const { return outTime; }

	void setOutTime(int t) { outTime = t; }

	int getCheckupTime() const { return checkupTime; }

	void setCheckupTime(int t) { checkupTime = t; }

	Patient* getAssignedPatient() const { return assignedPatient; }

	void setAssignedPatient(Patient* p) { assignedPatient = p; }

	CarType getCarType() const { return carType; }

	int getCarSpeed() const { return carSpeed; }

	//CarStatus getCarStatus() const { return carStatus; }

	//void setCarStatus(CarStatus status) { carStatus = status; }

	int getID() const { return ID; }

	static void ResetCarCount();

	/////////////////////////////////////////////////////////////////////////////////////////////////

	void IncrementBusyTime(int t) { busyTime += t; }

};

ostream& operator<<(ostream& out, Car& C);

#endif CAR_H