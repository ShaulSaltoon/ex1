/******************Definitions And Included Files************************/


#include "AsciiArtTool.h"
#include <stdlib.h>


/**************************Declared Functions****************************/


//int checkResult(RLEListResult result);
//receives an RLElistResult enum pointer and returns whether it was RLE_LIST_SUCCESS or not


/**************************Implemented Functions*************************/


RLEList asciiArtRead(FILE* in_stream) {
	RLEList list = RLEListCreate();
	char tmpChar;

	while (fscanf(in_stream, "%c", &tmpChar) != EOF)
	{
		if (RLEListAppend(list, tmpChar) != RLE_LIST_SUCCESS)
		{
			return NULL;	
		}
	} 
	return list;
}

RLEListResult asciiArtPrint(RLEList list, FILE* out_stream) {
	if (list == NULL || out_stream == NULL)
	{
		return RLE_LIST_NULL_ARGUMENT;
	}

	int length = RLEListSize(list);
	RLEListResult* result = RLE_LIST_SUCCESS;//might need to be without a *

	for (int i = 0; i < length; i++)
	{
		char tmpc = RLEListGet(list, i, result);//result might need to be &result instead
		if(result != RLE_LIST_SUCCESS)
		{
			return result;
		}
		fprintf(out_stream, "%c", tmpc);
	}

	return RLE_LIST_SUCCESS;
}

RLEListResult asciiArtPrintEncoded(RLEList list, FILE* out_stream) {
	if (list == NULL || out_stream == NULL)
	{
		return RLE_LIST_NULL_ARGUMENT;
	}
	RLEListResult* result = RLE_LIST_SUCCESS;
	char* encodedString = RLEListExportToString(list, result);
	
	fprintf(out_stream, "%s", encodedString);
	free(encodedString);
	return RLE_LIST_SUCCESS;
}