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
	PatientQueue requests;									// Requests Yet to Arrive
	
	ArrList<Hospital*> hospitals;							// List of All Loaded Hospitals //Change this to hospitalList class

	PatientQueue finishList;								// List of All Finished Requests at current timestep

	CarPriQueue outList;									// List of All Cars Out for patients at current timestep

	CarPriQueue backList;									// List of All Cars Returning with patients at current timestep

	LinkedQueue<CancellationRequest> cancellationRequests;	// Patients Cancellation Request Yet to Arrive

	int distanceMatrix[MAXHOSPITAL][MAXHOSPITAL];			// Weighted Graph Adjacency Matrix 

	int numOfHospitals;										// Number of Loaded Hospitals

	int worldTime;											// Current Timestep of the World

	int numOfRequests;										// Total Number of Requests Loaded

public:

	void Load(string filepath);

	int getFastestEmergency();

	void Advance();

};