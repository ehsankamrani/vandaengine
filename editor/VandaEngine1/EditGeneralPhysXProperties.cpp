// EditGeneralPhysXProperties.cpp : implementation file
//

#include "stdafx.h"
#include "VandaEngine1.h"
#include "EditGeneralPhysXProperties.h"
#include "afxdialogex.h"


// CEditGeneralPhysXProperties dialog

IMPLEMENT_DYNAMIC(CEditGeneralPhysXProperties, CDialog)

CEditGeneralPhysXProperties::CEditGeneralPhysXProperties(CWnd* pParent /*=NULL*/)
	: CDialog(CEditGeneralPhysXProperties::IDD, pParent)
	, m_strDefaultRestitution(_T(""))
	, m_strDefaultStaticFriction(_T(""))
	, m_strDefaultSkinWidth(_T(""))
	, m_strDefaultDynamicFriction(_T(""))
	, m_strGravityX(_T(""))
	, m_strGravityY(_T(""))
	, m_strGravityZ(_T(""))
	, m_strCameraCharacterDistance(_T(""))
	, m_strCapsuleRadius(_T(""))
	, m_strCapsuleHeight(_T(""))
	, m_strCharacterPower(_T(""))
	, m_strJumpPower(_T(""))
	, m_strCharacterSpeed(_T(""))
{

}

CEditGeneralPhysXProperties::~CEditGeneralPhysXProperties()
{
}

void CEditGeneralPhysXProperties::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_DEFAULT_RESTITUTION, m_editBoxRestitution);
	DDX_Control(pDX, IDC_EDIT_DEFAULT_STATIC_FRICTION, m_editBoxStaticFriction);
	DDX_Control(pDX, IDC_EDIT_DEFAULT_DYNAMIC_FRICTION, m_editBoxDynamicFriction);
	DDX_Control(pDX, IDC_EDIT_DEFAULT_SKIN_WIDTH, m_editBoxSkinWidth);
	DDX_Control(pDX, IDC_CHECK_DEBUG_MODE, m_checkBoxDebugMode);
	DDX_Control(pDX, IDC_CHECK_APPLY_GRAVITY, m_checkBoxApplyGravity);
	DDX_Control(pDX, IDC_EDIT_GRAVITY_X, m_editBoxGravityX);
	DDX_Control(pDX, IDC_EDIT_GRAVITY_Y, m_editBoxGravityY);
	DDX_Control(pDX, IDC_EDIT_GRAVITY_Z, m_editBoxGravityZ);
	DDX_Control(pDX, IDC_EDIT_CAMERA_CHARACTER_DISTANCE, m_editBoxCameraCharacterDistance);
	DDX_Control(pDX, IDC_CHECK_JUMP, m_checkBoxJumping);
	DDX_Control(pDX, IDC_EDIT_CHARACTER_RADIUS, m_editBoxCapsuleRadius);
	DDX_Control(pDX, IDC_EDIT_CHARACTER_HEIGHT, m_editBoxCapsuleHeight);
	DDX_Control(pDX, IDC_EDIT_CHARACTER_POWER, m_editBoxCharacterPower);
	DDX_Control(pDX, IDC_EDIT_CHARACTER_JUMP_POWER, m_editBoxJumpPower);
	DDX_Control(pDX, IDC_EDIT_CHARACTER_SPEED, m_editBoxCharacterSpeed);
	DDX_Control(pDX, IDC_EDIT_CHARACTER_SKIN_WIDTH, m_editBoxCharacterSkinWidth);
	DDX_Control(pDX, IDC_EDIT_CHARACTER_STEP_OFFSET, m_editBoxCharacterStepOffset);
	DDX_Control(pDX, IDC_EDIT_CHARACTER_SLOPE_LIMIT, m_editBoxCharacterSlopeLimit);
	DDX_Control(pDX, IDC_CHECK_GROUND_PLANE, m_checkBoxGroundPlane);
	DDX_Control(pDX, IDC_EDIT_GROUND_HEIGHT, m_editBoxGroundHeight);
}


