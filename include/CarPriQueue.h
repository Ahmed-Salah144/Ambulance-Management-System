#pragma once
#include"Lab/priQueue.h"
#include"Car.h"
class CarPriQueue :public priQueue<Car*>
{
public:


	Car* CancelPatientRequest(int patientID) {
		priNode<Car*>* current = head;
		priNode<Car*>* prev= nullptr;
		Car* cancelled = nullptr;
		int pri;
		while (current) {
			if (current->getItem(pri)->getAssignedPatient()->getID() == patientID) {
				if (prev == nullptr) {

					cancelled = current->getItem(pri);
					head = current->getNext();
					delete current;
				}
				else
				{
					cancelled = current->getItem(pri);
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
		return cancelled; }	// returns pointer to car that had the patient and removes it from list if found
	//otherwise returns null

	int getCount() { 
		priNode<Car*>* current = head;
		int count=0;
		while (current) {
			count += 1;
			current = current->getNext();

		}
	    return count ;
	
	} // Returns number of cars

	void print() {
		priNode<Car*>* current = head;
		int pri;
		if (!current)
			return;
		while (current->getNext()) {
			cout << *(current->getItem(pri)) << ", ";
			current = current->getNext();
		}
		cout << *(current->getItem(pri));

	} //Loops and prints all cars as needed in output (<< is overloaded for Car)
};