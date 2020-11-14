//Copyright (C) 2020 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

// AddResource.cpp : implementation file
//

#include "stdafx.h"
#include "VandaEngine1.h"
#include "AddResource.h"
#include "afxdialogex.h"
#include "AddNewDirectory.h"

// CAddResource dialog

IMPLEMENT_DYNAMIC(CAddResource, CDialog)

CAddResource::CAddResource(CWnd* pParent /*=NULL*/)
	: CDialog(CAddResource::IDD, pParent)
{
	m_index = 0;
	m_listIndex = -1;
}

CAddResource::~CAddResource()
{
}

void CAddResource::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMB_PACKAGE, m_comboDirectory);
	DDX_Control(pDX, IDC_LIST_RESOURCES, m_listFiles);
}


BEGIN_MESSAGE_MAP(CAddResource, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_NEW_DIRECTORY, &CAddResource::OnBnClickedButtonNewDirectory)
	ON_BN_CLICKED(IDC_BUTTON_REMOVE_DIRECTORY, &CAddResource::OnBnClickedButtonRemoveDirectory)
	ON_BN_CLICKED(IDC_BUTTON_ADD_RESOURCE, &CAddResource::OnBnClickedButtonAddResource)
	ON_BN_CLICKED(IDC_BUTTON_REMOVE_RESOURCE, &CAddResource::OnBnClickedButtonRemoveResource)
	ON_BN_CLICKED(IDOK, &CAddResource::OnBnClickedOk)
	ON_CBN_SELCHANGE(IDC_COMB_PACKAGE, &CAddResource::OnCbnSelchangeCombPackage)
END_MESSAGE_MAP()


// CAddResource message handlers


void CAddResource::OnBnClickedButtonNewDirectory()
{
	CAddNewDirectory* m_dlgNewDirectory = CNew(CAddNewDirectory);
	if (m_dlgNewDirectory->DoModal() == IDOK)
	{
		CChar name[MAX_NAME_SIZE];
		Cpy(name, m_dlgNewDirectory->GetDirectoryName());

		CChar NewDirectoryPath[MAX_NAME_SIZE];
		Cpy(NewDirectoryPath, g_currentProjectPath);
		Append(NewDirectoryPath, "Resources");
		CreateWindowsDirectory(NewDirectoryPath);
		Append(NewDirectoryPath, "/");
		Append(NewDirectoryPath, name);
		CreateWindowsDirectory(NewDirectoryPath);

		m_comboDirectory.InsertString(m_index, name);
		m_comboDirectory.SetCurSel(m_index);
		m_index++;

		m_listFiles.DeleteAllItems();

		g_projectResourceNames.push_back(std::vector<std::string>());
		//push new name to last element
		g_projectResourceNames[g_projectResourceNames.size() - 1].push_back(name);

		SaveResFile();
	}
	CDelete(m_dlgNewDirectory);
}


