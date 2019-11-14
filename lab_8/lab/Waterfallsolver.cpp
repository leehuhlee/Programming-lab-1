#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include "Waterfallsolver.h"
#include "define.h"
#include "mylist.h"

Line *mLine=NULL;
Point *mPoint=NULL;
int mLine_num;
int mPoint_num;

mylist*m_flow_point=NULL;

bool init_state=false;
bool draw_state=false;
bool sele_state=false;
int curr_point=0;

//OnFileOpen실행시 수행
//F1. 초기화 함수 : 새로운 입력 파일을 처리하게 전에 전역 변수를 초기화 하고, 배열, 리스트 등을 청소하는 함수이다. 
void F1(void){ // 초기화
	if(mLine!=NULL) free(mLine);
	if(mPoint!=NULL) free(mPoint);
	if(m_flow_point!=NULL) delete m_flow_point;
	mLine=NULL;
	mPoint=NULL;
	m_flow_point=NULL;

	mLine_num=0;
	mPoint_num=0;
	init_state=false;
	draw_state=false;
	sele_state=false;
	curr_point=0;
}

//OnFileOpen 에서 실행
//파일을 성공적으로 불러온다면 파일 읽기 함수: 파일로부터 입력 자료를 읽어 들여 S와 P를 구성하는 함수이다. 
void F2(LPCTSTR fname){// 파일읽기
	FILE* file;
	int i, tempx, tempy;

	file=fopen(fname, "r");
	fscanf(file, "%d\n", &mLine_num);
	mLine=(Line*)malloc(sizeof(Line)*mLine_num);
	for(i=0; i<mLine_num; i++){
		fscanf(file, "%d %d %d %d\n", &(mLine[i].xl), &(mLine[i].yl), &(mLine[i].xr), &(mLine[i].yr));
		if(mLine[i].xl>mLine[i].xr){
			tempx=mLine[i].xl; tempy=mLine[i].yl;
			mLine[i].xl=mLine[i].xr; mLine[i].yl=mLine[i].yr;
			mLine[i].xr=tempx; mLine[i].yr=tempy;
		}
	}
	fscanf(file, "%d\n", &(mPoint_num));
	mPoint=(Point*)malloc(sizeof(Point)*mPoint_num);
	for(i=0; i<mPoint_num; i++){
		fscanf(file, "%f %f\n", &(mPoint[i].x), &(mPoint[i].y));
	}
	fclose(file);
	init_state=true;
}

//OnWaterFlow
//물 흐르는 경로 만드는 함수 : 입력 자료를 토대로 선택된 시작점의 경로를 만들어 linked list를 구성하는 함수.
void F3(void){//물흐르는경로 함수
	Point S;
	Line *minP, *P;
	int i, j;
	float tslew, ty, cy, minlv, templv;

	if(init_state==false) return;

	if(m_flow_point!=NULL) delete m_flow_point;
	m_flow_point=new mylist();

	S.x=mPoint[curr_point].x;
	S.y=mPoint[curr_point].y;
	m_flow_point->add(&S);

	for(i=0; i<mLine_num; i++){
		minlv=templv=MAX; minP=NULL;
		for(j=0; j<mLine_num; j++){ // 가장 가까운거찾기
			P=&mLine[j];
			if(((float)P->yl>S.y) && ((float)P->yr>S.y)) continue;
			if(((float)P->xl<S.x) && (S.x<(float)P->xr)){
				tslew=(float)(P->yr-P->yl)/(float)(P->xr-P->xl);
				ty=(float)P->yl-tslew*(float)P->xl;
				cy=tslew*S.x+ty;
				templv=S.y-cy;
				if((minlv>templv)&&(templv>0.0)){
					minlv=templv; minP=P;
				}
			}
		}
		templv=MAX;
		if(minP!=NULL){// 역류방지
			if(minP->yl<minP->yr) templv=(float)minP->yl;
			else templv=(float)minP->yr;
		}
		if(templv<S.y){
			S.y=S.y-minlv; m_flow_point->add(&S);
			if(minP->yl<minP->yr){S.x=(float)minP->xl; S.y=(float)minP->yl;}//기울기따지기
			else{S.x=(float)minP->xr; S.y=(float)minP->yr;}//기울기따지기
			m_flow_point->add(&S);
		}else{
			break;
		}
	}
	S.y=0; m_flow_point->add(&S);
}//물줄기 제대로 굴러가게 하는 함수

 //OnDraw
 //F4. 배경을 그리는 함수 : 입력 데이터인 선분과 시작점을 화면에 그리는 함수 
