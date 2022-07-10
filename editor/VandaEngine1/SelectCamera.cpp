//Copyright (C) 2022 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

// SelectCamera.cpp : implementation file
//

#include "stdafx.h"
#include "VandaEngine1.h"
#include "SelectCamera.h"
#include  "AFXPRIV.H"

// CSelectCamera dialog

IMPLEMENT_DYNAMIC(CSelectCamera, CDialog)

CSelectCamera::CSelectCamera(CWnd* pParent /*=NULL*/)
	: CDialog(CSelectCamera::IDD, pParent)
{

}

CSelectCamera::~CSelectCamera()
{
}

void CSelectCamera::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_SELECT_CAMERA, m_listBoxCameraObjects);
	DDX_Control(pDX, IDC_RICHED_CAMERA_NAME, m_richCameraName);
}


BEGIN_MESSAGE_MAP(CSelectCamera, CDialog)
	ON_BN_CLICKED(IDOK, &CSelectCamera::OnBnClickedOk)
	ON_BN_CLICKED(ID_ACIVATE_AND_RENDER, &CSelectCamera::OnBnClickedAcivateAndRender)
	ON_BN_CLICKED(IDC_BUTTON_COPY_CAMERA_NAME, &CSelectCamera::OnBnClickedButtonCopyCameraName)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_SELECT_CAMERA, &CSelectCamera::OnLvnItemchangedListSelectCamera)
END_MESSAGE_MAP()


// CSelectCamera message handlers


CVoid CSelectCamera::InserItemToCameraList( char * objectName )
{
	cameraObjectIndex++;
	LVITEM lvItem;
	lvItem.mask = LVIF_TEXT;
	lvItem.iItem = cameraObjectIndex;
	lvItem.iSubItem = 0;
	lvItem.pszText = objectName;
	m_listBoxCameraObjects.InsertItem(&lvItem);
	m_listBoxCameraObjects.SetExtendedStyle( LVS_EX_INFOTIP | LVS_EX_ONECLICKACTIVATE | LVS_EX_LABELTIP );
	m_listBoxCameraObjects.SetItemState(cameraObjectIndex, LVIS_SELECTED, LVIS_SELECTED | LVIS_FOCUSED );
	m_listBoxCameraObjects.EnsureVisible(0, FALSE);
}

BOOL CSelectCamera::OnInitDialog()
{
	CDialog::OnInitDialog();
	cameraObjectIndex = -1;
	RECT rect;
	m_listBoxCameraObjects.GetClientRect(&rect);
	m_listBoxCameraObjects.InsertColumn(0, "Camera Names", LVCFMT_LEFT, rect.right - rect.left, 0 );
	//InserItemToCameraList( "*Default PhysX Camera (Play Mode)" );
	//InserItemToCameraList( "*Default Free Camera" );
	for( CUInt i = 0; i < g_importedCameraInstances.size(); i++ )
	{
		InserItemToCameraList( g_importedCameraInstances[i]->m_abstractCamera->GetName() );
	}

	return TRUE;  // return TRUE unless you set the focus to a control
}

