#pragma once
#include"Lab/priQueue.h"
#include"Car.h"
#include <ctime>
#include <cstdlib>
class CarPriQueue :public priQueue<Car*>
{
public:


	Car* CancelPatientRequest(int patientID) 
	{
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
				break;
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

	Car* CheckOutFailure(int chance,int checkuptimerange)
	{
		if (isEmpty())
			return nullptr;
		int random = rand()%100;
		if (random <= chance)
		{
			int pri;
			Car* car = nullptr;
			priNode<Car*>* current = head;
			random = rand() % getCount();
			if (random == 0)
			{
				car = current->getItem(pri);

				head = head->getNext();

				delete current;

				car->setCheckupTime(rand() % checkuptimerange + 1);

				return car;
			}
			for (int i = 0; i < random-1; i++)
			{
				current = current->getNext();
			}
			if (!current->getNext())
			{
				cerr << "Error in Failure probability" << endl;
				return nullptr;
			}
			priNode<Car*>* temp = current->getNext();

			car = temp->getItem(pri);

			current->setNext(temp->getNext());

			delete temp;

			car->setCheckupTime(rand() % checkuptimerange + 1 );

			return car;
		}
		return nullptr;
	}
	Car* CheckBackFailure(int chance, int checkuptimerange)
	{
		if (isEmpty())
			return nullptr;
		int random = rand() % 100;
		if (random <= chance)
		{
			int pri;
			Car* car = nullptr;
			priNode<Car*>* current = head;
			random = rand() % getCount();
			if (random == 0)
			{
				car = current->getItem(pri);
				if (car->getCheckupTime() > 0 || car->getAssignedPatient() == nullptr)
					return nullptr;
				head = head->getNext();

				delete current;

				car->setCheckupTime(rand() % checkuptimerange + 1);

				return car;
			}
			for (int i = 0; i < random - 1; i++)
			{
				current = current->getNext();
			}
			if (!current->getNext())
			{
				cerr << "Error in Failure probability" << endl;
				return nullptr;
			}
			priNode<Car*>* temp = current->getNext();

			car = temp->getItem(pri);

			if (car->getCheckupTime() > 0 || car->getAssignedPatient() == nullptr)
				return nullptr;

			current->setNext(temp->getNext());

			delete temp;

			car->setCheckupTime(rand() % checkuptimerange + 1);

			return car;
		}
		return nullptr;
	}
};