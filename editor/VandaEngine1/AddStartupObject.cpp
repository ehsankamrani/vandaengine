// AddStartupObject.cpp : implementation file
//

#include "stdafx.h"
#include "VandaEngine1.h"
#include "AddStartupObject.h"
#include "afxdialogex.h"
#include "ScriptEditor.h"

// CAddStartupObject dialog

IMPLEMENT_DYNAMIC(CAddStartupObject, CDialog)

CAddStartupObject::CAddStartupObject(CWnd* pParent /*=NULL*/)
	: CDialog(CAddStartupObject::IDD, pParent)
	, m_strName(_T(""))
	, m_strScript(_T(""))
{
	m_updateScript = CFalse;
	Cpy(m_strOldName, "\n");
	m_create = CTrue;
}

CAddStartupObject::~CAddStartupObject()
{
}

void CAddStartupObject::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_STARTUP_NAME, m_editName);
	DDX_Control(pDX, IDC_EDIT_SCRIPT, m_editScript);
}


BEGIN_MESSAGE_MAP(CAddStartupObject, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_ADD_SCRIPT, &CAddStartupObject::OnBnClickedButtonAddScript)
	ON_BN_CLICKED(IDC_BUTTON_REMOVE_SCRIPT, &CAddStartupObject::OnBnClickedButtonRemoveScript)
	ON_BN_CLICKED(IDOK, &CAddStartupObject::OnBnClickedOk)
	ON_EN_CHANGE(IDC_EDIT_STARTUP_NAME, &CAddStartupObject::OnEnChangeEditStartupName)
	ON_EN_CHANGE(IDC_EDIT_SCRIPT, &CAddStartupObject::OnEnChangeEditScript)
END_MESSAGE_MAP()


// CAddStartupObject message handlers


void CAddStartupObject::OnBnClickedButtonAddScript()
{
	CFileDialog dlgOpen(TRUE, _T("*.lua"), _T(""), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR,
		_T("LUA File (*.lua)|*.lua||"), NULL, NULL);
	if (IDOK == dlgOpen.DoModal())
	{
		m_strScript = (CString)dlgOpen.GetPathName();

		m_editScript.SetWindowText(m_strScript);

		m_updateScript = CTrue;
	}

	//CScriptEditor* m_dlgScriptEditor = CNew(CScriptEditor);
	//m_dlgScriptEditor->DoModal();
	//CDelete(m_dlgScriptEditor);
}

void CAddStartupObject::OnBnClickedButtonRemoveScript()
{
	if (!m_strScript.IsEmpty())
	{
		if (MessageBox("Remove current script?", "Warning", MB_YESNO) == IDYES)
		{
			m_strScript.Empty();
			m_editScript.SetWindowTextA("\n");
			m_updateScript = CTrue;
		}
	}
}

void CAddStartupObject::OnBnClickedOk()
{
	if (m_strName.IsEmpty() || m_strScript.IsEmpty())
	{
		MessageBox("Please specify name as well as script", "Vanda Engine Error", MB_OK | MB_ICONINFORMATION);
		return;
	}
	for (std::vector<std::string>::iterator it = g_engineObjectNames.begin(); it != g_engineObjectNames.end(); it++)
	{
		if (!Cmp(m_strOldName, (*it).c_str()) && Cmp((LPCTSTR)m_strName, (*it).c_str()))
		{
			MessageBox("This name already exists. Please select another name!", "Vanda Engine Error", MB_OK | MB_ICONERROR);
			return;
		}
	}

	if (m_create)
	{
		if (!g_startup)
			g_startup = CNew(CStartUp);
		CChar name[MAX_NAME_SIZE];
		CChar path[MAX_URI_SIZE];
		Cpy(name, m_strName.GetBuffer(m_strName.GetLength()));
		Cpy(path, m_strScript.GetBuffer(m_strScript.GetLength()));
		g_startup->SetName(name);
		g_startup->SetScriptPath(path);
		g_startup->SetUpdateScript(m_updateScript);
		ex_pVandaEngine1Dlg->InsertItemToEngineObjectList(name, eENGINEOBJECTLIST_STARTUP);
		ex_pVandaEngine1Dlg->m_mainBtnStartup.EnableWindow(FALSE);
		ex_pVandaEngine1Dlg->GetMenu()->EnableMenuItem(ID_INSERT_STARTUP, MF_DISABLED);
		g_menu.m_insertStartup = CTrue;

		g_engineObjectNames.push_back(name);
	}

	CDialog::OnOK();
}


BOOL CAddStartupObject::OnInitDialog()
{
	CDialog::OnInitDialog();

	if (!m_strName.IsEmpty())
		m_editName.SetWindowTextA(m_strName);
	if (!m_strScript.IsEmpty())
		m_editScript.SetWindowTextA(m_strScript);

	// TODO:  Add extra initialization here

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CAddStartupObject::OnEnChangeEditStartupName()
{
	m_editName.GetWindowTextA(m_strName);
}


void CAddStartupObject::OnEnChangeEditScript()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}

CVoid CAddStartupObject::SetCreate(CBool state)
{
	m_create = state;
}

CBool CAddStartupObject::GetCreate()
{
	return m_create;
}