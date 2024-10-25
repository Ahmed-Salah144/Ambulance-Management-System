#include "../include/Car.h"

int Car::totalNumberOfCars = 0;

Car::Car(int hid, CarType cT, int speed)
	: HID(hid),
	carType(cT),
	carSpeed(speed)
{
	ID = totalNumberOfCars++;
	carStatus = READY;
}
