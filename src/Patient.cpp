#include "../include/Patient.h"


Patient::Patient(int id, int rT, int hid, PatientType pT, int dist, int cS)
	:ID(id),
	requestTime(rT),
	closestHID(hid),
	patientType(pT),
	distance(dist),
	caseSeverity(cS)
{
	pickupTime = -1;
	assignmentTime = -1;
	finishTime = -1;
	HID = closestHID;

	failedCar = nullptr;
}
ostream& operator<<(ostream& out, Patient& P)
{
	out << P.getID();
	return out;
}
