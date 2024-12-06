#include "../include/Car.h"

int Car::totalNumberOfCars = 0;

Car::Car(int hid, CarType cT, int speed)
	: HID(hid),
	carType(cT),
	carSpeed(speed)
{
	ID = ++totalNumberOfCars;
	//carStatus = READY;
	assignedPatient = nullptr;
	busyTime = 0;
	checkupTime = -1;
	outTime = -1;
	assert(hid <= 200);
}
void Car::ResetCarCount()
{
	totalNumberOfCars = 0;
}
ostream& operator<<(ostream& out, Car& C)
{
	if (C.getCarType() == SC)
		out << "S";
	else
		out << "N";

	out << C.getID() << "_H" << C.getHID();

	if (C.getAssignedPatient() != nullptr)
		out << "_P" << C.getAssignedPatient()->getID();
	return out;
}
