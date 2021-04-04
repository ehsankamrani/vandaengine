// EditPrefab.cpp : implementation file
//

#include "stdafx.h"
#include "VandaEngine1.h"
#include "EditPrefab.h"
#include "afxdialogex.h"
#include "GraphicsEngine/Animation.h"
// CEditPrefab dialog

IMPLEMENT_DYNAMIC(CEditPrefab, CDialog)

CEditPrefab::CEditPrefab(CWnd* pParent /*=NULL*/)
	: CDialog(CEditPrefab::IDD, pParent)
{
	m_instancePrefab = NULL;
}

CEditPrefab::~CEditPrefab()
{
}

void CEditPrefab::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_PREFAB_INSTANCE_ANIMATIONS, m_listPrefabInstanceAnimationNames);
	DDX_Control(pDX, IDC_LIST_PREFAB_INSTANCE_CAMERAS, m_listPrefabInstanceCameraNames);
	DDX_Control(pDX, IDC_PHOTO, m_imageCtrl);
	DDX_Control(pDX, IDC_RICHED_PREFAB_INSTANCE_ANIMATION_NAME, m_richSelectedAnimationName);
	DDX_Control(pDX, IDC_RICHED_PREFAB_INSTANCE_CAMERA_NAME, m_richSelectedCameraName);
	DDX_Control(pDX, IDC_EDIT_POS_X, m_editPosX);
	DDX_Control(pDX, IDC_EDIT_POS_Y, m_editPosY);
	DDX_Control(pDX, IDC_EDIT_POS_Z, m_editPosZ);
	DDX_Control(pDX, IDC_EDIT_ROT_X, m_editRotX);
	DDX_Control(pDX, IDC_EDIT_ROT_Y, m_editRotY);
	DDX_Control(pDX, IDC_EDIT_ROT_Z, m_editRotZ);
	DDX_Control(pDX, IDC_EDIT_SCALE_X, m_editScaleX);
	DDX_Control(pDX, IDC_EDIT_SCALE_Y, m_editScaleY);
	DDX_Control(pDX, IDC_EDIT_SCALE_Z, m_editScaleZ);
	DDX_Control(pDX, IDC_STATIC_PREFAB_INSTANCE_NAME, m_textPrefabInstanceName);
	DDX_Control(pDX, IDC_RICHED_PREFAB_INSTANCE_NAME, m_richPrefabInstanceName);
}


BEGIN_MESSAGE_MAP(CEditPrefab, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_COPY_PREFAB_INSTANCE_CAMERA_NAME, &CEditPrefab::OnBnClickedButtonCopyPrefabInstanceCameraName)
	ON_BN_CLICKED(IDC_BUTTON_COPY_PREFAB_INSTANCE_ANIMATION_NAME, &CEditPrefab::OnBnClickedButtonCopyPrefabInstanceAnimationName)
	ON_BN_CLICKED(IDOK, &CEditPrefab::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_COPY_PREFAB_INSTANCE_NAME, &CEditPrefab::OnBnClickedButtonCopyPrefabInstanceName)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_PREFAB_INSTANCE_ANIMATIONS, &CEditPrefab::OnLvnItemchangedListPrefabInstanceAnimations)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_PREFAB_INSTANCE_CAMERAS, &CEditPrefab::OnLvnItemchangedListPrefabInstanceCameras)
	ON_EN_CHANGE(IDC_EDIT_POS_X, &CEditPrefab::OnEnChangeEditPosX)
	ON_EN_CHANGE(IDC_EDIT_POS_Y, &CEditPrefab::OnEnChangeEditPosY)
	ON_EN_CHANGE(IDC_EDIT_POS_Z, &CEditPrefab::OnEnChangeEditPosZ)
	ON_EN_CHANGE(IDC_EDIT_ROT_X, &CEditPrefab::OnEnChangeEditRotX)
	ON_EN_CHANGE(IDC_EDIT_ROT_Y, &CEditPrefab::OnEnChangeEditRotY)
	ON_EN_CHANGE(IDC_EDIT_ROT_Z, &CEditPrefab::OnEnChangeEditRotZ)
	ON_EN_CHANGE(IDC_EDIT_SCALE_X, &CEditPrefab::OnEnChangeEditScaleX)
	ON_EN_CHANGE(IDC_EDIT_SCALE_Y, &CEditPrefab::OnEnChangeEditScaleY)
	ON_EN_CHANGE(IDC_EDIT_SCALE_Z, &CEditPrefab::OnEnChangeEditScaleZ)
