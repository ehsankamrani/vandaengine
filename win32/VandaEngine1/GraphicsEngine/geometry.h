//Original Work: Copyright 2006 Sony Computer Entertainment Inc.
//Modified Work: Copyright (C) 2023 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#pragma once
#include <iostream>
#include <vector>
#include "base.h"
#include "skin.h"
#include "image.h"
#include "texture.h"
//#include "cfxLoader.h"
//#include "cfxEffect.h"
//#include "cfxSurface.h"
//#include "cfxPlatform.h"
#include "OpenGLUtility.h"
#include "../common/utility.h"
#include "../common/vector.h"
#include "../common/list.h"
#include "../VandaEngine1Win32.h"
#include "../scenemanagerEngine/octree.h"
#include "Prefab.h"
class CMaterial;
class CGeometry;
class CInstanceMaterial;
class CInstanceLight;
class CLOD;

class CInstanceMaterial
{
public:
	CInstanceMaterial() 
	{
		m_targetMaterial=0;
		//m_targetcfxMaterial=0;
		m_symbol= "";
		m_target= ""; 
	};
	CNode *m_parent; // Node where this instance was instantiated
	std::string	m_symbol;
	std::string	m_target;
	CMaterial * m_targetMaterial;
	//cfxMaterial * m_targetcfxMaterial;
};

class CInstance
{
public:
	CInstance() :  m_parent(0) {};
	//I assume that all the CMatrial objects are deleted insied CScene destructor
	~CInstance(){ m_materialInstances.clear(); };
	CNode *m_parent; // Node where this instance was instantiated */
	std::vector <CInstanceMaterial *> m_materialInstances; // list of material instances in the <technique_common>
};


class CInstanceGeometry : public CInstance
{
public:
	CInstanceGeometry() : m_abstractGeometry(0) {
		m_renderCount = 0; m_nameIndex = -1; m_hasPhysX = CFalse; Cpy(m_physXName, "\n");	m_lodAlgorithm = eLOD_NONE; m_prevLodAlgorithm = eLOD_NONE; m_physXDensity = 0.0f; m_physXPercentage = 50; m_physXCount = 0; m_firstUpdate = CTrue; m_isTrigger = CFalse; m_isInvisible = CFalse;
		m_distanceFromCamera = 0.0f; m_radius = 0.0f; m_renderWithPhysX = CFalse;  m_hasPhysicsMaterial = CFalse; m_isController = CFalse;
		CMatrixLoadIdentity(m_localToWorldMatrix); 	CMatrixLoadIdentity(m_localToWorldMatrixControlledByPhysX); CMatrixLoadIdentity(m_firstLocalToWorldMatrix);	}
	~CInstanceGeometry() { m_parentTree.clear(); }
	//We delete CGeometry object insied CScene destructor
	CGeometry *m_abstractGeometry;	// The abstract geometry where the original data is stored
	std::vector<COctree*>m_parentTree;
	CInt m_renderCount;
	std::vector<CInstanceLight*>m_lights;  //Lights that affect this geometry
	CMatrix	m_localToWorldMatrix;				// Full local to world matrix for this geometry
	CMatrix m_firstLocalToWorldMatrix;
	CBool m_firstUpdate;
	CMatrix m_localToWorldMatrixControlledByPhysX;
	CVec3f m_minLocalToWorldAABB; //To hold the world space max values of the AABB box
	CVec3f m_maxLocalToWorldAABB; //To hold the world space min values of the AABB box
	CVec3f m_minLocalToWorldAABBControlledByPhysX;
	CVec3f m_maxLocalToWorldAABBControlledByPhysX;
	CVec3f m_center;
	CFloat m_radius;
	CFloat m_distanceFromCamera;

	CVec3f m_localToWorldVertex[8];
	CInt m_nameIndex;
	CBool m_hasPhysX;
	CChar m_physXName[MAX_NAME_SIZE];
	CFloat m_physXDensity;
	CInt m_physXPercentage;
	CBool m_isTrigger;
	CBool m_isInvisible;
	////////////////physics material
	CBool m_hasPhysicsMaterial;
	CFloat m_physicsRestitution;
	CFloat m_physicsStaticFriction;
	CFloat m_physicsDynamicFriction;
	CFloat m_physicsSkinWidth;
	////////////////
	CInt m_physXCount;
	CPhysXAlgorithm m_lodAlgorithm;
	CPhysXAlgorithm m_prevLodAlgorithm;
	CBool m_renderWithPhysX;
	CNode* m_node; //instance geometry is attached to this node
	CBool m_isController;
	CChar* GetPhysXActorName() { return m_physXName; }
	CFloat GetPhysXActorDensity() { return m_physXDensity; }
	CBool GetHasPhysXActor() { return m_hasPhysX; }
	//physics material
	CBool HasPhysicsMaterial() { return m_hasPhysicsMaterial; }
	CFloat GetPhysicsRestitution() { return m_physicsRestitution; }
	CFloat GetPhysicsSkinWidth() { return m_physicsSkinWidth; }
	CFloat GetPhysicsStaticFriction() { return m_physicsStaticFriction; }
	CFloat GetPhysicsDynamicFriction() { return m_physicsDynamicFriction; }

