//Copyright (C) 2020 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

// AddGUI.cpp : implementation file
//

#include "stdafx.h"
#include "VandaEngine1.h"
#include "AddGUIButton.h"
#include "afxdialogex.h"


// CAddGUIButton dialog

IMPLEMENT_DYNAMIC(CAddGUIButton, CDialog)

CAddGUIButton::CAddGUIButton(CWnd* pParent /*=NULL*/)
	: CDialog(CAddGUIButton::IDD, pParent)
{
	m_create = CTrue;
	m_updateMainImage = CFalse;
	m_updateLeftClickImage = CFalse;
	m_updateHoverImage = CFalse;
	m_updateRightClickImage = CFalse;
	m_updateDisableImage = CFalse;
	m_updateLeftClickScript = CFalse;
	m_updateHoverScript = CFalse;
	m_updateRightClickScript = CFalse;

}

CAddGUIButton::~CAddGUIButton()
{
}

void CAddGUIButton::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_MAIN_IMG, m_editMainImg);
	DDX_Control(pDX, IDC_EDIT_LEFT_CLK_IMG, m_editLeftClickImg);
	DDX_Control(pDX, IDC_EDIT_HOVER_IMG, m_editHoverImg);
	DDX_Control(pDX, IDC_EDIT_RIGHT_CLK_IMG, m_editRightClickImg);
	DDX_Control(pDX, IDC_EDIT_DISABLE_IMG, m_editDisableImg);
	DDX_Control(pDX, IDC_EDIT_LEFT_CLK_SCRIPT, m_editLeftClickScript);
	DDX_Control(pDX, IDC_EDIT_HOVER_SCRIPT, m_editHoverScript);
	DDX_Control(pDX, IDC_EDIT_RIGHT_CLK_SCRIPT, m_editRightClickScript);
	DDX_Control(pDX, IDC_EDIT_SIZE, m_editSize);
	DDX_Control(pDX, IDC_EDIT_NAME, m_editName);
	DDX_Control(pDX, IDC_EDIT_POS_X, m_editPosX);
	DDX_Control(pDX, IDC_EDIT_POS_Y, m_editPosY);
}


BEGIN_MESSAGE_MAP(CAddGUIButton, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_ADD_MAIN_IMG, &CAddGUIButton::OnBnClickedButtonAddMainImg)
	ON_BN_CLICKED(IDC_BUTTON_ADD_LEFT_CLK_IMG, &CAddGUIButton::OnBnClickedButtonAddLeftClkImg)
	ON_BN_CLICKED(IDC_BUTTON_REMOVE_LEFT_CLK_IMG, &CAddGUIButton::OnBnClickedButtonRemoveLeftClkImg)
	ON_BN_CLICKED(IDC_BUTTON_ADD_HOVER_IMG, &CAddGUIButton::OnBnClickedButtonAddHoverImg)
	ON_BN_CLICKED(IDC_BUTTON_REMOVE_HOVER_IMG, &CAddGUIButton::OnBnClickedButtonRemoveHoverImg)
	ON_BN_CLICKED(IDC_BUTTON_ADD_RIGHT_CLK_IMG, &CAddGUIButton::OnBnClickedButtonAddRightClkImg)
	ON_BN_CLICKED(IDC_BUTTON_REMOVE_RIGHT_CLK_IMG, &CAddGUIButton::OnBnClickedButtonRemoveRightClkImg)
	ON_BN_CLICKED(IDC_BUTTON_ADD_DISABLE_IMG, &CAddGUIButton::OnBnClickedButtonAddDisableImg)
	ON_BN_CLICKED(IDC_BUTTON_REMOVE_DISABLE_IMG, &CAddGUIButton::OnBnClickedButtonRemoveDisableImg)
	ON_BN_CLICKED(IDC_BUTTON_ADD_LEFT_CLK_SCRIPT, &CAddGUIButton::OnBnClickedButtonAddLeftClkScript)
	ON_BN_CLICKED(IDC_BUTTON_REMOVE_LEFT_CLK_SCRIPT, &CAddGUIButton::OnBnClickedButtonRemoveLeftClkScript)
	ON_BN_CLICKED(IDC_BUTTON_ADD_HOVER_SCRIPT, &CAddGUIButton::OnBnClickedButtonAddHoverScript)
	ON_BN_CLICKED(IDC_BUTTON_REMOVE_HOVER_SCRIPT, &CAddGUIButton::OnBnClickedButtonRemoveHoverScript)
	ON_BN_CLICKED(IDC_BUTTON_ADD_RIGHT_CLK_SCRIPT, &CAddGUIButton::OnBnClickedButtonAddRightClkScript)
	ON_BN_CLICKED(IDC_BUTTON_REMOVE_RIGHT_CLK_SCRIPT, &CAddGUIButton::OnBnClickedButtonRemoveRightClkScript)
	ON_BN_CLICKED(IDOK, &CAddGUIButton::OnBnClickedOk)
	ON_EN_CHANGE(IDC_EDIT_SIZE, &CAddGUIButton::OnEnChangeEditSize)
	ON_EN_CHANGE(IDC_EDIT_NAME, &CAddGUIButton::OnEnChangeEditName)
	ON_EN_CHANGE(IDC_EDIT_POS_X, &CAddGUIButton::OnEnChangeEditPosX)
	ON_EN_CHANGE(IDC_EDIT_POS_Y, &CAddGUIButton::OnEnChangeEditPosY)
