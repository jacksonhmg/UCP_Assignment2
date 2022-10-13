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


void* removeFirst(LinkedList* pList)
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
			
			/* TODO: set pRet = pTail's pData */
			/* TODO: NULLIFY all fields in pTail */
			/* TODO: free pTail */
			/* TODO: set pTail = pCur */
			/* TODO: set pTail->pNext = NULL */
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
			/* TODO: set pRet = pTail's pData */
			/* TODO: NULLIFY all fields in pTail */
			/* TODO: free pTail */
			/* TODO: set pTail = pHead = NULL */
            pRet = pList->pTail->pData;
            pList->pTail->pData = NULL;
            pList->pTail->pNext = NULL;
			free(pList->pTail);
            /*pList->pHead = pList->pTail;*/
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
		/* take pCur->pNext to pTemp */
		pTemp = pCur->pNext;
		
		/* clean pCur */
		/*(*funcPtr)(pCur->pData);
		(*funcPtr)(pCur->pNext);*/

		(*funcPtr)(pCur->pData);
		pCur->pData = NULL;
		pCur->pNext = NULL;
		free(pCur);
		
		/* set pCur = pTemp */
		pCur = pTemp;		
	}	
	
	free(pList);
}

void freeStruct(mapStruct* data)
{
	int i;
    for(i = 0; i < data->nR; i++)
    {
        free(data->map[i]);
    }
    free(data->map);
	free(data);
}
