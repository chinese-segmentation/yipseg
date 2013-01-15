extern "C" bool ParagraphProcessings(char*paragraph,char*result);
extern "C" bool AddItem(char *word,char *POS,int fruenqucy);
extern "C" bool DelItem(char *word,char *POS);
extern "C" bool Save(char *sFilename);
extern "C" bool Load(char *sFilename);