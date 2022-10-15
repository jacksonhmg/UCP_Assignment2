#include "macros.h"
#ifndef LINKEDLIST_H
#define LINKEDLIST_H

typedef void (*listFunc)(mapStruct* data);

typedef struct LinkedListNode
{
	mapStruct* pData;
	struct LinkedListNode* pNext;
} LinkedListNode;

typedef struct LinkedList
{
	LinkedListNode* pHead;
	LinkedListNode* pTail;
	int iSize;	
} LinkedList;

LinkedList* createLinkedList();
void insertLast(LinkedList* list, void* entry);
void insertFirst(LinkedList* pList, void* pEntry);
void* removeLast(LinkedList* list);
void* removeFirst(LinkedList* pList, listFunc funcPtr);
void printLinkedList(LinkedList* list, listFunc funcPtr);
void freeLinkedList(LinkedList* list, listFunc funcPtr);
void freeStruct(mapStruct* data);
void freeData(mapStruct* data);


#endif