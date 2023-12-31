//Original Work: Copyright 2006 Sony Computer Entertainment Inc.
//Modified Work: Copyright (C) 2024 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#include "stdafx.h"
#include "base.h"

CBase::CBase()
{
	m_next = NULL;
	m_docURI[0] = 0;
	m_name[0] = 0;
}

// for auto deletion of the linked list 
CVoid CBase::Destroy()
{
	//CDelete( m_next ); 		
}

CBase* CBase::GetNext()
{
	return m_next;
}

CBase* CBase::SetNext(CBase * next)
{
	m_next = next;
	return this;
}

CChar* CBase::GetName()
{
	if (!m_str_name.empty())
	{
		Cpy(m_name, m_str_name.c_str());
		return m_name;
	}
	else
		return NULL;
}

CVoid CBase::SetName(const CChar * n)
{
	m_str_name = n;
	//Cpy(m_name, n);
}

CVoid CBase::SetDocURI(const CChar * n)
{
	m_str_docURI = n;
	//Cpy(m_docURI, n);
}

CChar* CBase::GetDocURI()
{
	if (!m_str_docURI.empty())
	{
		Cpy(m_docURI, m_str_docURI.c_str());
		return m_docURI;
	}
	else
		return NULL;
}
