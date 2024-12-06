#pragma once
#define MAXCAPACITY 300
#include<iostream>
using namespace std;
template <typename T>
class ListADT {
public:

    virtual ~ListADT() = default;

    virtual bool InsertEnd(const T& element) = 0;                // Add an element to the end of the list

    virtual bool Insert(int index, const T& element) = 0;        // Insert an element at a specific index

    virtual bool Remove(int index) = 0;                          // Remove an element at a specific index

    virtual T getEntry(int index) = 0;                           // Get the element at a specific index

    virtual bool Replace(int index, const T& element) = 0;       // Replace an element at a specific index

    virtual int getLength() const = 0;                           // Get the length of the list

    virtual bool isEmpty() const = 0;                            // Check if the list is empty

    virtual void Clear() = 0;                                    // Clear all elements from the list

    T operator[](int index)                                      // Overloading subscipt operator for easy access
    {
        return getEntry(index);
    }
};

template<typename T>
class ArrList : public ListADT<T> {

protected:
    T listElements[MAXCAPACITY+1];                               // One Indexed
    int count;
public:

    ArrList()
    {
        count = 0;
    }
    virtual bool InsertEnd(const T& element)                     // Add an element to the end of the list
    {   
        if (count == MAXCAPACITY)
            return false;
        count++;
        listElements[count] = element;
        return true;
    }
    virtual bool Insert(int index, const T& element)             // Insert an element at a specific index
    {
        if (index < 1 || index > count) 
        {
            return false;
        }
        if (count == MAXCAPACITY)
            return false;
        for (int i = count + 1; i > index; i--) 
        {
            listElements[i] = listElements[i - 1];
        }
        listElements[index] = element ;
        count++;
        return true;
    }
    virtual bool Remove(int index)                               // Remove an element at a specific index
    {
        if (index < 1 || index > count) {
            return false;
        }
        for (int i = index; i < count; i++) 
        {
            listElements[i] = listElements[i + 1];
        }
        count--;
        return true;
    }
    virtual T getEntry(int index)                                // Get the element at a specific index
    {

        return listElements[index];
    }
    virtual bool Replace(int index, const T& element)            // Replace an element at a specific index
    {
        if (index < 1 || index > count) 
        {
            return false;
        }
        listElements[index] = element;
        return true;
    }
    virtual int getLength() const                                // Get the length of the list
    {
        return count;
    }
    virtual bool isEmpty() const                                 // Check if the list is empty
    {
        if (count == 0)
            return true;
        return false;
    }
    virtual void Clear()                                         // Clear all elements from the list
    {
        count = 0;
    }
    void Print()                                                 // Print List Elements
    {
        for (int i = 1; i <= count; i++)
        {
            cout << listElements[i] << " ";
        }
        cout << endl;
    }

};