BEGIN_MESSAGE_MAP(CEditGeneralPhysXProperties, CDialog)
	ON_EN_CHANGE(IDC_EDIT_DEFAULT_RESTITUTION, &CEditGeneralPhysXProperties::OnEnChangeEditDefaultRestitution)
	ON_EN_CHANGE(IDC_EDIT_DEFAULT_STATIC_FRICTION, &CEditGeneralPhysXProperties::OnEnChangeEditDefaultStaticFriction)
	ON_EN_CHANGE(IDC_EDIT_DEFAULT_SKIN_WIDTH, &CEditGeneralPhysXProperties::OnEnChangeEditDefaultSkinWidth)
	ON_EN_CHANGE(IDC_EDIT_DEFAULT_DYNAMIC_FRICTION, &CEditGeneralPhysXProperties::OnEnChangeEditDefaultDynamicFriction)
	ON_EN_CHANGE(IDC_EDIT_GRAVITY_X, &CEditGeneralPhysXProperties::OnEnChangeEditGravityX)
	ON_EN_CHANGE(IDC_EDIT_GRAVITY_Y, &CEditGeneralPhysXProperties::OnEnChangeEditGravityY)
	ON_EN_CHANGE(IDC_EDIT_GRAVITY_Z, &CEditGeneralPhysXProperties::OnEnChangeEditGravityZ)
	ON_EN_CHANGE(IDC_EDIT_CAMERA_CHARACTER_DISTANCE, &CEditGeneralPhysXProperties::OnEnChangeEditCameraCharacterDistance)
	ON_EN_CHANGE(IDC_EDIT_CHARACTER_RADIUS, &CEditGeneralPhysXProperties::OnEnChangeEditCharacterRadius)
	ON_EN_CHANGE(IDC_EDIT_CHARACTER_HEIGHT, &CEditGeneralPhysXProperties::OnEnChangeEditCharacterHeight)
	ON_EN_CHANGE(IDC_EDIT_CHARACTER_POWER, &CEditGeneralPhysXProperties::OnEnChangeEditCharacterPower)
	ON_EN_CHANGE(IDC_EDIT_CHARACTER_JUMP_POWER, &CEditGeneralPhysXProperties::OnEnChangeEditCharacterJumpPower)
	ON_EN_CHANGE(IDC_EDIT_CHARACTER_SPEED, &CEditGeneralPhysXProperties::OnEnChangeEditCharacterSpeed)
	ON_EN_CHANGE(IDC_EDIT_CHARACTER_SKIN_WIDTH, &CEditGeneralPhysXProperties::OnEnChangeEditCharacterSkinWidth)
	ON_EN_CHANGE(IDC_EDIT_CHARACTER_STEP_OFFSET, &CEditGeneralPhysXProperties::OnEnChangeEditCharacterStepOffset)
	ON_EN_CHANGE(IDC_EDIT_CHARACTER_SLOPE_LIMIT, &CEditGeneralPhysXProperties::OnEnChangeEditCharacterSlopeLimit)
	ON_EN_CHANGE(IDC_EDIT_GROUND_HEIGHT, &CEditGeneralPhysXProperties::OnEnChangeEditGroundHeight)
	ON_BN_CLICKED(IDC_BUTTON_RESET, &CEditGeneralPhysXProperties::OnBnClickedButtonReset)
END_MESSAGE_MAP()


// CEditGeneralPhysXProperties message handlers


void CEditGeneralPhysXProperties::OnEnChangeEditDefaultRestitution()
{
	m_editBoxRestitution.GetWindowTextA( m_strDefaultRestitution );
	m_fDefaultRestitution = atof( m_strDefaultRestitution );

}


