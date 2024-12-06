#pragma once
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
enum UIState {

	INTERACTIVE,		// Interactive Mode On

	SILENT				// Silent Mode

};
struct CancellationRequest
{
	int patientID;		// Patient Who Cancelled His Request

	int requestTime;	// Request Arrival Time

	int HospitalID;		// Hospital ID of cancelled request

};


