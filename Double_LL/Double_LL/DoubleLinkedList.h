/************************************************************************
* Class: DoubleLinkedList
*
* Purpose: This class creates a double linked list with a head and tail.
*		   It allows the user to complete certain functions on the list
*		   such as adding elemets to the list deleting elements and so on.
*
* Manager functions:
* 	DoubleLinkedList () : m_head(nullptr), m_tail(nullptr)
* 		The default for head and tail is nullptr.
*	Array (int length, int start_index = 0)
*		Creates an appropriate sized array with the starting index
*              either zero or the supplied starting value.
*	Array (const Array & copy)
*	operator = (const Array & copy)
*	~Array()
*
* Methods:
*	operator [ ] (int index)
*		...
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
	void Prepend(T);
	void Append(T);
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
* Purpose: This function reads the input data for each plant.
*
* Precondition:
*     LastPlantNumber - Declared size of the array plantArray.
*                       Must be a non-negative value.
*
* Postcondition:
*      Returns the number of plants read.
*      Modifies the plantArray.
*
************************************************************************/
template <typename T>
DoubleLinkedList<T>::DoubleLinkedList() : m_head(nullptr), m_tail(nullptr)
{

}

template <typename T>
DoubleLinkedList<T>::~DoubleLinkedList()
{
	Purge();
}

template <typename T>
DoubleLinkedList<T>::DoubleLinkedList<T>(const DoubleLinkedList<T> & copy)
{
	m_head = nullptr;
	m_tail = nullptr;
	Node<T> * travel = copy.m_head;
	while (travel != nullptr)
	{
		Append(travel->Data);
		travel = travel->Next;
	}
}

template <typename T>
DoubleLinkedList<T> & DoubleLinkedList<T>::operator=(const DoubleLinkedList<T> & rhs)
{
	Node<T> * travel = rhs.m_head;
	while (travel != nullptr)
	{
		Append(travel->Data);
		travel = travel->Next;
	}
	return *this;
}

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

template <typename T>
T & DoubleLinkedList<T>::First() const
{
	if (m_head != nullptr)
	{
		return m_head->Data;
	}
	else
		throw "Error: No first element in list";
}

template <typename T>
T & DoubleLinkedList<T>::Last() const
{
	if (m_tail != nullptr)
	{
		return m_tail->Data;
	}
	else
		throw "Error: No last element in list";
}


template <typename T>
void DoubleLinkedList<T>::Prepend(T Data)
{
	Node<T> * prev_head = m_head;
	m_head = new Node<T>(Data);
	if (prev_head != nullptr)
	{
		prev_head->Previous = m_head;
	}
	m_head->Next = prev_head;
	m_head->Previous = nullptr;
	if (m_tail == nullptr)
	{
		m_tail = m_head;
	}
}

template <typename T>
void DoubleLinkedList<T>::Append(T Data)
{
	Node<T> * old_tail = m_tail;
	m_tail = new Node<T>(Data);

	if (m_tail != nullptr)
	{
		m_tail->Previous = old_tail;
		m_tail->Next = nullptr;
	}
	if (old_tail != nullptr)
	{
		old_tail->Next = m_tail;
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
		m_head = m_head->Next;
		delete data;
	}
	m_tail = nullptr;
}

template <typename T>
T DoubleLinkedList<T>::Extract(T data_extract)
{
	Node<T> * travel = m_head;
	while (travel != nullptr && travel->Data != data_extract)
	{
		travel = travel->Next;
	}
	if (travel)
	{
		if (travel == m_head)
			m_head = travel->Next;
		if (travel == m_tail)
			m_tail = travel->Previous;
		else if (travel->Previous != nullptr)
		{
			travel->Previous->Next = travel->Next;
			travel->Next->Previous = travel->Previous;
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
	while (travel != nullptr && travel->Data != find)
	{
		travel = travel->Next;
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
			newnode->Previous = m_head;
			newnode->Next = m_head->Next;
			m_head->Next->Previous = newnode;
			m_head->Next = newnode;
		}
		else
		{
			Node<T> * newnode = new Node<T>(put);
			newnode->Next = travel->Next;
			newnode->Previous = travel;
			travel->Next->Previous = newnode;
			travel->Next = newnode;
		}
	}
	else
		throw "Data not found within list";
}

template <typename T>
void DoubleLinkedList<T>::InsertBefore(const T & put, const T & find)
{
	Node<T> * travel = m_head;
	while (travel != nullptr && travel->Data != find)
	{
		travel = travel->Next;
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
			newnode->Next = m_tail;
			newnode->Previous = m_tail->Previous;
			m_tail->Previous->Next = newnode;
			m_tail->Previous = newnode;
		}
		else
		{
			Node<T> * newnode = new Node<T>(put);
			newnode->Previous = travel->Previous;
			newnode->Next = travel;
			travel->Previous->Next = newnode;
			travel->Previous = newnode;
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
		cout << m_head->Data << endl;
		m_head = m_head->Next;
	}
	m_head = prev_head;
}

template <typename T>
void DoubleLinkedList<T>::PrintBackwards()
{
	Node<T> * prev_tail = m_tail;
	while (m_tail != nullptr)
	{
		cout << m_tail->Data << endl;
		m_tail = m_tail->Previous;
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
