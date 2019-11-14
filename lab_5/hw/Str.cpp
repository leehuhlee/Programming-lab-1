#include<iostream>
#include<process.h>
#include "Str.h"
using namespace std;

        Str::Str(int leng){
			str=new char[leng];
			len=leng;
		}// leng 은 string의 길이.
        Str::Str(char *neyong){
			len=strlen(neyong);
			str=new char[len];
			strcpy(str,neyong);
		}// neyong은 초기화할 내용이 들어감.
        Str::~Str(){
			if(!str)
				delete str;
		}// 소멸자. 
        int Str::length(){
			return len;
		}// string의 길이를 리턴하는 함수. 
        char* Str::contents(void){
			return	str;
		}// string의 내용을 리턴하는 함수.
        int Str::compare(class Str &a){
			return strcmp(str,a.str);
		}// a의 내용과 strcmp.
        int Str::compare(char *a){
			return strcmp(str,a);
		}// a의 내용과 strcmp.
        void Str::operator=(char *a){
			int i;
			len=strlen(a);
			str=new char[len];
			strcpy(str,a);
		}// string의 값을 대입.
        void Str::operator=(class Str &a){
			int i;
			len=strlen(a.str);
			str=new char[len];
			strcpy(str,a.str);
		}// Str의 내용을 대입.