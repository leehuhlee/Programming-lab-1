#include "Array.h"
#include <iostream>
using namespace std;

Array::Array(int size){
	if (size<0){
		cout<<"error"<<endl;
		return;
	}
	else {
		data = new int [size];
		len = size;
	}
}

Array::~Array(){
	delete data;
}
int Array::length() const{
	return len;
}

int& Array::operator[](int i){
	static int tmp;
	if ( 0 > i || len<=i ){
		cout<<" Array bound error!"<<endl;
		return tmp;
	}
	else{
		return data[i];
	}
}

int Array::operator[](int i) const{
	static int tmp;
	if ( 0 > i || len<=i ){
		cout<<" Array bound error!"<<endl;
		return tmp;
	}
	else{
		return data[i];
	}
}

void Array::print(){
	cout << "[ ";
	for ( int i=0 ; i<len ; i++ ) {
		cout<<data[i]<<" ";
	}
	cout << "]"<<endl;;
}