#ifndef PATIENT_H
#define PATIENT_H
#include "Defs.h"
#include <iostream>
using namespace std;

class Car;

class Patient {

	/////////////////////////////////////////////////////////////////////////////////////////////////
	//	Constants
	/////////////////////////////////////////////////////////////////////////////////////////////////

	const int ID;						// Patient ID

	const int requestTime;				// Time of Ambulance Request

	const int closestHID;						// Closest Hospital ID

	const PatientType patientType;		// Normal/Special-Case/Emergency-Case

	const int caseSeverity;				// for Emergency patients --- -1 for other patients

	/////////////////////////////////////////////////////////////////////////////////////////////////

	int distance;						// Distance to Nearest Hospital

	int HID;

	int pickupTime;						// Time of Ambulance Arrival

	int assignmentTime;					// Time Ambulance left for the patient

	int finishTime;

	Car* failedCar;

public:

	Patient(int id, int rT, int hid, PatientType pT, int dist, int cS = -1);

	/////////////////////////////////////////////////////////////////////////////////////////////////
	//	Setters and Getters
	/////////////////////////////////////////////////////////////////////////////////////////////////

	int getID() const { return ID; }

	int getRequestTime() const { return requestTime; }

	int getHospitalID() const { return HID; }
	void setNewHospital(int newID,int newDist)
	{
		HID = newID;
		distance = newDist;
	}
	PatientType getPatientType() const { return patientType; }

	int getDistance() const { return distance; }

	void setDistance(int d) { distance = d; }

	Car* getFailedCar() const { return failedCar; }

	void setFailedCar(Car * c) { failedCar = c; }

	int getCaseSeverity() const { return caseSeverity; }

	void setPickupTime(int t) { pickupTime = t; }

	int getPickupTime() { return pickupTime; }

	void setAssignmentTime(int t) { assignmentTime = t; }

	int getAssignmentTime() { return assignmentTime; }

	void setFinishTime(int t) { finishTime = t; }

	int getFinishTime() { return finishTime; }

	/////////////////////////////////////////////////////////////////////////////////////////////////
};

ostream& operator<<(ostream& out, Patient& P);

#endif 