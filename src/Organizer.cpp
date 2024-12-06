#include "../include/Organizer.h"
#include <cassert>
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

	failedCarCount = 0;

	successfulCarCount = 0;

	failedHospitals = 0;

	numOfHospitals = 0;

	UIPtr = nullptr;

	for (int i = 0; i < MAXHOSPITAL; i++)
		for (int j = 0; j < MAXHOSPITAL; j++)
			distanceMatrix[i][j] = 0;
}
void Organizer::Load(string in)
{
	ifstream file(in);  

	if (!file)
		return;

	srand(time(0)*rand());

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

void Organizer::Output(string out)
{
	ofstream outfile(out);
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
	outfile << "Patients: " << npCount + spCount + epCount <<"/"<<numOfPatients<< "\t[NP: " << npCount << ", SP: " << spCount << ", EP: " << epCount << "]\n";
	outfile << "Hospitals: " << numOfHospitals << endl;
	outfile << "Cars: " << ncCount + scCount<< "\t[SCar: " << scCount << ", NCar: " << ncCount <<"]\n";
	if( failedHospitals == numOfHospitals || npCount + spCount + epCount == 0)
	{
		outfile << "Average Wait Time = " << "N/A" << endl;
		outfile << "Average Busy Time = " << "N/A" << endl;
		outfile << "Average Utilization = " << "N/A" << "\n";
		outfile << "Failed Cars = " << "N/A" << "%\n";
	}
	else
	{
		outfile << "Average Wait Time = " << (waitTimeSum * 100 / (npCount + spCount + epCount)) / 100.0f << endl;
		outfile << "Average Busy Time = " << (busyTimeSum * 100 / (ncCount + scCount)) / 100.0f << endl;
		outfile << "Average Utilization = " << (busyTimeSum * 1000 / (ncCount + scCount)) / 10.0f / worldTime << "%\n";
		outfile << "Failed Cars = " << (failedCarCount * 100 / successfulCarCount) / 100.0f << "%\n";
	}
	outfile << "Failed Cars = " << failedCarCount << "\n";
	outfile << "Failed Hospitals = " << failedHospitals << "\n";
	//busy time and utilisation
	//THIS IS NOT FINISHED
}

void Organizer::Simulate(string in,string out)
{
	Load(in);
	while ((!hospitals.isEmpty() || !patients.isEmpty()) && !hospitals.isFailed())
	{
		Advance();
	}
	Output(out);
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
	assert(worldTime < 10000000);

	ProcessPatientList();

	ProcessOutList();

	ProcessBackList();
	
	ProcessCheckupList();

	ProcessCancellationList();


	Car* failedCar = nullptr;
	if (failedCar = outList.CheckOutFailure(outFailureChance, failureTime))
		OutCarFailure(failedCar);

	//if (failedCar = backList.CheckBackFailure(outFailureChance, failureTime))
		//BackCarFailure(failedCar);

	//HospitalFailure();

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

	backList.enqueue(car, -(2 * worldTime - car->getOutTime()));

	car->setAssignedPatient(nullptr);

	hospitals[car->getHID()]->EnqueueFailedPatient(patient);

	//failedOut++;

}

void Organizer::BackCarFailure(Car* car)

{
	Patient* patient = car->getAssignedPatient();
	//if (!patient)
	//{
		//return;
	//}
	switch (car->getCarType())
	{
	case SC:
		if (hospitals[car->getHID()]->isSCEmpty() && !hospitals[car->getHID()]->isFailed())
		{
			backList.enqueue(car, -(patient->getAssignmentTime() + patient->getDistance() + car->getCarSpeed()));
			car->setCheckupTime(-1);
			return;
		}
		break;
	case NC:
		if (hospitals[car->getHID()]->isNCEmpty() && !hospitals[car->getHID()]->isFailed())
		{
			backList.enqueue(car, -(patient->getAssignmentTime() + patient->getDistance() + car->getCarSpeed()));
			car->setCheckupTime(-1);
			return;
		}
		break;
	}

	car->setAssignedPatient(nullptr);

	patient->setFailedCar(car);

	patient->setDistance(patient->getDistance() - ( worldTime - patient->getPickupTime()) * car->getCarSpeed());

	hospitals[car->getHID()]->EnqueueFailedPatient(patient);
	
	//failedBack++;
}

int Organizer::CheckHospitalFailure()
{
	int random = rand() % 10000;
	int x;
	if (random < hospitalFailureChance*100)
	{
		return rand() % numOfHospitals + 1;
	}
	return 0;
}

void Organizer::ProcessCancellationList()
{

	CancellationRequest cancellation{ -1,-1,-1 };

	cancellationRequests.peek(cancellation);

	while (!cancellationRequests.isEmpty() && cancellation.requestTime <= worldTime)
	{
		cancellationRequests.dequeue(cancellation);
		Car* cancelledCar = outList.CancelPatientRequest(cancellation.patientID);
		if (cancelledCar)
		{
			Patient* cancelledPatient = cancelledCar->getAssignedPatient();
			cancelledCar->setAssignedPatient(nullptr);

			backList.enqueue(cancelledCar, -(2 * worldTime - cancelledPatient->getAssignmentTime()));

			delete cancelledPatient;
		}
		else
		{
			hospitals[cancellation.HospitalID]->CancelPatient(cancellation.patientID);
		}
		cancellationRequests.peek(cancellation);
	}
}

void Organizer::ProcessCheckupList()
{
	Car* checkupListFront = nullptr;
	int finishTime = 0;
	checkupList.peek(checkupListFront, finishTime);
	finishTime = -finishTime;

	while (!checkupList.isEmpty() && finishTime <= worldTime)
	{
		checkupList.dequeue(checkupListFront, finishTime);
		finishTime = -finishTime;

		checkupListFront->setCheckupTime(-1);

		//assert(checkupListFront->getHID() <= numOfHospitals);

		hospitals[checkupListFront->getHID()]->ReturnCarToFreeList(checkupListFront, worldTime);

		checkupList.peek(checkupListFront, finishTime);
		finishTime = -finishTime;
	}

}

void Organizer::ProcessOutList()
{

	Car* outListFront = nullptr;
	Patient* pickedPatient = nullptr;
	int pickupTime = 0;
	outList.peek(outListFront, pickupTime);

	pickupTime = -pickupTime;				//Inverted Priority

	while (!outList.isEmpty() && pickupTime <= worldTime)
	{
		outList.dequeue(outListFront, pickupTime);

		pickupTime = -pickupTime;

		Patient* assignedPatient = outListFront->getAssignedPatient();

		assignedPatient->setPickupTime(pickupTime);

		//outListFront->IncrementFreeTime(pickupTime - assignmentTime);

		backList.enqueue(outListFront, -(2 * worldTime - assignedPatient->getAssignmentTime()));//Inversion of expected arrival time

		if (assignedPatient->getFailedCar())
		{
			Car* brokenCar = assignedPatient->getFailedCar();
			backList.enqueue(brokenCar, -(2 * worldTime - assignedPatient->getAssignmentTime()));
		}

		outList.peek(outListFront, pickupTime);

		pickupTime = -pickupTime;
	}
}

void Organizer::ProcessBackList()
{
	Car* backListFront = nullptr;
	Patient* finishedPatient = nullptr;
	int finishTime = 0;
	backList.peek(backListFront, finishTime);
	finishTime = -finishTime;

	while (!backList.isEmpty() && finishTime <= worldTime)
	{
		backList.dequeue(backListFront, finishTime);
		finishTime = -finishTime;

		if (backListFront->getAssignedPatient())
		{
			finishedPatient = backListFront->getAssignedPatient();

			assert(worldTime > 0);

			finishedPatient->setFinishTime(worldTime);

			finishList.enqueue(finishedPatient);

			backListFront->setAssignedPatient(nullptr);

			//backListFront->IncrementFreeTime(finishTime - finishedPatient->getPickupTime());

			//assert(backListFront->getHID() <= numOfHospitals);
			if (finishedPatient->getFailedCar())
			{
				finishedPatient->setFailedCar(nullptr);
			}

			hospitals[backListFront->getHID()]->ReturnCarToFreeList(backListFront, worldTime);
			successfulCarCount++;
		}
		else if (backListFront->getCheckupTime() == -1)
		{
			hospitals[backListFront->getHID()]->ReturnCarToFreeList(backListFront, worldTime);
			successfulCarCount++;
		}
		else
		{
			checkupList.enqueue(backListFront, -(worldTime + backListFront->getCheckupTime()));
			failedCarCount++;
		}
		backList.peek(backListFront, finishTime);
		finishTime = -finishTime;
	}
}

void Organizer::ProcessPatientList()
{
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
			/*if (!hospitals[patientsFront->getHospitalID()]->HandleEmergencyPatient(patientsFront))
			{
				hospitals[getFastestEmergency()]->EnqueueEmergencyPatient(patientsFront);
				//This function is not taking distance into account FIX IT
			}*/
			hospitals[patientsFront->getHospitalID()]->EnqueueEmergencyPatient(patientsFront);
			break;
		default:
			assert(1 == 0);
		}
		patients.peek(patientsFront);
	}
}

void Organizer::HospitalFailure()
{
	int failedHospitalID = CheckHospitalFailure();
	if (!failedHospitalID || hospitals[failedHospitalID]->isFailed())
		return;

	int nearestID = getNearestHospital(failedHospitalID);

	Patient* patient = nullptr;
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

	hospitals[failedHospitalID]->Fail(hospitals[failedHospitalID]);

	Car* car = nullptr;

	while (car = backList.FailCarOfHospital(failedHospitalID, failureTime))
	{
		BackCarFailure(car);
	}

	while (car = outList.FailCarOfHospital(failedHospitalID, failureTime))
	{
		OutCarFailure(car);
	}
	failedHospitals++;
}

int Organizer::getNearestHospital(int hospitalID)
{
	int min = INT_MAX;
	int closestID = -1;
	for (int i = 1; i <= numOfHospitals; i++)
	{
		if (distanceMatrix[hospitalID-1][i-1] < min && i!=hospitalID && !hospitals[hospitalID]->isFailed())
		{
			closestID = i;
			min = distanceMatrix[hospitalID - 1][i - 1];
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
	Car::ResetCarCount();
	delete UIPtr;


}
