/************************************************************************
* Author:	 Ryan Polaski
* Filename : Node.h
* Date Created : 1/6/16
* Modifications : 1/8/16 – Documented program
*
* Class: Node
*
* Purpose: This class creates the nodes for the linked list.
*		   It contains the next and previous pointers which
*		   allow the user to navigate up and down the list
*
* Manager functions:
* 	Node(T);
*	~Node();
*	Node<T> & operator = (const Node<T> &);
*	Node<T>(const Node<T> &);
*
*************************************************************************/
#ifndef NODE_H
#define NODE_H

template <typename T>
class Node
{
public:
	template <typename T>
	friend class DoubleLinkedList;

private:
	Node(T);
	~Node();
	Node<T> & operator = (const Node<T> &);
	Node<T>(const Node<T> &);

	T m_data;
	Node<T> * m_next;
	Node<T> * m_previous;
};

template <typename T>
Node<T>::Node(T data2)
{
	m_data = data2;
}

template <typename T>
Node<T>::~Node()
{
	m_next = nullptr;
	m_previous = nullptr;
}

template <typename T>
Node<T> & Node<T>::operator = (const Node<T> & rhs)
{
	m_data = rhs.m_data;
}

template <typename T>
Node<T>::Node<T>(const Node<T> & copy)
{
	m_data = copy.m_data;
	m_next = nullptr;
	m_previous = nullptr;
}


#endif

