#include "tetris.h"

static struct sigaction act, oact;

int main(){
	int exit=0;

	initscr();
	noecho();
	keypad(stdscr, TRUE);	
	createRankList();
	srand((unsigned int)time(NULL));
	while(!exit){
		clear();
		switch(menu()){
		case MENU_PLAY: play(); break;
		case MENU_RANK: rank(); break;
		case MENU_EXIT: exit=1; break;
		default: break;
		}
	}

	endwin();
	system("clear");
	return 0;
}

void InitTetris(){
	int i,j;

	for(j=0;j<HEIGHT;j++)
		for(i=0;i<WIDTH;i++)
			field[j][i]=0;

	nextBlock[0]=rand()%7;
	nextBlock[1]=rand()%7;
	nextBlock[2]=rand()%7;
	blockRotate=0;
	blockY=-1;
	blockX=WIDTH/2-2;
	score=0;	
	gameOver=0;
	timed_out=0;

	DrawOutline();
	DrawField();
	DrawBlockWithFeatures(blockY,blockX,nextBlock[0],blockRotate);
	DrawNextBlock(nextBlock);
	PrintScore(score);
}

void DrawOutline(){	
	int i,j;
	/* 블럭이 떨어지는 공간의 태두리를 그린다.*/
	DrawBox(0,0,HEIGHT,WIDTH);

	/* next block을 보여주는 공간의 태두리를 그린다.*/
	move(2,WIDTH+10);
	printw("NEXT BLOCK");
	DrawBox(3,WIDTH+10,4,8);

	move(8,WIDTH+10);
	printw("NEXT BLOCK");
	DrawBox(9,WIDTH+10,4,8);

	/* score를 보여주는 공간의 태두리를 그린다.*/
	move(14,WIDTH+10);
	printw("SCORE");
	DrawBox(15,WIDTH+10,1,8);
}

int GetCommand(){
	int command;
	command = wgetch(stdscr);
	switch(command){
	case KEY_UP:
		break;
	case KEY_DOWN:
		break;
	case KEY_LEFT:
		break;
	case KEY_RIGHT:
		break;
	case ' ':	/* space key*/
		/*fall block*/
		break;
	case 'q':
	case 'Q':
		command = QUIT;
		break;
	default:
		command = NOTHING;
		break;
	}
	return command;
}

int ProcessCommand(int command){
	int ret=1;
	int drawFlag=0;
	switch(command){
	case QUIT:
		ret = QUIT;
		break;
	case KEY_UP:
		if((drawFlag = CheckToMove(field,nextBlock[0],(blockRotate+1)%4,blockY,blockX)))
			blockRotate=(blockRotate+1)%4;
		break;
	case KEY_DOWN:
		if((drawFlag = CheckToMove(field,nextBlock[0],blockRotate,blockY+1,blockX)))
			blockY++;
		break;
	case KEY_RIGHT:
		if((drawFlag = CheckToMove(field,nextBlock[0],blockRotate,blockY,blockX+1)))
			blockX++;
		break;
	case KEY_LEFT:
		if((drawFlag = CheckToMove(field,nextBlock[0],blockRotate,blockY,blockX-1)))
			blockX--;
		break;
	default:
		break;
	}
	if(drawFlag) DrawChange(field,command,nextBlock[0],blockRotate,blockY,blockX);
	return ret;	
}

void DrawField(){
	int i,j;
	for(j=0;j<HEIGHT;j++){
		move(j+1,1);
		for(i=0;i<WIDTH;i++){
			if(field[j][i]==1){
				attron(A_REVERSE);
				printw(" ");
				attroff(A_REVERSE);
			}
			else printw(".");
		}
	}
}


void PrintScore(int score){
	move(16,WIDTH+11);
	printw("%8d",score);
}

void DrawNextBlock(int *nextBlock){
	int i, j;
	for( i = 0; i < 4; i++ ){
		move(4+i,WIDTH+13);
		for( j = 0; j < 4; j++ ){
			if( block[nextBlock[1]][0][i][j] == 1 ){
				attron(A_REVERSE);
				printw(" ");
				attroff(A_REVERSE);
			}
			else printw(" ");
		}
	}
	for(i=0;i<4;i++){
		move(10+i,WIDTH+13);
		for(j=0;j<4;j++){
			if(block[nextBlock[2]][0][i][j]==1){
				attron(A_REVERSE);
				printw(" ");
				attroff(A_REVERSE);
			}
			else printw(" ");
		}
	}
}

void DrawBlock(int y, int x, int blockID,int blockRotate,char tile){
	int i,j;
	for(i=0;i<4;i++)
		for(j=0;j<4;j++){
			if(block[blockID][blockRotate][i][j]==1 && i+y>=0){
				move(i+y+1,j+x+1);
				attron(A_REVERSE);
				printw("%c",tile);
				attroff(A_REVERSE);
			}
		}

	move(HEIGHT,WIDTH+10);
}

