//
//      String
//
// More convenient than using character arrays (char*). 
// Its your typical String class - nuff said.
//
//
//

#ifndef SM_STRING_H
#define SM_STRING_H

#include <stdio.h>
#include <string.h>

class String {
  public:
	char *buf;
				String();
				String(const String &t);
				String(const char *s);
				String(char *s,int len);
				String(const int a);
				String(const float a);
				~String();
	String &	operator =(const String &s);
	String &	operator =(const char *s);
	String &	operator+=(const String &b);
	String &	sprintf(char *format,...);
	char &		operator[](int i);
				operator const char *() const{ return buf;}
				operator char *() { return buf;}
	String &	DropFirstChars(char *delimeter=" \t");
	void		writeto(int &a) const;
	void		writeto(float &a) const;
	void		writeto(String &a) const;
	int			Asint() const;
	float		Asfloat() const;
	//String &	operator =(int a){char tmp[16];sprintf(tmp,"%d",a);*this=tmp;return *this;}
	//String &	operator =(float f){char tmp[16];sprintf(tmp,"%f",f);*this=tmp;return *this;}
	//String &	operator =(float3 v){char tmp[32];sprintf(tmp,"%f %f %f",v.x,v.y,v.z);*this=tmp;return *this;}
};

String operator+(const String &a,const String &b);

int operator==(const String &a,const String &b);
int operator!=(const String &a,const String &b);
int operator> (const String &a,const String &b);
int operator< (const String &a,const String &b);
int operator>=(const String &a,const String &b);
int operator<=(const String &a,const String &b);
int operator==(const String &a,const char   *b);
int operator!=(const String &a,const char   *b);
int operator> (const String &a,const char   *b);
int operator< (const String &a,const char   *b);
int operator>=(const String &a,const char   *b);
int operator<=(const String &a,const char   *b);
int operator==(const char   *a,const String &b);
int operator!=(const char   *a,const String &b);
int operator> (const char   *a,const String &b);
int operator< (const char   *a,const String &b);
int operator>=(const char   *a,const String &b);
int operator<=(const char   *a,const String &b);

int    IsOneOf(const char c,const char *s);  // iff s contains a c
const char*  SkipChars(const char *s,const char *delimeter=" \t");
const char*  SkipToChars(const char *s,const char *tokens);
char*  SkipChars(char *s,const char *delimeter=" \t");
char*  SkipToChars(char *s,const char *tokens);
String PopFirstWord(String &line,char *delimeter=" \t\n\r");
String PopLastWord(String &line);
int    hashpos(String &s,int number_of_slots);
String ToLower(const char *b);

int fileexists(char *filename);
String filefind(String filename,String pathlist,String extentions);

#endif
