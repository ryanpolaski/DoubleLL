/************************************************************************
* Author:	 Ryan Polaski
* Filename : DoubleLinkedList.h
* Date Created : 1/6/16
* Modifications : 1/8/16 – Documented program
*
* Class: DoubleLinkedList
*
* Purpose: This class creates a double linked list with a head and tail.
*		   It allows the user to complete certain functions on the list
*		   such as adding elemets to the list deleting elements and so on.
*
* Manager functions:
* 	DoubleLinkedList () : m_head(nullptr), m_tail(nullptr)
* 		The default for head and tail is nullptr.
*	~DoubleLinkedList();
*	DoubleLinkedList<T>& operator=(const DoubleLinkedList<T> & rhs);
*	DoubleLinkedList<T>(const DoubleLinkedList<T> & copy);
*	
* Methods:
*	bool isEmpty();
*	T & First() const;
*	T & Last() const;
*	void Prepend(T);
*	void Append(T);
*	void Purge();
*	T Extract(T);
*	void InsertAfter(const T & put, const T & find);
*	void InsertBefore(const T & put, const T & find);
*	void PrintForwards();
*	void PrintBackwards();
* Getters
*	Node<T>* getHead();
*	Node<T>* getTail();
*		
*************************************************************************/
#ifndef DOUBLELINKEDLIST_H
#define DOUBLELINKEDLIST_H
#include "Node.h"

template <typename T>
class DoubleLinkedList
{
public:
	//OCCF
	DoubleLinkedList();
	~DoubleLinkedList();
	DoubleLinkedList<T>& operator=(const DoubleLinkedList<T> & rhs);
	DoubleLinkedList<T>(const DoubleLinkedList<T> & copy);

	bool isEmpty();
	T & First() const;
	T & Last() const;
	void Prepend(const T &);
	void Append(const T &);
	void Purge();
	T Extract(T);
	void InsertAfter(const T & put, const T & find);
	void InsertBefore(const T & put, const T & find);
	void PrintForwards();
	void PrintBackwards();

	// Getters
	Node<T>* getHead();
	Node<T>* getTail();

private:

	// Data Members
	Node<T> * m_head;
	Node<T> * m_tail;
};

/**********************************************************************
* Purpose: This function initializes the head and tail to nullptr
*
* Precondition:
*
* Postcondition:
*      Sets head and taill to nullptr
*
************************************************************************/
template <typename T>
DoubleLinkedList<T>::DoubleLinkedList() : m_head(nullptr), m_tail(nullptr)
{

}

/**********************************************************************
* Purpose: This function calls the purge function to delete anything
*		   created
*
* Precondition:
*
* Postcondition:
*      Calls the purge function
*
************************************************************************/
template <typename T>
DoubleLinkedList<T>::~DoubleLinkedList()
{
	Purge();
}

/**********************************************************************
* Purpose: This function initializes the head and tail to nullptr
*
* Precondition:
*		Want to copy one objects data into another
*
* Postcondition:
*		Copys data was copied into the empty object
*
************************************************************************/
template <typename T>
DoubleLinkedList<T>::DoubleLinkedList<T>(const DoubleLinkedList<T> & copy)
{
	m_head = nullptr;
	m_tail = nullptr;
	Node<T> * travel = copy.m_head;
	while (travel != nullptr)
	{
		Append(travel->m_data);
		travel = travel->m_next;
	}
}

/**********************************************************************
* Purpose: This function sets one objects equal to another
*
* Precondition:
*		Want to set one object equal to another
*
* Postcondition:
*		One object was set equal to another
*
************************************************************************/
template <typename T>
DoubleLinkedList<T> & DoubleLinkedList<T>::operator=(const DoubleLinkedList<T> & rhs)
{
	Node<T> * travel = rhs.m_head;
	while (travel != nullptr)
	{
		Append(travel->m_data);
		travel = travel->m_next;
	}
	return *this;
}

/**********************************************************************
* Purpose: This function checks to see if the list is empty
*
* Precondition:
*		Want to see if the list has any data inside it
*
* Postcondition:
*      Returns a bool depending on if the list is empty of not
*
************************************************************************/
template <typename T>
bool DoubleLinkedList<T>::isEmpty()
{
	bool check = 1;
	if (m_head == nullptr)
	{
		check = 0;
	}
	return check;
}

/**********************************************************************
* Purpose: This function returns the first element in the list
*
* Precondition:
*		Want to see the first element in the list
*
* Postcondition:
*      Returns the first element in the list
*
************************************************************************/
template <typename T>
T & DoubleLinkedList<T>::First() const
{
	if (m_head != nullptr)
	{
		return m_head->m_data;
	}
	else
		throw "Error: No first element in list";
}

