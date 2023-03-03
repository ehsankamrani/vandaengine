#ifndef STRINGDICT_H
#define STRINGDICT_H

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

#include <vector>
#include <map>
#include <set>

#include "stl.h"
#include "stable.h"

#include <stdio.h>
#include <string.h>
#include <assert.h>



extern const char *emptystring;

class StringRef
{
public:
public:
	StringRef(void)
	{
		mString = "";
	}

	inline StringRef(const char *str);
	inline StringRef(const StringRef &str);

	operator const char *() const
	{
		return mString;
	}

	const char * Get(void) const { return mString; };

	void Set(const char *str)
	{
		mString = str;
	}

	const StringRef &operator= (const StringRef& rhs )
	{
		mString = rhs.Get();
		return *this;
	}

	bool operator== ( const StringRef& rhs ) const
	{
		return rhs.mString == mString;
	}

	bool operator< ( const StringRef& rhs ) const
	{
		return rhs.mString < mString;
	}

	bool operator!= ( const StringRef& rhs ) const
	{
		return rhs.mString != mString;
	}

	bool operator> ( const StringRef& rhs ) const
	{
		return rhs.mString > mString;
	}

	bool operator<= ( const StringRef& rhs ) const
	{
		return rhs.mString < mString;
	}

	bool operator>= ( const StringRef& rhs ) const
	{
		return rhs.mString >= mString;
	}

	bool SamePrefix(const char *prefix) const
	{
		unsigned int len = (unsigned int)strlen(prefix);
		if ( len && strncmp(mString,prefix,len) == 0 ) return true;
		return false;
	}

	bool SameSuffix(const StringRef &suf) const
	{
		const char *source = mString;
		const char *suffix = suf.mString;
		unsigned int len1 = (unsigned int)strlen(source);
		unsigned int len2 = (unsigned int)strlen(suffix);
		if ( len1 < len2 ) return false;
		const char *compare = &source[(len1-len2)];
		if ( strcmp(compare,suffix) == 0 ) return true;
		return false;
	}

private:
	const char *mString; // the actual char ptr
};


class StringDict
{
public:

	StringDict(void)
	{
	}

	~StringDict(void)
	{
	}

	StringRef Get(const char *text)
	{
		StringRef ref;
		if ( text )
		{
			if ( strcmp(text,emptystring) == 0 )
			{
				ref.Set(emptystring);
			}
			else
			{
				if ( strcmp(text,emptystring) == 0 )
				{
					ref.Set(emptystring);
				}
				else
				{
					const char *foo = mStringTable.Get(text);
					ref.Set(foo);
				}
			}
		}
		return ref;
	}

	StringRef Get(const char *text,bool &first)
	{
		assert(text); // no null string support for this version!
		StringRef ref;
		const char *foo = mStringTable.Get(text,first);
		ref.Set(foo);
		return ref;
	}

private:
	StringTable mStringTable;
};

extern StringDict gStringDict;

typedef std::vector< StringRef  >    StringRefVector;
typedef std::set< StringRef >        StringRefSet;

inline StringRef SGET(const char *foo)
{
	return gStringDict.Get(foo);
}

inline StringRef::StringRef(const char *str)
{
	StringRef ref = SGET(str);
	mString = ref.mString;
}

inline StringRef::StringRef(const StringRef &str)
{
	mString = str.Get();
}

// This is a helper class so you can easily do an alphabetical sort on an STL vector of StringRefs.
// Usage: std::sort( list.begin(), list.end(), StringSortRef() );
class StringSortRef
{
	public:

	 bool operator()(const StringRef &a,const StringRef &b) const
	 {
		 const char *str1 = a.Get();
		 const char *str2 = b.Get();
		 int r = stricmp(str1,str2);
		 return r < 0;
	 }
};

#endif
