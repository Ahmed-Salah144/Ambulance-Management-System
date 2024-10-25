#pragma once
#include<queue>
using namespace std;

/////////////////////////////////////////////////////////////////////////////////////////////////
//	This is temporary
/////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T>

class PriQueue {

	priority_queue<T> stlq;
	int count;
public:
	PriQueue()
	{
		count = 0;
	}
	bool isEmpty() const
	{
		if (stlq.empty())
			return true;
		return false;
	}
	bool enqueue(const T& item)
	{
		stlq.push(item);
		count++;
		return true;
	}
	bool dequeue(T& popped)
	{
		if (isEmpty())
			return false;
		count--;
		popped = stlq.top();
		stlq.pop();
		return true;
	}
	bool peek(T& front)
	{
		if (isEmpty())
			return false;
		front = stlq.top();
		return true;
	}
	void print()
	{
		priority_queue<T> temp = stlq;
		while (!temp.empty())
		{
			cout << temp.top() << " ";
			temp.pop();
		}
		cout << endl;
	}
	int getCount()
	{
		return count;
	}
	~PriQueue()
	{
	}

};