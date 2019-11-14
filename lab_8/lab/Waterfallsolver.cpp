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

//OnFileOpen����� ����
//F1. �ʱ�ȭ �Լ� : ���ο� �Է� ������ ó���ϰ� ���� ���� ������ �ʱ�ȭ �ϰ�, �迭, ����Ʈ ���� û���ϴ� �Լ��̴�. 
void F1(void){ // �ʱ�ȭ
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

//OnFileOpen ���� ����
//������ ���������� �ҷ��´ٸ� ���� �б� �Լ�: ���Ϸκ��� �Է� �ڷḦ �о� �鿩 S�� P�� �����ϴ� �Լ��̴�. 
void F2(LPCTSTR fname){// �����б�
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
//�� �帣�� ��� ����� �Լ� : �Է� �ڷḦ ���� ���õ� �������� ��θ� ����� linked list�� �����ϴ� �Լ�.
void F3(void){//���帣�°�� �Լ�
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
		for(j=0; j<mLine_num; j++){ // ���� ������ã��
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
		if(minP!=NULL){// ��������
			if(minP->yl<minP->yr) templv=(float)minP->yl;
			else templv=(float)minP->yr;
		}
		if(templv<S.y){
			S.y=S.y-minlv; m_flow_point->add(&S);
			if(minP->yl<minP->yr){S.x=(float)minP->xl; S.y=(float)minP->yl;}//���������
			else{S.x=(float)minP->xr; S.y=(float)minP->yr;}//���������
			m_flow_point->add(&S);
		}else{
			break;
		}
	}
	S.y=0; m_flow_point->add(&S);
}//���ٱ� ����� �������� �ϴ� �Լ�

 //OnDraw
 //F4. ����� �׸��� �Լ� : �Է� �������� ���а� �������� ȭ�鿡 �׸��� �Լ� 
void F4(CDC* pDC){// ���
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
//F5. ���õ� �������� �׸��� �Լ� : ���õ� �������� ��� �ٸ� �������� �ٸ� ������ �׷� �� �������� �� �� �ִ�. S��ư�� ������ ���� �������� ���ʷ� ���õǾ�� �ϹǷ� ���� ���õ� �������� S������ index�� ����Ͽ� �ξ�� �Ѵ�.
void F5(CDC* pDC){//���õ� �������� �׸����Լ�
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
//F6. �� �帣�� ��θ� �׸��� �Լ� : F3�� ���Ͽ� ������� linked list�� �̿��Ͽ� �� �帧�� �����쿡 �׸���. 
void F6(CDC* pDC){//�� �帣�� ��θ� �׸��� �Լ�
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
//�ٸ� ���� ĥ���ִ� �Լ�
void charge_start_point(void){//��ŸƮ ����Ʈ �ٲٴ��Լ�
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