#include <stdio.h>
#include <string.h>
#include "ICTCLAS.h"
#include "Result.h"

CResult m_ICTCLAS;
CDictionary m_DICTIONARY;

bool ParagraphProcessings(char*paragraph,char*result)
{
	char * sResult;
    sResult=new char[(strlen(paragraph)+13)*50];
	if(!m_ICTCLAS.ParagraphProcessing(paragraph,sResult))
           strcpy(result," 错误：程序初始化异常！");
	else
           strcpy(result,sResult);
	delete [] sResult;
	return true;
}


bool AddItem(char *word,char *POS,int fruenqucy)
{
	//获取word的词性
	int handle = m_DICTIONARY.GetPOSValue(POS);
	bool result=false;
	result = m_DICTIONARY.AddItem(word,handle,fruenqucy);
	return result;
}

bool DelItem(char *word,char *POS)
{
 bool result = false;
 int handle =m_DICTIONARY.GetPOSValue(POS);
 result =m_DICTIONARY.DelItem(word,handle);
 return result;

}
bool Save(char *sFilename){
	return m_DICTIONARY.Save(sFilename);
}

bool Load(char *sFilename)
{
	return m_DICTIONARY.Load(sFilename);
}
