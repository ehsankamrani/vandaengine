//Copyright (C) 2023 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

// EditLOD.cpp : implementation file
//

#include "stdafx.h"
#include "VandaEngine1.h"
#include "EditLOD.h"
#include "afxdialogex.h"


// CEditLOD dialog

IMPLEMENT_DYNAMIC(CEditLOD, CDialog)

CEditLOD::CEditLOD(CWnd* pParent /*=NULL*/)
	: CDialog(CEditLOD::IDD, pParent)
{

}

CEditLOD::~CEditLOD()
{
}

void CEditLOD::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RICHEDIT_LOD1_MAX, m_lod1Max);
	DDX_Control(pDX, IDC_RICHEDIT_LOD2_MIN, m_lod2Min);
	DDX_Control(pDX, IDC_RICHEDIT_LOD2_MAX, m_lod2Max);
	DDX_Control(pDX, IDC_RICHEDIT_LOD3_MIN, m_lod3Min);
	DDX_Control(pDX, IDC_RICHEDIT_LOD3_MAX, m_lod3Max);
	DDX_Control(pDX, IDC_RICHEDIT_LOD1_MIN_OC_DISTANCE, m_lod1MinObjectCameraDistance);
	DDX_Control(pDX, IDC_RICHEDIT_LOD4_OC_DISTANCE, m_lod4ObjectCameraDistance);
	DDX_Control(pDX, IDC_RICHEDIT_WATER_REFLECTION_PERCENTS, m_waterReflectionPercents);
	DDX_Control(pDX, IDC_RICHEDIT_WATER_REFLECTION_DISTANCE, m_waterReflectionDistance);
	DDX_Control(pDX, IDC_RICHEDIT_WATER_INVISIBLE_PERCENTS, m_waterInvisiblePercents);
	DDX_Control(pDX, IDC_RICHEDIT_WATER_INVISIBLE_MIN_DISTANCE, m_waterInvisibleDistance);
}


BEGIN_MESSAGE_MAP(CEditLOD, CDialog)
	ON_BN_CLICKED(IDOK, &CEditLOD::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_RESET, &CEditLOD::OnBnClickedButtonReset)
END_MESSAGE_MAP()






