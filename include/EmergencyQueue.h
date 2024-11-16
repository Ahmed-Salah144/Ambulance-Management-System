#pragma once
#include"Lab/LinkedQueue.h"
#include"Patient.h"
class EmergencyQueue : public LinkedQueue<Patient*>
{
public:

	void print() {}		// prints all patients in list as needed in output(<< is overloaded for Patient) 

	int getCount() { return 0; }
};