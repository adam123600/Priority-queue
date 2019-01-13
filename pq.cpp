#include "pq.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// przywracanie kopca
void UpdateDown( PQueue* pQueue, int l, int p );
void UpdateUp( PQueue* pQueue, int l, int p );


PQueue* PQInit( int nSize )
{

	// tworzy kolejke o podanym rozmiarze 

	PQueue* pQueue = (PQueue*)calloc( 1, sizeof( PQueue ) );
	if( !pQueue )
	{
		perror( "ERROR MEMORY ALLOCATION, PQinit pq.cpp" );
		return 0;
	}

//	pQueue->PQCurrSize = 0;
	pQueue->PQSize = nSize;
	pQueue->pQueueArray = (PQItem*)calloc( nSize, sizeof( PQItem ) );

	if( !pQueue->pQueueArray )
	{
		perror( "ERROR, MEMORY ALLOCATION, PQInit pq.cpp" );
		return 0;
	}

	return pQueue;
}

int PQisEmpty( PQueue* pQueue )
{
	return !pQueue->PQCurrSize;
}


void PQEnqueue( PQueue* pQueue, int nKey, int nPrior )
{
	// sprawdzic czy pelna

	if( pQueue->PQCurrSize == pQueue->PQSize )
	{
		perror( "QUEUE IS FULL, PQEnqueue pq.cpp" );
		return;
	}

	// wklada do kolejki priorytetowej element o kluczy nKey i priorytecie nPrior
	// wstawia na koncu

	pQueue->pQueueArray[pQueue->PQCurrSize].nKey = nKey;
	pQueue->pQueueArray[pQueue->PQCurrSize].nPrior = nPrior;

	// uaktualnienie w gore

	UpdateUp( pQueue, 0, pQueue->PQCurrSize++ );

}


int PQDequeue( PQueue* pQueue )
{
	// wyciaga pierwszy element z kolejki ( czyli o najwiekszym priorytecie );

	// sprawdzenie czy pusta
	if( PQisEmpty( pQueue ) )
	{
		printf( "QUEUE IS EMPTY, PQDequeue" );
		return 0;
	}

	// wyjac element z indexu 0 ( pierwszy element )
	int result = pQueue->pQueueArray[0].nKey;
	

	// wrzucic ostatni element na zerowy 
	pQueue->pQueueArray[0].nKey = pQueue->pQueueArray[pQueue->PQCurrSize - 1].nKey;
	pQueue->pQueueArray[0].nPrior = pQueue->pQueueArray[pQueue->PQCurrSize - 1].nPrior;


	// update w dol
	UpdateDown( pQueue, 0, --pQueue->PQCurrSize ); 
	
	return result;

}

void PQClearQueue( PQueue* pQueue )
{
	// ma wyczyscic kolejke
	// cala kolejka zostaje tylko jest wyczyszczona

	memset( pQueue->pQueueArray, 0, pQueue->PQSize * sizeof( PQItem ) );
	pQueue->PQCurrSize = 0;
}

void PQRelease( PQueue** pQueue )
{
	// zwraca w parametrze we/wy NULL
	// calkowicie usuwa kolejke // parametr przeakzany przez adres
	// po zwolnieniu wszystkiego wrzuca NULL do wskaznika

	free( ( *pQueue )->pQueueArray );
	free( *pQueue  );
	*pQueue = NULL;
}

void PQPrint( PQueue* pQueue)
{
	// printowanie // moze byc na warnukowej kompilacji

	if( PQisEmpty( pQueue ) )
	{
		printf( "QUEUE IS EMPTY!" );
		return;
	}

	for( int i = 0; i < pQueue->PQCurrSize; i++ )
		printf( "KEY: %d\t\tPRIOR: %d\n", pQueue->pQueueArray[i].nKey, pQueue->pQueueArray[i].nPrior );
	
}


void UpdateDown( PQueue* pQueue, int l, int p )
{
	// analogicznie jak w sorotowaniu stogowym
	// sprawdzic czy nie trzeba zmienic warunkow

	if( l == p ) return;
	int i = l;
	int j = 2 * i + 1;
	PQItem temp = pQueue->pQueueArray[i];

	while( j <= p )
	{
		if( j < p )
			if( pQueue->pQueueArray[j].nPrior < pQueue->pQueueArray[j + 1].nPrior )
				j++;

		if( pQueue->pQueueArray[i].nPrior < temp.nPrior ) break;

		pQueue->pQueueArray[i] = pQueue->pQueueArray[j];
		i = j;
		j = 2 * i + 1;
	}
	pQueue->pQueueArray[i] = temp;
}

void UpdateUp( PQueue* pQueue, int l, int p )
{
	int i = p;
	int j = ( i - 1 ) / 2;

	PQItem temp = pQueue->pQueueArray[i];

	while( i > 0 && pQueue->pQueueArray[j].nPrior < temp.nPrior )
	{
		pQueue->pQueueArray[i] = pQueue->pQueueArray[j];
		i = j;
		j = ( i - 1 ) / 2;
	}

	pQueue->pQueueArray[i] = temp;
}



void DecreaseKey( PQueue* pQueue, int nKey, int nPrior)
{
	  // ( nPrior < Item.nPrior );
	  // dostanie kolejke klucz i priorytet
	  // wyszukam element o zadanym kluczu i zakladam ze parametr jest silnie mniejszy od priorytetu
	  // jesli tak nie jest to nic nie robie
	
	if( nPrior < pQueue->pQueueArray[nKey].nPrior )
	{
		pQueue->pQueueArray[nKey].nPrior = nPrior;
		UpdateDown( pQueue, nKey, pQueue->PQCurrSize - 1 );
	}
	
}


void IncreaseKey( PQueue* pQueue, int nKey, int nPrior )
{
	// (nPrior > Item.Prior);
	// jesli nie zachowayn warunek z prawej strony to nic nie robie
	// jak warunek sie zgadza to zwiekszyc klucz

	if( nPrior > pQueue->pQueueArray[nKey].nPrior )
	{
		pQueue->pQueueArray[nKey].nPrior = nPrior;
		UpdateUp( pQueue, 0, nKey );
	}

}

