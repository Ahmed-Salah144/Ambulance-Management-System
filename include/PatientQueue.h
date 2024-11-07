#pragma once
#include"Lab/LinkedQueue.h"
#include"Patient.h"
class PatientQueue : public LinkedQueue<Patient*>
{
public:

	bool CancelPatientRequest(int patientID);	// returns true if the request was found and cancelled false otherwise

	void print();		// prints all patients in list as needed in output(<< is overloaded for Patient) 
};