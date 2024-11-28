#ifndef UICLASS
#define UICLASS

#include <iostream>
#include "Hospital.h"
#include "cstdlib"

using namespace std;

class Organizer;

class UI
{

	UIState mode;				// Interactive or Silent

	int currentHospital;		// Current Hospital to Print

	Organizer* organizer;		// Organizer Pointer in order to access organizer data


public:

	UI(Organizer* o);

	UIState getMode();

	bool printInterface();

};

#endif