END_MESSAGE_MAP()


// CAddGUIButton message handlers


void CAddGUIButton::OnBnClickedButtonAddMainImg()
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

		if (!m_strDisableImgPath.IsEmpty())
		{
			CChar str[MAX_NAME_SIZE];
			Cpy(str, m_strDisableImgPath.GetBuffer(m_strDisableImgPath.GetLength()));
			CChar* AfterPath = GetAfterPath(str);
			GetWithoutDot(AfterPath);

			if (Cmp(AfterPath, new_image_name))
				foundTarget = CTrue;
		}
		if (!foundTarget && !m_strHoverImgPath.IsEmpty())
		{
			CChar str[MAX_NAME_SIZE];
			Cpy(str, m_strHoverImgPath.GetBuffer(m_strHoverImgPath.GetLength()));
			CChar* AfterPath = GetAfterPath(str);
			GetWithoutDot(AfterPath);

			if (Cmp(AfterPath, new_image_name))
				foundTarget = CTrue;

		}
		if (!foundTarget && !m_strLeftClickImgPath.IsEmpty())
		{
			CChar str[MAX_NAME_SIZE];
			Cpy(str, m_strLeftClickImgPath.GetBuffer(m_strLeftClickImgPath.GetLength()));
			CChar* AfterPath = GetAfterPath(str);
			GetWithoutDot(AfterPath);

			if (Cmp(AfterPath, new_image_name))
				foundTarget = CTrue;

		}
		if (!foundTarget && !m_strRightClickImgPath.IsEmpty())
		{
			CChar str[MAX_NAME_SIZE];
			Cpy(str, m_strRightClickImgPath.GetBuffer(m_strRightClickImgPath.GetLength()));
			CChar* AfterPath = GetAfterPath(str);
			GetWithoutDot(AfterPath);

			if (Cmp(AfterPath, new_image_name))
				foundTarget = CTrue;
		}
		if (!foundTarget)
		{
			for (CUInt i = 0; i < g_guiBackgrounds.size(); i++)
			{
				CChar name[MAX_NAME_SIZE];
				Cpy(name, GetAfterPath(g_guiBackgrounds[i]->GetImagePath()));
				GetWithoutDot(name);
				if (Cmp(name, new_image_name))
					foundTarget = CTrue;
			}
			for (CUInt i = 0; i < g_guiButtons.size(); i++)
			{
				if (!Cmp(GetName(), g_guiButtons[i]->GetName()))
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
			m_strMainImgPath = (CString)dlgOpen.GetPathName();
			m_strMainPureImgPath = dlgOpen.GetFileTitle();

			m_editMainImg.SetWindowText(m_strMainImgPath);

			m_updateMainImage = CTrue;
		}
	}
}


