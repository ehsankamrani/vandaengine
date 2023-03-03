//Copyright (C) 2023 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#pragma once
#include "..\\common\\utility.h"
#include "opengl.h"
#include "image.h"
#include "texture.h"
#include <stdio.h>
#include "CHeightClass.h"
#include "CTerrainTexture.h"
#include "CTerrainVBOCull.h"
//std headers
#include <string>
#include <set>
#include <map>
#include <vector>

class CTerrain
{
public:
	CTerrain();
	~CTerrain();
	CInt Initialize();
	CVoid SetIndex() { m_nameIndex = g_nameIndex++; } //selection
	CInt GetIndex() { return m_nameIndex; }
	CVoid Destroy();
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

	//Get Functions
	CChar* GetName() { return m_strName; }

	CChar* GetHeightMapPath() { return m_strHeightMapPath; }

	CChar* GetBottomTexturePath() { return m_strBottomTexturePath; }
	CChar* GetBottomNormalMapPath() { return m_strBottomNormalMapPath; }

	CChar* GetSlopeTexturePath() { return m_strSlopeTexturePath; }
	CChar* GetSlopeNormalMapPath() { return m_strSlopeNormalMapPath; }

	CChar* GetTopTexturePath() { return m_strTopTexturePath; }
	CChar* GetTopNormalMapPath() { return m_strTopNormalMapPath; }

	CFloat GetShininess() { return m_fShininess; }
	CInt GetSmooth() { return m_smooth; }
	CFloat GetScaleHeight() { return m_fScaleHeight; }
	CFloat GetScaleWidth() { return m_fScaleWidth; }
	CFloat GetSlopeFactor() { return m_fSlopeFactor; }
	CFloat GetTopStartHeight() { return m_fTopStartHeight; }
	CBool GetFlatten() { return m_flatten; }

	CFloat* GetAmbientColor() { return m_fAmbientColor; }
	CFloat* GetDiffuseColor() { return m_fDiffuseColor; }
	CFloat* GetSpecularColor() { return m_fSpecularColor; }
	CBool GetCookPhysicsTriangles() { return m_cookPhysicsTriangles; }
	CChar* GetPhysicsPath() { return m_physicsPath; }
	CTerrainVBOCull* GetTerrain() { return m_terrain; }
	CHeightClass* GetTerrainHeightmap() { return m_terrainHeightmap; }
	CTerrainTexture* GetTerrainTexture() { return m_terrainTexture; }

	//Set Functions
	CVoid SetName(CChar* name) { Cpy(m_strName, name); }

	CVoid SetHeightMapPath(CChar* path) { Cpy(m_strHeightMapPath, path); }

	CVoid SetBottomTexturePath(CChar* path) { Cpy(m_strBottomTexturePath, path); }
	CVoid SetBottomNormalMapPath(CChar* path) { Cpy(m_strBottomNormalMapPath, path); }

	CVoid SetSlopeTexturePath(CChar* path) { Cpy(m_strSlopeTexturePath, path); }
	CVoid SetSlopeNormalMapPath(CChar* path) { Cpy(m_strSlopeNormalMapPath, path); }

	CVoid SetTopTexturePath(CChar* path) { Cpy(m_strTopTexturePath, path); }
	CVoid SetTopNormalMapPath(CChar* path) { Cpy(m_strTopNormalMapPath, path); }

	CVoid SetShininess(CFloat shininess) { m_fShininess = shininess; }
	CVoid SetSmooth(CInt smooth) { m_smooth = smooth; }
	CVoid SetScaleHeight(CFloat scaleHeight) { m_fScaleHeight = scaleHeight; }
	CVoid SetScaleWidth(CFloat scaleWidth) { m_fScaleWidth = scaleWidth; }
	CVoid SetSlopeFactor(CFloat slopeFactor) { m_fSlopeFactor = slopeFactor; }
	CVoid SetTopStartHeight(CFloat topStartHeight) { m_fTopStartHeight = topStartHeight; }
	CVoid SetFlatten(CBool flatten) { m_flatten = flatten; }
	CVoid SetCookPhysicsTriangles(CBool set) { m_cookPhysicsTriangles = set; }
	CVoid SetPhysicsPath(CChar* path) { Cpy(m_physicsPath, path); }
	CVoid SetAmbientColor(CFloat* ambientColor) {
		for (CUInt i = 0; i < 4; i++)
		{
			m_fAmbientColor[i] = ambientColor[i];
		}
	}
	CVoid SetDiffuseColor(CFloat* diffuseColor)
	{
		for (CUInt i = 0; i < 4; i++)
		{
			m_fDiffuseColor[i] = diffuseColor[i];
		}
	}
	CVoid SetSpecularColor(CFloat* specularColor)
	{
		for (CUInt i = 0; i < 4; i++)
		{
			m_fSpecularColor[i] = specularColor[i];
		}
	}

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

	CVoid ResetLua();
	CBool LoadLuaFile();


private:
	CInt m_nameIndex; // selection
	CBool m_cookPhysicsTriangles;

	CChar m_strHeightMapPath[MAX_NAME_SIZE];
	CChar m_strBottomTexturePath[MAX_NAME_SIZE];
	CChar m_strBottomNormalMapPath[MAX_NAME_SIZE];
	CChar m_strSlopeTexturePath[MAX_NAME_SIZE];
	CChar m_strSlopeNormalMapPath[MAX_NAME_SIZE];
	CChar m_strTopTexturePath[MAX_NAME_SIZE];
	CChar m_strTopNormalMapPath[MAX_NAME_SIZE];
	CChar m_strName[MAX_NAME_SIZE];
	CChar m_physicsPath[MAX_NAME_SIZE];

	CFloat m_fShininess;
	CInt m_smooth;
	CFloat m_fScaleHeight;
	CFloat m_fScaleWidth;
	CFloat m_fSlopeFactor;
	CFloat m_fTopStartHeight;
	CBool m_flatten;

	CFloat m_fAmbientColor[4];
	CFloat m_fDiffuseColor[4];
	CFloat m_fSpecularColor[4];

	CTerrainVBOCull* m_terrain;
	CHeightClass* m_terrainHeightmap;
	CTerrainTexture* m_terrainTexture;

	lua_State* m_lua;
	CBool m_hasScript;
	CChar m_script[MAX_URI_SIZE];
	CBool m_updateScript;
	CChar m_tempScriptPath[MAX_URI_SIZE];
	CChar m_tempCurrentScriptPath[MAX_URI_SIZE];
	CChar m_lastScriptPath[MAX_URI_SIZE];
};

