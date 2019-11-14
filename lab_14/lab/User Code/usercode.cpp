#include <stdlib.h>
#include "..\ExternDoc.h"
#include "..\UI\Zoom.h"
#include "..\UI\MsgView.h"
#include "..\Graphics\DrawFunc.h"
#include "..\Example\Example.h"

#define ERROR_NUMBER -1

//function prototype

static void drawDirect(CDC *pDC);
static void drawBuffered();

//Start of user code
#include <float.h>

typedef struct vertex VTX;
typedef struct vtx_linked_list VLL;

struct vertex{
	int row;
	int col;
	bool right;
	bool down;
};
VTX **map;
VTX **map2;
int WIDTH, HEIGHT;

struct vtx_linked_list{
	VTX *node;
	VLL *next;
};

VLL *q;
int qn;

typedef struct stack_* stackp;

typedef struct stack_{
	VTX *node;
	stackp L;
}stack;

stackp sta;
stackp stb;

int drawmode;

void DFS_(VTX *mark);
VTX *stackpop();
void stackpush(VTX *data);

void DFS(){
	DFS_(&map2[0][0]);
}

void DFS_(VTX *mark){
	stackpush(mark);
	if(mark->col==WIDTH-1 && mark->row==HEIGHT-1)
		return;
	if(mark->col>0 && map2[mark->row][mark->col-1].right==true){              //왼쪽
		map2[mark->row][mark->col-1].right=false;
		DFS_(&map2[mark->row][mark->col-1]);
	}
	else if(mark->col<WIDTH-1 && map2[mark->row][mark->col].right==true){      //오른쪽
		map2[mark->row][mark->col].right=false;
		DFS_(&map[mark->row][mark->col+1]);
	}
	else if(mark->row>0 && map2[mark->row-1][mark->col].down==true){          //위
		map2[mark->row-1][mark->col].down=false;
		DFS_(&map2[mark->row-1][mark->col]);
	}
	else if(mark->row<HEIGHT-1 && map2[mark->row][mark->col].down==true){       //아래
		map2[mark->row][mark->col].down=false;
		DFS_(&map2[mark->row+1][mark->col]);
	}
	else{
		stackpop();
		DFS_(stackpop());
	}
}

VTX *stackpop(){
	VTX* rm;
	rm=sta->node;
	sta=sta->L;
	return rm;
}

VTX *stackpop2(){
	VTX* rm;
	rm=stb->node;
	stb=stb->L;
	return rm;
}

void stackpush(VTX *data){
	stack *nn;
	stack *nn2;

	nn=(stack*)malloc(sizeof(stack));
	nn2=(stack*)malloc(sizeof(stack));
	nn->node=data;
	nn->L=NULL;
	nn2->node=data;
	nn2->L=NULL;
	if(sta==NULL){
		sta=nn;
	}
	else{
		nn->L=sta;
		sta=nn;
	}
	if(stb==NULL){
		stb=nn2;
	}
	else{
		nn2->L=stb;
		stb=nn2;
	}
}
void push(VTX *data){
	VLL *nn;

	nn=(VLL*)malloc(sizeof(VLL));
	nn->node=data;
	nn->next=NULL;
	qn++;
	if(q==NULL){
		q=nn;
	}
	else{
		nn->next=q;
		q=nn;
	}
}

void pop(){
	VLL *rm;
	qn--;
	rm=q;
	q=q->next;
	free(rm);
}

/*****************************************************************
* function	: bool readFile(const char* filename)
* argument	: cons char* filename - filename to be opened
* return	: true if success, otherwise flase
* remark	: After read data file, phisycal view must be set;
*			  otherwise drawing will not be executed correctly.
*			  The window will be invalidated after readFile()
*			  returns true.
******************************************************************/

bool readFile(const char* filename){
	
	//start of the user code
	int i,j,res,row,col;
	char rm;
	FILE* fp = fopen( filename, "r" );

	if( fp == NULL ) return false;

	fscanf(fp,"%c",&rm);
	i=0;
	while(1){
		fscanf(fp,"%c",&rm);
		if(rm=='\n')break;
		i++;
	}
	i/=2;
	WIDTH=i;
	i=1;
	while(1){
		res=fscanf(fp,"%c",&rm);
		if(res==EOF)break;
		if(rm=='\n')i++;
	}
	i/=2;
	HEIGHT=i;

	map=(VTX **)malloc(sizeof(VTX*)*HEIGHT);
	map2=(VTX **)malloc(sizeof(VTX*)*HEIGHT);

	for(i=0;i<HEIGHT;i++){
		map[i]=(VTX *)malloc(sizeof(VTX)*WIDTH);
		map2[i]=(VTX *)malloc(sizeof(VTX)*WIDTH);
	}
	fclose(fp);
	fp=fopen(filename,"r");

	for(i=0;i<WIDTH*2+2;i++){
		fscanf(fp,"%c",&rm);
	}
	for(i=0;i<HEIGHT;i++){
		fscanf(fp,"%c",&rm);
		for(j=0;j<WIDTH;j++){
			fscanf(fp,"%c",&rm);
			fscanf(fp,"%c",&rm);
			if(rm==' ')map[i][j].right=true;
			else map[i][j].right=false;
			map[i][j].row=i;
			map[i][j].col=j;
		}
		fscanf(fp,"%c",&rm);
		fscanf(fp,"%c",&rm);
		for(j=0;j<WIDTH;j++){
			fscanf(fp,"%c",&rm);
			if(rm==' ')map[i][j].down=true;
			else map[i][j].down=false;
			fscanf(fp,"%c",&rm);
		}
		fscanf(fp,"%c",&rm);
	}
	fclose(fp);
	
	for(i=0;i<HEIGHT;i++){
		for(j=0;j<WIDTH;j++){
			push(&map[i][j]);
			map2[i][j]=map[i][j];
		}
	}
	setWindow(0,0,4*WIDTH+5,4*HEIGHT+5,0);
	return true; //edit after finish this function
	//end of usercode
}

