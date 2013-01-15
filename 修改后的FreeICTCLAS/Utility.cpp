

#include "Utility.h"
#include <stdio.h>
#include <string.h>

/*********************************************************************
 *
 *  Func Name  : CC_Find
 *
 *  Description: Find a Chinese sub-string in the Chinese String 
 *              
 *
 *  Parameters :  string:Null-terminated string to search
 *
 * 			      strCharSet:Null-terminated string to search for
 *
 *  Returns    : char *
 *********************************************************************/
char *CC_Find(const char *string, const char *strCharSet)
{
const char *cp=strstr(string,strCharSet);
char *dp;
dp=(char*)cp;
   if(cp!=NULL&&(cp-string)%2==1)
   {
	  return NULL;
   }
   return dp;
}
/*********************************************************************
 *
 *  Func Name  : charType
 *
 *  Description: Judge the type of sChar or (sChar,sChar+1)
 *              
 *
 *  Parameters : sFilename: the file name for the output CC List
 *    
 *  Returns    : int : the type of char
 *********************************************************************/
int charType(unsigned char *sChar)
{
  if(*sChar<128)
  {
	 if(strchr("\042!,.?()[]{}+=",(int)*sChar))
		 return CT_DELIMITER;
	 return CT_SINGLE;
  }
  else if(*sChar==162)
	  return CT_INDEX;
  else if(*sChar==163&&*(sChar+1)>175&&*(sChar+1)<186)
	  return CT_NUM;
  else if(*sChar==163&&(*(sChar+1)>=193&&*(sChar+1)<=218||*(sChar+1)>=225&&*(sChar+1)<=250))
	  return CT_LETTER;
  else if(*sChar==161||*sChar==163)
	  return CT_DELIMITER;
  else if(*sChar>=176&&*sChar<=247)
      return CT_CHINESE;
  else
      return CT_OTHER;
}
/*********************************************************************
 *
 *  Func Name  : IsAllChinese
 *
 *  Description: Judge the string is all made up of chinese char
 *              
 *
 *  Parameters : sSentence: the original sentence which includes Chinese or Non-Chinese char
 *    
 *  Returns    : success or fail 
 *********************************************************************/
bool IsAllChinese(unsigned char *sString)
{
	unsigned int nLen=strlen((const char *)sString),i=0;
	while(i<nLen-1&&sString[i]<248&&sString[i]>175)
	{
		i+=2;
	}
	if(i<nLen)
		return false;
	return true;
}
/*********************************************************************
 *
 *  Func Name  : IsAllSingleByte
 *
 *  Description: Judge the string is all made up of Single Byte Char
 *              
 *
 *  Parameters : sSentence: the original sentence which includes Chinese or Non-Chinese char
 *    
 *  Returns    : success or fail 
 *********************************************************************/
bool IsAllSingleByte(unsigned char *sString)
{
	unsigned int nLen=strlen((const char *)sString),i=0;
	while(i<nLen&&sString[i]<128)
	{
		i++;
	}
	if(i<nLen)
		return false;
	return true;
}
/*********************************************************************
 *
 *  Func Name  : IsAllNum
 *
 *  Description: Judge the string is all made up of Num Char
 *              
 *
 *  Parameters : sSentence: the original sentence which includes Chinese or Non-Chinese char
 *    
 *  Returns    : success or fail
 *********************************************************************/
