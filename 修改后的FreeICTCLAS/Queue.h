

#if !defined(AFX_QUEUE_H__382C7319_66D8_4041_ABA2_EE25B9D15D9C__INCLUDED_)
#define AFX_QUEUE_H__382C7319_66D8_4041_ABA2_EE25B9D15D9C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "DynamicArray.h"

struct tagQueueElem{
    unsigned int nParent;//the weight
	unsigned int nIndex;//number of index in the parent node
	ELEMENT_TYPE eWeight;//the weight of last path
    struct tagQueueElem *next;
};
typedef struct tagQueueElem QUEUE_ELEMENT,*PQUEUE_ELEMENT;

class CQueue  
{
public:
	bool IsSingle();
	bool IsEmpty(bool bBrowsed=false);
	int Push(unsigned int nValue=0,//The value for parent node
			 unsigned int nIndex=0,//number of index in the parent node
             ELEMENT_TYPE eWeight=0//the weight of last path 
			 );
	int Pop( unsigned int *npValue,//The value for node
			 unsigned int *npIndex,//number of index in the parent node
		     ELEMENT_TYPE *epWeight=0,//the weight of last path 
			 bool  bModify=true,//false: not modify the data
			 bool bFirstGet=true//first get data,just for browse 
		   );
	
	CQueue();
	virtual ~CQueue();
private:
	PQUEUE_ELEMENT m_pHead;//The chain sort according the weight of shortest path
	PQUEUE_ELEMENT m_pLastAccess;//The node last accessed
};

#endif // !defined(AFX_QUEUE_H__382C7319_66D8_4041_ABA2_EE25B9D15D9C__INCLUDED_)
