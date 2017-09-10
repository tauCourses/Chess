#include "StatesStack.h"

StateArrayList* StateArrayListCreate(int maxSize, size_t elementSize, State (*destroyElement)(State *))
{
    if(maxSize <= 0 || elementSize <=0 || destroyElement == NULL)
        return NULL;
    StateArrayList* arrayList = (StateArrayList *) malloc(sizeof(StateArrayList));
    if(arrayList == NULL)
        return NULL;

    arrayList->actualSize = 0;
    arrayList->maxSize = maxSize;
    arrayList->elementSize = elementSize;
    arrayList->destroyElement = destroyElement;
    arrayList->elements = (State*) malloc(arrayList->maxSize * elementSize);
    if(arrayList->elements == NULL)
    {
        free(arrayList);
        return NULL;
    }
    return arrayList;
}

StateArrayList* StateArrayListCopy(StateArrayList* src)
{
    if(src == NULL)
        return NULL;

    StateArrayList* arrayList = (StateArrayList *) malloc(sizeof(StateArrayList));
    if(arrayList == NULL)
        return NULL;

    arrayList->actualSize = src->actualSize;
    arrayList->maxSize = src->maxSize;
    arrayList->elementSize = src->elementSize;
    arrayList->destroyElement = src->destroyElement;
    arrayList->elements = (State**) malloc(arrayList->maxSize * src->elementSize);
    if(arrayList->elements == NULL)
    {
        free(arrayList);
        return NULL;
    }
    memcpy(arrayList->elements, src->elements, src->actualSize * sizeof(src->elementSize));
    return arrayList;
}

void StateArrayListDestroy(StateArrayList* src)
{
    if(src == NULL)
        return;
    while (!StateArrayListIsEmpty(src)){
        src->destroyElement(StateArrayListPop(src));
    }

    free(src->elements);
    free(src);
}

SP_ARRAY_LIST_MESSAGE StateArrayListClear(StateArrayList* src)
{
    if(src == NULL)
        return SP_ARRAY_LIST_INVALID_ARGUMENT;

    src->actualSize = 0;
    return SP_ARRAY_LIST_SUCCESS;
}

SP_ARRAY_LIST_MESSAGE StateArrayListPush(StateArrayList* src, State* elem)
{
    if(src == NULL)
        return SP_ARRAY_LIST_INVALID_ARGUMENT;
    if(src->actualSize == src->maxSize){
        printf("Push when full: About to destroy the last one\n");
        printf("this is list max size:%d and this actual size:%d\n", src->maxSize,src->actualSize);
        State* toRemove = StateArrayListGetLast(src);
        printf("%d\n",((State*)toRemove)->hasBKingMoved);

//        printStateBoard(((State*)toRemove));
//        printLocation(((State*)toRemove)->WKingLoc);


        src->destroyElement(toRemove);
        StateArrayListRemoveLast(src);
        printf("just destroyed the last one\n");
    }

    return StateArrayListAddFirst(src, elem);
}

State* StateArrayListPop(StateArrayList* src)
{
    if(src == NULL)
        return NULL;
    if(StateArrayListIsEmpty(src))
        return NULL;

    State* val = StateArrayListGetFirst(src);
    StateArrayListRemoveFirst(src);

    return val;
}

SP_ARRAY_LIST_MESSAGE StateArrayListAddAt(StateArrayList* src, State* elem, int index)
{
    if(src == NULL)
        return SP_ARRAY_LIST_INVALID_ARGUMENT;
    if(index < 0 || index > src->actualSize)
        return SP_ARRAY_LIST_INVALID_ARGUMENT;
    if(src->actualSize == src->maxSize)
        return SP_ARRAY_LIST_FULL;

    for(int i = src->actualSize -1; i>=index; i--)
        src->elements[i+1] = src->elements[i];
    State* newElem = malloc(src->elementSize);
    memcpy(newElem, elem, src->elementSize);

    src->elements[index] = newElem;
    src->actualSize++;
    return SP_ARRAY_LIST_SUCCESS;
}

SP_ARRAY_LIST_MESSAGE StateArrayListAddFirst(StateArrayList* src, State* elem)
{
    return StateArrayListAddAt(src,elem,0);
}

SP_ARRAY_LIST_MESSAGE StateArrayListAddLast(StateArrayList* src, State* elem)
{
    if(src == NULL)
        return SP_ARRAY_LIST_INVALID_ARGUMENT;
    return StateArrayListAddAt(src,elem,src->actualSize);
}

SP_ARRAY_LIST_MESSAGE StateArrayListRemoveAt(StateArrayList* src, int index)
{
    if(src == NULL)
        return SP_ARRAY_LIST_INVALID_ARGUMENT;
    if(src->actualSize == 0)
        return SP_ARRAY_LIST_EMPTY;
    if(index < 0 || index >= src->actualSize)
        return SP_ARRAY_LIST_INVALID_ARGUMENT;

    for(int i=index+1; i<src->actualSize;i++)
        src->elements[i-1] = src->elements[i];

    src->actualSize--;
    return SP_ARRAY_LIST_SUCCESS;
}

SP_ARRAY_LIST_MESSAGE StateArrayListRemoveFirst(StateArrayList* src)
{
    return StateArrayListRemoveAt(src,0);
}

SP_ARRAY_LIST_MESSAGE StateArrayListRemoveLast(StateArrayList* src)
{
    if(src == NULL)
        return SP_ARRAY_LIST_INVALID_ARGUMENT;
    return StateArrayListRemoveAt(src,src->actualSize-1);
}

State* StateArrayListGetAt(StateArrayList* src, int index)
{
    if(src == NULL)
        return NULL;
    if(index < 0 || index >= src->actualSize)
        return NULL;
    printf("im in getAt, this is the get at index %d: %d\n",index,((State*)(src->elements[index]))->hasBKingMoved);
    return (src->elements[index]);
}

State* StateArrayListGetFirst(StateArrayList* src)
{
    return StateArrayListGetAt(src,0);
}

State* StateArrayListGetLast(StateArrayList* src)
{
    if(src == NULL)
        return NULL;
    return StateArrayListGetAt(src,src->actualSize-1);

}

int StateArrayListMaxCapacity(StateArrayList* src)
{
    if(src == NULL)
        return -1;
    return src->maxSize;
}

int StateArrayListSize(StateArrayList* src)
{
    if(src == NULL)
        return -1;
    return src->actualSize;
}

bool StateArrayListIsFull(StateArrayList* src)
{
    if(src == NULL)
        return false;
    return src->actualSize < src->maxSize;
}

bool StateArrayListIsEmpty(StateArrayList* src)
{
    if(src == NULL)
        return false;
    return src->actualSize == 0;
}

void StateArrayListPrint(StateArrayList* src, State (*printElement)(State*))
{
    if(src == NULL)
    {
        printf("src is NULL\n");
        return;
    }
    for(int i=0; i<src->actualSize; i++)
        printElement(src->elements[i]);
    printf("\n");
}
