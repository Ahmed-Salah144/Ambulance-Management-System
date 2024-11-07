#pragma once
#include"Lab/priQueue.h"
#include"Car.h"
class CarPriQueue :public priQueue<Car*>
{

public:

	// TO DO :

	Car* CancelPatientRequest(int patientID);	// returns pointer to car that had the patient and removes it from list if found
	//otherwise returns null

	int getCount(); // Returns number of cars

	void print(); //Loops and prints all cars as needed in output (<< is overloaded for Car)
};