void DrawBox(int y,int x, int height, int width){
	int i,j;
	move(y,x);
	addch(ACS_ULCORNER);
	for(i=0;i<width;i++)
		addch(ACS_HLINE);
	addch(ACS_URCORNER);
	for(j=0;j<height;j++){
		move(y+j+1,x);
		addch(ACS_VLINE);
		move(y+j+1,x+width+1);
		addch(ACS_VLINE);
	}
	move(y+j+1,x);
	addch(ACS_LLCORNER);
	for(i=0;i<width;i++)
		addch(ACS_HLINE);
	addch(ACS_LRCORNER);
}

void play(){
	int command;
	clear();
	act.sa_handler = BlockDown;
	sigaction(SIGALRM,&act,&oact);
	InitTetris();
	do{
		if(timed_out==0){
			alarm(1);
			timed_out=1;
		}

		command = GetCommand();
		if(ProcessCommand(command)==QUIT){
			alarm(0);
			DrawBox(HEIGHT/2-1,WIDTH/2-5,1,10);
			move(HEIGHT/2,WIDTH/2-4);
			printw("Good-bye!!");
			refresh();
			getch();
			newRank(score);

			return;
		}
	}while(!gameOver);

	alarm(0);
	getch();
	DrawBox(HEIGHT/2-1,WIDTH/2-5,1,10);
	move(HEIGHT/2,WIDTH/2-4);
	printw("GameOver!!");
	refresh();
	getch();
	newRank(score);
}

char menu(){
	printw("1. play\n");
	printw("2. rank\n");
	printw("3. recommended play\n");
	printw("4. exit\n");
	return wgetch(stdscr);
}

int CheckToMove(char f[HEIGHT][WIDTH],int currentBlock,int blockRotate, int blockY, int blockX){
	// user code
	int i,j;
	for(i=0; i<4;i++){
		for(j=0; j<4; j++){
			if(block[currentBlock][blockRotate][i][j]==1){
				 if(f[i+blockY][j+blockX]==1){
					 return 0;
				 }
				if((i+blockY)>=HEIGHT){
					return 0;
				}
				if((j+blockX)<0){
					return 0;
				}
				if((j+blockX)>=WIDTH){
					return 0;
				}
			}
		}
	}
	return 1;
}

void DrawChange(char f[HEIGHT][WIDTH],int command,int currentBlock,int blockRotate, int blockY, int blockX){
	// user code
	int i,j,x=blockX,y=blockY,r=blockRotate;
	switch(command){
		case KEY_UP : 
			r=(blockRotate+3)%4;
			break;
		case KEY_DOWN : 
			y--;
			break;
		case KEY_RIGHT : 
			x--;
			break;
		case KEY_LEFT : 
			x++;
			break;
	}
	for(i=0;i<4;i++){
		for(j=0;j<4;j++){
			if(block[currentBlock][r][i][j]==1 && i+y>=0){
						move(i+y+1,j+x+1);
						printw(".");
					}
				}
		}
			move(HEIGHT,WIDTH+10);
		
	DrawField();
	DrawBlockWithFeatures(blockY,blockX,currentBlock,blockRotate);
	//DrawBlock(blockY,blockX,currentBlock,blockRotate,' ');
}

void BlockDown(int sig){
	// user code
	int i;
	if(CheckToMove(field,nextBlock[0],blockRotate,blockY+1,blockX)==1){
		blockY++;
		DrawChange(field,KEY_DOWN,nextBlock[0],blockRotate,blockY,blockX);
	}
	else{
		if(blockY==-1){
			gameOver=1;
		}
		score+=AddBlockToField(field,nextBlock[0],blockRotate,blockY,blockX);
		score+=DeleteLine(field);
		nextBlock[0]=nextBlock[1];
		nextBlock[1]=nextBlock[2];
		nextBlock[2]=rand()%7;
		blockRotate=0;
		blockY=-1;
		blockX=(WIDTH/2)-2;
		DrawNextBlock(nextBlock);
		DrawField();
		PrintScore(score);
	}
	timed_out=0;
}

int AddBlockToField(char f[HEIGHT][WIDTH],int currentBlock,int blockRotate, int blockY, int blockX){
	// user code
	int i,j;
	int touched=0;
	for(i=0;i<4;i++){
		for(j=0;j<4;j++){
			if(block[currentBlock][blockRotate][i][j]==1){
				field[blockY+i][blockX+j]=1;
				if(field[blockY+i+1][blockX+j]==1||blockY+i+1==HEIGHT)
					touched++;
			}
		}
	}
	return touched*10;
}

int DeleteLine(char f[HEIGHT][WIDTH]){
	// user code
	int flag;
	int i, j, i2, j2;
	int line=0;
	for(i=0;i<HEIGHT;i++){
		flag=0;
		for(j=0;j<WIDTH;j++){
			if(f[i][j]==0) {
				flag=1;
			}
		}
			if( flag==0){
				line++;
				for(i2=i;i2>0;i2--){
					for(j2=0;j2<WIDTH;j2++){
						f[i2][j2]=f[i2-1][j2];
					}
				}
			}
		flag=0;
		}
		return line*line*100;
}

