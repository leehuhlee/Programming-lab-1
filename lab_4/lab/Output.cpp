#include "Header.h"

void Print_Line( char *line, int *Count, int *B_Flag ) {
	int i, N_Blanks, N_Chars, Start=0;//1
	//Start를 0으로 초기화

	Get_Blanks_Chars( line, Start, &N_Blanks, &N_Chars );
	while ( N_Chars != 0 ) {
		if ( (*B_Flag == 1) && ((*Count + N_Chars + 1) <= LIMIT) ) {

			/* In this part, N_Blanks == 0 in order that L1 and L2 should be merged.
			* "N_Blanks != 0" means that L2 is written at the next line.
			*/
			if ( N_Blanks != 0 ) {
				printf("Something Wrong!\n");
				exit(-1);
			}

			putchar(' ');
			*B_Flag=0;//2
			for ( i = Start; i < Start + N_Chars; i++ ) {//3
				//i의 끝부분 수정
				putchar(line[i]);
			}
			Start = Start + N_Chars;
			*Count = *Count + N_Chars + 1;
			Get_Blanks_Chars( line, Start, &N_Blanks, &N_Chars );
		}
		else if ( (*Count + N_Blanks + N_Chars) <= LIMIT ) {
			for ( i = Start; i < Start + N_Blanks + N_Chars ; i++ ) {//4
				//i의 끝부분 수정
				putchar(line[i]);
			}
			Start = Start + N_Blanks + N_Chars;
			*Count = *Count + N_Blanks + N_Chars;
			Get_Blanks_Chars( line, Start, &N_Blanks, &N_Chars );
		}
		else {
			if ( *Count == 0 ) {
				for ( i = Start; i < Start + N_Blanks + N_Chars ; i++ ) {//5
					//i의 끝부분 수정
					putchar(line[i]);
				}
				Start = Start + N_Blanks + N_Chars;
				putchar('\n');
				Get_Blanks_Chars( line, Start, &N_Blanks, &N_Chars );
			}
			else {
				putchar('\n');
				*B_Flag = 0;
				for ( i = Start + N_Blanks; i < Start + N_Blanks + N_Chars; i++ ) {//6
					//i의 끝부분 수정
					putchar(line[i]);
				}
				Start = Start + N_Blanks + N_Chars;
				*Count = N_Chars;
				Get_Blanks_Chars( line, Start, &N_Blanks, &N_Chars );
			}
		}
	}
}
//6개 입니다.
