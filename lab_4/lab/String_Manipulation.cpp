#include "Header.h"

void Remove_Blanks_At_The_End( char *line ) {
	int i, k, newline_flag;

	for ( k = 0; ; k++ ) {
		if ( line[k] == '\n' ) {
			newline_flag = 1;
			break;
		}
		else if ( line[k] == '\0' ) {
			break;
		}
	}
	for ( i = k-1; i >= 0; i-- ) {//1
		//i 시작 부분을 변경(변경전에 한 문자씩 짤림)
		if ( line[i] != ' ' ) {
			break;
		}
	}
	i++;//2
	//추가
	if ( newline_flag == 1 ) {
		line[i] = '\n';
		line[i+1] = '\0';
	}
	else {
		line[i] = '\0';
	}
}

void Get_Blanks_Chars( char *line, int Start, int *N_Blanks, int *N_Chars ) {
	int i, blank_flag=0;//3
	*N_Chars=0;//4
	*N_Blanks=0;//5
	//초기화 수정

	for ( i = Start; ; i++ ) {
		if ( (line[i] == '\n') || (line[i] == '\0') ) {
			break;
		}
		else if ( line[i] == ' ' ) {
			if ( blank_flag == 0 ) {
				++(*N_Blanks);
			}
			else {
				break;
			}
		}
		else {
			blank_flag = 1;
			++(*N_Chars);
		}
	}
}
//총 5개 입니다.
