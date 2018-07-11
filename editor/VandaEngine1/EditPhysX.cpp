// EditPhysX.cpp : implementation file
//

#include "stdafx.h"
#include "VandaEngine1.h"
#include "EditPhysX.h"
#include "afxdialogex.h"


// CEditPhysX dialog

IMPLEMENT_DYNAMIC(CEditPhysX, CDialog)

CEditPhysX::CEditPhysX(CWnd* pParent /*=NULL*/)
	: CDialog(CEditPhysX::IDD, pParent)
{

}

CEditPhysX::~CEditPhysX()
{
}

void CEditPhysX::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BTN_PHYSX, m_btnGeneratePhysX);
	DDX_Control(pDX, IDC_BTN_DELETE_PHYSX, m_btnRemovePhysX);
	DDX_Control(pDX, IDC_COMBO_PHYSX, m_comboPhysX);
	DDX_Control(pDX, IDC_EDIT_PHYSX, m_editBoxPhysX);
	DDX_Control(pDX, IDC_CHECK_TRIGGER, m_checkBoxTrigger);
	DDX_Control(pDX, IDC_EDIT_PHYSX_PERCENTAGE, m_physXPercentage);
	DDX_Control(pDX, IDC_EDIT_PHYSX_DENSITY, m_physXDensity);
	DDX_Control(pDX, IDC_CHECK_INVISIBLE, m_checkBoxInvisible);
}


BEGIN_MESSAGE_MAP(CEditPhysX, CDialog)
	ON_BN_CLICKED(IDC_BTN_PHYSX, &CEditPhysX::OnBnClickedBtnPhysx)
	ON_BN_CLICKED(IDC_BTN_DELETE_PHYSX, &CEditPhysX::OnBnClickedBtnDeletePhysx)
	ON_CBN_SELCHANGE(IDC_COMBO_PHYSX, &CEditPhysX::OnCbnSelchangeComboPhysx)
	ON_EN_CHANGE(IDC_EDIT_PHYSX_PERCENTAGE, &CEditPhysX::OnEnChangeEditPhysxPercentage)
	ON_EN_CHANGE(IDC_EDIT_PHYSX_DENSITY, &CEditPhysX::OnEnChangeEditPhysxDensity)
END_MESSAGE_MAP()


// CEditPhysX message handlers

CVoid CEditPhysX::SetPhysX( CInstanceGeometry* instanceGeo )
{
	if( instanceGeo )
	{
		m_strPhysX = instanceGeo->m_physXName;
		m_fDensity = instanceGeo->m_physXDensity;
		m_strDensity.Format( "%f",m_fDensity );

		m_iPercentage = instanceGeo->m_physXPercentage;
		m_strPercentage.Format( "%d", m_iPercentage );

		m_instanceGeometry = instanceGeo;
	}
	else
	{
		m_strPhysX = "\n";
		m_instanceGeometry = NULL;
	}

	if( Cmp((LPCTSTR)m_strPhysX, "\n" ) )
	{
		m_removePhysXBtnState = CFalse;
		m_physXBtnState = CTrue;
	}
	else
	{
		m_physXBtnState = CFalse;
		m_removePhysXBtnState = CTrue;
	}
}

