//Copyright (C) 2021 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

// AddGUIBackground.cpp : implementation file
//

#include "stdafx.h"
#include "VandaEngine1.h"
#include "AddGUIBackground.h"
#include "afxdialogex.h"
#include "GUIEngine/GUIBackground.h"

// CAddGUIBackground dialog

IMPLEMENT_DYNAMIC(CAddGUIBackground, CDialog)

CAddGUIBackground::CAddGUIBackground(CWnd* pParent /*=NULL*/)
	: CDialog(CAddGUIBackground::IDD, pParent)
{
	m_create = CTrue;
	m_updateImage = CFalse;
}

CAddGUIBackground::~CAddGUIBackground()
{
}

void CAddGUIBackground::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_MAIN_IMG, m_editImg);
	DDX_Control(pDX, IDC_EDIT_PERCENTAGE, m_editPercentage);
	DDX_Control(pDX, IDC_EDIT_NAME, m_editName);
	DDX_Control(pDX, IDC_EDIT_POS_X, m_editPosX);
	DDX_Control(pDX, IDC_EDIT_POS_Y, m_editPosY);
}


BEGIN_MESSAGE_MAP(CAddGUIBackground, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_ADD_MAIN_IMG, &CAddGUIBackground::OnBnClickedButtonAddMainImg)
	ON_EN_CHANGE(IDC_EDIT_PERCENTAGE, &CAddGUIBackground::OnEnChangeEditPercentage)
	ON_BN_CLICKED(IDOK, &CAddGUIBackground::OnBnClickedOk)
	ON_EN_CHANGE(IDC_EDIT_MAIN_IMG, &CAddGUIBackground::OnEnChangeEditMainImg)
	ON_EN_CHANGE(IDC_EDIT_POS_X, &CAddGUIBackground::OnEnChangeEditPosX)
	ON_EN_CHANGE(IDC_EDIT_POS_Y, &CAddGUIBackground::OnEnChangeEditPosY)
	ON_EN_CHANGE(IDC_EDIT_NAME, &CAddGUIBackground::OnEnChangeEditName)
END_MESSAGE_MAP()


// CAddGUIBackground message handlers


void CAddGUIBackground::OnBnClickedButtonAddMainImg()
{
	CFileDialog dlgOpen(TRUE, _T("*.dds"), _T(""), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR,
		_T("DDS File (*.dds)|*.dds||"), NULL, NULL);
	if (IDOK == dlgOpen.DoModal())
	{
		CBool foundTarget = CFalse;
		CString imagePath = (CString)dlgOpen.GetPathName();
		CString imageName = dlgOpen.GetFileTitle();

		CChar new_image_name[MAX_NAME_SIZE];
		Cpy(new_image_name, imageName.GetBuffer(imageName.GetLength()));

		for (CUInt i = 0; i < g_guiBackgrounds.size(); i++)
		{
			if (!Cmp(GetName(), g_guiBackgrounds[i]->GetName()))
			{
				CChar name[MAX_NAME_SIZE];
				Cpy(name, GetAfterPath(g_guiBackgrounds[i]->GetImagePath()));
				GetWithoutDot(name);
				if (Cmp(name, new_image_name))
					foundTarget = CTrue;
			}
		}
		for (CUInt i = 0; i < g_guiButtons.size(); i++)
		{
			{
				CChar name[MAX_NAME_SIZE];
				Cpy(name, GetAfterPath(g_guiButtons[i]->GetMainImagePath()));
				GetWithoutDot(name);
				if (Cmp(name, new_image_name))
				{
					foundTarget = CTrue;
					break;
				}
			}
			if (g_guiButtons[i]->GetHasRightClickImage())
			{

				CChar name[MAX_NAME_SIZE];
				Cpy(name, GetAfterPath(g_guiButtons[i]->GetRightClickImagePath()));
				GetWithoutDot(name);
				if (Cmp(name, new_image_name))
				{
					foundTarget = CTrue;
					break;
				}
			}
			if (g_guiButtons[i]->GetHasLeftClickImage())
			{
				CChar name[MAX_NAME_SIZE];
				Cpy(name, GetAfterPath(g_guiButtons[i]->GetLeftClickImagePath()));
				GetWithoutDot(name);
				if (Cmp(name, new_image_name))
				{
					foundTarget = CTrue;
					break;
				}
			}
			if (g_guiButtons[i]->GetHasDisableImage())
			{
				CChar name[MAX_NAME_SIZE];
				Cpy(name, GetAfterPath(g_guiButtons[i]->GetDisableImagePath()));
				GetWithoutDot(name);
				if (Cmp(name, new_image_name))
				{
					foundTarget = CTrue;
					break;
				}
			}
			if (g_guiButtons[i]->GetHasHoverImage())
			{
				CChar name[MAX_NAME_SIZE];
				Cpy(name, GetAfterPath(g_guiButtons[i]->GetHoverImagePath()));
				GetWithoutDot(name);
				if (Cmp(name, new_image_name))
				{
					foundTarget = CTrue;
					break;
				}
			}

		}

		CBool proceed = CTrue;
		if (foundTarget)
			if (MessageBox("Another image path uses the same name. If you save your GUI, These images will overwrite each other\nProceed?", "Warning", MB_YESNO | MB_ICONINFORMATION) == IDYES)
				proceed = CTrue;
			else
				proceed = CFalse;

		if (proceed)
		{
			m_strImagePath = (CString)dlgOpen.GetPathName();
			m_strImageName = dlgOpen.GetFileTitle();

			m_editImg.SetWindowText(m_strImagePath);
			m_updateImage = CTrue;
		}
	}
}

