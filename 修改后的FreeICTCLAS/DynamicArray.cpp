#include "DynamicArray.h"
#include <stdlib.h>
#include <malloc.h>
#include <string.h>


CDynamicArray::CDynamicArray(bool bRowFirst)
{
   m_pHead=NULL;
   m_nRow=0;
   m_nCol=0;
   m_bRowFirst=bRowFirst;
}

CDynamicArray::~CDynamicArray()
{
   PARRAY_CHAIN pCur=m_pHead,pTemp;//The pointer of array chain
   while(pCur!=NULL)
   {
	   pTemp=pCur->next;
       if(pCur->sWord)
			delete [] pCur->sWord;
	   free(pCur); 
	   pCur=pTemp;
   }
}

/*********************************************************************
 *
 *  Func Name  : GetElement
 *
 *  Description:  Get the element value
 *              
 *
 *  Parameters : nRow: the row number
 *               nCol: the Column number
 *    
 *  Returns    : the element value if found,else Infinite value
 *********************************************************************/
ELEMENT_TYPE CDynamicArray::GetElement(int nRow, int nCol,PARRAY_CHAIN pStart,PARRAY_CHAIN *pRet)
{
   PARRAY_CHAIN pCur=pStart;
   if(pStart==0)
	    pCur=m_pHead;
   if(pRet!=0)
	   *pRet=NULL;
   if(nRow>(int)m_nRow||nCol>(int)m_nCol)//Judge if the row and col is overflow
	   return INFINITE_VALUE;
  if(m_bRowFirst)
   {
	   while(pCur!=NULL&&(nRow!=-1&&(int)pCur->row<nRow||(nCol!=-1&&(int)pCur->row==nRow&&(int)pCur->col<nCol)))
	   {
		   if(pRet!=0)
			   *pRet=pCur;
		   pCur=pCur->next;
	   }
   }
   else
   {
	   while(pCur!=NULL&&(nCol!=-1&&(int)pCur->col<nCol||((int)pCur->col==nCol&&nRow!=-1&&(int)pCur->row<nRow)))
	   {
		   if(pRet!=0)
			   *pRet=pCur;
		   pCur=pCur->next;
	   }
   }
   if(pCur!=NULL&&((int)pCur->row==nRow||nRow==-1)&&((int)pCur->col==nCol||nCol==-1))//Find the same position
   {//Find it and return the value
	   if(pRet!=0)
		   *pRet=pCur;
	   return pCur->value;
   }
	return INFINITE_VALUE;
}

/*********************************************************************
 *
 *  Func Name  : SetElement
 *
 *  Description:  Set the element value
 *              
 *
 *  Parameters : nRow: the row number
 *               nCol: the Column number
 *               fValue: the value to be set
 *               nPOS: the position of the word
 *               sWord: the word string
 *  Returns    : the element value if found,else Infinite value
 *********************************************************************/
int CDynamicArray::SetElement(unsigned int nRow, unsigned int nCol, ELEMENT_TYPE fValue,int nPOS,char *sWord)
{
   PARRAY_CHAIN pCur=m_pHead,pPre=NULL,pAdd;//The pointer of array chain
   if(nRow>m_nRow)//Set the array row
	   m_nRow=nRow;
   if(nCol>m_nCol)//Set the array col
	   m_nCol=nCol;
   if(m_bRowFirst)
   {
	   while(pCur!=NULL&&(pCur->row<nRow||(pCur->row==nRow&&pCur->col<nCol)))
	   {
		   pPre=pCur;
		   pCur=pCur->next;
	   }
   }
   else
   {
	   while(pCur!=NULL&&(pCur->col<nCol||(pCur->col==nCol&&pCur->row<nRow)))
	   {
		   pPre=pCur;
		   pCur=pCur->next;
	   }
   }

   if(pCur!=NULL&&pCur->row==nRow&&pCur->col==nCol)//Find the same position
   {
	   pCur->value=fValue;//Set the value
	   pCur->nPOS=nPOS;//Set the possible POS
   }
   else
   {
       pAdd=(PARRAY_CHAIN)malloc(sizeof(ARRAY_CHAIN));//malloc a new node
	   pAdd->col=nCol;//get the value
	   pAdd->row=nRow;
	   pAdd->value=fValue;
	   pAdd->nPOS=nPOS;
	   if(sWord)//sWord is not empty
	   {
		   pAdd->nWordLen=strlen(sWord);
		   pAdd->sWord=new char[pAdd->nWordLen+1];
		   strcpy(pAdd->sWord,sWord);
	   }
	   else//sWord is Empty
	   {
		   pAdd->nWordLen=0;
		   pAdd->sWord=NULL;
	   }
	   pAdd->next=pCur;
	
	   if(pPre==NULL)//link pAdd after the pPre
		   m_pHead=pAdd;
	   else
		   pPre->next=pAdd;
   }
   return 0;
}


