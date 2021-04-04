// ScriptUtilityResources.cpp : implementation file
//

#include "stdafx.h"
#include "VandaEngine1.h"
#include "ScriptUtilityResources.h"
#include "afxdialogex.h"


// CScriptUtilityResources dialog

IMPLEMENT_DYNAMIC(CScriptUtilityResources, CDialog)

CScriptUtilityResources::CScriptUtilityResources(CWnd* pParent /*=NULL*/)
	: CDialog(CScriptUtilityResources::IDD, pParent)
{
	m_listIndex = -1;
}

CScriptUtilityResources::~CScriptUtilityResources()
{
	for (CUInt i = 0; i < m_projectResourceNames.size(); i++)
	{
		m_projectResourceNames[i].clear();
	}
	m_projectResourceNames.clear();
}

void CScriptUtilityResources::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_RESOURCE_FILES, m_listResourceFiles);
	DDX_Control(pDX, IDC_COMB_RESOURCE_FOLDER, m_comboResourceFolder);
	DDX_Control(pDX, IDC_STATIC_PROJECT_VSCENE_NAME, m_textProjectVSceneName);
	DDX_Control(pDX, IDC_RICHED_RESOURCE_FOLDER_NAME, m_richFolderName);
	DDX_Control(pDX, IDC_RICHED_RESOURCE_FILE_NAME, m_richFileName);
	DDX_Control(pDX, IDC_RICHED_RESOURCE_FOLDER_FILE_NAME, m_richFolderFileName);
	DDX_Control(pDX, IDC_BUTTON_COPY_RESOURCE_FOLDER, m_btnFolderName);
	DDX_Control(pDX, IDC_BUTTON_COPY_RESOURCE_FILE, m_btnFileName);
	DDX_Control(pDX, IDC_BUTTON_COPY_RESOURCE_FOLDER_FILE, m_btnFolderFileName);
}


BEGIN_MESSAGE_MAP(CScriptUtilityResources, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_COPY_RESOURCE_FOLDER, &CScriptUtilityResources::OnBnClickedButtonCopyResourceFolder)
	ON_BN_CLICKED(IDC_BUTTON_COPY_RESOURCE_FILE, &CScriptUtilityResources::OnBnClickedButtonCopyResourceFile)
	ON_BN_CLICKED(IDC_BUTTON_COPY_RESOURCE_FOLDER_FILE, &CScriptUtilityResources::OnBnClickedButtonCopyResourceFolderFile)
	ON_CBN_SELCHANGE(IDC_COMB_RESOURCE_FOLDER, &CScriptUtilityResources::OnCbnSelchangeCombResourceFolder)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_RESOURCE_FILES, &CScriptUtilityResources::OnLvnItemchangedListResourceFiles)
END_MESSAGE_MAP()


// CScriptUtilityResources message handlers


void CScriptUtilityResources::OnBnClickedButtonCopyResourceFolder()
{
	CString s;
	m_richFolderName.GetWindowTextA(s);
	if (s.IsEmpty())
		MessageBox("Please select a folder!", "Error", MB_OK | MB_ICONERROR);
	else
	{
		m_richFolderName.Copy();
		CChar message[MAX_URI_SIZE];
		sprintf(message, "Folder name '%s' copied to clipboard", s);
		MessageBox(message, "Report", MB_OK | MB_ICONINFORMATION);
	}
}


void CScriptUtilityResources::OnBnClickedButtonCopyResourceFile()
{
	CString s;
	m_richFileName.GetWindowTextA(s);
	if (s.IsEmpty())
		MessageBox("Please select a file from the list!", "Error", MB_OK | MB_ICONERROR);
	else
	{
		m_richFileName.Copy();
		CChar message[MAX_URI_SIZE];
		sprintf(message, "File name '%s' copied to clipboard", s);
		MessageBox(message, "Report", MB_OK | MB_ICONINFORMATION);
	}
}


