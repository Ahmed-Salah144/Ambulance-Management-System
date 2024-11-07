#pragma once
#include "CarStack.h"
#include "PatientQueue.h"
#include "EmergencyQueue.h"
/////////////////////////////////////////////////////////////////////////////////////////////////
//	Forward Declarations
/////////////////////////////////////////////////////////////////////////////////////////////////

//class Car;

//class Patient;

/////////////////////////////////////////////////////////////////////////////////////////////////
class Hospital {

	/////////////////////////////////////////////////////////////////////////////////////////////////
	//	Constants
	/////////////////////////////////////////////////////////////////////////////////////////////////

	const int ID;						// Hospital ID

	const int numOfNC;					// Number of Normal Cars

	const int numOfSC;					// Number of Special-Equipment Cars

	/////////////////////////////////////////////////////////////////////////////////////////////////
	//	Car Data
	/////////////////////////////////////////////////////////////////////////////////////////////////

	CarStack readySCList;				// List of Available Cars(Special-Equipment)

	//CarPriQueue outSCList;				// List of Out Cars(Special-Equipment)

	//CarPriQueue backSCList;				// List of Returning Cars(Special-Equipment)

	CarStack readyNCList;				// List of Available Cars(Normal)

	//CarPriQueue outNCList;				// List of Out Cars(Normal)

	//CarPriQueue backNCList;				// List of Returning Cars(Normal)

	/////////////////////////////////////////////////////////////////////////////////////////////////
	//	Patient Data
	/////////////////////////////////////////////////////////////////////////////////////////////////

	PatientQueue NPqueue;			// Queue for Normal Patients

	PatientQueue SPqueue;			// Queue for Special-Case Patients

	EmergencyQueue EPqueue;			// Priority Queue for Emergency Case Patients Based on Case Severity

public:

	// Hosptial Non-Defualt Constructor Requires The Number of Special and Normal Cars and Their Speeds and The Hospital ID 

	Hospital(int id, int scNum, int ncNum, int scSpeed, int ncSpeed);

	void EnqueueSpecialPatient(Patient* patient);

	void EnqueueNormalPatient(Patient* patient);

	void EnqueueEmergencyPatient(Patient* patient);

	bool HandleEmergencyPatient(Patient* patient);

	int getEmergencyQueueLength();

	void Update(int worldTime);



};