void CSelectCamera::OnBnClickedOk()
{
	CInstanceCamera* tempInstanceCamera;

	int nSelected = -1; 
	POSITION p = m_listBoxCameraObjects.GetFirstSelectedItemPosition();
	while(p)
	{
		nSelected = m_listBoxCameraObjects.GetNextSelectedItem(p);
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
		m_listBoxCameraObjects.GetItem(&lvi);

		//if( Cmp( "*Default PhysX Camera (Play Mode)", szBuffer ) )
		//{
		//	for (CUInt c = 0; c < g_engineCameraInstances.size(); c++)
		//	{
		//		g_engineCameraInstances[c]->SetActive(CFalse);
		//	}

		//	ex_pVandaEngine1Dlg->OnBnClickedBtnPlayDeactive();
		//}
		//else if( Cmp( "*Default Free Camera", szBuffer ) )
		//{
		//	for (CUInt c = 0; c < g_engineCameraInstances.size(); c++)
		//	{
		//		g_engineCameraInstances[c]->SetActive(CFalse);
		//	}

		//	ex_pVandaEngine1Dlg->OnBnClickedBtnPlayActive();
		//}
		//else
		//{
			//if (g_multipleView->IsPlayGameMode())
			//	ex_pVandaEngine1Dlg->ResetPhysX(CTrue);

			for( CUInt i = 0; i < g_importedCameraInstances.size(); i++ )
			{
				if( Cmp( g_importedCameraInstances[i]->m_abstractCamera->GetName(), szBuffer ) )
				{
					tempInstanceCamera = g_importedCameraInstances[i];
					g_render.SetActiveInstanceCamera( tempInstanceCamera );
					g_currentCameraType = eCAMERA_COLLADA;
					ex_pVandaEngine1Dlg->m_mainBtnFreeCamera.EnableWindow(TRUE);

					break;
				}
			}
			//for (CUInt i = 0; i < g_scene.size(); i++)
			//{
			//	g_render.SetScene(g_scene[i]);
			//	g_render.GetScene()->Update();
			//}

			//if (g_editorMode == eMODE_PREFAB)
			//{
			//	for (CUInt i = 0; i < g_scene.size(); i++)
			//	{
			//		for (CUInt j = 0; j < g_scene[i]->m_instanceGeometries.size(); j++)
			//		{
			//			if (g_scene[i]->m_instanceGeometries[j]->m_hasPhysX)
			//			{
			//				g_scene[i]->GeneratePhysX(g_scene[i]->m_instanceGeometries[j]->m_lodAlgorithm, g_scene[i]->m_instanceGeometries[j]->m_physXDensity, g_scene[i]->m_instanceGeometries[j]->m_physXPercentage, g_scene[i]->m_instanceGeometries[j]->m_isTrigger, g_scene[i]->m_instanceGeometries[j]->m_isInvisible, g_scene[i]->m_instanceGeometries[j]);
			//			}
			//		}
			//	}
			//}

			//ex_pBtnTestModeActive->ShowWindow(SW_HIDE);
			//ex_pBtnTestModeActive->EnableWindow(FALSE);
			//ex_pBtnTestModeActive->UpdateWindow();
			//ex_pBtnTestModeDeactive->ShowWindow(SW_SHOW);
			//ex_pBtnTestModeDeactive->EnableWindow(TRUE);
			//ex_pBtnTestModeDeactive->UpdateWindow();

			//g_multipleView->m_nx->gControllers->reportSceneChanged();
			//gPhysXscene->simulate(1.0f / 60.0f/*elapsedTime*/);
			//gPhysXscene->flushStream();
			//gPhysXscene->fetchResults(NX_ALL_FINISHED, true);

		//}
	}
	else
	{
		MessageBox("Please select an item from the list!", "ERROR", MB_OK | MB_ICONERROR);
		return;
	}
	OnOK();
}

INT_PTR CSelectCamera::DoModal()
{
	// TODO: Add your specialized code here and/or call the base class
	CDialogTemplate dlt;
	INT_PTR nResult;
	// load dialog template
	if (!dlt.Load(MAKEINTRESOURCE(CSelectCamera::IDD))) return -1;
	// set the font, for example "Arial", 10 pts.
	dlt.SetFont("Arial", 8);
	// get pointer to the modified dialog template
	LPSTR pdata = (LPSTR)GlobalLock(dlt.m_hTemplate);
	// let MFC know that you are using your own template
	m_lpszTemplateName = NULL;
	InitModalIndirect(pdata);
	// display dialog box
	nResult = CDialog::DoModal();
	// unlock memory object
	GlobalUnlock(dlt.m_hTemplate);
	return nResult;
}

void CSelectCamera::OnBnClickedAcivateAndRender()
{
	if( g_vandaDemo )
	{
		MessageBox( "This feature lets you render the scene from the perspective of selected camera.\nIf your selected camera includes animation, Vanda Engine Version 1.x activates its animation and captures a video from the perspective of camera.\nThis feature is not available in RTI demo Edition Version 1.x", "Vanda Engine Error", MB_OK | MB_ICONINFORMATION );
	}
	else
	{
	}
}


void CSelectCamera::OnBnClickedButtonCopyCameraName()
{
	CString s;
	m_richCameraName.GetWindowTextA(s);
	if (s.IsEmpty())
		MessageBox("Please select a camera from the list!", "Error", MB_OK | MB_ICONERROR);
	else
	{
		m_richCameraName.Copy();
		CChar message[MAX_URI_SIZE];
		sprintf(message, "Item '%s' copied to clipboard", (LPCSTR)s);
		MessageBox(message, "Report", MB_OK | MB_ICONINFORMATION);
	}
}


void CSelectCamera::OnLvnItemchangedListSelectCamera(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	int nSelected = -1;
	POSITION p = m_listBoxCameraObjects.GetFirstSelectedItemPosition();
	while (p)
	{
		nSelected = m_listBoxCameraObjects.GetNextSelectedItem(p);
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
		m_listBoxCameraObjects.GetItem(&lvi);

		m_richCameraName.SetWindowTextA(szBuffer);
		CInt end = m_richCameraName.GetWindowTextLengthA();
		m_richCameraName.SetSel(0, end);

	}
	else
	{
		m_richCameraName.SetWindowTextA("");
		m_richCameraName.SetSel(0, 0);
	}

	*pResult = 0;
}
