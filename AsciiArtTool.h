#ifndef AsciiArtTool_H_
#define AsciiArtTool_H_

#include "RLEList.h"

/*
*	asciiArRead: creates a RLE list from the input file
* 
* @param in_stream - file that has the ascii art that needs to be read
* 
* @return
*	RLEList of the art in the file
*/
RLEList asciiArtRead(FILE* in_stream);


/*
*	asciiArtPrint: receives an RLE list and prints it to the output file
* 
* @param list - RLE list that will be printed
* @param out_stream - the file to which the RLE list will be printed
* 
* @return
*	RLE_LIST_SUCCESS if the RLE list was successfully printed to the eoutput file
*	RLE_LIST_NULL_ARGUMENT if either the list or the file received were NULL
*	NULL if the list wasnt successfully printed
*/
RLEListResult asciiArtPrint(RLEList list, FILE* out_stream);


/*
*	asciiArtPrintEncoded: receives and RLE list of the art, inverts it and then prints it
* 
* @param list - RLE list of the ascii art
* @param out_stream - the file to which the inverted picture is to be printed
* 
* @return
*	RLE_LIST_SUCCESS if the inverted picture was successfully printed to the output file
*	RLE_LIST_NULL_ARGUMENT if one of the arguments received was NULL
*	NULL if the inverted picture wasnt successfully printed
*/
RLEListResult asciiArtPrintEncoded(RLEList list, FILE* out_stream);

#endif