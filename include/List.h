#pragma once
#define MAXCAPACITY 200
#include <cassert>
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

    //virtual int Find(int key) = 0;                               // Return the index of an element by using a key

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
        assert(index >= 1 && index <= count);

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

template<typename T>
struct Node {

    T item;
    Node<T>* next;

    Node()
    {
        next = nullptr;
    }
    Node(const T& t)
    {
        next = nullptr;
        item = t;
    }
};

template<typename T>
class LinkedList : public ListADT<T> {

    Node<T>* head;

    Node<T>* tail;

    int count;

public:
    LinkedList()
    {
        count = 0;
        head = nullptr;
        tail = nullptr;
    }
    virtual ~LinkedList()
    {
        Clear();
    }
    virtual bool InsertEnd(const T& element)                     // Add an element to the end of the list
    {
        if (tail == nullptr)
        {
            tail = new Node<T>(element);
            head = tail;
        }
        else
        {
            tail->next = new Node<T>(element);
            tail = tail->next;
        }
        count++;
        return true;
    }
    virtual bool Insert(int index, const T& element)             // Insert an element at a specific index
    {
        if (index < 1 || index>count+1)
            return false;
        if (index == count + 1)
        {
            InsertEnd(element);
            return true;
        }
        Node<T>* current = head;
        if (index == 1)
        {
            head = new Node<T>(element);
            head->next = current;
            count++;
            return true;
        }
        for (int i = 0; i < index - 2; i++)
        {
            current = current->next;
        }
        Node<T>* newnode = new Node<T>(element);
        newnode->next = current->next;
        current->next = newnode;
        count++;
        return true;
    }
    virtual bool Remove(int index)                               // Remove an element at a specific index
    {
        if (index < 1 || index>count)
            return false;
        Node<T>* current = head;
        if (index == 1)
        {
            head = head->next;
            delete current;
            count--;
            return true;
        }
        for (int i = 0; i < index - 2; i++)
        {
            current = current->next;
        }
        Node<T>* temp = current->next;
        current->next = current->next->next;
        delete temp;
        count--;
        return true;
    }
    virtual T getEntry(int index)                                // Get the element at a specific index
    {
        assert( index >= 1 && index <= count);
        Node<T>* current = head;
        for (int i = 0; i < index-1; i++)
        {
            current = current->next;
        }
        return current->item;
    }
    virtual bool Replace(int index, const T& element)            // Replace an element at a specific index
    {
        if (index<1 || index>count)
            return false;
        Node<T>* current = head;
        for (int i = 0; i < index - 1; i++)
        {
            current = current->next;
        }
        current->item = element;
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
        while (head != nullptr)
        {
            Node<T>* deletedNode = head;
            head = head->next;
            delete deletedNode;
        }
        count = 0;
    }
    void Print()                                                 // Print List Elements
    {
        Node<T>* currentNodePtr = head;
        if (head)
        {
            cout << currentNodePtr->item;
            currentNodePtr = currentNodePtr->next;
        }
        while (currentNodePtr != nullptr)
        {
            cout << " " << currentNodePtr->item;
            currentNodePtr = currentNodePtr->next;
        }
        cout << endl;
    }
};
