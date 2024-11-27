#pragma once
#include"Lab/LinkedQueue.h"
#include"Patient.h"
class EmergencyQueue : public LinkedQueue<Patient*>
{
public:
	// prints all patients in list as needed in output(<< is overloaded for Patient) 
	void print() {
		Node<Patient*>* current = frontPtr;
		while (current) {
			cout << current->getItem() <<", ";
			current = current->getNext();
		}
	}		

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