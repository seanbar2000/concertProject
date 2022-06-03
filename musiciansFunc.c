#include "musiciansHeader.h"
#include "freeHeader.h"
#include "InstrumentsHeader.h"
#include "utilitiesHeader.h"

// creates an array that holds in each cell an array of musician pointers
// every index represents an instrument id
// every array of musician pointers holds all the musicians that play that instrument
Musician*** createMusiciansCollection(Musician** MusiciansGroup, int musiciansGroupSize, InstrumentTree* tree, int** instrumentsCountP, int* musiciansCollectionSize)
{
	int size, i;
	Musician*** MusiciansCollection;
	int* instrumentCount; // holds the sizes of every array of musician pointers
	int sizeOfInstrument;


	size = countInstruments(tree);

	instrumentCount = (int*)malloc(sizeof(int) * size);
	checkMemoryAllocation(instrumentCount);

	MusiciansCollection = (Musician***)malloc(sizeof(Musician**) * size);
	checkMemoryAllocation(MusiciansCollection);


	for (i = 0; i < size; i++) 
	{
		MusiciansCollection[i] = (Musician**)malloc(sizeof(Musician*));
		checkMemoryAllocation(MusiciansCollection[i]);
		MusiciansCollection[i] = addMusicians(MusiciansCollection[i], MusiciansGroup, musiciansGroupSize, i + 1, &sizeOfInstrument);
		instrumentCount[i] = sizeOfInstrument;
	}

	*instrumentsCountP = instrumentCount;
	*musiciansCollectionSize = size;

	return MusiciansCollection;
}

// adds musicians who play the instrument that has insId to dest from src
// returns an array of musician pointers and its size
Musician** addMusicians(Musician** dest, Musician** src, int musiciansGroupSize, int insId, int* resSize)
{
	int i, logSize, phySize;
	ListNode* curr;

	i = logSize = 0;
	phySize = 1;

	for (i = 0; i < musiciansGroupSize; i++)
	{
		curr = src[i]->instruments.head;
		while (curr != NULL)
		{
			if (logSize == phySize)
			{
				phySize *= 2;
				dest = (Musician**)realloc(dest, sizeof(Musician*) * phySize);
				checkMemoryAllocation(dest);
			}

			if (curr->data.insId == insId)
			{
				dest[logSize] = src[i];
				logSize++;
			}

			curr = curr->next;
		}
	}
	*resSize = logSize;
	return dest;
}

// reads the data from the musician file and inputs it into a two dimensional array of musicians
// the function returns the two dimensional array of musicians a musician pointer
Musician** readMusiciansFile(char* fileName, InstrumentTree* tree, int* musiciansGroupSize) 
{
	FILE* musicians;
	Musician** MusiciansGroup;
	Musician* m;
	char line[LINE_SIZE];
	long int fsize;
	int phySize, logSize;


	musicians = fopen(fileName, "r");
	checkFileOpening(musicians);

	MusiciansGroup = (Musician**)malloc(sizeof(Musician*));
	checkMemoryAllocation(MusiciansGroup);
	fsize = fileSize(musicians);
	logSize = 0;
	phySize = 1;

	while (ftell(musicians) < fsize) 
	{
		fgets(line, LINE_SIZE, musicians);
		removeEnter(line, LINE_SIZE);
		m = readMusicanInfo(line, tree);
		MusiciansGroup = updateMusiciansArray(MusiciansGroup, m, &logSize, &phySize);

	}
	fclose(musicians);
	*musiciansGroupSize = logSize;
	return MusiciansGroup;
}

// recieves an array of musician pointers and updates its logical and physical size
Musician** updateMusiciansArray(Musician** MusiciansGroup, Musician* m, int* pLogSize, int* pPhySize) 
{
	int logSize, phySize;

	logSize = *pLogSize;
	phySize = *pPhySize;

	if (logSize == phySize) 
	{
		phySize *= 2;
		MusiciansGroup = (Musician**)realloc(MusiciansGroup, phySize * sizeof(Musician*));
		checkMemoryAllocation(MusiciansGroup);
	}
	MusiciansGroup[logSize] = m;
	logSize++;

	*pLogSize = logSize;
	*pPhySize = phySize;
	return MusiciansGroup;

}

