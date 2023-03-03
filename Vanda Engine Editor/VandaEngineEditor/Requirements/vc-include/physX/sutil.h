#ifndef SUTIL_H

#define SUTIL_H

/*----------------------------------------------------------------------
		Copyright (c) 2004 Open Dynamics Framework Group
					www.physicstools.org
		All rights reserved.

		Redistribution and use in source and binary forms, with or without modification, are permitted provided
		that the following conditions are met:

		Redistributions of source code must retain the above copyright notice, this list of conditions
		and the following disclaimer.

		Redistributions in binary form must reproduce the above copyright notice,
		this list of conditions and the following disclaimer in the documentation
		and/or other materials provided with the distribution.

		Neither the name of the Open Dynamics Framework Group nor the names of its contributors may
		be used to endorse or promote products derived from this software without specific prior written permission.

		THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 'AS IS' AND ANY EXPRESS OR IMPLIED WARRANTIES,
		INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
		DISCLAIMED. IN NO EVENT SHALL THE INTEL OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
		EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
		LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER
		IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
		THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
-----------------------------------------------------------------------*/


#pragma warning(disable:4786)



char *         stristr(const char *str,const char *key);       // case insensitive str str
bool           isstristr(const char *str,const char *key);     // bool true/false based on case insenstive strstr
unsigned int   GetHEX(const char *foo,const char **next=0);
unsigned char  GetHEX1(const char *foo,const char **next=0);
unsigned short GetHEX2(const char *foo,const char **next=0);
unsigned int   GetHEX4(const char *foo,const char **next=0);
float          GetFloatValue(const char *str,const char **next=0);
int            GetIntValue(const char *str,const char **next=0);
const char *   SkipWhitespace(const char *str);
bool           IsWhitespace(char c);
const char *   FloatString(float v,bool binary=false);
const char *   GetTrueFalse(unsigned int state);
bool           CharToWide(const char *source,void *dest,int maxlen);
bool           WideToChar(const void *source,char *dest,int maxlen);
const char **  GetArgs(char *str,int &count); // destructable parser, stomps EOS markers on the input string!
int            GetUserArgs(const char *us,const char *key,const char **args);
bool           GetUserSetting(const char *us,const char *key,int &v);
bool           GetUserSetting(const char *us,const char *key,const char * &v);
const char *   GetRootName(const char *fname); // strip off everything but the 'root' file name.
bool           IsTrueFalse(const char *c);
bool           IsDirectory(const char *fname,char *path,char *basename,char *postfix);
bool           hasSpace(const char *str); // true if the string contains a space


#endif