void DrawShadow(int y, int x, int blockID,int blockRotate){
	// user code
	while(CheckToMove(field,blockID,blockRotate,y,x)) y++;
	DrawBlock(y-1,x,blockID,blockRotate,'/');
}

void DrawBlockWithFeatures(int y, int x, int blockID, int blockRotate){
	DrawShadow(y,x,blockID,blockRotate);
	DrawBlock(y,x,blockID,blockRotate,' ');
}

void createRankList(){
	// user code
	int i,num;
	Node *pNode;
	char string[NAMELEN];
	FILE *fp=fopen("rank.txt","r");
	fscanf(fp,"%d",&size);
	for(i=0;i<size;i++){
		fscanf(fp,"%s %d",string, &num);
		if(!head){
			head=createnewNode(string,num);
		}
		else{
			for(pNode=head;pNode->link!=NULL;pNode=pNode->link);
			pNode->link=createnewNode(string,num);
		}
	}
	fclose(fp);
}

Node* createnewNode(char* string,int num){
	Node* newNode;
	newNode=(Node*)malloc(sizeof(Node));
	strcpy(newNode->name, string);
	newNode->score = num;
	newNode->link=NULL;
	return newNode;
}

void rank(){
	// user code
	int x=1,y=size,count=1, nameflag,index;
	char username[NAMELEN];
	Node* pNode=head, *delNode, *front=head, *rear=head->link;
	clear();
	printw("1. list ranks from X to Y\n");
	printw("2. list ranks by a specific name\n");
	printw("3. delete a specific rank\n");
	switch(wgetch(stdscr)){
		case '1':
			echo();
			printw("x : ");
			scanw("%d",&x);
			printw("y : ");
			scanw("%d",&y);
			noecho();
		printw("       name        |    score\n");
		printw("------------------------------------\n");
	if(x<1 || x>size || x=='\0') x=1;
	if(y<1 || y>size || y=='\0') y=size;
	if(x>y) printw("search failure: no rank in the list\n");
	else{
		while(count<=y){
			if(count>=x) printw("%-18s | %d\n",pNode->name,pNode->score);
			pNode=pNode->link;
			count++;
		}
	}
		break;
		case '2':
			nameflag=0;
			echo();
			printw("input the  name: ");
			scanw("%s",username);
			noecho();		
			printw("       name       |    score\n");
			printw("------------------------------------\n");
			for(;pNode!=NULL;pNode=pNode->link){
				if(strcmp(username,pNode->name)==0){
					printw("%-18s | %d\n",pNode->name,pNode->score);
					nameflag=1;
				}
			}
			if(nameflag==0){
				printw("search failure: no name in the list");
			}
			break;
		case '3':
			echo();
			printw("input the rank: ");
			scanw("%d",&index);
			noecho();
			if(size<index||index<=0){
				printw("serch failure: the rank not in the list");
				break;
			}
			if(index==1){
				front=NULL;
				printw("serch failure: the rank not in the list");
				head=rear;
				size--;
				writeRankFile();
				break;
			}
			else{
				printw("result: the rank deleted");
				for(count=1;count<index-1;rear=rear->link,front=front->link){
					count++;
				}
				size--;
				front->link=rear->link;
				writeRankFile();
			}
			break;
	}
	getch(); 
}

void writeRankFile(){
	// user code
	FILE *fp=fopen("rank.txt","w");
	Node* pNode;
	fprintf(fp,"%d\n",size);
	for(pNode=head;pNode->link!=NULL;pNode=pNode->link){
		fprintf(fp,"%s %d\n",pNode->name,pNode->score);
	}
	fprintf(fp,"%s %d\n",pNode->name,pNode->score);
}

void newRank(int score){
	// user code
	char user[NAMELEN];
	Node *curr, *pNode=head,*qNode;
	clear();
	echo();
	printw("your name : ");
	scanw("%s", user);
	curr=(Node*)malloc(sizeof(Node));
	strcpy(curr->name,user);
	curr->score=score;
	if(head==NULL){
		curr->link=NULL;
		head=curr;
	}
	else{
		while(1){
			if(pNode->link==NULL || pNode->link->score<score)break;
			pNode=pNode->link;
		}
		if(pNode->link==NULL)
		for(qNode=head;qNode->link!=NULL;qNode=qNode->link);
		qNode=curr;
		curr->link=pNode->link;
		pNode->link=curr;
	}
	size++;
	writeRankFile();
	noecho();
}

void DrawRecommend(int y, int x, int blockID,int blockRotate){
	// user code
}

int recommend(RecNode *root){
	int max=0; // 미리 보이는 블럭의 추천 배치까지 고려했을 때 얻을 수 있는 최대 점수

	// user code

	return max;
}

void recommendedPlay(){
	// user code
}
