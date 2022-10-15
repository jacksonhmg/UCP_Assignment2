#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "LinkedList.h"

LinkedList* createLinkedList()
{	
	LinkedList* pLinkedList = (LinkedList*) malloc(sizeof(LinkedList));
	pLinkedList->pHead = NULL;
	pLinkedList->pTail = NULL;
	pLinkedList->iSize = 0;

	return pLinkedList;	
}

void insertFirst(LinkedList* pList, void* pEntry)
{
	LinkedListNode* pNode = (LinkedListNode*) malloc (sizeof(LinkedListNode));
	pNode->pData = pEntry;
	pNode->pNext = NULL;

	if (pList->pHead == NULL)
	{
		assert(pList->pTail == NULL && pList->iSize == 0);		
		pList->pTail = pNode;
	}
	else
	{
		assert(pList->pTail && pList->iSize > 0);	
		pNode->pNext = pList->pHead;
	}

	pList->pHead = pNode;
	(pList->iSize)++;
}

void insertLast(LinkedList* pList, void* pEntry)
{
	/* Create a new node */
	LinkedListNode* pNode = (LinkedListNode*) malloc (sizeof(LinkedListNode));
	pNode->pData = pEntry;
	pNode->pNext = NULL;
		
	/* If linkedlist is empty */
	if (pList->pHead == NULL)
	{
		assert(pList->pTail == NULL && pList->iSize == 0);		
		pList->pHead = pNode;
	}
	else
	{
		assert(pList->pTail && pList->iSize > 0);	
		pList->pTail->pNext = pNode;
	}
	
	pList->pTail = pNode;
	(pList->iSize)++;
	
}


void* removeFirst(LinkedList* pList, listFunc funcPtr)
{
	LinkedListNode* pCur = pList->pHead;
	void* pRet = pList->pHead->pData;
	if(pCur)
	{
		if(pCur->pNext == NULL)
		{
			pList->pHead->pData = NULL;
			pList->pHead->pNext = NULL;
			free(pList->pHead);
			pList->pHead = NULL;
			pList->pTail = NULL;
		}
		else
		{
			pCur = pList->pHead->pNext;
			(*funcPtr)(pList->pHead->pData); /* added this here so that when undo is done, you free the struct correctly */
			pList->pHead->pData = NULL;
			pList->pHead->pNext = NULL;
			free(pList->pHead);
			pList->pHead = pCur;
		}
		(pList->iSize)--;
		pCur = NULL;
	}
	
	return pRet;
}

void* removeLast(LinkedList* pList) 
{ 
	LinkedListNode* pCur = pList->pHead;
	void* pRet = NULL;
	
	while (pCur)
	{		
		if (pCur->pNext == pList->pTail)
		{  /* If linkedlist has more than 1 node */
            pRet = pList->pTail->pData;
            pList->pTail->pData = NULL;
            pList->pTail->pNext = NULL;
            free(pList->pTail);
            pList->pTail = pCur;
			pList->pTail->pNext = NULL;


			(pList->iSize)--;
			pCur = NULL;
			
			assert(pList->pTail && pList->pHead && pList->iSize > 0);

		}
		else if (pCur == pList->pTail)
		{
            pRet = pList->pTail->pData;
            pList->pTail->pData = NULL;
            pList->pTail->pNext = NULL;
			free(pList->pTail);
            pList->pTail = NULL;
            pList->pHead = NULL;



			(pList->iSize)--;
			pCur = NULL;
			
			assert(pList->pTail == NULL && pList->pHead == NULL && pList->iSize == 0);

		}
		else
		{
			pCur = pCur->pNext;
		}		
	}

	return pRet;
}



void printLinkedList(LinkedList* pList, listFunc funcPtr)
{
	LinkedListNode* pCur = pList->pHead;
	
	while (pCur)
	{
		(*funcPtr)(pCur->pData);
		pCur = pCur->pNext;
	}
}

void freeLinkedList(LinkedList* pList, listFunc funcPtr) 
{
	LinkedListNode* pCur = pList->pHead;
	LinkedListNode* pTemp;
	
	while (pCur)
	{
		pTemp = pCur->pNext;

		(*funcPtr)(pCur->pData);
		pCur->pData = NULL;
		pCur->pNext = NULL;
		free(pCur);

		pCur = pTemp;		
	}	
	
	free(pList);
}

void freeStruct(mapStruct* data) /* free a created struct correctly including the malloc'd map inside it*/
{
	int i;
    for(i = 0; i < data->nR; i++)
    {
        free(data->map[i]);
    }
    free(data->map);
	free(data);
}

void freeData(mapStruct* data) /* when the struct inside the list did not have the map inside it malloc'd yet (see setup.c)*/
{
	free(data);
}