template <typename T>
T & DoubleLinkedList<T>::Last() const
{
	if (m_tail != nullptr)
	{
		return m_tail->m_data;
	}
	else
		throw "Error: No last element in list";
}


template <typename T>
void DoubleLinkedList<T>::Prepend(const T & data)
{
	Node<T> * prev_head = m_head;
	m_head = new Node<T>(data);
	if (prev_head != nullptr)
	{
		prev_head->m_previous = m_head;
	}
	m_head->m_next = prev_head;
	m_head->m_previous = nullptr;
	if (m_tail == nullptr)
	{
		m_tail = m_head;
	}
}

template <typename T>
void DoubleLinkedList<T>::Append(const T & Data)
{
	Node<T> * old_tail = m_tail;
	m_tail = new Node<T>(Data);

	if (m_tail != nullptr)
	{
		m_tail->m_previous = old_tail;
		m_tail->m_next = nullptr;
	}
	if (old_tail != nullptr)
	{
		old_tail->m_next = m_tail;
	}
	if (m_head == nullptr)
	{
		m_head = m_tail;
	}
}

template <typename T>
void DoubleLinkedList<T>::Purge()
{
	while (m_head != nullptr)
	{
		Node<T> * data = m_head;
		m_head = m_head->m_next;
		delete data;
	}
	m_tail = nullptr;
}

template <typename T>
T DoubleLinkedList<T>::Extract(T data_extract)
{
	Node<T> * travel = m_head;
	while (travel != nullptr && travel->m_data != data_extract)
	{
		travel = travel->m_next;
	}
	if (travel)
	{
		if (travel == m_head)
			m_head = travel->m_next;
		if (travel == m_tail)
			m_tail = travel->m_previous;
		else if (travel->m_previous != nullptr)
		{
			travel->m_previous->m_next = travel->m_next;
			travel->m_next->m_previous = travel->m_previous;
		}
		delete travel;
	}
	else
		throw "Data not found in list";
	return data_extract;
}

template <typename T>
void DoubleLinkedList<T>::InsertAfter(const T & put, const T & find)
{
	Node<T> * travel = m_head;
	while (travel != nullptr && travel->m_data != find)
	{
		travel = travel->m_next;
	}
	if (travel)
	{
		if (travel == m_tail)
		{
			Append(put);
		}
		else if (travel == m_head)
		{
			Node<T> * newnode = new Node<T>(put);
			newnode->m_previous = m_head;
			newnode->m_next = m_head->m_next;
			m_head->m_next->m_previous = newnode;
			m_head->m_next = newnode;
		}
		else
		{
			Node<T> * newnode = new Node<T>(put);
			newnode->m_next = travel->m_next;
			newnode->m_previous = travel;
			travel->m_next->m_previous = newnode;
			travel->m_next = newnode;
		}
	}
	else
		throw "Data not found within list";
}

template <typename T>
void DoubleLinkedList<T>::InsertBefore(const T & put, const T & find)
{
	Node<T> * travel = m_head;
	while (travel != nullptr && travel->m_data != find)
	{
		travel = travel->m_next;
	}
	if (travel)
	{
		if (travel == m_head)
		{
			Prepend(put);
		}
		else if (travel == m_tail)
		{
			Node<T> * newnode = new Node<T>(put);
			newnode->m_next = m_tail;
			newnode->m_previous = m_tail->m_previous;
			m_tail->m_previous->m_next = newnode;
			m_tail->m_previous = newnode;
		}
		else
		{
			Node<T> * newnode = new Node<T>(put);
			newnode->m_previous = travel->m_previous;
			newnode->m_next = travel;
			travel->m_previous->m_next = newnode;
			travel->m_previous = newnode;
		}
	}
	else
		throw "Data not found within list";
}


template <typename T>
void DoubleLinkedList<T>::PrintForwards()
{
	Node<T> * prev_head = m_head;
	if (m_head == nullptr)
	{
		cout << "Nothing in list" << endl;
	}

	while (m_head != nullptr)
	{
		cout << m_head->m_data << endl;
		m_head = m_head->m_next;
	}
	m_head = prev_head;
}

template <typename T>
void DoubleLinkedList<T>::PrintBackwards()
{
	Node<T> * prev_tail = m_tail;
	while (m_tail != nullptr)
	{
		cout << m_tail->m_data << endl;
		m_tail = m_tail->m_previous;
	}
	m_tail = prev_tail;
}

template <typename T>
Node<T>* DoubleLinkedList<T>::getHead()
{
	return m_head;
}

template <typename T>
Node<T>* DoubleLinkedList<T>::getTail()
{
	return m_tail;
}
#endif
