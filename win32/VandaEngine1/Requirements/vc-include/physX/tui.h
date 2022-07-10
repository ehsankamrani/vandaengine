#ifndef TUI_H

#define TUI_H

#include <stdio.h>

#include "stringdict.h"
#include "cparser.h"

enum  TuiType;
class TuiElement;
typedef std::vector< TuiElement * > TuiElementVector;
typedef std::vector<StringRefVector *> StringRefVectorVct;

enum TuiType
{
	TT_DEFAULT,            // default text user interface container
	TT_PAGE,               // treated as a page
	TT_BUTTON,
	TT_SCRIPT,
	TT_CHECKBOX,
	TT_SLIDER,
	TT_COMBO,
	TT_MULTI_SELECT,
	TT_TEXT,
	TT_LAST_TUI
};

#define DFLT_BUTTON_WIDTH		150
#define DFLT_BUTTON_HEIGHT		20
#define DFLT_BUTTON_SPACING		10

#define DFLT_SLIDER_SPACING		24
#define DFLT_SLIDER_TEXT_WIDTH	80
#define DFLT_SLIDER_HEIGHT		20
#define DFLT_SLIDER_WIDTH		300

#define DFLT_COMBO_WIDTH		250
#define DFLT_COMBO_SPACING		42
#define DFLT_COMBO_HEIGHT		20
#define DFLT_COMBO_DROPDOWN		100

#define DFLT_TEXT_SPACING		24

#define DFLT_LIST_WIDTH			300

#define DFLT_LAYOUT_WIDTH		1024
#define DFLT_LAYOUT_RIGHT_MARGIN 10

#define DFLT_CHECKBOX_SPACING	22

#define DFLT_LAYOUT_LEFT_MARGIN	( DFLT_LAYOUT_WIDTH - 3*(DFLT_BUTTON_WIDTH+DFLT_BUTTON_SPACING) - DFLT_LAYOUT_RIGHT_MARGIN )

#define DFLT_CONSOLE_WIDTH	1000
#define DFLT_CONSOLE_HEIGHT 36
#define DFLT_CONSOLE_POS_X	0 
#define DFLT_CONSOLE_POS_Y	730

//==================================================================================
//==================================================================================
class TuiChoice
{
public:
	TuiChoice(const StringRef &r,const StringRef &arg,bool state)
	{
		mChoice = r;
		mArg    = arg;
		mState  = state;
	}

	const StringRef& GetChoice(void) const { return mChoice; };
	const StringRef& GetArg(void) const { return mArg; };

	bool GetState(void) const { return mState; };
	void SetState(bool state) { mState = state; };

private:

	StringRef mChoice;
	StringRef mArg;
	bool      mState;
};

typedef std::vector< TuiChoice > TuiChoiceVector;

class TextUserInterface;

//==================================================================================
//==================================================================================
class PageLayout
{
public:
  PageLayout(void)
  {
  	mButtonWidth       = DFLT_BUTTON_WIDTH;
  	mButtonHeight      = DFLT_BUTTON_HEIGHT;
  	mButtonSpacing     = DFLT_BUTTON_SPACING;

  	mSliderSpacing     = DFLT_SLIDER_SPACING;
  	mSliderTextWidth   = DFLT_SLIDER_TEXT_WIDTH;
  	mSliderHeight      = DFLT_SLIDER_HEIGHT;
  	mSliderWidth       = DFLT_SLIDER_WIDTH;
  	
	mComboWidth        = DFLT_COMBO_WIDTH;
  	mComboSpacing      = DFLT_COMBO_SPACING;
  	mComboHeight       = DFLT_COMBO_HEIGHT;
  	mComboDropdown     = DFLT_COMBO_DROPDOWN;
  	
	mTextSpacing       = DFLT_TEXT_SPACING;

  	mListWidth         = DFLT_LIST_WIDTH;
  	
	mLayoutLeftMargin  = DFLT_LAYOUT_LEFT_MARGIN;
  	mLayoutWidth       = DFLT_LAYOUT_WIDTH;
  }

  void Modify( unsigned newScreenWidth, unsigned newScreenHeight );

  int	mButtonWidth;
  int	mButtonHeight;
  int	mButtonSpacing;
  int	mLayoutLeftMargin;
  int	mLayoutWidth;
  int	mSliderSpacing;
  int	mSliderTextWidth;
  int	mSliderHeight;
  int	mSliderWidth;
  int	mComboWidth;
  int	mComboSpacing;
  int	mComboHeight;
  int	mComboDropdown;
  int	mListWidth;
  int	mTextSpacing;
};

//==================================================================================
//==================================================================================
class TuiElement
{
public:
	TuiElement(const StringRef &key,TuiType type,int count,const char **commands);
	~TuiElement(void);