	CVoid EnablePhysicsMaterial(CBool state) { m_hasPhysicsMaterial = state; }
	CVoid SetPhysicsRestitution(CFloat restitution) { m_physicsRestitution = restitution; }
	CVoid SetPhysicsSkinWidth(CFloat skinWidth) { m_physicsSkinWidth = skinWidth; }
	CVoid SetPhysicsStaticFriction(CFloat staticFriction) { m_physicsStaticFriction = staticFriction; }
	CVoid SetPhysicsDynamicFriction(CFloat dynamicFriction) { m_physicsDynamicFriction = dynamicFriction; }
	CVoid SetDistanceFromCamera(CFloat distance) { m_distanceFromCamera = distance; }
	CFloat GetDistanceFromCamera() { return m_distanceFromCamera; }
	CVoid CalculateDistance();
};

class CInstanceController : public CInstance
{
public:
	CInstanceController() : m_abstractController(0) { m_instanceGeometry = CNew(CInstanceGeometry);};
	~CInstanceController() { CDelete( m_instanceGeometry) };
	CController * m_abstractController;
	CInstanceGeometry * m_instanceGeometry;
};


class CVertexAllPtr
{
public:
	CVec3f*	m_point;
	CVec3f*	m_normal;
	CVec2f*	m_texcoord[MAX_TEX_COORDS];
	
	CVec3f* m_tangent;
    CVec3f* m_bNormal; 

	CWeight* m_weights; 
	CVec3f*	m_bindPoint; 
	CVec3f*	m_bindNormal; 
		
	CVertexAllPtr():
		m_point(NULL),
		m_normal(NULL),
		m_tangent(NULL),
		m_bNormal(NULL),
		m_weights(NULL),
		m_bindPoint(NULL),
		m_bindNormal(NULL)

	{
		memset( m_texcoord, 0, sizeof( m_texcoord )); 
	}
};


class CPolyGroup; 
class CVertexAll
{
public:
	CVec3f m_point;
	CVec3f m_normal;
	CVec2f m_texcoord[MAX_TEX_COORDS];

	CVec3f m_tangent;
    CVec3f m_bNormal; 

	CWeight m_weights; 
	CVec3f m_bindPoint; 
	CVec3f m_bindNormal; 
	
	CVertexAll()
	{
		// All the members have default constructors that initialize them
	}

    ~CVertexAll()
    {
    }

	inline CVoid Set( CVertexAllPtr * v )
	{
		if( v->m_point )
			m_point = *v->m_point;
		if( v->m_normal )
			m_normal = *v->m_normal;
		for ( CInt32 i = 0;i < MAX_TEX_COORDS; i++)
		{
			if( v->m_texcoord[i] )
				m_texcoord[i] = *v->m_texcoord[i];
		}

		if( v->m_tangent )
			m_tangent = *v->m_tangent;

		if( v->m_bNormal )
			m_bNormal = *v->m_bNormal;

		if( v->m_weights )
			m_weights.Copy( v->m_weights ); 

		if ( v->m_bindPoint )
			m_bindPoint = *v->m_bindPoint; 

		if ( v->m_bindNormal )
			m_bindNormal = *v->m_bindNormal; 
	}

	inline CVoid Set( CVertexAll * v )
	{
		m_point = v->m_point;
		m_normal = v->m_normal;

		for	( CInt i =0 ; i<MAX_TEX_COORDS ; i++ )
			m_texcoord[i] = v->m_texcoord[i];

		m_tangent = v->m_tangent;
		m_bNormal = v->m_bNormal;
		m_weights.Copy( &v->m_weights ); 
		m_bindPoint = v->m_bindPoint; 
		m_bindNormal = v->m_bindNormal; 
	}

	CBool Compare( CPolyGroup * polyGroup, CInt idx );
	CVoid Copy( CPolyGroup * polyGroup, CInt idx );
};

class CPoly 
{
public:
	CInt32* m_points;
	CVertexAllPtr* m_pointData;
	
