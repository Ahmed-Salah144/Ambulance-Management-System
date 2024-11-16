#include "../include/Car.h"


int Car::totalNumberOfCars = 0;

Car::Car(int hid, CarType cT, int speed)
	: HID(hid),
	carType(cT),
	carSpeed(speed)
{
	ID = ++totalNumberOfCars;
	carStatus = READY;
	assignedPatient = nullptr;
}
ostream& operator<<(ostream& out, Car C)
{
	if (C.getCarStatus() == SC)
		out << "S";
	else
		out << "N";

	out << C.getID() << "_H" << C.getHID();

	if (C.getAssignedPatient() != nullptr)
		out << "_P" << C.getAssignedPatient()->getID();
	return out;
}
