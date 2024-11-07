#pragma once
#include "List.h"
#include "fstream"
#include "string"
#include "HospitalList.h"
#include "CarPriQueue.h"
#define MAXHOSPITAL 100

using namespace std;
class Organizer
{
	PatientQueue patients;									// Requests Yet to Arrive
	
	ArrList<Hospital*> hospitals;							// List of All Loaded Hospitals //Change this to hospitalList class

	PatientQueue finishList;								// List of All Finished Requests at current timestep

	CarPriQueue outList;									// List of All Cars Out for patients at current timestep

	CarPriQueue backList;									// List of All Cars Returning with patients at current timestep

	LinkedQueue<CancellationRequest> cancellationRequests;	// Patients Cancellation Request Yet to Arrive

	int distanceMatrix[MAXHOSPITAL][MAXHOSPITAL];			// Weighted Graph Adjacency Matrix 


	//////////////////////////////////////////////////////////////////////////////////////////////
	// Output File Data
	//////////////////////////////////////////////////////////////////////////////////////////////

	int numOfHospitals;										// Number of Loaded Hospitals

	int numOfCars;											// Total Number of Cars Loaded

	int numOfCarsSC;										// Number of Special Cars Loaded

	int numOfCarsNC;										// Number of Normal Cars Loaded

	int numOfPatientsEP;									// Number of Emergency Patient Requests

	int numOfPatientsSP;									// Number of Special Patient Requests

	int numOfPatientsNP;									// Number of Normal Patient Requests

	int numofEProuted;										// Number of Emergency Patients routed to other hospitals

	int numOfPatients;										// Total Number of Patient Requests Loaded

	int worldTime;											// Current Timestep of the World

	//////////////////////////////////////////////////////////////////////////////////////////////


public:

	Organizer();

	void Load(string filepath);

	void Output();

	int getFastestEmergency();

	void Advance();

};