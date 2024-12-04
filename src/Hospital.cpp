#include "../include/Hospital.h"
#include "../include/Organizer.h"
Hospital::Hospital(int id, int scNum, int ncNum, int scSpeed, int ncSpeed,Organizer* o)
	:ID(id),
	numOfSC(scNum),
	numOfNC(ncNum)
{
	organizer = o;
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
	if (readyNCList.getCount() + readySCList.getCount() > getEmergencyQueueLength())
	{
		EnqueueEmergencyPatient(patient);
		return true;
	}
	return false;
}

int Hospital::getEmergencyQueueLength()
{
	return EPqueue.getCount();
}

void Hospital::Update()
{

	//Update Car position
	//assign cars to patients
	while (!EPqueue.isEmpty() && ! readyNCList.isEmpty())
	{

		Patient* patient;
		Car* car;
		int severity;
		EPqueue.dequeue(patient,severity);
		readyNCList.dequeue(car);
		car->setAssignedPatient(patient);
		organizer->MoveToOut(car);
	}
	while (!EPqueue.isEmpty() && !readySCList.isEmpty())
	{

		Patient* patient;
		Car* car;
		int severity;
		EPqueue.dequeue(patient, severity);
		readyNCList.dequeue(car);
		car->setAssignedPatient(patient);
		organizer->MoveToOut(car);
	}
	while (!SPqueue.isEmpty() && !readySCList.isEmpty())
	{

		Patient* patient;
		Car* car;
		SPqueue.dequeue(patient);
		readySCList.dequeue(car);
		car->setAssignedPatient(patient);
		organizer->MoveToOut(car);
	}
	while (!NPqueue.isEmpty() && !readyNCList.isEmpty())
	{

		Patient* patient;
		Car* car;
		NPqueue.dequeue(patient);
		readyNCList.dequeue(car);
		car->setAssignedPatient(patient);
		organizer->MoveToOut(car);
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
