#include "SPArrayList.h"

SPArrayList* spArrayListCreate(int maxSize)
{
	if(maxSize <= 0)
		return NULL;
	SPArrayList* arrayList = (SPArrayList *) malloc(sizeof(SPArrayList));
	if(arrayList == NULL)
		return NULL;
	arrayList->actualSize = 0;
	arrayList->maxSize = maxSize;
	arrayList->elements = (Location*) malloc(arrayList->maxSize*sizeof(Location));
	if(arrayList->elements == NULL)
	{
		free(arrayList);
		return NULL;
	}
	return arrayList;
}

SPArrayList* spArrayListCopy(SPArrayList* src)
{
	if(src == NULL)
		return NULL;

	SPArrayList* arrayList = (SPArrayList *) malloc(sizeof(SPArrayList));
	if(arrayList == NULL)
		return NULL;

	arrayList->actualSize = src->actualSize;
	arrayList->maxSize = src->maxSize;
	arrayList->elements = (Location*) malloc(arrayList->maxSize*sizeof(Location));
	if(arrayList->elements == NULL)
	{
		free(arrayList);
		return NULL;
	}
	memcpy(arrayList->elements, src->elements, src->actualSize * sizeof(Location));
	return arrayList;	
}

void spArrayListDestroy(SPArrayList* src)
{
	if(src == NULL)
		return;

	free(src->elements);
	free(src);
}

SP_ARRAY_LIST_MESSAGE spArrayListClear(SPArrayList* src)
{
	if(src == NULL)
		return SP_ARRAY_LIST_INVALID_ARGUMENT;

	src->actualSize = 0;
	return SP_ARRAY_LIST_SUCCESS;
}

SP_ARRAY_LIST_MESSAGE spArrayListPush(SPArrayList* src, Location* elem)
{
	if(src == NULL)
		return SP_ARRAY_LIST_INVALID_ARGUMENT;
	if(src->actualSize == src->maxSize)
		spArrayListRemoveLast(src);
	return spArrayListAddFirst(src, elem);
}

Location* spArrayListPop(SPArrayList* src)
{
	if(src == NULL)
		return NULL;
	if(spArrayListIsEmpty(src))
		return NULL;
	Location* val = spArrayListGetFirst(src);
	spArrayListRemoveFirst(src);
	
	return val;
}

SP_ARRAY_LIST_MESSAGE spArrayListAddAt(SPArrayList* src, Location* elem, int index)
{
	if(src == NULL)
		return SP_ARRAY_LIST_INVALID_ARGUMENT;
	if(index < 0 || index > src->actualSize)
		return SP_ARRAY_LIST_INVALID_ARGUMENT;
	if(src->actualSize == src->maxSize)
		return SP_ARRAY_LIST_FULL;

	for(int i = src->actualSize -1; i>=index; i--)
		src->elements[i+1] = src->elements[i];

	src->elements[index] = *elem;
	src->actualSize++;
	return SP_ARRAY_LIST_SUCCESS;
}

 SP_ARRAY_LIST_MESSAGE spArrayListAddFirst(SPArrayList* src, Location* elem)
{
	return spArrayListAddAt(src,elem,0);
}

SP_ARRAY_LIST_MESSAGE spArrayListAddLast(SPArrayList* src, Location* elem)
{
	if(src == NULL)
		return SP_ARRAY_LIST_INVALID_ARGUMENT;
	return spArrayListAddAt(src,elem,src->actualSize);	
}

SP_ARRAY_LIST_MESSAGE spArrayListRemoveAt(SPArrayList* src, int index)
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

SP_ARRAY_LIST_MESSAGE spArrayListRemoveFirst(SPArrayList* src)
{
	return spArrayListRemoveAt(src,0);
}

SP_ARRAY_LIST_MESSAGE spArrayListRemoveLast(SPArrayList* src)
{
	if(src == NULL)
		return SP_ARRAY_LIST_INVALID_ARGUMENT;
	return spArrayListRemoveAt(src,src->actualSize-1);	
}

Location* spArrayListGetAt(SPArrayList* src, int index)
{
	if(src == NULL)
		return NULL;
	if(index < 0 || index >= src->actualSize)
		return NULL;
	return &(src->elements[index]);
}

Location* spArrayListGetFirst(SPArrayList* src)
{
	return spArrayListGetAt(src,0);
}

Location* spArrayListGetLast(SPArrayList* src)
{
	if(src == NULL)
		return NULL;
	return spArrayListGetAt(src,src->actualSize-1);	

}

int spArrayListMaxCapacity(SPArrayList* src)
{
	if(src == NULL)
		return -1;
	return src->maxSize;
}

int spArrayListSize(SPArrayList* src)
{
	if(src == NULL)
		return -1;
	return src->actualSize;
}

bool spArrayListIsFull(SPArrayList* src)
{
	if(src == NULL)
		return false;
	return src->actualSize < src->maxSize;
}

bool spArrayListIsEmpty(SPArrayList* src)
{
	if(src == NULL)
		return false;
	return src->actualSize == 0;
}

void spArrayListPrint(SPArrayList* src)
{
	if(src == NULL)
	{
		printf("src is NULL\n");
		return;
	}
	for(int i=0; i<src->actualSize; i++)
		printf("<%d,%c> ",src->elements[i].x,src->elements[i].y+'A');
	printf("\n");
}
