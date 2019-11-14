#include <stdlib.h>
#include <stdio.h>
#include "..\ExternDoc.h"
#include "..\UI\Zoom.h"
#include "..\UI\MsgView.h"
#include "..\Graphics\DrawFunc.h"
#include "..\Example\Example.h"

#define VISITED 1
#define NOT_VISITED 0

void draw();
void DFS();
void BFS();
void push(int h, int w);
int* pop();

typedef struct STACK
{
	int width;
	int height;
	STACK *next;
}stack;

typedef struct ROOM
{
	int room_num;
	int r_flag;
	int b_flag;
	int l_flag;
	int u_flag;
	int path;
}room;
room ** maze;

typedef struct _Node{
	int col;
	int row;
}Stack;

Node *Stack;
Node *Queue;

int* count;
int a=0;
int b=0;
int height=0;
int width=0;
int num=0;
stack *first=NULL;
bool dfs_flag=false;
bool bfs_flag = false;
#define ERROR_NUMBER -1

int front = -1, rear = -1;
int top = -1;

//function prototype

void spush(int col, int row);
void spop();
void qpush(int col, int row);
void qpop();

static void drawDirect(CDC *pDC);
static void drawBuffered();

//Start of user code
#include <float.h>

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
	char buf[1000];
	int i,j;
	int flag=0;
	int tempp=0;
	char temp[2];
	if(height!=0)
		height=0;
	if(width!=0)
		width=0;
	if(num!=0)
		num=0;
	FILE *fp;
	fp = fopen(filename,"r");
	if( fp == NULL )
		AfxMessageBox("File Open Error");
	while(!feof(fp))
	{
		fgets(buf,1000,fp);
		if( flag == 0 )
		{
			while(buf[width] !=10)
				width++;
			flag = 1;
		}
		height++;
	}
	height = height/2;
	width = width/2;
	
	maze=(room**)malloc(sizeof(room*)*height);
	for(i=0;i<height;i++)
		maze[i]=(room*)malloc(sizeof(room)*width);
	for(i=0;i<height;i++)
		for(j=0;j<width;j++)
		{
			maze[i][j].room_num=num++;
			maze[i][j].b_flag=0;
			maze[i][j].r_flag=0;
			maze[i][j].u_flag=0;
			maze[i][j].l_flag=0;
			maze[i][j].path=0;
		}

	fclose(fp);
	fp = fopen(filename,"r");
	fgets(buf,1000,fp);
	for(i=0;i<height;i++)
	{
		fscanf(fp,"%c",&temp[0]);
		for(j=0;j<width;j++)
		{
			fscanf(fp,"%c%c",&temp[0],&temp[1]);
			if(temp[1]==' ')
				maze[i][j].r_flag=1;
			else
				maze[i][j].r_flag=0;
		}
		fscanf(fp,"%c%c",&temp[0],&temp[1]);
		for(j=0;j<width;j++)
		{
			fscanf(fp,"%c%c",&temp[0],&temp[1]);
			if(temp[0] ==' ')
				maze[i][j].b_flag = 1;
			else
				maze[i][j].b_flag = 0;
		}
		fscanf(fp,"%c",&temp[0]);	
	}
	maze[0][0].l_flag=0;
	maze[0][0].u_flag=0;
	maze[height-1][width-1].b_flag=0;
	maze[height-1][width-1].r_flag=0;
	for(i=1;i<width;i++)
	{
		maze[0][i].u_flag = 0;
		if(maze[0][i-1].r_flag == 0)
			maze[0][i].l_flag = 0;
		else if(maze[0][i-1].r_flag == 1 )
			maze[0][i].l_flag = 1;
	}
	for(i=1;i<width;i++)
	{
		maze[height-1][i].u_flag = 0;
		if(maze[height-1][i-1].r_flag == 0)
			maze[height-1][i].l_flag = 0;
		else if(maze[height-1][i-1].r_flag == 1 )
			maze[height-1][i].l_flag = 1;
	}

	for(i=1;i<height;i++)
	{
		maze[i][0].l_flag=0;
		if(maze[i-1][0].b_flag == 0)
			maze[i][0].u_flag =0;
		else if(maze[i-1][0].b_flag == 1)
			maze[i][0].u_flag =1;
	}
	for(i=1;i<height;i++)
	{
		maze[i][width-1].l_flag=0;
		if(maze[i-1][width-1].b_flag == 0)
			maze[i][width-1].u_flag =0;
		else if(maze[i-1][width-1].b_flag == 1)
			maze[i][width-1].u_flag =1;
	}

	for(i=1;i<height;i++)
	{
		for(j=1;j<width;j++)
		{
			if(maze[i][j-1].r_flag == 0)
				maze[i][j].l_flag = 0;
			else if(maze[i][j-1].r_flag == 1 )
				maze[i][j].l_flag = 1;
			if(maze[i-1][j].b_flag == 0)
				maze[i][j].u_flag =0;
			else if(maze[i-1][j].b_flag == 1)
				maze[i][j].u_flag =1;
		}
	}
	count =(int*)malloc(sizeof(int)*(height*width));
	flag=0;
	for(i=0;i<height;i++)
	{
		for(j=0;j<width;j++)
		{
			tempp=0;
			if(maze[i][j].r_flag == 1)
				tempp++;
			if(maze[i][j].b_flag == 1)
				tempp++;
			if(maze[i][j].u_flag == 1)
				tempp++;
			if(maze[i][j].l_flag == 1)
				tempp++;
			count[flag++] = tempp;
		}
	}
	setWindow(0,0,5*width,5*height,1);
	fclose(fp);
	
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
	stack * temp;
	int i;
	for(i=0;i<height;i++)
		free(maze[i]);
	free(maze);
	while(first!=NULL)
	{
		temp = first;
		first = first->next;
		free(temp);
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
	int i, j;
	int x1,y1,x2,y2;

	
	draw();
	x1=0; 
	x2=1;
	y1=1;
	y2=4;
	
	if(width!=0)
	for(i=0;i<height;i++)
	{
		DrawSolidBox_I(x1, y1, x2, y2, 1, RGB(0,0,255),RGB(0,0,255));
		for(j=0;j<width;j++)
		{
			x1=x1+4; 
			x2=x2+4;
			
			if(maze[i][j].r_flag==0)
				DrawSolidBox_I(x1, y1, x2, y2, 1, RGB(0,0,255),RGB(0,0,255));
		}
		

		x1=0;
		x2=1;
		y1=y1+3;
		y2++;

		DrawSolidBox_I(x1, y1, x2, y2, 1, RGB(0,0,255),RGB(0,0,255));
		for(j=0;j<width;j++)
		{
			x1++;
			x2=x2+3;
			if(maze[i][j].b_flag==0)
				DrawSolidBox_I(x1, y1, x2, y2, 1, RGB(0,0,255),RGB(0,0,255));

			x1=x1+3;
			x2++;
			DrawSolidBox_I(x1, y1, x2, y2, 1, RGB(0,0,255),RGB(0,0,255));
		}	
		x1=0;
		x2=1;
		y1++;
		y2=y2+3;
	}
	if(dfs_flag==true)
	{	
		for(i=0;i<height;i++)
		{
			for(j=0;j<width;j++)
			{
				if(maze[i][j].path==1)
				{
					if(maze[i][j].r_flag==1 && maze[i][j+1].path==1 && j<width-1)
					{
						x1=j*4+2.5;
						y1=i*4+2.5;
						x2=(j+1)*4+2.5;
						y2=i*4+2.5;
						DrawLine_I(x1,y1,x2,y2,5,RGB(0,0,128));
					}
					if(maze[i][j].b_flag==1 && maze[i+1][j].path==1 && i<height-1)
					{
						x1=j*4+2.5;
						y1=i*4+2.5;
						x2=j*4+2.5;
						y2=(i+1)*4+2.5;
						DrawLine_I(x1,y1,x2,y2,5,RGB(0,0,128));
					}
					if(maze[i][j-1].r_flag==1 && maze[i][j-1].path==1 && j>0)
					{
						x1=j*4+2.5;
						y1=i*4+2.5;
						x2=(j-1)*4+2.5;
						y2=i*4+2.5;
						DrawLine_I(x1,y1,x2,y2,5,RGB(0,0,128));
					}
					if(i>0 && maze[i-1][j].b_flag==1 && maze[i-1][j].path==1)
					{
						x1=j*4+2.5;
						y1=i*4+2.5;
						x2=j*4+2.5;
						y2=(i-1)*4+2.5;
						DrawLine_I(x1,y1,x2,y2,5,RGB(0,0,128));
					}
				}
			}
		}
		for(i=0;i<height;i++)
		{
			for(j=0;j<width;j++)
			{
				if(maze[i][j].path==2)
				{
					if(maze[i][j].r_flag==1 && maze[i][j+1].path==1 && j<width-1)
					{
						x1=j*4+2.5;
						y1=i*4+2.5;
						x2=(j+1)*4+2.5;
						y2=i*4+2.5;
						DrawLine_I(x1,y1,x2,y2,5,RGB(0,0,128));
					}
					if(maze[i][j].b_flag==1 && maze[i+1][j].path==1 && i<height-1)
					{
						x1=j*4+2.5;
						y1=i*4+2.5;
						x2=j*4+2.5;
						y2=(i+1)*4+2.5;
						DrawLine_I(x1,y1,x2,y2,5,RGB(0,0,128));
					}
					if(maze[i][j-1].r_flag==1 && maze[i][j-1].path==1 && j>0)
					{
						x1=j*4+2.5;
						y1=i*4+2.5;
						x2=(j-1)*4+2.5;
						y2=i*4+2.5;
						DrawLine_I(x1,y1,x2,y2,5,RGB(0,0,128));
					}
					if(i>0 && maze[i-1][j].b_flag==1 && maze[i-1][j].path==1)
					{
						x1=j*4+2.5;
						y1=i*4+2.5;
						x2=j*4+2.5;
						y2=(i-1)*4+2.5;
						DrawLine_I(x1,y1,x2,y2,5,RGB(0,0,128));
					}
				}
			}
			
		}
		dfs_flag = false;

	}
	else if (bfs_flag == true){
		front = -1;
		rear = -1;
		for (i = 0; i < width; i++){
			for (j = 0; j < height; j++){
				maze[i][j].path = NOT_VISITED;
			}
		}

		/*Queue¸¦ ±¸Çö*/
		Queue = (Node*)malloc(sizeof(Node)*(height*width));
		DrawSolidBox_I(0.4, 0.4, 0.6, 0.6, 3, RGB(0, 0, 255), RGB(0, 0, 255));
		DrawSolidBox_I(height - 1 + 0.4, width - 1 + 0.4, height - 1 + 0.6, width - 1 + 0.6, 3, RGB(0, 0, 255), RGB(0, 0, 255));
		i = 0;
		j = 0;
		qpush(i, j);
		maze[i][j].path = VISITED;
		while (rear != front){
			qpop();
			i = Queue[front].col;
			j = Queue[front].row;
			if (maze[i][j].r_flag == 1){
				if (maze[i][j + 1].path == NOT_VISITED){
					maze[i][j + 1].path = VISITED;
					qpush(i, j + 1);
					DrawLine_I(j + 0.5, i + 0.5, j + 1.5, i + 0.5, 3, RGB(255, 0, 0));
					if (i == width - 1 && j == height - 2)
						break;
				}
			}
			if (maze[i][j].b_flag == 1){
				if (maze[i + 1][j].path == NOT_VISITED){
					maze[i + 1][j].path = VISITED;
					qpush(i + 1, j);
					DrawLine_I(j + 0.5, i + 0.5, j + 0.5, i + 1.5, 3, RGB(255, 0, 0));
					if (i == width - 2 && j == height - 1)
						break;
				}
			}
			if (maze[i][j].l_flag == 1){
				if (maze[i][j - 1].path == NOT_VISITED){
					maze[i][j - 1].path = VISITED;
					qpush(i, j - 1);
					DrawLine_I(j + 0.5, i + 0.5, j - 0.5, i + 0.5, 3, RGB(255, 0, 0));
				}
			}
			if (maze[i][j].u_flag == 1){
				if (maze[i - 1][j].path == NOT_VISITED){
					maze[i - 1][j].path = VISITED;
					qpush(i - 1, j);
					DrawLine_I(j + 0.5, i + 0.5, j + 0.5, i - 0.5, 3, RGB(255, 0, 0));
				}
			}
		}

		top = -1;//initialize
		for (i = 0; i < width; i++){
			for (j = 0; j < height; j++){
				maze[i][j].path = NOT_VISITED;
			}
		}
		//use dfs
		Stack = (Node*)malloc(sizeof(Node)*height*width);
		i = 0;
		j = 0;
		push(i, j);
		while (1){
			maze[i][j].path = VISITED;
			if (i == width - 1 && j == height - 1)
				break;
			if (maze[i][j].r_flag == 1){
				if (maze[i][j + 1].path == NOT_VISITED){
					maze[i][j + 1].path = VISITED;

					j = j + 1;
					spush(i, j);
					continue;
				}
			}
			if (maze[i][j].b_flag == 1){
				if (maze[i + 1][j].path == NOT_VISITED){
					maze[i + 1][j].path = VISITED;

					i = i + 1;
					spush(i, j);
					continue;
				}
			}
			if (maze[i][j].u_flag == 1){
				if (maze[i - 1][j].path == NOT_VISITED){
					maze[i - 1][j].path = VISITED;

					i = i - 1;
					spush(i, j);
					continue;
				}
			}
			if (maze[i][j].l_flag == 1){
				if (maze[i][j - 1].path == NOT_VISITED){
					maze[i][j - 1].path = VISITED;

					j = j - 1;
					spush(i, j);
					continue;
				}
			}
			spop();
			i = Stack[top].col;
			j = Stack[top].row;
		}
		for (i = 0; i < top; i++){
			DrawLine_I(Stack[i].height + 0.5, Stack[i].col + 0.5, Stack[i + 1].height + 0.5, Stack[i + 1].col + 0.5, 3, RGB(0, 255, 0));
		}

		free(Queue);
		free(Stack);
		bfs_flag = 0;
	}

		for(i=0;i<height;i++)
		{
			for(j=0;j<width;j++)
			{
				if(maze[i][j].path==2 || (i == height-1 && j== width-1))
				{
					if(maze[i][j].r_flag==1 && maze[i][j+1].path==2 && j<width-1)
					{
						x1=j*4+2.5;
						y1=i*4+2.5;
						x2=(j+1)*4+2.5;
						y2=i*4+2.5;
						DrawLine_I(x1,y1,x2,y2,5,RGB(128,128,128));
					}
					if(maze[i][j].b_flag==1 && maze[i+1][j].path==2 && i<height-1)
					{
						x1=j*4+2.5;
						y1=i*4+2.5;
						x2=j*4+2.5;
						y2=(i+1)*4+2.5;
						DrawLine_I(x1,y1,x2,y2,5,RGB(128,128,128));
					}
					if(maze[i][j-1].r_flag==1 && maze[i][j-1].path==2 && j>0)
					{
						x1=j*4+2.5;
						y1=i*4+2.5;
						x2=(j-1)*4+2.5;
						y2=i*4+2.5;
						DrawLine_I(x1,y1,x2,y2,5,RGB(128,128,128));
					}
					if(i>0 && maze[i-1][j].b_flag==1 && maze[i-1][j].path==2)
					{
						x1=j*4+2.5;
						y1=i*4+2.5;
						x2=j*4+2.5;
						y2=(i-1)*4+2.5;
						DrawLine_I(x1,y1,x2,y2,5,RGB(128,128,128));
					}
					
				}
			}
		}
		
	DrawSolidBox_I( 1.8, 1.8, 2.8, 2.8, 3, RGB( 0, 255, 0, ), RGB( 0, 255, 0 ) );
	DrawSolidBox_I( (width)*4-2.2, (height)*4-2.2, (width)*4-1.2, (height)*4-1.2,3, RGB( 0, 255, 0, ), RGB( 0, 255, 0 ) );
}
void draw()
{
	int i, j;
	int x1,y1,x2,y2;
	x1=0;
	y1=0;
	x2=1;
	y2=1;
	for(i=0;i<width;i++)
	{
		DrawSolidBox_I(x1, y1, x2, y2, 1, RGB(0,0,255),RGB(0,0,255));
		x1++; 
		x2=x2+3;
		DrawSolidBox_I(x1, y1, x2, y2, 1, RGB(0,0,255),RGB(0,0,255));
		x1=x1+3;
		x2++;
	}
	DrawSolidBox_I(x1, y1, x2, y2, 1, RGB(0,0,255),RGB(0,0,255));

}
void DFS()
{
	int finish = height*width-1;
	int w=0;
	int h=0;
	int *info;
	info = (int*)malloc(sizeof(int)*2);
	dfs_flag = true;
	
	while(1)
	{
		if(maze[h][w].room_num == finish)
			break;
		if(maze[h][w].u_flag==1 && maze[h-1][w].path == 0)
		{
			//count[maze[h][w].room_num]--;
			//count[maze[h-1][w].room_num]--;
			push(w,h);
			h=h-1;
		}
		else if(maze[h][w].r_flag==1 && maze[h][w+1].path == 0 )
		{
			//count[maze[h][w].room_num]--;
			//count[maze[h][w+1].room_num]--;
			push(w,h);
			w=w+1;
		}
		else if(maze[h][w].b_flag==1 && maze[h+1][w].path == 0)
		{
			//count[maze[h][w].room_num]--;
			//count[maze[h+1][w].room_num]--;
			push(w,h);
			h=h+1;
		}
		else if(maze[h][w].l_flag==1 && maze[h][w-1].path == 0)
		{
			//count[maze[h][w].room_num]--;
			//count[maze[h][w-1].room_num]--;
			push(w,h);
			w=w-1;
		}

		else
		{
			maze[h][w].path=1;
			info = pop();
			h= info[0];
			w = info[1];
		}
	}
	maze[0][0].path =2;
}
void push(int w,int h)
{
	stack* node;
	maze[h][w].path=2;
	node = (stack*)malloc(sizeof(stack));
	node->width = w;
	node->height=h;
	b++;
	if(first==NULL)
	{
		first = node;
		node->next = NULL;
	}

	else
	{
		node->next = first;
		first = node;
	}
}
int* pop()
{
	
	stack* temp;
	int* inf;
	inf = (int*)malloc(sizeof(int)*2);
	a++;
	if(first==NULL)
	{
		temp = first;
		inf[0] = temp->height;
		inf[1] = temp->width;
		temp->next=NULL;
		maze[inf[0]][inf[1]].path = 1;
		free(temp);
		return inf;
	}
	else
	{
		temp = first;
		first = first->next;
		inf[0] = temp->height;
		inf[1] = temp->width;
		temp->next=NULL;
		maze[inf[0]][inf[1]].path = 1;
		free(temp);
		return inf;
	}

		

}

void spush(int col, int row){
	top++;
	Stack[top].col = col;
	Stack[top].row = row;
}
void spop(){
	top--;
}

void qpush(int col, int row){
	rear++;
	Queue[rear].col = col;
	Queue[rear].row = row;
}
void qpop(){
	front++;
}

void BFS()
{
	bfs_flag = true;
}