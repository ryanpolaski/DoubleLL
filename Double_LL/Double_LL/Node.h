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

	T Data;
	Node<T> * Next;
	Node<T> * Previous;
};

template <typename T>
Node<T>::Node(T data2)
{
	Data = data2;
}

template <typename T>
Node<T>::~Node()
{
	Next = nullptr;
	Previous = nullptr;
}


#endif

