//Copyright (C) 2024 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#pragma once

#include "image.h"
#include "perspectiveWindow.h"
//std headers
#include <string>
#include <set>
#include <map>
#include <vector>

enum
{
	WATER_REFLECTION_ID,
	WATER_REFRACTION_ID,
	WATER_DEPTH_ID,
	WATER_NORMAL_ID,
	WATER_DUDVMAP_ID,
};

#define MAX_WATER_TEXTURES 3 //these textures include reflection, refraction and depth
#define g_waterTextureSize 512


class CWater
{
private:
	GLuint m_queryIndex;
	CFloat m_distanceFromCamera;
	CBool m_queryVisible;
	CBool m_isOutsideFrustom;
	CBool m_updateEvent;
	CBool m_updateAnimation;

public:
	CWater();
	~CWater();
	CVoid RenderWater( CVec3f cameraPos, CFloat elapsedTime );
	CVoid ResetLua();
	CBool LoadLuaFile();

	CVoid SetHasScript(CBool set) { m_hasScript = set; }
	CBool GetHasScript() { return m_hasScript; }
	CVoid SetScript(CChar* script) { Cpy(m_script, script); }
	CChar* GetScript() { return m_script; }
	CVoid SetLastScriptPath(CChar* script) { Cpy(m_lastScriptPath, script); }
	CChar* GetLastScriptPath() { return m_lastScriptPath; }

	CVoid SetUpdateScript(CBool set) { m_updateScript = set; }
	CBool GetUpdateScript() { return m_updateScript; }

	CVoid SetTempScriptPath(CChar* path) { Cpy(m_tempScriptPath, path); }
	CVoid SetTempCurrentScriptPath(CChar* path) { Cpy(m_tempCurrentScriptPath, path); }

	CChar* GetTempScriptPath() { return m_tempScriptPath; }
	CChar* GetTempCurrentScriptPath() { return m_tempCurrentScriptPath; }

	CVoid InitScript();
	CVoid UpdateScript();

	//functions to get and set script variables
	CChar* GetScriptStringVariable(CChar* variableName);
	CBool GetScriptBoolVariable(CChar* variableName);
	CInt GetScriptIntVariable(CChar* variableName);
	CDouble GetScriptDoubleVariable(CChar* variableName);
	CVoid SetScriptStringVariable(CChar* variableName, CChar* value);
	CVoid SetScriptBoolVariable(CChar* variableName, CBool value);
	CVoid SetScriptIntVariable(CChar* variableName, CInt value);
	CVoid SetScriptDoubleVariable(CChar* variableName, CDouble value);

	CVoid SetUpdateEvent(CBool set) { m_updateEvent = set; }
	CBool GetUpdateEvent() { return m_updateEvent; }

	CVoid SetUpdateAnimation(CBool set) { m_updateAnimation = set; }
	CBool GetUpdateAnimation() { return m_updateAnimation; }

	CFloat m_fWaterCPos[3];
	CFloat m_fWaterLPos[3];
	CFloat m_fWaterHeight;
	CFloat m_fWaterSpeed;
	CFloat m_fWaterUV;
	CFloat m_fWaterScaleX;
	CFloat m_fWaterScaleZ;
	CFloat m_fWaterRotateY;
	CFloat m_fWaterTransparency;
	CFloat m_fWaterColor[3];
	CFloat m_fWaterFogDensity;
	CBool m_isVisible;
	GLint m_result;
	CBool m_shadow;
	CBool m_sunReflection;

	//####public interface####	
	//The user just needs to use these functions 
	CFloat* GetPos() { return m_fWaterCPos; }
	CFloat* GetLightPos() { return m_fWaterLPos; }
	CFloat GetHeight() { return /*m_fWaterHeight*/m_fWaterCPos[1]; }
	CFloat GetSpeed() { return m_fWaterSpeed; }
	CFloat GetUV(){ return m_fWaterUV; }
	CFloat GetScaleX() { return m_fWaterScaleX; }
	CFloat GetScaleZ() { return m_fWaterScaleZ; }
	CFloat GetRotateY() { return m_fWaterRotateY; }
	CChar* GetName();
	CChar* GetLastName();
	CChar* GetDuDvMapName();
	CChar* GetNormalMapName();
	GLuint GetQueryIndex();
	CVoid CalculateDistance();
	CFloat GetDistanceFromCamera();
	CBool GetShadow() { return m_shadow; }
	CBool GetSunReflection() { return m_sunReflection; }

	CVoid SetDuDvMapName(CChar* name);
	CVoid SetNormalMapName(CChar* name);
	CInt GetIndex() { return m_nameIndex; }
	CBool GetVisible() { return m_isVisible; }

	CVoid SetName( CString name  );
	CVoid SetLastName(CChar* name);
	CVoid SetDuDvMap( CString mapName, CBool updateSharedImages = CFalse );
	CVoid SetNormalMap( CString mapName, CBool updateSharedImages = CFalse );
	CVoid SetPos( CFloat* pos ) { m_fWaterCPos[0] = pos[0]; m_fWaterCPos[1] = pos[1]; m_fWaterCPos[2] = pos[2]; }
	CVoid SetLightPos( CFloat* pos ) { m_fWaterLPos[0] = pos[0]; m_fWaterLPos[1] = pos[1]; m_fWaterLPos[2] = pos[2]; }
	CVoid SetHeight( CFloat height ) { m_fWaterHeight = height; }
	CVoid SetSpeed( CFloat speed ) { m_fWaterSpeed = speed; }
	CVoid SetUV( CFloat UV ) { m_fWaterUV = UV; }
	CVoid SetScaleX(CFloat scaleX) { m_fWaterScaleX = scaleX; }
	CVoid SetScaleZ(CFloat scaleZ) { m_fWaterScaleZ = scaleZ; }
	CVoid SetRotateY(CFloat rotateY) { m_fWaterRotateY = rotateY; }
	CVoid SetShadow(CBool status) { m_shadow = status; }
	CVoid SetSunReflection(CBool status) { m_sunReflection = status; }

