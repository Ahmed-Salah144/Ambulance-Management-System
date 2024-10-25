#pragma once
#include "Defs.h"
#include "Car.h"
#include "Patient.h"
#include "List.h"
#include "Queue.h"
#include "PriQueue.h"

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

	LinkedList<Car*> readySCList;				// List of Available Cars(Special-Equipment)

	LinkedList<Car*> busySCList;				// List of Away Cars(Special-Equipment)

	LinkedList<Car*> readyNCList;				// List of Available Cars(Normal)

	LinkedList<Car*> busyNCList;				// List of Away Cars(Normal)

	/////////////////////////////////////////////////////////////////////////////////////////////////
	//	Patient Data
	/////////////////////////////////////////////////////////////////////////////////////////////////

	Queue<Patient*> NPqueue;			// Queue for Normal Patients

	Queue<Patient*> SPqueue;			// Queue for Special-Case Patients

	PriQueue<Patient*> EPqueue;			// Priority Queue for Emergency Case Patients Based on Case Severity

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