
#ifndef CHESS_STATESSTACK_H
#define CHESS_STATESSTACK_H

#include "Infrastructure.h"

typedef struct state_array_list_t {
    State** elements;
    int actualSize;
    int maxSize;
    size_t elementSize;
    State (*destroyElement)(State *);
} StateArrayList;

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "Infrastructure.h"
//#include "console.h"


/**
 * StateArrayList summary:
 *
 * A container that represents a fixed size linked list. The capcity of the list
 * is specified at the creation. The container supports typical list
 * functionalities with the addition of random access as in arrays.
 * Upon insertion, if the maximum capacity is reached then an error message is
 * returned and the list is not affected. A summary of the supported functions
 * is given below:
 *
 * StateArrayListCreate       - Creates an empty array list with a specified
 *                           max capacity.
 * StateArrayListCopy         - Creates an exact copy of a specified array list.
 * StateArrayListDestroy      - Frees all memory resources associated with an array
 *                           list.
 * StateArrayListClear        - Clears all elements from a specified array list.
 * StateArrayListAddAt        - Inserts an element at a specified index, elements
 *                           will be shifted to make place.
 * StateArrayListAddFirst     - Inserts an element at the beginning of the array
 *                           list, elements will be shifted to make place.
 * StateArrayListAddLast      - Inserts an element at the end of the array list.
 * StateArrayListRemoveAt     - Removes an element at the specified index, elements
 *                           elements will be shifted as a result.
 * StateArrayListRemoveFirst  - Removes an element from the beginning of the array
 *                           list, elements will be shifted as a result.
 * StateArrayListRemoveLast   - Removes an element from the end of the array list
 * StateArrayListGetAt        - Accesses the element at the specified index.
 * StateArrayListGetFirst     - Accesses the first element of the array list.
 * StateArrayListGetLast      - Accesses the last element of the array list.
 * StateArrayListMaxCapcity   - Returns the maximum capcity of the array list.
 * StateArrayListSize         - Returns the number of elements in that array list.
 * StateArrayListIsFull       - Returns if the array list reached its max capacity.
 * StateArrayListIsEmpty      - Returns true if the array list contains no elements.
 */



/**
 *  Creates an empty array list with the specified maximum capacity.
 *  @param maxSize - the maximum capacity of the target array list.
 *  @return
 *  NULL, if an allocation error occurred or maxSize  <= 0.
 *  An instant of an array list otherwise.
 */
StateArrayList* StateArrayListCreate(int maxSize, size_t elementSize, State (*destroyElement)(State *));

/**
 *	Creates an exact copy of the src array list. Elements in the new copy will
 *	be in the same order as they appeared in the source list.
 *	@param src - the source array list.
 *	@return
 *	NULL if either an allocation error occurs or src == NULL.
 *	A new copy of the source array list, otherwise.
 */
StateArrayList* StateArrayListCopy(StateArrayList* src);

/**
 * Frees all memory resources associated with the source array list. If the
 * source array is NULL, then the function does nothing.
 * @param src - the source array list
 */
void StateArrayListDestroy(StateArrayList* src);

/**
 * Clears all elements from the source array list. After invoking this function,
 * the size of the source list will be reduced to zero and maximum capacity is
 * not affected.
 * @param src - the source array list
 * @return
 * SP_ARRAY_LIST_INVALID_ARGUMENT if src == NULL
 * SP_ARRAY_LIST_SUCCESS otherwise
 */
SP_ARRAY_LIST_MESSAGE StateArrayListClear(StateArrayList* src);

/**
 * Use the arrayList as a stack. After invoking this function,
 * the elem will be the first elements, and all other elements push to right.
 * if array is full it will remove the last element
 * @param src - the source array list
 * @param elem - the element to push
 * @return
 * SP_ARRAY_LIST_INVALID_ARGUMENT if src == NULL 
 * SP_ARRAY_LIST_SUCCESS - otherwise
 */
SP_ARRAY_LIST_MESSAGE StateArrayListPush(StateArrayList* src, State* elem);

/**
 * Use the arrayList as a stack. After invoking this function,
 * the first element will return and remove, and all other elements will push left.
 * if array is empty it return -1
 * @param src - the source array list
 * @return
 * -1 if src == NULL or src is empty 
 * element at index 0
 */
State* StateArrayListPop(StateArrayList* src);

/**
 * Inserts element at a specified index. The elements residing at and after the
 * specified index will be shifted to make place for the new element. If the
 * array list reached its maximum capacity and error message is returned and
 * the source list is not affected
 * @param src   - the source array list
 * @param elem  - the new element to be inserted
 * @param index - the index where the new element will be placed. The index is
 *                0-based.
 * @return
 * SP_ARRAY_LIST_INVALID_ARGUMENT - if src == NULL or the index is out of bound
 * SP_ARRAY_LIST_FULL - if the source array list reached its maximum capacity
 * SP_ARRAY_LIST_SUCCESS - otherwise
 */
SP_ARRAY_LIST_MESSAGE StateArrayListAddAt(StateArrayList* src, State* elem, int index);

/**
 * Inserts element at a the beginning of the source element. The elements
 * will be shifted to make place for the new element. If the
 * array list reached its maximum capacity and error message is returned and
 * the source list is not affected
 * @param src   - the source array list
 * @param elem  - the new element to be inserted
 * @return
 * SP_ARRAY_LIST_INVALID_ARGUMENT - if src == NULL or the index is out of bound
 * SP_ARRAY_LIST_FULL - if the source array list reached its maximum capacity
 * SP_ARRAY_LIST_SUCCESS - otherwise
 */
