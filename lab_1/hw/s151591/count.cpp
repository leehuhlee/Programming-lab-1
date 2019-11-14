#include "Header.h"

void count ( int number, int *numbercount ) {
	int numbertemp = number ;
	int numpart[ 1000 ] ;
	int len = 0 ;
	int ten ;
	int i, j, end ;
	
	while ( 1 ) {
		numpart[ len ] = numbertemp % 10 ;
		numbertemp /= 10 ;
		if ( numbertemp == 0 ) break ;
		len++ ;
	}
	ten = tencount ( len ) ;
	for ( i = len ; i > 0 ; i-- ) {
		number = number - ( numpart[ i ] * tencount ( i ));
		numbercount[ numpart[ i ] ] = numbercount[ numpart[ i ] ] + number + 1 ;
		ten = tencount ( i - 1 ) ;
		for ( j = 0 ; j < 10 ; j++ ) {
			numbercount[ j ] = numbercount[ j ] + ( ten * i ) * numpart[ i ];
		}
		ten = tencount ( i ) ;
		if ( i == len) end = 1 ;
		else end = 0 ;
		for ( j = numpart[ i ] - 1 ; j >= end ; j-- ) {
			numbercount[ j ] += ten ;
		}
	}
	for ( i = len - 1 ; i >= 0 ; i-- ) {
		numbercount[ 0 ] -= tencount ( i ) ;
	}
	if ( len > 0 ) end = 0;
	else end = 1;
	for ( i = end ; i <= numpart [ 0 ] ; i++) numbercount[ i ]++;
}

int tencount ( int len ) {
	int i, result = 1;
	for ( i = 0 ; i < len ; i++ ) result *= 10 ;
	return result;
}