	CInt32 m_numIndices; 
	CInt32 m_numPoints;

	CPoly():
		m_points(NULL),
		m_pointData(NULL),
		m_numIndices(0),
		m_numPoints(0)
	{
	}

	~CPoly()
	{
		CDelete( m_points );
		CDelete( m_pointData );  
	}
};

class CTri
{
public:
	CInt32 m_points[3];
	
	CTri()
	{
		memset( m_points, 0, sizeof ( m_points )); 
	}
};


class CSource
{
public:
	CFloat* m_data;
	CInt32 m_nbr; 
	CChar m_id[MAX_NAME_SIZE];	
	CChar m_semantic[MAX_NAME_SIZE]; 
	CChar m_vertexSourceId[MAX_NAME_SIZE];
	CBool m_hasVertexBinding; 

	CSource():
		m_data(NULL),
		m_nbr(0),
		m_hasVertexBinding(CFalse)
	{
		memset( m_id, 0, sizeof ( m_id )); 
		memset( m_semantic, 0, sizeof ( m_semantic )); 
		memset( m_vertexSourceId, 0, sizeof ( m_vertexSourceId )); 
	}

	~CSource()
	{
		DeleteData(); 
	}

	CVoid DeleteData()
	{
		CDeleteData( m_data ); 			
	}
};

class CInput 
{
public:
	CChar m_semantic[MAX_NAME_SIZE];
	CChar m_sourceName[MAX_NAME_SIZE]; 
	CSource *m_source; 
	CInputType m_type; 

	CInput():
		m_source(NULL),
		m_type(eUNKNOWN)

	{
		memset( m_semantic,	0, sizeof ( m_semantic )); 
		memset( m_sourceName, 0, sizeof ( m_sourceName )); 
	}
};

struct CVertexArray
{
	CInt	m_primitiveType;
	CInt	m_count;
	CInt	m_vertexFormat;
	CVoid* m_i;
	CVoid* m_p;
};

struct CMultiArray
{
	CVertexArray* m_pVertexArray;
	CInt32 m_nbVertexArray;
};

CVoid Cpy( CChar * s1, const CChar * s2 );
class CController; 
class CJoint; 
class CPolyGroup;


class CPolyGroup : public  CBase
{
public:
	//cfxMaterial *m_fXMaterial;	// COLLADA FX material for this polygon group */
	CMaterial *	m_material;		// OBSOLETE, will be removed by refactor later
	CChar m_materialName[MAX_NAME_SIZE];  //  could be obsolete or kept for debugging
	CBool m_hasSkin;  
	CGeometry* m_geometry;	
	CPoly* m_polys; 
	CTri* m_tris; 

	CMultiArray	m_multiArray; 
	CVertexArray m_boundingBoxArray;
	CVec3f m_minBound;
	CVec3f m_maxBound;

	CUInt32	m_count;
	CInt32	m_numTextures;
	CInt32	m_numSharedVerts; 

	CBool m_vertsShared; 
	CBool m_dataReadyForCg; 
	CVec4f*	m_skinIndicesCg;
	CVec4f*	m_skinWeightsCg; 

	CUInt* m_indexes;

	CBool m_hasAnimation;

	CImage* GetImage( const CChar * name );

	CChar m_strDirtMap[MAX_NAME_SIZE];
	CImage *m_dirtMapImg;
	CBool SetDirtMap( const CChar* path );
	CBool m_hasDirtMap;

	CChar m_strDiffuse[MAX_NAME_SIZE];
	CImage *m_diffuseImg;
	CBool SetDiffuse( const CChar * path );
	CBool m_hasDiffuse;

	CChar m_strNormalMap[MAX_NAME_SIZE];
	CImage *m_normalMapImg;
	CBool SetNormalMap( const CChar* path, CFloat bias, CFloat scale );
	CBool m_hasNormalMap;

	CChar m_strGlossMap[MAX_NAME_SIZE];
	CImage *m_glossMapImg;
	CBool SetGlossMap( const CChar* path );
	CBool m_hasGlossMap;

	std::vector<CImage*>m_images; //this points to all the *map pointers( see bellow )

	CFloat m_parallaxMapScale, m_parallaxMapBias;

	//Material Colors
	CFloat m_fAmbientColor[4];
	CFloat m_fDiffuseColor[4];
	CFloat m_fSpecularColor[4];
	CFloat m_fEmissionColor[4];
	CFloat m_fShininess, m_fTransparency;

