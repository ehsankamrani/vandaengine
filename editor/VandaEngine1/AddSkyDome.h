//Copyright (C) 2020 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#pragma once
#include "afxwin.h"


// CAddSkyDome dialog

class CAddSkyDome : public CDialog
{
	DECLARE_DYNAMIC(CAddSkyDome)

public:
	CAddSkyDome(CWnd* pParent = NULL);   // standard constructor
	virtual ~CAddSkyDome();

// Dialog Data
	enum { IDD = IDD_DIALOG_ADD_SKYDOM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	CFloat m_fSkyDomePos[3];
	CFloat m_fSkyDomeRadius;
	CFloat m_fSkyDomeDampening;
	CFloat m_iSkyDomeSides;
	CFloat m_iSkyDomeSlices;
	CBool m_bSkyDomeExponential;

	virtual BOOL OnInitDialog();
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()
public:

	//####public interface####	
	//The user just needs to use these functions
	CFloat* GetPos() { return m_fSkyDomePos; }
	CChar* GetName() { return (CChar*)m_strSkyDomeName.GetBuffer(m_strSkyDomeName.GetLength()); m_strSkyDomeName.ReleaseBuffer(); }
	CChar* GetTempName() { return (CChar*)m_strSkyDomeTempName.GetBuffer(m_strSkyDomeTempName.GetLength()); m_strSkyDomeTempName.ReleaseBuffer(); }
	CChar* GetPurePath() { return (CChar*)m_strSkyDomePurePath.GetBuffer(m_strSkyDomePurePath.GetLength()); m_strSkyDomePurePath.ReleaseBuffer(); }
	CChar* GetPath() { return (CChar*)m_strSkyDomePath.GetBuffer(m_strSkyDomePath.GetLength()); m_strSkyDomePath.ReleaseBuffer(); }
	CFloat GetRadius() { return m_fSkyDomeRadius; }
	CInt GetSides() { return m_iSkyDomeSides; }
	CInt GetSlices() { return m_iSkyDomeSlices; }
	CFloat GetDampening() { return m_fSkyDomeDampening; }
	CBool GetExponential() { return m_bSkyDomeExponential; }

	CVoid SetPos( CFloat* pos )
	{
		CChar posX[MAX_NAME_SIZE];
		CChar posY[MAX_NAME_SIZE];
		CChar posZ[MAX_NAME_SIZE];
		sprintf( posX, "%.3f", pos[0] );
		sprintf( posY, "%.3f", pos[1] );
		sprintf( posZ, "%.3f", pos[2] );
		m_strSkyDomePosX = posX;
		m_strSkyDomePosY = posY;
		m_strSkyDomePosZ = posZ;
	}

	CVoid SetCreate( CBool create )
	{
		if( create )
			m_create = CTrue;
		else
			m_create = CFalse;
	}

	CVoid SetEditMode( CBool editMode )
	{
		m_editMode = editMode;
	}

	CVoid SetName( CChar* name )
	{
		m_strSkyDomeName = name;
	}

	CVoid SetPath( CChar * path )
	{
		m_strSkyDomePath = path;
	}

	CVoid SetRadius( CFloat radius )
	{
		CChar temp[MAX_NAME_SIZE];
		sprintf( temp, "%.3f", radius );
		m_strSkyDomeRadius = temp;
	}
	
	CVoid SetSides( CInt sides )
	{
		CChar temp[MAX_NAME_SIZE];
		sprintf( temp, "%i", sides );
		m_strSkyDomeSides = temp;
	}

	CVoid SetSlices( CInt slices )
	{
		CChar temp[MAX_NAME_SIZE];
		sprintf( temp, "%i", slices );
		m_strSkyDomeSlices = temp;
	}

	CVoid SetDampening( CFloat dampening )
	{
		CChar temp[MAX_NAME_SIZE];
		sprintf( temp, "%.3f", dampening );
		m_strSkyDomeDampening = temp;
	}

	CVoid SetExponential( CBool exponential )
	{
		m_bSkyDomeExponential = exponential;
	}
	//#######################

	CEdit m_editBoxSkyDomeName;
	CEdit m_editBoxSkyDomeData;
	CEdit m_editBoxSkyDomePosX;
	CEdit m_editBoxSkyDomePosY;
	CEdit m_editBoxSkyDomePosZ;
	CEdit m_editBoxSkyDomeSides;
	CEdit m_editBoxSkyDomeSlices;
	CEdit m_editBoxSkyDomeRadius;
	CEdit m_editBoxSkyDomeDampening;

	CComboBox m_comboSkyDomeExponential;
	afx_msg void OnEnChangeEditSkydomeName();
	afx_msg void OnEnChangeEditSkydomeXPos();
	afx_msg void OnEnChangeEditSkydomeYPos();
	afx_msg void OnEnChangeEditSkydomeRadius();
	afx_msg void OnEnChangeEditSkydomeDampening();
	afx_msg void OnEnChangeEditSkydomeZPos();
	afx_msg void OnEnChangeEditSkydomeSides();
	afx_msg void OnEnChangeEditSkydomeSlices();
	afx_msg void OnCbnSelchangeComboSkydomExponential();
	afx_msg void OnBnClickedButtonSkydomPath();

public:
	CString m_strSkyDomePosX;
	CString m_strSkyDomePosY;
	CString m_strSkyDomePosZ;
	CString m_strSkyDomeRadius;
	CString m_strSkyDomeName;
	CString m_strSkyDomePath;
	CString m_strSkyDomePurePath;
	CString m_strSkyDomeSides;
	CString m_strSkyDomeSlices;
	CString m_strSkyDomeDampening;

	CString m_strSkyDomeTempName;
	CBool m_create;
	CBool m_editMode;
public:
	virtual INT_PTR DoModal();
	afx_msg void OnBnClickedOk();
	afx_msg void OnEnChangeEditSkydomPath();
};