void CAddResource::OnBnClickedButtonRemoveDirectory()
{
	if (m_comboDirectory.GetCount() == 0)
	{
		MessageBox("Please create at least one directory!", "Report", MB_OK | MB_ICONINFORMATION);
		return;
	}
	CString currentString;
	m_comboDirectory.GetLBText(m_comboDirectory.GetCurSel(), currentString);

	CChar temp[MAX_NAME_SIZE];
	sprintf(temp, "Are you sure you want to delete the '%s' directory?\nThis will delete all files located in this directory.", currentString);
	if (MessageBox(temp, "Warning", MB_YESNO | MB_ICONINFORMATION) == IDYES)
	{
		for (CUInt i = 0; i < g_projectResourceNames.size(); i++)
		{
			if (Cmp(g_projectResourceNames[i].front().c_str(), currentString))
			{
				g_projectResourceNames[i].clear();
				g_projectResourceNames.erase(g_projectResourceNames.begin() + i);
				break;
			}
		}

		CChar NewDirectoryPath[MAX_NAME_SIZE];
		Cpy(NewDirectoryPath, g_currentProjectPath);
		Append(NewDirectoryPath, "Resources");
		Append(NewDirectoryPath, "/");
		Append(NewDirectoryPath, currentString.GetBuffer(currentString.GetLength()));
		RemoveAllFilesAndFoldersInDirectory(NewDirectoryPath);

		m_comboDirectory.DeleteString(m_comboDirectory.GetCurSel());
		m_index--;
		if (m_comboDirectory.GetCount() > 0)
		{
			m_comboDirectory.SetCurSel(0);
			m_comboDirectory.UpdateWindow();

			m_listFiles.DeleteAllItems();

			for (CUInt i = 0; i < g_projectResourceNames[0].size(); i++)
			{
				if (i == 0) continue;
				CChar str[MAX_NAME_SIZE];
				Cpy(str, g_projectResourceNames[0][i].c_str());
				InserItemToList(str);
			}

		}
		
		if (m_comboDirectory.GetCount() == 0)
		{
			m_listFiles.DeleteAllItems();
			m_listIndex = -1;
		}
		SaveResFile();
	}

}


void CAddResource::OnBnClickedButtonAddResource()
{
	if (m_comboDirectory.GetCount() == 0)
	{
		MessageBox("Please create a new directory!", "Vanda Engine Error", MB_OK | MB_ICONERROR);
		return;
	}

	CFileDialog dlgOpen(TRUE, _T("*.ogg"), _T(""), OFN_ALLOWMULTISELECT | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR,
		_T("Ogg, DDS, AVI (*.ogg; *.dds; *.avi; *.lua)|*.ogg; *.dds; *.avi; *.lua||"), NULL, NULL);
	if (IDOK == dlgOpen.DoModal())
	{
		CString currentString;
		m_comboDirectory.GetLBText(m_comboDirectory.GetCurSel(), currentString);

		CInt index = -1;
		for (CUInt i = 0; i < g_projectResourceNames.size(); i++)
		{
			if (Cmp(g_projectResourceNames[i].front().c_str(), currentString))
			{
				index = i;
				break;
			}
		}

		CString filePath;
		POSITION p = dlgOpen.GetStartPosition();
		int itemcnt = m_listFiles.GetItemCount();
		while (p)
		{
			filePath = dlgOpen.GetNextPathName(p);
			CChar name[MAX_NAME_SIZE];
			Cpy(name, filePath.GetBuffer(filePath.GetLength()));
			CChar* afterPathName = GetAfterPath(name);
			CBool foundTarget = CFalse;
			CChar foundItem[MAX_NAME_SIZE];
			for (CInt i = 0; i < m_listFiles.GetItemCount(); i++)
			{
				CString itemText = m_listFiles.GetItemText(i, 0);
				CChar itemName[MAX_NAME_SIZE];
				Cpy(itemName, itemText.GetBuffer(itemText.GetLength()));

				if (Cmp(afterPathName, itemName))
				{
					foundTarget = CTrue;
					Cpy(foundItem, itemName);
					break;
				}
			}
			CChar NewDirectoryPath[MAX_NAME_SIZE];
			Cpy(NewDirectoryPath, g_currentProjectPath);
			Append(NewDirectoryPath, "Resources");
			Append(NewDirectoryPath, "/");
			Append(NewDirectoryPath, currentString.GetBuffer(currentString.GetLength()));
			Append(NewDirectoryPath, "/");
			Append(NewDirectoryPath, afterPathName);

			if (!foundTarget)
			{

				if (!CopyFile(name, NewDirectoryPath, FALSE))
				{
					CChar temp[MAX_NAME_SIZE];
					sprintf(temp, "\n%s%d%s%s%s%s", "Error (", GetLastError(), ") Couldn't copy the file ", name, " to ", NewDirectoryPath);
					PrintInfo(temp, COLOR_RED);
				}
				else
				{
					InserItemToList(afterPathName);
					g_projectResourceNames[index].push_back(afterPathName);
				}
			}
			else
			{
				CChar temp[MAX_NAME_SIZE];
				sprintf(temp, "Item '%s' Already exists.\nNew item overwrites this item. Proceed?", foundItem);
				if (MessageBox(temp, "Warning", MB_YESNO | MB_ICONINFORMATION) == IDYES)
				{
					if (!CopyFile(name, NewDirectoryPath, FALSE))
					{
						CChar temp[MAX_NAME_SIZE];
						sprintf(temp, "\n%s%d%s%s%s%s", "Error (", GetLastError(), ") Couldn't copy the file ", name, " to ", NewDirectoryPath);
						PrintInfo(temp, COLOR_RED);
					}
				}
			}
		}
		SaveResFile();
	}
}


