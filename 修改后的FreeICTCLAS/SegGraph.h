

#if !defined(AFX_SEGGRAPH_H__E051AD07_F18C_4171_94D6_39742104EB62__INCLUDED_)
#define AFX_SEGGRAPH_H__E051AD07_F18C_4171_94D6_39742104EB62__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Dictionary.h"//Dictionary
#include "DynamicArray.h"//Dynamic array
#define MAX_FREQUENCE   2079997//7528283+329805  //1993123+86874 
#define MAX_SENTENCE_LEN 2000

class CSegGraph  
{
public:
	bool GenerateWordNet(char *sSentence,CDictionary &dictCore,bool	bOriginalFreq=false);
	CSegGraph();
	virtual ~CSegGraph();
	char m_sAtom[MAX_SENTENCE_LEN][WORD_MAXLENGTH];//pAtoms: the buffer for returned segmented atoms
	int m_nAtomLength[MAX_SENTENCE_LEN];//Save the individual length of atom in the array
	int m_nAtomPOS[MAX_SENTENCE_LEN];//pAtoms: the POS property 
	unsigned int m_nAtomCount;//The count of atoms
	CDynamicArray m_segGraph;	
protected:
	bool AtomSegment(char *sSentence);

};

#endif // !defined(AFX_SEGGRAPH_H__E051AD07_F18C_4171_94D6_39742104EB62__INCLUDED_)
