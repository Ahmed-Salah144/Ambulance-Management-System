#include "include\Organizer.h"

int main()
{
	Organizer* myOrganizer=new Organizer;
	myOrganizer->Load("test.txt");
	myOrganizer->SendToHospital();
	myOrganizer->RandomSimulation();
	int x = 0;
	return 0;
}