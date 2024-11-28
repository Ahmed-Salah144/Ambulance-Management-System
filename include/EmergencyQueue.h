#pragma once
#include"Lab/priQueue.h"
#include"Patient.h"
class EmergencyQueue : public priQueue<Patient*>
{
public:
	// prints all patients in list as needed in output(<< is overloaded for Patient) 
	void print() {
		priNode<Patient*>* current = head;
		int pri = -1;
		if (!current)
			return;
		while (current->getNext()) {
			cout << *(current->getItem(pri)) <<", ";
			current = current->getNext();
		}
		cout << *(current->getItem(pri));
	}		

	int getCount() { 
		priNode<Patient*>* current = head;
		int 	count = 0;
		int pri;
		while (current) {
			if(current->getItem(pri)->getPatientType()==EP){
				count += 1;
			}
			current = current->getNext();
		}
		return count;
	}
};