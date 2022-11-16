/*************************Included Files*********************************/


#include "RLEList.h"


/********************Structs, Typedefs And Enums*************************/


struct RLEList_t
{
    int repetitions;
    char currentChar;
    struct RLEList_t* next;
}RLELIst_t;

typedef enum {
    character = 1,
    instances,
    nextLineIndicator
}RLEListStringID;

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


char RLEListGet(RLEList list, int index, RLEListResult *result)
{
    if (list == NULL) 
    {
        *result = RLE_LIST_NULL_ARGUMENT;// might cause a memory leak
        return 0;
    }

    if (index > RLEListSize(list) || index <= 0)//might need to be <0 if the index starts from 0
    {
        *result = RLE_LIST_INDEX_OUT_OF_BOUNDS;// might cause a memory leak
        return 0;
    }

    RLEList tmpList = list;
    int sum = 0;

    while (sum < index)
    {
        sum += list->repetitions;
        tmpList = list;
        list = list->next;
    } 
    *result = RLE_LIST_SUCCESS;// might cause a memory leak
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

    for (int i = 0; i < numOfNodes; i++)
    {
        RLEListStr[i*3 + character] = list->currentChar;
        RLEListStr[i*3 + instances] = list->repetitions;
        RLEListStr[i*3 + nextLineIndicator] = '\n';
        list = list->next;
    }

    /*RLEListStr[0] = '\0';
    char* ptrCurrentNodeStr = RLEListStr;
    
    for (int i = 0; i < numOfNodes; i++) 
    {
        int numOfChars = 0;
        numOfChars = sprintf(ptrCurrentNodeStr, "%c%d\n", list->currentChar, list->repetitions);
        ptrCurrentNodeStr += numOfChars;
        list = list->next;
    } */

    *result = RLE_LIST_SUCCESS;// might cause a memory leak
    return RLEListStr;
}


RLEListResult RLEListRemove(RLEList list, int index)
{
    if (list == NULL || index == 0) return RLE_LIST_NULL_ARGUMENT;
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
        if (index = 0)
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