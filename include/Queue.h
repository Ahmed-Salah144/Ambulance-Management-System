#pragma once
#include<queue>
#include<iostream>
using namespace std;

/////////////////////////////////////////////////////////////////////////////////////////////////
//	This is temporary
/////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T>
class Queue {

	queue<T> stlq;
	int count;
public:
	Queue()
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
		popped = stlq.front();
		stlq.pop();
		return true;
	}
	bool peek(T& front)
	{
		if (isEmpty())
			return false;
		front = stlq.front();
		return true;
	}
	void print()
	{
		queue<T> temp = stlq;
		while (!temp.empty())
		{
			cout << temp.front()<<" ";
			temp.pop();
		}
		cout << endl;
	}
	int getCount()
	{
		return count;
	}
	~Queue()
	{
	}

};