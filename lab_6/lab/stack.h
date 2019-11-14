#include "linkedlist.h"

template <class T>
class Stack:public LinkedList<T>{
	virtual bool Delete(T & element);
};

template <class T>
bool Stack<T>::Delete(T & element){
	if(first==NULL){
		return false;
	}
	Node<T> *temp;
	temp=first->link;
	delete first;
	first=temp;
	current_size--;
	return true;
}