#include "../include/Organizer.h"
Organizer::Organizer()
{
	//numOfCarsNC = 0;
	//numOfCarsSC = 0;
	//numOfCars = 0;
	//numOfPatientsEP = 0;
	//numOfPatientsSP = 0;
	//numOfPatientsNP = 0;
	numOfPatients = 0;
	worldTime = 0;
	//numofEProuted = 0;
	failureTime = 0;

	backFailureChance = 0;

	outFailureChance = 0;

	hospitalFailureChance = 0;

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

	srand(time(0));

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

		//numOfCarsSC += scNum;

		//numOfCarsNC += ncNum;

		Hospital* temp = new Hospital(i+1,scNum,ncNum,scSpeed,ncSpeed,this);

		hospitals.InsertEnd(temp);
	}

	//numOfCars = numOfCarsNC + numOfCarsSC;

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
			//numOfPatientsEP++;
		}
		else if (patientTypeString == "SP")
		{
			pT = SP;
			//numOfPatientsSP++;
		}
		else
		{
			pT = NP;
			//numOfPatientsNP++;
		}

		Patient* temp = new Patient(patientID,requestTime,hospitalID,pT,distanceToHospital,caseSeverity);
		
		patients.enqueue(temp);
	}
	// Loading Request Cancellation Data

	int numOfCancellations;

	file >> numOfCancellations;

	for (int i = 0; i < numOfCancellations; i++)
	{
		CancellationRequest temp{0,0,0};

		file >> temp.requestTime >> temp.patientID>>temp.HospitalID;

		cancellationRequests.enqueue(temp);
	}

	file >> failureTime >> outFailureChance >> backFailureChance >> hospitalFailureChance;

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
	int busyTimeSum = 0;
	int scCount = 0;
	int ncCount = 0;
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
		delete ptr;
	}
	for (int i = 1; i <= numOfHospitals; i++)
	{
		Car* car = nullptr;
		while (car = hospitals[i]->HandNCarOver())
		{
			ncCount++;
			busyTimeSum += car->getBusyTime();
			delete car;
		}
		while (car = hospitals[i]->HandSCarOver())
		{
			scCount++;
			busyTimeSum += car->getBusyTime();
			delete car;
		}
	}
	outfile << "Patients: " << npCount + spCount + epCount << "\t[NP: " << npCount << ", SP: " << spCount << ", EP: " << epCount << "]\n";
	outfile << "Hospitals: " << numOfHospitals << endl;
	outfile << "Cars: " << ncCount + scCount<< "\t[SCar: " << scCount << ", NCar: " << ncCount <<"]\n";
	outfile << "Average Wait Time = " << (waitTimeSum * 10 / (npCount + spCount + epCount)) / 10.0f << endl << endl;
	outfile << "Average Busy Time = " << (busyTimeSum * 10 / (ncCount + scCount)) / 10.0f << endl;
	outfile << "Average Utilization = " << (busyTimeSum*100/(ncCount + scCount))/worldTime << "%\n";
	//busy time and utilisation
	//THIS IS NOT FINISHED
}