void CEditGeneralPhysXProperties::OnEnChangeEditDefaultStaticFriction()
{
	m_editBoxStaticFriction.GetWindowTextA( m_strDefaultStaticFriction );
	m_fDefaultStaticFriction = atof( m_strDefaultStaticFriction );
}


void CEditGeneralPhysXProperties::OnEnChangeEditDefaultSkinWidth()
{
	m_editBoxSkinWidth.GetWindowTextA( m_strDefaultSkinWidth );
	m_fDefaultSkinWidth = atof( m_strDefaultSkinWidth );
}


void CEditGeneralPhysXProperties::OnEnChangeEditDefaultDynamicFriction()
{
	m_editBoxDynamicFriction.GetWindowTextA( m_strDefaultDynamicFriction );
	m_fDefaultDynamicFriction = atof( m_strDefaultDynamicFriction );
}


void CEditGeneralPhysXProperties::OnEnChangeEditGravityX()
{
	m_editBoxGravityX.GetWindowTextA( m_strGravityX );
	m_fGravityX = atof( m_strGravityX );
}


void CEditGeneralPhysXProperties::OnEnChangeEditGravityY()
{
	m_editBoxGravityY.GetWindowTextA( m_strGravityY );
	m_fGravityY = atof( m_strGravityY );
}


void CEditGeneralPhysXProperties::OnEnChangeEditGravityZ()
{
	m_editBoxGravityZ.GetWindowTextA( m_strGravityZ );
	m_fGravityZ = atof( m_strGravityZ );
}


void CEditGeneralPhysXProperties::OnEnChangeEditCameraCharacterDistance()
{
	m_editBoxCameraCharacterDistance.GetWindowTextA( m_strCameraCharacterDistance );
	m_fCameraCharacterDistance = atof( m_strCameraCharacterDistance );
}


void CEditGeneralPhysXProperties::OnEnChangeEditCharacterRadius()
{
	m_editBoxCapsuleRadius.GetWindowTextA( m_strCapsuleRadius );
	m_fCapsuleRadius = atof( m_strCapsuleRadius );
}


void CEditGeneralPhysXProperties::OnEnChangeEditCharacterHeight()
{
	m_editBoxCapsuleHeight.GetWindowTextA( m_strCapsuleHeight );
	m_fCapsuleHeight = atof( m_strCapsuleHeight );
}

void CEditGeneralPhysXProperties::OnEnChangeEditCharacterJumpPower()
{
	m_editBoxJumpPower.GetWindowTextA( m_strJumpPower );
	m_fJumpPower = atof( m_strJumpPower );
}


void CEditGeneralPhysXProperties::OnEnChangeEditCharacterSpeed()
{
	m_editBoxCharacterSpeed.GetWindowTextA( m_strCharacterSpeed );
	m_fCharacterWalkSpeed = atof( m_strCharacterSpeed );
}

void CEditGeneralPhysXProperties::OnEnChangeEditCharacterPower()
{
	m_editBoxCharacterPower.GetWindowTextA( m_strCharacterPower );
	m_fCharacterPower = atof( m_strCharacterPower );
}

