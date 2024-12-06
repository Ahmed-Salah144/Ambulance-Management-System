#include "include\Organizer.h"
#include <vector>
using namespace std;
void GenerateFile(string str)
{
	srand(time(0));
	ofstream outFile(str);
	if (!outFile)
	{
		cerr << "Failed to generate File" << endl;
	}
	int h = rand() % MAXHOSPITAL;
	outFile << h << endl;
	outFile << rand() % 5000 << "\t" << rand() % 5000 << endl;
	int dist[MAXHOSPITAL][MAXHOSPITAL];
	for (int i = 0; i < h; i++)
	{
		for (int j = i+1; j < h; j++)
		{
			dist[i][j] = rand() % 10000;
			dist[j][i] = dist[i][j];
		}
		dist[i][i] = 0;
	}
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < h; j++)
		{
			outFile << dist[i][j] << "\t";
		}
		outFile << "\n";
	}
	for (int i = 0; i < h; i++)
	{
		outFile << rand() % 100 << "\t" << rand() % 100 << endl;
	}
	int reqnum = rand() % 10000;
	outFile << reqnum << "\n";
	vector<int> idToHos(reqnum+1);
	int lastarrival = 0;
	int lastpatientid = 1;
	for (int i = 0; i < reqnum; i++)
	{
		int type = rand() % 2; // no EP
		int hos = rand() % h + 1;
		idToHos[lastpatientid] = hos;
		switch (type)
		{
		case 0:
			outFile << "NP\t" << lastarrival << "\t" << lastpatientid <<"\t"<<hos<<"\t"<<rand()%10000<<"\n";
			break;
		case 1:
			outFile << "SP\t" << lastarrival << "\t" << lastpatientid << "\t" << hos << "\t" << rand() % 10000 << "\n";
			break;
		case 2:
			outFile << "EP\t" << lastarrival << "\t" << lastpatientid << "\t" << hos << "\t" << rand() % 10000 << "\t"<<rand()%100<<"\n";
			break;
		}
		lastarrival += rand() % 10;
		lastpatientid++;
	}
	int cancellationcount = rand() % reqnum;
	int lastcancel = 0;
	int patientid = -1;
	outFile << cancellationcount << "\n";
	for (int i = 0; i < cancellationcount; i++)
	{
		patientid = rand() % reqnum;
		outFile << lastcancel<< "\t"<<patientid<<"\t" <<idToHos[patientid]<<"\n";
		lastcancel = lastcancel + rand() % 10;
	}

	outFile << rand() % 100 << "\n";
	outFile << rand() % 5 << "." << rand() % 100 << "\n";
	outFile << rand() % 3 << "." << rand() % 100 << "\n";
	outFile << rand() % 1 << "." << rand() % 100 << "\n";

}
int main()
{
	for (int i = 0; i < 1; i++)
	{
		//GenerateFile("autotest"+to_string(i)+".txt");
	}
	for (int i = 0; i < 1; i++)
	{
		Organizer* myOrganizer = new Organizer;
		myOrganizer->Simulate("autotest" + to_string(i) + ".txt", "Out" + to_string(i) + ".txt");
		delete myOrganizer;
	}
	return 0;
}