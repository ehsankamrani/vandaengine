//Copyright (C) 2021 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

// SaveLoadCharacterProfile.cpp : implementation file
//

#include "stdafx.h"
#include "VandaEngine1.h"
#include "SaveLoadCharacterProfile.h"
#include "afxdialogex.h"


// CSaveLoadCharacterProfile dialog

IMPLEMENT_DYNAMIC(CSaveLoadCharacterProfile, CDialog)

CSaveLoadCharacterProfile::CSaveLoadCharacterProfile(CWnd* pParent /*=NULL*/)
	: CDialog(CSaveLoadCharacterProfile::IDD, pParent)
{
	m_profileIndex = -1;
	m_save = CFalse;
	m_camera = CNew(CUpdateCamera);

}

CSaveLoadCharacterProfile::~CSaveLoadCharacterProfile()
{
	CDelete(m_camera);
}

void CSaveLoadCharacterProfile::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_CHARACTER_PROFILES, m_listCharacterProfiles);
	DDX_Control(pDX, IDC_PROFILE_NAME, m_editName);
}


BEGIN_MESSAGE_MAP(CSaveLoadCharacterProfile, CDialog)
	ON_EN_CHANGE(IDC_PROFILE_NAME, &CSaveLoadCharacterProfile::OnEnChangeProfileName)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_CHARACTER_PROFILES, &CSaveLoadCharacterProfile::OnLvnItemchangedListCharacterProfiles)
	ON_BN_CLICKED(IDOK, &CSaveLoadCharacterProfile::OnBnClickedOk)
END_MESSAGE_MAP()


// CSaveLoadCharacterProfile message handlers

CVoid CSaveLoadCharacterProfile::SetSaveMode(CBool save)
{
	m_save = save;
}

void CSaveLoadCharacterProfile::OnEnChangeProfileName()
{
	m_editName.GetWindowTextA(m_strName);
}