void CEditGeneralPhysXProperties::OnOK()
{
	if( m_strDefaultRestitution.IsEmpty() || m_strDefaultStaticFriction.IsEmpty() || m_strDefaultSkinWidth.IsEmpty() ||
		m_strDefaultDynamicFriction.IsEmpty() || m_strGravityX.IsEmpty() || m_strGravityY.IsEmpty() || m_strGravityZ.IsEmpty() ||
		m_strCameraCharacterDistance.IsEmpty() || m_strCapsuleRadius.IsEmpty() || m_strCapsuleHeight.IsEmpty() || 
		m_strCharacterPower.IsEmpty() || m_strCharacterSpeed.IsEmpty() || m_strJumpPower.IsEmpty() || m_strCharacterSkinWidth.IsEmpty() ||
		m_strCharacterSlopeLimit.IsEmpty() || m_strCharacterStepOffset.IsEmpty() || m_strGroundHeight.IsEmpty())
	{
		MessageBox( "Please enter valid data for all of the required fields", "Vanda Engine Error", MB_OK | MB_ICONERROR );
	}
	else
	{
		g_physXProperties.m_fDefaultRestitution = atof( m_strDefaultRestitution );
		g_physXProperties.m_fDefaultStaticFriction = atof( m_strDefaultStaticFriction );
		g_physXProperties.m_fDefaultSkinWidth = atof( m_strDefaultSkinWidth );
		g_physXProperties.m_fDefaultDynamicFriction = atof( m_strDefaultDynamicFriction );
		g_physXProperties.m_fGroundHeight = atof(m_strGroundHeight);
		g_physXProperties.m_fGravityX = atof( m_strGravityX );
		g_physXProperties.m_fGravityY = atof( m_strGravityY );
		g_physXProperties.m_fGravityZ = atof( m_strGravityZ );
		g_physXProperties.m_fCameraCharacterDistance = atof( m_strCameraCharacterDistance );
		g_physXProperties.m_fCapsuleRadius = atof( m_strCapsuleRadius );
		g_physXProperties.m_fCapsuleHeight = atof( m_strCapsuleHeight );
		g_physXProperties.m_fCharacterPower = atof( m_strCharacterPower );
		g_physXProperties.m_fCharacterWalkSpeed = atof( m_strCharacterSpeed );
		g_physXProperties.m_fCharacterSkinWidth = atof(m_strCharacterSkinWidth);
		g_physXProperties.m_fCharacterSlopeLimit = atof(m_strCharacterSlopeLimit);
		g_physXProperties.m_fCharacterStepOffset = atof(m_strCharacterStepOffset);
		g_physXProperties.m_fJumpPower = atof( m_strJumpPower );

		CInt checkState;

		checkState = m_checkBoxGroundPlane.GetCheck();
		if (checkState == BST_CHECKED)
		{
			g_physXProperties.m_bGroundPlane = CTrue;
		}
		else
		{
			g_physXProperties.m_bGroundPlane = CFalse;
		}

		checkState = m_checkBoxApplyGravity.GetCheck();
		if( checkState == BST_CHECKED )
		{
			g_physXProperties.m_bApplyGravity = CTrue;
			g_multipleView->m_nx->gDefaultGravity = NxVec3( g_physXProperties.m_fGravityX, g_physXProperties.m_fGravityY, g_physXProperties.m_fGravityZ );
		}
		else
		{
			g_physXProperties.m_bApplyGravity = CFalse;
			g_multipleView->m_nx->gDefaultGravity = NxVec3(0.0f);
		}

		checkState = m_checkBoxDebugMode.GetCheck();
		if( checkState == BST_CHECKED )
			g_physXProperties.m_bDebugMode = CTrue;
		else
			g_physXProperties.m_bDebugMode = CFalse;

		checkState = m_checkBoxJumping.GetCheck();
		if( checkState == BST_CHECKED )
			g_physXProperties.m_bJumping = CTrue;
		else
			g_physXProperties.m_bJumping = CFalse;

		ex_pVandaEngine1Dlg->ResetPhysX(CFalse);
		CDialog::OnOK();
	}
}

