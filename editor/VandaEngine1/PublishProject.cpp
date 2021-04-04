//Copyright (C) 2021 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

// PublishProject.cpp : implementation file
//

#include "stdafx.h"
#include "VandaEngine1.h"
#include "PublishProject.h"


// CPublishProject dialog

IMPLEMENT_DYNAMIC(CPublishProject, CDialog)

CPublishProject::CPublishProject(CWnd* pParent /*=NULL*/)
	: CDialog(CPublishProject::IDD, pParent)
{

}

CPublishProject::~CPublishProject()
{
	for (int nItem = m_listBoxAvailableScenes.GetItemCount()-1; nItem >= 0 ;nItem-- )
	{
		m_listBoxAvailableScenes.DeleteItem(nItem);
	}

	for (int nItem = m_listBoxScenesToBePublished.GetItemCount()-1; nItem >= 0 ;nItem-- )
	{
		m_listBoxScenesToBePublished.DeleteItem(nItem);
	}


}

void CPublishProject::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_DESTINATION, m_editBoxDestination);
	DDX_Control(pDX, IDC_EDIT_ICON, m_editBoxIcon);
	DDX_Control(pDX, IDC_CHECK_SAVE, m_checkBoxSave);
	DDX_Control(pDX, IDC_EDIT_NAME, m_editBoxName);
	DDX_Control(pDX, IDC_EDIT_SPLASH_LOGO, m_editBoxSplash);
	DDX_Control(pDX, IDC_LIST_AVAILABLE_SCENES, m_listBoxAvailableScenes);
	DDX_Control(pDX, IDC_LIST_SCENES_TO_PUBLISH, m_listBoxScenesToBePublished);
	DDX_Control(pDX, IDC_CHECK_PUBLISH_DEBUG, m_checkBoxDebug);
}


BEGIN_MESSAGE_MAP(CPublishProject, CDialog)
	ON_BN_CLICKED(IDC_BTN_DESTINATION, &CPublishProject::OnBnClickedBtnDestination)
	ON_BN_CLICKED(IDC_BTN_ICON, &CPublishProject::OnBnClickedBtnIcon)
	ON_EN_CHANGE(IDC_EDIT_NAME, &CPublishProject::OnEnChangeEditName)
	ON_BN_CLICKED(IDC_BTN_SPLASH_IMAGE, &CPublishProject::OnBnClickedBtnSplashImage)
	ON_BN_CLICKED(IDADD, &CPublishProject::OnBnClickedAdd)
	ON_BN_CLICKED(IDREMOVE, &CPublishProject::OnBnClickedRemove)
	ON_BN_CLICKED(IDOK, &CPublishProject::OnBnClickedOk)
	ON_BN_CLICKED(ID_MARK_AS_FIRST_SCENE, &CPublishProject::OnBnClickedMarkAsFirstScene)
END_MESSAGE_MAP()


// CPublishProject message handlers

void CPublishProject::OnBnClickedBtnDestination()
{
	if (g_multipleView->m_enableTimer)
		g_multipleView->EnableTimer(CFalse);

    BROWSEINFO   bi; 
    ZeroMemory(&bi,   sizeof(bi)); 
    TCHAR   szDisplayName[MAX_PATH]; 
    szDisplayName[0]    =   _T('S');

    bi.hwndOwner        =   NULL; 
    bi.pidlRoot         =   NULL; 
    bi.pszDisplayName   =   szDisplayName; 
    bi.lpszTitle        =   _T("Please select a folder for storing received files :"); 
    bi.ulFlags          =   BIF_RETURNONLYFSDIRS;
    bi.lParam           =   NULL; 
    bi.iImage           =   0;  

    LPITEMIDLIST   pidl   =   SHBrowseForFolder(&bi);
    TCHAR   szPathName[MAX_PATH]; 
    if   (NULL   !=   pidl)
    {
         BOOL bRet = SHGetPathFromIDList(pidl,szPathName);
         if(FALSE == bRet)
              return;
        m_strDestination = (CString)szPathName;
		m_editBoxDestination.SetWindowTextA( m_strDestination );
    }
}

void CPublishProject::OnBnClickedBtnIcon()
{
	CInt result;
	CFileDialog dlgOpen(TRUE, _T("*.ico"), _T(""), OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR,
		_T("ICO File (*.ico)|*.ico||"), NULL, NULL);
	result = dlgOpen.DoModal();
	if( result == IDOK )
	{
		m_strIcon = (CString)dlgOpen.GetPathName();
		m_editBoxIcon.SetWindowTextA( m_strIcon );
	}
}

