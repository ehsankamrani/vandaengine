#ifndef GUITUI_H

#define GUITUI_H

class CDXUTDialog;
class CDXUTDialogResourceManager;

#include "cparser.h"

#define CONSOLE_LINES			100

class ConsoleMessage
{
public:
	ConsoleMessage(void)
	{
		memset( mMessage, 0, 256 );
	}

	void SetConsoleMessage(const char *msg)
	{
		strcpy(mMessage,msg);
	}

	const char * GetMsg(void) const { return mMessage; };

private:
	char mMessage[256];
};

//==================================================================================
//==================================================================================
class GuiTui : public CommandParserInterface
{
public:
	GuiTui(void *device,void *hwnd,void *instance,CDXUTDialogResourceManager *pManager);
	~GuiTui(void);

	void Render(void);

	// Update the UI's state.
	void Update(void);

	bool          HasCursorFocus();
	void          HideAllGuiForTuiPages();

	bool MsgProc(void *hwnd,unsigned int msg,unsigned int wparam,unsigned int lparam);

	void OnMouseDown(unsigned int uiX, unsigned int uiY, unsigned int uiButtons);
	void OnMouseMove(unsigned int uiX, unsigned int uiY, unsigned int uiButtons);
	void OnMouseUp(unsigned int uiX, unsigned int uiY, unsigned int uiButtons);

	bool ToggleUI(void);

	void PrintText(const char *str,int x,int y,unsigned int color);

	void SetWindow(void* hwnd);


	void NotifyWindowResized( unsigned newWidth, unsigned newHeight );

	void NotifySceneTypeChanged( bool hardwareOn );

	void GetWindowSize( unsigned &width, unsigned &height );

	const char * GetConsoleMessage(int index)
	{
		index = mConsoleIndex+index;

		if ( index >= CONSOLE_LINES )
			index -= CONSOLE_LINES;
		else if ( index < 0 )
			return 0;

		return mConsole[index].GetMsg();
	}

	void AddConsoleMessage(const char *msg)
	{
		mConsole[mConsoleIndex].SetConsoleMessage(msg);
		mConsoleIndex++;
		if ( mConsoleIndex == CONSOLE_LINES )
			mConsoleIndex = 0;
	}

	int GetConsoleMessageIndex( void ) const
	{
		return mConsoleIndex;
	}

public: //-- CommandParserInterface overrides

	virtual int CommandCallback(int token,int count,const char **arglist);

	void onLostDevice(void);
	void onResetDevice(void *device);


private:

	int	mWidth;
	int mHeight;
	bool mConsoleKeyDown;
  void *mNullHwnd;
  bool mShowConsole;
  bool mCapture;
  float mDtime;
  CDXUTDialogResourceManager *mDialogResourceManager; // manager for shared resources of dialogs
	int                 mConsoleIndex;
	ConsoleMessage		  mConsole[CONSOLE_LINES];
};

//==================================================================================
inline void GuiTui::GetWindowSize( unsigned &width, unsigned &height )
{
	width  = mWidth;
	height = mHeight;
}



#endif

