#ifndef musiciansHeader
#define musiciansHeader
#include "mainHeader.h"

Musician* readMusicanInfo(char* info, InstrumentTree* tree);
char** readName(char** names, char* str, int* pLogSize, int* pPhySize);
void makeEmptyMPIList(MPIList* m);
void insertDatataToEndMPList(MPIList* lst, MusicianPriceInstrument data, ListNode* next);
ListNode* createNewMPIListNode(MusicianPriceInstrument data, ListNode* next);
void insertMPINodeToEndList(MPIList* lst, ListNode* tail);
bool isEmptyList(MPIList* lst);
bool isEmptyCIList(CIList* lst);
Musician** updateMusiciansArray(Musician** MusiciansGroup, Musician* m, int* pLogSize, int* pPhySize);
Musician** readMusiciansFile(char* fileName, InstrumentTree* tree, int* musiciansGroupSize);
void resetAvailability(Musician** MusiciansGroup, int musicianGroupSize);
Musician** addMusicians(Musician** dest, Musician** src, int musiciansGroupSize, int insId, int* resSize);
Musician*** createMusiciansCollection(Musician** MusiciansGroup, int musiciansGroupSize, InstrumentTree* tree, int** instrumentsCountP, int* musiciansCollectionSize);
void resetAvailability(Musician** MusiciansGroup, int musicianGroupSize);







#endif