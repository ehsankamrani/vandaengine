//Copyright (C) 2023 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

// AddWater.cpp : implementation file
//

#include "stdafx.h"
#include "VandaEngineEditor.h"
#include "AddWater.h"
#include  "AFXPRIV.H"
#include "ViewScript.h"

// CAddWater dialog

IMPLEMENT_DYNAMIC(CAddWater, CDialog)

CAddWater::CAddWater(CWnd* pParent /*=NULL*/)
	: CDialog(CAddWater::IDD, pParent)
{
	m_create = CFalse;
	m_editMode = CFalse;
	m_scriptUpdated = CFalse;
	m_hasScript = CFalse;
}

CAddWater::~CAddWater()
{
	m_strScript.ReleaseBuffer();
}

BOOL CAddWater::OnInitDialog()
{
	if (m_create)
	{
		m_waterColor = RGB(58, 122, 186);
	}
	else if (m_editMode)
	{
		m_waterColor = RGB((CInt)(m_fWaterColor[0] * 255), (CInt)(m_fWaterColor[1] * 255), (CInt)(m_fWaterColor[2] * 255));
	}
	m_waterColorBrush.DeleteObject();
	m_waterColorBrush.CreateSolidBrush(m_waterColor);

	CDialog::OnInitDialog();

	if( m_create )
	{
		m_strWaterSpeed = "0.08f";
		m_strWaterUV = "4.0f";
		m_strWaterTransparency = "0.5f";
		m_strWaterFogDensity = "0.1f";

		m_strWaterCX = "0.0f";
		m_strWaterCY = "0.0f";
		m_strWaterCZ = "0.0f";

		m_strWaterScaleX = "20.0f";
		m_strWaterScaleZ = "20.0f";

		m_strWaterRotateY = "0.0f";

		m_strWaterLX = "25.0f";
		m_strWaterLY = "3.0f";
		m_strWaterLZ = "25.0f";

		m_fWaterColor[0] = 0.2274f;
		m_fWaterColor[1] = 0.4784f;
		m_fWaterColor[2] = 0.7294f;

		m_strWaterHeight = "0.0f";
		CChar DuDvPath[MAX_NAME_SIZE];
		CChar NormalMapPath[MAX_NAME_SIZE];
		sprintf( DuDvPath, "%s%s", g_pathProperties.m_waterPath, "dudvmap.dds" );
		m_strDuDvMap = DuDvPath;
		m_strPureDuDvMap = "dudvmap";
		sprintf( NormalMapPath, "%s%s", g_pathProperties.m_waterPath, "normalmap.dds" );
		m_strNormalMap = NormalMapPath;
		m_strPureNormalMap = "normalmap";
		m_isVisible = CTrue;
		m_shadow = CTrue;
		m_sunReflection = CTrue;
	}

	if (m_editMode)
	{
		if (m_hasScript)
		{
			m_editBoxScript.SetWindowTextA(m_strScript);
		}
	}

	m_editBoxDuDvMap.SetWindowTextA( m_strDuDvMap );
	m_editBoxNormalMap.SetWindowTextA( m_strNormalMap );
	m_editBoxWaterName.SetWindowTextA( m_strWaterName );
	m_editBoxHeight.SetWindowTextA( m_strWaterHeight );
	m_editBoxSpeed.SetWindowTextA( m_strWaterSpeed );
	m_editBoxUV.SetWindowTextA( m_strWaterUV );
	m_editBoxTransparency.SetWindowTextA(m_strWaterTransparency);
	m_editBoxFogDensity.SetWindowTextA(m_strWaterFogDensity);
	m_editBoxCX.SetWindowTextA( m_strWaterCX );
	m_editBoxCY.SetWindowTextA( m_strWaterCY );
	m_editBoxCZ.SetWindowTextA( m_strWaterCZ );
	m_editBoxLX.SetWindowTextA( m_strWaterLX );
	m_editBoxLY.SetWindowTextA( m_strWaterLY );
	m_editBoxLZ.SetWindowTextA( m_strWaterLZ );
	m_editBoxScaleX.SetWindowTextA(m_strWaterScaleX);
	m_editBoxScaleZ.SetWindowTextA(m_strWaterScaleZ);
	m_editBoxRotY.SetWindowTextA(m_strWaterRotateY);

	if (m_isVisible)
		m_checkIsVisible.SetCheck(BST_CHECKED);
	else
		m_checkIsVisible.SetCheck(BST_UNCHECKED);

	if (m_shadow)
		m_checkShadow.SetCheck(BST_CHECKED);
	else
		m_checkShadow.SetCheck(BST_UNCHECKED);

	if (m_sunReflection)
		m_checkSunReflection.SetCheck(BST_CHECKED);
	else
		m_checkSunReflection.SetCheck(BST_UNCHECKED);

	m_strTempWaterName = m_strWaterName;

	m_editBoxHeight.EnableWindow( FALSE );
	return TRUE;
}

