#include "instrumentsHeader.h"
#include "freeHeader.h"
#include "musiciansHeader.h"

// free's the instrument tree
void freeInstrumentTree(InstrumentTree* tree) {
	freeInstrumentTreeHelper(tree->root);
	tree->root = NULL;
}

// free's memory from the leaf to the root 
void freeInstrumentTreeHelper(TreeNode* root) {
	{
		if (root == NULL)
			return;
		else
		{
			freeInstrumentTreeHelper(root->left);
			freeInstrumentTreeHelper(root->right);
			free(root->instrument);
			free(root);
		}
	}

}
// free's a two dimensunal array of musician
void freeMusiciansGroup(Musician** MusiciansGroup, int musiciansGroupSize) {
	int i, j;
	freeMPIList(MusiciansGroup, musiciansGroupSize);
	for (i = 0; i < musiciansGroupSize; i++) {
		for (j = 0; j < MusiciansGroup[i]->sizeOfName; j++)
			free(MusiciansGroup[i]->name[j]);
		free(MusiciansGroup[i]->name);
		free(MusiciansGroup[i]);
	}
	free(MusiciansGroup);
}

// frees the musician instrument prices array
void freeMPIList(Musician** MusiciansGroup, int musiciansGroupSize) {
	int i;
	ListNode* curr, * saver;
	for (i = 0; i < musiciansGroupSize; i++) {
		curr = MusiciansGroup[i]->instruments.head;
		while (curr != NULL) {
			saver = curr->next;
			free(curr);
			curr = saver;
		}
	}
}

// free's a three dimensional array of musician
void freeMusiciansCollection(Musician*** MusiciansCollection, int* instrumentCount, int musiciansCollectionSize) {
	int i;
	for (i = 0; i < musiciansCollectionSize; i++)
		free(MusiciansCollection[i]);
	free(MusiciansCollection);
	free(instrumentCount);
}

// free's concert memory
void freeConcert(Concert* concert) {
	CIListNode* curr, * saver;

	curr = concert->instruments.head;
	while (curr != NULL) {
		saver = curr->next;
		free(curr);
		curr = saver;
	}
	free(concert->name);

}
