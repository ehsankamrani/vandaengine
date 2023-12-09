//Copyright (C) 2023 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

// ScriptEditor.cpp : implementation file
//

#include "stdafx.h"
#include "VandaEngineEditor.h"
#include "ScriptEditor.h"
#include "afxdialogex.h"
#include "ScriptUtility.h"
#include "ScriptEditorAddEvent.h"
#include "ScriptEditorAddFunction.h"
// CScriptEditor dialog

IMPLEMENT_DYNAMIC(CScriptEditor, CDialog)

CScriptEditor::CScriptEditor(CWnd* pParent /*=NULL*/)
	: CDialog(CScriptEditor::IDD, pParent)
{
	m_changed = CFalse;
}

CScriptEditor::~CScriptEditor()
{
}

void CScriptEditor::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RICHED_REPORT, m_richReport);
	DDX_Control(pDX, IDC_RICHED_SCRIPT_EDITOR, m_richScriptEditor);
}


BEGIN_MESSAGE_MAP(CScriptEditor, CDialog)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_CANCEL, &CScriptEditor::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, &CScriptEditor::OnBnClickedOk)
	ON_EN_CHANGE(IDC_RICHED_SCRIPT_EDITOR, &CScriptEditor::OnEnChangeRichedScriptEditor)
	ON_WM_NCDESTROY()
	ON_WM_CREATE()
END_MESSAGE_MAP()


// CScriptEditor message handlers

void CScriptEditor::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	CDialog::OnClose();
}


void CScriptEditor::OnBnClickedCancel()
{
	ex_pVandaEngineDlg->ClearObjectNames();
	OnCancel();
}