bool IsAllNum(unsigned char *sString)
{

	unsigned int nLen=strlen((const char *)sString),i=0;
	char sChar[3];
	sChar[2]=0;
	if(i<nLen)//Get prefix such as + -
	{
		sChar[0]=sString[i++];
		if(sChar[0]<0)//Get first char
			sChar[1]=sString[i++];
		else
			sChar[1]=0;
		if(!strstr("±+—-＋",sChar))
		{
			i=0;
		}
	}
	while(i<nLen-1&&sString[i]==163&&sString[i+1]>175&&sString[i+1]<186)
	{
		i+=2;
	}
	if(i<nLen)//Get middle delimiter such as .
	{
		sChar[0]=sString[i++];
		if(sChar[0]<0)//Get first char
			sChar[1]=sString[i++];
		else
			sChar[1]=0;
		if(CC_Find("∶·．／",sChar)||sChar[0]=='.'||sChar[0]=='/')
		{//98．1％
			while(i<nLen-1&&sString[i]==163&&sString[i+1]>175&&sString[i+1]<186)
			{
				i+=2;
			}
		}	
		else
		{
			i-=strlen(sChar);
		}
	}

	if(i>=nLen)
		return true;
	while(i<nLen&&sString[i]>'0'-1&&sString[i]<'9'+1)
	{//single byte number char
		i+=1;
	}
	if(i<nLen)//Get middle delimiter such as .
	{
		sChar[0]=sString[i++];
		if(sChar[0]<0)//Get first char
			sChar[1]=sString[i++];
		else
			sChar[1]=0;
		if(CC_Find("∶·．／",sChar)||sChar[0]=='.'||sChar[0]=='/')
		{//98．1％
			while(i<nLen&&sString[i]>'0'-1&&sString[i]<'9'+1)
			{
				i+=1;
			}
		}	
		else
		{
			i-=strlen(sChar);
		}
	}
	if(i<nLen)//Get middle delimiter such as .
	{
		sChar[0]=sString[i++];
		if(sChar[0]<0)//Get first char
			sChar[1]=sString[i++];
		else
			sChar[1]=0;
		if(!CC_Find("百千万亿佰仟％‰",sChar)&&sChar[0]!='%')
			i-=strlen(sChar);
	}
	if(i>=nLen)
		return true;
	return false;
}
/*********************************************************************
 *
 *  Func Name  : BinarySearch
 *
 *  Description: Lookup the index of nVal in the table nTable which length is nTableLen
 *
 *  Parameters : nPOS: the POS value
 *
 *  Returns    : the index value
 *********************************************************************/
int BinarySearch(int nVal, int *nTable,int nTableLen)
{
	int nStart=0,nEnd=nTableLen-1,nMid=(nStart+nEnd)/2;
	while(nStart<=nEnd)//Binary search
	{
       if(nTable[nMid]==nVal)
	   {
			return nMid;//find it
	   }
	   else if(nTable[nMid]<nVal)
	   {
		   nStart=nMid+1;
	   }
	   else
       {
		   nEnd=nMid-1;
	   }
	   nMid=(nStart+nEnd)/2;
	}
	return -1;//Can not find it;
}
/*********************************************************************
 *
 *  Func Name  : IsAllChineseNum
 *
 *  Description: Decide whether the word is Chinese Num word
 *
 *  Parameters : sWord: the word
 *
 *  Returns    : success or fail
 *********************************************************************/
bool IsAllChineseNum(char *sWord)
{
  unsigned int  k; 
  char tchar[3];
  char ChineseNum[]="零○一二两三四五六七八九十廿百千万亿壹贰叁肆伍陆柒捌玖拾佰仟∶·．／点";//
  char sPrefix[]="几数第上成";
  for(k = 0; k < strlen(sWord); k+=2)
  {
     strncpy(tchar,sWord+k,2) ;
     tchar[2]='\0';
	 if(strncmp(sWord+k,"分之",4)==0)//百分之五
	 {
		k+=2;
		continue;
	 }

	 if(!CC_Find(ChineseNum, tchar)&&!(k==0&&CC_Find(sPrefix, tchar)))
		 return false;
  }
  return true;
}
/*********************************************************************
 *
 *  Func Name  : GetForeignCharCount
 *
 *  Description: Get the cout of the foreign name which may be a foreign name 
 *
 *  Parameters : sWord: the word
 *
 *  Returns    : count
 *********************************************************************/
int GetForeignCharCount(char *sWord)
{
  unsigned int nForeignCount,nCount;
  nForeignCount=GetCharCount(TRANS_ENGLISH,sWord);//English char counnts
  nCount=GetCharCount(TRANS_JAPANESE,sWord);//Japan char counnts
  if(nForeignCount<=nCount)
	nForeignCount=nCount;
  nCount=GetCharCount(TRANS_RUSSIAN,sWord);//Russian char counnts
  if(nForeignCount<=nCount)
	nForeignCount=nCount;
  return nForeignCount;
}
/*********************************************************************
 *
 *  Func Name  : GetCharCount
 *
 *  Description: Get the count of char which is in sWord and in sCharSet
 *
 *  Parameters : sWord: the word
 * 
 *  Returns    : COUNT
 *********************************************************************/
int GetCharCount(char *sCharSet,char *sWord)
{
  unsigned int  k=0; 
  char tchar[3];
  int nCount=0;
  tchar[2]=0;
  while(k < strlen(sWord))
  {
     tchar[0]=sWord[k];
 	 tchar[1]=0;
	 if(sWord[k]<0)
	 {
		 tchar[1]=sWord[k+1];
		 k+=1;
	 }
	 k+=1;
	 if((tchar[0]<0&&CC_Find(sCharSet, tchar))||strchr(sCharSet,tchar[0]))
          nCount++;
  }
  return nCount;
}
