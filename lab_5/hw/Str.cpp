#include<iostream>
#include<process.h>
#include "Str.h"
using namespace std;

        Str::Str(int leng){
			str=new char[leng];
			len=leng;
		}// leng �� string�� ����.
        Str::Str(char *neyong){
			len=strlen(neyong);
			str=new char[len];
			strcpy(str,neyong);
		}// neyong�� �ʱ�ȭ�� ������ ��.
        Str::~Str(){
			if(!str)
				delete str;
		}// �Ҹ���. 
        int Str::length(){
			return len;
		}// string�� ���̸� �����ϴ� �Լ�. 
        char* Str::contents(void){
			return	str;
		}// string�� ������ �����ϴ� �Լ�.
        int Str::compare(class Str &a){
			return strcmp(str,a.str);
		}// a�� ����� strcmp.
        int Str::compare(char *a){
			return strcmp(str,a);
		}// a�� ����� strcmp.
        void Str::operator=(char *a){
			int i;
			len=strlen(a);
			str=new char[len];
			strcpy(str,a);
		}// string�� ���� ����.
        void Str::operator=(class Str &a){
			int i;
			len=strlen(a.str);
			str=new char[len];
			strcpy(str,a.str);
		}// Str�� ������ ����.