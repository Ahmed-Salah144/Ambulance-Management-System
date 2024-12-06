#pragma once
#include"Hospital.h"
#include"List.h"
class HospitalList : public ArrList<Hospital*>
{

public:
	bool isEmpty() 
	{
		for (int i = 1; i <= count; i++)
		{
			if (!listElements[i]->isEmpty())
				return false;
		}
		return true;
	}
	bool isFailed()
	{
		for (int i = 1; i <= count; i++)
		{
			if (!listElements[i]->isFailed())
				return false;
		}
		return true;
	}
};