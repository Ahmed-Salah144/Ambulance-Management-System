#pragma once
#include"Lab/ArrayStack.h"
#include"Car.h"
class CarStack : public ArrayStack<Car*> 
{

public:

	int getCount() { return top + 1; }

};