BOOL CEditGeneralPhysXProperties::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_strDefaultRestitution.Format( "%.2f", g_physXProperties.m_fDefaultRestitution);
	m_strDefaultStaticFriction.Format( "%.2f", g_physXProperties.m_fDefaultStaticFriction);
	m_strDefaultSkinWidth.Format( "%.2f", g_physXProperties.m_fDefaultSkinWidth);
	m_strDefaultDynamicFriction.Format( "%.2f", g_physXProperties.m_fDefaultDynamicFriction);
	m_strGroundHeight.Format("%.2f", g_physXProperties.m_fGroundHeight);
	m_strGravityX.Format( "%.2f", g_physXProperties.m_fGravityX);
	m_strGravityY.Format( "%.2f", g_physXProperties.m_fGravityY);
	m_strGravityZ.Format( "%.2f", g_physXProperties.m_fGravityZ);
	m_strCameraCharacterDistance.Format( "%.2f", g_physXProperties.m_fCameraCharacterDistance);
	m_strCapsuleRadius.Format( "%.2f", g_physXProperties.m_fCapsuleRadius);
	m_strCapsuleHeight.Format( "%.2f", g_physXProperties.m_fCapsuleHeight);
	m_strCharacterPower.Format( "%.2f", g_physXProperties.m_fCharacterPower);
	m_strCharacterSpeed.Format( "%.2f", g_physXProperties.m_fCharacterWalkSpeed);
	m_strCharacterSlopeLimit.Format("%.2f", g_physXProperties.m_fCharacterSlopeLimit);
	m_strCharacterSkinWidth.Format("%.2f", g_physXProperties.m_fCharacterSkinWidth);
	m_strCharacterStepOffset.Format("%.2f", g_physXProperties.m_fCharacterStepOffset);
	m_strJumpPower.Format("%.2f", g_physXProperties.m_fJumpPower);

	m_fDefaultRestitution = atof( m_strDefaultRestitution );
	m_fDefaultStaticFriction = atof( m_strDefaultStaticFriction );
	m_fDefaultSkinWidth = atof( m_strDefaultSkinWidth );
	m_fDefaultDynamicFriction = atof( m_strDefaultDynamicFriction );
	m_fGroundHeight = atof(m_strGroundHeight);
	m_fGravityX = atof( m_strGravityX );
	m_fGravityY = atof( m_strGravityY );
	m_fGravityZ = atof( m_strGravityZ );
	m_fCameraCharacterDistance = atof( m_strCameraCharacterDistance );
	m_fCapsuleRadius = atof( m_strCapsuleRadius );
	m_fCapsuleHeight = atof( m_strCapsuleHeight );
	m_fCharacterPower = atof( m_strCharacterPower );
	m_fCharacterWalkSpeed = atof( m_strCharacterSpeed );
	m_fCharacterSkinWidth = atof(m_strCharacterSkinWidth);
	m_fCharacterStepOffset = atof(m_strCharacterStepOffset);
	m_fCharacterSlopeLimit = atof(m_strCharacterSlopeLimit);
	m_fJumpPower = atof( m_strJumpPower );

	m_editBoxRestitution.SetWindowTextA(m_strDefaultRestitution);
	m_editBoxStaticFriction.SetWindowTextA(m_strDefaultStaticFriction);
	m_editBoxDynamicFriction.SetWindowTextA(m_strDefaultDynamicFriction);
	m_editBoxSkinWidth.SetWindowTextA(m_strDefaultSkinWidth);
	m_editBoxGravityX.SetWindowTextA(m_strGravityX);
	m_editBoxGravityY.SetWindowTextA(m_strGravityY);
	m_editBoxGravityZ.SetWindowTextA(m_strGravityZ);
	m_editBoxCameraCharacterDistance.SetWindowTextA(m_strCameraCharacterDistance);
	m_editBoxCapsuleRadius.SetWindowTextA(m_strCapsuleRadius);
	m_editBoxCapsuleHeight.SetWindowTextA(m_strCapsuleHeight);
	m_editBoxCharacterPower.SetWindowTextA(m_strCharacterPower);
	m_editBoxCharacterSpeed.SetWindowTextA(m_strCharacterSpeed);
	m_editBoxCharacterSlopeLimit.SetWindowTextA(m_strCharacterSlopeLimit);
	m_editBoxCharacterSkinWidth.SetWindowTextA(m_strCharacterSkinWidth);
	m_editBoxCharacterStepOffset.SetWindowTextA(m_strCharacterStepOffset);
	m_editBoxGroundHeight.SetWindowTextA(m_strGroundHeight);

	m_editBoxJumpPower.SetWindowTextA(m_strJumpPower);

	if (g_physXProperties.m_bGroundPlane)
		m_checkBoxGroundPlane.SetCheck(BST_CHECKED);
	else
		m_checkBoxGroundPlane.SetCheck(BST_UNCHECKED);

	if( g_physXProperties.m_bApplyGravity )
		m_checkBoxApplyGravity.SetCheck( BST_CHECKED );
	else
		m_checkBoxApplyGravity.SetCheck( BST_UNCHECKED );

	if( g_physXProperties.m_bDebugMode )
		m_checkBoxDebugMode.SetCheck( BST_CHECKED );
	else
		m_checkBoxDebugMode.SetCheck( BST_UNCHECKED );

	if( g_physXProperties.m_bJumping )
		m_checkBoxJumping.SetCheck( BST_CHECKED );
	else
		m_checkBoxJumping.SetCheck( BST_UNCHECKED );

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}