void CPublishProject::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class
	if( m_strIcon.IsEmpty() || m_strDestination.IsEmpty() || m_strName.IsEmpty() || m_strSplash.IsEmpty() )
	{
		MessageBox( "Please fill all of the required fields" );
		return;
	}
	else if( m_listBoxScenesToBePublished.GetItemCount() == 0 )
	{
		MessageBox( "You should select at least one scene to be published" );
		return;
	}
	else if(!m_setFirstScene)
	{
		if( m_listBoxScenesToBePublished.GetItemCount() ==  1 )
		{
			CString itemTitle = m_listBoxScenesToBePublished.GetItemText(0, 0);
			g_firstSceneNameToBeLoaded = itemTitle.GetBuffer(itemTitle.GetLength());
			itemTitle.ReleaseBuffer();
		}
		else
		{
			MessageBox( "Please mark the first scene to be loaded" );
			return;
		}
	}
	for (int nItem = m_listBoxScenesToBePublished.GetItemCount()-1; nItem >= 0 ;nItem-- )
	{
		CString itemTitle = m_listBoxScenesToBePublished.GetItemText(nItem, 0);
		g_VSceneNamesOfCurrentProjectToBePublished.push_back( itemTitle.GetBuffer(itemTitle.GetLength()));
		itemTitle.ReleaseBuffer();
	}

	CInt checkState = m_checkBoxSave.GetCheck();
	if( checkState == BST_CHECKED )
		m_saveCurrentScene = CTrue;
	else
		m_saveCurrentScene = CFalse;

	checkState = m_checkBoxDebug.GetCheck();
	if (checkState == BST_CHECKED)
		m_publishDebug = CTrue;
	else
		m_publishDebug = CFalse;

	CDialog::OnOK();
}