void CEditLOD::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here

	m_lod1Max.GetWindowTextA(m_strLod1Max);
	if (m_strLod1Max.IsEmpty())
	{
		MessageBox("Please Enter a Value for LOD1 Max");
		return;
	}
	g_instancePrefabLODPercent.m_lod1 = atof(m_strLod1Max);

	m_lod1MinObjectCameraDistance.GetWindowTextA(m_strLod1MinObjectCameraDistance);
	if (m_strLod1MinObjectCameraDistance.IsEmpty())
	{
		MessageBox("Please Enter a Value for LOD1 Minimum Object-Camera Distance");
		return;
	}
	g_instancePrefabLODPercent.m_lod1MinObjectCameraDistance = atof(m_strLod1MinObjectCameraDistance);

	m_lod2Min.GetWindowTextA(m_strLod2Min);
	if (m_strLod2Min.IsEmpty())
	{
		MessageBox("Please Enter a Value for LOD2 Min");
		return;
	}
	g_instancePrefabLODPercent.m_lod2.x = atof(m_strLod2Min);

	m_lod2Max.GetWindowTextA(m_strLod2Max);
	if (m_strLod2Max.IsEmpty())
	{
		MessageBox("Please Enter a Value for LOD2 Max");
		return;
	}

	g_instancePrefabLODPercent.m_lod2.y = atof(m_strLod2Max);

	m_lod3Min.GetWindowTextA(m_strLod3Min);
	if (m_strLod3Min.IsEmpty())
	{
		MessageBox("Please Enter a Value for LOD3 Min");
		return;
	}
	g_instancePrefabLODPercent.m_lod3.x = atof(m_strLod3Min);

	m_lod3Max.GetWindowTextA(m_strLod3Max);
	if (m_strLod3Max.IsEmpty())
	{
		MessageBox("Please Enter a Value for LOD3 Max");
		return;
	}
	g_instancePrefabLODPercent.m_lod3.y = atof(m_strLod3Max);

	m_lod4ObjectCameraDistance.GetWindowTextA(m_strLod4ObjectCameraDistance);
	if (m_strLod4ObjectCameraDistance.IsEmpty())
	{
		MessageBox("Please Enter a Value for LOD4 Object-Camera Distance");
		return;
	}
	g_instancePrefabLODPercent.m_lod4ObjectCameraDistance = atof(m_strLod4ObjectCameraDistance);

	//water reflection percents
	m_waterReflectionPercents.GetWindowTextA(m_strWaterReflectionPercents);
	if (m_strWaterReflectionPercents.IsEmpty())
	{
		MessageBox("Please Enter a Value for Water Reflection Percents");
		return;
	}
	g_instancePrefabLODPercent.m_waterReflectionPercents = atof(m_strWaterReflectionPercents);

	//water reflection distance
	m_waterReflectionDistance.GetWindowTextA(m_strWaterReflectionDistance);
	if (m_strWaterReflectionDistance.IsEmpty())
	{
		MessageBox("Please Enter a Value for Water Reflection Distance");
		return;
	}
	g_instancePrefabLODPercent.m_waterReflectionCameraDistance = atof(m_strWaterReflectionDistance);

	//water Invisible percents
	m_waterInvisiblePercents.GetWindowTextA(m_strWaterInvisiblePercents);
	if (m_strWaterInvisiblePercents.IsEmpty())
	{
		MessageBox("Please Enter a Value for Water Invisible Percents");
		return;
	}
	g_instancePrefabLODPercent.m_waterInvisiblePercent = atof(m_strWaterInvisiblePercents);

	//water Invisible distance
	m_waterInvisibleDistance.GetWindowTextA(m_strWaterInvisibleDistance);
	if (m_strWaterInvisibleDistance.IsEmpty())
	{
		MessageBox("Please Enter a Value for Water Invisible Distance");
		return;
	}
	g_instancePrefabLODPercent.m_waterInvisibleCameraDistance = atof(m_strWaterInvisibleDistance);

	for (CUInt i = 0; i < g_instancePrefab.size(); i++)
	{
		if (g_instancePrefab[i]->GetIsTrigger() || Cmp(g_instancePrefab[i]->GetName(), "VANDA_MAIN_CHARACTER"))
			continue;

		g_instancePrefab[i]->SetSceneVisible(0, CFalse);
		g_instancePrefab[i]->SetSceneVisible(1, CFalse);
		g_instancePrefab[i]->SetSceneVisible(2, CFalse);
	}
	g_multipleView->SetElapsedTimeFromBeginning();
	g_multipleView->RenderWindow();

	CDialog::OnOK();
}


