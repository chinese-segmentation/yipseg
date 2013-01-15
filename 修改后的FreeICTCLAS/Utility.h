
#if !defined(AFX_CHINESE_UTILITY_H__B6D7EA03_7BCD_46AD_B38C_D8033ACD5813__INCLUDED_)
#define AFX_CHINESE_UTILITY_H__B6D7EA03_7BCD_46AD_B38C_D8033ACD5813__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define  CT_SENTENCE_BEGIN 1//Sentence begin 
#define  CT_SENTENCE_END   4//Sentence ending
#define  CT_SINGLE  5//SINGLE byte
#define  CT_DELIMITER CT_SINGLE+1//delimiter
#define  CT_CHINESE   CT_SINGLE+2//Chinese Char
#define  CT_LETTER    CT_SINGLE+3//HanYu Pinyin
#define  CT_NUM       CT_SINGLE+4//HanYu Pinyin
#define  CT_INDEX     CT_SINGLE+5//HanYu Pinyin
#define  CT_OTHER     CT_SINGLE+12//Other
#define POSTFIX_SINGLE "�Ӱ���ǳش嵥�����̵궴�ɶӷ��帮�Ը۸󹬹������źӺ������������ǽ־����ӿڿ�����¥·������Ū����������������Ȫ��ɽʡ��ˮ����̨̲̳����ͤ��������ϪϿ������������ҤӪ����԰ԷԺբկվ����ׯ�������"
#define POSTFIX_MUTIPLE {"�뵺","��ԭ","����","���","�󹫹�","����","����","�۹�","�ɲ�","�ۿ�","���ٹ�·","��ԭ","��·","��԰","���͹�","�ȵ�","�㳡","����","��Ͽ","��ͬ","����","����","����","�ֵ�","�ڰ�","��ͷ","ú��","����","ũ��","���","ƽԭ","����","Ⱥ��","ɳĮ","ɳ��","ɽ��","ɽ��","ˮ��","���","����","��·","�´�","ѩ��","�γ�","�κ�","�泡","ֱϽ��","������","������","������",""}
                          
#define  TRANS_ENGLISH   "�������������������°İʰŰͰװݰ������������ȱϱ˱𲨲��������������Ųɲֲ��񳹴��Ĵȴδ����������������µõĵǵϵҵٵ۶����Ŷض����������������Ʒҷѷ�򸣸������ǸɸԸ���������ŹϹ��������������ϺӺպ����������������Ӽּ��ܽ𾩾þӾ��������������¿ƿɿ˿Ͽ����������������������������������������������������������¡¬²³·��������������������éï÷����������������ĦĪīĬķľ������������������������ŦŬŵŷ��������������Ƥƽ��������ǡǿ��������Ȫ��������������������ɣɪɭɯɳɽ������ʥʩʫʯʲʷʿ��˹˾˿��������̩̹����������͡ͼ������������������Τάκ��������������������ϣϲ������Ъл������������ҢҶ��������������ӢӺ����Լ������ղ������������׿������٤��������üν�����������Ľ����������������ɺ����ѷ��������ܽ���������������"
#define  TRANS_RUSSIAN   "�������°ͱȱ˲�����Ĵ�µö��Ŷ���������Ǹ�����Ӽ�ݽ𿨿ƿɿ˿���������������������¬³������÷����ķ������ŵ������������������ɫɽ��ʲ˹����̹������ά������ϣл��ҮҶ�������������ǵٸ�����ջ������������������������������ɣɳ��̩ͼ������׿��"
#define  TRANS_JAPANESE  "���°˰װٰ�������ȱ��������ʲ˲ֲ������سന�����δ����������µص�ɶ������縣�Ը߹����Źȹع���úƺͺϺӺں���󻧻Ļ漪�ͼѼӼ�������������������þƾտ����ɿ˿�����������������������������¡¹������������ľ��������������Ƭƽ����ǧǰǳ����������������Ȫ������������ɭɴɼɽ��������ʥʯʵʸ������ˮ˳˾��̩��������������βδ����������ϸ������СТ����������������������ңҰҲҶһ����������ӣ��������������ԨԪԫԭԶ����������������լ����������ֲ֦֪֮��������������׵��������ܥݶ��޹������"
//Translation type
#define  TT_ENGLISH  0
#define  TT_RUSSIAN  1
#define  TT_JAPANESE  2
//Seperator type
#define  SEPERATOR_C_SENTENCE "������������"
#define  SEPERATOR_C_SUB_SENTENCE "����������������"
#define  SEPERATOR_E_SENTENCE "!?:;"
#define  SEPERATOR_E_SUB_SENTENCE ",()\042'"
#define  SEPERATOR_LINK "\n\r ��"
//Sentence begin and ending string
#define SENTENCE_BEGIN "ʼ##ʼ"
#define SENTENCE_END "ĩ##ĩ"
//Seperator between two words
#define WORD_SEGMENTER "@" 


char *CC_Find(const char *string, const char *strCharSet);
//Find a Chinese sub-string in the Chinese String 
int charType(unsigned char *sChar);
//Judge the type of sChar or (sChar,sChar+1)
bool IsAllChinese(unsigned char *sString);
//Judge the string is all made up of Chinese Char
bool IsAllSingleByte(unsigned char *sString);
//Judge the string is all made up of Single Byte Char
bool IsAllNum(unsigned char *sString);
//Judge the string is all made up of Num Char
int BinarySearch(int nVal, int *nTable,int nTableLen);
//Binary search a value in a table which len is nTableLen
bool IsAllChineseNum(char *sWord);
//Decide whether the word is Chinese Num word
int GetForeignCharCount(char *sWord);
//Decide whether the word is all  non-foreign translation
int GetCharCount(char *sCharSet,char *sWord);
//Get the count of char which is in sWord and in sCharSet


#endif // !defined(AFX_CHINESE_UTILITY_H__B6D7EA03_7BCD_46AD_B38C_D8033ACD5813__INCLUDED_)
