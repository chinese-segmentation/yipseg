

#include "Queue.h"
#include "malloc.h"
#include "stdlib.h"
#include "memory.h"


CQueue::CQueue()
{
	m_pHead=NULL;
	m_pLastAccess=NULL;
}

CQueue::~CQueue()
{
   PQUEUE_ELEMENT pCur=m_pHead,pTemp;//The pointer of queue chain
   while(pCur!=NULL)
   {
	   pTemp=pCur->next;
	   delete pCur;
	   pCur=pTemp;
   }
}
/*********************************************************************
 *
 *  Func Name  : Push
 *
 *  Description:  push the node informatiom in the queue
 *              
 *
 *  Parameters :  nValue: The value for parent node
 *                nIndex: number of index in the parent node
 *                eWeight: the weight of last path
 *
 *  Returns    : int
 *********************************************************************/
int CQueue::Push(unsigned int nValue,//The value for parent node
				 unsigned int nIndex,//number of index in the parent node
                 ELEMENT_TYPE eWeight//the weight of last path 
			     )
{//Sort it
   PQUEUE_ELEMENT pAdd,pCur=m_pHead,pPre=0;//The pointer of queue chain
   
   while(pCur!=NULL&&pCur->eWeight<eWeight)
   {//Get the proper posption,sort according the weight
	   pPre=pCur;
	   pCur=pCur->next;
   }
   pAdd=(PQUEUE_ELEMENT)new QUEUE_ELEMENT;
   pAdd->nParent=nValue;
   pAdd->nIndex=nIndex;
   pAdd->eWeight=eWeight;
   pAdd->next=pCur;
   if(pPre==0)
	   m_pHead=pAdd;
   else
	   pPre->next=pAdd;
   return 1;
}
/*********************************************************************
 *
 *  Func Name  : Pop
 *
 *  Description:  Get  information of the first node
 *              
 *
 *  Parameters :  npValue: The value for parent node
 *                npIndex: number of index in the parent node
 *                epWeight: the weight of last path
 *                bModify: judge wether delete the first node or not
 *                bFirstGet: judge wether the first get the node or not
 *  Returns    : int
 *********************************************************************/
int CQueue::Pop(unsigned int *npValue,//The value for parent node
				unsigned int *npIndex,//number of index in the parent node
                ELEMENT_TYPE *epWeight,//the weight of last path 
                bool  bModify,//not modify the data 
				bool  bFirstGet//first get data,just for browse 
			   )
{
	PQUEUE_ELEMENT pTemp;

	if(bModify) 
		pTemp=m_pHead;//The temp buffer
	else 
	{
	  if(bFirstGet)//First get the data
	 	   m_pLastAccess=m_pHead;//The temp buffer
	  pTemp=m_pLastAccess;
	}

	if(pTemp==NULL)
		return -1;//fail get the value
    if(npValue!=0)
	       *npValue=pTemp->nParent;
    if(npIndex!=0)
	       *npIndex=pTemp->nIndex;
    if(epWeight!=0)
		  *epWeight=pTemp->eWeight;

    if(bModify)//modify and get rid of the node
	{
 	   m_pHead=pTemp->next;
	   delete pTemp;//free the buffer
	}
	else
	{
       m_pLastAccess=pTemp->next;
    }
     return 1;
}
/*********************************************************************
 *
 *  Func Name  : IsEmpty
 *
 *  Description: judge the queue is empty or not
 *              
 *
 *  Parameters :  bBrowsed: judge whether the browse pointer got end.
 *               
 *
 *  Returns    : success or fail
 *********************************************************************/
bool CQueue::IsEmpty(bool bBrowsed)//bBrowsed=true: judge whether the browse pointer got end.
{
	if(bBrowsed==true)
		return (m_pLastAccess==NULL);
   return (m_pHead==NULL);
}
/*********************************************************************
 *
 *  Func Name  : IsSingle
 *
 *  Description: judge head node is single or not
 *                            
 *
 *  Returns    : success or fail
 *********************************************************************/
bool CQueue::IsSingle()
{
   return (m_pHead!=NULL&&m_pHead->next==NULL);
}