void CEditGeneralPhysXProperties::OnEnChangeEditCharacterSkinWidth()
{
	m_editBoxCharacterSkinWidth.GetWindowTextA(m_strCharacterSkinWidth);
	m_fCharacterSkinWidth = atof(m_strCharacterSkinWidth);
}


void CEditGeneralPhysXProperties::OnEnChangeEditCharacterStepOffset()
{
	m_editBoxCharacterStepOffset.GetWindowTextA(m_strCharacterStepOffset);
	m_fCharacterStepOffset = atof(m_strCharacterStepOffset);

}


void CEditGeneralPhysXProperties::OnEnChangeEditCharacterSlopeLimit()
{
	m_editBoxCharacterSlopeLimit.GetWindowTextA(m_strCharacterSlopeLimit);
	m_fCharacterSlopeLimit = atof(m_strCharacterSlopeLimit);
}


void CEditGeneralPhysXProperties::OnEnChangeEditGroundHeight()
{
	m_editBoxGroundHeight.GetWindowTextA(m_strGroundHeight);
	m_fGroundHeight = atof(m_strGroundHeight);

}



void CEditGeneralPhysXProperties::OnBnClickedButtonReset()
{
	if (MessageBox("Are you sure you want to reset PhysX Properties?", "Warning", MB_YESNO) == IDYES)
	{
		g_physXProperties.Reset();

		m_strDefaultRestitution.Format("%.2f", g_physXProperties.m_fDefaultRestitution);
		m_strDefaultStaticFriction.Format("%.2f", g_physXProperties.m_fDefaultStaticFriction);
		m_strDefaultSkinWidth.Format("%.2f", g_physXProperties.m_fDefaultSkinWidth);
		m_strDefaultDynamicFriction.Format("%.2f", g_physXProperties.m_fDefaultDynamicFriction);
		m_strGroundHeight.Format("%.2f", g_physXProperties.m_fGroundHeight);
		m_strGravityX.Format("%.2f", g_physXProperties.m_fGravityX);
		m_strGravityY.Format("%.2f", g_physXProperties.m_fGravityY);
		m_strGravityZ.Format("%.2f", g_physXProperties.m_fGravityZ);
		m_strCameraCharacterDistance.Format("%.2f", g_physXProperties.m_fCameraCharacterDistance);
		m_strCapsuleRadius.Format("%.2f", g_physXProperties.m_fCapsuleRadius);
		m_strCapsuleHeight.Format("%.2f", g_physXProperties.m_fCapsuleHeight);
		m_strCharacterPower.Format("%.2f", g_physXProperties.m_fCharacterPower);
		m_strCharacterSpeed.Format("%.2f", g_physXProperties.m_fCharacterWalkSpeed);
		m_strCharacterSlopeLimit.Format("%.2f", g_physXProperties.m_fCharacterSlopeLimit);
		m_strCharacterSkinWidth.Format("%.2f", g_physXProperties.m_fCharacterSkinWidth);
		m_strCharacterStepOffset.Format("%.2f", g_physXProperties.m_fCharacterStepOffset);
		m_strJumpPower.Format("%.2f", g_physXProperties.m_fJumpPower);

		m_fDefaultRestitution = atof(m_strDefaultRestitution);
		m_fDefaultStaticFriction = atof(m_strDefaultStaticFriction);
		m_fDefaultSkinWidth = atof(m_strDefaultSkinWidth);
		m_fDefaultDynamicFriction = atof(m_strDefaultDynamicFriction);
		m_fGroundHeight = atof(m_strGroundHeight);
		m_fGravityX = atof(m_strGravityX);
		m_fGravityY = atof(m_strGravityY);
		m_fGravityZ = atof(m_strGravityZ);
		m_fCameraCharacterDistance = atof(m_strCameraCharacterDistance);
		m_fCapsuleRadius = atof(m_strCapsuleRadius);
		m_fCapsuleHeight = atof(m_strCapsuleHeight);
		m_fCharacterPower = atof(m_strCharacterPower);
		m_fCharacterWalkSpeed = atof(m_strCharacterSpeed);
		m_fCharacterSkinWidth = atof(m_strCharacterSkinWidth);
		m_fCharacterStepOffset = atof(m_strCharacterStepOffset);
		m_fCharacterSlopeLimit = atof(m_strCharacterSlopeLimit);
		m_fJumpPower = atof(m_strJumpPower);

		m_editBoxRestitution.SetWindowTextA(m_strDefaultRestitution);
		m_editBoxStaticFriction.SetWindowTextA(m_strDefaultStaticFriction);
		m_editBoxDynamicFriction.SetWindowTextA(m_strDefaultDynamicFriction);
		m_editBoxSkinWidth.SetWindowTextA(m_strDefaultSkinWidth);
		m_editBoxGravityX.SetWindowTextA(m_strGravityX);
		m_editBoxGravityY.SetWindowTextA(m_strGravityY);
		m_editBoxGravityZ.SetWindowTextA(m_strGravityZ);
		m_editBoxCameraCharacterDistance.SetWindowTextA(m_strCameraCharacterDistance);
		m_editBoxCapsuleRadius.SetWindowTextA(m_strCapsuleRadius);
		m_editBoxCapsuleHeight.SetWindowTextA(m_strCapsuleHeight);
		m_editBoxCharacterPower.SetWindowTextA(m_strCharacterPower);
		m_editBoxCharacterSpeed.SetWindowTextA(m_strCharacterSpeed);
		m_editBoxCharacterSlopeLimit.SetWindowTextA(m_strCharacterSlopeLimit);
		m_editBoxCharacterSkinWidth.SetWindowTextA(m_strCharacterSkinWidth);
		m_editBoxCharacterStepOffset.SetWindowTextA(m_strCharacterStepOffset);
		m_editBoxGroundHeight.SetWindowTextA(m_strGroundHeight);

		m_editBoxJumpPower.SetWindowTextA(m_strJumpPower);

		if (g_physXProperties.m_bGroundPlane)
			m_checkBoxGroundPlane.SetCheck(BST_CHECKED);
		else
			m_checkBoxGroundPlane.SetCheck(BST_UNCHECKED);

		if (g_physXProperties.m_bApplyGravity)
			m_checkBoxApplyGravity.SetCheck(BST_CHECKED);
		else
			m_checkBoxApplyGravity.SetCheck(BST_UNCHECKED);

		if (g_physXProperties.m_bDebugMode)
			m_checkBoxDebugMode.SetCheck(BST_CHECKED);
		else
			m_checkBoxDebugMode.SetCheck(BST_UNCHECKED);

		if (g_physXProperties.m_bJumping)
			m_checkBoxJumping.SetCheck(BST_CHECKED);
		else
			m_checkBoxJumping.SetCheck(BST_UNCHECKED);
	}

}
