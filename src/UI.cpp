
#include "../include/UI.h"

#include "../include/Organizer.h"

UI::UI(Organizer * o)
{
	organizer = o;
	cout << "Choose Running Mode\nEnter S For Silent Mode\nEnter I For Interactive Mode\n";
	char input;
	cin >> input;
	while (tolower(input) != 's' && tolower(input) != 'i')
	{
		cout << "\nPlease Enter I or S\n";
		cin >> input;
	}
	switch (tolower(input))
	{
	case 's':
		mode = SILENT; 
		break;
	case 'i':
		mode = INTERACTIVE;
		break;
	}
	currentHospital = 0;
}

UIState UI::getMode()
{
	return mode;
}

bool UI::printInterface()
{
	if (++currentHospital > organizer->numOfHospitals)
	{
		currentHospital = 0;
		return false;
	}
	Hospital* hospitalPtr = organizer->hospitals.getEntry(currentHospital);
	system("cls");
	cout << "Current Timestep:   " << organizer->worldTime << endl;
	cout << "==============   Hospital #" << currentHospital << " data   ==============\n";

	cout << hospitalPtr->EPqueue.getCount() << " EP requests: ";
	hospitalPtr->EPqueue.print();
	cout << endl;

	cout << hospitalPtr->SPqueue.getCount() << " SP requests: ";
	hospitalPtr->SPqueue.print();
	cout << endl;

	cout << hospitalPtr->NPqueue.getCount() << " NP requests: ";
	hospitalPtr->NPqueue.print();
	cout << endl;

	cout << "Free Cars: " << hospitalPtr->readySCList.getCount() << " SCars, " << hospitalPtr->readyNCList.getCount() << " NCars\n";

	cout << "==============   Hospital #" << currentHospital << " data end  ===========\n";
	cout << "--------------------------------------------------\n";

	cout << organizer->outList.getCount() << " ==> Out Cars: "; 
	organizer->outList.print();
	cout << endl;

	cout << organizer->backList.getCount() << " ==> Back Cars: ";
	organizer->backList.print();
	cout << endl;

	cout << "--------------------------------------------------\n";

	 cout << organizer->finishList.getCount() << " finished patients:";
	organizer->finishList.print();
	cout << endl;

	cout << "Press Any Key To Display Next Hospital\n";

	cin.get();

	return true;
}

void UI::printOrganizerData()
{

}