void CAddGUIButton::OnBnClickedButtonAddLeftClkImg()
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

		if (!m_strDisableImgPath.IsEmpty())
		{
			CChar str[MAX_NAME_SIZE];
			Cpy(str, m_strDisableImgPath.GetBuffer(m_strDisableImgPath.GetLength()));
			CChar* AfterPath = GetAfterPath(str);
			GetWithoutDot(AfterPath);

			if (Cmp(AfterPath, new_image_name))
				foundTarget = CTrue;
		}
		if (!foundTarget && !m_strHoverImgPath.IsEmpty())
		{
			CChar str[MAX_NAME_SIZE];
			Cpy(str, m_strHoverImgPath.GetBuffer(m_strHoverImgPath.GetLength()));
			CChar* AfterPath = GetAfterPath(str);
			GetWithoutDot(AfterPath);

			if (Cmp(AfterPath, new_image_name))
				foundTarget = CTrue;

		}
		if (!foundTarget && !m_strMainImgPath.IsEmpty())
		{
			CChar str[MAX_NAME_SIZE];
			Cpy(str, m_strMainImgPath.GetBuffer(m_strMainImgPath.GetLength()));
			CChar* AfterPath = GetAfterPath(str);
			GetWithoutDot(AfterPath);

			if (Cmp(AfterPath, new_image_name))
				foundTarget = CTrue;

		}
		if (!foundTarget && !m_strRightClickImgPath.IsEmpty())
		{
			CChar str[MAX_NAME_SIZE];
			Cpy(str, m_strRightClickImgPath.GetBuffer(m_strRightClickImgPath.GetLength()));
			CChar* AfterPath = GetAfterPath(str);
			GetWithoutDot(AfterPath);

			if (Cmp(AfterPath, new_image_name))
				foundTarget = CTrue;
		}

		if (!foundTarget)
		{
			for (CUInt i = 0; i < g_guiBackgrounds.size(); i++)
			{
				CChar name[MAX_NAME_SIZE];
				Cpy(name, GetAfterPath(g_guiBackgrounds[i]->GetImagePath()));
				GetWithoutDot(name);
				if (Cmp(name, new_image_name))
					foundTarget = CTrue;
			}
			for (CUInt i = 0; i < g_guiButtons.size(); i++)
			{
				if (!Cmp(GetName(), g_guiButtons[i]->GetName()))
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
			}
		}

		CBool proceed = CTrue;
		if (foundTarget)
			if (MessageBox("Another image of this button uses the same image name. If you save your GUI, These images will overwrite each other\nProceed?", "Warning", MB_YESNO | MB_ICONINFORMATION) == IDYES)
				proceed = CTrue;
			else
				proceed = CFalse;

		if (proceed)
		{

			m_strLeftClickImgPath = (CString)dlgOpen.GetPathName();
			m_strLeftClickPureImgPath = dlgOpen.GetFileTitle();

			m_editLeftClickImg.SetWindowText(m_strLeftClickImgPath);

			m_updateLeftClickImage = CTrue;
		}
	}
}


void CAddGUIButton::OnBnClickedButtonRemoveLeftClkImg()
{
	if (!m_strLeftClickImgPath.IsEmpty())
		if (MessageBox("Delete current left click image?", "Warning", MB_YESNO | MB_ICONINFORMATION) == IDNO)
			return;
	m_editLeftClickImg.SetWindowTextA("\n");
	m_strLeftClickImgPath.Empty();
	m_strLeftClickPureImgPath.Empty();
}


void CAddGUIButton::OnBnClickedButtonAddHoverImg()
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

		if (!m_strDisableImgPath.IsEmpty())
		{
			CChar str[MAX_NAME_SIZE];
			Cpy(str, m_strDisableImgPath.GetBuffer(m_strDisableImgPath.GetLength()));
			CChar* AfterPath = GetAfterPath(str);
			GetWithoutDot(AfterPath);

			if (Cmp(AfterPath, new_image_name))
				foundTarget = CTrue;
		}
		if (!foundTarget && !m_strMainImgPath.IsEmpty())
		{
			CChar str[MAX_NAME_SIZE];
			Cpy(str, m_strMainImgPath.GetBuffer(m_strMainImgPath.GetLength()));
			CChar* AfterPath = GetAfterPath(str);
			GetWithoutDot(AfterPath);

			if (Cmp(AfterPath, new_image_name))
				foundTarget = CTrue;

		}
		if (!foundTarget && !m_strLeftClickImgPath.IsEmpty())
		{
			CChar str[MAX_NAME_SIZE];
			Cpy(str, m_strLeftClickImgPath.GetBuffer(m_strLeftClickImgPath.GetLength()));
			CChar* AfterPath = GetAfterPath(str);
			GetWithoutDot(AfterPath);

			if (Cmp(AfterPath, new_image_name))
				foundTarget = CTrue;

		}
		if (!foundTarget && !m_strRightClickImgPath.IsEmpty())
		{
			CChar str[MAX_NAME_SIZE];
			Cpy(str, m_strRightClickImgPath.GetBuffer(m_strRightClickImgPath.GetLength()));
			CChar* AfterPath = GetAfterPath(str);
			GetWithoutDot(AfterPath);

			if (Cmp(AfterPath, new_image_name))
				foundTarget = CTrue;
		}

		if (!foundTarget)
		{
			for (CUInt i = 0; i < g_guiBackgrounds.size(); i++)
			{
				CChar name[MAX_NAME_SIZE];
				Cpy(name, GetAfterPath(g_guiBackgrounds[i]->GetImagePath()));
				GetWithoutDot(name);
				if (Cmp(name, new_image_name))
					foundTarget = CTrue;
			}
			for (CUInt i = 0; i < g_guiButtons.size(); i++)
			{
				if (!Cmp(GetName(), g_guiButtons[i]->GetName()))
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
			}
		}

		CBool proceed = CTrue;
		if (foundTarget)
			if (MessageBox("Another image of this button uses the same image name. If you save your GUI, These images will overwrite each other\nProceed?", "Warning", MB_YESNO | MB_ICONINFORMATION) == IDYES)
				proceed = CTrue;
			else
				proceed = CFalse;

		if (proceed)
		{
			m_strHoverImgPath = (CString)dlgOpen.GetPathName();
			m_strHoverPureImgPath = dlgOpen.GetFileTitle();

			m_editHoverImg.SetWindowText(m_strHoverImgPath);

			m_updateHoverImage = CTrue;
		}
	}
}


