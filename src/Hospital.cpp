#include "../include/Hospital.h"
#include "../include/Organizer.h"
Hospital::Hospital(int id, int scNum, int ncNum, int scSpeed, int ncSpeed)
	:ID(id),
	numOfSC(scNum),
	numOfNC(ncNum)
{
	for (int i = 0; i < scNum; i++)
	{
		Car* temp = new Car(this->ID,SC, scSpeed);
		readySCList.enqueue(temp);
	}
	for (int i = 0; i < ncNum; i++)
	{
		Car* temp = new Car(this->ID, NC, ncSpeed);
		readyNCList.enqueue(temp);
	}
}


void Hospital::EnqueueSpecialPatient(Patient* patient)
{
	SPqueue.enqueue(patient);
}

void Hospital::EnqueueNormalPatient(Patient* patient)
{
	NPqueue.enqueue(patient);
}

void Hospital::EnqueueEmergencyPatient(Patient* patient)
{
	EPqueue.enqueue(patient,patient->getCaseSeverity());
}

bool Hospital::HandleEmergencyPatient(Patient* patient)
{
	/*if (readyNCList.getLength() + readySCList.getLength() > getEmergencyQueueLength())
	{
		EnqueueSpecialPatient(patient);
		return true;
	}*/
	return false;
}

int Hospital::getEmergencyQueueLength()
{
	return EPqueue.getCount();
}

void Hospital::Update(int worldTime)
{
	//Update Car position
	//assign cars to patients
}

void Hospital::RandomSim(Organizer * o)
{
	int random = rand() % 100;
	Car* carPtr=nullptr;
	Patient* patientPtr=nullptr;
	switch (random / 5)
	{
	case 2:case 3:
		SPqueue.dequeue(patientPtr);
		if(patientPtr)
			o->MoveToFinish(patientPtr);
		break;
	case 4:
		int pri;
		EPqueue.dequeue(patientPtr,pri);
		if (patientPtr)
			o->MoveToFinish(patientPtr);
		break;
	case 5:case 6:
		NPqueue.dequeue(patientPtr);
		if (patientPtr)
			o->MoveToFinish(patientPtr);
		break;
	case 8:
		readySCList.dequeue(carPtr);
		if (carPtr)
			o->MoveToOut(carPtr);
		break;
	case 14:
		readyNCList.dequeue(carPtr);
		if (carPtr)
			o->MoveToOut(carPtr);
		break;
	case 16:case 17:
		o->MoveToBack();
		break;
	case 18:
		if (random == 90)
			break;
		o->MoveToFree();
		break;
	}
}

void Hospital::ReturnCar(Car* car)
{
	switch (car->getCarType())
	{
	case SC:
		readySCList.enqueue(car);
		break;
	case NC:
		readyNCList.enqueue(car);
		break;
	}
}

void Hospital::Clear()
{
	while (!readySCList.isEmpty())
	{
		Car* ptr;
		readySCList.dequeue(ptr);
		delete ptr;
	}
	while (!readyNCList.isEmpty())
	{
		Car* ptr;
		readyNCList.dequeue(ptr);
		delete ptr;
	}
	while (!EPqueue.isEmpty())
	{
		Patient* ptr;
		int pri;
		EPqueue.dequeue(ptr, pri);
		delete ptr;
	}
	while (!SPqueue.isEmpty())
	{
		Patient* ptr;
		SPqueue.dequeue(ptr);
		delete ptr;
	}
	while (!NPqueue.isEmpty())
	{
		Patient* ptr;
		NPqueue.dequeue(ptr);
		delete ptr;
	}
}

Hospital::~Hospital()
{
	Clear();
}
