#include "../include/Organizer.h"

Organizer::Organizer()
{
	numOfCarsNC = 0;
	numOfCarsSC = 0;
	numOfCars = 0;
	numOfPatientsEP = 0;
	numOfPatientsSP = 0;
	numOfPatientsNP = 0;
	numOfPatients = 0;
	worldTime = 0;
	numofEProuted = 0;
	numOfHospitals = 0;
}
void Organizer::Load(string filepath)
{
	ifstream file(filepath);  

	//assert(file);				// Aborts program if file was not loaded
	
	file >> numOfHospitals;

	int scSpeed, ncSpeed;		// Special and Normal Car speed

	file >> scSpeed >> ncSpeed;

	for (int i = 0; i < numOfHospitals; i++)
	{
		for (int j = 0; j < numOfHospitals; j++)
		{
			file >> distanceMatrix[i][j];
		}
	}

	for (int i = 0; i < numOfHospitals; i++)
	{	
		int scNum,ncNum;			//Number of Special and Normal Cars for Each Hospital

		file >> scNum >> ncNum;

		numOfCarsSC += scNum;

		numOfCarsNC += ncNum;

		Hospital* temp = new Hospital(i+1,scNum,ncNum,scSpeed,ncSpeed);

		hospitals.InsertEnd(temp);
	}

	numOfCars = numOfCarsNC + numOfCarsSC;

	file >> numOfPatients;


	for (int i = 0; i < numOfPatients; i++)
	{
		string patientTypeString="";
		PatientType pT;
		int requestTime=-1;
		int patientID=-1;
		int hospitalID=-1;
		int distanceToHospital=-1;
		int caseSeverity=-1;

		//Loading Request Data

		file >> patientTypeString >> requestTime >> patientID >> hospitalID >> distanceToHospital;


		if (patientTypeString == "EP")
		{
			file >> caseSeverity;
			pT = EP;
			numOfPatientsEP++;
		}
		else if (patientTypeString == "SP")
		{
			pT = SP;
			numOfPatientsSP++;
		}
		else
		{
			pT = NP;
			numOfPatientsNP++;
		}

		Patient* temp = new Patient(patientID,requestTime,hospitalID,pT,distanceToHospital,caseSeverity);
		
		patients.enqueue(temp);
	}
	// Loading Request Cancellation Data

	int numOfCancellations;

	file >> numOfCancellations;

	for (int i = 0; i < numOfCancellations; i++)
	{
		CancellationRequest temp;

		file >> temp.requestTime >> temp.patientID;

		cancellationRequests.enqueue(temp);
	}
	UIPtr = new UI(this);
}

void Organizer::Output()
{

}

int Organizer::getFastestEmergency()
{
	int HID = 1;

	int minQueueLength = hospitals[1]->getEmergencyQueueLength();

	for (int i = 2; i <= numOfHospitals; i++)
	{
		if (minQueueLength > hospitals[i]->getEmergencyQueueLength())
		{
			minQueueLength = hospitals[i]->getEmergencyQueueLength();

			HID = i;
		}
	}
	return HID;
}

void Organizer::Advance()
{
	worldTime++;						// Advance Timestep

	Patient* queueFront;				// Used to Peek the Requests Queue

	patients.peek(queueFront);

	while (!patients.isEmpty() && queueFront->getRequestTime() < worldTime)
	{
		patients.dequeue(queueFront);
		switch (queueFront->getPatientType())
		{
		case NP:
			hospitals[queueFront->getHospitalID()]->EnqueueNormalPatient(queueFront);
			break;
		case SP:
			hospitals[queueFront->getHospitalID()]->EnqueueSpecialPatient(queueFront);
			break;
		case EP:
			if (hospitals[queueFront->getHospitalID()]->HandleEmergencyPatient(queueFront))
			{
			}
			else
			{
				hospitals[getFastestEmergency()]->EnqueueEmergencyPatient(queueFront);
				//This function is not taking distance into account FIX IT
			}
			break;
		}
		patients.peek(queueFront);
	}
}

void Organizer::RandomSimulation()
{
	while (worldTime < 100)
	{
		worldTime++;
		for (int i = 1; i < numOfHospitals; i++)
		{
			hospitals[i]->RandomSim(this);
		}
		while (UIPtr->printHospitalData());
	}
}

void Organizer::SendToHospital()
{
	Patient* queueFront;				// Used to Peek the Requests Queue

	while (!patients.isEmpty())
	{
		patients.dequeue(queueFront);
		switch (queueFront->getPatientType())
		{
		case NP:
			hospitals[queueFront->getHospitalID()]->EnqueueNormalPatient(queueFront);
			break;
		case SP:
			hospitals[queueFront->getHospitalID()]->EnqueueSpecialPatient(queueFront);
			break;
		case EP:
			hospitals[queueFront->getHospitalID()]->EnqueueEmergencyPatient(queueFront);
			break;
		}
	}
}

void Organizer::MoveToFinish(Patient * p)
{
	finishList.enqueue(p);
}

void Organizer::MoveToOut(Car* c)
{
	outList.enqueue(c, 10);
}

void Organizer::MoveToBack()
{
	Car* carPtr=nullptr;
	int pri;
	outList.dequeue(carPtr,pri);
	if (carPtr)
		backList.enqueue(carPtr,pri);
}

void Organizer::MoveToFree()
{
	Car* carPtr=nullptr;
	int pri;
	backList.dequeue(carPtr,pri);
	if (carPtr)
		hospitals[carPtr->getHID()]->ReturnCar(carPtr);

}
