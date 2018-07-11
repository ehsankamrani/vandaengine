//Copyright (C) 2018 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#pragma once
#include "afxwin.h"


// CAddWater dialog

class CAddWater : public CDialog
{
	DECLARE_DYNAMIC(CAddWater)

public:
	CAddWater(CWnd* pParent = NULL);   // standard constructor
	virtual ~CAddWater();
	virtual BOOL OnInitDialog();

	CString m_strDuDvMap;
	CString m_strNormalMap;

	CString m_strPureDuDvMap;
	CString m_strPureNormalMap;
	CString m_strWaterName;
	CString m_strTempWaterName; //for edit mode

	CString m_strWaterHeight;
	CString m_strWaterSpeed;
	CString m_strWaterUV;
	CString m_strWaterScale;
	CString m_strWaterCX;
	CString m_strWaterCY;
	CString m_strWaterCZ;
	CString m_strWaterLX;
	CString m_strWaterLY;
	CString m_strWaterLZ;

	CFloat m_fWaterHeight;
	CFloat m_fWaterSpeed;
	CFloat m_fWaterUV;
	CFloat m_fWaterScale;
	CFloat m_fWaterCPos[3];
	CFloat m_fWaterLPos[3];

	CBool m_editMode;
	//####public interface####	
	//The user just needs to use these functions
	CFloat* GetPos() { return m_fWaterCPos; }
	CFloat* GetLightPos() { return m_fWaterLPos; }
	CFloat GetHeight() { return m_fWaterHeight; }
	CFloat GetSpeed() { return m_fWaterSpeed; }
	CFloat GetUV(){ return m_fWaterUV; }
	CFloat GetScale() { return m_fWaterScale; }
	CChar* GetName() { return (CChar*)m_strWaterName.GetBuffer(m_strWaterName.GetLength()); m_strWaterName.ReleaseBuffer(); }
	CChar* GetTempName() { return (CChar*)m_strTempWaterName.GetBuffer(m_strTempWaterName.GetLength()); m_strTempWaterName.ReleaseBuffer(); }
	CChar* GetDuDvMap() {return (CChar*)m_strDuDvMap.GetBuffer(m_strDuDvMap.GetLength()); m_strDuDvMap.ReleaseBuffer(); }
	CChar* GetNormalMap() {return (CChar*)m_strNormalMap.GetBuffer(m_strNormalMap.GetLength()); m_strNormalMap.ReleaseBuffer(); }

	CVoid SetCreate( CBool create )
	{
		if( create ) m_create = CTrue;
		else m_create = CFalse;
	}
	CVoid SetName( CChar* name )
	{
		m_strWaterName = name;
	}
	CVoid SetNormalMapName( CChar* name )
	{
		m_strNormalMap = name;
	}
	CVoid SetDuDvMapName( CChar* name )
	{
		m_strDuDvMap = name;
	}
	CVoid SetPos( CFloat* pos )
	{
		CChar posX[MAX_NAME_SIZE];
		CChar posY[MAX_NAME_SIZE];
		CChar posZ[MAX_NAME_SIZE];
		sprintf( posX, "%f", pos[0] );
		sprintf( posY, "%f", pos[1] );
		sprintf( posZ, "%f", pos[2] );
		m_strWaterCX = posX;
		m_strWaterCY = posY;
		m_strWaterCZ = posZ;
	}
	CVoid SetLightPos( CFloat* pos )
	{
		CChar posX[MAX_NAME_SIZE];
		CChar posY[MAX_NAME_SIZE];
		CChar posZ[MAX_NAME_SIZE];
		sprintf( posX, "%f", pos[0] );
		sprintf( posY, "%f", pos[1] );
		sprintf( posZ, "%f", pos[2] );
		m_strWaterLX = posX;
		m_strWaterLY = posY;
		m_strWaterLZ = posZ;
	}
	CVoid SetHeight( CFloat height )
	{
		CChar temp[MAX_NAME_SIZE];
		sprintf( temp, "%f", height );
		m_strWaterHeight = temp;
	}
	CVoid SetSpeed( CFloat speed )
	{
		CChar temp[MAX_NAME_SIZE];
		sprintf( temp, "%f", speed );
		m_strWaterSpeed = temp;
	}
	CVoid SetUV( CFloat UV )
	{
		CChar temp[MAX_NAME_SIZE];
		sprintf( temp, "%f", UV );
		m_strWaterUV = temp;
	}
	CVoid SetScale( CFloat scale )
	{
		CChar temp[MAX_NAME_SIZE];
		sprintf( temp, "%f", scale );
		m_strWaterScale = temp;
	}
	CVoid SetEditMode( CBool editMode )
	{
		m_editMode = editMode;
	}
// Dialog Data
	enum { IDD = IDD_DIALOG_ADD_WATER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
private:
	afx_msg void OnBnClickedButtonWaterDudv();

	afx_msg void OnBnClickedButtonWaterNormal();


protected:
	virtual void OnOK();
public:
	CEdit m_editBoxDuDvMap;
	CEdit m_editBoxNormalMap;
	CEdit m_editBoxWaterName;
	CBool m_create;

	//CEdit m_editBoxHeight;
	//CEdit m_editBoxSpeed;
	//CEdit m_editBoxUV;
	//CEdit m_editBoxScale;
	//CEdit m_editBoxCX;
	//CEdit m_editBoxCY;
	//CEdit m_editBoxCZ;
	//CEdit m_editBoxLX;
	//CEdit m_editBoxLY;
	//CEdit m_editBoxLZ;

public:
	afx_msg void OnEnChangeEditWaterName();
	//afx_msg void OnEnChangeEditWaterHeight();
	//afx_msg void OnEnChangeEditWaterSpeed();
	//afx_msg void OnEnChangeEditWaterUV();
	//afx_msg void OnEnChangeEditWaterScale();
	//afx_msg void OnEnChangeEditWaterCX();
	//afx_msg void OnEnChangeEditWaterCY();
	//afx_msg void OnEnChangeEditWaterCZ();
	//afx_msg void OnEnChangeEditWaterLX();
	//afx_msg void OnEnChangeEditWaterLY();
	//afx_msg void OnEnChangeEditWaterLZ();

public:
	virtual INT_PTR DoModal();
public:
	CEdit m_editBoxHeight;
public:
	afx_msg void OnEnChangeEditWaterHeight();
public:
	CEdit m_editBoxSpeed;
public:
	CEdit m_editBoxUV;
public:
	CEdit m_editBoxScale;
public:
	CEdit m_editBoxCX;
public:
	CEdit m_editBoxCY;
public:
	CEdit m_editBoxCZ;
public:
	CEdit m_editBoxLX;
public:
	CEdit m_editBoxLY;
public:
	CEdit m_editBoxLZ;
public:
	afx_msg void OnEnChangeEditWaterSpeed();
public:
	afx_msg void OnEnChangeEditWaterUv();
public:
	afx_msg void OnEnChangeEditWaterScale();
public:
	afx_msg void OnEnChangeEditWaterCenterX();
public:
	afx_msg void OnEnChangeEditWaterCenterY();
public:
	afx_msg void OnEnChangeEditWaterCenterZ();
public:
	afx_msg void OnEnChangeEditWaterLightX();
public:
	afx_msg void OnEnChangeEditWaterLightY();
public:
	afx_msg void OnEnChangeEditWaterLightZ();
};