// converts information from the info string and inputs it into a musician pointer
Musician* readMusicanInfo(char* info, InstrumentTree* tree)
{
	MusicianPriceInstrument instrument;
	Musician* m;
	char seps[SEPSIZE] = " ,.;:?!-\t'()[]{}<>~_;}";
	char* token;
	int logSize, phySize;

	token = strtok(info, seps);
	logSize = 0;
	phySize = 1;
	instrument.insId = 0;
	instrument.price = 0;

	m = (Musician*)malloc(sizeof(Musician));
	checkMemoryAllocation(m);

	m->name = (char**)malloc(sizeof(char*));
	checkMemoryAllocation(m->name);
	makeEmptyMPIList(&(m->instruments));

	while (token != NULL)
	{
		if (findInsId(tree, token) != -1) //checks if the token is in the instrument tree
		{
			instrument.insId = findInsId(tree, token);
		}
		else {
			if (token[0] >= '0' && token[0] <= '9') //checks if the token is a number
				instrument.price = convertToFloat(token);
			else
				m->name = readName(m->name, token, &logSize, &phySize);


			// adds the instrument information to the list of musician price
			if (instrument.insId != 0 && instrument.price != 0) 
			{
				insertDatataToEndMPList(&(m->instruments), instrument, NULL);
				instrument.insId = 0;
				instrument.price = 0;

			}
		}
		token = strtok(NULL, seps);
	}

	m->available = true;
	m->sizeOfName = logSize;
	return m;
}

// recieves a string array, its physical and logical size and a string
char** readName(char** names, char* str, int* pLogSize, int* pPhySize) 
{
	int phySize;
	int logSize;

	phySize = *pPhySize;
	logSize = *pLogSize;


	if (logSize == phySize) 
	{
		phySize *= 2;
		names = (char**)realloc(names, phySize * sizeof(char*));
		checkMemoryAllocation(names);
	}

	names[logSize] = (char*)malloc(LINE_SIZE * sizeof(char));
	checkMemoryAllocation(names[logSize]);
	strcpy(names[logSize], str);
	logSize++;


	*pPhySize = phySize;
	*pLogSize = logSize;
	return names;
}

// initializes the musician price list
void makeEmptyMPIList(MPIList* m)
{
	m->head = m->tail = NULL;
}

// inputs the data into the end of the musician price instrument list
void insertDatataToEndMPList(MPIList* lst, MusicianPriceInstrument data, ListNode* next)
{
	ListNode* newTail;
	newTail = createNewMPIListNode(data, NULL);
	insertMPINodeToEndList(lst, newTail);

}

// creates a new MPIList and inputs data into it
ListNode* createNewMPIListNode(MusicianPriceInstrument data, ListNode* next) 
{
	ListNode* res = (ListNode*)malloc(sizeof(ListNode));
	checkMemoryAllocation(res);
	res->data = data;
	res->next = next;

	return res;
}

// inserts a node to the end of the list
void insertMPINodeToEndList(MPIList* lst, ListNode* tail) 
{
	if (isEmptyList(lst))
		lst->head = lst->tail = tail;
	else {
		lst->tail->next = tail;
		lst->tail = tail;
	}
	tail->next = NULL;
}

// checks if the MPIList is empty
bool isEmptyList(MPIList* lst) 
{
	if (lst->head == NULL)
		return true;
	return false;
}

// resets the musicians availability int the array
void resetAvailability(Musician** MusiciansGroup, int musicianGroupSize) 
{
	int i;
	for (i = 0; i < musicianGroupSize; i++)
		MusiciansGroup[i]->available = true;
}

