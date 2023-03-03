#ifndef  _GLOBALS_H_
#define _GLOBALS_H_

template<typename T>
class PointerHolder
{
	T* mPointer;

public:
	PointerHolder() : mPointer(0) 
	{
		mPointer = 0;
	}

	~PointerHolder()
	{
		clear();
	}

	inline void clear()
	{
		if(mPointer)
		{
			delete mPointer;
			mPointer = 0;
		}
	}

	void set(T* p)
	{
		clear();
		mPointer = p;
	}
	
	inline T* ref()
	{
		return mPointer;
	}

};

class CommandParser;
class FileSystem;
class GuiTui;
class TextUserInterface;
class Log;


class GlobalManager
{

public:
	PointerHolder<CommandParser>           gCommandParser;
	PointerHolder<FileSystem>              gFileSystem;
	PointerHolder<GuiTui>		           gGuiTui;
	PointerHolder<TextUserInterface>       gTui;
	PointerHolder<Log>                     gLog;
};

extern GlobalManager gAllGlobals;

#endif // _GLOBALS_H_