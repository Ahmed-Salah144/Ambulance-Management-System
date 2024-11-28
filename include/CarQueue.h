#pragma once
#include"Lab/LinkedQueue.h"
#include"Car.h"
class CarQueue : public LinkedQueue<Car*> 
{

public:

	int getCount() 
	{
		Node<Car*>* current = frontPtr;
		int count = 0;
		while (current) {
			count += 1;
			current = current->getNext();
		}
		return count;
	}

};