	CVoid SetVisible(CBool isVisible) { m_isVisible = isVisible; }
	CVoid SetQueryVisible(CBool visible) { m_queryVisible = visible; }
	CBool GetQueryVisible() { return m_queryVisible; }
	CVoid SetOutsideFrustom(CBool isOutsideFrustom) { m_isOutsideFrustom = isOutsideFrustom; }
	CBool GetOutsideFrustom() { return m_isOutsideFrustom; }
	CVoid SetIndex() { m_nameIndex = g_nameIndex++; }
	CVoid SetResult(GLint result);
	GLint GetResult();
	// This renders the current screen to a texture map, given a specified size and type

	CVoid CreateRenderTexture(CInt size, CInt channels, CInt type, CInt textureID );

	// This renders our screen to a texture that is used for reflection
	CVoid CreateReflectionTexture(CInt textureSize );

	// This renders our screen to a texture for refraction and depth
	CVoid CreateRefractionDepthTexture(CInt textureSize);

	void SetSideVertexPositions();
	CBool IsPointInWater(CVec3f point);
	CBool IsPointAboveWater(CVec3f point);

	CFloat GetRadius();
	CVoid RenderIcon( CBool selectionMode = CFalse );

	std::vector<std::map<std::string,CBool>> m_VSceneList; //List of all VScenes created via the editor, save functions

	inline CVoid AddVSceneToList(std::string vSceneName, CBool save) //save functions
	{
		for (CUInt i = 0; i < m_VSceneList.size(); i++)
		{
			if (m_VSceneList[i].begin()->first == vSceneName)
			{
				m_VSceneList[i].begin()->second = save;
				return;
			}
		}
		std::map<std::string, CBool> tempVScene;
		tempVScene[vSceneName] = save;
		m_VSceneList.push_back(tempVScene);
	}
	inline CBool IsInVSceneList( std::string vSceneName, CBool content, CBool reverseTheContent ) //save functions
	{
		for( CUInt i = 0; i < m_VSceneList.size(); i++ )
		{
			if( m_VSceneList[i].begin()->first == vSceneName )
			{
				if( m_VSceneList[i].begin()->second == content) //found the target
				{
					if( reverseTheContent )
						m_VSceneList[i].begin()->second = !content;
					return CTrue;
				}
				else
					return CFalse;
			}
		}
		if( reverseTheContent )
			AddVSceneToList( vSceneName, !content );
		else
			AddVSceneToList( vSceneName, content );
		return CTrue;
	}

	CChar m_strWaterName[MAX_NAME_SIZE];
	CChar m_lastName[MAX_NAME_SIZE];
	CChar m_strDuDvMap[MAX_NAME_SIZE];
	CChar m_strNormalMap[MAX_NAME_SIZE];
	CUInt m_waterTexture[ MAX_WATER_TEXTURES ];
	CVec3f m_sidePoint[4]; //each water has four vertexes
	CVec3f m_sidePointNoRotate[4];

	CImage *GetWaterImage( const CChar * name );

	CUInt GetNumPrefabInstanceNames();
	CVoid AddPrefabInstanceName(CChar* name);
	const CChar* GetPrefabInstanceName(CUInt index);

	CUInt GetNumPrefabInstances();
	CVoid AddPrefabInstance(CInstancePrefab* instance);
	CVoid RemovePrefabInstance(CUInt index);
	CInstancePrefab* GetPrefabInstance(CUInt index);
	
	CFloat GetTransparency() { return m_fWaterTransparency; }
	CVoid SetTransparency(CFloat value) { m_fWaterTransparency = value; }

	CFloat* GetColor() { return m_fWaterColor; }
	CVoid SetColor(CFloat* color) { m_fWaterColor[0] = color[0];  m_fWaterColor[1] = color[1]; m_fWaterColor[2] = color[2]; }

	CFloat GetFogDensity() { return m_fWaterFogDensity; }
	CVoid SetFogDensity(CFloat value) { m_fWaterFogDensity = value; }

private:
	CImage *m_dudvMapImg;
	CImage *m_normalMapImg;
	CUInt m_fboID[ MAX_WATER_TEXTURES ]; //each texture has its own FBO ID
	CUInt m_rbID[ MAX_WATER_TEXTURES ]; //each texture has its own FBO ID

	CInt m_nameIndex; //selection

	std::vector <std::string> m_instanceName;
	std::vector<CInstancePrefab*> m_instancePrefab;

private:
	CFloat m_move;

	// This loads all of our animation textures and stores them in our texture array
	CVoid LoadAnimTextures(UINT textureArray[], LPSTR szFileName, CInt startIndex, CInt textureCount);

	// This cycles through our caustic bitmaps to produce the animation
	CVoid RenderCaustics(CFloat causticScale);

	lua_State* m_lua;
	CBool m_hasScript;
	CChar m_script[MAX_URI_SIZE];
	CBool m_updateScript;
	CChar m_tempScriptPath[MAX_URI_SIZE];
	CChar m_tempCurrentScriptPath[MAX_URI_SIZE];
	CChar m_lastScriptPath[MAX_URI_SIZE];

};