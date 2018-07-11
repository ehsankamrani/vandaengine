// SavePrefabDlg.cpp : implementation file
//

#include "stdafx.h"
#include "VandaEngine1.h"
#include "SavePrefabDlg.h"
#include "afxdialogex.h"


// CSavePrefabDlg dialog

IMPLEMENT_DYNAMIC(CSavePrefabDlg, CDialog)

CSavePrefabDlg::CSavePrefabDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSavePrefabDlg::IDD, pParent)
{

}

CSavePrefabDlg::~CSavePrefabDlg()
{
}

void CSavePrefabDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PREFAB_NAME, m_editBoxPrefabName);
	DDX_Control(pDX, IDC_COMB_PREFAB_PACKAGE, m_prefabPackageList);
}

BEGIN_MESSAGE_MAP(CSavePrefabDlg, CDialog)
	ON_EN_CHANGE(IDC_PREFAB_NAME, &CSavePrefabDlg::OnEnChangePrefabName)
	ON_BN_CLICKED(IDC_BUTTON_ADD_PACKAGE, &CSavePrefabDlg::OnBnClickedButtonAddPackage)
END_MESSAGE_MAP()

// CSavePrefabDlg message handlers

void CSavePrefabDlg::OnEnChangePrefabName()
{
	m_editBoxPrefabName.GetWindowTextA(m_strPrefabName);
}

void CSavePrefabDlg::OnOK()
{
	CInt packageIndex;
	CChar new_name[MAX_NAME_SIZE];

	if (g_prefabPackagesAndNames.size() == 0)
	{
		MessageBox("Please select a package!", "Vanda Engine Error", MB_OK | MB_ICONINFORMATION);
		return;
	}

	if (m_strPrefabName.IsEmpty())
	{
		MessageBox("Please choose a name for the new prefab!");
		return;
	}
	else
	{
		packageIndex = m_prefabPackageList.GetCurSel();
		if (Cmp(g_prefabPackagesAndNames[packageIndex].front().c_str(), "Vanda_Basics") && !g_admin)
		{
			MessageBox("You can not save prefabs in Vanda_Basics package.", "Vanda Engine Error", MB_ICONERROR | MB_OK);
			return;
		}
		strcpy(new_name, (LPCTSTR)m_strPrefabName);
		//check the sub items of this package. Skip the first element. First one is the package name
		for (CUInt i = 0; i < g_prefabPackagesAndNames[packageIndex].size(); i++)
		{
			if (i == 0) continue;
			if (Cmp(g_prefabPackagesAndNames[packageIndex][i].c_str(), new_name))
			{
				MessageBox("This name already exists!", "Vanda Engine Error", MB_ICONERROR | MB_OK);
				return;
			}
		}
		//save prefab
		g_prefabPackagesAndNames[packageIndex].push_back(new_name);
	}
	m_strNewPrefabPackageName = g_prefabPackagesAndNames[packageIndex].front().c_str();

	m_strNewPrefabName = new_name;

	CChar packageAndPrefabName[MAX_NAME_SIZE];
	sprintf(packageAndPrefabName, "%s%s%s", g_prefabPackagesAndNames[packageIndex].front().c_str(), "_", new_name);
	m_strNewPackageAndPrefabName = packageAndPrefabName;

	GenerateRandomPassword();
	ex_pVandaEngine1Dlg->SavePrefabFiles();

	CDialog::OnOK();
}


BOOL CSavePrefabDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	for (CUInt i = 0; i < g_prefabPackagesAndNames.size(); i++)
	{
		if (Cmp(g_prefabPackagesAndNames[i].front().c_str(), "Vanda_Basics") && !g_admin)
		{
			continue;
		}
		else
			m_prefabPackageList.InsertString(i, g_prefabPackagesAndNames[i].front().c_str());
	}

	if (g_prefabPackagesAndNames.size())
	{
		m_prefabPackageList.SetCurSel(0);
		m_prefabPackageList.UpdateWindow();
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CSavePrefabDlg::OnBnClickedButtonAddPackage()
{
	m_prefabNameDlg = CNew(CPrefabNameDlg);
	m_prefabNameDlg->SetInitialData("\n", "\n", CTrue);
	if (IDOK == m_prefabNameDlg->DoModal())
	{
		m_prefabPackageList.InsertString(m_prefabPackageList.GetCount(), m_prefabNameDlg->GetNewName());
		m_prefabPackageList.SetCurSel(m_prefabPackageList.GetCount() - 1);
		m_prefabPackageList.UpdateWindow();
	}
	CDelete(m_prefabNameDlg);
}

void CSavePrefabDlg::GenerateRandomPassword()
{
	static string charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890=*&^%$#@!~-+)(_";
	string result;
	result.resize(100);

	for (int i = 0; i < 100; i++)
		result[i] = charset[rand() % charset.length()];
	m_strPassword = result.c_str();

}
