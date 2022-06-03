#ifndef InstrumentsHeader
#define InstrumentsHeader
#include "mainHeader.h"

void createInstrumentTree(InstrumentTree* t, char* str, int id);
TreeNode* createNewTreeNode(char* instrument, unsigned int insid, TreeNode* left, TreeNode* right);
void makeEmptyTree(InstrumentTree* tree);
int findInsId(InstrumentTree* tree, char* instrument);
int findInsIdHelper(TreeNode* root, char* instrument);
int countInstruments(InstrumentTree* tree);
int countInstrumentsHelper(TreeNode* root);
InstrumentTree readInstrumentsFile(char* fileName);






#endif