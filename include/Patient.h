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

	const int distance;						// Distance to Nearest Hospital

	const int caseSeverity;					// for Emergency patients --- -1 for other patients

	/////////////////////////////////////////////////////////////////////////////////////////////////

	int pickupTime;						// Time of Ambulance Arrival

	int assignmentTime;					// Time Ambulance left for the patient

	//bool cancelled;						// True if patient has cancelled the request

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

	//bool isCancelled() const { return cancelled; }

	void setPickupTime(int t) { pickupTime = t; }

	//void Cancel() { cancelled = true; }

	/////////////////////////////////////////////////////////////////////////////////////////////////
};

ostream& operator<<(ostream& out, Patient& P);

#endif 