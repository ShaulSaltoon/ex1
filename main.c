/*************************Definitions And Included Librareis*************/

#include "AsciiArtTool.h"
#include <string.h>

#define ENCODED 'e'
#define INVERTED 'i'

#define READ "r"
#define WRITE "w"
#define APPEND "a"


/*************************Declared Functions*****************************/


char readEncodedInvertedFlag(char* inFlag);
//differentiates between the recieved flags and returns the relevent char value

char mappingFunction(char OldChar);
//swithces all the spaces with @ and vise versa.

/*************************Implemented Functions**************************/




int main(int argc, char **argv) {
	if (argc != 4)
	{
		return 0;
	}
	char flag = readEncodedInvertedFlag(argv[1]);
	if (flag != INVERTED && flag != ENCODED)
	{
		return 0;
	}
	FILE* inputFile = fopen(argv[2], READ);
	if (!inputFile) 
	{
		return 0;
	}
	
	FILE* outputFile = fopen(argv[3], WRITE);
	if (!outputFile) 
	{
		fclose(inputFile);
		return 0;
	}

	RLEList list = asciiArtRead(inputFile);


	if (flag == ENCODED) 
	{
		asciiArtPrintEncoded(list, outputFile);
	}

	if (flag == INVERTED) 
	{
		RLEListMap(list, mappingFunction);
		asciiArtPrint(list, outputFile);
	}

	fclose(inputFile);
	fclose(outputFile);
	RLEListDestroy(list);
	
	return 0;
}


char readEncodedInvertedFlag(char* inFlag){
	if (strcmp(inFlag, "-e") == 0)
		return ENCODED;
	if (strcmp(inFlag, "-i") == 0)
		return INVERTED;
	else return '\0';
}


char mappingFunction(char OldChar) {
	if (OldChar == ' ')
	{
		OldChar = '@';
	}

	if (OldChar == '@')
	{
		OldChar = ' ';
	}
	
	return OldChar;
}