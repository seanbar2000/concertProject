#ifndef concertsHeader
#define concertsHeader
#include "mainHeader.h"

int arrangeCrew(MusicianCrew* dest, Musician** src, CIListNode* node, int* writeInd, int size);
bool isEmptyCIList(CIList* lst);
void getConcerts(Musician*** MusiciansCollection, int* instrumentCount, InstrumentTree* tree, Musician** MusiciansGroup, int musicianGroupSize);
char* getConcertString();
Concert getNewConcert(char* concertInfo, InstrumentTree* tree);
void makeEmptyCIList(CIList* instruments);
void insertDataToEndCIList(CIList* instruments, int instrumentID, int inst, char importance);
CIListNode* createNewCIListNode(int instrumentID, int inst, char importance, CIListNode* next);
void insertCILNodeToEndList(CIList* instruments, CIListNode* newTail);
void updateDate(int pos, char* token, Date* date);
void AssignConcert(Concert concert, Musician*** MusiciansCollection, int* instrumentCount, int musicianGroupSize, InstrumentTree* tree);
int compareInstrumentPrices(void* elem1, void* elem2);
void findPriceOfMusicians(MusicianCrew* musicians, int size);

#endif