BOOL CSaveLoadCharacterProfile::OnInitDialog()
{
	CDialog::OnInitDialog();
	RECT tempRect;
	m_listCharacterProfiles.GetClientRect(&tempRect);

	CBitmap cBmp;
	CBitmap* cBmpMask = NULL;
	m_profileImage.Create(80, 80, ILC_COLOR24, 1, 1);

	cBmp.LoadBitmap(IDB_BITMAP_DEFAULT_PRF);
	m_profileImage.Add(&cBmp, cBmpMask);
	cBmp.DeleteObject();

	m_listCharacterProfiles.SetImageList(&m_profileImage, LVSIL_NORMAL);

	m_listCharacterProfiles.GetClientRect(&tempRect);
	m_listCharacterProfiles.InsertColumn(0, "Profiles", LVCFMT_LEFT | LVS_SHOWSELALWAYS, (tempRect.right - tempRect.left) * 80 / 100);
	m_listCharacterProfiles.ShowWindow(SW_SHOW);
	m_listCharacterProfiles.UpdateWindow();

	//insert items
	m_listCharacterProfiles.SetExtendedStyle(LVS_EX_INFOTIP | LVS_EX_ONECLICKACTIVATE);

	for (CUInt i = 0; i < g_characterProfiles.size(); i++)
	{
		CChar str[MAX_NAME_SIZE];
		Cpy(str, g_characterProfiles[i].c_str());
		InsertItemToProfileList(str);
	}

	m_editName.SetWindowTextA("");
	if (m_save)
		m_editName.SetReadOnly(CFalse);
	else
		m_editName.SetReadOnly(CTrue);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

CVoid CSaveLoadCharacterProfile::InsertItemToProfileList(CChar* profileName)
{
	m_profileIndex++;
	int index = m_profileIndex;
	LVITEM lvItem;
	lvItem.mask = LVIF_TEXT;
	lvItem.iItem = index;
	lvItem.iSubItem = 0;
	lvItem.pszText = profileName;
	m_listCharacterProfiles.InsertItem(&lvItem);

	m_listCharacterProfiles.SetItemState(index, LVIS_SELECTED, LVIS_SELECTED | LVIS_FOCUSED);
	m_listCharacterProfiles.SetSelectionMark(index);
	m_listCharacterProfiles.EnsureVisible(index, FALSE);
	m_listCharacterProfiles.UpdateWindow();
}

void CSaveLoadCharacterProfile::OnLvnItemchangedListCharacterProfiles(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	int nSelected = -1;
	POSITION p = m_listCharacterProfiles.GetFirstSelectedItemPosition();
	while (p)
	{
		nSelected = m_listCharacterProfiles.GetNextSelectedItem(p);
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
		m_listCharacterProfiles.GetItem(&lvi);
		GetWithoutDot(szBuffer);
		m_editName.SetWindowTextA(szBuffer);
	}
	else
		m_editName.SetWindowTextA("");
	*pResult = 0;
}


void CSaveLoadCharacterProfile::OnBnClickedOk()
{
	CString m_profileName;
	m_editName.GetWindowTextA(m_profileName);
	if (Cmp((LPCSTR)m_profileName, ""))
	{
		MessageBox("Please select a profile!", "Vanda Engine Error", MB_OK | MB_ICONINFORMATION);
		return;
	}
	Cpy(m_name, (LPCSTR)m_profileName);

	CChar CharacterProfilePath[MAX_NAME_SIZE];

	//Create Character Profiles Directory
	HRESULT result2 = SHGetFolderPath(NULL, CSIDL_PERSONAL, NULL, SHGFP_TYPE_CURRENT, CharacterProfilePath);
	if (result2 != S_OK)
	{
		PrintInfo("\nCouldn't get the documents folder to write data", COLOR_RED);
	}
	else
	{
		Append(CharacterProfilePath, "/Vanda/Profiles/");
		Append(CharacterProfilePath, m_name);
		Append(CharacterProfilePath, ".prf");
	}

	if (m_save)
	{
		CBool foundTarget = CFalse;
		for (CUInt i = 0; i < g_characterProfiles.size(); i++)
		{
			if (Cmp(m_name, g_characterProfiles[i].c_str()))
			{
				foundTarget = CTrue;
				break;
			}
		}
		if (foundTarget)
		{
			if (MessageBox("Are you sure you want to overwrite this profile?", "Warning", MB_YESNO) == IDNO)
				return;
		}

		FILE *filePtr;
		filePtr = fopen(CharacterProfilePath, "wb");
		if (!filePtr)
		{
			MessageBox("Couldn't open the file to save data!", "Vanda Engine Error", MB_OK | MB_ICONERROR);
			return;
		}
		fwrite(&m_characterType, sizeof(CPhysXCameraType), 1, filePtr);

		fwrite(g_currentPrefabPackageName, sizeof(CChar), MAX_NAME_SIZE, filePtr);
		fwrite(g_currentPrefabName, sizeof(CChar), MAX_NAME_SIZE, filePtr);

		fwrite(m_characterName, sizeof(CChar), MAX_NAME_SIZE, filePtr);
	
		fwrite(&m_position, sizeof(CVec3f), 1, filePtr);
		fwrite(&m_scale, sizeof(CFloat), 1, filePtr);
		fwrite(&m_delayIdle, sizeof(CFloat), 1, filePtr);

		CUInt idleSize = m_idle.size();
		CUInt walkSize = m_walk.size();
		CUInt runSize = m_run.size();
		CUInt jumpSize = m_jump.size();

		fwrite(&idleSize, sizeof(CUInt), 1, filePtr);
		for (CUInt i = 0; i < m_idle.size(); i++)
		{
			CChar name[MAX_NAME_SIZE];
			Cpy(name, m_idle[i].c_str());
			fwrite(name, sizeof(CChar), MAX_NAME_SIZE, filePtr);
		}

		fwrite(&walkSize, sizeof(CUInt), 1, filePtr);
		for (CUInt i = 0; i < m_walk.size(); i++)
		{
			CChar name[MAX_NAME_SIZE];
			Cpy(name, m_walk[i].c_str());
			fwrite(name, sizeof(CChar), MAX_NAME_SIZE, filePtr);
		}

		fwrite(&jumpSize, sizeof(CUInt), 1, filePtr);
		for (CUInt i = 0; i < m_jump.size(); i++)
		{
			CChar name[MAX_NAME_SIZE];
			Cpy(name, m_jump[i].c_str());
			fwrite(name, sizeof(CChar), MAX_NAME_SIZE, filePtr);
		}

		fwrite(&runSize, sizeof(CUInt), 1, filePtr);
		for (CUInt i = 0; i < m_run.size(); i++)
		{
			CChar name[MAX_NAME_SIZE];
			Cpy(name, m_run[i].c_str());
			fwrite(name, sizeof(CChar), MAX_NAME_SIZE, filePtr);
		}

		//write PhysX data here
		fwrite(&m_physXProperties.m_fCameraCharacterDistance, sizeof(CFloat), 1, filePtr);
		fwrite(&m_physXProperties.m_fCapsuleRadius, sizeof(CFloat), 1, filePtr);
		fwrite(&m_physXProperties.m_fCapsuleHeight, sizeof(CFloat), 1, filePtr);
		fwrite(&m_physXProperties.m_fCharacterPower, sizeof(CFloat), 1, filePtr);
		fwrite(&m_physXProperties.m_fCharacterWalkSpeed, sizeof(CFloat), 1, filePtr);
		fwrite(&m_physXProperties.m_fCharacterRunSpeed, sizeof(CFloat), 1, filePtr);
		fwrite(&m_physXProperties.m_fCharacterSlopeLimit, sizeof(CFloat), 1, filePtr);
		fwrite(&m_physXProperties.m_fCharacterSkinWidth, sizeof(CFloat), 1, filePtr);
		fwrite(&m_physXProperties.m_fCharacterStepOffset, sizeof(CFloat), 1, filePtr);
		fwrite(&m_physXProperties.m_fJumpPower, sizeof(CFloat), 1, filePtr);
		fwrite(&m_physXProperties.m_bJumping, sizeof(CBool), 1, filePtr);
		fwrite(&m_physXProperties.m_bDebugMode, sizeof(CBool), 1, filePtr);

		fwrite(&m_characterBlendingProperties, sizeof(CCharacterBlendingProperties), 1, filePtr);

		GLdouble angle = m_camera->m_cameraManager->GetDefaultAngle();
		GLdouble minAngle = m_camera->m_cameraManager->GetMinAngle();
		GLdouble maxAngle = m_camera->m_cameraManager->GetMaxAngle();

		fwrite(&angle, sizeof(GLdouble), 1, filePtr);
		fwrite(&minAngle, sizeof(GLdouble), 1, filePtr);
		fwrite(&maxAngle, sizeof(GLdouble), 1, filePtr);

		fwrite(&m_camera->m_perspectiveCameraTilt, sizeof(CFloat), 1, filePtr);
		fwrite(&m_camera->m_perspectiveCameraMinTilt, sizeof(CFloat), 1, filePtr);
		fwrite(&m_camera->m_perspectiveCameraMaxTilt, sizeof(CFloat), 1, filePtr);

		fclose(filePtr);

		if (!foundTarget)
			g_characterProfiles.push_back(m_name);
	}
	else
	{
		FILE *filePtr;
		filePtr = fopen(CharacterProfilePath, "rb");
		if (!filePtr)
		{
			MessageBox("Couldn't open the file to save data!", "Vanda Engine Error", MB_OK | MB_ICONERROR);
			return;
		}
		CPhysXCameraType characterCameraType;
		fread(&characterCameraType, sizeof(CPhysXCameraType), 1, filePtr);
		ex_pMainCharacterDlg->SetCharacterCameraType(characterCameraType);

		fread(g_currentPrefabPackageName, sizeof(CChar), MAX_NAME_SIZE, filePtr);
		fread(g_currentPrefabName, sizeof(CChar), MAX_NAME_SIZE, filePtr);

		fread(m_characterName, sizeof(CChar), MAX_NAME_SIZE, filePtr);
		ex_pMainCharacterDlg->SetCharacterName(m_characterName);

		fread(&m_position, sizeof(CVec3f), 1, filePtr);
		ex_pMainCharacterDlg->SetCharacterPosition(m_position);

		fread(&m_scale, sizeof(CFloat), 1, filePtr);
		ex_pMainCharacterDlg->SetCharacterScale(m_scale);

		fread(&m_delayIdle, sizeof(CFloat), 1, filePtr);
		ex_pMainCharacterDlg->SetCharacterPlayMoreIdlesEveryXSeconds(m_delayIdle);

		CUInt idleSize;
		CUInt walkSize;
		CUInt runSize;
		CUInt jumpSize;
		m_idle.clear();
		m_run.clear();
		m_walk.clear();
		m_jump.clear();

		fread(&idleSize, sizeof(CUInt), 1, filePtr);
		for (CUInt i = 0; i < idleSize; i++)
		{
			CChar name[MAX_NAME_SIZE];
			fread(name, sizeof(CChar), MAX_NAME_SIZE, filePtr);
			m_idle.push_back(name);
		}
		ex_pMainCharacterDlg->SetIdle(m_idle);

		fread(&walkSize, sizeof(CUInt), 1, filePtr);
		for (CUInt i = 0; i < walkSize; i++)
		{
			CChar name[MAX_NAME_SIZE];
			fread(name, sizeof(CChar), MAX_NAME_SIZE, filePtr);
			m_walk.push_back(name);
		}
		ex_pMainCharacterDlg->SetWalk(m_walk);

		fread(&jumpSize, sizeof(CUInt), 1, filePtr);
		for (CUInt i = 0; i < jumpSize; i++)
		{
			CChar name[MAX_NAME_SIZE];
			fread(name, sizeof(CChar), MAX_NAME_SIZE, filePtr);
			m_jump.push_back(name);
		}
		ex_pMainCharacterDlg->SetJump(m_jump);

		fread(&runSize, sizeof(CUInt), 1, filePtr);
		for (CUInt i = 0; i < runSize; i++)
		{
			CChar name[MAX_NAME_SIZE];
			fread(name, sizeof(CChar), MAX_NAME_SIZE, filePtr);
			m_run.push_back(name);
		}
		ex_pMainCharacterDlg->SetRun(m_run);

		//write PhysX data here
		fread(&m_physXProperties.m_fCameraCharacterDistance, sizeof(CFloat), 1, filePtr);
		fread(&m_physXProperties.m_fCapsuleRadius, sizeof(CFloat), 1, filePtr);
		fread(&m_physXProperties.m_fCapsuleHeight, sizeof(CFloat), 1, filePtr);
		fread(&m_physXProperties.m_fCharacterPower, sizeof(CFloat), 1, filePtr);
		fread(&m_physXProperties.m_fCharacterWalkSpeed, sizeof(CFloat), 1, filePtr);
		fread(&m_physXProperties.m_fCharacterRunSpeed, sizeof(CFloat), 1, filePtr);
		fread(&m_physXProperties.m_fCharacterSlopeLimit, sizeof(CFloat), 1, filePtr);
		fread(&m_physXProperties.m_fCharacterSkinWidth, sizeof(CFloat), 1, filePtr);
		fread(&m_physXProperties.m_fCharacterStepOffset, sizeof(CFloat), 1, filePtr);
		fread(&m_physXProperties.m_fJumpPower, sizeof(CFloat), 1, filePtr);
		fread(&m_physXProperties.m_bJumping, sizeof(CBool), 1, filePtr);
		fread(&m_physXProperties.m_bDebugMode, sizeof(CBool), 1, filePtr);

		ex_pMainCharacterDlg->SetPhysXProperties(m_physXProperties);

		fread(&m_characterBlendingProperties, sizeof(CCharacterBlendingProperties), 1, filePtr);
		ex_pMainCharacterDlg->SetCharacterBlendingProperties(m_characterBlendingProperties);

		GLdouble angle;
		GLdouble minAngle;
		GLdouble maxAngle;

		fread(&angle, sizeof(GLdouble), 1, filePtr);
		fread(&minAngle, sizeof(GLdouble), 1, filePtr);
		fread(&maxAngle, sizeof(GLdouble), 1, filePtr);

		m_camera->m_cameraManager->SetDefaultAngle(angle);
		m_camera->m_cameraManager->SetAngle(angle);
		m_camera->m_cameraManager->SetMinAngle(minAngle);
		m_camera->m_cameraManager->SetMaxAngle(maxAngle);

		fread(&m_camera->m_perspectiveCameraTilt, sizeof(CFloat), 1, filePtr);
		fread(&m_camera->m_perspectiveCameraMinTilt, sizeof(CFloat), 1, filePtr);
		fread(&m_camera->m_perspectiveCameraMaxTilt, sizeof(CFloat), 1, filePtr);

		ex_pMainCharacterDlg->SetCharacterCameraProperties(m_camera);

		fclose(filePtr);

	}
	CDialog::OnOK();
}

CVoid CSaveLoadCharacterProfile::SetCharacterCameraType(CPhysXCameraType type)
{
	m_characterType = type;
}

CChar* CSaveLoadCharacterProfile::GetName()
{
	return m_name;
}

CVoid CSaveLoadCharacterProfile::SetIdleName(std::vector<std::string> idle)
{
	m_idle = idle;
}

CVoid CSaveLoadCharacterProfile::SetWalkName(std::vector<std::string> walk)
{
	m_walk = walk;
}

CVoid CSaveLoadCharacterProfile::SetRunName(std::vector<std::string> run)
{
	m_run = run;
}

CVoid CSaveLoadCharacterProfile::SetJumpName(std::vector<std::string> jump)
{
	m_jump = jump;
}

CVoid CSaveLoadCharacterProfile::SetCharacterName(CChar* name)
{
	Cpy(m_characterName, name);
}

CVoid CSaveLoadCharacterProfile::SetPosition(CVec3f pos)
{
	m_position = pos;
}

CVoid CSaveLoadCharacterProfile::SetScale(CFloat scale)
{
	m_scale = scale;
}

CVoid CSaveLoadCharacterProfile::SetPlayMoreIdlesEveryXSeconds(CFloat delayIdle)
{
	m_delayIdle = delayIdle;
}

CVoid CSaveLoadCharacterProfile::SetPhysXProperties(CPhysXProperties physXProperties)
{
	m_physXProperties = physXProperties;
}

CVoid CSaveLoadCharacterProfile::SetCharacterBlendingProperties(CCharacterBlendingProperties properties)
{
	m_characterBlendingProperties = properties;
}

CVoid CSaveLoadCharacterProfile::SetCharacterCameraProperties(CUpdateCamera* properties)
{
	m_camera->m_cameraManager->SetDefaultAngle(properties->m_cameraManager->GetDefaultAngle());
	//m_camera->m_cameraManager->SetMinAngle(properties->m_cameraManager->GetMinAngle());
	//m_camera->m_cameraManager->SetMaxAngle(properties->m_cameraManager->GetMaxAngle());

	m_camera->m_perspectiveCameraTilt = properties->m_perspectiveCameraTilt;
	m_camera->m_perspectiveCameraMinTilt = properties->m_perspectiveCameraMinTilt;
	m_camera->m_perspectiveCameraMaxTilt = properties->m_perspectiveCameraMaxTilt;
}