SP_ARRAY_LIST_MESSAGE StateArrayListAddFirst(StateArrayList* src, State* elem);

/**
 * Inserts element at a the end of the source element. If the array list
 * reached its maximum capacity and error message is returned and the source
 * list is not affected.
 * @param src   - the source array list
 * @param elem  - the new element to be inserted
 * @return
 * SP_ARRAY_LIST_INVALID_ARGUMENT - if src == NULL or the index is out of bound
 * SP_ARRAY_LIST_FULL - if the source array list reached its maximum capacity
 * SP_ARRAY_LIST_SUCCESS - otherwise
 */
SP_ARRAY_LIST_MESSAGE StateArrayListAddLast(StateArrayList* src, State* elem);

/**
 * Removes an element from a specified index. The elements residing after the
 * specified index will be shifted to make to keep the list continuous. If the
 * array list is empty then an error message is returned and the source list
 * is not affected
 * @param src   - The source array list
 * @param index - The index from where the element will be removed.
 *                The index is 0-based.
 * @return
 * SP_ARRAY_LIST_INVALID_ARGUMENT - if src == NULL or the index is out of bound
 * SP_ARRAY_LIST_EMPTY - if the source array list is empty
 * SP_ARRAY_LIST_SUCCESS - otherwise
 */
SP_ARRAY_LIST_MESSAGE StateArrayListRemoveAt(StateArrayList* src, int index);

/**
 * Removes an element from a the beginning of the list.
 * The elements will be shifted to make to keep the list continuous. If the
 * array list is empty then an error message is returned and the source list
 * is not affected
 * @param src   - The source array list
 * @param elem  - The new element to be inserted
 * @return
 * SP_ARRAY_LIST_INVALID_ARGUMENT - if src == NULL
 * SP_ARRAY_LIST_EMPTY - if the source array list is empty
 * SP_ARRAY_LIST_SUCCESS - otherwise
 */
SP_ARRAY_LIST_MESSAGE StateArrayListRemoveFirst(StateArrayList* src);

/**
 * Removes an element from a the end of the list.
 * The elements will be shifted to make to keep the list continuous. If the
 * array list is empty then an error message is returned and the source list
 * is not affected
 * @param src   - The source array list
 * @param elem  - The new element to be inserted
 * @return
 * SP_ARRAY_LIST_INVALID_ARGUMENT - if src == NULL
 * SP_ARRAY_LIST_EMPTY - if the source array list is empty
 * SP_ARRAY_LIST_SUCCESS - otherwise.
 */
SP_ARRAY_LIST_MESSAGE StateArrayListRemoveLast(StateArrayList* src);

/**
 * Returns the element at the specified index. The function is called
 * with the assertion that all arguments are valid. If any of the arguments is
 * invalid then an undefined value is returned.
 * @param src - the source array list
 * @param index - the specified index, the index is 0-based.
 * @return
 * Undefined value if either src == NULL or index out of bound.
 * Otherwise, the element at the specified index is returned.
 */
State* StateArrayListGetAt(StateArrayList* src, int index);

/**
 * Returns the element at the beginning of the list. The function is called
 * with the assertion that all arguments are valid. If any of the arguments is
 * invalid then an undefined value is returned.
 * @param src - the source array list
 * @return
 * Undefined value if either src == NULL or the list is empty
 * Otherwise, the element at the beginning of the list is returned.
 */
State* StateArrayListGetFirst(StateArrayList* src);

/**
 * Returns the element at the end of the list. The function is called
 * with the assertion that all arguments are valid. If any of the arguments is
 * invalid then an undefined value is returned.
 * @param src - the source array list
 * @return
 * Undefined value if either src == NULL or the list is empty
 * Otherwise, the element at the end of the list is returned.
 */
State* StateArrayListGetLast(StateArrayList* src);

/**
 * Returns the maximum capacity of the list. The function is called
 * with the assertion that all arguments are valid. If any of the arguments is
 * invalid then an undefined value is returned.
 * @param src - the source array list
 * @return
 * Undefined value if either src == NULL
 * Otherwise, the maximum capacity of the list is returned.
 */
int StateArrayListMaxCapacity(StateArrayList* src);

/**
 * Returns the number of elements in the list. The function is called
 * with the assertion that all arguments are valid. If any of the arguments is
 * invalid then an undefined value is returned.
 * @param src - the source array list
 * @return
 * Undefined value if either src == NULL
 * Otherwise, the number of the elements in the list is returned.
 */
int StateArrayListSize(StateArrayList* src);

/**
 * Returns true if the list is full, that is the number of elements in the list
 * equals its maximum capacity.
 * @param src - the source array list
 * @return
 * false if either src == NULL or the number of elements in the list is less
 * than its maximum capacity.
 * Otherwise, true is returned.
 */
bool StateArrayListIsFull(StateArrayList* src);

/**
 * Returns true if the list is empty, that is the number of elements in the list
 * equals to zero.
 * @param src - the source array list
 * @return
 * false if either src == NULL or the number of elements in the list is not zero.
 * Otherwise, true is returned.
 */
bool StateArrayListIsEmpty(StateArrayList* src);

/**
 * Print the content of the array list
 * @param src - the source array list
*/
void StateArrayListPrint(StateArrayList* src, State (*printElement)(State*));


#endif //CHESS_STATESSTACK_H