void CEditPhysX::OnBnClickedBtnPhysx()
{
	if( g_multipleView->m_nx->m_hasScene )
	{
		MessageBox( "PhysX generation does not work with external PhysX scenes.\nPlease remove the external PhysX scene and try again.", "Vanda Engine Error", MB_OK | MB_ICONERROR );
		return;
	}
	if( !g_menu.m_geometryBasedSelection )
	{
		MessageBox( "PhysX generation only works in 'geometry based selection'", "Vanda Engine Error", MB_OK | MB_ICONERROR );
		return;
	}
	CInt curSel = m_comboPhysX.GetCurSel();
	CPhysXAlgorithm algorithm;
	switch( curSel )
	{
		case 0:
			algorithm = eLOD_CONVEX_HULL;
			break;
		case 1:
			algorithm = eLOD_LENGTH;
			break;
		case 2:
			algorithm = eLOD_LENGTH_CURVATURE;
			break;
		case 3:
			algorithm = eLOD_BOX;
			break;
		case 4:
			algorithm = eLOD_SPHERE;
			break;
		case 5:
			algorithm = eLOD_CAPSULE_METHOD1;
			break;
		case 6:
			algorithm = eLOD_CAPSULE_METHOD2;
			break;
		case 7:
			algorithm = eLOD_CAPSULE_METHOD3;
		default:
			break;
	}

	m_physXDensity.GetWindowTextA( m_strDensity );
	m_fDensity = atof( m_strDensity );
	if( m_fDensity < 0.0f )
		m_fDensity = 0.0f;
	if( m_fDensity > 0 && m_instanceGeometry && m_instanceGeometry->m_abstractGeometry->m_hasAnimation  ) 
	{
		MessageBoxA( "You can't assign a dynamic actor to an animated instanced geometry. Please set density to 0 and try again.", "Vanda Engine Error", MB_OK | MB_ICONERROR );
		return;
	}
	if( (algorithm == eLOD_LENGTH || algorithm == eLOD_LENGTH_CURVATURE ) && m_instanceGeometry && m_instanceGeometry->m_abstractGeometry->m_hasAnimation )
	{
		MessageBoxA( "You can't assign a triangulated PhysX shape to an animated instanced geometry. Please choose another shape and try again.", "Vanda Engine Error", MB_OK | MB_ICONERROR );
		return;

	}
	CInt isTrigger;
	isTrigger = m_checkBoxTrigger.GetCheck();

	if( isTrigger && m_instanceGeometry && m_instanceGeometry->m_abstractGeometry->m_hasAnimation)
	{
		MessageBoxA( "You can't assign a trigger to an animated instanced geometry or skin. Please uncheck trigger checkbox and try again.", "Vanda Engine Error", MB_OK | MB_ICONERROR );
		return;
	}
	if( isTrigger && m_fDensity)
	{
		MessageBoxA( "You can't create a dynamic trigger. Please set denistity to 0 or uncheck trigger checkbox.", "Vanda Engine Error", MB_OK | MB_ICONERROR );
		return;
	}

	m_physXPercentage.GetWindowTextA( m_strPercentage );
	m_iPercentage = (CInt)atof( m_strPercentage );
	if( m_iPercentage <= 0 )
		m_iPercentage = 1;
	else if( m_iPercentage > 100 )
		m_iPercentage = 100;

	CInt index = -1;
	CBool m_bIsTrigger;
	if( isTrigger )
		m_bIsTrigger = CTrue;
	else
		m_bIsTrigger = CFalse;

	CInt isInvisible;
	CBool m_bInvisible;
	isInvisible = m_checkBoxInvisible.GetCheck();

	if( isInvisible == BST_CHECKED )
		m_bInvisible = CTrue;
	else
		m_bInvisible = CFalse;


	for( CUInt i = 0; i < g_scene.size(); i++ )
	{
		index = g_scene[i]->GeneratePhysX(algorithm, m_fDensity, m_iPercentage, m_bIsTrigger, m_bInvisible);
		if( index != -1 )
			break;
	}
	//if( m_bIsTrigger )
	//{
	//	ex_pBtnScriptEditor->EnableWindow( TRUE );
	//	ex_pMenu->EnableMenuItem( ID_TOOLS_SCRIPTMANAGER, MF_ENABLED );
	//	ex_pAddScript->SetInstanceGeo(m_instanceGeometry);
	//}

	if( index != -1 )
	{
		if( !g_physXProperties.m_bDebugMode )
		{
			g_physXProperties.m_bDebugMode = CTrue;

			ex_pMenu->CheckMenuItem( ID_PHYSICS_DEBUGMODE, MF_CHECKED );
			PrintInfo( "\nPhysX Debug mode enabled" );
		}
		PrintInfo( "\nNew PhysX mesh generated successfully");
	
		CString nameIndex;
		nameIndex.Format( "%d", index );
		m_btnRemovePhysX.EnableWindow( TRUE );
		m_btnGeneratePhysX.EnableWindow( FALSE );
		if( m_instanceGeometry )
			m_strPhysX = m_instanceGeometry->m_physXName;
		m_editBoxPhysX.SetWindowTextA( m_strPhysX );
		if( m_instanceGeometry &&  (m_fDensity > 0 || m_instanceGeometry->m_abstractGeometry->m_hasAnimation))
			ex_pVandaEngine1Dlg->InsertItemToPhysXList( m_instanceGeometry->m_physXName, ePHYSXELEMENTLIST_DYNAMIC_RIGIDBODY );
		else if( m_instanceGeometry && m_bIsTrigger )
			ex_pVandaEngine1Dlg->InsertItemToPhysXList( m_instanceGeometry->m_physXName, ePHYSXELEMENTLIST_TRIGGER );
		else if( m_instanceGeometry )
			ex_pVandaEngine1Dlg->InsertItemToPhysXList( m_instanceGeometry->m_physXName, ePHYSXELEMENTLIST_STATIC_RIGIDBODY );
		g_updateOctree = CTrue;

	}
	else
	{
		PrintInfo( "\nFailed to generate the PhysX actor", COLOR_RED);
		m_editBoxPhysX.SetWindowTextA( NULL );
		//m_btnRemovePhysX.EnableWindow( FALSE );
	}
	g_multipleView->m_nx->gControllers->reportSceneChanged();
	gPhysXscene->simulate(1.0f/60.0f/*elapsedTime*/);
	gPhysXscene->flushStream();
	gPhysXscene->fetchResults(NX_ALL_FINISHED, true);

	g_multipleView->SetElapsedTimeFromBeginning();
	g_multipleView->RenderWindow();
	g_multipleView->RenderWindow();
}


