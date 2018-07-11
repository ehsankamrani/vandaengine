// EditVSceneName.cpp : implementation file
//

#include "stdafx.h"
#include "VandaEngine1.h"
#include "EditVSceneName.h"
#include "afxdialogex.h"


// CEditVSceneName dialog

IMPLEMENT_DYNAMIC(CEditVSceneName, CDialog)

CEditVSceneName::CEditVSceneName(CWnd* pParent /*=NULL*/)
	: CDialog(CEditVSceneName::IDD, pParent)
{
	m_save = CTrue;
	Cpy(m_name, "\n");
	Cpy(m_selectedName, "\n");
	m_VSceneIndex = -1;
}

CEditVSceneName::~CEditVSceneName()
{
}

void CEditVSceneName::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PREFAB_NAME, m_editName);
	DDX_Control(pDX, IDC_LIST_VSCENES, m_listVScenes);
}


BEGIN_MESSAGE_MAP(CEditVSceneName, CDialog)
	ON_BN_CLICKED(IDOK, &CEditVSceneName::OnBnClickedOk)
	ON_EN_CHANGE(IDC_PREFAB_NAME, &CEditVSceneName::OnEnChangePrefabName)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_VSCENES, &CEditVSceneName::OnLvnItemchangedListVscenes)
END_MESSAGE_MAP()


// CEditVSceneName message handlers


void CEditVSceneName::OnBnClickedOk()
{
	if (m_strName.IsEmpty())
	{
		MessageBox("Please choose a name", "Vanda Engine Error", MB_OK | MB_ICONERROR);
		return;
	}
	CBool foundTarget = CFalse;
	Cpy(m_name, (LPCTSTR)m_strName);
	GetWithoutDot(m_name);
	Append(m_name, ".vin");

	CChar selectedName[MAX_NAME_SIZE];
	Cpy(selectedName, m_selectedName);
	Append(selectedName, ".vin");
	for (CUInt i = 0; i < g_VSceneNamesOfCurrentProject.size(); i++)
	{
		if (!m_save)
		{
			if (!Cmp(g_VSceneNamesOfCurrentProject[i].c_str(), selectedName))
			{
				if (Cmp(m_name, g_VSceneNamesOfCurrentProject[i].c_str()))
				{
					foundTarget = CTrue;
					break;
				}
			}
		}
		else
		{
			if (Cmp(m_name, g_VSceneNamesOfCurrentProject[i].c_str()))
			{
				foundTarget = CTrue;
					break;
			}
		}
	}
	if (foundTarget)
	{
		if (m_save)
		{
			if (MessageBox("This VScene already exits. Do you want to overwrite it?", "Vanda Engine Report", MB_OK | MB_ICONINFORMATION | MB_YESNO) == IDYES)
				CDialog::OnOK();
			else
				return;
		}
		else
		{
			MessageBox("This VScene name already exits. Please choose another name.", "Vanda Engine Error", MB_OK | MB_ICONERROR);
			return;
		}
	}
	CDialog::OnOK();
}

void CEditVSceneName::SetInitialData(CBool save, CChar* selName)
{
	m_save = save;
	if (selName)
		Cpy(m_selectedName, selName);
}


void CEditVSceneName::OnEnChangePrefabName()
{
	m_editName.GetWindowTextA(m_strName);
}

CChar* CEditVSceneName::GetName()
{
	return m_name;
}

BOOL CEditVSceneName::OnInitDialog()
{
	CDialog::OnInitDialog();
	if (!Cmp(m_selectedName, "\n"))
		m_editName.SetWindowTextA(m_selectedName);
	RECT tempRect;
	m_listVScenes.GetClientRect(&tempRect);

	CBitmap cBmp;
	CBitmap* cBmpMask = NULL;
	m_VSceneImage.Create(80, 80, ILC_COLOR24, 1, 1);

	cBmp.LoadBitmap(IDB_BITMAP_DEFAULT_VIN);
	m_VSceneImage.Add(&cBmp, cBmpMask);
	cBmp.DeleteObject();

	m_listVScenes.SetImageList(&m_VSceneImage, LVSIL_NORMAL);

	m_listVScenes.GetClientRect(&tempRect);
	m_listVScenes.InsertColumn(0, "VScenes", LVCFMT_LEFT | LVS_SHOWSELALWAYS, (tempRect.right - tempRect.left) * 80 / 100);
	m_listVScenes.ShowWindow(SW_SHOW);
	m_listVScenes.UpdateWindow();

	//insert items
	m_listVScenes.SetExtendedStyle(LVS_EX_INFOTIP | LVS_EX_ONECLICKACTIVATE);

	for (CUInt i = 0; i < g_VSceneNamesOfCurrentProject.size(); i++)
	{
		CChar str[MAX_NAME_SIZE];
		Cpy(str, g_VSceneNamesOfCurrentProject[i].c_str());
		InsertItemToVSceneList(str);
	}

	m_editName.SetWindowTextA("");

	return TRUE;  // return TRUE unless you set the focus to a control
}

CVoid CEditVSceneName::InsertItemToVSceneList(CChar* vsceneName)
{
	m_VSceneIndex++;
	int index = m_VSceneIndex;
	LVITEM lvItem;
	lvItem.mask = LVIF_TEXT;
	lvItem.iItem = index;
	lvItem.iSubItem = 0;
	lvItem.pszText = vsceneName;
	m_listVScenes.InsertItem(&lvItem);

	m_listVScenes.SetItemState(index, LVIS_SELECTED, LVIS_SELECTED | LVIS_FOCUSED);
	m_listVScenes.SetSelectionMark(index);
	m_listVScenes.EnsureVisible(index, FALSE);
	m_listVScenes.UpdateWindow();
}

void CEditVSceneName::OnLvnItemchangedListVscenes(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	int nSelected = -1;
	POSITION p = m_listVScenes.GetFirstSelectedItemPosition();
	while (p)
	{
		nSelected = m_listVScenes.GetNextSelectedItem(p);
	}
	TCHAR szBuffer[1024]; //package

	if (nSelected >= 0)
	{
		DWORD cchBuf(1024);
		LVITEM lvi;
		lvi.iItem = nSelected;
		lvi.iSubItem = 0;
		lvi.mask = LVIF_TEXT;
		lvi.pszText = szBuffer;
		lvi.cchTextMax = cchBuf;
		m_listVScenes.GetItem(&lvi);
		GetWithoutDot(szBuffer);
		m_editName.SetWindowTextA(szBuffer);
	}
	*pResult = 0;
}
