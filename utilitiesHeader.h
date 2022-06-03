#ifndef utilitiesHeader
#define utilitiesHeader
#include "mainHeader.h"

float convertToFloat(char* str);
void checkMemoryAllocation(void* ptr);
void checkFileOpening(FILE* fp);
long int fileSize(FILE* fp);
void removeEnter(char* line, int size);
int convertToInt(char* str);
float hourToFloat(char* str);



#endif