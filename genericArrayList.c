#include "genericArrayList.h"

genericArrayList* genericArrayListCreate(int maxSize, size_t elementSize, void (*destroyElement)(void *))
{
	if(maxSize <= 0 || elementSize <=0 || destroyElement == NULL)
		return NULL;
	genericArrayList* arrayList = (genericArrayList *) malloc(sizeof(genericArrayList));
	if(arrayList == NULL)
		return NULL;

    arrayList->actualSize = 0;
	arrayList->maxSize = maxSize;
    arrayList->elementSize = elementSize;
    arrayList->destroyElement = destroyElement;
	arrayList->elements = (void*) malloc(arrayList->maxSize * elementSize);
	if(arrayList->elements == NULL)
	{
		free(arrayList);
		return NULL;
	}
	return arrayList;
}

genericArrayList* genericArrayListCopy(genericArrayList* src)
{
	if(src == NULL)
		return NULL;

	genericArrayList* arrayList = (genericArrayList *) malloc(sizeof(genericArrayList));
	if(arrayList == NULL)
		return NULL;

	arrayList->actualSize = src->actualSize;
	arrayList->maxSize = src->maxSize;
	arrayList->elements = (void**) malloc(arrayList->maxSize * src->elementSize);
	if(arrayList->elements == NULL)
	{
		free(arrayList);
		return NULL;
	}
	memcpy(arrayList->elements, src->elements, src->actualSize * sizeof(src->elementSize));
	return arrayList;	
}

void genericArrayListDestroy(genericArrayList* src)
{
	if(src == NULL)
		return;

	free(src->elements);
	free(src);
}

SP_ARRAY_LIST_MESSAGE genericArrayListClear(genericArrayList* src)
{
	if(src == NULL)
		return SP_ARRAY_LIST_INVALID_ARGUMENT;

	src->actualSize = 0;
	return SP_ARRAY_LIST_SUCCESS;
}

SP_ARRAY_LIST_MESSAGE genericArrayListPush(genericArrayList* src, void* elem)
{
    if(src == NULL)
		return SP_ARRAY_LIST_INVALID_ARGUMENT;
	if(src->actualSize == src->maxSize)
        genericArrayListRemoveLast(src);
	return genericArrayListAddFirst(src, elem);
}

void* genericArrayListPop(genericArrayList* src)
{
	if(src == NULL)
		return NULL;
	if(genericArrayListIsEmpty(src))
		return NULL;

	printf("\nim in pop %d\n",((State*)genericArrayListGetFirst(src))->currentPlayer);
    void* val = malloc(src->elementSize);
    memcpy(val, genericArrayListGetFirst(src), src->elementSize);



	genericArrayListRemoveFirst(src);
	
	return val;
}

SP_ARRAY_LIST_MESSAGE genericArrayListAddAt(genericArrayList* src, void* elem, int index)
{
	if(src == NULL)
		return SP_ARRAY_LIST_INVALID_ARGUMENT;
	if(index < 0 || index > src->actualSize)
		return SP_ARRAY_LIST_INVALID_ARGUMENT;
	if(src->actualSize == src->maxSize)
		return SP_ARRAY_LIST_FULL;

	for(int i = src->actualSize -1; i>=index; i--)
		src->elements[i+1] = src->elements[i];
	void* newElem = malloc(src->elementSize);
	memcpy(newElem, elem, src->elementSize);

	src->elements[index] = newElem;
	src->actualSize++;
	return SP_ARRAY_LIST_SUCCESS;
}

 SP_ARRAY_LIST_MESSAGE genericArrayListAddFirst(genericArrayList* src, void* elem)
{
	return genericArrayListAddAt(src,elem,0);
}

SP_ARRAY_LIST_MESSAGE genericArrayListAddLast(genericArrayList* src, void* elem)
{
	if(src == NULL)
		return SP_ARRAY_LIST_INVALID_ARGUMENT;
	return genericArrayListAddAt(src,elem,src->actualSize);
}

SP_ARRAY_LIST_MESSAGE genericArrayListRemoveAt(genericArrayList* src, int index)
{
	if(src == NULL)
		return SP_ARRAY_LIST_INVALID_ARGUMENT;
	if(src->actualSize == 0)
		return SP_ARRAY_LIST_EMPTY;
	if(index < 0 || index >= src->actualSize)
		return SP_ARRAY_LIST_INVALID_ARGUMENT;

    printf("im about to destroy element!\n");
    src->destroyElement(src->elements[index]);
    printf("it's done element is dead now.!\n");

	for(int i=index+1; i<src->actualSize;i++)
		src->elements[i-1] = src->elements[i];

	src->actualSize--;
	return SP_ARRAY_LIST_SUCCESS;	
}

SP_ARRAY_LIST_MESSAGE genericArrayListRemoveFirst(genericArrayList* src)
{
	return genericArrayListRemoveAt(src,0);
}

SP_ARRAY_LIST_MESSAGE genericArrayListRemoveLast(genericArrayList* src)
{
	if(src == NULL)
		return SP_ARRAY_LIST_INVALID_ARGUMENT;
	return genericArrayListRemoveAt(src,src->actualSize-1);	
}

void* genericArrayListGetAt(genericArrayList* src, int index)
{
	if(src == NULL)
		return NULL;
	if(index < 0 || index >= src->actualSize)
		return NULL;
	return (src->elements[index]);
}

void* genericArrayListGetFirst(genericArrayList* src)
{
	return genericArrayListGetAt(src,0);
}

void* genericArrayListGetLast(genericArrayList* src)
{
	if(src == NULL)
		return NULL;
	return genericArrayListGetAt(src,src->actualSize-1);	

}

int genericArrayListMaxCapacity(genericArrayList* src)
{
	if(src == NULL)
		return -1;
	return src->maxSize;
}

int genericArrayListSize(genericArrayList* src)
{
	if(src == NULL)
		return -1;
	return src->actualSize;
}

bool genericArrayListIsFull(genericArrayList* src)
{
	if(src == NULL)
		return false;
	return src->actualSize < src->maxSize;
}

bool genericArrayListIsEmpty(genericArrayList* src)
{
	if(src == NULL)
		return false;
	return src->actualSize == 0;
}

void genericArrayListPrint(genericArrayList* src, void (*printElement)(void*))
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
