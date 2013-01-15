

#if !defined(AFX_CONTEXTSTAT_H__DA515FDC_F8F9_48F6_B25D_D2B91011528B__INCLUDED_)
#define AFX_CONTEXTSTAT_H__DA515FDC_F8F9_48F6_B25D_D2B91011528B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
struct tagContext{
	int nKey;//The key word
	int **aContextArray;//The context array
	int *aTagFreq;//The total number a tag appears
	int nTotalFreq;//The total number of all the tags
	struct tagContext *next;//The chain pointer to next Context
};
typedef struct tagContext MYCONTEXT,*PMYCONTEXT;
class CContextStat  
{
public:
	int GetFrequency(int nKey,int nSymbol);
	double GetContextPossibility(int nKey,int nPrev,int nCur);
	bool Load(char *sFilename);
	bool Add(int nKey,int nPrevSymbol,int nCurrentSymbol,int nFrequency);
	CContextStat();
	virtual ~CContextStat();
private:
	int m_nTableLen;
	int *m_pSymbolTable;
	PMYCONTEXT m_pContext;
	//int m_nCategory;
protected:
	bool GetItem(int nKey,PMYCONTEXT *pItemRet);
};

#endif // !defined(AFX_CONTEXTSTAT_H__DA515FDC_F8F9_48F6_B25D_D2B91011528B__INCLUDED_)
