#ifndef LINKEDLIST_H
#define LINKEDLIST_H

typedef void (*listFunc)(void* data);

typedef struct LinkedListNode
{
	void* pData;
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
void* removeFirst(LinkedList* pList);
void printLinkedList(LinkedList* list, listFunc funcPtr);
void freeLinkedList(LinkedList* list, listFunc funcPtr);


#endif