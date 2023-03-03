#ifndef STABLE_H

#define STABLE_H

#pragma warning(disable:4996)

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

#include <assert.h>
#include <string.h>
#include <string>
#include <set>


class CharPtrLess
{
public:
	bool operator()(const char *v1,const char *v2) const
	{
		int v = strcmp(v1,v2);
		if ( v < 0 ) return true;
		return false;
	};
};

#ifdef PLAYSTATION3
typedef std::set< const char *, CharPtrLess > CharPtrSet;
#else
typedef std::set< const char *, CharPtrLess > CharPtrSet;
#endif

class StringTable
{
public:
	StringTable(void)
	{
	};

	~StringTable(void)
	{
		CharPtrSet::iterator i;
		for (i=mStrings.begin(); i!=mStrings.end(); i++)
		{
			char *str = (char *)(*i);
			free(str);
		}
	}

	const char * Get(const char *str)
	{
		CharPtrSet::iterator found;
		found = mStrings.find( str );
		if ( found != mStrings.end() ) return (*found);
		unsigned int l = (unsigned int)strlen(str);
		char *mem = (char *) malloc(sizeof(char)*(l+1));
		strcpy(mem,str);
		mStrings.insert( mem );
		return mem;
	};

	const char * Get(const char *str,bool &first)
	{
		CharPtrSet::iterator found;
		found = mStrings.find( str );
		if ( found != mStrings.end() )
		{
			first = false;
			return (*found);
		}
		first = true;
		unsigned int l = (unsigned int)strlen(str);
		char *mem = (char *) malloc(sizeof(char)*(l+1));
		strcpy(mem,str);
		mStrings.insert( mem );
		return mem;
	};

	CharPtrSet& GetSet(void) { return mStrings; };

private:
	CharPtrSet mStrings;
};


class CharPtrInt
{
public:
	const char *mString;
	int         mId;
};

class CharPtrIntLess1
{
public:
	bool operator()(const CharPtrInt &v1,const CharPtrInt &v2) const
	{
		int v = strcmp(v1.mString,v2.mString);
		if ( v < 0 ) return true;
		return false;
	};
};

class CharPtrIntLess2
{
public:
	bool operator()(const CharPtrInt &v1,const CharPtrInt &v2) const
	{
#if PLAYSTATION3
		int v = strcasecmp(v1.mString,v2.mString);
#else
		int v = stricmp(v1.mString,v2.mString);
#endif
		if ( v < 0 ) return true;
		return false;
	};
};

#ifdef PLAYSTATION3
typedef std::set< CharPtrInt, CharPtrIntLess1 > CharPtrIntSet1;
typedef std::set< CharPtrInt, CharPtrIntLess2 > CharPtrIntSet2;
#else
typedef std::set< CharPtrInt, CharPtrIntLess1 > CharPtrIntSet1;
typedef std::set< CharPtrInt, CharPtrIntLess2 > CharPtrIntSet2;
#endif

class StringTableInt
{
public:
	StringTableInt(void)
	{
		mCase = true;
	}

	int Get(const char *str) const
	{
		int ret = 0;
		if ( mCase )
		{
			CharPtrIntSet1::const_iterator found;
			CharPtrInt cpi;
			cpi.mString = str;
			cpi.mId     = 0;
			found = mStrings1.find( cpi );
			if ( found != mStrings1.end() )
				ret = (*found).mId;
		}
		else
		{
			CharPtrIntSet2::const_iterator found;
			CharPtrInt cpi;
			cpi.mString = str;
			cpi.mId     = 0;
			found = mStrings2.find( cpi );
			if ( found != mStrings2.end() )
				ret = (*found).mId;
		}
		return ret;
	};

	void Add(const char *foo,int id)
	{
		assert( id > 0 );
		CharPtrInt cpi;
		cpi.mString = foo;
		cpi.mId     = id;
		if ( mCase )
			mStrings1.insert(cpi);
		else
			mStrings2.insert(cpi);
	}

	const char * Get(int id) const
	{
		const char *ret = 0;
		if ( mCase )
		{
			CharPtrIntSet1::const_iterator i;
			for (i=mStrings1.begin(); i!=mStrings1.end(); ++i)
			{
				if ( (*i).mId == id )
				{
					ret = (*i).mString;
					break;
				}
			}
		}
		else
		{
			CharPtrIntSet2::const_iterator i;
			for (i=mStrings2.begin(); i!=mStrings2.end(); ++i)
			{
				if ( (*i).mId == id )
				{
					ret = (*i).mString;
					break;
				}
			}
		}
		return ret;
	}

	void SetCaseSensitive(bool s)
	{
		mCase = s;
	}

private:
	bool        mCase;
	CharPtrIntSet1 mStrings1;     // case sensitive
	CharPtrIntSet2 mStrings2;     // case insensitive
};


#endif
