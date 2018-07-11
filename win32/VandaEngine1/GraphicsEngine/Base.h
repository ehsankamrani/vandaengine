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
#pragma once
#include "..\common\utility.h"
class CBase 
{
protected: 

	CChar m_name[ MAX_NAME_SIZE ];
	CBase* m_next; 
	CChar m_docURI[ MAX_URI_SIZE ];

public:
	CBase();
	virtual ~CBase() { Destroy(); }; 
	
	// for auto deletion of the linked list 
	CVoid Destroy();
	CBase *GetNext();	
	CBase *SetNext( CBase * next ); 	
	CChar *GetName();			
	CVoid SetName( const CChar * n );
	CVoid SetDocURI(const CChar * n); 
	CChar *GetDocURI();	
};