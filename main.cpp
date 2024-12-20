#include "include\Organizer.h"
#include <vector>
#include <algorithm>
using namespace std;
void sorting(vector<vector<int>>& vec) {
	sort(vec.begin(), vec.end(), [](const vector<int>& a, const vector<int>& b) {
		return a[0] < b[0]; // Sort by the first element
		});
}
void GenerateFile(string str)
{
	srand(time(0) * rand());
	ofstream outFile(str);
	if (!outFile)
	{
		cerr << "Failed to generate File" << endl;
	}
	int h = rand() % MAXHOSPITAL +1 ;
	outFile << h << endl;
	outFile << rand() % 5000 + 50 << "\t" << rand() % 5000 + 50  << endl;
	int dist[MAXHOSPITAL][MAXHOSPITAL];
	for (int i = 0; i < h; i++)
	{
		for (int j = i+1; j < h; j++)
		{
			dist[i][j] = rand() % 10000 +1;
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
		outFile << rand() % 100 + 1 << "\t" << rand() % 100 +1 << endl;
	}
	int reqnum = rand() % 100000 + 1;
	outFile << reqnum << "\n";
	int * idToHos = new int[reqnum+1];
	int* idToArrival = new int[reqnum + 1];
	int lastarrival = 0;
	int lastpatientid = 1;
	for (int i = 0; i < reqnum; i++)
	{
		int type = rand() % 3;
		int hos = rand() % h + 1;
		idToHos[lastpatientid] = hos;
		idToArrival[lastpatientid] = lastarrival;
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
	int cancellationcount = rand() % reqnum + 1 ;
	int lastcancel = 0;
	int patientid = -1;
	outFile << cancellationcount << "\n";
	vector<vector<int>> vec(cancellationcount, vector<int>(3));
	for (int i = 0; i < cancellationcount; i++)
	{
		vec[i][1] = rand() % reqnum + 1;
		vec[i][0] = idToArrival[vec[i][1]] + rand() % 100;
		vec[i][2] = idToHos[vec[i][1]];
	}
	sorting(vec);
	for (int i = 0; i < cancellationcount; i++)
	{
		outFile << vec[i][0]<< "\t"<< vec[i][1] <<"\t" <<vec[i][2]<<"\n";
	}

	outFile << rand() % 100 + 1 << "\n";
	outFile << rand() % 5 << "." << rand() % 100 << "\n";
	outFile << rand() % 5 << "." << rand() % 100 << "\n";
	outFile << rand() % 2 << "." << rand() % 100 << "\n";

	delete[] idToHos;
	delete[] idToArrival;
}

int main()
{
	for (int i = 0; i < 6 ; i++)
	{
		GenerateFile("tests/autotest"+to_string(i)+".txt");
	}
	for (int i = 0; i < 6; i++)
	{
		Organizer* myOrganizer = new Organizer;
		myOrganizer->Simulate("tests/autotest" + to_string(i) + ".txt", "tests/Out" + to_string(i) + ".txt");
		delete myOrganizer;
		cout << "Finished test " << i << endl;
	}
	return 0;
}