void Organizer::Simulate(int x)
{
	Load("test2.txt");
	while (!hospitals.isEmpty() || !patients.isEmpty())
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

		Patient* assignedPatient = outListFront->getAssignedPatient();

		assignedPatient->setPickupTime(pickupTime);

		//outListFront->IncrementFreeTime(pickupTime - assignmentTime);

		backList.enqueue(outListFront,-(2*worldTime- assignedPatient->getAssignmentTime()));//Inversion of expected arrival time

		if (assignedPatient->getFailedCar())
		{
			Car* brokenCar = assignedPatient->getFailedCar();
			backList.enqueue(brokenCar, -(2 * worldTime - assignedPatient->getAssignmentTime()));
			assignedPatient->setFailedCar(nullptr);

		}

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

		if (backListFront->getCheckupTime() == -1 && backListFront->getAssignedPatient())
		{
			finishedPatient = backListFront->getAssignedPatient();

			finishList.enqueue(finishedPatient);

			finishedPatient->setFinishTime(finishTime);

			backListFront->setAssignedPatient(nullptr);

			//backListFront->IncrementFreeTime(finishTime - finishedPatient->getPickupTime());

			hospitals[backListFront->getHID()]->ReturnCarToFreeList(backListFront,worldTime);
		}
		else if(backListFront->getCheckupTime() == -1)
			hospitals[backListFront->getHID()]->ReturnCarToFreeList(backListFront,worldTime);
		else
			checkupList.enqueue(backListFront, -(worldTime+backListFront->getCheckupTime()));

		backList.peek(backListFront, finishTime);
		finishTime = -finishTime;
	}

	Car* checkupListFront = nullptr;
	finishTime = 0;
	checkupList.peek(checkupListFront, finishTime);
	finishTime = -finishTime;

	while (!checkupList.isEmpty() && finishTime <= worldTime)
	{
		checkupList.dequeue(checkupListFront, finishTime);
		finishTime = -finishTime;

		checkupListFront->setCheckupTime(-1);
		hospitals[checkupListFront->getHID()]->ReturnCarToFreeList(checkupListFront,worldTime);

		checkupList.peek(checkupListFront, finishTime);
		finishTime = -finishTime;
	}

	CancellationRequest cancellation{-1,-1,-1};
	cancellationRequests.peek(cancellation);
	while (!cancellationRequests.isEmpty() && cancellation.requestTime <= worldTime)
	{
		cancellationRequests.dequeue(cancellation);
		Car * cancelledCar = outList.CancelPatientRequest(cancellation.patientID);
		if (cancelledCar)
		{
			Patient* cancelledPatient = cancelledCar->getAssignedPatient();
			cancelledCar->setAssignedPatient(nullptr);

			backList.enqueue(cancelledCar, - (2*worldTime - cancelledPatient->getAssignmentTime()));

			delete cancelledPatient;
		}
		else
		{
			hospitals[cancellation.HospitalID]->CancelPatient(cancellation.patientID);
		}
		cancellationRequests.peek(cancellation);
	}
	Car* failedCar = nullptr;

	failedCar = outList.CheckOutFailure(outFailureChance, failureTime);

	if (failedCar)
		OutCarFailure(failedCar);

	failedCar = nullptr;

	failedCar = backList.CheckBackFailure(backFailureChance,failureTime);

	if (failedCar)
	{
		switch (failedCar->getCarType())
		{
		case SC:
			if (hospitals[failedCar->getHID()]->isSCEmpty())
			{
				backList.enqueue(failedCar, -(failedCar->getAssignedPatient()->getAssignmentTime() + failedCar->getAssignedPatient()->getDistance() + failedCar->getCarSpeed()));
				failedCar->setCheckupTime(-1);
			}
			else
				BackCarFailure(failedCar);
			break;
		case NC:
			if (hospitals[failedCar->getHID()]->isNCEmpty())
			{
				backList.enqueue(failedCar, -(failedCar->getAssignedPatient()->getAssignmentTime()+ failedCar->getAssignedPatient()->getDistance() +failedCar->getCarSpeed()));
				failedCar->setCheckupTime(-1);
			}
			else
				BackCarFailure(failedCar);
			break;
		}
	}
	int failedHospitalID = CheckHospitalFailure();

	if (failedHospitalID && !hospitals[failedHospitalID]->isFailed())
	{
		int nearestID = getNearestHospital(failedHospitalID);

		Patient* patient=nullptr;
		while (patient = hospitals[failedHospitalID]->HandNPOver())
		{
			hospitals[nearestID]->EnqueueNormalPatient(patient);
		}
		while (patient = hospitals[failedHospitalID]->HandSPOver())
		{
			hospitals[nearestID]->EnqueueSpecialPatient(patient);
		}
		while (patient = hospitals[failedHospitalID]->HandEPOver())
		{
			hospitals[nearestID]->EnqueueEmergencyPatient(patient);
		}
		hospitals[failedHospitalID]->Clear();

	}
	for (int i = 1; i <= numOfHospitals; i++)
	{
		hospitals[i]->Update();
	}
	if (UIPtr->getMode() == INTERACTIVE)
		while (UIPtr->printInterface());
}

void Organizer::OutCarFailure(Car* car)
{
	Patient* patient = car->getAssignedPatient();

	backList.enqueue(car, -(2 * worldTime - patient->getAssignmentTime()));

	car->setAssignedPatient(nullptr);

	hospitals[patient->getHospitalID()]->EnqueueFailedPatient(patient);

}

void Organizer::BackCarFailure(Car* car)
{
	Patient* patient = car->getAssignedPatient();

	car->setAssignedPatient(nullptr);

	patient->setFailedCar(car);

	patient->setDistance(patient->getDistance() - ( worldTime - patient->getPickupTime()) * car->getCarSpeed());

	hospitals[patient->getHospitalID()]->EnqueueFailedPatient(patient);
}

int Organizer::CheckHospitalFailure()
{
	int random = rand() % 100;
	if (random <= hospitalFailureChance)
	{
		return random = rand() % numOfHospitals + 1;
	}
	return 0;
}

int Organizer::getNearestHospital(int hospitalID)
{
	int min = INT_MAX;
	int closestID = -1;
	for (int i = 1; i <= numOfHospitals; i++)
	{
		if (distanceMatrix[hospitalID][i] < min && i!=hospitalID)
		{
			closestID = i;
		}
	}
	return closestID;
}

/*void Organizer::MoveToFinish(Patient* p)
{
	finishList.enqueue(p);
}*/

void Organizer::MoveToOut(Car* c)
{
	c->getAssignedPatient()->setAssignmentTime(worldTime);
	c->setOutTime(worldTime);
	int pri = worldTime + 1 + c->getAssignedPatient()->getDistance() / c->getCarSpeed();
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
