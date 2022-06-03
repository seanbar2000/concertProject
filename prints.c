#include "printsHeader.h"

// prints the concert information in order
void printConcert(Concert concert, MusicianCrew* musicians, int size, InstrumentTree* tree)
{
	printf("%s, ", concert.name);
	printNum(concert.date_of_concert.day);
	printNum(concert.date_of_concert.month);
	printf("%d ", concert.date_of_concert.year);
	printHour(concert.date_of_concert.hour);
	printMusicians(musicians, size, tree);
	printTotalPrice(musicians, size);
}

// prints the hour
void printHour(float hour)
{
	int h1, h2, min1, min2, h = (int)hour;
	float min = hour - h;
	h1 = h / 10;
	h2 = h % 10;
	min1 = (int)(min * 10);
	min2 = (int)(min * 100) % 10;
	printf("%d%d:%d%d ", h1, h2, min1, min2);

}

// prints the total price of the musicians crew
void printTotalPrice(MusicianCrew* musicians, int size)
{
	float res = 0;
	for (int i = 0; i < size; i++)
		res += musicians[i].price;

	printf("Total cost: %.2f. ", res);
}

//prints the musicians information in the musicianCrew
void printMusicians(MusicianCrew* musicians, int size, InstrumentTree* tree)
{
	for (int i = 0; i < size; i++)
	{
		printMusicianName(musicians[i].player->name, musicians[i].player->sizeOfName);
		printInstrumentName(tree, musicians[i].instrument);
		if (i + 1 == size)
			printf("(%.2f). ", musicians[i].price);
		else
			printf("(%.2f), ", musicians[i].price);
	}
}

// prints musician name
void printMusicianName(char** name, int size) 
{
	int i;
	for (i = 0; i < size; i++)
		printf("%s ", name[i]);
	printf("- ");
}

// prints day or month in a date
void printNum(int num)
{
	if (num < 10)
		printf("0%d ", num);
	else
		printf("%d ", num);
}

// prints the name of an instrument through his id
void printInstrumentName(InstrumentTree* tree, int id)
{
	printInstrumentNameHelper(tree->root, id);
}

// prints the name of the instrument that has the id
void printInstrumentNameHelper(TreeNode* root, int id)
{
	if (root == NULL)
		return;

	if (root->insId == id)
		printf("%s ", root->instrument);

	else {
		printInstrumentNameHelper(root->left, id);
		printInstrumentNameHelper(root->right, id);
	}
}
