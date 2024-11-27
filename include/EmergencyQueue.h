#pragma once
#include"Lab/LinkedQueue.h"
#include"Patient.h"
class EmergencyQueue : public LinkedQueue<Patient*>
{
public:

	void print() {}		// prints all patients in list as needed in output(<< is overloaded for Patient) 

	int getCount() { 
		Node<Patient*>* current = frontPtr;
		int 	count = 0;
		while (current) {
			if(current->getItem()->getPatientType()==EP){
				count += 1;
			}
			current = current->getNext();
		}
		return count;
	}
};