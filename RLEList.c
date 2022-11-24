/*************************Included Files*********************************/

#include <assert.h>
#include "RLEList.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


/********************Structs, Typedefs And Enums*************************/

#define SIZE_FAIL -1
#define RESULT_FAIL 0
struct RLEList_t
{
    int repetitions;
    char currentChar;
    struct RLEList_t* next;
}RLELIst_t;


/**********************Declarations Of Helper Functions******************/


int findNumOfNodes(RLEList list) 
{
    int sum = 1;
    while (list->next) {
        sum++;
        list = list->next;
    }
    return sum;
}


/**************************Function Implementation***********************/


RLEList RLEListCreate() 
{
    RLEList node = malloc(sizeof(*node));
    if (node == NULL) {
        return NULL;
    }

    node->repetitions = 0;
    node->currentChar = '\0';
    node->next = NULL;
    return node;
}

//works:
void RLEListDestroy (RLEList list)
{
    if( list == NULL)
    {
        return;
    }
    while(list){
        RLEList delete = list;
        list = list ->next;
        free(delete);
    }
}

//works:
RLEListResult RLEListAppend(RLEList list, char value)
{
    if(list==NULL||value=='\0')
    {
        return RLE_LIST_NULL_ARGUMENT;
    }

    while (list->next)
    {
        list = list->next;
    }//in order to get to the last node

    if (list->currentChar == value)
    {
        list->repetitions++;
        return RLE_LIST_SUCCESS;
    }
    
    else {
        if (list->currentChar == '\0')
        {
            list->currentChar = value;
            list->repetitions ++;
            return RLE_LIST_SUCCESS;
        }
        else {
            RLEList newPart = RLEListCreate();
            if (newPart != NULL)
            {
                newPart->currentChar = value;
                newPart->repetitions = 1;
                list->next = newPart;
                return RLE_LIST_SUCCESS;
            }
            else {
                return RLE_LIST_OUT_OF_MEMORY;
            }
        }
    }

    /*if(list->currentChar==value)
    {
        list->repetitions++;
    }        //list is a pointer to the first node, you arnt checking the last node

    else{
        RLEList ptr = malloc(sizeof(*ptr));

        if(!ptr)
        {
            return RLE_LIST_OUT_OF_MEMORY;
        }

        ptr-> currentChar= value;
        ptr->repetitions=1;
        list->next=ptr;
    }
    return RLE_LIST_SUCCESS;*/
}

//works
int RLEListSize(RLEList list) {
    if (list == NULL) {
        return SIZE_FAIL;
    }

    int size = 0;
    while (list != NULL) {
        size += list->repetitions;
        if ( list->next == NULL) {
            break;
        }
        
        
        list = list->next;

    }
    return size;
}

char RLEListGet(RLEList list, int index, RLEListResult *result)
{
    if (list == NULL) 
    {
        if (result != NULL)
        {
        *result = RLE_LIST_NULL_ARGUMENT;
        }
        return RESULT_FAIL;
    }

    if (index > RLEListSize(list) -1 || index < 0)//listsize -1 cause the index is like in an array
    {
        if (result != NULL)
        {
            *result = RLE_LIST_INDEX_OUT_OF_BOUNDS;
        }
        return RESULT_FAIL;
    }

    index++; // treating it like a real number and not a index for an array
    RLEList tmpList = list;
    int sum = RESULT_FAIL;

    while (sum < index)
    {
        sum += list->repetitions;
        tmpList = list;
        list = list->next;
    } 
    if (result != NULL)
    {
        *result = RLE_LIST_SUCCESS;
    }
    return tmpList->currentChar;
}

