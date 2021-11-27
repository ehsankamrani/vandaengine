//Copyright (C) 2021 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

// AddGUIText.cpp : implementation file
//

#include "stdafx.h"
#include "VandaEngine1.h"
#include "AddGUIText.h"
#include "afxdialogex.h"


// CAddGUIText dialog

IMPLEMENT_DYNAMIC(CAddGUIText, CDialog)

CAddGUIText::CAddGUIText(CWnd* pParent /*=NULL*/)
	: CDialog(CAddGUIText::IDD, pParent)
{
	m_create = CTrue;
}

CAddGUIText::~CAddGUIText()
{
}

void CAddGUIText::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_TEXT, m_editText);
	DDX_Control(pDX, IDC_EDIT_SIZE, m_editSize);
	DDX_Control(pDX, IDC_COMBO_TYPE, m_comboType);
	DDX_Control(pDX, IDC_EDIT_COLOR, m_editColor);
	DDX_Control(pDX, IDC_EDIT_NAME, m_editName);
	DDX_Control(pDX, IDC_EDIT_POS_X, m_editPosX);
	DDX_Control(pDX, IDC_EDIT_POS_Y, m_editPosY);
}


BEGIN_MESSAGE_MAP(CAddGUIText, CDialog)
	ON_BN_CLICKED(IDOK, &CAddGUIText::OnBnClickedOk)
	ON_EN_CHANGE(IDC_EDIT_SIZE, &CAddGUIText::OnEnChangeEditSize)
	ON_EN_CHANGE(IDC_EDIT_TEXT, &CAddGUIText::OnEnChangeEditText)
	ON_BN_CLICKED(IDC_BUTTON_COLOR, &CAddGUIText::OnBnClickedButtonColor)
	ON_WM_CTLCOLOR()
	ON_EN_CHANGE(IDC_EDIT_NAME, &CAddGUIText::OnEnChangeEditName)
	ON_EN_CHANGE(IDC_EDIT_POS_X, &CAddGUIText::OnEnChangeEditPosX)
	ON_EN_CHANGE(IDC_EDIT_POS_Y, &CAddGUIText::OnEnChangeEditPosY)
END_MESSAGE_MAP()


// CAddGUIText message handlers

CVoid CAddGUIText::SetName(CChar* name)
{
	m_strName = name;
	m_strTempName = name;
}

CVoid CAddGUIText::SetPosition(CVec2f pos)
{
	m_fPosX = pos.x;
	m_fPosY = pos.y;

	m_strPosX.Format("%.3f", m_fPosX);
	m_strPosY.Format("%.3f", m_fPosY);
}

CVoid CAddGUIText::SetSize(CFloat size)
{
	m_fTextSize = size;
	m_strTextSize.Format("%.3f", m_fTextSize);
}

CVoid CAddGUIText::SetColor(CVec3f color)
{
	m_fColor[0] = color.x;
	m_fColor[1] = color.y;
	m_fColor[2] = color.z;
	m_fColor[3] = 1.0f;

	m_color = RGB(CInt(color.x * 255.f), CInt(color.y * 255.f), CInt(color.z * 255.f));
}

CVoid CAddGUIText::SetFontType(CFontType type)
{
	m_fontType = type;
}

CVoid CAddGUIText::SetText(CChar* text)
{
	m_strText = text;
}

CChar* CAddGUIText::GetName()
{
	return m_strName.GetBuffer(m_strName.GetLength());
}

CVec2f CAddGUIText::GetPosition()
{
	CVec2f pos(m_fPosX, m_fPosY);
	return pos;
}

CFloat CAddGUIText::GetSize()
{
	return m_fTextSize;
}

CVec3f CAddGUIText::GetColor()
{
	CVec3f color(m_fColor[0], m_fColor[1], m_fColor[2]);
	return color;
}

CFontType CAddGUIText::GetFontType()
{
	return m_fontType;
}

CChar* CAddGUIText::GetText()
{
	return m_strText.GetBuffer(m_strText.GetLength());
}

