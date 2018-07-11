// AddMultipleAnimations.cpp : implementation file
//

#include "stdafx.h"
#include "VandaEngine1.h"
#include "AddMultipleAnimations.h"
#include "afxdialogex.h"


// CAddMultipleAnimations dialog

IMPLEMENT_DYNAMIC(CAddMultipleAnimations, CDialog)

CAddMultipleAnimations::CAddMultipleAnimations(CWnd* pParent /*=NULL*/)
	: CDialog(CAddMultipleAnimations::IDD, pParent)
{
	m_comboIndex = 0;
	m_baseModelName = "\n";
}

CAddMultipleAnimations::~CAddMultipleAnimations()
{
}

void CAddMultipleAnimations::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_ANIMATIONS, m_comboAnimations);
	DDX_Control(pDX, IDC_EDIT_BASE_MODEL, m_editBoxBaseModel);
}


BEGIN_MESSAGE_MAP(CAddMultipleAnimations, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_ADD_TO_LIST, &CAddMultipleAnimations::OnBnClickedButtonAddToList)
	ON_BN_CLICKED(IDOK, &CAddMultipleAnimations::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_ADD_BASE_MODEL, &CAddMultipleAnimations::OnBnClickedButtonAddBaseModel)
END_MESSAGE_MAP()


// CAddMultipleAnimations message handlers


void CAddMultipleAnimations::OnBnClickedButtonAddToList()
{
	CFileDialog dlgOpen(TRUE, _T("*.dae"), _T(""), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR,
		_T("COLLADA File (*.dae)|*.dae||"), NULL, NULL);

	if (dlgOpen.DoModal() == IDOK)
	{
		CString fileName(dlgOpen.GetPathName());
		CString PurefileName(dlgOpen.GetFileName());
		CBool foundTarget = CFalse;
		for (CUInt i = 0; i < m_animationNames.size(); i++)
		{
			if (Cmp(m_animationNames[i].c_str(), (LPCTSTR)PurefileName))
				foundTarget = CTrue;
		}
		if (foundTarget)
		{
			MessageBox("You have already added this file", "Vanda Engine Error", MB_OK | MB_ICONERROR);
			return;
		}
		else
			m_animationNames.push_back((LPCTSTR)fileName);
		m_comboAnimations.InsertString(m_comboIndex, PurefileName);
		m_comboAnimations.SetCurSel(m_comboIndex);
		m_comboIndex++;
	}
}

void CAddMultipleAnimations::OnBnClickedOk()
{
	CChar baseName[MAX_NAME_SIZE];
	Cpy(baseName, m_baseModelName.c_str());
	if (Cmp(baseName, "\n"))
	{
		MessageBox("Please add base model.", "Vanda Engine Error.", MB_OK | MB_ICONINFORMATION);
		return;
	}
	CDialog::OnOK();
	
	ex_pVandaEngine1Dlg->OnMenuClickedImportColladaMultipleAnimations(baseName, m_animationNames);
}


void CAddMultipleAnimations::OnBnClickedButtonAddBaseModel()
{
	CFileDialog dlgOpen(TRUE, _T("*.dae"), _T(""), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR,
		_T("COLLADA File (*.dae)|*.dae||"), NULL, NULL);

	if (dlgOpen.DoModal() == IDOK)
	{
		CString fileName(dlgOpen.GetPathName());
		CString PurefileName(dlgOpen.GetFileName());


		if (g_editorMode == eMODE_PREFAB)
		{
			if (!(CmpIn(PurefileName.GetString(), "_LOD1") || CmpIn(PurefileName.GetString(), "_LOD2") || CmpIn(PurefileName.GetString(), "_LOD3")))
			{
				MessageBox("Couldn't find _LOD1, _LOD2, or LOD3 at the end of file name", "Vanda Engine Error", MB_OK | MB_ICONERROR);
				return;
			}
		}

		if (CmpIn(PurefileName.GetString(), "_LOD1"))
		{
			for (CUInt i = 0; i < g_scene.size(); i++)
			{
				if (CmpIn(g_scene[i]->m_pureFileName, "_LOD1"))
				{
					MessageBox("Up to one LOD 1 is supported.\nPlease remove current LOD 1 and try again.", "Vanda Engine Error", MB_OK | MB_ICONERROR);
					return;
				}
			}
		}
		else if (CmpIn(PurefileName.GetString(), "_LOD2"))
		{
			for (CUInt i = 0; i < g_scene.size(); i++)
			{
				if (CmpIn(g_scene[i]->m_pureFileName, "_LOD2"))
				{
					MessageBox("Up to one LOD 2 is supported.\nPlease remove current LOD 2 and try again.", "Vanda Engine Error", MB_OK | MB_ICONERROR);
					return;
				}
			}
		}
		else if (CmpIn(PurefileName.GetString(), "_LOD3"))
		{
			for (CUInt i = 0; i < g_scene.size(); i++)
			{
				if (CmpIn(g_scene[i]->m_pureFileName, "_LOD3"))
				{
					MessageBox("Up to one LOD 3 is supported.\nPlease remove current LOD 3 and try again.", "Vanda Engine Error", MB_OK | MB_ICONERROR);
					return;
				}
			}
		}

		m_editBoxBaseModel.SetWindowTextA(fileName);
		m_baseModelName.clear();
		m_baseModelName = (LPCTSTR)fileName;
	}
}