	CFloat* GetAmbient() { return m_fAmbientColor; }
	CFloat* GetDiffuse() { return m_fDiffuseColor; }
	CFloat* GetSpecular() { return m_fSpecularColor; }
	CFloat* GetEmission() { return m_fEmissionColor; }
	CFloat GetShininess() { return m_fShininess; }
	CFloat GetTransparency() { return m_fTransparency; }


	CVoid SetAmbient(CFloat* ambient)
	{
		for (CUInt i = 0; i < 4; i++)
			m_fAmbientColor[i] = ambient[i];
	}
	CVoid SetDiffuse(CFloat* diffuse)
	{
		for (CUInt i = 0; i < 4; i++)
			m_fDiffuseColor[i] = diffuse[i];
	}
	CVoid SetSpecular(CFloat* specular)
	{
		for (CUInt i = 0; i < 4; i++)
			m_fSpecularColor[i] = specular[i];
	}
	CVoid SetEmission(CFloat* emission)
	{
		for (CUInt i = 0; i < 4; i++)
			m_fEmissionColor[i] = emission[i];
	}
	CVoid SetShininess(CFloat shininess) { m_fShininess = shininess; }
	CVoid SetTransparency(CFloat transparency) { m_fTransparency = transparency; }
	//////////////////

	inline CVoid RemoveDiffuse()
	{
		Cpy( m_strDiffuse, "\n" );
		//CTexture::DeleteTexture( m_diffuseImg );
		m_hasDiffuse = CFalse;
	}

	inline CVoid RemoveNormalMap()
	{
		Cpy( m_strNormalMap, "\n" );
		//CTexture::DeleteTexture( m_diffuseImg );
		m_hasNormalMap = CFalse;
	}

	inline CVoid RemoveDirtMap()
	{
		Cpy( m_strDirtMap, "\n" );
		//CTexture::DeleteTexture( m_diffuseImg );
		m_hasDirtMap = CFalse;
	}

	inline CVoid RemoveGlossMap()
	{
		Cpy( m_strGlossMap, "\n" );
		//CTexture::DeleteTexture( m_glossMapImg );
		m_hasGlossMap = CFalse;
	}

	CBool m_setMatFromCollada;

public:

	CPolyGroup()
	{
		m_material = NULL;
		//m_fXMaterial = NULL;
		m_numTextures	=	0;
		m_polys = NULL;
		m_tris = NULL; 
		m_multiArray.m_pVertexArray = 0;
		m_numSharedVerts = 0; 
		m_hasSkin = CFalse; 
		m_vertsShared = CFalse; 
		m_dataReadyForCg = CFalse; 
		m_skinIndicesCg = NULL;
		m_skinWeightsCg = NULL; 

		m_hasAnimation = CFalse;
		m_parallaxMapBias = -0.03;
		m_parallaxMapScale = 0.06;

		m_indexes = 0;

		Cpy (m_strDiffuse, "\n");
		m_hasDiffuse = CFalse;
		m_diffuseImg = NULL;

		Cpy (m_strNormalMap, "\n");
		m_hasNormalMap = CFalse;
		m_normalMapImg = NULL;

		Cpy (m_strDirtMap, "\n");
		m_hasDirtMap = CFalse;
		m_dirtMapImg = NULL;

		Cpy (m_strGlossMap, "\n");
		m_hasGlossMap = CFalse;
		m_glossMapImg = NULL;
		m_setMatFromCollada = CTrue;
	}
	~CPolyGroup()
	{
		Destroy(); 
		DeleteVertexData(); 
		DeletePolygonData(); 
		m_images.clear();
	}
	CVoid EnableShader();

protected:
	friend class CScene; 
	friend class CGeometry; 

	CVoid	DeleteVertexData()
	{
		if (m_indexes)
		{
			CDeleteData( m_indexes ); 
			m_indexes = NULL;			
		}
	}

	CVoid	DeleteData()
	{
	}

	CVoid DeletePolygonData()
	{
		CDeleteData( m_polys ); 
		CDeleteData( m_tris ); 		
	}

	CVoid DeleteAll()
	{
		DeleteVertexData();
		DeleteData(); 	
		DeletePolygonData(); 		
	}

	CVoid SetMaterialFromCOLLADA( CMaterial * mat, CChar * matName )
	{
		m_material = mat; 
		Cpy( m_materialName, matName ); 
	}

	CInput * GetPointInput();  
	CVoid CopyPointInput( CPolyGroup * group );