void CAddGUIText::OnBnClickedOk()
{
	if (m_strText.IsEmpty() || m_strTextSize.IsEmpty() || m_strName.IsEmpty() || m_strPosX.IsEmpty() || m_strPosY.IsEmpty())
	{
		MessageBox("Please Fill In All Of The Required Fields", "Vanda Engine Error", MB_OK | MB_ICONERROR);
		return;
	}
	CBool compare = CFalse;
	if (!m_strName.IsEmpty())
	{
		compare = CTrue;
		if (!m_create)
		{
			CChar name[MAX_NAME_SIZE];
			CChar tempName[MAX_NAME_SIZE];
			Cpy(name, (LPCSTR)m_strName);
			Cpy(tempName, (LPCSTR)m_strTempName);

			StringToUpper(name);
			StringToUpper(tempName);

			if (Cmp(name, tempName))
				compare = CFalse;
		}

	}
	else
		compare = CFalse;

	if (compare)
	{
		for (std::vector<std::string>::iterator it = g_guiNames.begin(); it != g_guiNames.end(); it++)
		{
			CChar engineObjectCapsName[MAX_NAME_SIZE];
			Cpy(engineObjectCapsName, (*it).c_str());
			StringToUpper(engineObjectCapsName);

			CChar currentObjectName[MAX_NAME_SIZE];
			Cpy(currentObjectName, (LPCSTR)m_strName);
			StringToUpper(currentObjectName);


			if (Cmp(currentObjectName, engineObjectCapsName))
			{
				MessageBox("This name already exists. Please select another name!", "Vanda Engine Error", MB_OK | MB_ICONERROR);
				return;
			}
		}
	}
	CInt currentSelection = m_comboType.GetCurSel();
	if (currentSelection == 0)
		m_fontType = eFONT_ARIAL;
	else if (currentSelection == 1)
		m_fontType = eFONT_TIMES_NEW_ROMAN;

	if (m_fPosX < 0.0f || m_fPosX > g_width)
	{
		CChar temp[MAX_NAME_SIZE];
		sprintf(temp, "Please Enter a value between 0.0 and %i for X position", g_width);
		MessageBox(temp);
		return;
	}
	if (m_fPosY < 0.0f || m_fPosY > g_height)
	{
		CChar temp[MAX_NAME_SIZE];
		sprintf(temp, "Please Enter a value between 0.0 and %i for Y position", g_height);
		MessageBox(temp);
		return;
	}
	if (m_create)
	{
		CGUIText* guiText = CNew(CGUIText);
		guiText->SetName(m_strName.GetBuffer(m_strName.GetLength()));
		CVec2f pos(m_fPosX, m_fPosY);
		guiText->SetPosition(pos);
		guiText->SetSize(m_fTextSize);
		CVec3f color(m_fColor[0], m_fColor[1], m_fColor[2]);
		guiText->SetColor(color);
		guiText->SetText(m_strText.GetBuffer(m_strText.GetLength()));
		guiText->SetType(m_fontType);
		if (!guiText->SetFont())
		{
			CDelete(guiText);
			return;
		}

		if (!Cmp(g_currentPackageAndGUIName, "\n"))
		{
			guiText->SetPackageName(g_currentGUIPackageName);
			guiText->SetGUIName(g_currentGUIName);
		}

		g_guiTexts.push_back(guiText);
		g_guiNames.push_back(m_strName.GetBuffer(m_strName.GetLength()));
		ex_pVandaEngine1Dlg->InsertItemToGUIList(m_strName.GetBuffer(m_strName.GetLength()), eGUILIST_TEXT);
		PrintInfo("\nText added successfully");

	}

	CDialog::OnOK();
}


void CAddGUIText::OnEnChangeEditSize()
{
	m_editSize.GetWindowTextA(m_strTextSize);
	m_fTextSize = atof(m_strTextSize);
}


void CAddGUIText::OnEnChangeEditText()
{
	m_editText.GetWindowTextA(m_strText);
}

CVoid CAddGUIText::SetCreate(CBool create)
{
	m_create = create;
}

BOOL CAddGUIText::OnInitDialog()
{
	CDialog::OnInitDialog();

	if (m_create)
	{
		m_color = RGB(128, 128, 0);
		m_fColor[0] = 0.7f;
		m_fColor[1] = 0.7f;
		m_fColor[2] = 0.2f;
		m_fColor[3] = 1.0f;
		m_fPosX = g_width / 2;
		m_fPosY = g_height / 2;
		m_strPosX.Format("%.3f", m_fPosX); m_strPosY.Format("%.3f", m_fPosY);
		m_editPosX.SetWindowTextA(m_strPosX);
		m_editPosY.SetWindowTextA(m_strPosY);

		m_fTextSize = 18;
		m_strTextSize = "18";
		m_editSize.SetWindowTextA(m_strTextSize);

		m_brush.CreateSolidBrush(m_color);
	}
	else
	{
		m_editName.SetWindowTextA(m_strName);
		m_editPosX.SetWindowTextA(m_strPosX);
		m_editPosY.SetWindowTextA(m_strPosY);
		m_editSize.SetWindowTextA(m_strTextSize);
		m_editText.SetWindowTextA(m_strText);
		m_brush.CreateSolidBrush(m_color);
	}

	m_comboType.InsertString(0, "Arial");
	m_comboType.InsertString(1, "Times New Roman");
	if (m_create)
	{
		m_comboType.SetCurSel(0);
	}
	else
	{
		if (m_fontType == eFONT_ARIAL)
			m_comboType.SetCurSel(0);
		else if (m_fontType == eFONT_TIMES_NEW_ROMAN)
			m_comboType.SetCurSel(1);
	}
	m_comboType.UpdateWindow();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CAddGUIText::OnBnClickedButtonColor()
{
	CColorDialog dlg;
	if (dlg.DoModal() == IDOK)
	{
		m_color = dlg.GetColor();
		m_fColor[0] = (CFloat)GetRValue(m_color) / 255.f;
		m_fColor[1] = (CFloat)GetGValue(m_color) / 255.f;
		m_fColor[2] = (CFloat)GetBValue(m_color) / 255.f;
		m_fColor[3] = 1.0f; //I write it directly, no need to use alpha value for the ambient light
		m_brush.CreateSolidBrush(m_color);
		m_editColor.RedrawWindow();
	}
}


HBRUSH CAddGUIText::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	switch (pWnd->GetDlgCtrlID())
	{
	case IDC_EDIT_COLOR:
		pDC->SetBkColor(m_color);
		return m_brush;
	}
	return CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
}


void CAddGUIText::OnEnChangeEditName()
{
	m_editName.GetWindowTextA(m_strName);
}


void CAddGUIText::OnEnChangeEditPosX()
{
	m_editPosX.GetWindowTextA(m_strPosX);
	m_fPosX = atof(m_strPosX);
}


void CAddGUIText::OnEnChangeEditPosY()
{
	m_editPosY.GetWindowTextA(m_strPosY);
	m_fPosY = atof(m_strPosY);
}