void CAddResource::OnBnClickedButtonRemoveResource()
{
	int nSelected = -1;
	POSITION p = m_listFiles.GetFirstSelectedItemPosition();
	while (p)
	{
		nSelected = m_listFiles.GetNextSelectedItem(p);
	}
	if (nSelected >= 0)
	{
		TCHAR szBuffer[1024];
		DWORD cchBuf(1024);
		LVITEM lvi;
		lvi.iItem = nSelected;
		lvi.iSubItem = 0;
		lvi.mask = LVIF_TEXT;
		lvi.pszText = szBuffer;
		lvi.cchTextMax = cchBuf;
		m_listFiles.GetItem(&lvi);

		CChar temp[MAX_NAME_SIZE];
		sprintf(temp, "Are you sure you want to delete '%s'?", szBuffer);
		if (MessageBox(temp, "Warning", MB_YESNO | MB_ICONINFORMATION) == IDYES)
		{
			CString currentString;
			m_comboDirectory.GetLBText(m_comboDirectory.GetCurSel(), currentString);

			CChar fileName[MAX_NAME_SIZE];
			Cpy(fileName, g_currentProjectPath);
			Append(fileName, "Resources");
			Append(fileName, "/");
			Append(fileName, currentString.GetBuffer(currentString.GetLength()));
			Append(fileName, "/");
			Append(fileName, szBuffer);

			//delete item
			DeleteFile(fileName);
			m_listFiles.DeleteItem(nSelected);
			m_listIndex--;

			CInt index = -1;
			for (CUInt i = 0; i < g_projectResourceNames.size(); i++)
			{
				if (Cmp(g_projectResourceNames[i].front().c_str(), currentString))
				{
					index = i;
					break;
				}
			}

			for (CUInt i = 0; i < g_projectResourceNames[index].size(); i++)
			{
				if (i == 0) continue;
				if (Cmp(g_projectResourceNames[index][i].c_str(), szBuffer))
				{
					g_projectResourceNames[index].erase(g_projectResourceNames[index].begin() + i);
				}
			}

		}
		SaveResFile();
	}
	else
	{
		MessageBox("Please Select an Item!", "Report", MB_OK | MB_ICONINFORMATION);
		return;
	}
}

void CAddResource::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialog::OnOK();
}

