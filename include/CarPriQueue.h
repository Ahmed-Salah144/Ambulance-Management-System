#pragma once
#include"Lab/priQueue.h"
#include"Car.h"
#include"../include/Lab/LinkedQueue.h"
class CarPriQueue :public LinkedQueue<Car*>
{
public:

	// TO DO :

	Car* CancelPatientRequest(int patientID) {
		Node<Car*>* current = frontPtr ;
		Node<Car*>* prev= nullptr;
		while (current) {
			if (current->getItem()->getAssignedPatient()->getID() == patientID) {
				if (prev == nullptr) {
					frontPtr = current->getNext();
				}
				else
					prev->setNext(current->getNext());

				 return current->getItem();

			

			}
			prev = current;
			 current = current->getNext();
			
		}
		

		return nullptr; }	// returns pointer to car that had the patient and removes it from list if found
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
		int numCars = 0;
		int numSC = 0;
		int numNC = 0;
		while (current) {
			if (current->getItem()->getCarType() == SC) {
				numSC += 1;
				numCars += 1;
			}
			else {
				numNC += 1;
				numCars += 1;
			}
			current = current->getNext();
		}
		cout << "cars: " << numCars << "                     " << "[SCars: " << numSC << " , NCars: " << numNC << " ]" << endl;


	} //Loops and prints all cars as needed in output (<< is overloaded for Car)
};