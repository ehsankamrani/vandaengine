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

class CDDS;
class CImage;

class CTexture
{
public:
	CTexture();
	~CTexture();
	CInt32 GetTextureType( CChar * name );
	CBool SetTexture( CImage *texObj );
	static CBool CreateTargaTexture( CImage * texObj );
	static CBool CreateDDSTexture( CImage * texObj, CDDS * ddsImg );
	static CBool DeleteTexture( CImage * texObj );
	//static CBool LoadTargaTexture( CImage * texObj, CChar* name, CChar* sceneFileName ); 
	static CBool LoadDDSTexture( CImage * texObj, CChar* name, CChar* sceneFileName ); 
};