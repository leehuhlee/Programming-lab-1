#ifndef __LINKEDLIST__
#define __LINKEDLIST__
#include <iostream>
using namespace std;

// Linked List Node
template <class T>

class Node{
public:
    T data;
    Node *link;
    Node(T element){
        data = element;
        link = 0; }
};

// Linked List Class
template <class T>
class LinkedList
{
protected:
    Node<T> *first;
    int current_size;
public:
    LinkedList(){
        first = 0;
        current_size = 0; 
	};
    T GetSize() { return current_size; }; // ��� ������ ����
    void Insert(T element); // �� �տ� ���Ҹ� ����
    virtual bool Delete(T &element); // �� ���� ���Ҹ� ����
    void Print();	// ����Ʈ�� ���
};

template <class T>
void LinkedList<T>::Insert(T element){ // �� ��带 �� �տ� ����
    Node<T> *newnode = new Node<T>(element);
    newnode->link = first;
    first = newnode;
    current_size++;
}

template <class T>
bool LinkedList<T>::Delete(T &element){
    // ������ ����� ���� �����ϸ鼭, �޸𸮿��� �Ҵ� ����
    if(first == 0) return false;
    Node<T> *current = first, *previous = 0;
    while(1){    // ������ ������ ã�ư��� �ݺ���
        if(current->link == 0)    // find end node
        {
            if(previous) previous->link = current->link;
            else first = first->link;
            break;
        }
        previous = current;
        current = current->link;
    }
    element = current->data;
    delete current;
    current_size--;
    return true;
}

template <class T>
void LinkedList<T>::Print(){
	if(first==NULL){
		return;
	}
	Node<T> *now=first;
	int num=1;
	
	while(now!=NULL){
		if(num!=1){
			cout<<"->";
		}
		cout<<"["<<num<<"|"<<now->data<<"]";
		num++;
		now=now->link;
	}
	cout<<endl;
}
#endif