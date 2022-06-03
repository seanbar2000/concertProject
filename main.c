#include "instrumentsHeader.h"
#include "freeHeader.h"
#include "musiciansHeader.h"
#include "utilitiesHeader.h"
#include "printsHeader.h"
#include "concertsHeader.h"

void main()
{

	InstrumentTree tree;
	Musician** MusiciansGroup;
	Musician*** MusiciansCollection;
	int* instrumentCount;
	int musiciansGroupSize, musiciansCollectionSize;


	tree = readInstrumentsFile("instruments.txt");
	MusiciansGroup = readMusiciansFile("musicians.txt", &tree, &musiciansGroupSize);
	MusiciansCollection = createMusiciansCollection(MusiciansGroup, musiciansGroupSize, &tree, &instrumentCount, &musiciansCollectionSize);
	getConcerts(MusiciansCollection, instrumentCount, &tree, MusiciansGroup, musiciansGroupSize);
	freeMusiciansGroup(MusiciansGroup, musiciansGroupSize);
	freeMusiciansCollection(MusiciansCollection, instrumentCount, musiciansCollectionSize);
	freeInstrumentTree(&tree);
}