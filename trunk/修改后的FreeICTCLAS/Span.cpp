


#include "Span.h"
#include "Segment.h"
#include "Utility.h"
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

CSpan::CSpan()
{
	m_tagType=TT_NORMAL;//Default tagging type
}

CSpan::~CSpan()
{
}

/*********************************************************************
 *
 *  Func Name  : LoadContext
 *
 *  Description: Load the context file
 *              
 *
 *  Parameters : sFilename: the file name
 *
 *  Returns    : success or fail
 *
 *********************************************************************/
bool CSpan::LoadContext(char *sFilename)
{
	return m_context.Load(sFilename);
}



/*********************************************************************
 *
 *  Func Name  : SetTagType
 *
 *  Description: Set the tag type
 *              
 *
 *  Parameters : nType: the word type
 *
 *  Returns    : success or fail
 *
 *********************************************************************/
void CSpan::SetTagType(enum TAG_TYPE  nType)
{
	m_tagType=nType;
}