BOOL CAddResource::OnInitDialog()
{
	CDialog::OnInitDialog();

	for (CUInt i = 0; i < g_projectResourceNames.size(); i++)
	{
		g_projectResourceNames[i].clear();
	}
	g_projectResourceNames.clear();

	//load project files
	FILE* filePtr;
	CChar fileName[MAX_NAME_SIZE];
	Cpy(fileName, g_currentProjectPath);
	Append(fileName, "Resources");
	Append(fileName, "/resources.res");

	filePtr = fopen(fileName, "rb");
	if (filePtr)
	{
		CUInt size;
		fread(&size, sizeof(CUInt), 1, filePtr);

		for (CUInt i = 0; i < size; i++)
		{
			g_projectResourceNames.push_back(std::vector<std::string>());

			CUInt row_size;
			fread(&row_size, sizeof(CUInt), 1, filePtr);
			for (CUInt j = 0; j < row_size; j++)
			{
				CChar name[MAX_NAME_SIZE];
				fread(name, sizeof(CChar), MAX_NAME_SIZE, filePtr);
				g_projectResourceNames[i].push_back(name);
			}
		}
		fclose(filePtr);
	}

	RECT rect;
	m_listFiles.GetClientRect(&rect);

	m_listFiles.InsertColumn(0, "File Names", LVCFMT_LEFT, rect.right - rect.left, 0);
	m_listFiles.SetExtendedStyle(LVS_EX_INFOTIP | LVS_EX_ONECLICKACTIVATE | LVS_EX_LABELTIP);

	for (CUInt i = 0; i < g_projectResourceNames.size(); i++)
	{
		CChar str[MAX_NAME_SIZE];
		Cpy(str, g_projectResourceNames[i].front().c_str());
		m_comboDirectory.InsertString(m_index, str);
		m_index++;
	}
	if (g_projectResourceNames.size())
	{
		m_comboDirectory.SetCurSel(0);

		for (CUInt i = 0; i < g_projectResourceNames[0].size(); i++)
		{
			if (i == 0) continue;
			CChar str[MAX_NAME_SIZE];
			Cpy(str, g_projectResourceNames[0][i].c_str());
			InserItemToList(str);
		}
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

CVoid CAddResource::InserItemToList(char * name)
{
	m_listIndex++;
	LVITEM lvItem;
	lvItem.mask = LVIF_TEXT;
	lvItem.iItem = m_listIndex;
	lvItem.iSubItem = 0;
	lvItem.pszText = name;
	m_listFiles.InsertItem(&lvItem);
	m_listFiles.SetItemState(m_listIndex, LVIS_SELECTED, LVIS_SELECTED | LVIS_FOCUSED);
	m_listFiles.EnsureVisible(0, FALSE);
}

void CAddResource::OnCbnSelchangeCombPackage()
{
	CString currentString;
	m_comboDirectory.GetLBText(m_comboDirectory.GetCurSel(), currentString);

	CInt index = -1;
	for (CInt i = 0; i < (CInt)g_projectResourceNames.size(); i++)
	{
		if (Cmp(g_projectResourceNames[i].front().c_str(), currentString))
		{
			index = i;
			break;
		}
	}
	if (index != -1)
	{
		m_listIndex = -1;
		m_listFiles.DeleteAllItems();
		for (CUInt i = 0; i < g_projectResourceNames[index].size(); i++)
		{
			if (i == 0) continue;
			CChar str[MAX_NAME_SIZE];
			Cpy(str, g_projectResourceNames[index][i].c_str());
			InserItemToList(str);
		}
	}
}

CVoid CAddResource::SaveResFile()
{
	FILE* filePtr;
	CChar fileName[MAX_NAME_SIZE];
	Cpy(fileName, g_currentProjectPath);
	Append(fileName, "Resources");
	Append(fileName, "/resources.res");

	filePtr = fopen(fileName, "wb");
	if (filePtr)
	{
		CUInt size = g_projectResourceNames.size();
		fwrite(&size, sizeof(CUInt), 1, filePtr);

		for (CUInt i = 0; i < g_projectResourceNames.size(); i++)
		{
			CUInt row_size = g_projectResourceNames[i].size();
			fwrite(&row_size, sizeof(CUInt), 1, filePtr);
			for (CUInt j = 0; j < row_size; j++)
			{
				CChar name[MAX_NAME_SIZE];
				Cpy(name, g_projectResourceNames[i][j].c_str());
				fwrite(name, sizeof(CChar), MAX_NAME_SIZE, filePtr);
			}
		}
		fclose(filePtr);
	}

	///////////////////

}