void CAddGUIBackground::OnEnChangeEditPercentage()
{
	m_editPercentage.GetWindowTextA(m_strPercentage);
	m_fPercentage = atof(m_strPercentage);
}


BOOL CAddGUIBackground::OnInitDialog()
{
	CDialog::OnInitDialog();

	if (m_create)
	{
		m_fPosX = g_width / 2;
		m_fPosY = g_height / 2;
		m_strPosX.Format("%.3f", m_fPosX); m_strPosY.Format("%.3f", m_fPosY);

		m_editPosX.SetWindowTextA(m_strPosX);
		m_editPosY.SetWindowTextA(m_strPosY);

		m_fPercentage = 10.0f;
		m_strPercentage = "10.0";
		m_editPercentage.SetWindowTextA(m_strPercentage);
	}
	else
	{
		m_editName.SetWindowTextA(m_strName);
		m_editPosX.SetWindowTextA(m_strPosX);
		m_editPosY.SetWindowTextA(m_strPosY);
		m_editPercentage.SetWindowTextA(m_strPercentage);
		m_editImg.SetWindowTextA(m_strImagePath);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

CVoid CAddGUIBackground::SetCreate(CBool create)
{
	m_create = create;
}

CVoid CAddGUIBackground::SetName(CChar* name)
{
	m_strName = name;
	m_strTempName = name;
}

CVoid CAddGUIBackground::SetPosition(CVec2f pos)
{
	m_fPosX = pos.x;
	m_fPosY = pos.y;

	m_strPosX.Format("%.3f", m_fPosX);
	m_strPosY.Format("%.3f", m_fPosY);
}

CVoid CAddGUIBackground::SetImagePath(CChar* path)
{
	m_strImagePath = path;
}

CVoid CAddGUIBackground::SetUpdateImage(CBool state)
{
	m_updateImage = state;
}

CVoid CAddGUIBackground::SetSize(CFloat size)
{
	m_fPercentage = size;
	m_strPercentage.Format("%.3f", m_fPercentage);
}

CChar* CAddGUIBackground::GetName()
{
	return m_strName.GetBuffer(m_strName.GetLength());
}

CVec2f CAddGUIBackground::GetPosition()
{
	CVec2f pos(m_fPosX, m_fPosY);
	return pos;
}

CChar* CAddGUIBackground::GetImagePath()
{
	return m_strImagePath.GetBuffer(m_strImagePath.GetLength());
}

CFloat CAddGUIBackground::GetSize()
{
	return m_fPercentage;
}

CBool CAddGUIBackground::GetUpdateImage()
{
	return m_updateImage;
}

void CAddGUIBackground::OnBnClickedOk()
{
	if (m_strImagePath.IsEmpty() || m_strPercentage.IsEmpty() || m_strPosX.IsEmpty() || m_strPosY.IsEmpty() || m_strName.IsEmpty())
	{
		MessageBox("Please Fill In All Of The Required Fields", "Vanda Engine Error", MB_OK | MB_ICONERROR);
		return;
	}
	for (std::vector<std::string>::iterator it = g_guiNames.begin(); it != g_guiNames.end(); it++)
	{
		if (!m_create)
		{
			if (Cmp((LPCTSTR)m_strTempName, (*it).c_str()))
				break;
		}
		if (Cmp((LPCTSTR)m_strName, (*it).c_str()))
		{
			MessageBox("This name already exists. Please select another name!", "Vanda Engine Error", MB_OK | MB_ICONERROR);
			return;
		}
	}
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
		CGUIBackground* guiBackground = CNew(CGUIBackground);
		guiBackground->SetName(m_strName.GetBuffer(m_strName.GetLength()));
		CVec2f pos(m_fPosX, m_fPosY);
		guiBackground->SetSize(m_fPercentage);
		guiBackground->SetImagePath(m_strImagePath.GetBuffer(m_strImagePath.GetLength()));
		guiBackground->LoadBackgroundImage();
		guiBackground->SetUpdateImage(CTrue);
		guiBackground->SetPosition(pos);

		if (!Cmp(g_currentPackageAndGUIName, "\n"))
		{
			guiBackground->SetPackageName(g_currentGUIPackageName);
			guiBackground->SetGUIName(g_currentGUIName);
		}

		g_guiBackgrounds.push_back(guiBackground);
		g_guiNames.push_back(m_strName.GetBuffer(m_strName.GetLength()));

		ex_pVandaEngine1Dlg->InsertItemToGUIList(m_strName.GetBuffer(m_strName.GetLength()), eGUILIST_BACKGROUND);
		PrintInfo("\nBackground added successfully");
	}
	CDialog::OnOK();
}


void CAddGUIBackground::OnEnChangeEditMainImg()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}


void CAddGUIBackground::OnEnChangeEditPosX()
{
	m_editPosX.GetWindowTextA(m_strPosX);
	m_fPosX = atof(m_strPosX);
}


void CAddGUIBackground::OnEnChangeEditPosY()
{
	m_editPosY.GetWindowTextA(m_strPosY);
	m_fPosY = atof(m_strPosY);
}


void CAddGUIBackground::OnEnChangeEditName()
{
	m_editName.GetWindowTextA(m_strName);
}
