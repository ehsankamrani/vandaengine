#ifndef CPARSER_H

#define CPARSER_H


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

#include "inparser.h"       // include the in-place file parser
#include "stringdict.h"     // include the string dictionary

class TokenTag;

typedef std::map<StringRef, TokenTag> TokenMap;


//==================================================================================
//==================================================================================
class CommandParserInterface
{
	friend class CommandParser;
public:
	CommandParserInterface(void);
	virtual ~CommandParserInterface(void);

	virtual int CommandCallback(int token,int count,const char **arglist) = 0;

	virtual int CommandFallback(int count,const char **arglist)
	{
		int ret = 0;
		return ret;
	}

	void AddToken(const char *key,int token);
	int GetTokenFromKey(const char *key);
	const char *GetKeyFromToken( const char *prefix, int token );

private:
};


typedef std::vector< CommandParserInterface * > CommandParserInterfaceVector;

//==================================================================================
//==================================================================================
class TokenTag
{
public:
	TokenTag(void) { };
	TokenTag(int tlocal,CommandParserInterface *service)
	{
		mLocalToken = tlocal;
		mService = service;
	};
	int GetLocalToken(void) const { return mLocalToken; };
	CommandParserInterface * GetService(void) const { return mService; }
private:
	int mLocalToken; // JWR  local internal token for this command.
	CommandParserInterface *mService;
};

class RootCommands; // handles root commands.


//==================================================================================
//==================================================================================
class CommandParser : public InPlaceParserInterface
{
public:
	CommandParser(void);
	~CommandParser(void);

	int __cdecl Parse(const char *fmt, ...);

	void AddToken(const char *key,int token,CommandParserInterface *service);
	int GetTokenFromKey(const char *key);
	const char *GetKeyFromToken( const char *prefix, int token );

	void RemoveToken(const char *key);

	void DeRegister(CommandParserInterface *service);

	int Batch(const char *fname);

	virtual int ParseLine(int lineno,int argc,const char **argv);

	int CommandLine(int argc,const char **argv,bool fallbackok=true);

	void AddFallback(CommandParserInterface *iface)
	{
		mFallbacks.push_back(iface);
	}

	int GetLineNo(void) const { return mLineNo; };

	bool receiveMessage(const char *msg);

	void checkMessages(void);

private:
	RootCommands   *mRoot;
	TokenMap        mTokens; // JWR  token id's organized based on ascii name.
	CommandParserInterfaceVector mFallbacks;
	int mLineNo;
};

//==================================================================================
//==================================================================================
class CommandCapture
{
public:
	CommandCapture(int token,int count,const char **args);
	CommandCapture(const CommandCapture &a); // copy constructor to do a 'deep' copy.
	~CommandCapture(void);

	void Invoke(CommandParserInterface *iface); // spool it as a callback.
	const char ** GetArgs(void) const { return (const char **)mArgs; };
	unsigned int GetCount(void) const { return (unsigned int) mCount; };

private:
	int    mToken;
	int    mCount;
	char **mArgs;
};

typedef std::vector< CommandCapture * > CommandCaptureVector;

#include "MyGlobals.h"
#define PARSE(x) gAllGlobals.gCommandParser.ref()->Parse(x)
#define CPARSER (*gAllGlobals.gCommandParser.ref())

#endif