	CVoid ParseSource( const CChar * data, const CChar * name, const CChar * count );
    CInputType SetType( CChar * s );
	CVoid Draw(CNode *parentNode, CInstance * instance, CBool isSelected, CBool hasDiffuse ); //if the object is selected we have to use another color for the diffuse component
	CVoid SetHasSkin(){ m_hasSkin = CTrue; }
	CVoid DrawSkinned( CNode *parentNode, CVec3f * bindPos, CVec3f * bindNorms, 
				CJoint * joints, CInt nbrBindPoints, CInt nbrJoints, CInstance * instance);
	CVoid RenderSkinnedCg( CVec3f * bindPos, CVec3f * bindNorms, 
				CJoint * joints, CInt nbrBindPoints, CInt nbrJoints );
	/*cfxMaterial* */ CVoid SetupMaterialForDrawFromCOLLADA(CNode *parentNode, CInstance * instance, CBool isSelected, CBool hasDiffuse );
	CVoid SetupMaterialForDrawFromGameEngine(CBool isSelected);
	CVoid SaveMaterialValues(CMaterial * mat);

	CVoid RenderCg(); 
	CVoid SetDataPointers(); 
	CVoid RenderDebug();
public:
	//---------------------- External interfaces ---------------------------------//
	// Each Geometry represents a Collada Geometry Library.  Each lib can have 
	// may groups.  I these groups you will get the Material and from the Material
	// you can get the texture(s) if there are any.  
	// You will also get the Point,Normal,Tanget, TexCoords[8], UVs and Weights.
	// Currently the Weight data is loaded, but I have added it to the triangulation 
	// so this will return null for now.  But you can build your interface from the 
	// stucts that I have provide already.  

	inline CMaterial *GetMaterial()	{ return m_material; }
	inline CTri *GetTris() { return m_tris; }
	CVoid SetRender();
	virtual CVoid Render() = 0;
	virtual CVoid SetVBOs() = 0;

	CVoid SetReadMaterialColorFromCOLLADA() { m_setMatFromCollada = CTrue; }
	CVoid SetReadMaterialColorFromGameEngine(){ m_setMatFromCollada = CFalse; }
	//---------------------- End External interfaces -----------------------------//

};

class CPolygons : public CPolyGroup
{
public:
	CPolygons ();
	~CPolygons ();
	CVoid SetVBOs();
	CVoid Render();
	std::vector<CUInt> m_countvector;	
	std::vector<CUInt *> m_indexvector;
private:
	CUInt * m_VBOID;
};

class CTriangles : public CPolyGroup
{
public:
	CTriangles ();
	~CTriangles ();
	CVoid SetVBOs();
	CVoid Render();
private:
	CUInt m_VBOID;
};

class CLines : public CPolyGroup
{
public:
	CLines ();
	~CLines ();
	CVoid SetVBOs();
	CVoid Render();
private:
	CUInt m_VBOID;
};
class CLinestrips : public CPolyGroup
{
public:
	CLinestrips ();
	~CLinestrips ();
	std::vector<CUInt> m_countvector;	
	std::vector<CUInt *> m_indexvector;
	CVoid SetVBOs();
	CVoid Render();
private:
	CUInt * m_VBOID;
};
class CTriStrips : public CPolyGroup
{
public:
	CTriStrips ();
	~CTriStrips ();
	std::vector<CUInt> m_countvector;	
	std::vector<CUInt *> m_indexvector;
	CVoid SetVBOs();
	CVoid Render();
private:
	CUInt * m_VBOID;
};

class CGeometry : public CBase 
{
 	CController	*m_skinData; 

	CBool m_verticesSet; 
	CBool m_vertexSourceCopied; 

public:
	CVec3f*	m_points;
	CVec3f*	m_normals;
	CVec3f* m_tangents;
	CVec3f* m_bNormals;
	//CColor4f*	m_colors; 
	CVec2f*	m_texCoords[MAX_TEX_COORDS];
	CWeight* m_weights; 
	CUInt m_vertexcount;
	CUInt m_vertexcountmax;
	CUInt*	m_skinIndex;
	CVec3f*	m_bindPoints; 
	CVec3f*	m_bindNormals; 
	CMatrix* m_skinMatrixStack; 
	CMatrix3x4*	m_skinMatrixStack3x4; 
	CUInt m_VBOIDs[eGeoDataTypeMax];
	CUInt m_nameIndex; //This is used for OpenGL selection. This is a unique name which we pass to glPushName() in selection mode
	CUInt GetNameIndex() { return m_nameIndex; }
	CVector m_minAABB; //To hold the max values of the AABB box
	CVector m_maxAABB; //To hold the min values of the AABB box
	CVector m_center;
	COpenGLUtility m_glUtil;
	List <int>m_collapseMap;

