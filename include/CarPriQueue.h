#pragma once
#include"Lab/priQueue.h"
#include"Car.h"
#include"../include/Lab/LinkedQueue.h"
class CarPriQueue :public LinkedQueue<Car*>
{
public:


	Car* CancelPatientRequest(int patientID) {
		Node<Car*>* current = frontPtr ;
		Node<Car*>* prev= nullptr;
		Car* cancelled = nullptr;
		while (current) {
			if (current->getItem()->getAssignedPatient()->getID() == patientID) {
				if (prev == nullptr) {

					cancelled = current->getItem();
					delete current;
					frontPtr = current->getNext();
				}
				else
				{
					cancelled = current->getItem();
					delete current;
					prev->setNext(current->getNext());
				}
			}
			else
			{
				prev = current;
				current = current->getNext();
			}
			
		}
		return cancelled; }	// returns pointer to car that had the patient and removes it from list if found
	//otherwise returns null

	int getCount() { 
		Node<Car*>* current = frontPtr;
		int count=0;
		while (current) {
			count += 1;
			current = current->getNext();

		}
	    return count ;
	
	} // Returns number of cars

	void print() {
		Node<Car*>* current = frontPtr;
		if (!current)
			return;
		while (current->getNext()) {
			cout << *(current->getItem()) << ", ";
			current = current->getNext();
		}
		cout << *(current->getItem());

	} //Loops and prints all cars as needed in output (<< is overloaded for Car)
};