const CDynamicArray & CDynamicArray::operator =(const CDynamicArray &array)
{
   PARRAY_CHAIN pCur,pAdd,pTail=NULL;//The pointer of array chain
   SetEmpty();
   m_nCol=array.m_nCol;
   m_nRow=array.m_nRow;
   pCur=array.m_pHead;
   while(pCur!=NULL)
   {
	   pAdd=(PARRAY_CHAIN)malloc(sizeof(ARRAY_CHAIN));//malloc a new node
	   pAdd->col=pCur->col;//get the value
	   pAdd->row=pCur->row;
	   pAdd->value=pCur->value;
	   pAdd->nPOS=pCur->nPOS;
	   pAdd->next=NULL;
       pAdd->sWord=NULL;
	   if(pCur->nWordLen>=0)
	   {
		   pAdd->nWordLen=pCur->nWordLen;
		   pAdd->sWord=new char[pAdd->nWordLen+1];
		   strcpy(pAdd->sWord,pCur->sWord);
	   }

	   if(pTail==NULL)
		   m_pHead=pAdd;//The head element
	   else
           pTail->next=pAdd;
       pTail=pAdd;
	   pCur=pCur->next;
   }
   return *this;
}
/*********************************************************************
 *
 *  Func Name  : SetEmpty
 *
 *  Description:  Clear the dynamic array
 *              
 *    
 *  Returns    : the element value if found,else Infinite value
 *  
 *********************************************************************/
void CDynamicArray::SetEmpty()
{
   PARRAY_CHAIN pCur=m_pHead,pTemp;
   while(pCur!=NULL)//delete the node 
   {
	   pTemp=pCur->next;
 	   if(pCur->nWordLen>0)
			delete [] pCur->sWord;
       free(pCur); 
	   pCur=pTemp;
   }
   m_pHead=NULL;
   m_nCol=0;
   m_nRow=0;
}

/*********************************************************************
 *
 *  Func Name  : GetElement
 *
 *  Description:  Get the element value
 *              
 *
 *  Parameters : nRow: the row number
 *               nCol: the Column number
 *               pRetValue: the value to be return
 *               pRetPOS: the position of the return word 
 *               sRetWord: the return word it found
 *  Returns    : success or fail
 *********************************************************************/
bool CDynamicArray::operator ==(const CDynamicArray &array)
{
   PARRAY_CHAIN pFirst,pSecond;//The pointer of array chain
   if(m_nCol!=array.m_nCol||m_nRow!=array.m_nRow)//Row or Col not equal
	   return false;
   
   pFirst=array.m_pHead;
   pSecond=m_pHead;
   while(pFirst!=NULL&&pSecond!=NULL&&pFirst->row==pSecond->row&&pFirst->col==pSecond->col&&pFirst->value==pSecond->value)
   {
	   pFirst=pFirst->next;
	   pSecond=pSecond->next;
   }
   if(pFirst==NULL&&pSecond==NULL)
        return true;
   return false;
}
/*********************************************************************
 *
 *  Func Name  : GetElement
 *
 *  Description:  Get the element value
 *              
 *
 *  Parameters : nRow: the row number
 *               nCol: the Column number
 *               pRetValue: the value to be return
 *               pRetPOS: the position of the return word 
 *               sRetWord: the return word it found
 *  Returns    : success or fail
 *********************************************************************/
bool CDynamicArray::GetElement(int nRow, int nCol, ELEMENT_TYPE *pRetValue, int *pRetPOS,char *sRetWord)
{
    PARRAY_CHAIN pCur=m_pHead;
	*pRetValue=INFINITE_VALUE;
	*pRetPOS=0;
   if(nRow>(int)m_nRow||nCol>(int)m_nCol)//Judge if the row and col is overflow
	   return false;
   if(m_bRowFirst)
   {
	   while(pCur!=NULL&&(nRow!=-1&&(int)pCur->row<nRow||(nCol!=-1&&(int)pCur->row==nRow&&(int)pCur->col<nCol)))
	   {
		   pCur=pCur->next;
	   }
   }
   else
   {
	   while(pCur!=NULL&&(nCol!=-1&&(int)pCur->col<nCol||((int)pCur->col==nCol&&nRow!=-1&&(int)pCur->row<nRow)))
	   {
		   pCur=pCur->next;
	   }
   }
   if(pCur!=NULL&&((int)pCur->row==nRow||nRow==-1)&&((int)pCur->col==nCol||nCol==-1))//Find the same position
   {//Find it and return the value
		*pRetValue=pCur->value;
		if(pRetPOS)
			*pRetPOS=pCur->nPOS;
	    if(sRetWord)//sWord is not empty
		{
		   strcpy(sRetWord,pCur->sWord);
		}
   }
	return true;
}

/*********************************************************************
 *
 *  Func Name  : GetHead
 *
 *  Description:  Get the head Element buffer and return the count of elements
 *              
 *    
 *  Returns    : the head of the array chain
 *********************************************************************/
PARRAY_CHAIN CDynamicArray::GetHead()
{
	return m_pHead;
}
/*********************************************************************
 *
 *  Func Name  : GetHead
 *
 *  Description:  Get the head Element buffer and return the count of elements
 *              
 *    
 *  Returns    : the head of the array chain
 *********************************************************************/
unsigned int CDynamicArray::GetTail(PARRAY_CHAIN *pTailRet)
{
    PARRAY_CHAIN pCur=m_pHead,pPrev=NULL;
	//pCur: current node;pPrev:previous node
	unsigned int nCount=0;
	while(pCur!=NULL)
	{
		nCount+=1;
		pPrev=pCur;
		pCur=pCur->next;
	}
	*pTailRet=pPrev;
	return nCount;
}
/*********************************************************************
 *
 *  Func Name  : GetTail
 *
 *  Description:  Get the tail Element buffer and return the count of elements
 *              
 *
 *  Parameters : pTailRet:the return array if found 
 *    
 *  Returns    : the count value if found,else Infinite value
 *********************************************************************/
bool CDynamicArray::SetRowFirst(bool RowFirst)
{
	m_bRowFirst=RowFirst;
	return true;
}