BOOL CScriptEditor::OnInitDialog()
{
	ex_pVandaEngineDlg->LoadObjectNames(); //this will initialize object properties for scripts

	CDialog::OnInitDialog();

	CMenu menu;
	menu.LoadMenu(IDR_MENU5);
	SetMenu(&menu);
	menu.Detach();

	CHARFORMAT cfDefault;
	cfDefault.cbSize = sizeof(cfDefault);
	cfDefault.dwEffects = CFE_PROTECTED;
	cfDefault.dwMask = CFM_BOLD | CFM_FACE | CFM_SIZE | CFM_CHARSET | CFM_PROTECTED | CFM_COLOR;
	cfDefault.yHeight = 10 * 20;
	cfDefault.crTextColor = RGB(0, 0, 0);
	cfDefault.bCharSet = 0;
	strcpy(cfDefault.szFaceName, _T("Consolas"));// or "Times New Roman" etc etc

	m_richScriptEditor.SetDefaultCharFormat(cfDefault);
	m_richScriptEditor.SetEventMask(ENM_CHANGE | ENM_SELCHANGE | ENM_PROTECTED);
	m_richScriptEditor.SetBackgroundColor(FALSE, RGB(255, 255, 255));
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CScriptEditor::OnBnClickedOk()
{
	if (!SaveChanges())
		return;
	ex_pVandaEngineDlg->ClearObjectNames();
	CDialog::OnOK();
}


BOOL CScriptEditor::OnCommand(WPARAM wParam, LPARAM lParam)
{
	// TODO: Add your specialized code here and/or call the base class
	if (wParam == ID_NEWSCRIPT_BLANK)
	{
		if (!SaveChanges())
			return CDialog::OnCommand(wParam, lParam);
		savePath.Empty();
		m_richScriptEditor.SetWindowTextA("");
		m_changed = CFalse;
		SetWindowText("Script Editor - Untitled");
	}
	else if (wParam == ID_NEWSCRIPT_VSCENE_SCRIPT)
	{
		if (!SaveChanges())
			return CDialog::OnCommand(wParam, lParam);
		savePath.Empty();
		LoadFile("Assets/Engine/Scripts/VSceneScript.txt");
		SetWindowText("Script Editor - Untitled");
	}
	else if (wParam == ID_NEWSCRIPT_PREFAB)
	{
		if (!SaveChanges())
			return CDialog::OnCommand(wParam, lParam);
		savePath.Empty();
		LoadFile("Assets/Engine/Scripts/Prefab.txt");
		SetWindowText("Script Editor - Untitled");
	}
	else if (wParam == ID_NEWSCRIPT_TRIGGER)
	{
		if (!SaveChanges())
			return CDialog::OnCommand(wParam, lParam);
		savePath.Empty();
		LoadFile("Assets/Engine/Scripts/Trigger.txt");
		SetWindowText("Script Editor - Untitled");
	}
	else if (wParam == ID_NEWSCRIPT_VIDEO)
	{
		if (!SaveChanges())
			return CDialog::OnCommand(wParam, lParam);
		savePath.Empty();
		LoadFile("Assets/Engine/Scripts/Video.txt");
		SetWindowText("Script Editor - Untitled");
	}
	else if (wParam == ID_NEWSCRIPT_BUTTON)
	{
		if (!SaveChanges())
			return CDialog::OnCommand(wParam, lParam);
		savePath.Empty();
		LoadFile("Assets/Engine/Scripts/GUI.txt");
		SetWindowText("Script Editor - Untitled");
	}
	else if (wParam == ID_NEWSCRIPT_MAINCHARACTER)
	{
		if (!SaveChanges())
			return CDialog::OnCommand(wParam, lParam);
		savePath.Empty();
		LoadFile("Assets/Engine/Scripts/MainCharacter.txt");
		SetWindowText("Script Editor - Untitled");
	}
	else if (wParam == ID_FILE_OPEN_SCRIPT)
	{
		if (!SaveChanges())
			return CDialog::OnCommand(wParam, lParam);
		savePath.Empty();

		CFileDialog dlgOpen(TRUE, _T("*.lua"), _T(""), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR,
			_T("LUA File (*.lua)|*.lua||"), NULL, NULL);
		if (IDOK == dlgOpen.DoModal())
		{
			LoadFile(dlgOpen.GetPathName().GetBuffer(dlgOpen.GetPathName().GetLength()));
			dlgOpen.GetPathName().ReleaseBuffer();
			savePath = dlgOpen.GetPathName();

			CChar title[MAX_NAME_SIZE];
			sprintf(title, "Script Editor - %s", dlgOpen.GetFileName().GetBuffer(dlgOpen.GetFileName().GetLength()));
			SetWindowText(title);
			dlgOpen.GetFileName().ReleaseBuffer();
		}
		m_changed = CFalse;
	}
	else if (wParam == ID_FILE_SAVE_SCRIPT)
	{
		if (!savePath.IsEmpty())
		{
			WriteFile(savePath.GetBuffer(savePath.GetLength()));
			savePath.ReleaseBuffer();
		}
		else
		{
			CFileDialog dlgSave(FALSE, _T("*.lua"), _T(""), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR,
				_T("LUA File (*.lua)|*.lua||"), NULL, NULL);
			if (IDOK == dlgSave.DoModal())
			{
				WriteFile(dlgSave.GetPathName().GetBuffer(dlgSave.GetPathName().GetLength()));
				dlgSave.GetPathName().ReleaseBuffer();
				savePath = dlgSave.GetPathName();

				CChar title[MAX_NAME_SIZE];
				sprintf(title, "Script Editor - %s", dlgSave.GetFileName().GetBuffer(dlgSave.GetFileName().GetLength()));
				SetWindowText(title);
				dlgSave.GetFileName().ReleaseBuffer();
			}
		}
		m_changed = CFalse;
	}
	else if (wParam == ID_FILE_SAVEAS_SCRIPT)
	{
		CFileDialog dlgSave(FALSE, _T("*.lua"), _T(""), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR,
			_T("LUA File (*.lua)|*.lua||"), NULL, NULL);
		if (IDOK == dlgSave.DoModal())
		{
			WriteFile(dlgSave.GetPathName().GetBuffer(dlgSave.GetPathName().GetLength()));
			dlgSave.GetPathName().ReleaseBuffer();
			savePath = dlgSave.GetPathName();
			m_changed = CFalse;

			CChar title[MAX_NAME_SIZE];
			sprintf(title, "Script Editor - %s", dlgSave.GetFileName().GetBuffer(dlgSave.GetFileName().GetLength()));
			SetWindowText(title);
			dlgSave.GetFileName().ReleaseBuffer();
		}
	}
	else if (wParam == ID_FILE_EXIT)
	{
		OnBnClickedOk();
	}
	else if (wParam == ID_EDIT_UNDO_SCRIPT)
	{
		m_richScriptEditor.Undo();
	}
	else if (wParam == ID_EDIT_REDO_SCRIPT)
	{
		m_richScriptEditor.Redo();
	}
	else if (wParam == ID_EDIT_COPY_SCRIPT)
	{
		m_richScriptEditor.Copy();
	}
	else if (wParam == ID_EDIT_PASTE_SCRIPT)
	{
		m_richScriptEditor.PasteSpecial(CF_TEXT);
	}
	else if (wParam == ID_DEBUG_STARTDEBUGGING)
	{
		m_richReport.SetWindowTextA("");
		CString string;
		m_richScriptEditor.GetWindowTextA(string);
		const char* buffer = (LPCTSTR)string;
		g_testScript = CTrue;
		int s = luaL_loadbuffer(g_lua, buffer, strlen(buffer), "buffer");
		if (s == 0) {
			// execute Lua program
			s = LuaExecuteProgram(g_lua);
		}
		if (s != 0) {
			PrintScriptInfo(lua_tostring(g_lua, -1), COLOR_RED);
			lua_pop(g_lua, 1); // remove error message
		}
		if (s == 0)
		{
			PrintScriptInfo("No errors found", COLOR_GREEN);
		}
		g_testScript = CFalse;
	}
	else if (wParam == ID_TOOLS_SCRIPTUTILITY)
	{
		CScriptUtility* dlg = CNew(CScriptUtility);
		dlg->DoModal();
		CDelete(dlg);
	}
	else if (wParam == ID_TOOLS_ADDEVENT)
	{
		CScriptEditorAddEvent* dlg = CNew(CScriptEditorAddEvent);
		if(dlg->DoModal() == IDOK)
			m_richScriptEditor.PasteSpecial(CF_TEXT);
		CDelete(dlg);
	}
	else if (wParam == ID_TOOLS_ADDFUNCTION)
	{
		CScriptEditorAddFunction* dlg = CNew(CScriptEditorAddFunction);
		if (dlg->DoModal() == IDOK)
			m_richScriptEditor.PasteSpecial(CF_TEXT);
		CDelete(dlg);

	}
	else if (wParam == ID_HELP_SCRIPT_REFERENCE_MANUAL_CHM)
	{
		ShellExecute(NULL, "open", "Assets\\Docs\\VandaEngineScriptingReferenceManual.chm", NULL, NULL, SW_SHOWNORMAL);
	}
	else if (wParam == ID_HELP_SCRIPT_REFERENCE_MANUAL_PDF)
	{
		ShellExecute(NULL, "open", "Assets\\Docs\\VandaEngineScriptingReferenceManual.pdf", NULL, NULL, SW_SHOWNORMAL);
	}
	else if (wParam == ID_HELP_ONLINEHELP)
	{
		ShellExecute(NULL, "open", "https://vanda3d.org/scripting-reference-manual/", NULL, NULL, SW_SHOWNORMAL);
	}
	
	return CDialog::OnCommand(wParam, lParam);
}

CVoid CScriptEditor::LoadFile(CChar* filePath)
{
	m_buffer.clear();
	std::ifstream file(filePath, std::ios::binary);

	if (file.is_open())
	{
		file.seekg(0, std::ios::end);

		std::ifstream::pos_type fileSize = file.tellg();

		m_buffer.resize(fileSize);
		file.seekg(0, std::ios::beg);
		file.read(&m_buffer[0], fileSize);
	}
	else
	{
		MessageBox("Couldn't open the file", "Vanda Engine Error", MB_OK | MB_ICONERROR);
		return;
	}

	CString c1(m_buffer.c_str());
	// writing the file to rich edit control
	m_richScriptEditor.SetWindowTextA(c1.GetBuffer());

	return;
}

CVoid CScriptEditor::WriteFile(CChar* filePath)
{
	CString c1;
	m_richScriptEditor.GetWindowTextA(c1);
	std::ofstream file(filePath, std::ios::binary);
	if (file.is_open())
	{
		file << c1.GetBuffer(c1.GetLength());
		c1.ReleaseBuffer();
		file.close();
	}
	else
	{
		MessageBox("Couldn't open the file", "Vanda Engine Error", MB_OK | MB_ICONERROR);
		return;
	}
}

CBool CScriptEditor::SaveChanges()
{
	if (m_changed)
	{
		CInt iResponse = MessageBox("Do you want to save your changes?", "Warning", MB_YESNOCANCEL | MB_ICONSTOP);
		if (iResponse == IDYES) //save changes
		{
			if (savePath.IsEmpty())
			{
				CFileDialog dlgSave(FALSE, _T("*.lua"), _T(""), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR,
					_T("LUA File (*.lua)|*.lua||"), NULL, NULL);
				if (IDOK == dlgSave.DoModal())
				{
					WriteFile(dlgSave.GetPathName().GetBuffer(dlgSave.GetPathName().GetLength()));
					dlgSave.GetPathName().ReleaseBuffer();
				}
			}
			else
			{
				WriteFile(savePath.GetBuffer(savePath.GetLength()));
				savePath.ReleaseBuffer();
			}
			return CTrue;
		}
		else if (iResponse == IDNO)
		{
			return CTrue;
		}
		else if (iResponse == IDCANCEL)
		{
			return CFalse;
		}
	}
	return CTrue;
}

void CScriptEditor::OnEnChangeRichedScriptEditor()
{
	m_changed = CTrue;
}

CVoid CScriptEditor::PrintScriptInfo(CString strText, COLORREF color)
{
	CInt reportCounter = 1;
	CChar temp[MAX_NAME_SIZE];
	if (reportCounter != 1)
		sprintf(temp, "\n%i> %s", reportCounter, strText.GetString());
	else
		sprintf(temp, "%i> %s", reportCounter, strText.GetString());

	CHARFORMAT2 cf;
	cf.dwMask = CFM_COLOR | CFM_FACE;
	cf.dwEffects = NULL;
	cf.crTextColor = color;
	Cpy(cf.szFaceName, "Consolas");
	//cf.yHeight = CInt( rect.bottom - rect.top ) * 10.5 ;

	CInt nSel = m_richReport.GetWindowTextLength();
	m_richReport.SetSel(nSel, nSel);

	m_richReport.SetSelectionCharFormat(cf);
	m_richReport.ReplaceSel(temp);
	m_richReport.UpdateData(TRUE);
	m_richReport.UpdateWindow();

	reportCounter++;
}

void CScriptEditor::OnNcDestroy()
{
	CDialog::OnNcDestroy();
	delete this;
	// TODO: Add your message handler code here
}


void CScriptEditor::OnCancel()
{
	// TODO: Add your specialized code here and/or call the base class
	DestroyWindow();
}


void CScriptEditor::OnOK()
{
	if (UpdateData(true))
	{
		DestroyWindow();
	}
}


int CScriptEditor::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	SetWindowLong(this->m_hWnd,
		GWL_STYLE,
		GetWindowLong(this->m_hWnd, GWL_STYLE) | WS_MINIMIZEBOX/* | WS_MAXIMIZEBOX*/);

	return 0;
}
