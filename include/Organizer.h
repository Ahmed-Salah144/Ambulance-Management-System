#pragma once
#include"Queue.h"
#include"Stack.h"
#include"PriQueue.h"
#include"List.h"
#include"fstream"
#include"sstream"
#include"string"
#include"Patient.h"
#include"Car.h"
#include"Hospital.h"
#define MAXHOSPITAL 100
using namespace std;
class Organizer
{
	Queue<Patient*> requests;								// Requests Yet to Arrive
	
	ArrList<Hospital*> hospitals;							// List of All Loaded Hospitals

	ArrList<Patient*> routedRequests;						// Patients Routed to Hospitals

	Queue<CancellationRequest> cancellationRequests;		// Patients Cancellation Request Yet to Arrive

	int distanceMatrix[MAXHOSPITAL][MAXHOSPITAL];			// Weighted Graph Adjacency Matrix 

	int numOfHospitals;										// Number of Loaded Hospitals

	int worldTime;											// Current Timestep of the World

	int numOfRequests;										// Total Number of Requests Loaded

public:

	void Load(string filepath);

	int getFastestEmergency();

	void Advance();

};