void CAddGUIButton::OnBnClickedButtonRemoveHoverImg()
{
	if (!m_strHoverImgPath.IsEmpty())
		if (MessageBox("Delete current hover image?", "Warning", MB_YESNO | MB_ICONINFORMATION) == IDNO)
			return;

	m_editHoverImg.SetWindowTextA("\n");
	m_strHoverImgPath.Empty();
	m_strHoverPureImgPath.Empty();
}


void CAddGUIButton::OnBnClickedButtonAddRightClkImg()
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

		if (!m_strDisableImgPath.IsEmpty())
		{
			CChar str[MAX_NAME_SIZE];
			Cpy(str, m_strDisableImgPath.GetBuffer(m_strDisableImgPath.GetLength()));
			CChar* AfterPath = GetAfterPath(str);
			GetWithoutDot(AfterPath);

			if (Cmp(AfterPath, new_image_name))
				foundTarget = CTrue;
		}
		if (!foundTarget && !m_strHoverImgPath.IsEmpty())
		{
			CChar str[MAX_NAME_SIZE];
			Cpy(str, m_strHoverImgPath.GetBuffer(m_strHoverImgPath.GetLength()));
			CChar* AfterPath = GetAfterPath(str);
			GetWithoutDot(AfterPath);

			if (Cmp(AfterPath, new_image_name))
				foundTarget = CTrue;

		}
		if (!foundTarget && !m_strLeftClickImgPath.IsEmpty())
		{
			CChar str[MAX_NAME_SIZE];
			Cpy(str, m_strLeftClickImgPath.GetBuffer(m_strLeftClickImgPath.GetLength()));
			CChar* AfterPath = GetAfterPath(str);
			GetWithoutDot(AfterPath);

			if (Cmp(AfterPath, new_image_name))
				foundTarget = CTrue;

		}
		if (!foundTarget && !m_strMainImgPath.IsEmpty())
		{
			CChar str[MAX_NAME_SIZE];
			Cpy(str, m_strMainImgPath.GetBuffer(m_strMainImgPath.GetLength()));
			CChar* AfterPath = GetAfterPath(str);
			GetWithoutDot(AfterPath);

			if (Cmp(AfterPath, new_image_name))
				foundTarget = CTrue;
		}

		if (!foundTarget)
		{
			for (CUInt i = 0; i < g_guiBackgrounds.size(); i++)
			{
				CChar name[MAX_NAME_SIZE];
				Cpy(name, GetAfterPath(g_guiBackgrounds[i]->GetImagePath()));
				GetWithoutDot(name);
				if (Cmp(name, new_image_name))
					foundTarget = CTrue;
			}
			for (CUInt i = 0; i < g_guiButtons.size(); i++)
			{
				if (!Cmp(GetName(), g_guiButtons[i]->GetName()))
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
			}
		}

		CBool proceed = CTrue;
		if (foundTarget)
			if (MessageBox("Another image of this button uses the same image name. If you save your GUI, These images will overwrite each other\nProceed?", "Warning", MB_YESNO | MB_ICONINFORMATION) == IDYES)
				proceed = CTrue;
			else
				proceed = CFalse;

		if (proceed)
		{
			m_strRightClickImgPath = (CString)dlgOpen.GetPathName();
			m_strRightClickPureImgPath = dlgOpen.GetFileTitle();

			m_editRightClickImg.SetWindowText(m_strRightClickImgPath);

			m_updateRightClickImage = CTrue;
		}

	}
}


void CAddGUIButton::OnBnClickedButtonRemoveRightClkImg()
{
	if (!m_strRightClickImgPath.IsEmpty())
		if (MessageBox("Delete current right click image?", "Warning", MB_YESNO | MB_ICONINFORMATION) == IDNO)
			return;

	m_editRightClickImg.SetWindowTextA("\n");
	m_strRightClickImgPath.Empty();
	m_strRightClickPureImgPath.Empty();
}


