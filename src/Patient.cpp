#include "../include/Patient.h"

Patient::Patient(int id, int rT, int hid, PatientType pT, int dist, int cS)
	:ID(id),
	requestTime(rT),
	HID(hid),
	patientType(pT),
	distance(dist),
	caseSeverity(cS)
{
	pickupTime = -1;
	cancelled = false;
}

