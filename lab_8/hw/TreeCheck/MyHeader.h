#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>

#define NODE_MAX_NUM 100

typedef struct PAIRS_{
	int x;
	int y;
}PAIRS;

typedef struct CASES_{
	int Pnum;
	PAIRS *p;
}CASES;

CASES *testCases;
int testCaseNum=0;
int currentCase=-1;
int non_tree_flag=0;
char *resultString;

bool dfs ( int P[], int flag[], int c){
  flag[c] = 1;
  if ( P[c] == 0 ) 
    return false;	 // no cycle
  else if ( flag[P[c]] == 1 )
    return true;	 // cycle detected
  else
    return dfs(P, flag, P[c]);
}

bool Cycle_Check ( int P[] ) {
  int flag[NODE_MAX_NUM], i, j;
  for(j = 0; j < NODE_MAX_NUM; j++){
    if (P[j] <= 0 )
      continue;
    for(i = 0; i < NODE_MAX_NUM; i++)
      flag[i] = -1;
    if ( dfs ( P, flag, j ) == true )
      return true; // a cycle exists
  }
  return false;	// no cycle
}

void F1(){ //전역변수초기화
	testCaseNum=0;
	currentCase=-1;
	resultString=(char *)calloc(100,sizeof(char));
	non_tree_flag=0;
}

void F2(const char *filename){ //파일읽기
	FILE *fp;
	int i, j, a, b;

	fp=fopen(filename,"r");
	fscanf(fp,"%d",&testCaseNum);
	testCases=(CASES *)calloc(testCaseNum,sizeof(CASES));
	for (i=0; i<testCaseNum; i++){
		fscanf(fp,"%d",&testCases[i].Pnum);
		testCases[i].p=(PAIRS *)calloc(testCases[i].Pnum,sizeof(PAIRS));
		for (j=0; j<testCases[i].Pnum; j++){	
			fscanf(fp,"%d %d  ",&a,&b);
			testCases[i].p[j].x=a;
			testCases[i].p[j].y=b;
		}
	}
	fclose(fp);
}

char* F3(int number){ //트리체크
	int P[NODE_MAX_NUM];
	int i, flag=0;
//	P=(int *)calloc(testCases[number].Pnum,sizeof(int));
	//for (i=0; i<testCases[number].Pnum; i++)
		//P[i]=-1;
	for (i=0; i<NODE_MAX_NUM; i++)
		P[i]=-1;
	sprintf(resultString,"Case %d is not a tree.\0",number+1);
	for (i=0; i<testCases[number].Pnum; i++){
		if (P[testCases[number].p[i].x]==-1)
			P[testCases[number].p[i].x]=0;
		if (P[testCases[number].p[i].y]<=0)
			P[testCases[number].p[i].y]=testCases[number].p[i].x;
		else{
			non_tree_flag=1;
			return resultString;
		}
	}
	for(i=0; i<testCases[number].Pnum; i++){
		if (P[i]==0 && flag==1){
			non_tree_flag=1;
			return resultString;
		}
		if (P[i]==0)	flag=1;
	}
	if(Cycle_Check(P)==true){
		non_tree_flag=1;
		return resultString;
	}
	if (non_tree_flag==0){
		sprintf(resultString,"Case %d is a tree.\0",number+1);
		return resultString;
	}
}