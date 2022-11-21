/*************************Included Files*********************************/


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

    node->repetitions = 1;
    node->currentChar = '\0';
    node->next = NULL;
    return node;
}

void RLEListDestroy (RLEList list)
{
    while(list){
        RLEList delete = list;
        list = list ->next;
        free(delete);
    }
}


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


int RLEListSize(RLEList list) {
    if (list == NULL) {
        return SIZE_FAIL;
    }

    int size = 0;
    while (list != NULL) {
        if (list->currentChar == '\0' && list->repetitions == 1 && list->next == NULL) {
            break;
        }
        
        size += list->repetitions;
        list = list->next;

    }
    return size;
}


char RLEListGet(RLEList list, int index, RLEListResult *result)
{
    if (list == NULL) 
    {
        //*result = RLE_LIST_NULL_ARGUMENT;// might cause a memory leak
        return RESULT_FAIL;
    }

    if (index > RLEListSize(list) || index <= 0)//might need to be <0 if the index starts from 0
    {
        //*result = RLE_LIST_INDEX_OUT_OF_BOUNDS;// might cause a memory leak
        return RESULT_FAIL;
    }

    RLEList tmpList = list;
    int sum = RESULT_FAIL;

    while (sum < index)
    {
        sum += list->repetitions;
        tmpList = list;
        list = list->next;
    } 
    //*result = RLE_LIST_SUCCESS;// might cause a memory leak
    return tmpList->currentChar;
}


RLEListResult RLEListMap(RLEList list, MapFunction map_function)
{
    if (list == NULL || map_function == NULL) return  RLE_LIST_NULL_ARGUMENT;
    
    do {
        list->currentChar = map_function(list->currentChar);
        list = list->next;
    } while (list);
    return RLE_LIST_SUCCESS;
}


char* RLEListExportToString(RLEList list, RLEListResult* result) 
{
    if (list == NULL) 
    {
        *result = RLE_LIST_NULL_ARGUMENT;// might cause a memory leak
        return NULL;
    }

    //int listSize = RLEListSize(list);
    int numOfNodes = findNumOfNodes(list);
    char* RLEListStr = (char*)malloc(sizeof(char) * (numOfNodes * 3 + 1));

    if (!RLEListStr) 
    {
        *result = RLE_LIST_OUT_OF_MEMORY;// might cause a memory leak
        return NULL;
    }

    RLEListStr[0] = '\0';
    char* ptrCurrentNodeStr = RLEListStr;
    
    for (int i = 0; i < numOfNodes; i++) 
    {
        int numOfChars = 0;
        numOfChars = sprintf(ptrCurrentNodeStr, "%c%d\n", list->currentChar, list->repetitions);
        ptrCurrentNodeStr += numOfChars;
        list = list->next;
    }

    *result = RLE_LIST_SUCCESS;// might cause a memory leak
    return RLEListStr;
}


RLEListResult RLEListRemove(RLEList list, int index)
{
    if (list == NULL) return RLE_LIST_NULL_ARGUMENT;
    if (index > RLEListSize(list) || index <= 0) return RLE_LIST_INDEX_OUT_OF_BOUNDS;
    
    struct RLEList_t* lastNode = NULL;
    int num = 0;

    while (num < index)
    {
        lastNode = list;
        num += list->repetitions;
        list = list->next;
    }

    list->repetitions--;
    
    if (list->repetitions <= 0)
    {
        if (index < 0)
        {
            struct RLEList_t* nodeToDelete = list;
            list = list->next;
            free(nodeToDelete);//is it actually deleting the first node or is it just deleting NodeToDelete?
        }

        else 
        {
            struct RLEList_t* nextNode = list->next;
            lastNode->next = nextNode;
            struct RLEList_t* nodeToDelete = list;
            if(lastNode->currentChar != nextNode->currentChar)
            {
                free(nodeToDelete);//is it actually deleting the first node or is it just deleting NodeToDelete?
            }
            else
            {
                lastNode->repetitions +=nextNode->repetitions;
                lastNode->next = nextNode->next;
                free(nodeToDelete);//repetitive
                free(nextNode);
            }
        }
    }

    return RLE_LIST_SUCCESS;
}