	std::vector<CVec3f*>m_physx_points;
	std::vector<CTriangles*> m_physx_triangles;
	CInstanceGeometry* m_currentInstanceGeometry; 
	std::vector<CInstanceGeometry*> m_instanceGeometries;
	std::vector<CInstanceController*> m_instanceControllers;

	//To get required shader data. I get this data inside the editor.
	CChar m_strNormalMap[MAX_NAME_SIZE];
	CChar m_strDirtMap[MAX_NAME_SIZE];
	CChar m_strGlossMap[MAX_NAME_SIZE];
	CChar m_strHeightMap[MAX_NAME_SIZE];
	CChar m_strDuDvMap[MAX_NAME_SIZE];
	CChar m_strDiffuse[MAX_NAME_SIZE];
	CFloat m_parallaxMapScale, m_parallaxMapBias;

	//Material Colors
	CFloat m_fAmbientColor[4];
	CFloat m_fDiffuseColor[4];
	CFloat m_fSpecularColor[4];
	CFloat m_fEmissionColor[4];
	CFloat m_fShininess, m_fTransparency;

	CFloat* GetAmbient() { return m_fAmbientColor; }
	CFloat* GetDiffuse() { return m_fDiffuseColor; }
	CFloat* GetSpecular() { return m_fSpecularColor; }
	CFloat* GetEmission() { return m_fEmissionColor; }
	CFloat GetShininess() { return m_fShininess; }
	CFloat GetTransparency() { return m_fTransparency; }


	CVoid SetAmbient(CFloat* ambient)
	{
		for (CUInt i = 0; i < 4; i++)
			m_fAmbientColor[i] = ambient[i];
	}
	CVoid SetDiffuse(CFloat* diffuse)
	{
		for (CUInt i = 0; i < 4; i++)
			m_fDiffuseColor[i] = diffuse[i];
	}
	CVoid SetSpecular(CFloat* specular)
	{
		for (CUInt i = 0; i < 4; i++)
			m_fSpecularColor[i] = specular[i];
	}
	CVoid SetEmission(CFloat* emission)
	{
		for (CUInt i = 0; i < 4; i++)
			m_fEmissionColor[i] = emission[i];
	}
	CVoid SetShininess(CFloat shininess) { m_fShininess = shininess; }
	CVoid SetTransparency(CFloat transparency) { m_fTransparency = transparency; }
	//////////////////

	std::vector<CImage*>m_images; //this points to all the *map pointers( see bellow )

	CImage *m_normalMapImg;
	CImage *m_dirtMapImg;
	CImage *m_glossMapImg;
	CImage *m_heightMapImg;
	CImage *m_dudvMapImg;
	CImage *m_diffuseImg;

	CLOD* m_lod;
	CBool m_hasNormalMap, m_hasGlossMap, m_hasHeightMap, m_hasDuDvMap, m_hasDirtMap, m_hasDiffuse;
	CBool m_cullFaces; // Cull faces of the current geometry?

	CBool m_hasAnimation;
	CUpAxis m_upAxis;
	CVoid SetSkins(CInt nbrJoints );

	std::vector<CPolyGroup *> m_groups;

	CBool m_updateSkin;

	CGeometry()
	{
		m_lod = NULL;
		m_verticesSet = CFalse; 
		m_vertexSourceCopied  = CFalse; 
		m_skinData = NULL; 
		m_bindPoints = NULL;
		m_bindNormals = NULL; 
		m_skinMatrixStack = NULL; 
		m_skinMatrixStack3x4 = NULL; 
		m_vertexcount = 0;
		m_vertexcountmax = 1 /** 1024*/;
		m_points = CNewData(CVec3f, m_vertexcountmax); 
		m_normals = CNewData( CVec3f, m_vertexcountmax);
		m_tangents = NULL;
		m_bNormals = NULL;
		m_skinIndex = NULL;
		for( CInt i = 0; i < MAX_TEX_COORDS; i++ )
			m_texCoords[i] = NULL;
		m_weights = 0;
		m_nameIndex = 0;
		m_minAABB.m_i = m_minAABB.m_j = m_minAABB.m_k = 100000000.0f;
		m_maxAABB.m_i = m_maxAABB.m_j = m_maxAABB.m_k = -100000000.0f;
		m_parallaxMapBias = -0.03;
		m_parallaxMapScale = 0.06;

		memset( m_VBOIDs, 0, sizeof( m_VBOIDs )); 

		Cpy (m_strNormalMap, "\n");
		Cpy (m_strDirtMap, "\n");
		Cpy (m_strGlossMap, "\n");
		Cpy (m_strHeightMap, "\n");  // I currently use the alpha channel of the normal map as a height map
		Cpy (m_strDuDvMap, "\n");
		Cpy (m_strDiffuse, "\n");
		
		//I just use per pixel lighting at the beginning
		m_hasGlossMap = m_hasNormalMap = m_hasHeightMap = m_hasDuDvMap = m_hasDirtMap = m_hasDiffuse = CFalse;
		m_cullFaces = CTrue;

		m_hasAnimation = CFalse;

		m_normalMapImg = NULL;
		m_dirtMapImg = NULL;
		m_glossMapImg = NULL;
		m_heightMapImg = NULL; // I currently use the alpha channel of the normal map as a height map, so this item is not required right now
		m_dudvMapImg = NULL;
		m_diffuseImg = NULL;

		m_minAABB.m_i = m_minAABB.m_j = m_minAABB.m_k = 100000000.0f;
		m_maxAABB.m_i = m_maxAABB.m_j = m_maxAABB.m_k = -100000000.0f;

		m_updateSkin = CTrue;
		//m_normalMapImg = new CImage();
		//m_dirtMapImg = new CImage();
		//m_glossMapImg = new CImage();
	}
	~CGeometry();