/******************************************************************
* function	: bool FreeMemory()
*
* remark	: Save user data to a file
*******************************************************************/
void freeMemory(){
	//start of the user code
	//end of usercode
	int i;

	for(i=0;i<HEIGHT;i++){
		free(map[i]);
	}
	free(map);

	while(1){
		if(qn==0)break;
		pop();
	}
	while(1){
		if(sta==NULL)break;
		stackpop();
		
	}
	while(1){
		if(stb==NULL)break;
		stackpop2();
	}
}

/**************************************************************
* function	: bool writeFile(const char* filename)
*
* argument	: const char* filename - filename to be written
* return	: true if success, otherwise false
* remark	: Save user data to a file
****************************************************************/
bool writeFile(const char* filename){
	//start of the user code
	bool flag;
	flag = 0;

	return flag;
	//end of usercode
}

/************************************************************************
* fucntion	: void drawMain(CDC* pDC)
*
* argument	: CDC* pDC - device context object pointer
* remark	: Main drawing function. Called by CMFC_MainView::OnDraw()
*************************************************************************/
void drawMain(CDC *pDC){
	//if direct drawing is defined
#if defined(GRAPHICS_DIRECT)
	drawDirect(pDC);
	//if buffered drawing is defined
#elif defined(GRAPHICS_BUFFERED)
	drawBuffered();
#endif
}

/************************************************************************
* function	: static void drawDirect(CDC *pDC
*
* argument	: CDC* pDC - device context object pointer
* remark	: Direct drawing routines here.
*************************************************************************/
static void drawDirect(CDC *pDC){
	//begin of user code
	//Nothing to write currently.
	//end of user code
}

/***********************************************************************
* function	: static void drawBuffered()
*
* argument	: CDC* pDC -0 device object pointer
* remark	: Buffered drawing routines here.
************************************************************************/
static void drawBuffered(){
	//start of the user code
	//end of the user code
	int lineWidth = 0.01;
	int i,j;
	VTX *sch1,*sch2;
	stackp sc;
	DrawSolidBox_I(0,4*HEIGHT,1,4*HEIGHT+1,lineWidth,RGB(0,0,255),RGB(0,0,255));
	for(i=0;i<WIDTH;i++){
		DrawSolidBox_I(4*i+1,4*HEIGHT,4*i+4,4*HEIGHT+1,lineWidth,RGB(0,0,255),RGB(0,0,255));
		DrawSolidBox_I(4*i+4,4*HEIGHT,4*i+5,4*HEIGHT+1,lineWidth,RGB(0,0,255),RGB(0,0,255));
	}
	for(i=0;i<HEIGHT;i++){
		DrawSolidBox_I(0,4*(HEIGHT-i)-3,1,4*(HEIGHT-i),lineWidth,RGB(0,0,255),RGB(0,0,255));
		DrawSolidBox_I(0,4*(HEIGHT-i-1),1,4*(HEIGHT-i)-3,lineWidth,RGB(0,0,255),RGB(0,0,255));
		for(j=0;j<WIDTH;j++){
			if(map[i][j].right ==false)
				DrawSolidBox_I(4*(j+1),4*(HEIGHT-i)-3,4*j+5,4*(HEIGHT-i),lineWidth,RGB(0,0,255),RGB(0,0,255));
			if(map[i][j].down == false)
				DrawSolidBox_I(4*j+1,4*(HEIGHT-i-1),4*(j+1),4*(HEIGHT-i)-3,lineWidth,RGB(0,0,255),RGB(0,0,255));
			DrawSolidBox_I(4*(j+1),4*(HEIGHT-i-1),4*j+5,4*(HEIGHT-i)-3,lineWidth,RGB(0,0,255),RGB(0,0,255));
		}
	}



	if(drawmode==1){
		sc=stb;
		sch1=sc->node;
		sc=sc->L;
		while(1){
			sch2=sc->node;
			sc=sc->L;
			//DrawSolidBox_I(4*sch1->col+2,4*(HEIGHT-sch1->row)-1,4*sch1->col+3,4*(HEIGHT-sch1->row),lineWidth,RGB(150,150,150),RGB(150,150,150));
			DrawLine_I(4*sch1->col+2,4*(HEIGHT-sch1->row)-1,4*sch2->col+2,4*(HEIGHT-sch2->row)-1,13,RGB(150,150,150));
			if(sc==NULL){
				break;
			}
			sch1=sch2;
		}
		sc=sta;
		sch1=sc->node;
		sc=sc->L;
		while(1){
			sch2=sc->node;
			sc=sc->L;
			//DrawSolidBox_I(4*sch1->col+2,4*(HEIGHT-sch1->row)-1,4*sch1->col+3,4*(HEIGHT-sch1->row),lineWidth,RGB(150,150,150),RGB(150,150,150));
			DrawLine_I(4*sch1->col+2,4*(HEIGHT-sch1->row)-1,4*sch2->col+2,4*(HEIGHT-sch2->row)-1,15,RGB(10,10,10));
			if(sc==NULL){
				break;
			}
			sch1=sch2;
		}
	}

}