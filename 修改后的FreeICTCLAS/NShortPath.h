

#if !defined(AFX_NSHORTPATH_H__817D57F2_F3D8_40C8_A57E_20570862BCB3__INCLUDED_)
#define AFX_NSHORTPATH_H__817D57F2_F3D8_40C8_A57E_20570862BCB3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "DynamicArray.h"
#include "queue.h"
#include <stdio.h>
class CNShortPath  
{
public:
	int m_nResultCount;
	int Output(int **nResult,bool bBest,int *npCount);
	int ShortPath();
	CNShortPath(CDynamicArray *aCost,unsigned int nValueKind=1);
	virtual ~CNShortPath();
private:
	void GetPaths(unsigned int nNode,unsigned int nIndex,int **nResult=0,bool bBest=false);
	CDynamicArray *m_apCost;
    unsigned int m_nValueKind;//The number of value kinds
    unsigned int m_nVertex;//The number of vertex in the graph
	CQueue   **m_pParent;//The 2-dimension array for the nodes
	ELEMENT_TYPE **m_pWeight;//The weight of node
};

#endif // !defined(AFX_NSHORTPATH_H__817D57F2_F3D8_40C8_A57E_20570862BCB3__INCLUDED_)
