// ScriptUtilityImportedCameras.cpp : implementation file
//

#include "stdafx.h"
#include "VandaEngine1.h"
#include "ScriptUtilityImportedCameras.h"
#include "afxdialogex.h"


// CScriptUtilityImportedCameras dialog

IMPLEMENT_DYNAMIC(CScriptUtilityImportedCameras, CDialog)

CScriptUtilityImportedCameras::CScriptUtilityImportedCameras(CWnd* pParent /*=NULL*/)
	: CDialog(CScriptUtilityImportedCameras::IDD, pParent)
{

}

CScriptUtilityImportedCameras::~CScriptUtilityImportedCameras()
{
}

void CScriptUtilityImportedCameras::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RICHED_IMPORTED_CAMERAS_NAME, m_richImportedCameraName);
	DDX_Control(pDX, IDC_LIST_IMPORTED_CAMERAS, m_listImportedCameras);
	DDX_Control(pDX, IDC_STATIC_PROJECT_VSCENE_NAME, m_textProjectVSceneName);
}


BEGIN_MESSAGE_MAP(CScriptUtilityImportedCameras, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_COPY_IMPORTED_CAMERA_NAME, &CScriptUtilityImportedCameras::OnBnClickedButtonCopyImportedCameraName)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_IMPORTED_CAMERAS, &CScriptUtilityImportedCameras::OnLvnItemchangedListImportedCameras)
END_MESSAGE_MAP()


// CScriptUtilityImportedCameras message handlers


void CScriptUtilityImportedCameras::OnBnClickedButtonCopyImportedCameraName()
{
	CString s;
	m_richImportedCameraName.GetWindowTextA(s);
	if (s.IsEmpty())
		MessageBox("Please select a camera from the list!", "Error", MB_OK | MB_ICONERROR);
	else
	{
		m_richImportedCameraName.Copy();
		CChar message[MAX_URI_SIZE];
		sprintf(message, "Item '%s' copied to clipboard", s);
		MessageBox(message, "Report", MB_OK | MB_ICONINFORMATION);
	}
}


BOOL CScriptUtilityImportedCameras::OnInitDialog()
{
	CDialog::OnInitDialog();

	CChar text[MAX_NAME_SIZE];
	sprintf(text, "Project: %s - VScene: %s", m_projectName, m_VSceneName);
	m_textProjectVSceneName.SetWindowTextA(text);

	RECT tempRect;
	m_listImportedCameras.GetClientRect(&tempRect);
	m_listImportedCameras.InsertColumn(0, "Cameras", LVCFMT_LEFT | LVS_SHOWSELALWAYS, (tempRect.right - tempRect.left) * 90 / 100);
	m_listImportedCameras.ShowWindow(SW_SHOW);
	m_listImportedCameras.UpdateWindow();

	CInt importedCameraIndex = -1;

	CBool foundTarget = CFalse;

	for (CUInt pr = 0; pr < g_projects.size(); pr++)
	{
		if (Cmp(g_projects[pr]->m_name, m_projectName))
		{
			for (CUInt vs = 0; vs < g_projects[pr]->m_sceneNames.size(); vs++)
			{
				CChar VSceneNameWithoutDot[MAX_NAME_SIZE];
				Cpy(VSceneNameWithoutDot, g_projects[pr]->m_sceneNames[vs].c_str());
				GetWithoutDot(VSceneNameWithoutDot);

				if (Cmp(VSceneNameWithoutDot, m_VSceneName))
				{
					for (CUInt j = 0; j < g_projects[pr]->m_vsceneObjectNames[vs].m_importedCameraNames.size(); j++)
					{
						importedCameraIndex++;
						int index = importedCameraIndex;
						LVITEM lvItem;
						lvItem.mask = LVIF_TEXT;
						lvItem.iItem = index;
						lvItem.iSubItem = 0;
						lvItem.pszText = (CChar*)g_projects[pr]->m_vsceneObjectNames[vs].m_importedCameraNames[j].c_str();
						m_listImportedCameras.InsertItem(&lvItem);
						m_listImportedCameras.SetExtendedStyle(LVS_EX_INFOTIP | LVS_EX_ONECLICKACTIVATE | LVS_EX_LABELTIP);

						m_listImportedCameras.EnsureVisible(index, FALSE);
						m_listImportedCameras.UpdateWindow();

						if (importedCameraIndex == 0)
						{
							m_richImportedCameraName.SetWindowTextA(lvItem.pszText);
							CInt end = m_richImportedCameraName.GetWindowTextLengthA();
							m_richImportedCameraName.SetSel(0, end);
						}
					}
					foundTarget = CTrue;
				}
				if (foundTarget)
					break;
			}
		}
		if (foundTarget)
			break;
	}

	if ( m_listImportedCameras.GetItemCount())
	{
		m_listImportedCameras.SetItemState(0, LVIS_SELECTED, LVIS_SELECTED | LVIS_FOCUSED);
		m_listImportedCameras.SetSelectionMark(0);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CScriptUtilityImportedCameras::OnLvnItemchangedListImportedCameras(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	int nSelected = -1;
	POSITION p = m_listImportedCameras.GetFirstSelectedItemPosition();
	while (p)
	{
		nSelected = m_listImportedCameras.GetNextSelectedItem(p);
	}
	TCHAR szBuffer[1024];

	if (nSelected >= 0)
	{
		DWORD cchBuf(1024);
		LVITEM lvi;
		lvi.iItem = nSelected;
		lvi.iSubItem = 0;
		lvi.mask = LVIF_TEXT;
		lvi.pszText = szBuffer;
		lvi.cchTextMax = cchBuf;
		m_listImportedCameras.GetItem(&lvi);

		m_richImportedCameraName.SetWindowTextA(szBuffer);
		CInt end = m_richImportedCameraName.GetWindowTextLengthA();
		m_richImportedCameraName.SetSel(0, end);

	}
	else
	{
		m_richImportedCameraName.SetWindowTextA("");
		m_richImportedCameraName.SetSel(0, 0);
	}

	*pResult = 0;
}

CVoid CScriptUtilityImportedCameras::SetSelectedProjectAndVSceneNames(CChar* projectName, CChar* VSceneName)
{
	Cpy(m_projectName, projectName);
	Cpy(m_VSceneName, VSceneName);
}