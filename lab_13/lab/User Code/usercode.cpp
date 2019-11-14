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

/*****************************************************************
* function	: bool readFile(const char* filename)
* argument	: cons char* filename - filename to be opened
* return	: true if success, otherwise flase
* remark	: After read data file, phisycal view must be set;
*			  otherwise drawing will not be executed correctly.
*			  The window will be invalidated after readFile()
*			  returns true.
******************************************************************/

typedef struct _Maze {
	int row ;
	int col ;
	int right ;
	int down ;
} Maze ;

Maze **maze ;
int row, col;

bool readFile(const char* filename){
	//start of the user code
	char wall = 0 ;
	int i , j ;
	int flag = 0 ;
	FILE *fp = fopen ( filename , "r" ) ;

	if ( ! fp ) return false ;

	row = 0;
	col = 0;

	while ( wall != '|' ) { //becase first line is constructed by + or - , so second line's first is |
		fscanf ( fp , "%c" , &wall ) ;
		col++;
	}
	col = col / 2 - 1 ; //contain |
	while ( fscanf ( fp , "%c" , &wall ) != EOF ) row++ ; //just EOS, i don't coding about line
	row = ( ( row + 1 ) / ( col * 2 + 1 ) ) / 2 ;

	maze = ( Maze** ) malloc ( sizeof ( Maze* ) * row ) ; // give first line memory
	for ( i = 0 ; i < row ; i++ ) {
		maze[ i ] = ( Maze* ) malloc ( sizeof ( Maze ) * col ) ;
	}
	fclose ( fp ) ;

	// %*c is trash
	fp = fopen ( filename , "r" ) ;
	fscanf ( fp , "%*c" ) ; // first line
	for ( i = 0 ; i < col ; i++ ) fscanf ( fp , "%*c%*c" ) ;
	i = 0 ;
	while ( 1 ) {
		if ( i == row ) break ;
		fscanf ( fp , "%*c%c" , &wall ) ;
		for ( j = 0 ; j < col ; j++ ) { //save for right wall info.
			fscanf ( fp , "%*c%c" , &wall ) ;
			maze[ i ][ j ].row = i ;
			maze[ i ][ j ].col = j ;
			if ( wall == '|' ) maze[ i ][ j ].right = 1 ;
			else maze[ i ][ j ].right = 0 ;	
		}
		fscanf ( fp , "%*c%*c" ) ; // | +
		for ( j = 0 ; j < col ; j++ ) {
			fscanf ( fp , "%c%*c" , &wall ) ;
			if ( wall == '-' ) maze[ i ][ j ].down = 1 ;
			else maze[ i ][ j ].down = 0 ;
		}
		i++ ;
	}
	fclose ( fp ) ;
	setWindow ( 0 , 0 , 4 * col + 5 , 4 * row + 5 , 0 ) ;
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
	int i ;
	for ( i = 0 ; i < row ; i++ )
		free ( maze[ i ] ) ;
	free ( maze ) ;
	//end of usercode
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

	int lineWidth = 0.01 ;
	int i , j , x , y ; 

	//Draw upper border

	// first row
	DrawSolidBox_I ( 0, 4 * row , 1 , 4 * row + 1 , lineWidth , RGB ( 0 , 0 , 255 ) , RGB ( 0 , 0 , 255 ) ) ; //first block
	for ( i = 0 ; i < col ; i++ ) {
		DrawSolidBox_I ( 4 * i + 1 , 4 * row , 4 * i + 4 , 4 * row + 1 , lineWidth , RGB ( 0 , 0 , 255 ) , RGB ( 0 , 0 , 255 ) ) ; // edge
		DrawSolidBox_I ( 4 * i + 4 , 4 * row , 4 * i + 5 , 4 * row + 1 , lineWidth , RGB ( 0 , 0 , 255 ) , RGB ( 0 , 0 , 255 ) ) ; // node
	}

	// first col
	for ( i = 0 ; i < row ; i++ ) {
		DrawSolidBox_I ( 0 , 4 * ( row - i ) - 3 , 1 , 4 * ( row - i ) , lineWidth , RGB ( 0 , 0 , 255 ) , RGB ( 0 , 0 , 255 ) ) ;
		DrawSolidBox_I ( 0 , 4 * ( row - i - 1 ) , 1 , 4 * ( row - i ) - 3 , lineWidth , RGB ( 0 , 0 , 255 ) , RGB ( 0 , 0 , 255 ) ) ;

		// otherwise
		for ( j = 0 ; j < col ; j++ ) {
			if ( maze[ i ][ j ].right == 1 )
				DrawSolidBox_I ( 4 * ( j + 1  ) , 4 * ( row - i ) - 3 , 4 * j + 5 , 4 * ( row - i ) , lineWidth , RGB ( 0 , 0 , 255 ) , RGB ( 0 , 0 , 255 ) ) ;
			if ( maze[ i ][ j ].down == 1 )
				DrawSolidBox_I ( 4 * j + 1 , 4 * ( row - i - 1 ) , 4 * ( j + 1 ) , 4 * ( row - i ) - 3 , lineWidth , RGB ( 0 , 0 , 255 ) , RGB ( 0 , 0 , 255 ) ) ;
				DrawSolidBox_I ( 4 * ( j + 1  ) , 4 * ( row - i - 1 ) , 4 * j + 5 , 4 * ( row - i ) - 3 , lineWidth , RGB ( 0 , 0 , 255 ) , RGB ( 0 , 0 , 255 ) ) ;
		}
	}
	//end of the user code
}