void CScriptUtilityResources::OnBnClickedButtonCopyResourceFolderFile()
{
	CString s;
	m_richFolderFileName.GetWindowTextA(s);
	if (s.IsEmpty())
		MessageBox("Please select folder and file", "Error", MB_OK | MB_ICONERROR);
	else
	{
		m_richFolderFileName.Copy();
		CChar message[MAX_URI_SIZE];
		sprintf(message, "'%s' name copied to clipboard", s);
		MessageBox(message, "Report", MB_OK | MB_ICONINFORMATION);
	}
}

CVoid CScriptUtilityResources::SetSelectedProjectAndVSceneNames(CChar* projectName)
{
	Cpy(m_projectName, projectName);
}


BOOL CScriptUtilityResources::OnInitDialog()
{
	CDialog::OnInitDialog();

	CChar text[MAX_NAME_SIZE];
	sprintf(text, "Project: %s", m_projectName);
	m_textProjectVSceneName.SetWindowTextA(text);

	CChar DocumentPath[MAX_URI_SIZE];
	SHGetFolderPath(NULL, CSIDL_PERSONAL, NULL, SHGFP_TYPE_CURRENT, DocumentPath);
	sprintf(m_projectFilePath, "%s%s%s%s", DocumentPath, "/Vanda/Projects/", m_projectName, "/Resources/resources.res");

	FILE* filePtr;
	filePtr = fopen(m_projectFilePath, "rb");
	if (filePtr)
	{
		CUInt size;
		fread(&size, sizeof(CUInt), 1, filePtr);

		for (CUInt i = 0; i < size; i++)
		{
			m_projectResourceNames.push_back(std::vector<std::string>());

			CUInt row_size;
			fread(&row_size, sizeof(CUInt), 1, filePtr);
			for (CUInt j = 0; j < row_size; j++)
			{
				CChar name[MAX_NAME_SIZE];
				fread(name, sizeof(CChar), MAX_NAME_SIZE, filePtr);
				m_projectResourceNames[i].push_back(name);
			}
		}
		fclose(filePtr);
	}

	RECT rect;
	m_listResourceFiles.GetClientRect(&rect);

	m_listResourceFiles.InsertColumn(0, "File Names", LVCFMT_LEFT, rect.right - rect.left, 0);
	m_listResourceFiles.SetExtendedStyle(LVS_EX_INFOTIP | LVS_EX_ONECLICKACTIVATE | LVS_EX_LABELTIP);

	CInt m_index = 0;
	for (CUInt i = 0; i < m_projectResourceNames.size(); i++)
	{
		CChar str[MAX_NAME_SIZE];
		Cpy(str, m_projectResourceNames[i].front().c_str());
		m_comboResourceFolder.InsertString(m_index, str);
		m_index++;
	}
	if (m_projectResourceNames.size())
	{
		m_comboResourceFolder.SetCurSel(0);

		for (CUInt i = 0; i < m_projectResourceNames[0].size(); i++)
		{
			if (i == 0) continue;
			CChar str[MAX_NAME_SIZE];
			Cpy(str, m_projectResourceNames[0][i].c_str());
			InserItemToList(str);
		}
	}
	if (m_comboResourceFolder.GetCount())
	{
		CString currentComboString;
		m_comboResourceFolder.GetLBText(m_comboResourceFolder.GetCurSel(), currentComboString);

		m_richFolderName.SetWindowTextA(currentComboString);
		CInt end = m_richFolderName.GetWindowTextLengthA();
		m_richFolderName.SetSel(0, end);
	}
	else
	{
		m_btnFolderName.EnableWindow(FALSE);
		m_btnFolderFileName.EnableWindow(FALSE);
		m_btnFileName.EnableWindow(FALSE);
	}

	if (m_listResourceFiles.GetItemCount())
	{
		m_listResourceFiles.SetItemState(0, LVIS_SELECTED, LVIS_SELECTED | LVIS_FOCUSED);
		m_listResourceFiles.SetSelectionMark(0);
	}
	else
	{
		m_btnFolderFileName.EnableWindow(FALSE);
		m_btnFileName.EnableWindow(FALSE);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

CVoid CScriptUtilityResources::InserItemToList(char * name)
{
	m_listIndex++;
	LVITEM lvItem;
	lvItem.mask = LVIF_TEXT;
	lvItem.iItem = m_listIndex;
	lvItem.iSubItem = 0;
	lvItem.pszText = name;
	m_listResourceFiles.InsertItem(&lvItem);
	m_listResourceFiles.EnsureVisible(0, FALSE);
}

void CScriptUtilityResources::OnCbnSelchangeCombResourceFolder()
{
	CString currentComboString;
	m_comboResourceFolder.GetLBText(m_comboResourceFolder.GetCurSel(), currentComboString);

	m_richFolderName.SetWindowTextA(currentComboString);
	CInt end = m_richFolderName.GetWindowTextLengthA();
	m_richFolderName.SetSel(0, end);

	CInt index = -1;
	for (CInt i = 0; i < (CInt)m_projectResourceNames.size(); i++)
	{
		if (Cmp(m_projectResourceNames[i].front().c_str(), currentComboString))
		{
			index = i;
			break;
		}
	}
	if (index != -1)
	{
		m_listIndex = -1;
		m_listResourceFiles.DeleteAllItems();
		for (CUInt i = 0; i < m_projectResourceNames[index].size(); i++)
		{
			if (i == 0) continue;
			CChar str[MAX_NAME_SIZE];
			Cpy(str, m_projectResourceNames[index][i].c_str());
			InserItemToList(str);
		}
	}

	if (m_listResourceFiles.GetItemCount())
	{
		m_listResourceFiles.SetItemState(0, LVIS_SELECTED, LVIS_SELECTED | LVIS_FOCUSED);
		m_listResourceFiles.SetSelectionMark(0);

		m_btnFolderFileName.EnableWindow(TRUE);
		m_btnFileName.EnableWindow(TRUE);
	}
	else
	{
		m_btnFolderFileName.EnableWindow(FALSE);
		m_btnFileName.EnableWindow(FALSE);
	}
}


void CScriptUtilityResources::OnLvnItemchangedListResourceFiles(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	int nSelected = -1;
	POSITION p = m_listResourceFiles.GetFirstSelectedItemPosition();
	while (p)
	{
		nSelected = m_listResourceFiles.GetNextSelectedItem(p);
	}
	TCHAR fileName[1024];

	if (nSelected >= 0)
	{
		DWORD cchBuf(1024);
		LVITEM lvi;
		lvi.iItem = nSelected;
		lvi.iSubItem = 0;
		lvi.mask = LVIF_TEXT;
		lvi.pszText = fileName;
		lvi.cchTextMax = cchBuf;
		m_listResourceFiles.GetItem(&lvi);

		m_richFileName.SetWindowTextA(fileName);
		CInt end = m_richFileName.GetWindowTextLengthA();
		m_richFileName.SetSel(0, end);

		CString currentComboString;
		m_comboResourceFolder.GetLBText(m_comboResourceFolder.GetCurSel(), currentComboString);
		
		CChar folderName[MAX_NAME_SIZE];
		Cpy(folderName, currentComboString.GetBuffer(currentComboString.GetLength()));
		currentComboString.ReleaseBuffer();

		CChar folderAndFileName[MAX_NAME_SIZE];
		sprintf(folderAndFileName, "%s_%s", folderName, fileName);

		m_richFolderFileName.SetWindowTextA(folderAndFileName);
		end = m_richFolderFileName.GetWindowTextLengthA();
		m_richFolderFileName.SetSel(0, end);

	}
	else
	{
		m_richFileName.SetWindowTextA("");
		m_richFileName.SetSel(0, 0);

		m_richFolderFileName.SetWindowTextA("");
		m_richFolderFileName.SetSel(0, 0);
	}

	*pResult = 0;
}
