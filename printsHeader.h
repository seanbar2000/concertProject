#ifndef printsHeader
#define printsHeader
#include "mainHeader.h"

void printHour(float hour);
void printTotalPrice(MusicianCrew* musicians, int size);
void printMusicians(MusicianCrew* musicians, int size, InstrumentTree* tree);
void printNum(int num);
void printConcert(Concert concert, MusicianCrew* musicians, int size, InstrumentTree* tree);
void printMusicianName(char** name, int size);
void printInstrumentName(InstrumentTree* tree, int id);
void printInstrumentNameHelper(TreeNode* root, int id);







#endif