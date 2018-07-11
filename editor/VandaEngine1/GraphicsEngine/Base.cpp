/*
 * Copyright 2006 Sony Computer Entertainment Inc.
 *
 * Licensed under the SCEA Shared Source License, Version 1.0 (the "License"); you may not use this 
 * file except in compliance with the License. You may obtain a copy of the License at:
 * http://research.scea.com/scea_shared_source_license.html
 *
 * Unless required by applicable law or agreed to in writing, software distributed under the License 
 * is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or 
 * implied. See the License for the specific language governing permissions and limitations under the 
 * License. 
 */
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

 CBase* CBase::SetNext( CBase * next )
{
	m_next = next;
	return this;
}

 CChar* CBase::GetName()
{
	return m_name;
}

 CVoid	CBase::SetName( const CChar * n )
{
	Cpy( m_name, n);
}

 CVoid CBase::SetDocURI(const CChar * n)
{
	Cpy( m_docURI, n);
} 

 CChar* CBase::GetDocURI()
{
	return m_docURI;
}