void CEditPhysX::OnBnClickedBtnDeletePhysx()
{
	if( g_multipleView->m_nx->m_hasScene )
	{
		MessageBox( "PhysX generation does not work with external PhysX scenes.\nPlease remove the external PhysX scene and try again.", "Vanda Engine Error", MB_OK | MB_ICONERROR );
		return;
	}

	if( !g_menu.m_geometryBasedSelection )
	{
		MessageBox( "PhysX generation only works in 'geometry based selection'", "Vanda Engine Error", MB_OK | MB_ICONERROR );
		return;
	}
	RemovePhysXMesh();
	//ex_pBtnScriptEditor->EnableWindow( FALSE );
	ex_pMenu->EnableMenuItem( ID_TOOLS_SCRIPTMANAGER, MF_DISABLED | MF_GRAYED );
	ex_pAddScript->SetInstanceGeo(NULL);

	g_updateOctree = CTrue;
	g_multipleView->RenderWindow();
}




BOOL CEditPhysX::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_editBoxPhysX.SetWindowTextA( m_strPhysX );
	m_btnGeneratePhysX.EnableWindow( m_physXBtnState );
	m_btnRemovePhysX.EnableWindow( m_removePhysXBtnState );

	m_comboPhysX.InsertString( 0, "Convex Hull" );
	m_comboPhysX.InsertString(	 1, "Triangulate: Length" );
	m_comboPhysX.InsertString( 2, "Triangulate: Length * Curvature" );
	m_comboPhysX.InsertString( 3, "Box" );
	m_comboPhysX.InsertString( 4, "Sphere" );
	m_comboPhysX.InsertString( 5, "Capsule: Method 1" );
	m_comboPhysX.InsertString( 6, "Capsule: Method 2" );
	m_comboPhysX.InsertString( 7, "Capsule: Method 3" );

	if( m_instanceGeometry && m_instanceGeometry->m_lodAlgorithm != eLOD_NONE )
		m_comboPhysX.SetCurSel(m_instanceGeometry->m_lodAlgorithm);
	else
		m_comboPhysX.SetCurSel(0);

	if( m_instanceGeometry && (m_instanceGeometry->m_lodAlgorithm == eLOD_LENGTH_CURVATURE ||  m_instanceGeometry->m_lodAlgorithm == eLOD_LENGTH))
		m_physXPercentage.EnableWindow( TRUE );
	else
		m_physXPercentage.EnableWindow( FALSE );

	if( m_instanceGeometry && m_instanceGeometry->m_isTrigger )
		m_checkBoxTrigger.SetCheck( BST_CHECKED );
	else
		m_checkBoxTrigger.SetCheck( BST_UNCHECKED );

	if( m_instanceGeometry && m_instanceGeometry->m_isInvisible )
		m_checkBoxInvisible.SetCheck( BST_CHECKED );
	else
		m_checkBoxInvisible.SetCheck( BST_UNCHECKED );

	m_physXPercentage.SetWindowTextA( m_strPercentage );
	m_physXDensity.SetWindowTextA( m_strDensity );

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

