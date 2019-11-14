#include<iostream>
using namespace std;

template <class T>
class Array{
	protected:
		T *data;
		int len;

	public:
		Array(int size);
		~Array();

		int length() const;

		T & operator[](int i);
		T operator[](int i) const;

		void print();
};

template <class T>
Array<T>::Array(int size){ // ������
	if(size<=0){// size�� 0 ���� ���̸� �����޽��� ����ϰ� ����
		cout<<"ERROR!"<<endl;
		exit(-1);
	}
	else{// size�� ����̸� new�� ����Ͽ� �迭 data�� �Ҵ�, len�� �ʱ�ȭ
		data=new T[size];
		len=size;
	}
}

template <class T>
Array<T>::~Array(){ // �Ҹ���; �Ҵ�� �޸� ����
	delete(data);
	len=0;
}

template <class T>
int Array<T>::length() const{ //�迭�� ũ�� ����
	return len;
}

template <class T>
T & Array<T>::operator [](int i){ //left value : �迭�� ���Ҹ� ����
	static T tmp;
	if(i>=0 && i<=len) return data[i];//�迭�� �ε����� ���� ���� ������ �ش� ���Ҹ� ����
	else{//�׷��� ������ ���� �޽��� ����ϰ� tmp�� ����
		cout<<"Array bound error!"<<endl;
		return tmp;
	}

}

template <class T>
T Array<T>::operator [](int i) const{// right value : �迭�� ������ ���� ��ȯ
	if(i>=0 && i<=len) return data[i];//�迭�� �ε����� ���� ���� ������ ���� ����
	else{//�׷��� ������ ���� �޽��� ����ϰ� 0�� ����
		cout<<"Array bound error!"<<endl;
		return 0;
	}
}

template <class T>
void Array<T>::print(){//�迭�� ��� ������ ������ִ� �Լ�
	int i;
	cout<<"[";
	for(i=0;i<len;i++){
		cout<<" "<<data[i];
	}
	cout<<"]"<<endl;
}

template <class T>
class GrowableArray: public Array <T>
{
	protected:
		int len;
		T *temp;
	public:
		GrowableArray(int a);
		~GrowableArray();
		T &operator[](int);
		T operator[](int ) const;
};

template <class T>
GrowableArray<T>::GrowableArray(int size):Array<T>(size){
	len=size;
}

template <class T>
GrowableArray<T>::~GrowableArray() {
	;
}

template <class T>
T &GrowableArray<T>::operator[](int index) {
	int i;
	if ( index > len ) {
		temp = new T[len];
		for ( i = 0 ; i < len ; i++ ) 
			temp[i] = this->data[i];
	
		Array<T>::data = new T[2*index];
		Array<T>::len = 2*index;
		for ( i = 0 ; i < len ; i++ ) 
			this->data[i] = temp[i];
		for ( i = len ; i < 2*index ; i++ ) 
			this->data[i] = 0;
		delete[] temp;
	}
	return Array<T>::operator[](index);
}

template <class T>
T GrowableArray<T> ::operator[] (int index) const {
	return Array<T>::operator [](index);
}


int main(){
	// GrowableArray test (int)
	cout<<"GrowableArray<int> Test"<<endl;
	GrowableArray<int> g(10);
	int i;
	for(i = 0; i < g.length(); i++) g[i] = 2 * i + 3;
	cout<<"g(10)"; g.print();
	g[13] = 13;
	cout<<"g(26)"; g.print();
		
	// GrowableArray test (double)
	cout<<"GrowableArray<double> Test"<<endl;
	GrowableArray<double> dg(10);
	for(i = 0; i < dg.length(); i++) dg[i] = 2 * i + 3.14;
	cout<<"dg(10)"; dg.print();
	dg[13] = 13.31;
	cout<<"dg(26)"; dg.print();
}