void F4(CDC* pDC){// 배경
	CPen MyPen;
	MyPen.CreatePen(PS_SOLID, 5, RGB(0, 0, 154));
	pDC->SelectObject(MyPen);
	pDC->MoveTo(gXmin, gYmin); pDC->LineTo(gXmax, gYmin);
	pDC->MoveTo(gXmin, gYmax); pDC->LineTo(gXmax, gYmax);

	MyPen.DeleteObject();

	MyPen.CreatePen(PS_SOLID, 5, RGB(255, 0, 0));
	pDC->SelectObject(MyPen);
	for(int i=0; i<mLine_num; i++){
		pDC->MoveTo(gXmin+mLine[i].xl*lineSize, gYmax-mLine[i].yl*lineSize);
		pDC->LineTo(gXmin+mLine[i].xr*lineSize, gYmax-mLine[i].yr*lineSize);
	}
	MyPen.DeleteObject(); MyPen.CreatePen(PS_SOLID, 10, RGB(0, 255, 0));
	pDC->SelectObject(MyPen);
	for(int i=0; i<mPoint_num; i++){
		pDC->Ellipse(gXmin+(int)mPoint[i].x*lineSize-cirsize,
					 gYmax-(int)mPoint[i].y*lineSize-cirsize,
					 gXmin+(int)mPoint[i].x*lineSize+cirsize,
					 gYmax-(int)mPoint[i].y*lineSize+cirsize);
	}
}

//OnDraw
//F5. 선택된 시작점을 그리는 함수 : 선택된 시작점의 경우 다른 시작점과 다른 색으로 그려 그 시작점을 알 수 있다. S버튼을 누름에 따라 시작점이 차례로 선택되어야 하므로 현재 선택된 시작점의 S에서의 index를 기억하여 두어야 한다.
void F5(CDC* pDC){//선택된 시작점을 그리는함수
	CPen MyPen;
	if(init_state==false) return;
	if(sele_state==false) return;

	MyPen.CreatePen(PS_SOLID, 10, RGB(0, 0, 255));
	pDC->SelectObject(MyPen);
	pDC->Ellipse(gXmin+(int)(mPoint[curr_point].x*lineSize)-cirsize,
				 gYmax-(int)(mPoint[curr_point].y*lineSize)-cirsize,
				 gXmin+(int)(mPoint[curr_point].x*lineSize)+cirsize,
				 gYmax-(int)(mPoint[curr_point].y*lineSize)+cirsize);
}

//OnDraw
//F6. 물 흐르는 경로를 그리는 함수 : F3에 의하여 만들어진 linked list를 이용하여 물 흐름을 윈도우에 그린다. 
void F6(CDC* pDC){//물 흐르는 경로를 그리는 함수
	node* temp;
	CPen MyPen;
	if(init_state==false) return;
	if(sele_state==false) return;
	if(draw_state==false) return;

	MyPen.CreatePen(PS_SOLID, 5, RGB(0, 0, 255));
	pDC->SelectObject(MyPen);
	temp=m_flow_point->move_first();
	while(temp->next!=NULL){
		pDC->MoveTo(gXmin+(int)(temp->point->x*lineSize), gYmax-(int)(temp->point->y*lineSize));
		pDC->LineTo(gXmin+(int)(temp->next->point->x*lineSize), gYmax-(int)(temp->next->point->y*lineSize));
		temp=m_flow_point->move_next();
	}
}

//OnSelectPoint
//다른 점을 칠해주는 함수
void charge_start_point(void){//스타트 포인트 바꾸는함수
	if(init_state==false) return;
	if(sele_state==true){
		curr_point++;
		if(curr_point==mPoint_num){
			curr_point=0;
			sele_state=false;
		}
	}
	else{
		sele_state=true;
		curr_point=0;
	}
}

void enable_drawWaterflow(bool mEnable){
	if(init_state==false) return;
	draw_state=mEnable;
}