void CAddGUIButton::OnBnClickedButtonAddDisableImg()
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

		if (!m_strMainImgPath.IsEmpty())
		{
			CChar str[MAX_NAME_SIZE];
			Cpy(str, m_strMainImgPath.GetBuffer(m_strMainImgPath.GetLength()));
			CChar* AfterPath = GetAfterPath(str);
			GetWithoutDot(AfterPath);

			if (Cmp(AfterPath, new_image_name))
				foundTarget = CTrue;
		}
		if (!foundTarget && !m_strHoverImgPath.IsEmpty())
		{
			CChar str[MAX_NAME_SIZE];
			Cpy(str, m_strHoverImgPath.GetBuffer(m_strHoverImgPath.GetLength()));
			CChar* AfterPath = GetAfterPath(str);
			GetWithoutDot(AfterPath);

			if (Cmp(AfterPath, new_image_name))
				foundTarget = CTrue;

		}
		if (!foundTarget && !m_strLeftClickImgPath.IsEmpty())
		{
			CChar str[MAX_NAME_SIZE];
			Cpy(str, m_strLeftClickImgPath.GetBuffer(m_strLeftClickImgPath.GetLength()));
			CChar* AfterPath = GetAfterPath(str);
			GetWithoutDot(AfterPath);

			if (Cmp(AfterPath, new_image_name))
				foundTarget = CTrue;

		}
		if (!foundTarget && !m_strRightClickImgPath.IsEmpty())
		{
			CChar str[MAX_NAME_SIZE];
			Cpy(str, m_strRightClickImgPath.GetBuffer(m_strRightClickImgPath.GetLength()));
			CChar* AfterPath = GetAfterPath(str);
			GetWithoutDot(AfterPath);

			if (Cmp(AfterPath, new_image_name))
				foundTarget = CTrue;
		}

		if (!foundTarget)
		{
			for (CUInt i = 0; i < g_guiBackgrounds.size(); i++)
			{
				CChar name[MAX_NAME_SIZE];
				Cpy(name, GetAfterPath(g_guiBackgrounds[i]->GetImagePath()));
				GetWithoutDot(name);
				if (Cmp(name, new_image_name))
					foundTarget = CTrue;
			}
			for (CUInt i = 0; i < g_guiButtons.size(); i++)
			{
				if (!Cmp(GetName(), g_guiButtons[i]->GetName()))
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
			}
		}

		CBool proceed = CTrue;
		if (foundTarget)
			if (MessageBox("Another image of this button uses the same image name. If you save your GUI, These images will overwrite each other\nProceed?", "Warning", MB_YESNO | MB_ICONINFORMATION) == IDYES)
				proceed = CTrue;
			else
				proceed = CFalse;

		if (proceed)
		{
			m_strDisableImgPath = (CString)dlgOpen.GetPathName();
			m_strDisablePureImgPath = dlgOpen.GetFileTitle();

			m_editDisableImg.SetWindowText(m_strDisableImgPath);

			m_updateDisableImage = CTrue;
		}

	}
}


void CAddGUIButton::OnBnClickedButtonRemoveDisableImg()
{
	if (!m_strDisableImgPath.IsEmpty())
		if (MessageBox("Delete current disable image?", "Warning", MB_YESNO | MB_ICONINFORMATION) == IDNO)
			return;

	m_editDisableImg.SetWindowTextA("\n");
	m_strDisableImgPath.Empty();
	m_strDisablePureImgPath.Empty();
}


void CAddGUIButton::OnBnClickedButtonAddLeftClkScript()
{
	CFileDialog dlgOpen(TRUE, _T("*.lua"), _T(""), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR,
		_T("LUA File (*.lua)|*.lua||"), NULL, NULL);
	if (IDOK == dlgOpen.DoModal())
	{
		m_strLeftClickScriptPath = (CString)dlgOpen.GetPathName();
		m_strLeftClickPureScriptPath = dlgOpen.GetFileTitle();

		m_editLeftClickScript.SetWindowText(m_strLeftClickScriptPath);

		m_updateLeftClickScript = CTrue;
	}
}


void CAddGUIButton::OnBnClickedButtonRemoveLeftClkScript()
{
	if (!m_strLeftClickScriptPath.IsEmpty())
		if (MessageBox("Delete current left click script?", "Warning", MB_YESNO | MB_ICONINFORMATION) == IDNO)
			return;

	m_editLeftClickScript.SetWindowTextA("\n");
	m_strLeftClickScriptPath.Empty();
	m_strLeftClickPureScriptPath.Empty();
}


void CAddGUIButton::OnBnClickedButtonAddHoverScript()
{
	CFileDialog dlgOpen(TRUE, _T("*.lua"), _T(""), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR,
		_T("LUA File (*.lua)|*.lua||"), NULL, NULL);
	if (IDOK == dlgOpen.DoModal())
	{
		m_strHoverScriptPath = (CString)dlgOpen.GetPathName();
		m_strHoverPureScriptPath = dlgOpen.GetFileTitle();

		m_editHoverScript.SetWindowText(m_strHoverScriptPath);

		m_updateHoverScript = CTrue;
	}
}


