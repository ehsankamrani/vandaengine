//Copyright (C) 2022 Ehsan Kamrani 
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
	CChar m_lastName[MAX_NAME_SIZE];
	CString m_strTempWaterName; //for edit mode

	CString m_strWaterHeight;
	CString m_strWaterSpeed;
	CString m_strWaterUV;
	CString m_strWaterTransparency;
	CString m_strWaterFogDensity;
	CString m_strWaterCX;
	CString m_strWaterCY;
	CString m_strWaterCZ;
	CString m_strWaterLX;
	CString m_strWaterLY;
	CString m_strWaterLZ;
	CString m_strWaterScaleX;
	CString m_strWaterScaleZ;
	CString m_strWaterRotateY;
	CBool m_isVisible;

	CFloat m_fWaterHeight;
	CFloat m_fWaterSpeed;
	CFloat m_fWaterUV;
	CFloat m_fWaterTransparency;
	CFloat m_fWaterFogDensity;
	CFloat m_fWaterCPos[3];
	CFloat m_fWaterLPos[3];
	CFloat m_fWaterScaleX;
	CFloat m_fWaterScaleZ;
	CFloat m_fWaterRotateY;

	CBool m_editMode;
	//####public interface####	
	//The user just needs to use these functions
	CFloat* GetPos() { return m_fWaterCPos; }
	CFloat* GetLightPos() { return m_fWaterLPos; }
	CFloat GetHeight() { return m_fWaterHeight; }
	CFloat GetSpeed() { return m_fWaterSpeed; }
	CFloat GetUV(){ return m_fWaterUV; }
	CFloat GetTransparency() { return m_fWaterTransparency; }
	CFloat GetFogDensity() { return m_fWaterFogDensity; }
	CChar* GetName() { return (CChar*)m_strWaterName.GetBuffer(m_strWaterName.GetLength()); m_strWaterName.ReleaseBuffer(); }
	CChar* GetLastName() { return m_lastName; }
	CChar* GetTempName() { return (CChar*)m_strTempWaterName.GetBuffer(m_strTempWaterName.GetLength()); m_strTempWaterName.ReleaseBuffer(); }
	CChar* GetDuDvMap() {return (CChar*)m_strDuDvMap.GetBuffer(m_strDuDvMap.GetLength()); m_strDuDvMap.ReleaseBuffer(); }
	CChar* GetNormalMap() {return (CChar*)m_strNormalMap.GetBuffer(m_strNormalMap.GetLength()); m_strNormalMap.ReleaseBuffer(); }
	CBool GetVisible() { return m_isVisible; }
	CFloat* GetColor() { return m_fWaterColor; }
	CFloat GetRotateY() { return m_fWaterRotateY; }
	CFloat GetScaleX() { return m_fWaterScaleX; }
	CFloat GetScaleZ() { return m_fWaterScaleZ; }

	CBool GetHasScript() { return m_hasScript; }
	CChar* GetScriptPath() { return m_strScript.GetBuffer(m_strScript.GetLength()); }
	CBool GetUpdateScript() { return m_scriptUpdated; }
	
	CVoid SetCreate( CBool create )
	{
		if( create ) m_create = CTrue;
		else m_create = CFalse;
	}
	CVoid SetName( CChar* name )
	{
		m_strWaterName = name;
	}
	CVoid SetLastName(CChar* name)
	{
		Cpy(m_lastName, name);
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
		sprintf( posX, "%.2f", pos[0] );
		sprintf( posY, "%.2f", pos[1] );
		sprintf( posZ, "%.2f", pos[2] );
		m_strWaterCX = posX;
		m_strWaterCY = posY;
		m_strWaterCZ = posZ;
	}
	CVoid SetLightPos( CFloat* pos )
	{
		CChar posX[MAX_NAME_SIZE];
		CChar posY[MAX_NAME_SIZE];
		CChar posZ[MAX_NAME_SIZE];
		sprintf( posX, "%.2f", pos[0] );
		sprintf( posY, "%.2f", pos[1] );
		sprintf( posZ, "%.2f", pos[2] );
		m_strWaterLX = posX;
		m_strWaterLY = posY;
		m_strWaterLZ = posZ;
	}
	CVoid SetHeight( CFloat height )
	{
		CChar temp[MAX_NAME_SIZE];
		sprintf( temp, "%.2f", height );
		m_strWaterHeight = temp;
	}
	CVoid SetSpeed( CFloat speed )
	{
		CChar temp[MAX_NAME_SIZE];
		sprintf( temp, "%.2f", speed );
		m_strWaterSpeed = temp;
	}
	CVoid SetUV( CFloat UV )
	{
		CChar temp[MAX_NAME_SIZE];
		sprintf( temp, "%.2f", UV );
		m_strWaterUV = temp;
	}
	CVoid SetScaleX(CFloat scaleX)
	{
		CChar temp[MAX_NAME_SIZE];
		sprintf(temp, "%.2f", scaleX);
		m_strWaterScaleX = temp;
	}
	CVoid SetScaleZ(CFloat scaleZ)
	{
		CChar temp[MAX_NAME_SIZE];
		sprintf(temp, "%.2f", scaleZ);
		m_strWaterScaleZ = temp;
	}
	CVoid SetRotateY(CFloat rotateY)
	{
		CChar temp[MAX_NAME_SIZE];
		sprintf(temp, "%.2f", rotateY);
		m_strWaterRotateY = temp;
	}

	CVoid SetTransparency(CFloat transparency)
	{
		CChar temp[MAX_NAME_SIZE];
		sprintf(temp, "%.2f", transparency);
		m_strWaterTransparency = temp;
	}
	CVoid SetFogDensity(CFloat density)
	{
		CChar temp[MAX_NAME_SIZE];
		sprintf(temp, "%.2f", density);
		m_strWaterFogDensity = temp;
	}
	CVoid SetEditMode( CBool editMode )
	{
		m_editMode = editMode;
	}

	CVoid SetVisible(CBool isVisible)
	{
		m_isVisible = isVisible;
	}
	CVoid SetColor(CFloat* color)
	{
		m_fWaterColor[0] = color[0];
		m_fWaterColor[1] = color[1];
		m_fWaterColor[2] = color[2];
	}

	CVoid SetHasScript(CBool hasScript) { m_hasScript = hasScript; }
	CVoid SetScriptPath(CChar* scriptPath) { m_strScript = scriptPath; }
	CVoid SetUpdateScript(CBool update) { m_scriptUpdated = update; }

