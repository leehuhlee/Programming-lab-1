#include "Header.h"

int main ( ) {
	int test, number, numbercount [ 10 ] = { 0 } ;
	int i ;
	scanf ( "%d" , &test ) ;
	for ( i = 0 ; i < test ; i++) {
		scanf ( "%d" , &number ) ;
		count ( number, numbercount ) ;
		print ( numbercount ) ;
	}
	return 0;
}
