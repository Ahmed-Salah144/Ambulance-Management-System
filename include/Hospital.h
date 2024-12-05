#pragma once
#include "CarQueue.h"
#include "PatientQueue.h"
#include "EmergencyQueue.h"
class Organizer;

class UI;

/////////////////////////////////////////////////////////////////////////////////////////////////
class Hospital {

	/////////////////////////////////////////////////////////////////////////////////////////////////
	//	Constants
	/////////////////////////////////////////////////////////////////////////////////////////////////

	const int ID;						// Hospital ID

	const int numOfNC;					// Number of Normal Cars

	const int numOfSC;					// Number of Special-Equipment Cars

	bool failed;

	/////////////////////////////////////////////////////////////////////////////////////////////////
	//	Car Data
	/////////////////////////////////////////////////////////////////////////////////////////////////

	CarQueue readySCList;				// List of Available Cars(Special-Equipment)

	CarQueue readyNCList;				// List of Available Cars(Normal)


	/////////////////////////////////////////////////////////////////////////////////////////////////
	//	Patient Data
	/////////////////////////////////////////////////////////////////////////////////////////////////

	PatientQueue NPqueue;			// Queue for Normal Patients

	PatientQueue SPqueue;			// Queue for Special-Case Patients

	EmergencyQueue EPqueue;			// Priority Queue for Emergency Case Patients Based on Case Severity

	Organizer* organizer;

	friend class UI;

public:

	// Hosptial Non-Defualt Constructor Requires The Number of Special and Normal Cars and Their Speeds and The Hospital ID 

	Hospital(int id, int scNum, int ncNum, int scSpeed, int ncSpeed,Organizer* o);

	void EnqueueSpecialPatient(Patient* patient);

	void EnqueueNormalPatient(Patient* patient);

	void EnqueueEmergencyPatient(Patient* patient);

	void EnqueueFailedPatient(Patient* patient);

	bool HandleEmergencyPatient(Patient* patient);		// PHASE 2 Rerouting to other hospitals

	void CancelPatient(int patientID);

	int getEmergencyQueueLength();

	void Update();

	void ReturnCarToFreeList(Car * car,int time);							// assign car to correct readylist from the back list

	Car* HandNCarOver();

	Car* HandSCarOver();

	Patient* HandNPOver();

	Patient* HandSPOver();

	Patient* HandEPOver();

	void Fail(int nearest);

	bool isFailed();

	bool isNCEmpty();

	bool isSCEmpty();

	bool isEmpty();


	void Clear();

	~Hospital();


};