END_MESSAGE_MAP()


// CEditPrefab message handlers


void CEditPrefab::OnBnClickedButtonCopyPrefabInstanceCameraName()
{
	CString s;
	m_richSelectedCameraName.GetWindowTextA(s);
	if (s.IsEmpty())
		MessageBox("Please select a camera from the list (if exists)!", "Error", MB_OK | MB_ICONERROR);
	else
	{
		m_richSelectedCameraName.Copy();
		CChar message[MAX_URI_SIZE];
		sprintf(message, "Item '%s' copied to clipboard", s);
		MessageBox(message, "Report", MB_OK | MB_ICONINFORMATION);
	}
}


void CEditPrefab::OnBnClickedButtonCopyPrefabInstanceAnimationName()
{
	CString s;
	m_richSelectedAnimationName.GetWindowTextA(s);
	if (s.IsEmpty())
		MessageBox("Please select an animation from the list (if exists)!", "Error", MB_OK | MB_ICONERROR);
	else
	{
		m_richSelectedAnimationName.Copy();
		CChar message[MAX_URI_SIZE];
		sprintf(message, "Item '%s' copied to clipboard", s);
		MessageBox(message, "Report", MB_OK | MB_ICONINFORMATION);
	}
}


void CEditPrefab::OnBnClickedOk()
{
	if (m_strPosX.IsEmpty() || m_strPosY.IsEmpty() || m_strPosZ.IsEmpty() || m_strRotX.IsEmpty() || m_strRotY.IsEmpty() || m_strRotZ.IsEmpty()
		|| m_strScaleX.IsEmpty() || m_strScaleY.IsEmpty() || m_strScaleZ.IsEmpty())
	{
		MessageBox("Please fill in all position, rotation and scale fields", "Error", MB_OK | MB_ICONERROR);
		return;
	}
	CVec3f position(m_fPosX, m_fPosY, m_fPosZ);
	m_instancePrefab->SetTranslate(position);
	g_arrowPosition = position;
	CVec4f rotation(m_fRotX, m_fRotY, m_fRotZ, m_instancePrefab->GetRotate().w);
	m_instancePrefab->SetRotate(rotation);
	CVec3f arrowRot(m_fRotX, m_fRotY, m_fRotZ);
	g_arrowRotate = arrowRot;
	CVec3f scale(m_fScaleX, m_fScaleY, m_fScaleZ);
	m_instancePrefab->SetScale(scale);
	g_arrowScale = scale;

	SetDialogData3(CTrue, m_instancePrefab);

	g_updateOctree = CTrue;

	CDialog::OnOK();
}


