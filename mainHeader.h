#ifndef mainHeader
#define mainHeader

#define _CRT_SECURE_NO_WARNINGS
#define _CRTDBG_MAP_ALLOC
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <crtdbg.h>
#define LINE_SIZE 151
#define NOT_FOUND -1
#define SEPSIZE 23
#define HOUR_LENGTH 5

typedef struct date {
	int day, month, year;
	float hour;
}Date;

typedef struct CI {
	int num;
	int inst;
	char importance;
}ConcertInstrument;

typedef struct ciListNode {
	ConcertInstrument data;
	struct ciListNode* next;

}CIListNode;

typedef struct CIL
{
	CIListNode* head;
	CIListNode* tail;

}CIList;

typedef struct concert {
	Date date_of_concert;
	char* name;
	CIList instruments;
}Concert;

typedef struct treeNode {
	char* instrument;
	unsigned int insId;
	struct treeNode* left;
	struct treeNode* right;
}TreeNode;

typedef struct tree {
	TreeNode* root;
}InstrumentTree;

typedef struct musicianPriceInstrument
{
	unsigned short insId;
	float price;
}MusicianPriceInstrument;


typedef struct listNode {
	MusicianPriceInstrument data;
	struct listNode* next;
} ListNode;

typedef struct mpiList {
	ListNode* head;
	ListNode* tail;
} MPIList;

typedef struct musician
{
	char** name;
	int sizeOfName;
	bool available;
	MPIList instruments;

}Musician;

typedef struct currentInstrument {
	Musician* musician;
	int instrumentID;
	char importance;

}currentInstrument;

typedef struct MusicianCrew
{
	Musician* player;
	int instrument;
	float price;

}MusicianCrew;




#endif