	TuiType           GetType(void) const;
	void              SetType(TuiType type);
	void              SetTokens(int count,const char **args);
	void              SetDescription(int count,const char **args);
	void              SetText(const char *text);
	void              SetTextColor(unsigned color );
	void              Add(TuiElement *tui);
	void              SetName(const StringRef &name);
	void              SetKey(const StringRef &key);
	void              Reset(void);
	void              End(void);
	void              Indent(int indent);
	void              ShowHelp(int indent,bool detailed,int index,bool showcount);
	bool              ShowHelp(const char *str);

	TuiElement *      Command(const StringRef &c,int count,const char **arglist,TextUserInterface *tui);

	bool              NeedSpace(const char *foo);

	const char *      GetCommand(const StringRef &c,int count,const char **arglist,TuiElement *parent,TextUserInterface *tui);

	void              Execute(int count,const char **arglist,TuiElement *parent,TextUserInterface *tui);
	void              SetArg(int count,const char *c);

	const char *      GetText( void ) const;
	unsigned          GetTextColor( void ) const;
	TuiElementVector& GetElements(void);
	void *            GetUserPtr(void);
	void *            GetUserPtr2(void);
	void              SetUserPtr(void *ptr);
	void              SetUserPtr2(void *ptr);
	const StringRef&  GetKey(void) const;
	const StringRef&  GetName(void) const;
	TuiElement *      ExecuteElement(int index,int count,const char **arglist,TextUserInterface *tui);
	TuiElement *      GetElement(int index);

	void              AddArg(int count,const char **arglist);
	void              AddChoice(int count,const char **arglist);
	void              AddChoices(int count,const char **arglist);
	void              AddFiles(int count,const char **arglist);
	void              AddTechniques(const char *fxfile); // add all of the 'tehcniques' in a FX file
	void              SetMinMax(float fmin,float fmax) { mMin = fmin; mMax = fmax; };
	void              AddActors(void);

	TuiChoiceVector& GetChoices(void) { return mChoices; };

	const char *      ArgumentLookup(const char *name);
	const char *      GetToggleArg(int count); // locate this argument, toggle the result and return.
	bool		      GetArg(int count, char *arg) const;
	bool		      GetArg_Actual(int count, char *arg) const;

 	bool              GetState(void);
 
 	int			      GetSliderTick(float v) const; // convert into a normalized tick value 0-1000
 	float             GetSliderValue(int tick) const; // convert integer tick (0-1000) into floating point value.
 
 	void              Save(FILE *fph);

 	void              SetSaveOk(bool saveok) { mSaveOk = saveok; };
	void			  SetExecuteOk(bool executeok) { mExecuteOk = executeok; };
 	void              SetRecip(bool state) { mRecip = state; };
 
 	void              Refresh(void);

 	void              SetNeedsUpdating( bool yesNo );
 	bool              GetNeedsUpdating( void ) const;

 	void              AddOnCheckShow( int count, const char **name );
 	void              AddOnCheckRescript( int count, const char **script );
 	const StringRefVectorVct& GetOnCheckShow( void ) const;
 	const StringRefVectorVct& GetOnCheckRescript( void ) const;
 	void              SetVisible( bool visible );
 	bool              IsVisible( void ) const;

 	void              OnCheckboxChange( bool state, int id );
 	void              OnComboBoxChange( const char *selectedItem, int id );

 	void              DetermineVisibleElements( const char *, int );
 	void              DetermineRescriptedItems( const char *, int );

	void			  AddExecuteOnLoad( const char **, int );
	void			  AddExecuteOnExit( const char **, int );
	void			  OnLoad( TuiElement *loadingPage );
	void			  OnExit( TuiElement *exitingPage );

	int				  GetElementIndexOfTypeWithName( TuiType type, const char *name );
	TuiElement *	  GetElementOfTypeWithName( TuiType type, const char *name );

	bool			  NotifyHardwareStatus( bool hwOn );

	PageLayout& getPageLayout(void) { return mPageLayout; };

	void SetInt(bool state) { mInt = state; };
	bool GetInt(void) const { return mInt; };

	void				SetSWEnabled( bool state ) { mSWEnabled = state; }
	void				SetHWEnabled( bool state ) { mHWEnabled = state; }
	bool				GetSWEnabled( void ) const { return mSWEnabled; }
	bool				GetHWEnabled( void ) const { return mHWEnabled; }

	TuiElement *		GetPreviousPage( void );

	bool ChildNeedsUpdating(void)
	{
  		bool ret = false;

   		TuiElementVector::const_iterator i;
   		for (i=mElements.begin(); i!=mElements.end(); i++)
   		{
   			TuiElement *te = (*i);
   			if ( te->GetType() != TT_PAGE )
   			{
    			if ( te->GetNeedsUpdating() )
    			{
    				te->SetNeedsUpdating(false);
    				ret = true;
    			}
    		}
		}

		return ret;
	}