void CAddWater::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_WATER_DUDV, m_editBoxDuDvMap);
	DDX_Control(pDX, IDC_EDIT_WATER_NORMAL, m_editBoxNormalMap);
	DDX_Control(pDX, IDC_EDIT_WATER_NAME, m_editBoxWaterName);
	DDX_Control(pDX, IDC_EDIT_WATER_HEIGHT, m_editBoxHeight);
	DDX_Control(pDX, IDC_EDIT_WATER_SPEED, m_editBoxSpeed);
	DDX_Control(pDX, IDC_EDIT_WATER_UV, m_editBoxUV);
	DDX_Control(pDX, IDC_EDIT_WATER_CENTER_X, m_editBoxCX);
	DDX_Control(pDX, IDC_EDIT_WATER_CENTER_Y, m_editBoxCY);
	DDX_Control(pDX, IDC_EDIT_WATER_CENTER_Z, m_editBoxCZ);
	DDX_Control(pDX, IDC_EDIT_WATER_LIGHT_X, m_editBoxLX);
	DDX_Control(pDX, IDC_EDIT_WATER_LIGHT_Y, m_editBoxLY);
	DDX_Control(pDX, IDC_EDIT_WATER_LIGHT_Z, m_editBoxLZ);
	DDX_Control(pDX, IDC_CHECK_IS_WATER_VISIBLE, m_checkIsVisible);
	DDX_Control(pDX, IDC_EDIT_WATER_TRANSPARENCY, m_editBoxTransparency);
	DDX_Control(pDX, IDC_EDIT_WATER_COLOR, m_editBoxWaterColor);
	DDX_Control(pDX, IDC_EDIT_WATER_FOG_DENSITy, m_editBoxFogDensity);
	DDX_Control(pDX, IDC_EDIT_WATER_ROTATE_Y, m_editBoxRotY);
	DDX_Control(pDX, IDC_EDIT_WATER_SCALE_X, m_editBoxScaleX);
	DDX_Control(pDX, IDC_EDIT_WATER_SCALE_Z, m_editBoxScaleZ);
	DDX_Control(pDX, IDC_EDIT_WATER_SCRIPT, m_editBoxScript);
	DDX_Control(pDX, IDC_CHECK_WATER_SHADOW, m_checkShadow);
	DDX_Control(pDX, IDC_CHECK_WATER_SUN_REFLECTION, m_checkSunReflection);
}


