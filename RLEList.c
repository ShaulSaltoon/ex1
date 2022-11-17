#include "RLEList.h"
#define FAIL -1
struct RLEList_t{
    char symbol;
    int len;
    RLEList *next;
};

//implement the functions here

RLEList RLEListCreate (){
    RLEList ptr = malloc(sizeof(*ptr));
    if(!ptr){
        return NULL;
    }
    return ptr;
}

void RLEListDestroy (RLEList list){
    while(list){
        RLEList delete = list;
        list = list ->next;
        free(delete);
    }
}
//Q: they want me to check if the value is suited for the current Node ?
//or just append to the node without questions?
RLEListResult RLEListAppend(RLEList list, char value){
    if(list==NULL||value==NULL){
        return RLE_LIST_NULL_ARGUMENT;
    }
    if(list->symbol==value){
        list->len++;
    }else{
         RLEList ptr = malloc(sizeof(*ptr));
        if(!ptr){
            return RLE_LIST_OUT_OF_MEMORY;
        }
        ptr->symbol = value;
        ptr->len=1;
        list->next=ptr;
    }
    return RLE_LIST_SUCCESS;
}

   
    


int RLEListSize(RLEList list){
    if(list == NULL){
        return FAIL;
    }
    int count=0;
    while(list->next!=NULL){
        count ++;
        list = list->next;
    }
    return count;

}