BOOL CEditPrefab::OnInitDialog()
{
	CDialog::OnInitDialog();

	RECT tempAnimationRect;
	m_listPrefabInstanceAnimationNames.GetClientRect(&tempAnimationRect);
	m_listPrefabInstanceAnimationNames.InsertColumn(0, "Prefab Animations", LVCFMT_LEFT | LVS_SHOWSELALWAYS, (tempAnimationRect.right - tempAnimationRect.left) * 90 / 100);
	m_listPrefabInstanceAnimationNames.ShowWindow(SW_SHOW);
	m_listPrefabInstanceAnimationNames.UpdateWindow();

	RECT tempCameraRect;
	m_listPrefabInstanceCameraNames.GetClientRect(&tempCameraRect);
	m_listPrefabInstanceCameraNames.InsertColumn(0, "Prefab Cameras", LVCFMT_LEFT | LVS_SHOWSELALWAYS, (tempCameraRect.right - tempCameraRect.left) * 90 / 100);
	m_listPrefabInstanceCameraNames.ShowWindow(SW_SHOW);
	m_listPrefabInstanceCameraNames.UpdateWindow();

	if (m_instancePrefab)
	{
		//prefab instance name
		m_textPrefabInstanceName.SetWindowTextA(m_instancePrefab->GetName());
		m_richPrefabInstanceName.SetWindowTextA(m_instancePrefab->GetName());
		CInt end = m_richPrefabInstanceName.GetWindowTextLengthA();
		m_richPrefabInstanceName.SetSel(0, end);

		CInt prefabInstanceAnimationIndex = -1;
		CInt prefabInstanceCameraIndex = -1;

		for (CInt k = 0; k < m_instancePrefab->GetScene(0)->GetNumClips(); k++)
		{
			prefabInstanceAnimationIndex++;
			int index = prefabInstanceAnimationIndex;
			LVITEM lvItem;
			lvItem.mask = LVIF_TEXT;
			lvItem.iItem = index;
			lvItem.iSubItem = 0;
			lvItem.pszText = m_instancePrefab->GetScene(0)->m_animationClips[k]->GetName();
			m_listPrefabInstanceAnimationNames.InsertItem(&lvItem);
			m_listPrefabInstanceAnimationNames.SetExtendedStyle(LVS_EX_INFOTIP | LVS_EX_ONECLICKACTIVATE | LVS_EX_LABELTIP);

			m_listPrefabInstanceAnimationNames.EnsureVisible(index, FALSE);
			m_listPrefabInstanceAnimationNames.UpdateWindow();

			if (k == 0)
			{
				m_richSelectedAnimationName.SetWindowTextA(lvItem.pszText);
				CInt end = m_richSelectedAnimationName.GetWindowTextLengthA();
				m_richSelectedAnimationName.SetSel(0, end);
			}
		}

		std::vector <std::string> camera_names;

		for (CUInt sceneIndex = 0; sceneIndex < 3; sceneIndex++)
		{
			CBool hasLOD = m_instancePrefab->GetPrefab()->GetHasLod(sceneIndex);

			if (hasLOD)
			{
				//number of instance cameras
				CUInt numCameras = m_instancePrefab->GetScene(sceneIndex)->m_cameraInstances.size();

				//camera instance names
				for (CUInt j = 0; j < numCameras; j++)
				{
					CChar cameraName[MAX_NAME_SIZE];
					Cpy(cameraName, m_instancePrefab->GetScene(sceneIndex)->m_cameraInstances[j]->m_abstractCamera->GetPureName());

					CBool foundTarget = CFalse;
					for (CUInt k = 0; k < camera_names.size(); k++)
					{
						if (Cmp(camera_names[k].c_str(), cameraName))
						{
							foundTarget = CTrue;
							break;
						}
					}

					if (foundTarget)
						continue;
					else
						camera_names.push_back(cameraName);

					prefabInstanceCameraIndex++;
					int index = prefabInstanceCameraIndex;
					LVITEM lvItem;
					lvItem.mask = LVIF_TEXT;
					lvItem.iItem = index;
					lvItem.iSubItem = 0;
					lvItem.pszText = cameraName;
					m_listPrefabInstanceCameraNames.InsertItem(&lvItem);
					m_listPrefabInstanceCameraNames.SetExtendedStyle(LVS_EX_INFOTIP | LVS_EX_ONECLICKACTIVATE | LVS_EX_LABELTIP);

					m_listPrefabInstanceCameraNames.EnsureVisible(index, FALSE);
					m_listPrefabInstanceCameraNames.UpdateWindow();

					if (j == 0)
					{
						m_richSelectedCameraName.SetWindowTextA(lvItem.pszText);
						CInt end = m_richSelectedCameraName.GetWindowTextLengthA();
						m_richSelectedCameraName.SetSel(0, end);
					}
				}
			}
		}

		//position
		CFloat val;
		CChar temp1_pos[MAX_NAME_SIZE];
		val = roundf(m_instancePrefab->GetTranslate().x * 100) / 100;
		sprintf(temp1_pos, "%.2f", val);
		m_editPosX.SetWindowTextA(temp1_pos);

		CChar temp2_pos[MAX_NAME_SIZE];
		val = roundf(m_instancePrefab->GetTranslate().y * 100) / 100;
		sprintf(temp2_pos, "%.2f", val);
		m_editPosY.SetWindowTextA(temp2_pos);

		CChar temp3_pos[MAX_NAME_SIZE];
		val = roundf(m_instancePrefab->GetTranslate().z * 100) / 100;
		sprintf(temp3_pos, "%.2f", val);
		m_editPosZ.SetWindowTextA(temp3_pos);

		//rotation
		CChar temp1_rot[MAX_NAME_SIZE];
		val = roundf(m_instancePrefab->GetRotate().x * 100) / 100;
		sprintf(temp1_rot, "%.2f", val);
		m_editRotX.SetWindowTextA(temp1_rot);

		CChar temp2_rot[MAX_NAME_SIZE];
		val = roundf(m_instancePrefab->GetRotate().y * 100) / 100;
		sprintf(temp2_rot, "%.2f", val);
		m_editRotY.SetWindowTextA(temp2_rot);

		CChar temp3_rot[MAX_NAME_SIZE];
		val = roundf(m_instancePrefab->GetRotate().z * 100) / 100;
		sprintf(temp3_rot, "%.2f", val);
		m_editRotZ.SetWindowTextA(temp3_rot);

		//scale
		CChar temp1_scale[MAX_NAME_SIZE];
		val = roundf(m_instancePrefab->GetScale().x * 100) / 100;
		sprintf(temp1_scale, "%.2f", val);
		m_editScaleX.SetWindowTextA(temp1_scale);

		CChar temp2_scale[MAX_NAME_SIZE];
		val = roundf(m_instancePrefab->GetScale().y * 100) / 100;
		sprintf(temp2_scale, "%.2f", val);
		m_editScaleY.SetWindowTextA(temp2_scale);

		CChar temp3_scale[MAX_NAME_SIZE];
		val = roundf(m_instancePrefab->GetScale().z * 100) / 100;
		sprintf(temp3_scale, "%.2f", val);
		m_editScaleZ.SetWindowTextA(temp3_scale);

		UpdatePreview();

		camera_names.clear();
	}

	if (m_listPrefabInstanceAnimationNames.GetItemCount())
	{
		m_listPrefabInstanceAnimationNames.SetItemState(0, LVIS_SELECTED, LVIS_SELECTED | LVIS_FOCUSED);
		m_listPrefabInstanceAnimationNames.SetSelectionMark(0);
	}

	if (m_listPrefabInstanceCameraNames.GetItemCount())
	{
		m_listPrefabInstanceCameraNames.SetItemState(0, LVIS_SELECTED, LVIS_SELECTED | LVIS_FOCUSED);
		m_listPrefabInstanceCameraNames.SetSelectionMark(0);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CEditPrefab::OnBnClickedButtonCopyPrefabInstanceName()
{
	CString s;
	m_richPrefabInstanceName.GetWindowTextA(s);
	if (s.IsEmpty())
		MessageBox("Couldn't find the prefab instance name!", "Error", MB_OK | MB_ICONERROR);
	else
	{
		m_richPrefabInstanceName.Copy();
		CChar message[MAX_URI_SIZE];
		sprintf(message, "prefab instance name '%s' copied to clipboard", s);
		MessageBox(message, "Report", MB_OK | MB_ICONINFORMATION);
	}
}

CVoid CEditPrefab::SetPrefabInstance(CInstancePrefab* instance_prefab)
{
	m_instancePrefab = instance_prefab;
}

void CEditPrefab::OnLvnItemchangedListPrefabInstanceAnimations(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	int nSelected = -1;
	POSITION p = m_listPrefabInstanceAnimationNames.GetFirstSelectedItemPosition();
	while (p)
	{
		nSelected = m_listPrefabInstanceAnimationNames.GetNextSelectedItem(p);
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
		m_listPrefabInstanceAnimationNames.GetItem(&lvi);
		*pResult = 0;

		m_richSelectedAnimationName.SetWindowTextA(szBuffer);
		CInt end = m_richSelectedAnimationName.GetWindowTextLengthA();
		m_richSelectedAnimationName.SetSel(0, end);
	}
	else
	{
		m_richSelectedAnimationName.SetWindowTextA("");
		m_richSelectedAnimationName.SetSel(0, 0);
	}
}

void CEditPrefab::OnLvnItemchangedListPrefabInstanceCameras(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	int nSelected = -1;
	POSITION p = m_listPrefabInstanceCameraNames.GetFirstSelectedItemPosition();
	while (p)
	{
		nSelected = m_listPrefabInstanceCameraNames.GetNextSelectedItem(p);
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
		m_listPrefabInstanceCameraNames.GetItem(&lvi);
		*pResult = 0;

		m_richSelectedCameraName.SetWindowTextA(szBuffer);
		CInt end = m_richSelectedCameraName.GetWindowTextLengthA();
		m_richSelectedCameraName.SetSel(0, end);
	}
	else
	{
		m_richSelectedCameraName.SetWindowTextA("");
		m_richSelectedCameraName.SetSel(0, 0);
	}
}

CVoid CEditPrefab::UpdatePreview()
{
	if (!m_instancePrefab)
		return;

	DeleteObject(m_hBitmap);
	//get document folder
	CChar docPath[MAX_URI_SIZE];
	HRESULT result = SHGetFolderPath(NULL, CSIDL_PERSONAL, NULL, SHGFP_TYPE_CURRENT, docPath);
	if (result != S_OK)
	{
		PrintInfo("\nCouldn't get the documents folder", COLOR_RED);
		return;
	}

	CChar bitmapPath[MAX_URI_SIZE];
	sprintf(bitmapPath, "%s%s%s%s%s%s%s%s%s%s", docPath, "/Vanda/Packages/", m_instancePrefab->GetPrefab()->GetPackageName(), "/", m_instancePrefab->GetPrefab()->GetPrefabName(), "/", m_instancePrefab->GetPrefab()->GetPackageName(), "_", m_instancePrefab->GetPrefab()->GetPrefabName(), ".bmp");
	m_hBitmap = (HBITMAP)::LoadImage(AfxGetInstanceHandle(), bitmapPath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	m_imageCtrl.SetBitmap(m_hBitmap);
}

void CEditPrefab::OnEnChangeEditPosX()
{
	m_editPosX.GetWindowTextA(m_strPosX);
	m_fPosX = atof(m_strPosX);
}


void CEditPrefab::OnEnChangeEditPosY()
{
	m_editPosY.GetWindowTextA(m_strPosY);
	m_fPosY = atof(m_strPosY);
}


void CEditPrefab::OnEnChangeEditPosZ()
{
	m_editPosZ.GetWindowTextA(m_strPosZ);
	m_fPosZ = atof(m_strPosZ);
}


void CEditPrefab::OnEnChangeEditRotX()
{
	m_editRotX.GetWindowTextA(m_strRotX);
	m_fRotX = atof(m_strRotX);
}


void CEditPrefab::OnEnChangeEditRotY()
{
	m_editRotY.GetWindowTextA(m_strRotY);
	m_fRotY = atof(m_strRotY);
}


void CEditPrefab::OnEnChangeEditRotZ()
{
	m_editRotZ.GetWindowTextA(m_strRotZ);
	m_fRotZ = atof(m_strRotZ);
}


void CEditPrefab::OnEnChangeEditScaleX()
{
	m_editScaleX.GetWindowTextA(m_strScaleX);
	m_fScaleX = atof(m_strScaleX);
}


void CEditPrefab::OnEnChangeEditScaleY()
{
	m_editScaleY.GetWindowTextA(m_strScaleY);
	m_fScaleY = atof(m_strScaleY);
}


void CEditPrefab::OnEnChangeEditScaleZ()
{
	m_editScaleZ.GetWindowTextA(m_strScaleZ);
	m_fScaleZ = atof(m_strScaleZ);
}
