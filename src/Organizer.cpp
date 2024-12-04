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
	UIPtr = nullptr;
	for (int i = 0; i < MAXHOSPITAL; i++)
		for (int j = 0; j < MAXHOSPITAL; j++)
			distanceMatrix[i][j] = 0;
}
void Organizer::Load(string filepath)
{
	ifstream file(filepath);  

	if (!file)
		return;
	
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

		Hospital* temp = new Hospital(i+1,scNum,ncNum,scSpeed,ncSpeed,this);

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

		file >> temp.requestTime >> temp.patientID>>temp.HospitalID;

		cancellationRequests.enqueue(temp);
	}
	UIPtr = new UI(this);
}

void Organizer::Output()
{
	ofstream outfile("Output.txt");
	if (!outfile)
	{
		cout << "Error Opening File" << endl;
		return;
	}
	int npCount = 0, spCount = 0, epCount = 0;
	int waitTimeSum = 0;
	outfile << "FT\tPID\tQT\tWT\n";
	while (!finishList.isEmpty())
	{
		Patient* ptr = nullptr;
		finishList.dequeue(ptr);
		outfile << ptr->getFinishTime() << "\t" << *ptr << "\t" << ptr->getRequestTime() << "\t" << ptr->getPickupTime() - ptr->getRequestTime() << endl;
		waitTimeSum += ptr->getPickupTime() - ptr->getRequestTime();
		switch (ptr->getPatientType())
		{
		case SP:
			spCount++;
			break;
		case NP:
			npCount++;
			break;
		case EP:
			epCount++;
			break;
		}
	}

	outfile << "Patients: " << npCount + spCount + epCount << "\t[NP: " << npCount << ", SP: " << spCount << ", EP: " << epCount << "]\n";
	outfile << "Hospitals: " << numOfHospitals << endl;

	//THIS IS NOT FINISHED
}

void Organizer::Simulate(int x)
{
	Load("test2.txt");
	while (worldTime<x)
	{
		Advance();
	}
	Output();
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

	Patient* patientsFront = nullptr;				// Used to Peek the Requests Queue

	patients.peek(patientsFront);

	while (!patients.isEmpty() && patientsFront->getRequestTime() <= worldTime)
	{
		patients.dequeue(patientsFront);
		switch (patientsFront->getPatientType())
		{
		case NP:
			hospitals[patientsFront->getHospitalID()]->EnqueueNormalPatient(patientsFront);
			break;
		case SP:
			hospitals[patientsFront->getHospitalID()]->EnqueueSpecialPatient(patientsFront);
			break;
		case EP:
			if (!hospitals[patientsFront->getHospitalID()]->HandleEmergencyPatient(patientsFront))
			{
				hospitals[getFastestEmergency()]->EnqueueEmergencyPatient(patientsFront);
				//This function is not taking distance into account FIX IT
			}
			break;
		}
		patients.peek(patientsFront);
	}

	Car* outListFront = nullptr;
	Patient* pickedPatient = nullptr;
	int pickupTime=0;
	outList.peek(outListFront,pickupTime);

	pickupTime = -pickupTime;				//Inverted Priority

	while (!outList.isEmpty() && pickupTime <= worldTime)
	{
		outList.dequeue(outListFront, pickupTime);
		pickupTime = -pickupTime;
		outListFront->getAssignedPatient()->setPickupTime(pickupTime);
		int assignmentTime = outListFront->getAssignedPatient()->getAssignmentTime();
		backList.enqueue(outListFront,-(2*worldTime-assignmentTime));//Inversion of expected arrival time
		outList.peek(outListFront, pickupTime);
		pickupTime = -pickupTime;
	}

	Car* backListFront = nullptr;
	Patient* finishedPatient = nullptr;
	int finishTime = 0;
	backList.peek(backListFront, finishTime);
	finishTime = -finishTime;

	while (!backList.isEmpty() && finishTime <= worldTime)
	{
		backList.dequeue(backListFront, finishTime);
		finishTime = -finishTime;

		finishedPatient = backListFront->getAssignedPatient();

		finishList.enqueue(finishedPatient);

		finishedPatient->setFinishTime(finishTime);

		backListFront->setAssignedPatient(nullptr);

		hospitals[backListFront->getHID()]->ReturnCar(backListFront);

		backList.peek(backListFront, finishTime);
		finishTime = -finishTime;
	}

	for (int i = 1; i <= numOfHospitals; i++)
	{
		hospitals[i]->Update();
	}
	if (UIPtr->getMode() == INTERACTIVE)
		while (UIPtr->printInterface());
}

/*void Organizer::MoveToFinish(Patient* p)
{
	finishList.enqueue(p);
}*/

void Organizer::MoveToOut(Car* c)
{
	c->getAssignedPatient()->setAssignmentTime(worldTime);
	int pri = worldTime + c->getAssignedPatient()->getDistance() / c->getCarSpeed();
	outList.enqueue(c,-pri);
}

/*void Organizer::MoveToBack()
{
	Car* carPtr=nullptr;
	int pri=1;
	outList.dequeue(carPtr,pri);
	if (carPtr)
		backList.enqueue(carPtr,pri);
}*/
/*
void Organizer::MoveToFree()
{
	Car* carPtr=nullptr;
	int pri = 1;
	backList.dequeue(carPtr,pri);
	if (carPtr)
		hospitals[carPtr->getHID()]->ReturnCar(carPtr);

}*/

Organizer::~Organizer()
{
	for (int i = 1; i <= numOfHospitals; i++)
	{
		hospitals[i]->Clear();
	}
	while (!finishList.isEmpty())
	{
		Patient* ptr;
		finishList.dequeue(ptr);
		delete ptr;
	}
	while (!patients.isEmpty())
	{
		Patient* ptr;
		patients.dequeue(ptr);
		delete ptr;
	}
	while (!backList.isEmpty())
	{
		Car* ptr;
		int pri;
		backList.dequeue(ptr,pri);
		delete ptr;
	}
	while (!outList.isEmpty())
	{
		Car* ptr;
		int pri;
		outList.dequeue(ptr,pri);
		delete ptr;
	}
	delete UIPtr;

}