// Dialog Data
	enum { IDD = IDD_DIALOG_ADD_WATER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
private:
	afx_msg void OnBnClickedButtonWaterDudv();

	afx_msg void OnBnClickedButtonWaterNormal();

	COLORREF m_waterColor;
	CBrush m_waterColorBrush;
	CFloat m_fWaterColor[3];

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
	CButton m_checkIsVisible;
	CEdit m_editBoxTransparency;
	afx_msg void OnEnChangeEditWaterTransparency();
	afx_msg void OnBnClickedButtonWaterColor();
	CEdit m_editBoxWaterColor;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CEdit m_editBoxFogDensity;
	afx_msg void OnEnChangeEditWaterFogDensity();
	CEdit m_editBoxRotY;
	CEdit m_editBoxScaleX;
	CEdit m_editBoxScaleZ;
	CRichEditCtrl m_editBoxScript;
	afx_msg void OnBnClickedBtnAddWaterScript();
	afx_msg void OnBnClickedBtnRemoveWaterScript();
	afx_msg void OnBnClickedButtonViewWaterScript();
	afx_msg void OnEnChangeEditWaterScaleX();
	afx_msg void OnEnChangeEditWaterScaleZ();
	afx_msg void OnEnChangeEditWaterRotateY();

	private:
		CBool m_scriptUpdated;
		CString m_strScript;
		CBool m_hasScript;
};
