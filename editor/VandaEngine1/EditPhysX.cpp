//Copyright (C) 2023 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

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
	DDX_Control(pDX, IDC_EDIT_PHYSICS_RESTITUTION, m_editPhysicsRestitution);
	DDX_Control(pDX, IDC_EDIT_PHYSICS_STATIC_FRICTION, m_editPhysicsStaticFriction);
	DDX_Control(pDX, IDC_EDIT_PHYSICS_DYNAMIC_FRICTION, m_editPhysicsDynamicFriction);
	DDX_Control(pDX, IDC_EDIT_PHYSICS_SKIN_WIDTH, m_editPhysicsSkinWidth);
	DDX_Control(pDX, IDC_CHECK_HAS_PHYSICS_MATERIAL, m_checkBoxHasPhysicsMaterial);
}


BEGIN_MESSAGE_MAP(CEditPhysX, CDialog)
	ON_BN_CLICKED(IDC_BTN_PHYSX, &CEditPhysX::OnBnClickedBtnPhysx)
	ON_BN_CLICKED(IDC_BTN_DELETE_PHYSX, &CEditPhysX::OnBnClickedBtnDeletePhysx)
	ON_CBN_SELCHANGE(IDC_COMBO_PHYSX, &CEditPhysX::OnCbnSelchangeComboPhysx)
	ON_EN_CHANGE(IDC_EDIT_PHYSX_PERCENTAGE, &CEditPhysX::OnEnChangeEditPhysxPercentage)
	ON_EN_CHANGE(IDC_EDIT_PHYSX_DENSITY, &CEditPhysX::OnEnChangeEditPhysxDensity)
	ON_EN_CHANGE(IDC_EDIT_PHYSX, &CEditPhysX::OnEnChangeEditPhysx)
	ON_BN_CLICKED(IDCANCEL, &CEditPhysX::OnBnClickedCancel)
	ON_EN_CHANGE(IDC_EDIT_PHYSICS_RESTITUTION, &CEditPhysX::OnEnChangeEditPhysicsRestitution)
	ON_EN_CHANGE(IDC_EDIT_PHYSICS_STATIC_FRICTION, &CEditPhysX::OnEnChangeEditPhysicsStaticFriction)
	ON_EN_CHANGE(IDC_EDIT_PHYSICS_SKIN_WIDTH, &CEditPhysX::OnEnChangeEditPhysicsSkinWidth)
	ON_EN_CHANGE(IDC_EDIT_PHYSICS_DYNAMIC_FRICTION, &CEditPhysX::OnEnChangeEditPhysicsDynamicFriction)
	ON_BN_CLICKED(IDC_CHECK_HAS_PHYSICS_MATERIAL, &CEditPhysX::OnBnClickedCheckHasPhysicsMaterial)
	ON_BN_CLICKED(IDOK, &CEditPhysX::OnBnClickedOk)
END_MESSAGE_MAP()


// CEditPhysX message handlers

