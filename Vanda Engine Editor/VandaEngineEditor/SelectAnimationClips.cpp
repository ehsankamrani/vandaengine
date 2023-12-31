//Copyright (C) 2024 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

// SelectAnimationClips.cpp : implementation file
//

#include "stdafx.h"
#include "VandaEngineEditor.h"
#include "SelectAnimationClips.h"
#include "afxdialogex.h"


// CSelectAnimationClips dialog

IMPLEMENT_DYNAMIC(CSelectAnimationClips, CDialog)

CSelectAnimationClips::CSelectAnimationClips(CWnd* pParent /*=NULL*/)
	: CDialog(CSelectAnimationClips::IDD, pParent)
{
	m_index = -1;
}

CSelectAnimationClips::~CSelectAnimationClips()
{
}

void CSelectAnimationClips::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_ANIMATION_CLIPS, m_listAnimationClips);
}


BEGIN_MESSAGE_MAP(CSelectAnimationClips, CDialog)
	ON_BN_CLICKED(IDOK, &CSelectAnimationClips::OnBnClickedOk)
END_MESSAGE_MAP()


// CSelectAnimationClips message handlers


BOOL CSelectAnimationClips::OnInitDialog()
{
	CDialog::OnInitDialog();
	CRect rect;
	m_listAnimationClips.GetClientRect(&rect);

	m_listAnimationClips.InsertColumn(0, "Animation Names", LVCFMT_LEFT, rect.right - rect.left, 0);
	m_listAnimationClips.SetExtendedStyle(LVS_EX_INFOTIP | LVS_EX_ONECLICKACTIVATE | LVS_EX_LABELTIP);

	for (CUInt i = 0; i < m_list.size(); i++)
	{
		CChar* name = GetAfterPath((CChar*)m_list[i].c_str());
		GetWithoutDot(name);
		InserItemToList(name);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CSelectAnimationClips::OnBnClickedOk()
{
	int nSelected = -1;
	POSITION p = m_listAnimationClips.GetFirstSelectedItemPosition();
	while (p)
	{
		nSelected = m_listAnimationClips.GetNextSelectedItem(p);
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
		m_listAnimationClips.GetItem(&lvi);

		Cpy(m_selectedAnimation, szBuffer);
	}
	else
	{
		MessageBox("Please select an item", "Vanda Engine Error", MB_OK | MB_ICONINFORMATION);
		return;
	}
	CDialog::OnOK();
}

CVoid CSelectAnimationClips::SetAnimationList(std::vector<std::string>list)
{
	m_list = list;
}

CChar* CSelectAnimationClips::GetSelectedAnimation()
{
	return m_selectedAnimation;
}

CVoid CSelectAnimationClips::InserItemToList(char * name)
{
	m_index++;
	LVITEM lvItem;
	lvItem.mask = LVIF_TEXT;
	lvItem.iItem = m_index;
	lvItem.iSubItem = 0;
	lvItem.pszText = name;
	m_listAnimationClips.InsertItem(&lvItem);
	m_listAnimationClips.SetItemState(m_index, LVIS_SELECTED, LVIS_SELECTED | LVIS_FOCUSED);
	m_listAnimationClips.EnsureVisible(0, FALSE);
}

