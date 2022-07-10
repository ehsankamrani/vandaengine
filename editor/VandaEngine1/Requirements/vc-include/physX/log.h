#ifndef LOG_H

#define LOG_H

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


#include <vector>
#include <stdio.h>

#define MAXNUMERIC 32  // JWR  support up to 16 32 character long numeric formated strings
#define MAXFNUM    16

#define MAXLOGRETAIN 50
#define MAXLOGSTRING 256

class TrapLog
{
public:
  virtual void logMessage(const char *str) = 0;
};

class Log
{
public:
	Log(void);
	Log(const char *fname,bool buffer=true);
	~Log(void);

	void Display(const char *fmt, ...);
	void AddBuffer(char *buffer,const char *fmt, ...);

	const char * FormatNumber(int number); // JWR  format this integer into a fancy comma delimited string

	void Flush(void);

	const char * GetLogMessage(void); // spool report output messages...
	bool         HasLogMessage(void) const { return mHaveLogMessage; };

  void setTrapLog(TrapLog *log) { mTrapLog = log; };
  TrapLog * getTrapLog(void) const { return mTrapLog; };

private:
	int              mLogLevel;
	FILE            *mFph;
	int              mIndex;
	char             mFormat[MAXNUMERIC*MAXFNUM];
	bool             mBufferMessages;
	int              mLogFrame;
	char             mBuffer[1024];
	bool             mHaveLogMessage;
	int              mLogIndex;
	char            *mLog[MAXLOGRETAIN];
	TrapLog         *mTrapLog;
};


#endif