	CVoid SetUpdateSkin(CBool set) { m_updateSkin = set; }
	CBool GetUpdateSkin() { return m_updateSkin; }

	CImage* GetImage( const CChar * name );
	CVoid SetDiffuse( const CChar * mapName );
	CVoid SetNormalMap( const CChar * path );
	CVoid SetDirtMap( const CChar * path );
	CVoid SetGlossMap( const CChar * path );
	CVoid SetHeightMap( const CChar * path );
	CVoid SetDuDvMap( const CChar * path );

	CVoid CalculateLODInfo( CPhysXAlgorithm algorithm);
	inline CVoid RegenerateIndex(CUInt MaxLODVertex, std::vector<CInt>&tri_vector)
	{
		for(CUInt i=0;i<m_groups.size();i++)
		{
			CTriangles* triangle =  m_physx_triangles[i];
			for (CUInt a = 0; a < triangle->m_count; a++)
			{
				CUInt i0, i1, i2;
				i0 = Map(triangle->m_indexes[a*3], MaxLODVertex);
				i1 = Map(triangle->m_indexes[1+a*3], MaxLODVertex);
				i2 = Map(triangle->m_indexes[2+a*3], MaxLODVertex);
				if(i0==i1 || i1==i2 || i2==i0) continue;
				tri_vector.push_back( i0);
				tri_vector.push_back(i1);
				tri_vector.push_back(i2);

				glBegin( GL_LINE_LOOP );
				glVertex3f( m_physx_points[i0]->x, m_physx_points[i0]->y, m_physx_points[i0]->z );
				glVertex3f( m_physx_points[i1]->x, m_physx_points[i1]->y, m_physx_points[i1]->z );
				glVertex3f( m_physx_points[i2]->x, m_physx_points[i2]->y, m_physx_points[i2]->z );
				glEnd();
			}
		}
	}

	inline CInt Map(CUInt a,CUInt max) {
		if(max<=0) return 0;
		while(a>=max) {  
			a= m_collapseMap[a];
		}
		return a;
	}

	inline CVoid RemoveNormalMap()
	{
		Cpy( m_strNormalMap, "\n" );
		//CTexture::DeleteTexture( m_normalMapImg );
		m_hasNormalMap = CFalse;
		//m_hasHeightMap = CFalse; //Currently the alpha channel of normal map consists of height map
	}
	inline CVoid RemoveGlossMap()
	{
		Cpy( m_strGlossMap, "\n" );
		//CTexture::DeleteTexture( m_glossMapImg );
		m_hasGlossMap = CFalse;
	}
	inline CVoid RemoveHeightMap()
	{
		Cpy( m_strHeightMap, "\n" );
		//CTexture::DeleteTexture( m_heightMapImg );
		m_hasHeightMap = CFalse;
	}

	inline CVoid RemoveDirtMap()
	{
		Cpy( m_strDirtMap, "\n" );
		//CTexture::DeleteTexture( m_dirtMapImg );
		m_hasDirtMap = CFalse;
	}
	inline CVoid RemoveDiffuse()
	{
		Cpy( m_strDiffuse, "\n" );
		//CTexture::DeleteTexture( m_diffuseImg );
		m_hasDiffuse = CFalse;
	}

	inline CVoid SetCullFace( CBool cullFaces )
	{
		m_cullFaces = cullFaces;
	}

protected:
	friend class CScene; 
	friend class CNode; 