	bool HasElement(TuiElement *t) const
	{
  		bool ret = false;
  		TuiElementVector::const_iterator i;
  		for (i=mElements.begin(); i!=mElements.end(); i++)
  		{
  			if ( t == (*i) )
  			{
  				ret = true;
  				break;
  			}
  		}
  		return ret;
	}

private:

	void			  GetOnLoadOnExitCommand( char *buff, int buffLen, const StringRef &command );

	TuiType          mType;     // type of text user interface element

	StringRef        mKey;      // key name
	StringRef        mName;     // descriptive name
	StringRef        mText;
	StringRefVector  mTokens;
	StringRefVector  mArgs;     // default arguments.
	StringRefVector  mDescription; // the detailed usage description.
	StringRefVector  mCommands; // the shorthand command or commands.
	TuiElementVector mElements; // sub-elements in this element
	void             *mUserPtr; // user data field
	void             *mUserPtr2; //-- temporary until Ag gui is working
	TuiChoiceVector   mChoices; // choices for combo boxes or list boxes
	TuiChoiceVector   mOriginalChoices; // original choices prior to reading file spec!
	float             mMin;
	float             mMax;
	bool              mSaveOk;
	bool              mExecuteOk;
	int               mSaveFrame;
	bool              mRecip;
	StringRefVector   mFileSpecs;
	unsigned          mTextColor;
	bool              mInt;
	bool              mHasActors;

 	StringRefVectorVct mOnCheckShow;
 	StringRefVectorVct mOnCheckRescript;
	StringRefVector	  mOnLoadCommands;
	StringRefVector   mOnExitCommands;
 	bool              mNeedsUpdating;
 	bool              mVisible;

	bool			  mHWEnabled;
	bool			  mSWEnabled;

//***
//***
  PageLayout        mPageLayout;

};

//==================================================================================
inline void TuiElement::SetNeedsUpdating( bool yesNo )
{
	mNeedsUpdating = yesNo;
}

//==================================================================================
inline bool TuiElement::GetNeedsUpdating( void ) const
{
	return mNeedsUpdating;
}

//==================================================================================
inline const StringRefVectorVct& TuiElement::GetOnCheckShow( void ) const
{
	return mOnCheckShow;
}

//==================================================================================
inline const StringRefVectorVct& TuiElement::GetOnCheckRescript( void ) const
{
	return mOnCheckRescript;
}

//==================================================================================
inline void TuiElement::SetVisible( bool visible )
{
	mVisible = visible;
}

//==================================================================================
inline bool TuiElement::IsVisible( void ) const
{
	return mVisible;
}

//==================================================================================
inline const char *TuiElement::GetText( void ) const
{
	return mText.Get();
}

//==================================================================================
inline unsigned TuiElement::GetTextColor( void ) const
{
	return mTextColor;
}

typedef std::map<StringRef, TuiElement*> TuiElementMap;

//==================================================================================
//==================================================================================
class TextUserInterface : public CommandParserInterface
{
public:
	TextUserInterface(const char *startup);
	~TextUserInterface(void);

	virtual int CommandCallback(int token,int count,const char **arglist);
	virtual int CommandFallback(int count,const char **arglist);

	TuiElement * Locate(const StringRef &name) const; // locate a text user interface element by name.
	int SlashCommand(const char *key,int count,const char **arglist);

	TuiElement * GetPage(void) { return mPage; }
	void SetPage(TuiElement *page) { mPage = page; };

	void HelpAll(void);

	bool GetShowGraphics(void) const { return mShowGraphics; };
	void SetShowGraphics(bool state) { mShowGraphics = state; };
	bool ToggleShowGraphics(void)
	{
		if ( mShowGraphics )
			mShowGraphics = false;
		else
			mShowGraphics = true;
		return mShowGraphics;
	};


	// 'look up' this argument by name field.
	const char * ArgumentLookup(const char *name);

	void Refresh(void);

	bool IsTuiLoad(void) const { return mTuiLoad; };

	void setLook(const float *eye,const float *look)
	{
	  mEyePos[0] = eye[0];
	  mEyePos[1] = eye[1];
	  mEyePos[2] = eye[2];

	  mLookAt[0] = look[0];
	  mLookAt[1] = look[1];
	  mLookAt[2] = look[2];
	}

	void NotifyAllPagesOfNewDimensions( unsigned width, unsigned height );
	TuiElement *GetElementOfTypeWithName( TuiType type, const char *name );

	void NotifyHardwareStatus( bool hwOn );

private:

	void Begin(TuiType type,int count,const char **arglist);
	void End(void);

	bool          mShowGraphics;
	TuiElement   *mPage;       // current active user interface page.
	TuiElement   *mCurrent;
	TuiElementMap mTui; // complete text user interface specification.
	std::vector<TuiElement*>   mTuiOthers; // need to release.

	float         mEyePos[3]; //
	float         mLookAt[3];

	FILE          *mFph;
	FILE          *mFileOpen;

	bool          mTuiLoad;
	StringRef     mSaveName;
	int           mSlashDepth;
};



#endif



