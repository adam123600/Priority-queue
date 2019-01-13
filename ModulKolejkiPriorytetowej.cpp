// ModulKolejkiPriorytetowej.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "pq.h"

// plik naglowkoy z funkcjami publicznymi
// pq.h
// pq.cpp

#define SIZE 11

int main()
{
	
	PQueue* pQueue = NULL;
	if( !(pQueue = PQInit( SIZE )) )
	{
		perror( "ERROR, MEMORY ALLOCATION, pQueue main.cpp" );
		return 0;
	}
	srand( (unsigned)time( NULL ) );

	printf( "SIZE OF QUEUE: %d\n\n", SIZE );

	for( int i = 0; i < SIZE; i++ )
	{
		int nPrior = rand() % 10;
		int nKey = rand() % 30;
		PQEnqueue( pQueue, nKey, nPrior );
	}

	printf( "NEW QUEUE:\n" );
	PQPrint( pQueue );
	printf( "\n\n" );


	// sciagniecie 5 elementow
	printf( "DEQUEUE 5 ELEMENTS:\n" );
	for( int i = 0; i < 5; i++ )
		printf( "%d\n", PQDequeue( pQueue ) );

	printf( "\n\nQUEUE WITHOUT 5 ELEMENTS:\n" );
	PQPrint( pQueue );

	// wrucenie elementow
	printf( "\n\nENQUEUE 10 ELEMENTS: \n" );
	for( int i = 0; i < 10; i++ )
	{
		int nKey = rand() % 30;
		int nPrior = rand() % 10;
		PQEnqueue( pQueue, nKey, nPrior );
		printf( "KEY: %d\tPRIOR: %d\n", nKey, nPrior );
	}

	
	printf( "\n\nQUEUE + ENQUEUE 9 ELEMENTS (MAX ELEMENTS: %d):\n", SIZE );
	PQPrint( pQueue );

	printf( "\n\nDEQUEUE WHOLE QUEUE:\n" );
	while( !PQisEmpty( pQueue ) )
		printf( "%d\n", PQDequeue( pQueue ) );

	// sciagniecie z pustej
	printf( "\n\nDEQUEUE 2 ELEMENTS FROM EMPTY QUEUE:\n" );
	for( int i = 0; i < 2; i++ )
		printf( "%d\n", PQDequeue( pQueue ) );

	PQRelease( &pQueue ); // usuniecie kolejki
	printf( "\n\n" );
	return 0;
}

