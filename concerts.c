#include "concertsHeader.h"
#include "musiciansHeader.h"
#include "utilitiesHeader.h"
#include "printsHeader.h"
#include "InstrumentsHeader.h"

// checks if the concert instrument list is empty
bool isEmptyCIList(CIList* lst) 
{
	if (lst->head == NULL)
		return true;
	return false;
}

// recieves concert information from the user and arranges a new concert if possible
void getConcerts(Musician*** MusiciansCollection, int* instrumentCount, InstrumentTree* tree, Musician** MusiciansGroup, int musicianGroupSize)
{
	Concert concert;
	char* concertStr;

	concertStr = getConcertString();

	while (concertStr[0] != '\0') {
		concert = getNewConcert(concertStr, tree);
		AssignConcert(concert, MusiciansCollection, instrumentCount, musicianGroupSize, tree);
		resetAvailability(MusiciansGroup, musicianGroupSize);
		freeConcert(&concert);
		free(concertStr);
		concertStr = getConcertString();
	}

	free(concertStr);

}

// assigns a new concert if possible
void AssignConcert(Concert concert, Musician*** MusiciansCollection, int* instrumentCount, int musicianGroupSize, InstrumentTree* tree) {
	CIListNode* curr;  // instruments needed for the concert
	currentInstrument* tmp;  // temporary holds musicians that play the same instrument
	int i, writeInd, count;	 // count - the number of the same instrument needed in the concert
	MusicianCrew* musiciansCrew;  // holds the musicians concert crew
	bool end;

	end = false;
	writeInd = count = 0;
	curr = concert.instruments.head;

	musiciansCrew = (MusicianCrew*)malloc(sizeof(MusicianCrew) * musicianGroupSize);
	checkMemoryAllocation(musiciansCrew);

	while (curr != NULL && !end) 
	{
		tmp = (currentInstrument*)malloc(sizeof(currentInstrument) * instrumentCount[curr->data.inst - 1]);
		checkMemoryAllocation(tmp);

		// adds to tmp the musicians that play the current instrument
		for (i = 0; i < instrumentCount[curr->data.inst - 1]; i++) 
		{
			tmp[i].instrumentID = curr->data.inst;
			tmp[i].importance = curr->data.importance;
			tmp[i].musician = MusiciansCollection[curr->data.inst - 1][i];
		}

		//sorting by importance
		qsort(tmp, instrumentCount[curr->data.inst - 1], sizeof(currentInstrument), compareInstrumentPrices);
		
		// returning the sorted musicians to the musiciansCollection array
		for (i = 0; i < instrumentCount[curr->data.inst - 1]; i++)
			MusiciansCollection[curr->data.inst - 1][i] = tmp[i].musician;

		// checks if the number of current concert instrument is greater than the number of musicians playing it
		if (instrumentCount[curr->data.inst - 1] < curr->data.num) 
		{
			printf("Couldn't find musicians for the concert %s.\n", concert.name);
			end = true;
		}
		else
		{
			count = arrangeCrew(musiciansCrew, MusiciansCollection[curr->data.inst - 1], curr, &writeInd, instrumentCount[curr->data.inst - 1]);
			if (count) {
				printf("Couldn't find musicians for the concert %s.\n", concert.name);
				end = true;
			}
		}
		free(tmp);
		count = 0;
		curr = curr->next;
	}

	findPriceOfMusicians(musiciansCrew, writeInd);

	if (!end)
		printConcert(concert, musiciansCrew, writeInd, tree);


	free(musiciansCrew);
}

// choses the free musicians and adds to the concert crew
int arrangeCrew(MusicianCrew* dest, Musician** src, CIListNode* node, int* writeInd, int size)
{
	int counter = node->data.num;  // num of musicians needed for instrument
	for (int i = 0; i < size; i++)
	{
		if (src[i]->available && counter)
		{
			src[i]->available = false;
			dest[*writeInd].player = src[i];
			dest[*writeInd].instrument = node->data.inst;
			(*writeInd)++;
			counter--;
		}
	}
	return counter;
}

// finds the price the musician charges for playing the instrument needed for the concert
void findPriceOfMusicians(MusicianCrew* musicians, int size) 
{
	int i;
	ListNode* curr;
	for (i = 0; i < size; i++) 
	{
		curr = musicians[i].player->instruments.head;
		while (curr != NULL) 
		{
			if (curr->data.insId == musicians[i].instrument)
				musicians[i].price = curr->data.price;
			curr = curr->next;
		}

	}
}

