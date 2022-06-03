#ifndef freeHeader
#define freeHeader
#include "mainHeader.h"
void freeMPIList(Musician** MusiciansGroup, int musiciansGroupSize);
void freeMusiciansGroup(Musician** MusiciansGroup, int musicianGroupSize);
void freeMusiciansCollection(Musician*** MusiciansCollection, int* instrumentCount, int musiciansCollectionSize);
void freeConcert(Concert* concert);
void freeInstrumentTree(InstrumentTree* tree);
void freeInstrumentTreeHelper(TreeNode* root);





#endif