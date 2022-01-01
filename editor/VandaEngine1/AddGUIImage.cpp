//Copyright (C) 2022 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

// AddGUIImage.cpp : implementation file
//

#include "stdafx.h"
#include "VandaEngine1.h"
#include "AddGUIImage.h"
#include "afxdialogex.h"
#include "GUIEngine/GUIImage.h"

// CAddGUIImage dialog

IMPLEMENT_DYNAMIC(CAddGUIImage, CDialog)

CAddGUIImage::CAddGUIImage(CWnd* pParent /*=NULL*/)
	: CDialog(CAddGUIImage::IDD, pParent)
{
	m_create = CTrue;
	m_updateImage = CFalse;
}

CAddGUIImage::~CAddGUIImage()
{
}

void CAddGUIImage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_MAIN_IMG, m_editImg);
	DDX_Control(pDX, IDC_EDIT_PERCENTAGE, m_editPercentage);
	DDX_Control(pDX, IDC_EDIT_NAME, m_editName);
	DDX_Control(pDX, IDC_EDIT_POS_X, m_editPosX);
	DDX_Control(pDX, IDC_EDIT_POS_Y, m_editPosY);
}


BEGIN_MESSAGE_MAP(CAddGUIImage, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_ADD_MAIN_IMG, &CAddGUIImage::OnBnClickedButtonAddMainImg)
	ON_EN_CHANGE(IDC_EDIT_PERCENTAGE, &CAddGUIImage::OnEnChangeEditPercentage)
	ON_BN_CLICKED(IDOK, &CAddGUIImage::OnBnClickedOk)
	ON_EN_CHANGE(IDC_EDIT_MAIN_IMG, &CAddGUIImage::OnEnChangeEditMainImg)
	ON_EN_CHANGE(IDC_EDIT_POS_X, &CAddGUIImage::OnEnChangeEditPosX)
	ON_EN_CHANGE(IDC_EDIT_POS_Y, &CAddGUIImage::OnEnChangeEditPosY)
	ON_EN_CHANGE(IDC_EDIT_NAME, &CAddGUIImage::OnEnChangeEditName)
END_MESSAGE_MAP()


// CAddGUIImage message handlers


void CAddGUIImage::OnBnClickedButtonAddMainImg()
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

		for (CUInt i = 0; i < g_guiImages.size(); i++)
		{
			if (!Cmp(GetName(), g_guiImages[i]->GetName()))
			{
				CChar name[MAX_NAME_SIZE];
				Cpy(name, GetAfterPath(g_guiImages[i]->GetImagePath()));
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

void CAddGUIImage::OnEnChangeEditPercentage()
{
	m_editPercentage.GetWindowTextA(m_strPercentage);
	m_fPercentage = atof(m_strPercentage);
}


BOOL CAddGUIImage::OnInitDialog()
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

CVoid CAddGUIImage::SetCreate(CBool create)
{
	m_create = create;
}

CVoid CAddGUIImage::SetName(CChar* name)
{
	m_strName = name;
	m_strTempName = name;
}

CVoid CAddGUIImage::SetPosition(CVec2f pos)
{
	m_fPosX = pos.x;
	m_fPosY = pos.y;

	m_strPosX.Format("%.3f", m_fPosX);
	m_strPosY.Format("%.3f", m_fPosY);
}

CVoid CAddGUIImage::SetImagePath(CChar* path)
{
	m_strImagePath = path;
}

CVoid CAddGUIImage::SetUpdateImage(CBool state)
{
	m_updateImage = state;
}

CVoid CAddGUIImage::SetSize(CFloat size)
{
	m_fPercentage = size;
	m_strPercentage.Format("%.3f", m_fPercentage);
}

CVoid CAddGUIImage::SetVisible(CBool state)
{
	m_visible = state;
}

CChar* CAddGUIImage::GetName()
{
	return m_strName.GetBuffer(m_strName.GetLength());
}

CVec2f CAddGUIImage::GetPosition()
{
	CVec2f pos(m_fPosX, m_fPosY);
	return pos;
}

CChar* CAddGUIImage::GetImagePath()
{
	return m_strImagePath.GetBuffer(m_strImagePath.GetLength());
}

CFloat CAddGUIImage::GetSize()
{
	return m_fPercentage;
}

CBool CAddGUIImage::IsVisible()
{
	return m_visible;
}

CBool CAddGUIImage::GetUpdateImage()
{
	return m_updateImage;
}

void CAddGUIImage::OnBnClickedOk()
{
	if (m_strImagePath.IsEmpty() || m_strPercentage.IsEmpty() || m_strPosX.IsEmpty() || m_strPosY.IsEmpty() || m_strName.IsEmpty())
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
		CGUIImage* guiImage = CNew(CGUIImage);
		guiImage->SetName(m_strName.GetBuffer(m_strName.GetLength()));
		CVec2f pos(m_fPosX, m_fPosY);
		guiImage->SetSize(m_fPercentage);
		guiImage->SetImagePath(m_strImagePath.GetBuffer(m_strImagePath.GetLength()));
		guiImage->LoadGUIImage();
		guiImage->SetUpdateImage(CTrue);
		guiImage->SetPosition(pos);

		if (!Cmp(g_currentPackageAndGUIName, "\n"))
		{
			guiImage->SetPackageName(g_currentGUIPackageName);
			guiImage->SetGUIName(g_currentGUIName);
		}

		g_guiImages.push_back(guiImage);
		g_guiNames.push_back(m_strName.GetBuffer(m_strName.GetLength()));

		ex_pVandaEngine1Dlg->InsertItemToGUIList(m_strName.GetBuffer(m_strName.GetLength()), eGUILIST_IMAGE);
		PrintInfo("\nImage added successfully");
	}
	CDialog::OnOK();
}


void CAddGUIImage::OnEnChangeEditMainImg()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}


void CAddGUIImage::OnEnChangeEditPosX()
{
	m_editPosX.GetWindowTextA(m_strPosX);
	m_fPosX = atof(m_strPosX);
}


void CAddGUIImage::OnEnChangeEditPosY()
{
	m_editPosY.GetWindowTextA(m_strPosY);
	m_fPosY = atof(m_strPosY);
}


void CAddGUIImage::OnEnChangeEditName()
{
	m_editName.GetWindowTextA(m_strName);
}
