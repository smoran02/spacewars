#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

#include <iostream>
#include <stdexcept>

//node class to hold the data for the linked list
template <typename T>
class Node
{
	public:
	
		Node(T d);
		
		T data;
		Node<T>* next;
		Node<T>* previous;
};

template <typename T>
Node<T>::Node( T d)
: data(d)
{
	this->next = NULL;
	this->previous = NULL;
}

template <typename T>
class LinkedList
{
	protected:
		
		int length;
		Node<T>* head;
		
	public:
		
		LinkedList();
		LinkedList(const LinkedList<T>& other);
		~LinkedList();
	
		LinkedList<T>& operator=(const LinkedList<T> &other);
		
		bool empty() const;
		int size() const;		
		void push_front( T val);		
		T& at(const int& index);			
		void erase(const int& index);
		void remove(Node<T>* removeNode);
		void remove();
		Node<T>* getFirst();
		Node<T>* getNext(Node<T>* b);
		bool contains(const T&) const;

	private:
	
		void destroy();
};

//constructor
template <typename T>
LinkedList<T>::LinkedList()
{
	this->length = 0;
	this->head = NULL;
}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& other)
{
	this->length = 0;
	this->head = NULL;
	
	copy(other);
}

//function to get the first node in the list
template <typename T>
Node<T>* LinkedList<T>::getFirst()
{
	return this->head;
}

//function to get the next node in the list
template <typename T>
Node<T>* LinkedList<T>::getNext(Node<T>* b)
{
	return b->next;
}

template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& other)
{
	if(this != &other) copy(other);
	return *this;
}

template <typename T>
LinkedList<T>::~LinkedList()
{
	destroy();
}

//delete the list
template <typename T>
void LinkedList<T>::destroy()
{
	Node<T>* current = this->head;
	while(current != NULL)
	{
		Node<T>* toDelete = current;
		current = current->next;
		delete toDelete;
	}
	
	this->length = 0;
	this->head = NULL;
}

//returns true if list is empty
template <typename T>
bool LinkedList<T>::empty() const
{
	return this->length == 0;
}

//returns number of nodes in the list
template <typename T>
int LinkedList<T>::size() const
{
	return this->length;
}

//removes the first node in the list
template <typename T>
void LinkedList<T>::remove()
{
	Node<T>* toDelete = this->head;
	if (this->head->next != NULL)
	{
		this->head = this->head->next;
		this->head->previous = NULL;
	}
	else
	{
		this->head = NULL;
	}
	length--;
	delete toDelete;
}

//removes the specified node from the list
template <typename T>
void LinkedList<T>::remove(Node<T>* removeNode)
{
	if (this->head == removeNode)
	{
		remove();
	}
	else if (removeNode->next == 0)
	{
		Node<T>* toDelete = removeNode;
		toDelete->previous->next = 0;
		delete toDelete;
		length--;
	}
	else
	{
		Node<T>* toDelete = removeNode;
		removeNode->previous->next = removeNode->next;
		removeNode->next->previous = removeNode->previous;
		delete toDelete;
		length--;
	}
}

template <typename T>
bool LinkedList<T>::contains(const T& value) const
{
	Node<T>* searchFor = new Node<T>(value);
	Node<T>* finder = this->head;
	while (finder != NULL)
	{
		if (finder->data == searchFor->data)
		{
			return true;
		}
		else
			finder = finder->next;
	}
	return false;
}
		
template <typename T>
void LinkedList<T>::push_front( T val)
{
	//make a new node
	Node<T>* newOne = new Node<T>(val);
		
	//push it onto the front of the list
	newOne->next = this->head;
	this->head = newOne;

	//increase the length of the list by one
	this->length++;
}
	
template <typename T>
T& LinkedList<T>::at(const int& index)
{
	//make sure the index is in bounds
	if(index < 0 || index >= this->length)
	{
		throw std::out_of_range("index was out of bounds in at().");
	}

	//walk through the list until we hit the index we want
	Node<T>* current = this->head;
	int currentIndex = 0;
	while(currentIndex != index)
	{
		current = current->next;
		currentIndex++;
	}

	//return the data at the given index
	return current->data;
}
		
template <typename T>
void LinkedList<T>::erase(const int& index)
{
	//check that the index is in bounds
	if(index < 0 || index >= this->length)
	{
		throw std::out_of_range("index was out of bounds in erase()!");
	}

	Node<T>* previous = NULL;
	Node<T>* current = this->head;
	int currentIndex = 0;
	
	//walk through the list until "current" points to
	//the thing we want to get rid of
	while(currentIndex != index)
	{
		previous = current;
		current = current->next;
		currentIndex++;
	}
	
	//removing the first element
	if(previous == NULL)
	{
		this->head = head->next;
	}
	//remove a middle element
	else
	{
		previous->next = current->next;
	}
	
	//free up the memory that was allocated by the insert
	delete current;
	this->length--;
}
		


#endif