BEGIN_MESSAGE_MAP(CAddWater, CDialog)
	ON_BN_CLICKED(ID_BUTTON_WATER_DUDV, &CAddWater::OnBnClickedButtonWaterDudv)
	ON_BN_CLICKED(ID_BUTTON_WATER_NORMAL, &CAddWater::OnBnClickedButtonWaterNormal)
	ON_EN_CHANGE(IDC_EDIT_WATER_NAME, &CAddWater::OnEnChangeEditWaterName)
	ON_EN_CHANGE(IDC_EDIT_WATER_HEIGHT, &CAddWater::OnEnChangeEditWaterHeight)
	ON_EN_CHANGE(IDC_EDIT_WATER_SPEED, &CAddWater::OnEnChangeEditWaterSpeed)
	ON_EN_CHANGE(IDC_EDIT_WATER_UV, &CAddWater::OnEnChangeEditWaterUv)
	ON_EN_CHANGE(IDC_EDIT_WATER_CENTER_X, &CAddWater::OnEnChangeEditWaterCenterX)
	ON_EN_CHANGE(IDC_EDIT_WATER_CENTER_Y, &CAddWater::OnEnChangeEditWaterCenterY)
	ON_EN_CHANGE(IDC_EDIT_WATER_CENTER_Z, &CAddWater::OnEnChangeEditWaterCenterZ)
	ON_EN_CHANGE(IDC_EDIT_WATER_LIGHT_X, &CAddWater::OnEnChangeEditWaterLightX)
	ON_EN_CHANGE(IDC_EDIT_WATER_LIGHT_Y, &CAddWater::OnEnChangeEditWaterLightY)
	ON_EN_CHANGE(IDC_EDIT_WATER_LIGHT_Z, &CAddWater::OnEnChangeEditWaterLightZ)
	ON_EN_CHANGE(IDC_EDIT_WATER_TRANSPARENCY, &CAddWater::OnEnChangeEditWaterTransparency)
	ON_BN_CLICKED(IDC_BUTTON_WATER_COLOR, &CAddWater::OnBnClickedButtonWaterColor)
	ON_WM_CTLCOLOR()
	ON_EN_CHANGE(IDC_EDIT_WATER_FOG_DENSITy, &CAddWater::OnEnChangeEditWaterFogDensity)
	ON_BN_CLICKED(IDC_BTN_ADD_WATER_SCRIPT, &CAddWater::OnBnClickedBtnAddWaterScript)
	ON_BN_CLICKED(IDC_BTN_REMOVE_WATER_SCRIPT, &CAddWater::OnBnClickedBtnRemoveWaterScript)
	ON_BN_CLICKED(IDC_BUTTON_VIEW_WATER_SCRIPT, &CAddWater::OnBnClickedButtonViewWaterScript)
	ON_EN_CHANGE(IDC_EDIT_WATER_SCALE_X, &CAddWater::OnEnChangeEditWaterScaleX)
	ON_EN_CHANGE(IDC_EDIT_WATER_SCALE_Z, &CAddWater::OnEnChangeEditWaterScaleZ)
	ON_EN_CHANGE(IDC_EDIT_WATER_ROTATE_Y, &CAddWater::OnEnChangeEditWaterRotateY)
END_MESSAGE_MAP()


// CAddWater message handlers

void CAddWater::OnBnClickedButtonWaterDudv()
{
	// TODO: Add your control notification handler code here
	CFileDialog dlgOpen(TRUE, _T("*.dds"), _T(""), OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR,
		_T("DDS File (*.dds)|*.dds||"), NULL, NULL);
	if( IDOK == dlgOpen.DoModal() )
	{
		m_strDuDvMap = (CString)dlgOpen.GetPathName();
		m_strPureDuDvMap = dlgOpen.GetFileTitle();

		//CChar* originalDuDvPath = (CChar*)m_strDuDvMap.GetBuffer(m_strDuDvMap.GetLength() ); ;
		//CChar* tempDuDvPath = GetAfterPath( originalDuDvPath );
		//CChar DuDvPath[MAX_NAME_SIZE];
		//sprintf( DuDvPath, "%s%s", g_pathProperties.m_waterPath, tempDuDvPath );
		//m_strDuDvMap = DuDvPath;
		//m_strDuDvMap.ReleaseBuffer();

		m_editBoxDuDvMap.SetWindowText( m_strDuDvMap );
	}
}

