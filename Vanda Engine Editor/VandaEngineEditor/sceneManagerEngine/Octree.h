//Copyright (C) 2024 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#pragma once
#include "..\common\vector.h"
#include "..\common\point.h"
#include "..\common\utility.h"
#include "..\graphicsEngine\Geometry.h"
#include "..\graphicsEngine\OpenGLUtility.h"

enum COctreeID
{
	eROOT				= -1,
	eTOP_LEFT_FRONT		=  0,
	eBOTTOM_LEFT_FRONT	=  1,
	eBOTTOM_RIGHT_FRONT	=  2,
	eTOP_RIGHT_FRONT	=  3,
	eTOP_LEFT_BACK		=  4,
	eBOTTOM_LEFT_BACK	=  5,
	eBOTTOM_RIGHT_BACK	=  6,
	eTOP_RIGHT_BACK		=  7
};

class COctree  
{
public:
	COctree();
	~COctree();
	CVoid GetWorldDimensions();
	CVoid ResetOctreeGeoCount();
	CVoid Render(CBool checkVisibility = CFalse, CBool drawGeometry = CTrue);
	CVoid SplitNode8( COctree* parent );
	CBool AttachGeometriesToNode();
	CVoid AttachLightsToGeometries();
	CVoid SetName( CChar* name );
	inline CChar* GetName() { return m_name; }
	CVoid SetLevel( CInt level );
	CVoid ResetState();
	CVoid Init();
	CVec3f m_minAABB;
	CVec3f m_maxAABB;

private:
	CBool m_leaf; //does this node has any childs
	CVec3f m_center;
	COctree* m_pSubNode[8]; //each octree may have 8 childs
	COctree* m_pParent;
	CVoid SetDimentions( CVec3f min, CVec3f max );
	CBool IsPointInBox( CVec3f* p );
	CBool IsPointInLight( CVec3f* p, CInstanceLight* light );
	CVoid RenderGeometry();
	CInt m_geoCount;
	CInt m_level;
	CChar m_name[MAX_NAME_SIZE];
};