CVoid CEditPhysX::RemovePhysXMesh()
{
	CBool found = CFalse;
	for( CUInt i = 0; i < g_scene.size(); i++ )
	{
		for (int nItem = ex_pVandaEngine1Dlg->m_listBoxPhysXElements.GetItemCount()-1; nItem >= 0 ;nItem-- )
		{
			TCHAR szBuffer[1024];
			DWORD cchBuf(1024);
			LVITEM lvi;
			lvi.iItem = nItem;
			lvi.iSubItem = 0;
			lvi.mask = LVIF_TEXT;
			lvi.pszText = szBuffer;
			lvi.cchTextMax = cchBuf;

			ex_pVandaEngine1Dlg->m_listBoxPhysXElements.GetItem(&lvi);
			if( m_instanceGeometry && Cmp( szBuffer, m_instanceGeometry->m_physXName ) )
			{
				ex_pVandaEngine1Dlg->m_listBoxPhysXElements.DeleteItem(nItem);
				ex_pVandaEngine1Dlg->SortPhysXList();
				break;
			}
		}

		found = g_scene[i]->RemovePhysX();
		if( found )
			break;
	}
	if( found )
	{
		if( m_instanceGeometry->m_isTrigger )
		{
			if( m_instanceGeometry->m_hasEnterScript || m_instanceGeometry->m_hasExitScript )
			{
				for (CUInt index = 0; index < g_allPrefabNames.size(); index++)
				{
					m_instanceGeometry->m_node->GetScene()->IsInPrefabList(g_allPrefabNames[index].c_str(), CFalse, CTrue );
				}
			}
			m_instanceGeometry->m_isTrigger = CFalse;
			m_instanceGeometry->m_hasEnterScript = m_instanceGeometry->m_hasExitScript = CFalse;
			Cpy( m_instanceGeometry->m_enterScript, "\n" );
			Cpy( m_instanceGeometry->m_exitScript, "\n" );
			ex_pAddScript->m_strTriggerEnterScriptName.Empty();
			ex_pAddScript->m_strTriggerExitScriptName.Empty();
		}
		
		m_instanceGeometry->m_isInvisible = CFalse;

		PrintInfo( "\nActor removed successfully" );
		m_btnGeneratePhysX.EnableWindow( TRUE );
		m_btnRemovePhysX.EnableWindow( FALSE );
		m_editBoxPhysX.SetWindowTextA( NULL );
	}
	else
	{
		PrintInfo( "\nFailed to remove the actor" );
	}

	if( g_currentCameraType == eCAMERA_DEFAULT_FREE && gPhysXscene )
	{
	  // Run collision and dynamics for delta time since the last frame
		gPhysXscene->simulate(1.0f/60.0f/*elapsedTime*/);
		gPhysXscene->flushStream();
		gPhysXscene->fetchResults(NX_ALL_FINISHED, true);
	}
}

void CEditPhysX::OnCbnSelchangeComboPhysx()
{
	CInt curSel = m_comboPhysX.GetCurSel();
	if( curSel == eLOD_LENGTH_CURVATURE || curSel == eLOD_LENGTH )
		m_physXPercentage.EnableWindow( TRUE );
	else
		m_physXPercentage.EnableWindow( FALSE );
}

void CEditPhysX::OnEnChangeEditPhysxPercentage()
{
	m_physXPercentage.GetWindowTextA( m_strPercentage );
	m_iPercentage = (CInt)atof( m_strPercentage );
	if( m_iPercentage <= 0 )
		m_iPercentage = 1;
	else if( m_iPercentage > 100 )
		m_iPercentage = 100;
}


void CEditPhysX::OnEnChangeEditPhysxDensity()
{
	m_physXDensity.GetWindowTextA( m_strDensity );
	m_fDensity = atof( m_strDensity );
	if( m_fDensity < 0.0f )
		m_fDensity = 0.0f;
}
