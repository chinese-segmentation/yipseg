


#include "UnknowWord.h"
#include <string.h>
#include <math.h>

CUnknowWord::CUnknowWord()
{
	m_sUnknownFlags[0]=0;
}
CUnknowWord::~CUnknowWord()
{

}
/*********************************************************************
 *
 *  Func Name  : Recognition
 *
 *  Description: Unknown word recognition
 *              
 *
 *  Parameters :pWordSegResult:word Segmentation result;
 *              graphOptimum: The optimized segmentation graph
 *              graphSeg: The original segmentation graph
 *              dictCore: the core dictionary
 *
 *  Returns    : success or fail
 *
 *********************************************************************/
bool CUnknowWord::Recognition(PWORD_RESULT pWordSegResult, CDynamicArray &graphOptimum,CSegGraph &graphSeg,CDictionary &dictCore)
{	
	int nStartPos=0,j=0,nAtomStart,nAtomEnd,nPOSOriginal;
	ELEMENT_TYPE dValue;

	for(int i=0;i<m_roleTag.m_nUnknownIndex;i++)
	{
		while((unsigned int)j<graphSeg.m_nAtomCount&&nStartPos<m_roleTag.m_nUnknownWords[i][0])
		{
			nStartPos+=graphSeg.m_nAtomLength[j++];
		}
		nAtomStart=j;
		while((unsigned int)j<graphSeg.m_nAtomCount&&nStartPos<m_roleTag.m_nUnknownWords[i][1])
		{
			nStartPos+=graphSeg.m_nAtomLength[j++];
		}
		nAtomEnd=j;
		if(nAtomStart<nAtomEnd)
		{
			graphOptimum.GetElement(nAtomStart,nAtomEnd,&dValue,&nPOSOriginal);
			if(dValue>m_roleTag.m_dWordsPossibility[i])//Set the element with less frequency
				graphOptimum.SetElement(nAtomStart,nAtomEnd,m_roleTag.m_dWordsPossibility[i],m_nPOS,m_sUnknownFlags);
		}
	}
	return true;
}
/*********************************************************************
 *
 *  Func Name  : Configure
 *
 *  Description: Load unknown recognition dictionary
 *              
 *
 *  Parameters : sConfigFile:the file name 
 *               type: Unknown words type 
 *  Returns    : success or fail
 *********************************************************************/
bool CUnknowWord::Configure(char *sConfigFile,enum TAG_TYPE type)
{
	char sFilename[100];
	strcpy(sFilename,sConfigFile);
	strcat(sFilename,".dct");
	m_dict.Load(sFilename);
	strcpy(sFilename,sConfigFile);
	strcat(sFilename,".ctx");
	m_roleTag.LoadContext(sFilename);
	m_roleTag.SetTagType(type);
	switch(type)
	{
		case TT_PERSON:
		case TT_TRANS_PERSON://Set the special flag for transliterations
			m_nPOS=-28274;//-'n'*256-'r';
			strcpy(m_sUnknownFlags,"Î´##ÈË");
			break;
		case TT_PLACE:
			m_nPOS=-28275;//-'n'*256-'s';
			strcpy(m_sUnknownFlags,"Î´##µØ");
			break;
		default :
			m_nPOS=0;
			break;
	}
	return true;
}

/*********************************************************************
 *
 *  Func Name  : IsGivenName
 *
 *  Description: Judge whether the name is a given name
 *              
 *
 *  Parameters : sName: the name string
 *
 *  Returns    : success or fail
 *
 *********************************************************************/
bool CUnknowWord::IsGivenName(char *sName)
{
	char sFirstChar[3],sSecondChar[3];
	ELEMENT_TYPE dGivenNamePossibility=0,dSingleNamePossibility=0;
	if(strlen(sName)!=4)
		return false;		
	strncpy(sFirstChar,sName,2);
	sFirstChar[2]=0;
	strncpy(sSecondChar,sName+2,2);
	sSecondChar[2]=0;
	dGivenNamePossibility+=log((double)m_dict.GetFrequency(sFirstChar,2)+1.0)-log(m_roleTag.m_context.GetFrequency(0,2)+1.0);
	dGivenNamePossibility+=log((double)m_dict.GetFrequency(sSecondChar,3)+1.0)-log(m_roleTag.m_context.GetFrequency(0,3)+1.0);
	dGivenNamePossibility+=log(m_roleTag.m_context.GetContextPossibility(0,2,3)+1.0)-log(m_roleTag.m_context.GetFrequency(0,2)+1.0);
	dSingleNamePossibility+=log((double)m_dict.GetFrequency(sFirstChar,1)+1.0)-log(m_roleTag.m_context.GetFrequency(0,1)+1.0);
	dSingleNamePossibility+=log((double)m_dict.GetFrequency(sSecondChar,4)+1.0)-log(m_roleTag.m_context.GetFrequency(0,4)+1.0);
	//The possibility of conversion from 1 to 4
	dSingleNamePossibility+=log(m_roleTag.m_context.GetContextPossibility(0,1,4)+1.0)-log(m_roleTag.m_context.GetFrequency(0,1)+1.0);
	if(dSingleNamePossibility>=dGivenNamePossibility)
		return false;
	return true;
}
