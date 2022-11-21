#include "RLEList.h"
#define FAIL -1
struct RLEList_t
{
    char currentChar;
    int repetitions;
    RLEList *next;
};
//help functions:

//implement the functions here

RLEList RLEListCreate ()
{
    RLEList ptr = malloc(sizeof(*ptr));
    if(!ptr){
        return NULL;
    }
    return ptr;
}

void RLEListDestroy (RLEList list)
{
    while(list){
        RLEList delete = list;
        list = list ->next;
        free(delete);
    }
}
//Q: they want me to check if the value is suited for the current Node ?
//or just append to the node without questions?
RLEListResult RLEListAppend(RLEList list, char value)
{
    if(list==NULL||value==NULL){
        return RLE_LIST_NULL_ARGUMENT;
    }
    if(list->currentChar==value){
        list->repetitions++;
    }else{
         RLEList ptr = malloc(sizeof(*ptr));
        if(!ptr){
            return RLE_LIST_OUT_OF_MEMORY;
        }
        ptr-> currentChar= value;
        ptr->repetitions=1;
        list->next=ptr;
    }
    return RLE_LIST_SUCCESS;
}

   
    



RLEListResult RLEListRemove(RLEList list, int index){
    if(list == NULL){
        return RLE_LIST_NULL_ARGUMENT;
    }
    int count=1;
    while(count<index){
        list = list ->next;
        if(!list)
        {
            return RLE_LIST_INDEX_OUT_OF_BOUNDS;
        }
        count++;
    }


}



