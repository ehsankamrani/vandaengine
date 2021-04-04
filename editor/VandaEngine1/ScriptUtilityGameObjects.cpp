// ScriptUtilityGameObjects.cpp : implementation file
//

#include "stdafx.h"
#include "VandaEngine1.h"
#include "ScriptUtilityGameObjects.h"
#include "afxdialogex.h"


// CScriptUtilityGameObjects dialog

IMPLEMENT_DYNAMIC(CScriptUtilityGameObjects, CDialog)

CScriptUtilityGameObjects::CScriptUtilityGameObjects(CWnd* pParent /*=NULL*/)
	: CDialog(CScriptUtilityGameObjects::IDD, pParent)
{

}

CScriptUtilityGameObjects::~CScriptUtilityGameObjects()
{
}

void CScriptUtilityGameObjects::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RICHED_GAME_OBJECT_NAME, m_richGameObjectName);
	DDX_Control(pDX, IDC_LIST_GAME_OBJECTS, m_listGameObjectNames);
	DDX_Control(pDX, IDC_STATIC_PROJECT_VSCENE_NAME, m_textProjectVSceneName);
}


BEGIN_MESSAGE_MAP(CScriptUtilityGameObjects, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_COPY_GAME_OBJECT_NAME, &CScriptUtilityGameObjects::OnBnClickedButtonCopyGameObjectName)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_GAME_OBJECTS, &CScriptUtilityGameObjects::OnLvnItemchangedListGameObjects)
END_MESSAGE_MAP()


// CScriptUtilityGameObjects message handlers


void CScriptUtilityGameObjects::OnBnClickedButtonCopyGameObjectName()
{
	CString s;
	m_richGameObjectName.GetWindowTextA(s);
	if (s.IsEmpty())
		MessageBox("Please select a game object from the list!", "Error", MB_OK | MB_ICONERROR);
	else
	{
		m_richGameObjectName.Copy();
		CChar message[MAX_URI_SIZE];
		sprintf(message, "Item '%s' copied to clipboard", s);
		MessageBox(message, "Report", MB_OK | MB_ICONINFORMATION);
	}
}


BOOL CScriptUtilityGameObjects::OnInitDialog()
{
	CDialog::OnInitDialog();

	CChar text[MAX_NAME_SIZE];
	sprintf(text, "Project: %s - VScene: %s", m_projectName, m_VSceneName);
	m_textProjectVSceneName.SetWindowTextA(text);

	CBitmap cBmp;
	CBitmap* cBmpMask = NULL;

	m_engineObjectListImage.Create(32, 32, ILC_COLOR24, 10, 10);
	cBmp.LoadBitmap(IDB_BITMAP_SCRIPT_UTILITY_STATIC_SOUND);
	m_engineObjectListImage.Add(&cBmp, cBmpMask);
	cBmp.DeleteObject();
	cBmp.LoadBitmap(IDB_BITMAP_SCRIPT_UTILITY_CAMERA);
	m_engineObjectListImage.Add(&cBmp, cBmpMask);
	cBmp.DeleteObject();

	m_listGameObjectNames.SetImageList(&m_engineObjectListImage, LVSIL_SMALL);

	RECT tempRect;
	m_listGameObjectNames.GetClientRect(&tempRect);
	m_listGameObjectNames.InsertColumn(0, "Game Objects", LVCFMT_LEFT | LVS_SHOWSELALWAYS, (tempRect.right - tempRect.left) * 90 / 100);
	m_listGameObjectNames.ShowWindow(SW_SHOW);
	m_listGameObjectNames.UpdateWindow();

	CInt gameObjectIndex = -1;

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
					for (CUInt j = 0; j < g_projects[pr]->m_vsceneObjectNames[vs].m_staticSoundsNames.size(); j++)
					{
						gameObjectIndex++;
						int index = gameObjectIndex;
						LVITEM lvItem;
						lvItem.mask = LVIF_TEXT | LVIF_IMAGE;
						lvItem.iItem = index;
						lvItem.iSubItem = 0;
						lvItem.iImage = 0; //static sound
						lvItem.pszText = (CChar*)g_projects[pr]->m_vsceneObjectNames[vs].m_staticSoundsNames[j].c_str();
						m_listGameObjectNames.InsertItem(&lvItem);
						m_listGameObjectNames.SetExtendedStyle(LVS_EX_INFOTIP | LVS_EX_ONECLICKACTIVATE | LVS_EX_LABELTIP);

						m_listGameObjectNames.EnsureVisible(index, FALSE);
						m_listGameObjectNames.UpdateWindow();

						if (gameObjectIndex == 0)
						{
							m_richGameObjectName.SetWindowTextA(lvItem.pszText);
							CInt end = m_richGameObjectName.GetWindowTextLengthA();
							m_richGameObjectName.SetSel(0, end);
						}
					}
					for (CUInt j = 0; j < g_projects[pr]->m_vsceneObjectNames[vs].m_engineCameraNames.size(); j++)
					{
						gameObjectIndex++;
						int index = gameObjectIndex;
						LVITEM lvItem;
						lvItem.mask = LVIF_TEXT | LVIF_IMAGE;
						lvItem.iItem = index;
						lvItem.iSubItem = 0;
						lvItem.iImage = 1; //camera
						lvItem.pszText = (CChar*)g_projects[pr]->m_vsceneObjectNames[vs].m_engineCameraNames[j].c_str();
						m_listGameObjectNames.InsertItem(&lvItem);
						m_listGameObjectNames.SetExtendedStyle(LVS_EX_INFOTIP | LVS_EX_ONECLICKACTIVATE | LVS_EX_LABELTIP);

						m_listGameObjectNames.EnsureVisible(index, FALSE);
						m_listGameObjectNames.UpdateWindow();

						if (gameObjectIndex == 0)
						{
							m_richGameObjectName.SetWindowTextA(lvItem.pszText);
							CInt end = m_richGameObjectName.GetWindowTextLengthA();
							m_richGameObjectName.SetSel(0, end);
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

	if (m_listGameObjectNames.GetItemCount())
	{
		m_listGameObjectNames.SetItemState(0, LVIS_SELECTED, LVIS_SELECTED | LVIS_FOCUSED);
		m_listGameObjectNames.SetSelectionMark(0);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

CVoid CScriptUtilityGameObjects::SetSelectedProjectAndVSceneNames(CChar* projectName, CChar* VSceneName)
{
	Cpy(m_projectName, projectName);
	Cpy(m_VSceneName, VSceneName);
}

void CScriptUtilityGameObjects::OnLvnItemchangedListGameObjects(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	int nSelected = -1;
	POSITION p = m_listGameObjectNames.GetFirstSelectedItemPosition();
	while (p)
	{
		nSelected = m_listGameObjectNames.GetNextSelectedItem(p);
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
		m_listGameObjectNames.GetItem(&lvi);

		m_richGameObjectName.SetWindowTextA(szBuffer);
		CInt end = m_richGameObjectName.GetWindowTextLengthA();
		m_richGameObjectName.SetSel(0, end);

	}
	else
	{
		m_richGameObjectName.SetWindowTextA("");
		m_richGameObjectName.SetSel(0, 0);
	}

	*pResult = 0;
}