BOOL CPublishProject::OnInitDialog()
{
	m_saveCurrentScene = CTrue;
	m_setFirstScene = CFalse;
	CDialog::OnInitDialog();
	availableSceneIndex = -1;
	sceneToBePublishedIndex = -1;

	m_checkBoxSave.SetCheck( BST_CHECKED );
	m_checkBoxDebug.SetCheck(BST_UNCHECKED);
	m_publishDebug = CFalse;
	// Available Scenes
	RECT rect;
	m_listBoxAvailableScenes.GetClientRect(&rect);

	m_listBoxAvailableScenes.InsertColumn(0, "Available Scenes", LVCFMT_LEFT, rect.right - rect.left, 0 );
	for( CUInt i = 0; i < g_VSceneNamesOfCurrentProject.size(); i++ )
	{
		CChar sceneName[MAX_NAME_SIZE];
		Cpy( sceneName, g_VSceneNamesOfCurrentProject[i].c_str() );
		InserItemToAvailableScenesList( sceneName );
	}

	//scenes to be published
	m_listBoxScenesToBePublished.GetClientRect(&rect);
	m_listBoxScenesToBePublished.InsertColumn(0, "Scenes To Be Published", LVCFMT_LEFT, rect.right - rect.left, 0 );
	m_editBoxSplash.SetWindowTextA("Assets/Engine/Textures/Logo_Init.bmp");
	m_strSplash = "Assets/Engine/Textures/Logo_Init.bmp";
	m_editBoxIcon.SetWindowTextA("Assets/Engine/Textures/small.ico");
	m_strIcon = "Assets/Engine/Textures/small.ico";
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

CVoid CPublishProject::InserItemToAvailableScenesList( char * objectName )
{
	availableSceneIndex++;
	LVITEM lvItem;
	lvItem.mask = LVIF_TEXT;
	lvItem.iItem = availableSceneIndex;
	lvItem.iSubItem = 0;
	lvItem.pszText = objectName;
	m_listBoxAvailableScenes.InsertItem(&lvItem);
	m_listBoxAvailableScenes.SetExtendedStyle( LVS_EX_INFOTIP | LVS_EX_ONECLICKACTIVATE | LVS_EX_LABELTIP | LVS_EX_GRIDLINES  );
	//m_listBoxAvailableScenes.SetItemState(availableSceneIndex, LVIS_SELECTED, LVIS_SELECTED | LVIS_FOCUSED );
	m_listBoxAvailableScenes.EnsureVisible(0, FALSE);
}

CVoid CPublishProject::InserItemToScenesToBePublishedList( char * objectName )
{
	sceneToBePublishedIndex++;
	LVITEM lvItem;
	lvItem.mask = LVIF_TEXT;
	lvItem.iItem = sceneToBePublishedIndex;
	lvItem.iSubItem = 0;
	lvItem.pszText = objectName;
	m_listBoxScenesToBePublished.InsertItem(&lvItem);
	m_listBoxScenesToBePublished.SetExtendedStyle( LVS_EX_INFOTIP | LVS_EX_ONECLICKACTIVATE | LVS_EX_LABELTIP | LVS_EX_GRIDLINES  );
	//m_listBoxScenesToBePublished.SetItemState(sceneToBePublishedIndex, LVIS_SELECTED, LVIS_SELECTED | LVIS_FOCUSED );
	m_listBoxScenesToBePublished.EnsureVisible(0, FALSE);
}

void CPublishProject::OnEnChangeEditName()
{
	m_editBoxName.GetWindowTextA( m_strName );
}

void CPublishProject::OnBnClickedBtnSplashImage()
{
	CInt result;
	CFileDialog dlgOpen(TRUE, _T("*.bmp"), _T(""), OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR,
		_T("BMP File (*.bmp)|*.bmp||"), NULL, NULL);
	result = dlgOpen.DoModal();
	if( result == IDOK )
	{
		m_strSplash = (CString)dlgOpen.GetPathName();
		m_editBoxSplash.SetWindowTextA( m_strSplash );
	}
}

void CPublishProject::OnBnClickedAdd()
{
	int nSelected = -1; 
	POSITION p = m_listBoxAvailableScenes.GetFirstSelectedItemPosition();
	while(p)
	{
		nSelected = m_listBoxAvailableScenes.GetNextSelectedItem(p);
	}
	if( nSelected >= 0 )
	{
		TCHAR szBuffer[1024];
		DWORD cchBuf(1024);
		LVITEM lvi;
		lvi.iItem = nSelected;
		lvi.iSubItem = 0;
		lvi.mask = LVIF_TEXT;
		lvi.pszText = szBuffer;
		lvi.cchTextMax = cchBuf;
		m_listBoxAvailableScenes.GetItem(&lvi);

		InserItemToScenesToBePublishedList(lvi.pszText);
		m_listBoxAvailableScenes.DeleteItem(nSelected);
	}
}

void CPublishProject::OnBnClickedRemove()
{
	int nSelected = -1; 
	POSITION p = m_listBoxScenesToBePublished.GetFirstSelectedItemPosition();
	while(p)
	{
		nSelected = m_listBoxScenesToBePublished.GetNextSelectedItem(p);
	}
	if( nSelected >= 0 )
	{
		TCHAR szBuffer[1024];
		DWORD cchBuf(1024);
		LVITEM lvi;
		lvi.iItem = nSelected;
		lvi.iSubItem = 0;
		lvi.mask = LVIF_TEXT;
		lvi.pszText = szBuffer;
		lvi.cchTextMax = cchBuf;
		m_listBoxScenesToBePublished.GetItem(&lvi);

		InserItemToAvailableScenesList(lvi.pszText);
		m_listBoxScenesToBePublished.DeleteItem(nSelected);
	}
}

void CPublishProject::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	OnOK();
}

void CPublishProject::OnBnClickedMarkAsFirstScene()
{
	int nSelected = -1; 
	POSITION p = m_listBoxScenesToBePublished.GetFirstSelectedItemPosition();
	while(p)
	{
		nSelected = m_listBoxScenesToBePublished.GetNextSelectedItem(p);
	}
	if( nSelected >= 0 )
	{
		TCHAR szBuffer[1024];
		DWORD cchBuf(1024);
		LVITEM lvi;
		lvi.iItem = nSelected;
		lvi.iSubItem = 0;
		lvi.mask = LVIF_TEXT;
		lvi.pszText = szBuffer;
		lvi.cchTextMax = cchBuf;
		m_listBoxScenesToBePublished.GetItem(&lvi);
		
		m_setFirstScene = CTrue;
		g_firstSceneNameToBeLoaded = lvi.pszText;
		CChar temp[MAX_NAME_SIZE];
		sprintf( temp, "%s%s", lvi.pszText, " marked as first scene to be loaded" );
		MessageBox( temp, "Report", MB_OK );
	}
	else
	{
		MessageBox( "Please select a scene from the list!", "Report", MB_OK );
	}

}
