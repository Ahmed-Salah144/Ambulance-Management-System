#ifndef PATIENT_H
#define PATIENT_H
#include "Defs.h"
#include <iostream>
using namespace std;
class Patient {

	/////////////////////////////////////////////////////////////////////////////////////////////////
	//	Constants
	/////////////////////////////////////////////////////////////////////////////////////////////////

	const int ID;						// Patient ID

	const int requestTime;				// Time of Ambulance Request

	const int HID;						// Closest Hospital ID

	const PatientType patientType;		// Normal/Special-Case/Emergency-Case

	const int distance;					// Distance to Nearest Hospital

	const int caseSeverity;				// for Emergency patients --- -1 for other patients

	/////////////////////////////////////////////////////////////////////////////////////////////////

	int pickupTime;						// Time of Ambulance Arrival

	int assignmentTime;					// Time Ambulance left for the patient

	int finishTime;

public:

	Patient(int id, int rT, int hid, PatientType pT, int dist, int cS = -1);

	/////////////////////////////////////////////////////////////////////////////////////////////////
	//	Setters and Getters
	/////////////////////////////////////////////////////////////////////////////////////////////////

	int getID() const { return ID; }

	int getRequestTime() const { return requestTime; }

	int getHospitalID() const { return HID; }

	PatientType getPatientType() const { return patientType; }

	int getDistance() const { return distance; }

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