void CAddWater::OnBnClickedButtonWaterNormal()
{
	// TODO: Add your control notification handler code here
	CFileDialog dlgOpen(TRUE, _T("*.dds"), _T(""), OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR,
		_T("DDS File (*.dds)|*.dds||"), NULL, NULL);
	if( IDOK == dlgOpen.DoModal() )
	{
		m_strNormalMap = (CString)dlgOpen.GetPathName();
		m_strPureNormalMap = dlgOpen.GetFileTitle();

		//CChar* originalNormalMapPath = (CChar*)m_strNormalMap.GetBuffer(m_strNormalMap.GetLength() ); ;
		//CChar* tempNormalMapPath = GetAfterPath( originalNormalMapPath );
		//CChar NormalMapPath[MAX_NAME_SIZE];
		//sprintf( NormalMapPath, "%s%s", g_pathProperties.m_waterPath, tempNormalMapPath );
		//m_strNormalMap = NormalMapPath;
		//m_strNormalMap.ReleaseBuffer();

		m_editBoxNormalMap.SetWindowText( m_strNormalMap );
	}
}

void CAddWater::OnOK()
{
	CBool compare = CFalse;
	if( !m_strWaterName.IsEmpty() )
	{
		compare = CTrue;
		if( m_editMode )
		{
			CChar name[MAX_NAME_SIZE];
			CChar tempName[MAX_NAME_SIZE];
			Cpy(name, (LPCSTR)m_strWaterName);
			Cpy(tempName, (LPCSTR)m_strTempWaterName);

			StringToUpper(name);
			StringToUpper(tempName);

			if (Cmp(name, tempName))
				compare = CFalse;
		}
	}
	else
		compare = CFalse;

	if( compare )
	{
		for( std::vector<std::string>::iterator it = g_engineObjectNames.begin(); it != g_engineObjectNames.end();it++ )
		{
			CChar engineObjectCapsName[MAX_NAME_SIZE];
			Cpy(engineObjectCapsName, (*it).c_str());
			StringToUpper(engineObjectCapsName);

			CChar currentObjectName[MAX_NAME_SIZE];
			Cpy(currentObjectName, (LPCSTR)m_strWaterName);
			StringToUpper(currentObjectName);

			if (Cmp(currentObjectName, engineObjectCapsName))
			{
				MessageBox("This name already exists. Please select another name!", "Vanda Engine Error", MB_OK | MB_ICONERROR);
				return;
			}
		}
	}
	CInt checkState;
	checkState = m_checkIsVisible.GetCheck();
	if (checkState == BST_CHECKED)
		m_isVisible = CTrue;
	else
		m_isVisible = CFalse;

	checkState = m_checkShadow.GetCheck();
	if (checkState == BST_CHECKED)
		m_shadow = CTrue;
	else
		m_shadow = CFalse;

	checkState = m_checkSunReflection.GetCheck();
	if (checkState == BST_CHECKED)
		m_sunReflection = CTrue;
	else
		m_sunReflection = CFalse;

	// TODO: Add your specialized code here and/or call the base class
	if (m_strNormalMap.IsEmpty() || m_strDuDvMap.IsEmpty() || m_strWaterName.IsEmpty() || m_strWaterHeight.IsEmpty() ||
		m_strWaterSpeed.IsEmpty() || m_strWaterUV.IsEmpty() || m_strWaterTransparency.IsEmpty() ||
		m_strWaterFogDensity.IsEmpty() || m_strWaterCX.IsEmpty() || m_strWaterCY.IsEmpty() || m_strWaterCZ.IsEmpty() ||
		m_strWaterRotateY.IsEmpty() || m_strWaterScaleX.IsEmpty() || m_strWaterScaleZ.IsEmpty() ||
		m_strWaterLX.IsEmpty() || m_strWaterLY.IsEmpty() || m_strWaterLZ.IsEmpty())
	{
		MessageBox("Please Fill In All Of The Required Fields", "Vanda Engine Error", MB_OK | MB_ICONERROR);
		return;
	}

	if (m_fWaterScaleX < 0.01f || m_fWaterScaleZ < 0.01f)
	{
		MessageBox("Water scale must be greater than 0.01", "Vanda Engine Error", MB_OK | MB_ICONERROR);
		return;
	}
	
	if (m_fWaterFogDensity < 0.0f)
	{
		MessageBox("Fog density must be equal or greater than 0.0", "Vanda Engine Error", MB_OK | MB_ICONERROR);
		return;
	}

	if (m_fWaterTransparency < 0.0f || m_fWaterTransparency > 1.0f)
	{
		MessageBox("Transparency must be in [0.0,1.0] range", "Vanda Engine Error", MB_OK | MB_ICONERROR);
		return;
	}

	CChar name[MAX_NAME_SIZE];
	Cpy(name, (LPCSTR)m_strWaterName);
	StringToUpper(name);

	if (Cmp(name, "THIS"))
	{
		MessageBox("'this' is a reserved name. Please select another name!", "Vanda Engine Error", MB_OK | MB_ICONERROR);
		return;
	}

	CDialog::OnOK();
}
void CAddWater::OnEnChangeEditWaterName()
{
	m_editBoxWaterName.GetWindowTextA( m_strWaterName );
}

