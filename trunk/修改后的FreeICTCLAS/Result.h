

#if !defined(AFX_RESULT_H__DEB31BCA_0410_4D5E_97EA_78F9B16B8938__INCLUDED_)
#define AFX_RESULT_H__DEB31BCA_0410_4D5E_97EA_78F9B16B8938__INCLUDED_

#include "Dictionary.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Dictionary.h"
#include "Segment.h"
#include "Span.h"
#include "UnknowWord.h"
#define _ICT_DEBUG 0

class CResult  
{
public:
	double m_dSmoothingPara;
	bool Processing(char *sSentence,unsigned int nCount);
	bool ParagraphProcessing(char *sParagraph,char *sResult);
	PWORD_RESULT *m_pResult;
	ELEMENT_TYPE m_dResultPossibility[MAX_SEGMENT_NUM];
	int m_nResultCount;
	bool Output(PWORD_RESULT pItem,char *sResult,bool bFirstWordIgnore=false);
	CResult();
	virtual ~CResult();
	int m_nOperateType;//0:Only Segment;1: First Tag; 2:Second Type
	int m_nOutputFormat;//0:PKU criterion;1:973 criterion; 2: XML criterion
private:
	CSegment m_Seg;//Seg class
	CDictionary m_dictCore,m_dictBigram;//Core dictionary,bigram dictionary
	CSpan m_POSTagger;//POS tagger
	CUnknowWord m_uPerson,m_uTransPerson,m_uPlace;//Person recognition
protected:
	bool ChineseNameSplit(char *sPersonName,char *sSurname, char *sSurname2,char *sGivenName,CDictionary &personDict);
	bool Adjust(PWORD_RESULT pItem,PWORD_RESULT pItemRet);
	ELEMENT_TYPE ComputePossibility(PWORD_RESULT pItem);
	bool Sort();

};


#endif // !defined(AFX_RESULT_H__DEB31BCA_0410_4D5E_97EA_78F9B16B8938__INCLUDED_)