CVoid CEditPhysX::SetPhysX( CInstanceGeometry* instanceGeo )
{
	if( instanceGeo )
	{
		m_strPhysX = instanceGeo->m_physXName;
		m_fDensity = instanceGeo->m_physXDensity;
		m_strDensity.Format( "%.3f",m_fDensity );

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

	if (m_strDensity.IsEmpty())
	{
		MessageBoxA("Please specify a value for density.", "Vanda Engine Error", MB_OK | MB_ICONERROR);
		return;
	}

	if( m_fDensity > 0 && m_instanceGeometry && m_instanceGeometry->m_abstractGeometry->m_hasAnimation  ) 
	{
		MessageBoxA( "You can't assign a dynamic actor to an animated instanced geometry. Please set density to 0 and try again.", "Vanda Engine Error", MB_OK | MB_ICONERROR );
		return;
	}
	if (m_fDensity > 0 && g_prefabProperties.m_isTransformable)
	{
		MessageBoxA("You can't assign a dynamic actor to a transformable prefab.\nPlease set density to 0 or deactivate IsTransformable in prefab properties dialog.", "Vanda Engine Error", MB_OK | MB_ICONERROR);
		return;
	}
	if( (algorithm == eLOD_LENGTH || algorithm == eLOD_LENGTH_CURVATURE ) && m_instanceGeometry && m_instanceGeometry->m_abstractGeometry->m_hasAnimation )
	{
		MessageBoxA( "You can't assign a triangulated PhysX shape to an animated instanced geometry. Please choose another shape and try again.", "Vanda Engine Error", MB_OK | MB_ICONERROR );
		return;
	}

	if ((algorithm == eLOD_LENGTH || algorithm == eLOD_LENGTH_CURVATURE) && g_prefabProperties.m_isTransformable)
	{
		MessageBoxA("You can't assign a triangulated PhysX shape to a transformable prefab.\nPlease choose another shape or deactivate IsTransformable in prefab properties dialog.", "Vanda Engine Error", MB_OK | MB_ICONERROR);
		return;
	}

	CInt isTrigger;
	isTrigger = m_checkBoxTrigger.GetCheck();

	if( isTrigger && m_fDensity)
	{
		MessageBoxA( "You can't create a dynamic trigger. Please set density to 0 or uncheck trigger checkbox.", "Vanda Engine Error", MB_OK | MB_ICONERROR );
		return;
	}

	if (m_fDensity > 0)
	{
		for (CUInt i = 0; i < g_scene.size(); i++)
		{
			for (CUInt j = 0; j < g_scene[i]->m_instanceGeometries.size(); j++)
			{
				if (g_selectedName != g_scene[i]->m_instanceGeometries[j]->m_nameIndex)
				{
					if (Cmp(g_scene[i]->m_instanceGeometries[j]->m_abstractGeometry->GetName(), m_instanceGeometry->m_abstractGeometry->GetName()))
					{
						if (g_scene[i]->m_instanceGeometries[j]->m_physXDensity > 0.0f)
						{
							MessageBox("You can't create dynamic physics colliders for more than 1 LOD of the same geometry instance", "Vanda Engine Error", MB_OK);
							return;
						}
					}
				}
			}
		}
	}
	

	CInt checkMaterialState;
	CBool m_bHasPhysicsMaterial = CFalse;
	checkMaterialState = m_checkBoxHasPhysicsMaterial.GetCheck();
	if (checkMaterialState == BST_CHECKED)
		m_bHasPhysicsMaterial = CTrue;

	if (m_bHasPhysicsMaterial)
	{
		if (m_strPhysicsRestitution.IsEmpty())
		{
			MessageBox("Please specify a value for restitution", "Vanda Engine Error", MB_OK | MB_ICONERROR);
			return;
		}
		if (m_strPhysicsStaticFriction.IsEmpty())
		{
			MessageBox("Please specify a value for static friction", "Vanda Engine Error", MB_OK | MB_ICONERROR);
			return;
		}
		if (m_strPhysicsSkinWidth.IsEmpty())
		{
			MessageBox("Please specify a value for skin width", "Vanda Engine Error", MB_OK | MB_ICONERROR);
			return;
		}
		if (m_strPhysicsDynamicFriction.IsEmpty())
		{
			MessageBox("Please specify a value for dynamic friction", "Vanda Engine Error", MB_OK | MB_ICONERROR);
			return;
		}
		if (m_fPhysicsRestitution < 0.0f || m_fPhysicsRestitution > 1.0f)
		{
			MessageBox("restitution must be between 0 and 1", "Vanda Engine Error", MB_OK | MB_ICONERROR);
			return;
		}
		if (m_fPhysicsStaticFriction < 0.0)
		{
			MessageBox("static friction must be between 0 or higher", "Vanda Engine Error", MB_OK | MB_ICONERROR);
			return;
		}
		if (m_fPhysicsDynamicFriction < 0.0)
		{
			MessageBox("dynamic friction must be between 0 or higher", "Vanda Engine Error", MB_OK | MB_ICONERROR);
			return;
		}
		if (m_fPhysicsSkinWidth <= 0.0f)
		{
			MessageBox("skin width must be greater than 0", "Vanda Engine Error", MB_OK | MB_ICONERROR);
			return;
		}
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


	for (CUInt i = 0; i < g_scene.size(); i++)
	{
		CPhysXMaterial physicsMaterial;
		physicsMaterial.HasMaterial = m_bHasPhysicsMaterial;
		physicsMaterial.Restitution = m_fPhysicsRestitution;
		physicsMaterial.SkinWidth = m_fPhysicsSkinWidth;
		physicsMaterial.StaticFriction = m_fPhysicsStaticFriction;
		physicsMaterial.DynamicFriction = m_fPhysicsDynamicFriction;

		index = g_scene[i]->GeneratePhysX(algorithm, m_fDensity, m_iPercentage, m_bIsTrigger, m_bInvisible, physicsMaterial);

		if (index != -1)
			break;
	}
	if (index == -1 && m_fDensity > 0.0f && g_scene.size() > 1)
	{
		MessageBoxA("We don't support dynamic PhysX actor for LOD 2 or LOD 3. Please remove LOD 2 and LOD 3 and try again", "Vanda Engine Error", MB_OK | MB_ICONERROR);
	}

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

	if (m_instanceGeometry)
	{
		init_strPhysX = m_instanceGeometry->m_physXName;
		init_algorithm = m_instanceGeometry->m_lodAlgorithm;
		init_density = m_instanceGeometry->m_physXDensity;
		init_percentage = m_instanceGeometry->m_physXPercentage;
		init_trigger = m_instanceGeometry->m_isTrigger;
		init_invisible = m_instanceGeometry->m_isInvisible;

		init_hasPhysicsMaterial = m_instanceGeometry->HasPhysicsMaterial();
		init_physicsRestitution = m_instanceGeometry->GetPhysicsRestitution();
		init_physicsStaticFriction = m_instanceGeometry->GetPhysicsStaticFriction();
		init_physicsDynamicFriction = m_instanceGeometry->GetPhysicsDynamicFriction();
		init_physicsSkinWidth = m_instanceGeometry->GetPhysicsSkinWidth();
	}

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

	//material
	if (m_instanceGeometry && m_instanceGeometry->HasPhysicsMaterial())
	{
		m_checkBoxHasPhysicsMaterial.SetCheck(BST_CHECKED);
		m_editPhysicsRestitution.EnableWindow();
		m_editPhysicsStaticFriction.EnableWindow();
		m_editPhysicsDynamicFriction.EnableWindow();
		m_editPhysicsSkinWidth.EnableWindow();

		m_strPhysicsRestitution.Format("%.2f", m_instanceGeometry->GetPhysicsRestitution());
		m_strPhysicsStaticFriction.Format("%.2f", m_instanceGeometry->GetPhysicsStaticFriction());
		m_strPhysicsDynamicFriction.Format("%.2f", m_instanceGeometry->GetPhysicsDynamicFriction());
		m_strPhysicsSkinWidth.Format("%.2f", m_instanceGeometry->GetPhysicsSkinWidth());

		m_fPhysicsRestitution = atof(m_strPhysicsRestitution);
		m_fPhysicsStaticFriction = atof(m_strPhysicsStaticFriction);
		m_fPhysicsDynamicFriction = atof(m_strPhysicsDynamicFriction);
		m_fPhysicsSkinWidth = atof(m_strPhysicsSkinWidth);

		m_editPhysicsRestitution.SetWindowTextA(m_strPhysicsRestitution);
		m_editPhysicsStaticFriction.SetWindowTextA(m_strPhysicsStaticFriction);
		m_editPhysicsDynamicFriction.SetWindowTextA(m_strPhysicsDynamicFriction);
		m_editPhysicsSkinWidth.SetWindowTextA(m_strPhysicsSkinWidth);
	}
	else
	{
		m_checkBoxHasPhysicsMaterial.SetCheck(BST_UNCHECKED);
		m_editPhysicsRestitution.EnableWindow(FALSE);
		m_editPhysicsStaticFriction.EnableWindow(FALSE);
		m_editPhysicsDynamicFriction.EnableWindow(FALSE);
		m_editPhysicsSkinWidth.EnableWindow(FALSE);

		m_editPhysicsRestitution.SetWindowTextA("");
		m_editPhysicsStaticFriction.SetWindowTextA("");
		m_editPhysicsDynamicFriction.SetWindowTextA("");
		m_editPhysicsSkinWidth.SetWindowTextA("");

	}


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
		PrintInfo( "\nActor removed successfully" );
		m_btnGeneratePhysX.EnableWindow( TRUE );
		m_btnRemovePhysX.EnableWindow( FALSE );
		m_editBoxPhysX.SetWindowTextA( NULL );
	}
	else
	{
		PrintInfo( "\nFailed to remove the actor" );
	}

	if( !g_multipleView->IsPlayGameMode() && gPhysXscene )
	{
	  // Run collision and dynamics for delta time since the last frame
		g_multipleView->m_nx->gControllers->reportSceneChanged();
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


void CEditPhysX::OnEnChangeEditPhysx()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}


void CEditPhysX::OnBnClickedCancel()
{
	CInt index = -1;
	if (m_btnRemovePhysX.IsWindowEnabled())
	{
		RemovePhysXMesh();
	}
	if (!Cmp((LPCTSTR)init_strPhysX, "\n"))
	{
		for (CUInt i = 0; i < g_scene.size(); i++)
		{
			CPhysXMaterial physicsMaterial;
			physicsMaterial.HasMaterial = init_hasPhysicsMaterial;
			physicsMaterial.Restitution = init_physicsRestitution;
			physicsMaterial.SkinWidth = init_physicsSkinWidth;
			physicsMaterial.StaticFriction = init_physicsStaticFriction;
			physicsMaterial.DynamicFriction = init_physicsDynamicFriction;

			index = g_scene[i]->GeneratePhysX(init_algorithm, init_density, init_percentage, init_trigger, init_invisible, physicsMaterial);

			if (index != -1)
				break;
		}

		if (m_instanceGeometry && (init_density > 0 || m_instanceGeometry->m_abstractGeometry->m_hasAnimation))
			ex_pVandaEngine1Dlg->InsertItemToPhysXList((CChar*)init_strPhysX.GetBuffer(init_strPhysX.GetLength()), ePHYSXELEMENTLIST_DYNAMIC_RIGIDBODY);
		else if (m_instanceGeometry && init_trigger)
			ex_pVandaEngine1Dlg->InsertItemToPhysXList((CChar*)init_strPhysX.GetBuffer(init_strPhysX.GetLength()), ePHYSXELEMENTLIST_TRIGGER);
		else if (m_instanceGeometry)
			ex_pVandaEngine1Dlg->InsertItemToPhysXList((CChar*)init_strPhysX.GetBuffer(init_strPhysX.GetLength()), ePHYSXELEMENTLIST_STATIC_RIGIDBODY);
	}
	g_updateOctree = CTrue;
	g_multipleView->m_nx->gControllers->reportSceneChanged();
	gPhysXscene->simulate(1.0f / 60.0f/*elapsedTime*/);
	gPhysXscene->flushStream();
	gPhysXscene->fetchResults(NX_ALL_FINISHED, true);
	g_multipleView->RenderWindow();

	CDialog::OnCancel();
}


void CEditPhysX::OnEnChangeEditPhysicsRestitution()
{
	m_editPhysicsRestitution.GetWindowTextA(m_strPhysicsRestitution);
	m_fPhysicsRestitution = atof(m_strPhysicsRestitution);
}


void CEditPhysX::OnEnChangeEditPhysicsStaticFriction()
{
	m_editPhysicsStaticFriction.GetWindowTextA(m_strPhysicsStaticFriction);
	m_fPhysicsStaticFriction = atof(m_strPhysicsStaticFriction);
}


void CEditPhysX::OnEnChangeEditPhysicsSkinWidth()
{
	m_editPhysicsSkinWidth.GetWindowTextA(m_strPhysicsSkinWidth);
	m_fPhysicsSkinWidth = atof(m_strPhysicsSkinWidth);
}


void CEditPhysX::OnEnChangeEditPhysicsDynamicFriction()
{
	m_editPhysicsDynamicFriction.GetWindowTextA(m_strPhysicsDynamicFriction);
	m_fPhysicsDynamicFriction = atof(m_strPhysicsDynamicFriction);
}

void CEditPhysX::OnBnClickedCheckHasPhysicsMaterial()
{
	CInt checkMaterialState;
	CBool hasPhysicsMaterial = CFalse;
	checkMaterialState = m_checkBoxHasPhysicsMaterial.GetCheck();
	if (checkMaterialState == BST_CHECKED)
	{
		m_editPhysicsRestitution.EnableWindow();
		m_editPhysicsStaticFriction.EnableWindow();
		m_editPhysicsDynamicFriction.EnableWindow();
		m_editPhysicsSkinWidth.EnableWindow();
	}
	else
	{
		m_editPhysicsRestitution.EnableWindow(FALSE);
		m_editPhysicsStaticFriction.EnableWindow(FALSE);
		m_editPhysicsDynamicFriction.EnableWindow(FALSE);
		m_editPhysicsSkinWidth.EnableWindow(FALSE);
	}
}


void CEditPhysX::OnBnClickedOk()
{
	CInt isInvisible;
	CBool m_bInvisible;
	isInvisible = m_checkBoxInvisible.GetCheck();

	if (isInvisible == BST_CHECKED)
		m_bInvisible = CTrue;
	else
		m_bInvisible = CFalse;

	m_instanceGeometry->m_isInvisible = m_bInvisible;

	CDialog::OnOK();
}
