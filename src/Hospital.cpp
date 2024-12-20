#include "../include/Hospital.h"
#include "../include/Organizer.h"
Hospital::Hospital(int id, int scNum, int ncNum, int scSpeed, int ncSpeed,Organizer* o)
	:ID(id),
	numOfSC(scNum),
	numOfNC(ncNum)
{
	organizer = o;
	failed = false;
	nearestHospital = nullptr;
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
	if (failed && nearestHospital && nearestHospital->ID != ID)
	{
		organizer->switchPatientHospital(patient, nearestHospital->ID);
		nearestHospital->EnqueueSpecialPatient(patient);
	}
	else
		SPqueue.enqueue(patient);
}

void Hospital::EnqueueNormalPatient(Patient* patient)
{
	if (failed && nearestHospital && nearestHospital->ID != ID)
	{
		organizer->switchPatientHospital(patient, nearestHospital->ID);
		nearestHospital->EnqueueNormalPatient(patient);
	}
	else
	NPqueue.enqueue(patient);
}

void Hospital::EnqueueEmergencyPatient(Patient* patient)
{
	if (failed && nearestHospital && nearestHospital->ID != ID)
	{
		organizer->switchPatientHospital(patient, nearestHospital->ID);
		nearestHospital->EnqueueEmergencyPatient(patient);
	}
	else
	EPqueue.enqueue(patient,patient->getCaseSeverity());
}

void Hospital::EnqueueFailedPatient(Patient* patient)
{
	switch (patient->getPatientType())
	{
	case NP:
		if (failed && nearestHospital && nearestHospital->ID != ID)
		{
			organizer->switchPatientHospital(patient, nearestHospital->ID);
			nearestHospital->EnqueueFailedPatient(patient);
		}
		else
			NPqueue.enqueueFront(patient);
		break;
	case SP:
		if (failed && nearestHospital && nearestHospital->ID != ID)
		{
			nearestHospital->EnqueueFailedPatient(patient);
			organizer->switchPatientHospital(patient, nearestHospital->ID);
		}
		else
			SPqueue.enqueueFront(patient);
		break;
	case EP:
		if (failed && nearestHospital && nearestHospital->ID != ID)
		{
			nearestHospital->EnqueueFailedPatient(patient);
			organizer->switchPatientHospital(patient, nearestHospital->ID);
		}
		else
			EPqueue.enqueue(patient, INT_MAX);
		break;

	}
}

bool Hospital::HandleEmergencyPatient(Patient* patient)
{
	if (failed)
		return false;
	if (readyNCList.getCount() + readySCList.getCount() > getEmergencyQueueLength())
	{
		EnqueueEmergencyPatient(patient);
		return true;
	}
	return false;
}

void Hospital::CancelPatient(int patientID)
{
	if (failed && nearestHospital && nearestHospital->ID != ID)
	{
		nearestHospital->CancelPatient(patientID);
		return;
	}
	Patient* cancelledptr=NPqueue.CancelPatientRequest(patientID);
	if (cancelledptr)
	{
		delete cancelledptr;
	}
}

int Hospital::getEmergencyQueueLength()
{
	if (failed)
		return INT_MAX;
	return EPqueue.getCount();
}

void Hospital::Update()
{

	//assign cars to patients
	if (failed)
		return;
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
		Car* car=nullptr;
		int severity;
		EPqueue.dequeue(patient, severity);
		readySCList.dequeue(car);
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

void Hospital::ReturnCarToFreeList(Car* car,int time)
{
	if (failed)
	{
		delete car;
		return;
	}
	car->IncrementBusyTime(time - car->getOutTime());
	car->setOutTime(-1);
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

Car* Hospital::HandNCarOver()
{
	Car* car = nullptr;
	readyNCList.dequeue(car);
	return car;
}

Car* Hospital::HandSCarOver()
{
	Car* car = nullptr;
	readySCList.dequeue(car);
	return car;
}

Patient* Hospital::HandNPOver()
{
	Patient* ptr=nullptr;
	NPqueue.dequeue(ptr);
	return ptr;
}
Patient* Hospital::HandSPOver()
{
	Patient* ptr = nullptr;
	SPqueue.dequeue(ptr);
	return ptr;
}
Patient* Hospital::HandEPOver()
{
	Patient* ptr = nullptr;
	int pri;
	EPqueue.dequeue(ptr,pri);
	return ptr;
}

void Hospital::Fail(Hospital* nearest)
{
	failed = true;
	nearestHospital = nearest;
}

bool Hospital::isFailed()
{
	return failed;
}

bool Hospital::isNCEmpty()
{
	return readyNCList.isEmpty();
}

bool Hospital::isSCEmpty()
{
	return readySCList.isEmpty();
}

bool Hospital::isEmpty()
{
	if (readySCList.getCount() == numOfSC && readyNCList.getCount() == numOfNC && 
		SPqueue.isEmpty() && NPqueue.isEmpty() && EPqueue.isEmpty())//Cars Falling through?
		return true;
	return false;
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