void CAddGUIButton::OnBnClickedButtonRemoveHoverScript()
{
	if (!m_strHoverScriptPath.IsEmpty())
		if (MessageBox("Delete current hover script?", "Warning", MB_YESNO | MB_ICONINFORMATION) == IDNO)
			return;

	m_editHoverScript.SetWindowTextA("\n");
	m_strHoverPureScriptPath.Empty();
	m_strHoverScriptPath.Empty();
}


void CAddGUIButton::OnBnClickedButtonAddRightClkScript()
{
	CFileDialog dlgOpen(TRUE, _T("*.lua"), _T(""), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR,
		_T("LUA File (*.lua)|*.lua||"), NULL, NULL);
	if (IDOK == dlgOpen.DoModal())
	{
		m_strRightClickScriptPath = (CString)dlgOpen.GetPathName();
		m_strRightClickPureScriptPath = dlgOpen.GetFileTitle();

		m_editRightClickScript.SetWindowText(m_strRightClickScriptPath);

		m_updateRightClickScript = CTrue;

	}
}


void CAddGUIButton::OnBnClickedButtonRemoveRightClkScript()
{
	if (!m_strRightClickScriptPath.IsEmpty())
		if (MessageBox("Delete current right click script?", "Warning", MB_YESNO | MB_ICONINFORMATION) == IDNO)
			return;

	m_editRightClickScript.SetWindowTextA("\n");
	m_strRightClickScriptPath.Empty();
	m_strRightClickPureScriptPath.Empty();
}

CVoid CAddGUIButton::SetCreate(CBool create)
{
	m_create = create;
}

