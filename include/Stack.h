#pragma once
#include<stack>
#include<iostream>
using namespace std;
template<typename T>
class Stack {

	stack<T> stlstack;
	int count;
public:
	Stack()
	{
		count = 0;
	}
	bool isEmpty() const
	{
		if (stlstack.empty())
			return true;
		return false;
	}
	bool push(const T& item)
	{
		stlstack.push(item);
		count++;
		return true;
	}
	bool pop(T& Popped)
	{
		if (isEmpty())
			return false;
		count--;
		Popped = stlstack.top();
		stlstack.pop();
		return true;
	}
	bool peek(T& Top)
	{
		if (isEmpty())
			return false;
		Top = stlstack.top();
		return true;
	}
	void print()
	{
		stack<T> temp = stlstack;
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
	~Stack()
	{
	}

};