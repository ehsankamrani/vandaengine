//
//           xmlparse
//           by: s melax 
// 
// A simple parser for loading
// valid xml into a useful tree data structure.
// See the .cpp file for details.
//

#ifndef SM_XMLPARSE_H
#define SM_XMLPARSE_H

#include "array.h"
#include "stringclass.h"
#include "hash.h"


class XMLElement
{
public:
	String tag;
	Hash<String,String> attributes;  // normally this is used for any "metadata" (info about the data, not the data itself)
	Array<XMLElement*> children;
	String body;
	void *data;
	String ctype;
	int   count;
	XMLElement *Child(String s){for(int i=0;i<children.count;i++)if(s==children[i]->tag)return children[i];return NULL;}
	XMLElement(char *_tag):tag(_tag),data(NULL){}
	XMLElement():data(NULL),ctype(NULL),count(0){}
	~XMLElement();
};


XMLElement *XMLParseFile(const char *filename);
void        XMLSaveFile(XMLElement *elem,const char *filename);
unsigned char *Linearize(void *root,int l,int r,int size,char *ctype,int *pnum);

int CalcSize(const char *ctype);
unsigned char *AscToBin(const char *ascii_data,const int count,const char *ctype,void *_data=NULL);
void *XMLExtractData(XMLElement *e);





// for loading and saving basic types from a C++ class.
inline char *ctype(const float&) {return "f";}
inline char *ctype(const int&)   {return "d";}

class ClassDesc;
extern Hash<String,ClassDesc*> classdesc;
class ClassDesc
{
public:
	String name;
	class memberdef
	{
	  public:
		char* name;
		char* ctype;
		int offset;
		int isarray;
		memberdef(){}
		memberdef(char *n,char* t,int o,int a=0):name(n),ctype(t),offset(o),isarray(a){}
	};
	Array<memberdef> members;
	ClassDesc(const String &_name);
	~ClassDesc();
};

#define ADDMEMBER(C,M)   classdesc[ ToLower(#C) ]->members.Add(ClassDesc::memberdef( #M , ctype(((C*)NULL)->M)   , OFFSET(C,M) )) ;
#define ADDMARRAY(C,M,T) classdesc[ ToLower(#C) ]->members.Add(ClassDesc::memberdef( #M , T , OFFSET(C,M) , 1)) ;
void *LoadMember(XMLElement *c,void *p,ClassDesc *d); // 
void *LoadClass(XMLElement *e,void *p,ClassDesc *d);  // reflection style loading of ascii xml into C++ class
XMLElement *SaveClass(void *base,ClassDesc *d);





#endif
