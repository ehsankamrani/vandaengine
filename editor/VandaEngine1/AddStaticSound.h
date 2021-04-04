//Copyright (C) 2021 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#pragma once
#include "afxwin.h"


// CAddStaticSound dialog

class CAddStaticSound : public CDialog
{
	DECLARE_DYNAMIC(CAddStaticSound)

public:
	CAddStaticSound(CWnd* pParent = NULL);   // standard constructor
	virtual ~CAddStaticSound();

	//####public interface####	
	//The user just needs to use these functions
	CFloat* GetSoundPos() { return m_fStaticSoundPos; }
	CChar* GetName() { return (CChar*)m_strStaticSoundName.GetBuffer(m_strStaticSoundName.GetLength()); m_strStaticSoundName.ReleaseBuffer(); }
	CChar* GetTempName() { return (CChar*)m_strStaticSoundTempName.GetBuffer(m_strStaticSoundTempName.GetLength()); m_strStaticSoundTempName.ReleaseBuffer(); }
	CChar* GetPath() {return (CChar*)m_strStaticSoundDataPath.GetBuffer(m_strStaticSoundDataPath.GetLength()); m_strStaticSoundDataPath.ReleaseBuffer(); }
	CFloat GetPitch() { return m_fStaticSoundPitch; }
	CFloat GetVolume() { return m_fStaticSoundVolume; }
	CFloat GetReferenceDistance() { return m_fStaticSoundReferenceDistance; }
	CFloat GetMaxDistance() { return m_fStaticSoundMaxDistance; }
	CFloat GetRolloff() { return m_fStaticSoundRolloff; }

	CBool GetPlayCondition() { return m_play; }
	CBool GetLoopCondition() { return m_loop; }
	CInt GetIndex() {return m_nameIndex; }
	CVoid SetSoundPos( CFloat* pos )
	{
		CChar posX[MAX_NAME_SIZE];
		CChar posY[MAX_NAME_SIZE];
		CChar posZ[MAX_NAME_SIZE];
		sprintf( posX, "%.3f", pos[0] );
		sprintf( posY, "%.3f", pos[1] );
		sprintf( posZ, "%.3f", pos[2] );
		m_strStaticSoundPosX = posX;
		m_strStaticSoundPosY = posY;
		m_strStaticSoundPosZ = posZ;
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
		m_strStaticSoundName = name;
	}

	CVoid SetPath( CChar * path )
	{
		m_strStaticSoundDataPath = path;
	}

	CVoid SetRolloff( CFloat rolloff )
	{
		CChar temp[MAX_NAME_SIZE];
		sprintf( temp, "%.3f", rolloff );
		m_strStaticSoundRolloff = temp;
	}

	CVoid SetPitch( CFloat pitch )
	{
		CChar temp[MAX_NAME_SIZE];
		sprintf( temp, "%.3f", pitch );
		m_strStaticSoundPitch = temp;
	}

	CVoid SetReferenceDistance( CFloat referenceDistance )
	{
		CChar temp[MAX_NAME_SIZE];
		sprintf( temp, "%.3f", referenceDistance );
		m_strStaticSoundReferenceDistance = temp;
	}

	CVoid SetMaxDistance( CFloat maxDistance )
	{
		CChar temp[MAX_NAME_SIZE];
		sprintf( temp, "%.3f", maxDistance );
		m_strStaticSoundMaxDistance = temp;
	}

	CVoid SetVolume( CFloat volume )
	{
		CChar temp[MAX_NAME_SIZE];
		sprintf( temp, "%.3f", volume );
		m_strStaticSoundVolume = temp;
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
	//#######################


// Dialog Data
	enum { IDD = IDD_DIALOG_ADD_STATIC_SOUND };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	CEdit m_editBoxStaticSoundName;
	CEdit m_editBoxStaticSoundPosX;
	CEdit m_editBoxStaticSoundPosY;
	CEdit m_editBoxStaticSoundPosZ;
	CEdit m_editBoxStaticSoundRolloff;
	CEdit m_editBoxStaticSoundPitch;
	CEdit m_editBoxStaticSoundData;
	CEdit m_editBoxStaticSoundReferenceDistance;
	CEdit m_editBoxStaticSoundMaxDistance;
	CEdit m_editBoxStaticSoundVolume;

	CComboBox m_comboStaticSoundLoop;
	CComboBox m_comboStaticSoundPlay;

	//The above strings are converted to the following floating point values
	CFloat m_fStaticSoundPos[3];
	CFloat m_fStaticSoundPitch;
	CFloat m_fStaticSoundVolume;
	CFloat m_fStaticSoundRolloff;
	CFloat m_fStaticSoundMaxDistance;
	CFloat m_fStaticSoundReferenceDistance;
	CBool m_loop, m_play;

	CInt m_nameIndex; //selection

	virtual BOOL OnInitDialog();
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEditStaticSoundXPos();
	afx_msg void OnEnChangeEditStaticSoundYPos();
	afx_msg void OnEnChangeEditStaticSoundZPos();
	afx_msg void OnEnChangeEditStaticSoundPitch();
	afx_msg void OnEnChangeEditStaticSoundRolloff();
	afx_msg void OnCbnSelchangeComboStaticSoundLoop();
	afx_msg void OnCbnSelchangeComboStaticSoundPlay();
	afx_msg void OnBnClickedButtonStaticSoundData();
	afx_msg void OnEnChangeEditStaticSoundName();
	afx_msg void OnEnChangeEditStaticSoundReferenceDistance();
	afx_msg void OnEnChangeEditStaticSoundMaxDistance();

	CString m_strStaticSoundPosX;
	CString m_strStaticSoundPosY;
	CString m_strStaticSoundPosZ;
	CString m_strStaticSoundPitch;
	CString m_strStaticSoundName;
	CString m_strStaticSoundTempName;
	CString m_strStaticSoundDataPath;
	CString m_strStaticSoundPureDataPath;
	CString m_strStaticSoundRolloff;
	CString m_strStaticSoundMaxDistance;
	CString m_strStaticSoundReferenceDistance;
	CString m_strStaticSoundVolume;

	CBool m_create;
	CBool m_editMode;

public:
	afx_msg void OnEnChangeEditStaticSoundVolume();
public:
	virtual INT_PTR DoModal();
	afx_msg void OnBnClickedOk();
};
