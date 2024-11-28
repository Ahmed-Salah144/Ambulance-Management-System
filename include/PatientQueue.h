#pragma once
#include"Lab/LinkedQueue.h"
#include"Patient.h"
#include "CarPriQueue.h"
class PatientQueue : public LinkedQueue<Patient*>
{

public:
	
	Patient* CancelPatientRequest(int patientID) { 
		Node<Patient*>* current = frontPtr;
		Node<Patient*>* prev = nullptr;
		Patient* cancelled = nullptr;
		while (current) {
			if (current->getItem()->getID() == patientID) {
				if (prev == nullptr)
				{
					cancelled = current->getItem();
					frontPtr = current->getNext();
					delete current;
				}
				else
				{
					cancelled = current->getItem();
					prev->setNext(current->getNext());
					delete current;
				}
			}
			else
			{
				prev = current;
				current = current->getNext();
			}
		}		
		return cancelled; }	// returns cancelled patient if the request was found and cancelled and nullptr otherwise

	// prints all patients in list as needed in output(<< is overloaded for Patient)
	void print() {
		Node<Patient*>* current = frontPtr;
		if (!current)
			return;
		while (current->getNext()) {
			cout << *(current->getItem()) << ", ";
			current = current->getNext();
		}
		cout << *(current->getItem());
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