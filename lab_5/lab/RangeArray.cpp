#include "RangeArray.h"
#include <iostream>
using namespace std;

RangeArray::RangeArray ( int first, int last):Array(last-first+1){
	low = first ;
	high = last ;
}
RangeArray::~RangeArray(){
	//RangeArray�� Array�� ���(Array�� �θ� RangeArray�� ����)
	//���� Array���� delete�Ǳ� ������ �� �ʿ䰡 ����.
}
int RangeArray::baseValue(){
	return low;
		}
int RangeArray::endValue(){
	return high;
}	
int& RangeArray::operator[](int i){
	static int tmp;
	if ( i<low || i>high ){
		cout<<" Array bound error!"<<endl;
		return tmp;
	}
	else{
		return data[i-low];
	}	
}
int RangeArray::operator[](int i) const{
	static int tmp;
	if ( i<low || i>high ){
		cout<<" Array bound error!"<<endl;
		return tmp;
	}
	else{
		return data[i-low];
	}
}