// compares the prices for playing an instrument between musicians
int compareInstrumentPrices(void* elem1, void* elem2) 
{
	currentInstrument* a = (currentInstrument*)elem1;
	currentInstrument* b = (currentInstrument*)elem2;
	ListNode* node1, * node2;
	bool flag;


	node1 = a->musician->instruments.head;
	node2 = b->musician->instruments.head;
	flag = false;

	while (node1 != NULL && node2 != NULL && !flag) {
		if (node1->data.insId != a->instrumentID)
			node1 = node1->next;
		else if (node2->data.insId != b->instrumentID)
			node2 = node2->next;
		else
			flag = true;
	}

	if (a->importance == '0')
		return (int)(node1->data.price - node2->data.price);
	else
		return (int)((-1) * (node1->data.price - node2->data.price));
}

// recieves data  about concert from user
// creates a string of the recieved data
char* getConcertString()
{
	int logSize, phySize;
	char* concertStr;
	char ch;
	bool endString;

	phySize = 1;
	logSize = 0;
	endString = false;

	concertStr = (char*)malloc(sizeof(char) * phySize);
	checkMemoryAllocation(concertStr);

	while (!endString) {
		ch = getchar();
		if (logSize == phySize) {
			phySize *= 2;
			concertStr = (char*)realloc(concertStr, sizeof(char) * phySize);
			checkMemoryAllocation(concertStr);
		}
		if (ch != '\n') {
			concertStr[logSize] = ch;
			logSize++;
		}
		else
			endString = true;
	}
	concertStr[logSize] = '\0';


	return concertStr;
}

// recieves a string of information about a concert and instrument tree
// converts and inputs the data into the concert struct
Concert getNewConcert(char* concertInfo, InstrumentTree* tree)
{
	Concert res;
	CIList instruments; // list of instruments needed for the concert
	Date date;  // date of concert
	char* name, * token;
	char* seps = " ";
	int pos, numOfInst, inst;
	char importance;

	numOfInst = inst = pos = date.day = date.month = date.year = 0;
	date.hour = 0.0;
	name = NULL;
	importance = '\0';
	token = strtok(concertInfo, seps);

	makeEmptyCIList(&instruments);

	// inputs with seperators the data from the concert string
	while (token != NULL)
	{
		if (pos == 0)
			name = _strdup(token);

		else if (pos > 0 && pos < 5)
			updateDate(pos, token, &date);

		else 
		{
			if (!inst)
				inst = findInsId(tree, token);
			else if (!numOfInst)
				numOfInst = convertToInt(token);
			else
				importance = token[0];

		}

		// inputs the information into instruments list
		if (inst && numOfInst && importance != '\0') {
			insertDataToEndCIList(&instruments, inst, numOfInst, importance);
			inst = 0;
			numOfInst = 0;
			importance = '\0';
		}
		pos++;
		token = strtok(NULL, seps);
	}
	res.date_of_concert = date;
	res.instruments = instruments;
	res.name = name;

	return res;

}

// initializes the concert instruments list
void makeEmptyCIList(CIList* instruments)
{
	instruments->head = instruments->tail = NULL;
}

// inserts a concert instrument to the end of the CIList
void insertDataToEndCIList(CIList* instruments, int instrumentID, int inst, char importance)
{
	CIListNode* newTail;
	newTail = createNewCIListNode(instrumentID, inst, importance, NULL);
	insertCILNodeToEndList(instruments, newTail);
}

// creates a new CIList node and inputs inforamtion into it
CIListNode* createNewCIListNode(int inst, int numOfInst, char importance, CIListNode* next) 
{
	CIListNode* res;
	res = (CIListNode*)malloc(sizeof(CIListNode));
	checkMemoryAllocation(res);
	res->data.num = numOfInst;
	res->data.inst = inst;
	res->data.importance = importance;
	res->next = next;

	return res;
}

//input: list of concert instruments, new concert instrument
//output: updates the concert instruments list by adding the new instrument
void insertCILNodeToEndList(CIList* instruments, CIListNode* newTail) 
{
	if (isEmptyCIList(instruments))
		instruments->head = instruments->tail = newTail;
	else {
		instruments->tail->next = newTail;
		instruments->tail = newTail;

	}
	newTail->next = NULL;
}

//input: position in file, token and date pointer
//the function takes the data from token and converts it the the type it is from strings
void updateDate(int pos, char* token, Date* date)
{
	switch (pos)
	{
	case 1:
		date->day = convertToInt(token);
		break;
	case 2:
		date->month = convertToInt(token);
		break;
	case 3:
		date->year = convertToInt(token);
		break;
	case 4:
		date->hour = hourToFloat(token);
	}
}