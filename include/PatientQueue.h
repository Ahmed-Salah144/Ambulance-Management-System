#pragma once
#include"Lab/LinkedQueue.h"
#include"Patient.h"
#include "CarPriQueue.h"
class PatientQueue : public LinkedQueue<Patient*>
{

public:
	
	


	bool CancelPatientRequest(int patientID) { 
		Node<Patient*>* current = frontPtr;
		while (current) {
			if (current->getItem()->getID() == patientID) {
				return true;
			}
			else
				current = current->getNext();
		}
		
	
		
		return false; }	// returns true if the request was found and cancelled false otherwise

	// prints all patients in list as needed in output(<< is overloaded for Patient)
	void print() {
		Node<Patient*>* current = frontPtr;
		while (current) {
			cout << current->getItem() << ", ";
			current = current->getNext();
		}
	}		 

	int getCount() { 
		Node<Patient*>* current = frontPtr;
	int 	count = 0;
		while (current) {
			count += 1;
			current = current->getNext();
		}
		return count;
	}
};