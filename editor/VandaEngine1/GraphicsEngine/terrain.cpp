//Copyright (C) 2021 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#include "stdafx.h"
#include "terrain.h"
#include "render.h"
#include "../VandaEngine1dlg.h"
CTerrain::CTerrain()
{
    m_nameIndex = 0;
	m_cookPhysicsTriangles = CTrue;
	m_terrainHeightmap = CNew(CHeightClass);
	m_terrainTexture = CNew(CTerrainTexture);
	m_terrain = CNew(CTerrainVBOCull);
}

CTerrain::~CTerrain()
{
	Destroy();
}

CInt CTerrain::Initialize()
{
	SetIndex();
	// Initialize the heightmap by creating a midpoint displacement heightmap.
	m_terrainHeightmap = CNew(CHeightClass);
	m_terrainHeightmap->createHeightmap(CHeightClass::Image, g_terrain->GetHeightMapPath());

	//// Initialize the texture data.
	m_terrainTexture = CNew(CTerrainTexture);
	m_terrainTexture->init(m_terrainHeightmap->getHeightData());

	//// Create our mesh from the heightmap.
	m_terrain = CNew(CTerrainVBOCull);
	m_terrain->init(m_terrainHeightmap->getHeightData());

	//// Create the lightmap.
	//m_terrainTexture->createLightmap(10.f, 10.f, 10.f);

	return 1;
}

CVoid CTerrain::Destroy()
{
	m_VSceneList.clear();
	CDelete(m_terrainHeightmap);
	CDelete(m_terrainTexture);
	CDelete(m_terrain);
}


