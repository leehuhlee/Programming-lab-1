#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef struct{
	int bottom,right;
	int data;
}node;

int main(void){
	int r,c,c2;
	int row,col,temp;
	int flag=0;
	FILE *f=fopen("maze.maz","w");
	node **maze;
	node *curr, *prev;
	int set=1;

	srand(time(NULL));

	//input row col
	scanf("%d",&col);
	scanf("%d",&row);

	//make memory
	maze=(node**)malloc(sizeof(node*)*row);
	for(r=0;r<row;r++){
		maze[r]=(node*)malloc(sizeof(node)*col);
	}
	
	//initial maze
	for(r=0;r<row;r++){
		for(c=0;c<col;c++){
			maze[r][c].bottom=0;
			maze[r][c].right=0;
			maze[r][c].data=set;
			set++;
		}
	}

	// 0 is close 
	// 1 is open

	//complete maze
	for(r=0;r<row;r++){
		for(c=0;c<col;c++){
			//if(maze[r][c].data==maze[r][c+1].data) maze[r][c].right=0;
			//else 
			maze[r][c].right=rand()%2; //right random

			if(r==row-1){ // r is final row
				if(maze[r][c].data!=maze[r][c+1].data && c!=col-1) maze[r][c].right=1; 
			}

			if(maze[r][c].right==1){// col right is open
				temp=maze[r][c+1].data;

				if(c!=col-1){ // c is not final col
					maze[r][c+1].data=maze[r][c].data; // input same data
				}
				for(c2=0;c2<col;c2++){
					if(maze[r][c2].data==temp){
						maze[r][c2].data=maze[r][c].data;
					}
				}
			}
			if(c==col-1) maze[r][c].right=0; //fical col close
		}
		for(c=0;c<col;c++){//determine down node
			if(r==row-1) break; // r is final row
			maze[r][c].bottom=rand()%2; // bottom random

			if(maze[r][c].bottom) flag=1;

			if(maze[r][c].data!=maze[r][c+1].data){
				if(!flag) maze[r][c].bottom=1;
				else flag=0;
			}
			//if(maze[r][c].bottom){ // input same data
			//	maze[r+1][c].data=maze[r][c].data;
		//	}
		}
	}

	//print first line
	for(c=0;c<2*col+1;c++){
		if(c%2==0){
			fprintf(f,"+");
		}
		else{
			fprintf(f,"-");
		}
	}

	fprintf(f,"\n");

	// print last line
	for(r=0;r<row;r++){
		fprintf(f,"|");
		for(c=0;c<col;c++){
			if(maze[r][c].right==1){
				fprintf(f,"  ");
			}
			else{
				fprintf(f," |");
			}
		}
		fprintf(f,"\n");
		fprintf(f,"+");
		for(c=0;c<col;c++){
			if(maze[r][c].bottom==1){
				fprintf(f," +");
			}
			else{
				fprintf(f,"-+");
			}
		}
		fprintf(f,"\n");
	}

	fclose(f);

	return 0;
}
