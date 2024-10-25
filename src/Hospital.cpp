#include "../include/Hospital.h"

Hospital::Hospital(int id, int scNum, int ncNum, int scSpeed, int ncSpeed)
	:ID(id),
	numOfSC(scNum),
	numOfNC(ncNum)
{
	for (int i = 0; i < scNum; i++)
	{
		Car* temp = new Car(this->ID,SC, scSpeed);
		readySCList.InsertEnd(temp);
	}
	for (int i = 0; i < ncNum; i++)
	{
		Car* temp = new Car(this->ID, NC, ncSpeed);
		readyNCList.InsertEnd(temp);
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
	EPqueue.enqueue(patient);
}

bool Hospital::HandleEmergencyPatient(Patient* patient)
{
	if (readyNCList.getLength() + readySCList.getLength() > getEmergencyQueueLength())
	{
		EnqueueSpecialPatient(patient);
		return true;
	}
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
