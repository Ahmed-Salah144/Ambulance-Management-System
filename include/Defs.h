#pragma once
#include <cassert>
enum PatientType{

	SP,					// Special-Case Patient

	EP,					// Emergency-Case Patient

	NP					// Normal Patient

};

enum CarType {

	SC,					// Special Equipment Car

	NC					// Normal Car

};

enum CarStatus {

	READY,				// Available to Move Out

	ASSIGNED,			// Assigned to a Patient Request

	LOADED				// Carrying a Patient to the Hospital

};
struct CancellationRequest
{
	int patientID;		// Patient Who Cancelled His Request

	int requestTime;	// Request Arrival Time
};
