
#if !defined(AFX_SPAN_H__178113DA_8D45_4D47_B6DA_CB62C001BC35__INCLUDED_)
#define AFX_SPAN_H__178113DA_8D45_4D47_B6DA_CB62C001BC35__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Dictionary.h"
#include "ContextStat.h"
#include "DynamicArray.h"
#define MAX_WORDS_PER_SENTENCE 120
#define MAX_UNKNOWN_PER_SENTENCE 200
#define MAX_POS_PER_WORD 20
#define LITTLE_FREQUENCY 6
enum TAG_TYPE{
		TT_NORMAL,
		TT_PERSON,
		TT_PLACE,
		TT_TRANS_PERSON
};
class CSpan  
{
public:
	void SetTagType(enum TAG_TYPE nType=TT_NORMAL);
	//Set the tag type
	bool LoadContext(char *sFilename);
	CSpan();//CDictionary &dict
	virtual ~CSpan();
	int m_nUnknownIndex;
	//The number of unknown word
	int m_nUnknownWords[MAX_UNKNOWN_PER_SENTENCE][2];
	//The start and ending possition of unknown position
	ELEMENT_TYPE m_dWordsPossibility[MAX_UNKNOWN_PER_SENTENCE];
	//The possibility of unknown words
	CContextStat m_context;//context

private:
	enum TAG_TYPE m_tagType;//The type of tagging
};
#endif // !defined(AFX_SPAN_H__178113DA_8D45_4D47_B6DA_CB62C001BC35__INCLUDED_)
