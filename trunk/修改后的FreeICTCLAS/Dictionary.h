
#if !defined(AFX_DICTIONARY_H__80E88BC1_784E_4C96_868B_D7CD66DD6725__INCLUDED_)
#define AFX_DICTIONARY_H__80E88BC1_784E_4C96_868B_D7CD66DD6725__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define CC_NUM  6768
//The number of Chinese Char,including 5 empty position between 3756-3761
#define WORD_MAXLENGTH 100
#define WT_DELIMITER 0
#define WT_CHINESE   1
#define WT_OTHER     2
#define CC_ID(c1,c2) ((unsigned char)(c1)-176)*94+((unsigned char)(c2)-161)
//The ID equation of Chinese Char 
#define CC_CHAR1(id) (id)/94+176
//The first char computed by the Chinese Char ID
#define CC_CHAR2(id) (id)%94+161

struct tagWordResult{
	char sWord[WORD_MAXLENGTH];
	//The word 
	int nHandle;
	//the POS of the word
	double  dValue;
	//The -log(frequency/MAX)
};
typedef struct tagWordResult WORD_RESULT,*PWORD_RESULT;

/*data structure for word item*/
struct tagWordItem{
	int nWordLen;
	char *sWord;
	//The word 
	int nHandle;
	//the process or information handle of the word
	int  nFrequency;
	//The count which it appear
};
typedef struct tagWordItem WORD_ITEM,*PWORD_ITEM;
/*data structure for dictionary index table item*/
struct tagIndexTable{
    int nCount;
	//The count number of words which initial letter is sInit
    PWORD_ITEM pWordItemHead;
	//The  head of word items
};
typedef struct tagIndexTable INDEX_TABLE;

/*data structure for word item chain*/
struct tagWordChain{
       WORD_ITEM data;
       struct tagWordChain *next;
};
typedef struct tagWordChain WORD_CHAIN,*PWORD_CHAIN;
/*data structure for dictionary index table item*/
struct tagModifyTable{
    int nCount;
	//The count number of words which initial letter is sInit
	int nDelete;
    //The number of deleted items in the index table
	PWORD_CHAIN pWordItemHead;
	//The  head of word items
};
typedef struct tagModifyTable MODIFY_TABLE,*PMODIFY_TABLE;

class CDictionary  
{
public:
	bool Optimum();
	bool Merge(CDictionary dict2,int nRatio);
	bool OutputChars(char *sFilename);
	bool Output(char *sFilename);
	int GetFrequency(char *sWord,  int nHandle);
	bool GetPOSString(int nPOS,char *sPOSRet);
	int GetPOSValue(char *sPOS);
	bool GetMaxMatch(char *sWord, char *sWordRet, int *npHandleRet);
	bool MergePOS(int nHandle);
	bool GetHandle(char *sWord,int *pnCount,int *pnHandle,int *pnFrequency);
	bool IsExist(char *sWord,int nHandle);
	bool AddItem(char *sWord,int nHandle,int nFrequency=0);
	bool DelItem(char *sWord,int nHandle);
	bool Save(char *sFilename);
	bool Load(char *sFilename,bool bReset=false);
	int  GetWordType(char *sWord);
	bool PreProcessing(char *sWord,int *nId,char *sWordRet,bool bAdd=false);
	CDictionary();
    virtual ~CDictionary();
	INDEX_TABLE   m_IndexTable[CC_NUM];
    PMODIFY_TABLE m_pModifyTable;
	//The data for modify  
protected:
	bool DelModified();
	bool FindInOriginalTable(int nInnerCode,char *sWord,int nHandle,int *nPosRet=0);
	bool FindInModifyTable(int nInnerCode,char *sWord,int nHandle,PWORD_CHAIN *pFindRet=0);
};

#endif // !defined(AFX_DICTIONARY_H__80E88BC1_784E_4C96_868B_D7CD66DD6725__INCLUDED_)