void CAddGUIButton::OnBnClickedOk()
{
	if (m_strName.IsEmpty())
	{
		MessageBox("Please specify the name", "Vanda Engine Error", MB_OK | MB_ICONINFORMATION);
		return;
	}
	else if (m_strPosX.IsEmpty())
	{
		MessageBox("Please specify X position", "Vanda Engine Error", MB_OK | MB_ICONINFORMATION);
		return;
	}
	else if (m_strPosY.IsEmpty())
	{
		MessageBox("Please specify Y position", "Vanda Engine Error", MB_OK | MB_ICONINFORMATION);
		return;
	}
	else if (m_strMainImgPath.IsEmpty())
	{
		MessageBox("Please specify main image", "Vanda Engine Error", MB_OK | MB_ICONINFORMATION);
		return;
	}
	else if (m_strSize.IsEmpty())
	{
		MessageBox("Please specify size", "Vanda Engine Error", MB_OK | MB_ICONINFORMATION);
		return;
	}

	if (!m_strLeftClickScriptPath.IsEmpty() && m_strLeftClickImgPath.IsEmpty())
	{
		MessageBox("Please specify left click image", "Vanda Engine Error", MB_OK | MB_ICONERROR);
		return;
	}
	if (!m_strRightClickScriptPath.IsEmpty() && m_strRightClickImgPath.IsEmpty())
	{
		MessageBox("Please specify right click image", "Vanda Engine Error", MB_OK | MB_ICONERROR);
		return;
	}
	if (!m_strHoverScriptPath.IsEmpty() && m_strHoverImgPath.IsEmpty())
	{
		MessageBox("Please specify hover image", "Vanda Engine Error", MB_OK | MB_ICONERROR);
		return;
	}

	for (std::vector<std::string>::iterator it = g_guiNames.begin(); it != g_guiNames.end(); it++)
	{
		if (!m_create)
			if (Cmp((LPCTSTR)m_strTempName, (*it).c_str()))
				break;

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

	if (!m_strDisableImgPath.IsEmpty())
		m_hasDisableImage = CTrue;
	else
		m_hasDisableImage = CFalse;

	if (!m_strHoverImgPath.IsEmpty())
		m_hasHoverImage = CTrue;
	else
		m_hasHoverImage = CFalse;

	if (!m_strLeftClickImgPath.IsEmpty())
		m_hasLeftClickImage = CTrue;
	else
		m_hasLeftClickImage = CFalse;

	if (!m_strRightClickImgPath.IsEmpty())
		m_hasRightClickImage = CTrue;
	else
		m_hasRightClickImage = CFalse;

	if (!m_strLeftClickScriptPath.IsEmpty())
		m_hasLeftClickScript = CTrue;
	else
		m_hasLeftClickScript = CFalse;

	if (!m_strRightClickScriptPath.IsEmpty())
		m_hasRightClickScript = CTrue;
	else
		m_hasRightClickScript = CFalse;

	if (!m_strHoverScriptPath.IsEmpty())
		m_hasHoverScript = CTrue;
	else
		m_hasHoverScript = CFalse;

	if (m_create)
	{
		CGUIButton* guiButton = CNew(CGUIButton);

		guiButton->SetName(m_strName.GetBuffer(m_strName.GetLength()));
		CVec2f pos(m_fPosX, m_fPosY);
		guiButton->SetSize(m_fSize);
		guiButton->SetMainImagePath(m_strMainImgPath.GetBuffer(m_strMainImgPath.GetLength()));
		guiButton->LoadMainImage();
		guiButton->SetPosition(pos);

		if (!m_strDisableImgPath.IsEmpty())
		{
			guiButton->SetDisableImagePath(m_strDisableImgPath.GetBuffer(m_strDisableImgPath.GetLength()));
			guiButton->SetHasDisableImage(CTrue);
			guiButton->LoadDisableImage();
		}
		else
		{
			guiButton->SetHasDisableImage(CFalse);
		}
		if (!m_strHoverImgPath.IsEmpty())
		{
			guiButton->SetHoverImagePath(m_strHoverImgPath.GetBuffer(m_strHoverImgPath.GetLength()));
			guiButton->SetHasHoverImage(CTrue);
			guiButton->LoadHoverImage();
		}
		else
		{
			guiButton->SetHasHoverImage(CFalse);
		}
		if (!m_strLeftClickImgPath.IsEmpty())
		{
			guiButton->SetLeftClickImagePath(m_strLeftClickImgPath.GetBuffer(m_strLeftClickImgPath.GetLength()));
			guiButton->SetHasLeftClickImage(CTrue);
			guiButton->LoadLeftClickImage();
		}
		else
		{
			guiButton->SetHasLeftClickImage(CFalse);
		}
		if (!m_strRightClickImgPath.IsEmpty())
		{
			guiButton->SetRightClickImagePath(m_strRightClickImgPath.GetBuffer(m_strRightClickImgPath.GetLength()));
			guiButton->SetHasRightClickImage(CTrue);
			guiButton->LoadRightClickImage();
		}
		else
		{
			guiButton->SetHasRightClickImage(CFalse);
		}
		if (!m_strLeftClickScriptPath.IsEmpty())
		{
			guiButton->SetLeftClickScriptPath(m_strLeftClickScriptPath.GetBuffer(m_strLeftClickScriptPath.GetLength()));
			guiButton->SetHasLeftClickScript(CTrue);
		}
		else
		{
			guiButton->SetHasLeftClickScript(CFalse);
		}
		if (!m_strRightClickScriptPath.IsEmpty())
		{
			guiButton->SetRightClickScriptPath(m_strRightClickScriptPath.GetBuffer(m_strRightClickScriptPath.GetLength()));
			guiButton->SetHasRightClickScript(CTrue);
		}
		else
		{
			guiButton->SetHasRightClickScript(CFalse);
		}
		if (!m_strHoverScriptPath.IsEmpty())
		{
			guiButton->SetHoverScriptPath(m_strHoverScriptPath.GetBuffer(m_strHoverScriptPath.GetLength()));
			guiButton->SetHasHoverScript(CTrue);
		}
		else
		{
			guiButton->SetHasHoverScript(CFalse);
		}

		guiButton->SetUpdateMainImage(CTrue);
		guiButton->SetUpdateLeftClickImage(CTrue);
		guiButton->SetUpdateHoverImage(CTrue);
		guiButton->SetUpdateRightClickImage(CTrue);
		guiButton->SetUpdateDisableImage(CTrue);
		guiButton->SetUpdateLeftClickScript(CTrue);
		guiButton->SetUpdateRightClickScript(CTrue);
		guiButton->SetUpdateHoverScript(CTrue);

		if (!Cmp(g_currentPackageAndGUIName, "\n"))
		{
			guiButton->SetPackageName(g_currentGUIPackageName);
			guiButton->SetGUIName(g_currentGUIName);
		}

		g_guiButtons.push_back(guiButton);
		g_guiNames.push_back(m_strName.GetBuffer(m_strName.GetLength()));

		ex_pVandaEngine1Dlg->InsertItemToGUIList(m_strName.GetBuffer(m_strName.GetLength()), eGUILIST_BUTTON);
		PrintInfo("\nButton added successfully");

	}

	CDialog::OnOK();
}

CVoid CAddGUIButton::SetName(CChar* name)
{
	m_strName = name;
	m_strTempName = name;
}

CVoid CAddGUIButton::SetPosition(CVec2f pos)
{
	m_fPosX = pos.x;
	m_fPosY = pos.y;

	m_strPosX.Format("%.3f", m_fPosX);
	m_strPosY.Format("%.3f", m_fPosY);
}

CVoid CAddGUIButton::SetSize(CFloat size)
{
	m_fSize = size;
	m_strSize.Format("%.3f", m_fSize);
}

CVoid CAddGUIButton::SetMainImagePath(CChar* path)
{
	m_strMainImgPath = path;
}

CVoid CAddGUIButton::SetLeftClickImagePath(CChar* path)
{
	m_strLeftClickImgPath = path;
}

CVoid CAddGUIButton::SetHoverImagePath(CChar* path)
{
	m_strHoverImgPath = path;
}

CVoid CAddGUIButton::SetRightClickImagePath(CChar* path)
{
	m_strRightClickImgPath = path;
}

CVoid CAddGUIButton::SetDisableImagePath(CChar* path)
{
	m_strDisableImgPath = path;
}

CVoid CAddGUIButton::SetLeftClickScriptPath(CChar* path)
{
	m_strLeftClickScriptPath = path;
}

CVoid CAddGUIButton::SetHoverScriptPath(CChar* path)
{
	m_strHoverScriptPath = path;
}

CVoid CAddGUIButton::SetRightClickScriptPath(CChar* path)
{
	m_strRightClickScriptPath = path;
}

CChar* CAddGUIButton::GetName()
{
	return m_strName.GetBuffer(m_strName.GetLength());
}

CVec2f CAddGUIButton::GetPosition()
{
	CVec2f pos(m_fPosX, m_fPosY);
	return pos;
}

CFloat CAddGUIButton::GetSize()
{
	return m_fSize;
}

CChar* CAddGUIButton::GetMainImagePath()
{
	return m_strMainImgPath.GetBuffer(m_strMainImgPath.GetLength());
}

CChar* CAddGUIButton::GetLeftClickImagePath()
{
	return m_strLeftClickImgPath.GetBuffer(m_strLeftClickImgPath.GetLength());
}

CChar* CAddGUIButton::GetHoverImagePath()
{
	return m_strHoverImgPath.GetBuffer(m_strHoverImgPath.GetLength());
}

CChar* CAddGUIButton::GetRightClickImagePath()
{
	return m_strRightClickImgPath.GetBuffer(m_strRightClickImgPath.GetLength());
}

CChar* CAddGUIButton::GetDisableImagePath()
{
	return m_strDisableImgPath.GetBuffer(m_strDisableImgPath.GetLength());
}

CChar* CAddGUIButton::GetLeftClickScriptPath()
{
	return m_strLeftClickScriptPath.GetBuffer(m_strLeftClickScriptPath.GetLength());
}

CChar* CAddGUIButton::GetHoverScriptPath()
{
	return m_strHoverScriptPath.GetBuffer(m_strHoverScriptPath.GetLength());
}

CChar* CAddGUIButton::GetRightClickScriptPath()
{
	return m_strRightClickScriptPath.GetBuffer(m_strRightClickScriptPath.GetLength());
}

BOOL CAddGUIButton::OnInitDialog()
{
	CDialog::OnInitDialog();

	if (m_create)
	{
		m_fPosX = g_width / 2;
		m_fPosY = g_height / 2;
		m_strPosX.Format("%.3f", m_fPosX); m_strPosY.Format("%.3f", m_fPosY);
		m_editPosX.SetWindowTextA(m_strPosX);
		m_editPosY.SetWindowTextA(m_strPosY);

		m_fSize = 10.0f;
		m_strSize = "10.0";
		m_editSize.SetWindowTextA(m_strSize);
	}
	else
	{
		m_editName.SetWindowTextA(m_strName);
		m_editPosX.SetWindowTextA(m_strPosX);
		m_editPosY.SetWindowTextA(m_strPosY);
		m_editSize.SetWindowTextA(m_strSize);
		
		m_editMainImg.SetWindowTextA(m_strMainImgPath);
		m_editLeftClickImg.SetWindowTextA(m_strLeftClickImgPath);
		m_editHoverImg.SetWindowTextA(m_strHoverImgPath);
		m_editRightClickImg.SetWindowTextA(m_strRightClickImgPath);
		m_editDisableImg.SetWindowTextA(m_strDisableImgPath);

		m_editLeftClickScript.SetWindowTextA(m_strLeftClickScriptPath);
		m_editHoverScript.SetWindowTextA(m_strHoverScriptPath);
		m_editRightClickScript.SetWindowTextA(m_strRightClickScriptPath);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CAddGUIButton::OnEnChangeEditSize()
{
	m_editSize.GetWindowTextA(m_strSize);
	m_fSize = atof(m_strSize);
}


void CAddGUIButton::OnEnChangeEditName()
{
	m_editName.GetWindowTextA(m_strName);
}


void CAddGUIButton::OnEnChangeEditPosX()
{
	m_editPosX.GetWindowTextA(m_strPosX);
	m_fPosX = atof(m_strPosX);
}


void CAddGUIButton::OnEnChangeEditPosY()
{
	m_editPosY.GetWindowTextA(m_strPosY);
	m_fPosY = atof(m_strPosY);
}
