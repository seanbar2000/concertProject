#include "utilitiesHeader.h"

// converts string to float
float convertToFloat(char* str)
{
	float num;
	int i;

	i = 0;
	num = 0;

	while (str[i] != '\0') {
		num = num * 10 + (str[i] - '0');
		i++;
	}

	return num;
}

// checks if the memory was allocated
void checkMemoryAllocation(void* ptr)
{
	if (!ptr) {
		printf("Memory allocation failure.");
		exit(1);
	}
}

// checks if the file succeeded in opening
void checkFileOpening(FILE* fp) 
{
	if (!fp) {
		printf("Failed opening file.");
		exit(1);
	}
}

// gets the size of fp
long int fileSize(FILE* fp)
{
	long int res, saver;

	saver = ftell(fp);
	fseek(fp, 0, SEEK_END);
	res = ftell(fp);
	fseek(fp, saver, SEEK_SET);

	return res;
}

// removes \n in string - line
void removeEnter(char* line, int size)
{
	if (line[strlen(line) - 1] == '\n')
		line[strlen(line) - 1] = '\0';
}

// converts string to int
int convertToInt(char* str)
{
	int num;
	int i;

	i = 0;
	num = 0;

	while (str[i] != '\0') {
		num = num * 10 + (str[i] - '0');
		i++;
	}

	return num;
}

// converts string that represents the hour to a float value
float hourToFloat(char* str)
{
	float beforeP = 0, afterP = 0;

	for (int i = 0; i < HOUR_LENGTH; i++)
	{
		if (i < 2)
		{
			beforeP *= 10;
			beforeP += str[i] - '0';
		}
		else if (i > 2)
		{
			afterP *= 10;
			afterP += str[i] - '0';
		}
	}
	return beforeP + (afterP / 100);
}
