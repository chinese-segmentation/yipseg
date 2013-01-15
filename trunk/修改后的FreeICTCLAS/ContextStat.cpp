

#include "ContextStat.h"
#include "Utility.h"
#include <memory.h>
#include <stdio.h>
#include <string.h>


CContextStat::CContextStat()
{
	m_pSymbolTable=0;//new buffer for symbol
	m_pContext=0;//init with empty
}
CContextStat::~CContextStat()
{
	delete [] m_pSymbolTable;
	PMYCONTEXT pCur=m_pContext,pTemp;
	while(pCur!=NULL)
	{//delete the context array
		pTemp=pCur->next;
		for(int i=0;i<m_nTableLen;i++)
		   delete [] pCur->aContextArray[i];
		delete [] pCur->aContextArray;
		delete [] pCur->aTagFreq;
		delete pCur;
		pCur=pTemp;
	}
	
}

/*********************************************************************
 *
 *  Func Name  : Add
 *
 *  Description: Add the context symbol to the array
 *              
 *
 *  Parameters : nKey:the key of the node
 *               nPrevSymbol:the symbol of previous node
 *               nCurSymbol:the symbol of current node
 *               nFrequency:the frequerncy of the node
 *
 *  Returns    : success or fail
 *
 *********************************************************************/
bool CContextStat::Add(int nKey, int nPrevSymbol, int nCurSymbol, int nFrequency)
{//Add the context symbol to the array
	PMYCONTEXT pRetItem,pNew;
	int nPrevIndex,nCurIndex;
    if(!GetItem(nKey,&pRetItem))//Not get it
	{
		pNew=new MYCONTEXT;
		pNew->nKey=nKey;
		pNew->nTotalFreq=0;
		pNew->next=NULL;
		pNew->aContextArray=new int*[m_nTableLen];
		pNew->aTagFreq=new int[m_nTableLen];
		memset(pNew->aTagFreq,0,sizeof(int)*m_nTableLen);
		for(int i=0;i<m_nTableLen;i++)
		{//new buffer for every dimension
			pNew->aContextArray[i]=new int[m_nTableLen];
			memset(pNew->aContextArray[i],0,sizeof(int)*m_nTableLen);//Init the frequency
		}
		if(pRetItem==NULL)//Empty, the new item is head
			m_pContext=pNew;
		else//Link the new item between pRetItem and its next item
		{
			pNew->next=pRetItem->next;
			pRetItem->next=pNew;
		}
		pRetItem=pNew;
	}
	nPrevIndex=BinarySearch(nPrevSymbol,m_pSymbolTable,m_nTableLen);
	if(nPrevSymbol>256&&nPrevIndex==-1)//Not find, just for 'nx' and other uncommon POS
		nPrevIndex=BinarySearch(nPrevSymbol-nPrevSymbol%256,m_pSymbolTable,m_nTableLen);
	
	nCurIndex=BinarySearch(nCurSymbol,m_pSymbolTable,m_nTableLen);
	if(nCurSymbol>256&&nCurIndex==-1)//Not find, just for 'nx' and other uncommon POS
		nCurIndex=BinarySearch(nCurSymbol-nCurSymbol%256,m_pSymbolTable,m_nTableLen);
    if(nPrevIndex==-1||nCurIndex==-1)//error finding the symbol
		return false;
	pRetItem->aContextArray[nPrevIndex][nCurIndex]+=nFrequency;//Add the frequency
	pRetItem->aTagFreq[nPrevIndex]+=nFrequency;
	pRetItem->nTotalFreq+=nFrequency;
	return true;
}

/*********************************************************************
 *
 *  Func Name  : Load
 *
 *  Description: to get the context
 *              
 *
 *  Parameters : sFilename:the name of file to load
 *
 *  Returns    : success or fail
 *
 *********************************************************************/
