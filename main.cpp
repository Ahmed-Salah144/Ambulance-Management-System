#include "include\Organizer.h"

int main()
{
	Organizer* myOrganizer=new Organizer;
	myOrganizer->Load("test2.txt");
	myOrganizer->SendToHospital();
	myOrganizer->RandomSimulation();
	return 0;
}