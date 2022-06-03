#include "instrumentsHeader.h"
#include "freeHeader.h"
#include "musiciansHeader.h"
#include "utilitiesHeader.h"

// creates an instrument tree and adds an instrument
void createInstrumentTree(InstrumentTree* t, char* str, int id)
{
	InstrumentTree leftTree, rightTree;
	if (t->root == NULL)
	{
		t->root = createNewTreeNode(str, id, NULL, NULL);
		return;
	}
	else if (strcmp(t->root->instrument, str) > 0)
	{
		leftTree.root = t->root->left;
		createInstrumentTree(&leftTree, str, id);
		t->root->left = leftTree.root;
	}
	else if (strcmp(t->root->instrument, str) == 0)
	{
		printf("Please enter a different instrument\n");
		return;
	}
	else
	{
		rightTree.root = t->root->right;
		createInstrumentTree(&rightTree, str, id);
		t->root->right = rightTree.root;
	}

}

// adds a instrument TreeNode to the tree
TreeNode* createNewTreeNode(char* instrument, unsigned int insid, TreeNode* left, TreeNode* right)
{
	TreeNode* res;
	res = (TreeNode*)malloc(sizeof(TreeNode));
	checkMemoryAllocation(res);

	res->instrument = _strdup(instrument);
	res->insId = insid;
	res->left = left;
	res->right = right;

	return res;
}

// initializes a tree
void makeEmptyTree(InstrumentTree* tree)
{
	tree->root = NULL;
}

// finds and returns the id of instrument
int findInsId(InstrumentTree* tree, char* instrument)
{
	return findInsIdHelper(tree->root, instrument);
}

// searches through the tree to find the instrument name,
// returns the id of the instument
int findInsIdHelper(TreeNode* root, char* instrument)
{
	int res;
	if (root == NULL)
		return NOT_FOUND;

	else if (strcmp(root->instrument, instrument) == 0)
		return root->insId;
	else if (root->left == NULL && root->right == NULL)
		return NOT_FOUND;

	else
	{
		if (strcmp(root->instrument, instrument) > 0)
			res = findInsIdHelper(root->left, instrument);
		else
			res = findInsIdHelper(root->right, instrument);
		return res;
	}
}

// counts the amount of instruments in the tree
int countInstruments(InstrumentTree* tree) 
{
	return countInstrumentsHelper(tree->root);
}

// helps countInstruments count the amount of instruments in the tree
int countInstrumentsHelper(TreeNode* root) 
{
	int res;
	if (root == NULL)
		return 0;
	else {
		res = countInstrumentsHelper(root->left) + countInstrumentsHelper(root->right) + 1;
		return res;
	}

}

// reads the data from the instrument file and inputs it in an instrument tree
InstrumentTree readInstrumentsFile(char* fileName) 
{
	FILE* instruments;
	InstrumentTree tree;
	int id;
	char line[LINE_SIZE];
	long int fsize;

	makeEmptyTree(&tree);
	instruments = fopen(fileName, "r");
	checkFileOpening(instruments);

	fsize = fileSize(instruments);
	id = 1;

	while (ftell(instruments) < fsize)
	{
		fgets(line, LINE_SIZE, instruments);
		removeEnter(line, LINE_SIZE);
		createInstrumentTree(&tree, line, id);
		id++;
	}

	fclose(instruments);
	return tree;
}
