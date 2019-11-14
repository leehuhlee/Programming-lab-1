#include "tetris.h"

static struct sigaction act, oact;
int main(){
	int exit=0;

	initscr();
	noecho();
	keypad(stdscr, TRUE);	

	srand((unsigned int)time(NULL));

	recRoot=(RecNode*)malloc(sizeof(RecNode));
	recRoot->lv=-1;
	recRoot->score=0;
	recRoot->f=field;
	constructRecTree(recRoot);

	createRankList();

	while(!exit){
		clear();
		switch(menu()){
		case MENU_PLAY: play(); break;
		case MENU_RANK: rank(); break;
		case MENU_REC_PLAY: recommendedPlay(); break;
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
//	printw("%d",recRoot->lv);
	for(j=0;j<HEIGHT;j++)
		for(i=0;i<WIDTH;i++)
			field[j][i]=0;
//	printw("%d",recRoot->lv);
	nextBlock[0]=rand()%7;
	nextBlock[1]=rand()%7;
	nextBlock[2]=rand()%7;
//	printw("%d",recRoot->lv);
	blockRotate=0;
	blockY=-1;
	blockX=WIDTH/2-2;
	score=0;	
//	printw("%d",recRoot->lv);
	gameOver=0;
	timed_out=0;
//	printw("%d",recRoot->lv);
	recommend(recRoot);

	DrawOutline();
	DrawField();
	DrawBlockWithFeatures(blockY, blockX, nextBlock[0], blockRotate);
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
	DrawBox(10,WIDTH+10,4,8);
		
	/* score를 보여주는 공간의 태두리를 그린다.*/
	move(16,WIDTH+10);
	printw("SCORE");
	DrawBox(17,WIDTH+10,1,8);
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
	move(18,WIDTH+11);
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
		move(11+i, WIDTH+13);
		for(j=0; j<4; j++){
			if( block[nextBlock[2]][0][i][j] == 1 ){
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

int CheckToMove(char f[HEIGHT][WIDTH], int currentBlock, int blockRotate, int blockY, int blockX){
	int i, j;

	for(i=0; i<4; i++){
		for(j=0; j<4; j++){
			if(block[currentBlock][blockRotate][i][j]==1){
				if(f[i+blockY][j+blockX]==1) return 0;
				if(blockY+i>=HEIGHT) return 0;
				if(blockX+j<0) return 0;
				if(blockX+j>=WIDTH) return 0;
			}
		}
	}
	return 1;
}
void constructRecTree(RecNode *root){
	int i, h;
	RecNode **c=root->c;
	for(i=0; i<CHILDREN_MAX; ++i){
		c[i]=(RecNode *)malloc(sizeof(RecNode));
		c[i]->lv=root->lv+1;
		c[i]->f=(char(*)[WIDTH])malloc(sizeof(char)*HEIGHT*WIDTH);
		if(c[i]->lv < VISIBLE_BLOCKS){
			constructRecTree(c[i]);
		}
	}
}

void DrawChange(char f[HEIGHT][WIDTH],int command,int currentBlock,int blockRotate, int blockY, int blockX){
	
	int rot;
	int x, y;
	int sy;
	int i, j;

	rot=blockRotate;
	x=blockX;
	y=blockY;

	switch(command){
		case KEY_UP:
			rot=(rot+3)%4;
			break;
		case KEY_DOWN:
			y--;
			break;
		case KEY_LEFT:
			x++;
			break;
		case KEY_RIGHT:
			x--;
			break;
	}

	sy=y;

	while(CheckToMove(f,currentBlock,rot,sy+1,x))
		sy++;

	for(i=0; i<4; i++){
		for(j=0; j<4; j++){
			if(block[currentBlock][rot][i][j]==1){
				if((i+y>=0)&&(j+x<WIDTH)){
					move(i+y+1, j+x+1);
					printw(".");
				}
			}
			if(block[currentBlock][rot][i][j]==1){
				if((i+y>=0)&&(j+x<WIDTH)){
					move(i+sy+1, j+x+1);
					printw(".");
				}
			}
		}
	}

	DrawBlockWithFeatures(blockY, blockX, currentBlock, blockRotate);

}

void BlockDown(int sig){

	int check;

	check=CheckToMove(field, nextBlock[0], blockRotate, blockY+1, blockX);
	if(check){
		blockY++;
		DrawChange(field, KEY_DOWN, nextBlock[0], blockRotate, blockY, blockX);
		
	}
	else{
		if(blockY==-1) gameOver=1;
		score += AddBlockToField(field, nextBlock[0], blockRotate, blockY, blockX);
		score += DeleteLine(field);
		nextBlock[0]=nextBlock[1];
		nextBlock[1]=nextBlock[2];
		nextBlock[2]=rand()%7;
		blockRotate=0;
		blockY=-1;
		blockX=WIDTH/2-2;

		recommend(recRoot);

		DrawNextBlock(nextBlock);
		PrintScore(score);
		DrawField();
		DrawBlockWithFeatures(blockY, blockX, nextBlock[0], blockRotate);
	}
	timed_out=0;
}

void BlockDown2(int sig){
	blockX=recommendX;
	blockY=recommendY;
	blockRotate=recommendR;
	recommendY=-1;

	if(blockY==-1) gameOver=1;
	score += AddBlockToField(field, nextBlock[0], blockRotate, blockY, blockX);
	score += DeleteLine(field);
	nextBlock[0]=nextBlock[1];
	nextBlock[1]=nextBlock[2];
	nextBlock[2]=rand()%7;
	blockRotate=0;
	blockY=-1;
	blockX=WIDTH/2-2;

	recommend(recRoot);

	DrawNextBlock(nextBlock);
	PrintScore(score);
	DrawField();
	DrawBlockWithFeatures(blockY,blockX,nextBlock[0],blockRotate);

	timed_out=0;

}

int AddBlockToField(char f[HEIGHT][WIDTH],int currentBlock,int blockRotate, int blockY, int blockX){

	int i, j;
	int touched=0;

	for(i=0; i<4; i++){
		for(j=0; j<4; j++){
			if(block[currentBlock][blockRotate][i][j]==1){
				if(f[blockY+1+i][blockX+j] || (blockY+1+i)>=HEIGHT)
					touched++;

				f[blockY+i][blockX+j] = 1;
			}
		}
	}

	return (touched*10);
}

int DeleteLine(char f[HEIGHT][WIDTH]){
	
	int flag=0;
	int i, j, num=0;
	int a, b;

	for(i=HEIGHT-1; i>=0; i--){
		flag=0;
		for(j=0; j<WIDTH; j++){
			if(f[i][j]==1)
				flag++;
		}
		if(flag==WIDTH){
			for(b=0;b<WIDTH;b++)
				f[a][b]=0;
			num++;
			for(a=i; a>0; a--){
				for(b=0; b<WIDTH; b++){
					f[a][b]= f[a-1][b];
				}
			}
			i++;
		}

	}
	
	return (num*num*100);

}

void DrawShadow(int y, int x, int blockID,int blockRotate){
	

	while(CheckToMove(field, blockID, blockRotate, y+1, x))
		y++;

	DrawBlock(y, x, blockID, blockRotate, '/');

}

void createRankList(){

	int i;
	FILE*fp=fopen("rank.txt", "r");

	fscanf(fp,"%d", &ranknum);
	
	for(i=0; i<ranknum; i++){
		fscanf(fp, "%s %d", RankList[i].name, &RankList[i].score);
	}
	fclose(fp);
}

void rank(){
	char name[NAMELEN];
	int del, i;
	int j,ch,strl;
	clear();
	printw("1. list ranks from X to Y\n");
	printw("2. list ranks by a specific name\n");
	printw("3. delete a specific rank\n");
	switch(wgetch(stdscr)){
	case'1':
		echo();
		printw("X: ");
		scanw("%d", &from);
		printw("Y: ");
		scanw("%d", &to);
		noecho();
		printw("	name	   |    score   \n");
		printw("--------------------------------\n");
		if(from==0 || from<0 || from>ranknum)
			from=1;
		if(to==0||to>ranknum) to=ranknum;
		if(from>to)
			printw("search failure: no rank in the list\n");
		else{
			for(i=from-1; i<to; i++){
				printw("%s\t\t|", RankList[i].name);
				printw("  %d\n", RankList[i].score);
			}
		}
		from =0;
		to=0;
		break;
	case '2':
		echo();
		printw("Input the name: ");
		scanw("%s", name);
		noecho();
		printw("	name	  |	score   \n");
		printw("--------------------------------\n");
		ch=1;
		for(i=0; i<ranknum; i++){
			strl=strlen(RankList[i].name);
			if(strl!=strlen(name))continue;
			for(j=0;j<strl;j++){
				if(RankList[i].name[j]!=name[j]){
					break;
				}
			}
			if(j==strl){
				printw("%s\t\t|", RankList[i].name);
				printw("  %d\n", RankList[i].score);
				ch=0;
			}
		}
		if(ch==1)printw("search failure: no name in the list\n");
		break;
	case '3':
		echo();
		printw("input the rank: ");
		scanw("%d",&del);
		noecho();
		if(0<del && del<=ranknum){
			del--;
			for(i=del;i<ranknum-1;i++){
				RankList[i]=RankList[i+1];
			}
			writeRankFile();
			printw("result: the rank deleted\n");
		}

		else
			printw("search failure: the rank not in the list\n");
		break;
	default: break;
	}

	getch();
}

void writeRankFile(){
	
	FILE*fp=fopen("rank.txt", "w");
	int i;

	fprintf(fp, "%d\n", ranknum);
	for(i=0; i<ranknum; i++){
		fprintf(fp, "%s", RankList[i].name);
	       	fprintf(fp, " %d\n", RankList[i].score);
	}
	fclose(fp);
}

void newRank(int score){

	clear();
	echo();
	printw("your name: ");
	scanw("%s", RankList[ranknum].name);
	noecho();
	RankList[ranknum].score=score;
	quick_sort(RankList, 0, ranknum);
	ranknum++;
	writeRankFile();

}

void quick_sort(Node RankList[], int left, int right){

	int i=left, j=right, key;
       	Node temp;

	key=RankList[(left+right)/2].score;
	while(i<=j){
		while(RankList[i].score>key){
			i++;
		}
		while(RankList[j].score<key){
			j--;
		}
		if(i<=j){
			temp=RankList[i];
			RankList[i] = RankList[j];
			RankList[j] = temp;
			i++;
			j--;
		}
	}
	if(left<j)
		quick_sort(RankList, left, j);
	if(i<right)
		quick_sort(RankList, i, right);

}

void DrawRecommend(){
	if(CheckToMove(field, nextBlock[0], recommendR, recommendY, recommendX)==1){
		DrawBlock(recommendY, recommendX, nextBlock[0], recommendR, 'R');
	}
}

int evalState(int lv, char f[HEIGHT][WIDTH], int r, int y, int x){
	return AddBlockToField(f, nextBlock[lv], r, y, x)+DeleteLine(f);
}


int recommend(RecNode *root){
	int r, x, y, rBoundary, lBoundary;
	int h, w;
	int eval;
	int max=0;
	int solR, solY, solX;
	int recommended=0;
	int i=0;
	int lv=root->lv+1;
	RecNode **c=root->c;
	
	for(r=0; r<4; r++){
		lBoundary=3;
		for(h=0; h<BLOCK_HEIGHT; ++h){
			for(w=0; w<BLOCK_WIDTH; ++w){
				if(block[nextBlock[lv]][r][h][w]){
					break;
				}
			}
			if(w<lBoundary){
				lBoundary=w;
			}
		}


		lBoundary=0-lBoundary;

		rBoundary=0;
		for(h=0; h<BLOCK_HEIGHT; h++){
			for(w=BLOCK_WIDTH-1; w>=0; w--){
				if(block[nextBlock[lv]][r][h][w]){
					break;
				}
			}
			if(w>rBoundary){
				rBoundary=w;
			}
		}
		rBoundary=WIDTH-1-rBoundary;

		for(x=lBoundary; x<=rBoundary; x++, i++){
			for(h=0; h<HEIGHT; h++){
				for(w=0; w<WIDTH; w++){
					c[i]->f[h][w]=root->f[h][w];
				}
			}

			y=0;
			if(CheckToMove(c[i]->f, nextBlock[lv], r, y, x)){
				while(CheckToMove(c[i]->f, nextBlock[lv], r, ++y, x));
				--y;
			}
			else{
				return max;
			}

			c[i]->score=root->score+evalState(lv,c[i]->f, r, y, x);

			if(lv<VISIBLE_BLOCKS-1){
				eval=recommend(c[i]);
			}
			else{
				eval=c[i]->score;
			}
			if(max<eval){
				recommended=1;
				max=eval;
				solR=r;
				solY=y;
				solX=x;
			}
		}
	}
	if(lv==0 && recommended){
		recommendR=solR;
		recommendY=solY;
		recommendX=solX;
	}
	return max;
}


void recommendedPlay(){
	int command;
	int drawFlag=0;
	int y;
	clear();
	act.sa_handler=BlockDown;
	sigaction(SIGALRM,&act,&oact);
	InitTetris();
	do{
		if(timed_out==0){
			alarm(1);
			timed_out=1;
		}
		if(blockRotate!=recommendR){
			if((drawFlag=CheckToMove(field,nextBlock[0],(blockRotate+1)%4,blockY,blockX)))
				blockRotate =(blockRotate+1)%4;
			command=KEY_UP;
			}
		else if(blockX>recommendX){
			if((drawFlag=CheckToMove(field,nextBlock[0],blockRotate,blockY,blockX-1)))
				blockX--;
			command=KEY_LEFT;
		}
		else if(blockX<recommendX){
			if((drawFlag=CheckToMove(field,nextBlock[0],blockRotate,blockY,blockX+1)))
				blockX++;
			command=KEY_RIGHT;
		}
		else if(blockY<recommendY){
			if((drawFlag=CheckToMove(field,nextBlock[0],blockRotate,blockY+1,blockX)))
				//blockY++;
			command = KEY_LEFT;
		}
		if(drawFlag)DrawChange(field,command,nextBlock[0],blockRotate,blockY,blockX);
		drawFlag=0;

		command=GetCommand();
		if(ProcessCommand(command)==QUIT){
			alarm(0);
			DrawBox(HEIGHT/2-1,WIDTH/2-5,1,10);
			move(HEIGHT/2,WIDTH/2-4);
			printw("Good-bye!!");
			refresh();
			getch();

			return ;
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

void DrawBlockWithFeatures(int y, int x, int blockID, int blockRotate){
	DrawRecommend();
	DrawShadow(blockY, blockX, blockID, blockRotate);
	DrawBlock(blockY, blockX, blockID, blockRotate, ' ');
}
