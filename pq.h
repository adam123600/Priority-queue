#pragma once


typedef struct 
{
	int nKey;
	int nPrior;
}PQItem;

typedef struct
{
	PQItem* pQueueArray; // kolejka w postaci stogu
	int PQSize; // calkowity rozmiar kolejki
	int PQCurrSize; // obecny rozmiar kolejki


	// tablica ktora bedzie inicjowana przez osobna funkcje
	// pQueue // kolejka realizowana w postaciu stogu
	// musi byc pamietany calkowity rozmiar kolejki priorytetowej
	// int // pQSize // rozmiar kolejki priorytetowej
	// PQCurrSize // ilosc elementow w kolejce
	// aktualny rozmiar ( aktualan ilosc  elementow ) tej kolejki 
	// PQCurrSize to jednoczesnie jest index gdzie moge wstawic element // pod ten index wstawiam nowy element i podnosze index PQCurrSize
	// PQCurrSize musi byc mniejsze od calkowitego rozmiaru kolejki bo nie bedzie juz mozna wstawiac 
	// po wstawieniu elementu nalezy uaktualnic kopiec ( stog ) od dolu do gory
	// jak sciagamy to sciagamy element zerowy, ostatni przerzucamy na zerowy i uaktualniamy stog od gory do dolu // jak zostanie jeden element
	// to nie ma co uaktualniac
}PQueue;

// bedzie uaktualnianie stogu od gory i od dolu- funkcja update z sortowan gotowa 


PQueue* PQInit( int nSize ); // okresla maksymalny rozmiar kolejki, ma stworzyc ta kolejke
// tworzy strukture dynamicznie
// dla pQueue przydziela pamiec dynamicznie z parametru int
// ustawia PQSize przekazanym intem
// ustawia aktualny licznik elementow na zero
// mozna juz uzywac calloca
// sprawdzic trzeba czy sie udalo zaalokowac pamiec

int PQisEmpty( PQueue* pQueue);
// funkcja zwraca wartosc 0 lub 1
// jak jest pusta to zwraca 1
// jak nie pusta to zwraca 0
// czyli zaprzeczenie PQCurrSize;
// tak jak w stosie

void PQEnqueue( PQueue* pQueue, int nKey, int nPrior );
// wklada do kolejki priorytetowej element o kluczy nKey i priorytecie nPrior
//

int PQDequeue( PQueue* pQueue );
// wyciaga pierwszy element z kolejki ( czyli o najwiekszym priorytecie );

void PQClearQueue( PQueue* pQueue);
// ma wyczyscic kolejke
// cala kolejka zostaje tylko jest wyczyszczona

void PQRelease( PQueue** pQueue ); // zwraca w parametrze we/wy NULL
// calkowicie usuwa kolejke // parametr przeakzany przez adres
// po zwolnieniu wszystkiego wrzuca NULL do wskaznika

void PQPrint( PQueue* pQueue); // inorder
// printowanie // moze byc na warnukowej kompilacji
// drukowanie inorder

void DecreaseKey( PQueue* pQueue, int nKey, int nPrior ); // ( nPrior < Item.nPrior );
// dostanie kolejke klucz i priorytet
// wyszukam element o zadanym kluczu i zakladam ze parametr jest silnie mniejszy od priorytetu
// jesli tak nie jest to nic nie robie


void IncreaseKey( PQueue* pQueue, int nKey, int nPrior ); // (nPrior > Item.Prior);
// jesli nie zachowayn warunek z prawej strony to nic nie robie
// jak warunek sie zgadza to zwiekszyc klucz


//TESTY
// Queue q;
// int* q = INITQUE;
//
// wygenerowac przynajmniej 10 elementow losowo
// mozna napisac funkcje ktora generuje losowo elementy ( elementow )
// 

// wsadzic 10 elementow do kolejki
// kolejke zrobic na 11 elementow
// raz dequee
// dwa razy enqueue
// raz eenquee
// dwa razy 
// czyszczenie
// 2 razy en
// 3 razy de
// testowac co sie dzieje w skrajnych przypadkach czy dobrze dziala
// za kazdym razem drukowac kolejke aby widziec czy dobrze dziala
// 

// sam modul naistostniejszy
// program testowy do wytestowania skrajnych przypadkow czy dziala poprawnie kolejka