#include "include/List.h"

void TestArrList()
{
	ArrList<int> myList;
	int x;
	cin >> x;
	while (x != -1)
	{
		myList.InsertEnd(x);
		cin >> x;
	}
	cout<<"List Length : "<<myList.getLength()<<endl;
	for (int i = 1; i <= myList.getLength(); i++)
	{
		cout << "List Element : " << myList[i] << endl;
	}
	cout << "Print Test"<<endl;

	myList.Print();
	
	cout << "Removing Second Element \n";

	myList.Remove(2);

	myList.Print();

	cout << "Replacing Second Element with 10\n";

	myList.Replace(2, 10);

	myList.Print();

	cout << "Inserting Second Element with 55\n";

	myList.Insert(2, 55);

	myList.Print();

}
void TestLinkedList()
{
	LinkedList<int> myList;
	int x;
	cin >> x;
	while (x != -1)
	{
		myList.InsertEnd(x);
		cin >> x;
	}
	cout << "List Length : " << myList.getLength() << endl;
	for (int i = 1; i <= myList.getLength(); i++)
	{
		cout << "List Element : " << myList[i] << endl;
	}
	cout << "Print Test" << endl;

	myList.Print();

	cout << "Removing Second Element \n";

	myList.Remove(2);

	myList.Print();

	cout << "Replacing Second Element with 10\n";

	myList.Replace(2, 10);

	myList.Print();

	cout << "Inserting Second Element with 55\n";

	myList.Insert(2, 55);

	myList.Print();

}
int main()
{
	return 0;
}