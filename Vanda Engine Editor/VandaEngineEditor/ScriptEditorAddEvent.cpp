//Copyright (C) 2023 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

// ScriptEditorAddEvent.cpp : implementation file
//

#include "stdafx.h"
#include "VandaEngineEditor.h"
#include "ScriptEditorAddEvent.h"
#include "afxdialogex.h"


// CScriptEditorAddEvent dialog

IMPLEMENT_DYNAMIC(CScriptEditorAddEvent, CDialog)

CScriptEditorAddEvent::CScriptEditorAddEvent(CWnd* pParent /*=NULL*/)
	: CDialog(CScriptEditorAddEvent::IDD, pParent)
{
	if (g_multipleView->m_enableTimer)
		g_multipleView->EnableTimer(CFalse);

	m_index = -1;
	Cpy(m_initEventName, "function Init()\n\nend\n");
	Cpy(m_updateEventName, "function Update()\n\nend\n");
	Cpy(m_onTriggerEnterEventName, "function OnTriggerEnter(otherActorName)\n\nend\n");
	Cpy(m_onTriggerStayEventName, "function OnTriggerStay(otherActorName)\n\nend\n");
	Cpy(m_onTriggerExitEventName, "function OnTriggerExit(otherActorName)\n\nend\n");
	Cpy(m_onSelectMouseLButtonDown, "function OnSelectMouseLButtonDown()\n\nend\n");
	Cpy(m_onSelectMouseRButtonDown, "function OnSelectMouseRButtonDown()\n\nend\n");
	Cpy(m_onSelectMouseEnter, "function OnSelectMouseEnter()\n\nend\n");
	Cpy(m_onSelectEventName, "function OnSelect()\n\nend\n");
}

CScriptEditorAddEvent::~CScriptEditorAddEvent()
{
}

void CScriptEditorAddEvent::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_EVENTS, m_listEvents);
	DDX_Control(pDX, IDC_RICHED_EVENT_NAME, m_richEventName);
}


BEGIN_MESSAGE_MAP(CScriptEditorAddEvent, CDialog)
	ON_BN_CLICKED(IDOK, &CScriptEditorAddEvent::OnBnClickedOk)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_EVENTS, &CScriptEditorAddEvent::OnLvnItemchangedListEvents)
	ON_BN_CLICKED(IDCANCEL, &CScriptEditorAddEvent::OnBnClickedCancel)
END_MESSAGE_MAP()


// CScriptEditorAddEvent message handlers


void CScriptEditorAddEvent::OnBnClickedOk()
{
	CString s;
	m_richEventName.GetWindowTextA(s);
	if (s.IsEmpty())
	{
		MessageBox("Please select an item from the list", "Error", MB_OK | MB_ICONERROR);
		return;
	}
	else
	{
		m_richEventName.Copy();
	}
	if (g_multipleView->m_enableTimer)
		g_multipleView->EnableTimer(CTrue);

	CDialog::OnOK();
}


void CScriptEditorAddEvent::OnLvnItemchangedListEvents(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	int nSelected = -1;
	POSITION p = m_listEvents.GetFirstSelectedItemPosition();
	while (p)
	{
		nSelected = m_listEvents.GetNextSelectedItem(p);
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
		m_listEvents.GetItem(&lvi);

		if (Cmp(szBuffer, "Init"))
		{
			m_richEventName.SetWindowTextA(m_initEventName);
		}
		else if (Cmp(szBuffer, "Update"))
		{
			m_richEventName.SetWindowTextA(m_updateEventName);
		}
		else if (Cmp(szBuffer, "OnTriggerEnter"))
		{
			m_richEventName.SetWindowTextA(m_onTriggerEnterEventName);
		}
		else if (Cmp(szBuffer, "OnTriggerStay"))
		{
			m_richEventName.SetWindowTextA(m_onTriggerStayEventName);
		}
		else if (Cmp(szBuffer, "OnTriggerExit"))
		{
			m_richEventName.SetWindowTextA(m_onTriggerExitEventName);
		}
		else if (Cmp(szBuffer, "OnSelectMouseLButtonDown"))
		{
			m_richEventName.SetWindowTextA(m_onSelectMouseLButtonDown);
		}
		else if (Cmp(szBuffer, "OnSelectMouseRButtonDown"))
		{
			m_richEventName.SetWindowTextA(m_onSelectMouseRButtonDown);
		}
		else if (Cmp(szBuffer, "OnSelectMouseEnter"))
		{
			m_richEventName.SetWindowTextA(m_onSelectMouseEnter);
		}
		else if (Cmp(szBuffer, "OnSelect"))
		{
			m_richEventName.SetWindowTextA(m_onSelectEventName);
		}
		CInt end = m_richEventName.GetWindowTextLengthA();
		m_richEventName.SetSel(0, end);
	}
	else
	{
		m_richEventName.SetWindowTextA("");
		m_richEventName.SetSel(0, 0);
	}

	*pResult = 0;
}


BOOL CScriptEditorAddEvent::OnInitDialog()
{
	CDialog::OnInitDialog();

	CBitmap cBmp;
	CBitmap* cBmpMask = NULL;
	m_image.Create(32, 32, ILC_COLOR24, 1, 1);

	cBmp.LoadBitmap(IDB_BITMAP_ADD_ITEM);
	m_image.Add(&cBmp, cBmpMask);
	cBmp.DeleteObject();

	RECT tempRect;
	m_listEvents.GetClientRect(&tempRect);
	m_listEvents.SetImageList(&m_image, LVSIL_SMALL);
	m_listEvents.InsertColumn(0, "Events", LVCFMT_LEFT | LVS_SHOWSELALWAYS, (tempRect.right - tempRect.left) * 90 / 100);
	m_listEvents.ShowWindow(SW_SHOW);
	m_listEvents.UpdateWindow();

	InsertItem("Init");
	InsertItem("Update");
	InsertItem("OnTriggerEnter");
	InsertItem("OnTriggerStay");
	InsertItem("OnTriggerExit");
	InsertItem("OnSelectMouseLButtonDown");
	InsertItem("OnSelectMouseRButtonDown");
	InsertItem("OnSelectMouseEnter");
	InsertItem("OnSelect");

	m_listEvents.SetItemState(0, LVIS_SELECTED, LVIS_SELECTED | LVIS_FOCUSED);
	m_listEvents.SetSelectionMark(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

CVoid CScriptEditorAddEvent::InsertItem(CChar* name)
{
	m_index++;
	int index = m_index;
	LVITEM lvItem;
	lvItem.mask = LVIF_TEXT | LVIF_IMAGE;
	lvItem.iItem = index;
	lvItem.iImage = 0;
	lvItem.iSubItem = 0;
	lvItem.pszText = name;
	m_listEvents.InsertItem(&lvItem);

	m_listEvents.SetExtendedStyle(LVS_EX_INFOTIP | LVS_EX_ONECLICKACTIVATE | LVS_EX_LABELTIP);
	m_listEvents.EnsureVisible(index, FALSE);
	m_listEvents.UpdateWindow();
}

void CScriptEditorAddEvent::OnBnClickedCancel()
{
	if (g_multipleView->m_enableTimer)
		g_multipleView->EnableTimer(CTrue);
	CDialog::OnCancel();
}