INT_PTR CAddWater::DoModal()
{
	CDialogTemplate dlt;
	INT_PTR nResult;
	// load dialog template
	if (!dlt.Load(MAKEINTRESOURCE(CAddWater::IDD))) return -1;
	// set the font, for example "Arial", 10 pts.
	dlt.SetFont("Arial", 8);
	// get pointer to the modified dialog template
	LPSTR pdata = (LPSTR)GlobalLock(dlt.m_hTemplate);
	// let MFC know that you are using your own template
	m_lpszTemplateName = NULL;
	InitModalIndirect(pdata);
	// display dialog box
	nResult = CDialog::DoModal();
	// unlock memory object
	GlobalUnlock(dlt.m_hTemplate);
	return nResult;
}

void CAddWater::OnEnChangeEditWaterHeight()
{
	m_editBoxHeight.GetWindowTextA( m_strWaterHeight );
	m_fWaterHeight = atof( m_strWaterHeight );
}

void CAddWater::OnEnChangeEditWaterSpeed()
{
	m_editBoxSpeed.GetWindowTextA( m_strWaterSpeed );
	m_fWaterSpeed = atof( m_strWaterSpeed );
}

void CAddWater::OnEnChangeEditWaterUv()
{
	m_editBoxUV.GetWindowTextA( m_strWaterUV );
	m_fWaterUV = atof( m_strWaterUV );
}

void CAddWater::OnEnChangeEditWaterCenterX()
{
	m_editBoxCX.GetWindowTextA( m_strWaterCX );
	m_fWaterCPos[0] = atof( m_strWaterCX );
}

void CAddWater::OnEnChangeEditWaterCenterY()
{
	m_editBoxCY.GetWindowTextA( m_strWaterCY );
	m_fWaterCPos[1] = atof( m_strWaterCY );
}

void CAddWater::OnEnChangeEditWaterCenterZ()
{
	m_editBoxCZ.GetWindowTextA( m_strWaterCZ );
	m_fWaterCPos[2] = atof( m_strWaterCZ );
}

void CAddWater::OnEnChangeEditWaterLightX()
{
	m_editBoxLX.GetWindowTextA( m_strWaterLX );
	m_fWaterLPos[0] = atof( m_strWaterLX );
}

void CAddWater::OnEnChangeEditWaterLightY()
{
	m_editBoxLY.GetWindowTextA( m_strWaterLY );
	m_fWaterLPos[1] = atof( m_strWaterLY );
}

void CAddWater::OnEnChangeEditWaterLightZ()
{
	m_editBoxLZ.GetWindowTextA( m_strWaterLZ );
	m_fWaterLPos[2] = atof( m_strWaterLZ );
}



void CAddWater::OnEnChangeEditWaterTransparency()
{
	m_editBoxTransparency.GetWindowTextA(m_strWaterTransparency);
	m_fWaterTransparency = atof(m_strWaterTransparency);
}