//work !!! 
RLEListResult RLEListMap(RLEList list, MapFunction map_function)
{
    if (list == NULL || map_function == NULL) return  RLE_LIST_NULL_ARGUMENT;
    RLEList tempNode = list;
    do {
        tempNode->currentChar = map_function(tempNode->currentChar);
        tempNode = tempNode->next;
        
    } while (tempNode);
    //check for doubles:

    while(list->next!=NULL){
        tempNode=list->next;
        assert(tempNode==list->next);
        if(list->currentChar == tempNode->currentChar){
            list->repetitions += tempNode->repetitions;
            if(!tempNode->next){
                tempNode->repetitions = 0;
                tempNode->currentChar = '\0';
                tempNode->next = NULL;
                break;
            }
            //
            list->next=tempNode->next;
            free(tempNode);

            
        }else{
        list = list->next;
        }
    }

    return RLE_LIST_SUCCESS;
}

//work
char* RLEListExportToString(RLEList list, RLEListResult* result) 
{

    if (list == NULL) 
    {
        if(result != NULL)
        {
            *result = RLE_LIST_NULL_ARGUMENT;  
        }
        return NULL;
    }

    //int listSize = RLEListSize(list);
    int numOfNodes = findNumOfNodes(list);
    //changing the size of malloc to check:
    char* RLEListStr = (char*)malloc((sizeof(char)*2 + sizeof(int)+1 )* (numOfNodes + 1));
    //cheking if there is a malloc problem:
    if (!RLEListStr) 
    {   //check it the user wants to save the result:
        if(result != NULL)
        {
            *result = RLE_LIST_OUT_OF_MEMORY;
        }
        return NULL;
    }
    //dont know why you putting this sign in the beggining?
    //RLEListStr[0] = '\0';
    char* tempNode = RLEListStr;
    
    for (int i = 0; i < numOfNodes; i++) 
    {
        int spintfNum = 0;
        //sprintf(buffer, "Sum of %d and %d is %d", a, b, c);
        spintfNum= sprintf(tempNode, "%c%d\n", list->currentChar, list->repetitions);
        assert((spintfNum!=-1));
        //printf("%s",tempNode);
        tempNode += spintfNum;
        list = list->next;
    }

    if(result != NULL)
    {
        *result = RLE_LIST_SUCCESS;
    }
    return RLEListStr;
}

//work:
RLEListResult RLEListRemove(RLEList list, int index)
{
    if (list == NULL) 
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    if (index > RLEListSize(list)-1|| index < 0)//listsize -1 cause the index is like in an array
    {
        return RLE_LIST_INDEX_OUT_OF_BOUNDS;
    }
    int tempLoop= index+1;
    RLEList tempNode=list;
    RLEList tempLast = NULL;
    //select the correct node:
    while(tempLoop-tempNode->repetitions>0) {
        tempLoop -= tempNode->repetitions;
        //for later use:
        tempLast = tempNode;
        tempNode = tempNode->next;
        assert((tempLast->next==tempNode));

    }
    // no need of deleting node : 
    if(tempNode->repetitions > 1){
        tempNode->repetitions--;
        return RLE_LIST_SUCCESS;
    }
    //we need to delete node:

    //check if tempNode is the first one:
    if(!list->next){
        tempNode->repetitions = 0;
        tempNode->currentChar = '\0';
        tempNode->next = NULL;
       // free(tempNode);
        return RLE_LIST_SUCCESS;
    }
    if(tempNode == list)
    {
        tempNode = list->next;

        list->next = tempNode->next;
        *list = *tempNode;
     //   printf("list char: %c list rep %d\n",list->currentChar,list->repetitions);
        free(tempNode);
        return RLE_LIST_SUCCESS;
    }
    //temp node is in the middle or end: 
    if(tempNode->next==NULL){
        //temp node is in the end:
        
        tempLast->next=NULL;
        
    }else{
        //temp node is in the middle:
        //check if tempLast to the next in chain
        if(tempLast->currentChar!=tempNode->next->currentChar){
            tempLast->next= tempNode->next;
        }else{
            //we need to merge between nodes:
            tempLast->repetitions += tempNode->next->repetitions;
            tempLast->next= tempNode->next->next;
            free(tempNode->next);
        }
        
        
    }
    free(tempNode);
    return RLE_LIST_SUCCESS;
}