	CVoid TranformAABBforZUP()
	{
		CVec4f rot( 1.0, 0.0, 0.0, -90.0 );
		CVec3f tv[2];
		CMatrix matrix;
		CMatrixLoadIdentity( matrix );
		CMatrix4x4RotateAngleAxis( matrix, rot );
		CVec3f tempMin, tempMax;
		tempMin.x = m_minAABB.m_i;
		tempMin.y = m_minAABB.m_j;
		tempMin.z = m_minAABB.m_k;

		tempMax.x = m_maxAABB.m_i;
		tempMax.y = m_maxAABB.m_j;
		tempMax.z = m_maxAABB.m_k;

		CMatrixTransform( matrix, tempMin, tv[0] );
		CMatrixTransform( matrix, tempMax, tv[1] );
		m_minAABB.m_i = tv[0].x;
		m_minAABB.m_j = tv[0].y;
		m_minAABB.m_k = tv[0].z;

		m_maxAABB.m_i = tv[1].x;
		m_maxAABB.m_j = tv[1].y;
		m_maxAABB.m_k = tv[1].z;
	}

	CVoid ComputeAABB_Center()
	{
		for ( CUInt i = 0; i < m_vertexcount; i++ )
		{
			if( m_points[i].x > m_maxAABB.m_i )
				m_maxAABB.m_i = m_points[i].x;
			if( m_points[i].y > m_maxAABB.m_j )
				m_maxAABB.m_j = m_points[i].y;
			if( m_points[i].z > m_maxAABB.m_k )
				m_maxAABB.m_k = m_points[i].z;

			if( m_points[i].x < m_minAABB.m_i )
				m_minAABB.m_i = m_points[i].x;
			if( m_points[i].y < m_minAABB.m_j )
				m_minAABB.m_j = m_points[i].y;
			if( m_points[i].z < m_minAABB.m_k )
				m_minAABB.m_k = m_points[i].z;
		}

		if( m_minAABB.m_i == 100000000.0f && m_minAABB.m_j == 100000000.0f && m_minAABB.m_k == 100000000.0f &&
			m_maxAABB.m_i == -100000000.0f && m_maxAABB.m_j == -100000000.0f && m_maxAABB.m_k == -100000000.0f ) //there's no vertex!
		{
			m_minAABB.m_i = m_minAABB.m_j = m_minAABB.m_k = 0;
			m_maxAABB.m_i = m_maxAABB.m_j = m_maxAABB.m_k = 0;
		}

		CVector m_centerTemp = m_minAABB + m_maxAABB;
		m_center = m_centerTemp * 0.5f;
	}

	CVoid DrawAABBWithLines()
	{
		CVector color( 1.0, 1.0, 1.0 );
		m_glUtil.DrawCWBoxWithLines( m_minAABB, m_maxAABB, color );
	}
	CVoid DrawAABBWithQuads()
	{

		m_glUtil.DrawCWBoxWithQuads( m_minAABB, m_maxAABB );
	}


	CVoid ParseSource( const CChar * data, const CChar * name, const CChar * count );
	CVoid DeleteSources();
	CVoid AddVertexBinding( const CChar * curName, const CChar * newName, const CChar * sematic ); 
	inline CVoid SetVerticesReady() { m_verticesSet = CTrue; } 

	CVoid SetRender();
	CVoid ResetStates();
	
	CVoid SetGroupRender( CPolyGroup* group );
	CVoid ResetGroupStates( CPolyGroup* group );

	CVoid DrawSkinned(CNode *parentNode, CInstance * instance );
	inline CVoid  SetController( CController * ctrl )
	{ 
		m_skinData = ctrl; 
		for (CUInt i = 0; i < m_groups.size(); i++)
		m_groups[i]->SetHasSkin(); 
	}
	CChar *	GetSkinName();	
	//inline CInt GetTotalNumTris(){ return TotalNumTris; }
public:
	inline CBool HasSkinController()
	{ 
		if ( m_skinData ) 
			return CTrue;
		else
			return CFalse; 
	}
	CVoid GetJointsForWeights( CJoint *& Joints, CInt & NumJoints );

	CVoid Draw(CNode *parentNode, CInstance * instance);
};

struct CTransparentGeometry
{
	CInstancePrefab* m_instancePrefab;
	CScene* m_scene;
	CInstanceGeometry* m_instanceGeometry;
};

struct SortTransparentGeometry
{
	inline bool operator() (const CTransparentGeometry& struct1, const CTransparentGeometry& struct2)
	{
		return (struct1.m_instanceGeometry->GetDistanceFromCamera() > struct2.m_instanceGeometry->GetDistanceFromCamera());
	}
};