void CAddWater::OnBnClickedButtonWaterColor()
{
	CColorDialog dlg;
	if (dlg.DoModal() == IDOK)
	{
		m_waterColor = dlg.GetColor();
		m_fWaterColor[0] = (CFloat)GetRValue(m_waterColor) / 255.f;
		m_fWaterColor[1] = (CFloat)GetGValue(m_waterColor) / 255.f;
		m_fWaterColor[2] = (CFloat)GetBValue(m_waterColor) / 255.f;
		m_waterColorBrush.DeleteObject();
		m_waterColorBrush.CreateSolidBrush(m_waterColor);
		m_editBoxWaterColor.RedrawWindow();
	}
}


HBRUSH CAddWater::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	switch (pWnd->GetDlgCtrlID())
	{
	case IDC_EDIT_WATER_COLOR:
		pDC->SetBkColor(m_waterColor);
		return m_waterColorBrush;
	}
	return CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
}


void CAddWater::OnEnChangeEditWaterFogDensity()
{
	m_editBoxFogDensity.GetWindowTextA(m_strWaterFogDensity);
	m_fWaterFogDensity = atof(m_strWaterFogDensity);
}


void CAddWater::OnBnClickedBtnAddWaterScript()
{
	CFileDialog dlgOpen(TRUE, _T("*.lua"), _T(""), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR,
		_T("LUA File (*.lua)|*.lua||"), NULL, NULL);
	if (IDOK == dlgOpen.DoModal())
	{
		g_testScript = CTrue;
		CString m_string;
		m_string = (CString)dlgOpen.GetPathName();

		lua_close(g_lua);
		g_lua = LuaNewState();
		LuaOpenLibs(g_lua);
		LuaRegisterFunctions(g_lua);

		int s = luaL_loadfile(g_lua, m_string);
		if (s == 0) {
			// execute Lua program
			s = LuaExecuteProgram(g_lua);
		}
		if (s == 0)
		{
			m_editBoxScript.SetWindowText(m_string);
			m_strScript = m_string;
			m_scriptUpdated = CTrue;
			m_hasScript = CTrue;
			PrintInfo("\nScript loaded scuccessfully", COLOR_GREEN);
		}
		else
		{
			MessageBox("Script contains error(s).\nPlease use script editor to fix the issue(s)", "Error", MB_OK | MB_ICONERROR);
		}
		g_testScript = CFalse;
	}
}


void CAddWater::OnBnClickedBtnRemoveWaterScript()
{
	if (!m_hasScript)
	{
		MessageBox("No script was found!", "Error", MB_OK | MB_ICONERROR);
		return;
	}

	if (m_hasScript)
	{
		if (MessageBox("Remove current script?", "Warning", MB_YESNO) == IDYES)
		{
			m_editBoxScript.SetWindowTextA("\n");
			m_strScript.Empty();
			m_hasScript = CFalse;
		}
	}
}


void CAddWater::OnBnClickedButtonViewWaterScript()
{
	if (!m_hasScript)
	{
		MessageBox("Please add a script!", "Error", MB_OK | MB_ICONERROR);
		return;
	}

	CViewScript* dlg = CNew(CViewScript);
	dlg->SetScriptPath(m_strScript.GetBuffer(m_strScript.GetLength()));
	m_strScript.ReleaseBuffer();
	dlg->DoModal();
	CDelete(dlg);
}


void CAddWater::OnEnChangeEditWaterScaleX()
{
	m_editBoxScaleX.GetWindowTextA(m_strWaterScaleX);
	m_fWaterScaleX = atof(m_strWaterScaleX);
}


void CAddWater::OnEnChangeEditWaterScaleZ()
{
	m_editBoxScaleZ.GetWindowTextA(m_strWaterScaleZ);
	m_fWaterScaleZ = atof(m_strWaterScaleZ);
}


void CAddWater::OnEnChangeEditWaterRotateY()
{
	m_editBoxRotY.GetWindowTextA(m_strWaterRotateY);
	m_fWaterRotateY = atof(m_strWaterRotateY);
}
