

#if !defined(AFX_DYNAMICARRAY_H__C47E8C64_17A2_467F_8094_1DFDCC39A943__INCLUDED_)
#define AFX_DYNAMICARRAY_H__C47E8C64_17A2_467F_8094_1DFDCC39A943__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#define MIN_PROBLEM 1
#if MIN_PROBLEM==1//The shortest path
	#define INFINITE_VALUE 10000.00//infinite value
#else//The longest path
	#define INFINITE_VALUE 0.00//infinite value
#endif
#define ELEMENT_TYPE double//the type of element

//#define ROW_FIRST 0//Row first in the array store

struct tagArrayChain{
	unsigned int col,row;//row and column
    ELEMENT_TYPE value;//The value of the array
	int nPOS;
	int nWordLen;
	char *sWord;
	//The possible POS of the word related to the segmentation graph
    struct tagArrayChain *next;
};
typedef struct tagArrayChain ARRAY_CHAIN,*PARRAY_CHAIN;

class CDynamicArray  
{
public:
	bool SetRowFirst(bool RowFirst=true);
	unsigned int GetTail(PARRAY_CHAIN *pTailRet);
	//Get the tail Element buffer and return the count of elements
	PARRAY_CHAIN GetHead();
	//Get the head Element
	bool GetElement(int nRow, int nCol,ELEMENT_TYPE  *pRetValue,int *pRetPOS=0,char *sRetWord=0);
	void SetEmpty();
	CDynamicArray(bool bRowFirst=false);
	virtual ~CDynamicArray();
	const CDynamicArray & operator =(const CDynamicArray &);
	bool operator ==(const CDynamicArray &array);

	ELEMENT_TYPE GetElement( int nRow, int nCol,PARRAY_CHAIN pStart=0,PARRAY_CHAIN *pRet=0);
	int SetElement(unsigned int nRow, unsigned int nCol, ELEMENT_TYPE fValue,int nPOS,char *sWord=0);
	unsigned int m_nCol,m_nRow;//The row and col of the array
	bool m_bRowFirst;
private:
    PARRAY_CHAIN m_pHead;//The head pointer of array chain
};

#endif // !defined(AFX_DYNAMICARRAY_H__C47E8C64_17A2_467F_8094_1DFDCC39A943__INCLUDED_)