BOOL CEditLOD::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	m_strLod1Max.Format(_T("%.3f"), g_instancePrefabLODPercent.m_lod1);
	m_lod1Max.SetWindowTextA(m_strLod1Max);

	m_strLod1MinObjectCameraDistance.Format(_T("%.3f"), g_instancePrefabLODPercent.m_lod1MinObjectCameraDistance);
	m_lod1MinObjectCameraDistance.SetWindowTextA(m_strLod1MinObjectCameraDistance);

	m_strLod2Min.Format(_T("%.3f"), g_instancePrefabLODPercent.m_lod2.x);
	m_strLod2Max.Format(_T("%.3f"), g_instancePrefabLODPercent.m_lod2.y);

	m_lod2Min.SetWindowTextA(m_strLod2Min);
	m_lod2Max.SetWindowTextA(m_strLod2Max);

	m_strLod3Min.Format(_T("%.3f"), g_instancePrefabLODPercent.m_lod3.x);
	m_strLod3Max.Format(_T("%.3f"), g_instancePrefabLODPercent.m_lod3.y);

	m_lod3Min.SetWindowTextA(m_strLod3Min);
	m_lod3Max.SetWindowTextA(m_strLod3Max);

	m_strLod4ObjectCameraDistance.Format(_T("%.3f"), g_instancePrefabLODPercent.m_lod4ObjectCameraDistance);
	m_lod4ObjectCameraDistance.SetWindowTextA(m_strLod4ObjectCameraDistance);

	//water
	m_strWaterReflectionPercents.Format(_T("%.3f"), g_instancePrefabLODPercent.m_waterReflectionPercents);
	m_waterReflectionPercents.SetWindowTextA(m_strWaterReflectionPercents);

	m_strWaterReflectionDistance.Format(_T("%.3f"), g_instancePrefabLODPercent.m_waterReflectionCameraDistance);
	m_waterReflectionDistance.SetWindowTextA(m_strWaterReflectionDistance);

	m_strWaterInvisiblePercents.Format(_T("%.3f"), g_instancePrefabLODPercent.m_waterInvisiblePercent);
	m_waterInvisiblePercents.SetWindowTextA(m_strWaterInvisiblePercents);

	m_strWaterInvisibleDistance.Format(_T("%.3f"), g_instancePrefabLODPercent.m_waterInvisibleCameraDistance);
	m_waterInvisibleDistance.SetWindowTextA(m_strWaterInvisibleDistance);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CEditLOD::OnBnClickedButtonReset()
{
	if (MessageBox("reset factory LOD settings?", "Vanda Engine", MB_YESNO | MB_ICONINFORMATION) == IDYES)
	{
		// TODO: Add your control notification handler code here
		CLODProperties instancePrefabLODPercent;
		// TODO:  Add extra initialization here
		m_strLod1Max.Format(_T("%.3f"), instancePrefabLODPercent.m_lod1);
		m_lod1Max.SetWindowTextA(m_strLod1Max);

		m_strLod1MinObjectCameraDistance.Format(_T("%.3f"), instancePrefabLODPercent.m_lod1MinObjectCameraDistance);
		m_lod1MinObjectCameraDistance.SetWindowTextA(m_strLod1MinObjectCameraDistance);

		m_strLod2Min.Format(_T("%.3f"), instancePrefabLODPercent.m_lod2.x);
		m_strLod2Max.Format(_T("%.3f"), instancePrefabLODPercent.m_lod2.y);

		m_lod2Min.SetWindowTextA(m_strLod2Min);
		m_lod2Max.SetWindowTextA(m_strLod2Max);

		m_strLod3Min.Format(_T("%.3f"), instancePrefabLODPercent.m_lod3.x);
		m_strLod3Max.Format(_T("%.3f"), instancePrefabLODPercent.m_lod3.y);

		m_lod3Min.SetWindowTextA(m_strLod3Min);
		m_lod3Max.SetWindowTextA(m_strLod3Max);

		m_strLod4ObjectCameraDistance.Format(_T("%.3f"), instancePrefabLODPercent.m_lod4ObjectCameraDistance);
		m_lod4ObjectCameraDistance.SetWindowTextA(m_strLod4ObjectCameraDistance);

		//water
		m_strWaterReflectionPercents.Format(_T("%.3f"), instancePrefabLODPercent.m_waterReflectionPercents);
		m_waterReflectionPercents.SetWindowTextA(m_strWaterReflectionPercents);

		m_strWaterReflectionDistance.Format(_T("%.3f"), instancePrefabLODPercent.m_waterReflectionCameraDistance);
		m_waterReflectionDistance.SetWindowTextA(m_strWaterReflectionDistance);

		m_strWaterInvisiblePercents.Format(_T("%.3f"), instancePrefabLODPercent.m_waterInvisiblePercent);
		m_waterInvisiblePercents.SetWindowTextA(m_strWaterInvisiblePercents);

		m_strWaterInvisibleDistance.Format(_T("%.3f"), instancePrefabLODPercent.m_waterInvisibleCameraDistance);
		m_waterInvisibleDistance.SetWindowTextA(m_strWaterInvisibleDistance);

	}
}
