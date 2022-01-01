//Copyright (C) 2022 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#pragma once

class CBloom
{
public:
	CBloom(){};
	~CBloom();
	void CreateEmptyTexture( CInt width, CInt height, CInt channels, CInt type );
	void CreateRuntimeTexture( int textureWidth, int textureHeight, int sceneTextureId );
	CUInt m_fboID; //each texture has its own FBO ID
	CUInt m_rbID;
	CUInt m_bloomTexture;

	CUInt m_fboID2; //each texture has its own FBO ID
	CUInt m_rbID2;
	CUInt m_bloomTexture2;
};