bool CContextStat::Load(char *sFilename)
{
	FILE *fp;
	if((fp=fopen(sFilename,"rb"))==NULL)
	{
		return false;
	}
	PMYCONTEXT pCur=m_pContext,pTemp,pPre=NULL;
	while(pCur!=NULL)
	{//delete the context array
		pTemp=pCur->next;
		for(int i=0;i<m_nTableLen;i++)
		   delete [] pCur->aContextArray[i];
		delete [] pCur->aContextArray;
		delete [] pCur->aTagFreq;
		delete pCur;
		pCur=pTemp;
	}

	fread(&m_nTableLen,sizeof(m_nTableLen),1,fp);//write the table length
	if(m_pSymbolTable!=NULL)
		delete [] m_pSymbolTable;
	m_pSymbolTable=new int[m_nTableLen];//new buffer for symbol
	fread(m_pSymbolTable,sizeof(int),m_nTableLen,fp);//write the symbol table
    //free exists items
    while(!feof(fp))
	{//Read the context 
		pCur=new MYCONTEXT;
		pCur->next=NULL;
		if(fread(&pCur->nKey,sizeof(int),1,fp)<1)//Read error
		{
			delete pCur;
			break;
		}
        fread(&pCur->nTotalFreq,sizeof(int),1,fp);
		pCur->aTagFreq=new int [m_nTableLen];
		fread(pCur->aTagFreq,sizeof(int),m_nTableLen,fp);//the every POS frequency
		
		pCur->aContextArray=new int *[m_nTableLen];
        for(int i=0;i<m_nTableLen;i++)
		{
		    pCur->aContextArray[i]=new int[m_nTableLen];
			fread(pCur->aContextArray[i],sizeof(int),m_nTableLen,fp);
		}
		if(pPre==NULL)
			m_pContext=pCur;
		else
			pPre->next=pCur;
		pPre=pCur;
	}
	fclose(fp);
	return true;
}
/*********************************************************************
 *
 *  Func Name  : GetContextPossibility
 *
 *  Description: get the possibility of the  context
 *              
 *
 *  Parameters : nKey:the key of the node
 *               nPrev:the previous node
 *               nCur:the current node
 *
 *  Returns    : the possibility of the context
 *
 *********************************************************************/
double CContextStat::GetContextPossibility(int nKey, int nPrev, int nCur)
{
	PMYCONTEXT pCur;
	int nCurIndex=BinarySearch(nCur,m_pSymbolTable,m_nTableLen);
	int nPrevIndex=BinarySearch(nPrev,m_pSymbolTable,m_nTableLen);
	if(!GetItem(nKey,&pCur)||nCurIndex==-1||nPrevIndex==-1||pCur->aTagFreq[nPrevIndex]==0||pCur->aContextArray[nPrevIndex][nCurIndex]==0)
		return 0.000001;//return a lower value, not 0 to prevent data sparse
	int nPrevCurConFreq=pCur->aContextArray[nPrevIndex][nCurIndex];
	int nPrevFreq=pCur->aTagFreq[nPrevIndex];
	return 0.9*(double)nPrevCurConFreq/(double)nPrevFreq+0.1*(double)nPrevFreq/(double)pCur->nTotalFreq;
	//0.9 and 0.1 is a value based experience
}

/*********************************************************************
 *
 *  Func Name  : GetFrequency
 *
 *  Description: get the frequency of a symbol
 *              
 *
 *  Parameters : nKey:the key of the node
 *               nSymbol:the symbol of the node
 *
 *  Returns    : the frequency of the symbol
 *
 *********************************************************************/
int CContextStat::GetFrequency(int nKey, int nSymbol)
{//Get the frequency which nSymbol appears
	PMYCONTEXT pFound;
	int nIndex,nFrequency=0;
	if(!GetItem(nKey,&pFound))//Not found such a item
		return 0;
	nIndex=BinarySearch(nSymbol,m_pSymbolTable,m_nTableLen);
    if(nIndex==-1)//error finding the symbol
		return 0;
	nFrequency=pFound->aTagFreq[nIndex];//Add the frequency
	return nFrequency;
}

/*********************************************************************
 *
 *  Func Name  : GetItem
 *
 *  Description: Get the item according the nKey 
 *              
 *
 *  Parameters : nKey:the key of the node
 *               pItemRet:the pointer of the node
 *
 *  Returns    : success or fail
 *
 *********************************************************************/
bool CContextStat::GetItem(int nKey,PMYCONTEXT *pItemRet)
{//Get the item according the nKey
	PMYCONTEXT pCur=m_pContext,pPrev=NULL;
	if(nKey==0&&m_pContext)
	{
		*pItemRet=m_pContext;
		return true;
	}
	while(pCur!=NULL&&pCur->nKey<nKey)
	{//delete the context array
		pPrev=pCur;
		pCur=pCur->next;
	}
    if(pCur!=NULL&&pCur->nKey==nKey)
	{//find it and return the current item
		*pItemRet=pCur;
		return true;
	}
	*pItemRet=pPrev;
	return false;
}



