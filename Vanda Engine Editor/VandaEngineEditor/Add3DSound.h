//Copyright (C) 2024 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#pragma once
#include "afxwin.h"


// CAdd3DSound dialog

class CAdd3DSound : public CDialog
{
	DECLARE_DYNAMIC(CAdd3DSound)

public:
	CAdd3DSound(CWnd* pParent = NULL);   // standard constructor
	virtual ~CAdd3DSound();

	//####public interface####	
	//The user just needs to use these functions
	CFloat* GetSoundPos() { return m_f3DSoundPos; }
	CChar* GetName() { return (CChar*)m_str3DSoundName.GetBuffer(m_str3DSoundName.GetLength()); m_str3DSoundName.ReleaseBuffer(); }
	CChar* GetTempName() { return (CChar*)m_str3DSoundTempName.GetBuffer(m_str3DSoundTempName.GetLength()); m_str3DSoundTempName.ReleaseBuffer(); }
	CChar* GetPath() {return (CChar*)m_str3DSoundDataPath.GetBuffer(m_str3DSoundDataPath.GetLength()); m_str3DSoundDataPath.ReleaseBuffer(); }
	CFloat GetPitch() { return m_f3DSoundPitch; }
	CFloat GetVolume() { return m_f3DSoundVolume; }
	CFloat GetReferenceDistance() { return m_f3DSoundReferenceDistance; }
	CFloat GetMaxDistance() { return m_f3DSoundMaxDistance; }
	CFloat GetRolloff() { return m_f3DSoundRolloff; }

	CBool GetPlayCondition() { return m_play; }
	CBool GetLoopCondition() { return m_loop; }
	CInt GetIndex() {return m_nameIndex; }

	CChar* GetLastName() { return m_lastName; }
	CBool GetHasScript() { return m_hasScript; }
	CChar* GetScriptPath() { return m_strScript.GetBuffer(m_strScript.GetLength()); }
	CBool GetUpdateScript() { return m_scriptUpdated; }

	CVoid SetSoundPos( CFloat* pos )
	{
		CChar posX[MAX_NAME_SIZE];
		CChar posY[MAX_NAME_SIZE];
		CChar posZ[MAX_NAME_SIZE];
		sprintf( posX, "%.3f", pos[0] );
		sprintf( posY, "%.3f", pos[1] );
		sprintf( posZ, "%.3f", pos[2] );
		m_str3DSoundPosX = posX;
		m_str3DSoundPosY = posY;
		m_str3DSoundPosZ = posZ;
	}
	CVoid SetEditMode( CBool editMode )
	{
		m_editMode = editMode;
	}
	CVoid SetCreate( CBool create )
	{
		if( create ) m_create = CTrue;
		else m_create = CFalse;
	}

	CVoid SetName( CChar* name )
	{
		m_str3DSoundName = name;
	}

	CVoid SetPath( CChar * path )
	{
		m_str3DSoundDataPath = path;
	}

	CVoid SetRolloff( CFloat rolloff )
	{
		CChar temp[MAX_NAME_SIZE];
		sprintf( temp, "%.3f", rolloff );
		m_str3DSoundRolloff = temp;
	}

	CVoid SetPitch( CFloat pitch )
	{
		CChar temp[MAX_NAME_SIZE];
		sprintf( temp, "%.3f", pitch );
		m_str3DSoundPitch = temp;
	}

	CVoid SetReferenceDistance( CFloat referenceDistance )
	{
		CChar temp[MAX_NAME_SIZE];
		sprintf( temp, "%.3f", referenceDistance );
		m_str3DSoundReferenceDistance = temp;
	}

	CVoid SetMaxDistance( CFloat maxDistance )
	{
		CChar temp[MAX_NAME_SIZE];
		sprintf( temp, "%.3f", maxDistance );
		m_str3DSoundMaxDistance = temp;
	}

	CVoid SetVolume( CFloat volume )
	{
		CChar temp[MAX_NAME_SIZE];
		sprintf( temp, "%.3f", volume );
		m_str3DSoundVolume = temp;
	}

	CVoid SetLoop( CBool loop )
	{
		m_loop = loop;
	}

	CVoid SetPlay( CBool play )
	{
		m_play = play;
	}
	CVoid SetIndex( CInt index )
	{
		m_nameIndex = index;
	}

	CVoid SetLastName(CChar* name)
	{
		Cpy(m_lastName, name);
	}
	CVoid SetHasScript(CBool hasScript) { m_hasScript = hasScript; }
	CVoid SetScriptPath(CChar* scriptPath) { m_strScript = scriptPath; }
	CVoid SetUpdateScript(CBool update) { m_scriptUpdated = update; }

	//#######################


// Dialog Data
	enum { IDD = IDD_DIALOG_ADD_3D_SOUND };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	CEdit m_editBox3DSoundName;
	CEdit m_editBox3DSoundPosX;
	CEdit m_editBox3DSoundPosY;
	CEdit m_editBox3DSoundPosZ;
	CEdit m_editBox3DSoundRolloff;
	CEdit m_editBox3DSoundPitch;
	CEdit m_editBox3DSoundData;
	CEdit m_editBox3DSoundReferenceDistance;
	CEdit m_editBox3DSoundMaxDistance;
	CEdit m_editBox3DSoundVolume;

	CComboBox m_combo3DSoundLoop;
	CComboBox m_combo3DSoundPlay;

	//The above strings are converted to the following floating point values
	CFloat m_f3DSoundPos[3];
	CFloat m_f3DSoundPitch;
	CFloat m_f3DSoundVolume;
	CFloat m_f3DSoundRolloff;
	CFloat m_f3DSoundMaxDistance;
	CFloat m_f3DSoundReferenceDistance;
	CBool m_loop, m_play;

	CInt m_nameIndex; //selection
	CChar m_lastName[MAX_NAME_SIZE];

	virtual BOOL OnInitDialog();
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEdit3DSoundXPos();
	afx_msg void OnEnChangeEdit3DSoundYPos();
	afx_msg void OnEnChangeEdit3DSoundZPos();
	afx_msg void OnEnChangeEdit3DSoundPitch();
	afx_msg void OnEnChangeEdit3DSoundRolloff();
	afx_msg void OnCbnSelchangeCombo3DSoundLoop();
	afx_msg void OnCbnSelchangeCombo3DSoundPlay();
	afx_msg void OnBnClickedButton3DSoundData();
	afx_msg void OnEnChangeEdit3DSoundName();
	afx_msg void OnEnChangeEdit3DSoundReferenceDistance();
	afx_msg void OnEnChangeEdit3DSoundMaxDistance();

	CString m_str3DSoundPosX;
	CString m_str3DSoundPosY;
	CString m_str3DSoundPosZ;
	CString m_str3DSoundPitch;
	CString m_str3DSoundName;
	CString m_str3DSoundTempName;
	CString m_str3DSoundDataPath;
	CString m_str3DSoundPureDataPath;
	CString m_str3DSoundRolloff;
	CString m_str3DSoundMaxDistance;
	CString m_str3DSoundReferenceDistance;
	CString m_str3DSoundVolume;

	CBool m_create;
	CBool m_editMode;

public:
	afx_msg void OnEnChangeEdit3DSoundVolume();
public:
	virtual INT_PTR DoModal();
	afx_msg void OnBnClickedOk();
	CRichEditCtrl m_editBoxScript;
	afx_msg void OnBnClickedBtnAddScript();
	afx_msg void OnBnClickedBtnRemoveScript();
	afx_msg void OnBnClickedButtonViewScript();

private:
	CBool m_scriptUpdated;
	CString m_strScript;
	CBool m_hasScript;

};
