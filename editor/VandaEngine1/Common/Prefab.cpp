//Copyright (C) 2022 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#include "stdafx.h"
#include "Utility.h"
#include "Prefab.h"
#include "../GraphicsEngine/scene.h"
#include "../GraphicsEngine/Water.h"
#include "../GraphicsEngine/Light.h"
#include "../GraphicsEngine/animation.h"
CPrefab::CPrefab()
{
	Cpy(m_name, "\n");
	
	for (CUInt i = 0; i < 3; i++)
	{
		m_lod[i] = CNew(CVLOD);
		m_hasLod[i] = CFalse;
	}
	m_lod[0]->m_isVisible = CTrue;
	m_instanceIndex = 0;
	m_currentInstance = NULL;
	m_hasScript = CFalse;
	Cpy(m_script, "\n");
}

CPrefab::~CPrefab()
{
	for (CUInt i = 0; i < 3; i++)
	{
		CDelete(m_lod[i]);
	}
}

CVoid CPrefab::SetName(CChar* name)
{
	Cpy(m_name, name);
}

CVoid CPrefab::SetPackageName(CChar* name)
{
	Cpy(m_packageName, name);
}

CVoid CPrefab::SetPrefabName(CChar* name)
{
	Cpy(m_prefabName, name);
}

CVoid CPrefab::SetHasLod(CUInt index)
{
	m_hasLod[index] = CTrue;
}

CBool CPrefab::GetHasLod(CUInt index)
{
	return m_hasLod[index];
}

CChar* CPrefab::GetName()
{
	return m_name;
}

CChar* CPrefab::GetPackageName()
{
	return m_packageName;
}

CChar* CPrefab::GetPrefabName()
{
	return m_prefabName;
}

CVoid CPrefab::SetInstance(CInstancePrefab* instance)
{
	m_instance.push_back(instance);
	m_instanceIndex++;
}

CVoid CInstancePrefab::ResetLua()
{
	LuaClose(m_lua);
	m_lua = LuaNewState();
	LuaOpenLibs(m_lua);
	LuaRegisterFunctions(m_lua);
}

CBool CInstancePrefab::LoadLuaFile()
{
	ResetLua();
	if (!LuaLoadFile(m_lua, m_script))
		return CFalse;
	return CTrue;
}

CVoid CInstancePrefab::InitScript()
{
	if (m_hasScript)
	{
		g_currentInstancePrefab = this;

		lua_getglobal(m_lua, "Init");
		if (lua_isfunction(m_lua, -1))
		{
			lua_pcall(m_lua, 0, 0, 0);
		}

		lua_settop(m_lua, 0);
	}
}

CVoid CInstancePrefab::UpdateScript()
{
	if (m_hasScript)
	{
		g_currentInstancePrefab = this;

		lua_getglobal(m_lua, "Update");
		if (lua_isfunction(m_lua, -1))
		{
			lua_pcall(m_lua, 0, 0, 0);
		}

		lua_settop(m_lua, 0);
	}
}

CVoid CInstancePrefab::OnTriggerEnterScript(CChar *otherActorName)
{
	if (m_hasScript)
	{
		g_currentInstancePrefab = this;

		lua_getglobal(m_lua, "OnTriggerEnter");
		if (lua_isfunction(m_lua, -1))
		{
			lua_pushstring(m_lua, otherActorName);
			lua_pcall(m_lua, 1, 0, 0);
		}

		lua_settop(m_lua, 0);
	}
}


CVoid CInstancePrefab::OnTriggerStayScript(CChar *otherActorName)
{
	if (m_hasScript)
	{
		g_currentInstancePrefab = this;

		lua_getglobal(m_lua, "OnTriggerStay");
		if (lua_isfunction(m_lua, -1))
		{
			lua_pushstring(m_lua, otherActorName);
			lua_pcall(m_lua, 1, 0, 0);
		}

		lua_settop(m_lua, 0);
	}
}

CVoid CInstancePrefab::OnTriggerExitScript(CChar *otherActorName)
{
	if (m_hasScript)
	{
		g_currentInstancePrefab = this;

		lua_getglobal(m_lua, "OnTriggerExit");
		if (lua_isfunction(m_lua, -1))
		{
			lua_pushstring(m_lua, otherActorName);
			lua_pcall(m_lua, 1, 0, 0);
		}

		lua_settop(m_lua, 0);
	}
}

CVoid CInstancePrefab::OnSelectScript()
{
	if (m_hasScript)
	{
		g_currentInstancePrefab = this;

		lua_getglobal(m_lua, "OnSelect");
		if (lua_isfunction(m_lua, -1))
		{
			lua_pcall(m_lua, 0, 0, 0);
		}

		lua_settop(m_lua, 0);
	}
}

CInstancePrefab* CPrefab::GetInstance(CUInt index)
{
	return m_instance[index];
}

CVoid CPrefab::SetCurrentInstance(CInstancePrefab* instance)
{
	m_currentInstance = instance;
}

CInstancePrefab* CPrefab::GetCurrentInstance()
{
	return m_currentInstance;
}


CVoid CPrefab::RemoveInstance(CUInt index)
{
	m_instance.erase(m_instance.begin() + index);
}

CUInt CPrefab::GetNumInstances()
{
	return m_instance.size();
}

CUInt CPrefab::GetInstanceIndex()
{
	return m_instanceIndex;
}

CVLOD* CPrefab::GetLOD(CInt index)
{
	return m_lod[index];
}

CInstancePrefab::CInstancePrefab()
{
	m_isVisible = CTrue;
	m_isTrigger = CFalse;
	m_isSceneVisible[0] = CTrue;
	m_isSceneVisible[1] = CFalse;
	m_isSceneVisible[2] = CFalse;
	m_water = NULL;
	memset(m_scene, 0, sizeof(m_scene));
	m_hasCollider = CFalse;
	m_minAABB.x = m_minAABB.y = m_minAABB.z = 100000000.0f;
	m_maxAABB.x = m_maxAABB.y = m_maxAABB.z = -100000000.0f;

	m_translate.x = m_translate.y = m_translate.z = 0.0f;
	m_scale.x = m_scale.y = m_scale.z = 1.0f;
	//rotate 0 degrees around all axes
	m_rotate.x = m_rotate.y = m_rotate.z = 0.0f;  //x axis

	CVec4f trans(m_translate.x, m_translate.y, m_translate.z, 1.0f);
	CVec4f rot(m_rotate.x, m_rotate.y, m_rotate.z, m_rotate.w);
	CVec4f scale(m_scale.x, m_scale.y, m_scale.z, 1.0f);

	CMatrixLoadIdentity(m_instanceMatrix);
	CMatrix4x4Translate(m_instanceMatrix, trans);
	CMatrix4x4RotateAngleAxis(m_instanceMatrix, rot);
	CMatrix4x4Scale(m_instanceMatrix, scale);
	m_elapsedTime = 0.0f;
	m_prefab = NULL;
	Cpy(m_script, "\n");
	m_renderForQuery = CFalse;
	m_realTimeSceneCheckIsInFrustom = CTrue; //by default sences are checked to see if they are in frustom
	m_isControlledByPhysX = CFalse;
	m_isAnimated = CFalse;
	m_isStatic = CFalse;
	for (CUInt i = 0; i < 8; i++)
		m_lights[i] = NULL;
	m_lightCooked = CFalse;
	m_castShadow = CTrue;
	m_isTransformable = CFalse;
	m_isSelectable = CFalse;

	m_fAmbientColor[0] = m_fAmbientColor[1] = m_fAmbientColor[2] = 0.5f; m_fAmbientColor[3] = 1.0f;
	m_fDiffuseColor[0] = m_fDiffuseColor[1] = m_fDiffuseColor[2] = 0.5f; m_fDiffuseColor[3] = 1.0f;
	m_fSpecularColor[0] = m_fSpecularColor[1] = m_fSpecularColor[2] = 0.5f; m_fSpecularColor[3] = 1.0f;
	m_fEmissionColor[0] = m_fEmissionColor[1] = m_fEmissionColor[2] = 0.5f; m_fEmissionColor[3] = 1.0f;
	m_fShininess = 50.0f;
	m_fTransparency = 1.0f;
	m_enableMaterial = CFalse;

	m_lua = LuaNewState();
	LuaOpenLibs(m_lua);
	LuaRegisterFunctions(m_lua);
}

CInstancePrefab::~CInstancePrefab()
{
	glDeleteQueries(1, &m_queryIndex);
	glDeleteQueries(1, &m_waterQueryIndex);
	LuaClose(m_lua);
}

CVoid CInstancePrefab::SetWater(CWater* water)
{
	m_water = water;
}

inline CFloat CInstancePrefab::squared(CFloat v) { return v * v; }
CBool CInstancePrefab::DoesLightIntersectsPrefab(CVec3f C1, CVec3f C2, CVec3f S, CFloat R)
{
	CFloat dist_squared = R * R;
	/* assume C1 and C2 are element-wise sorted, if not, do that now */
	if (S.x < C1.x) dist_squared -= squared(S.x - C1.x);
	else if (S.x > C2.x) dist_squared -= squared(S.x - C2.x);
	if (S.y < C1.y) dist_squared -= squared(S.y - C1.y);
	else if (S.y > C2.y) dist_squared -= squared(S.y - C2.y);
	if (S.z< C1.z) dist_squared -= squared(S.z - C1.z);
	else if (S.z > C2.z) dist_squared -= squared(S.z - C2.z);
	return dist_squared > 0;
}

CVoid CInstancePrefab::SetLight()
{
	if (!GetVisible()) return;
	m_totalVisibleLights = 0;
	if (!GetIsAnimated() && !GetIsControlledByPhysX() && m_lightCooked)
	{
		if (g_engineLights.size() == 0)
		{
			m_totalLights = 1.0f; //default point light attached to the camera
			return;
		}

		for (CUInt j = 0; j < m_totalLights; j++)
		{
			if (m_lights[j])
			{
				CBool isDirectional = CFalse;
				CBool isDefaultDirectional = CFalse;
				if (m_lights[j]->m_abstractLight->GetType() == eLIGHTTYPE_DIRECTIONAL)
					isDirectional = CTrue;
				else if (!m_lights[j]->GetRunTimeVisible()) //it's point or spot light
					continue;

				if (isDirectional && Cmp(g_shadowProperties.m_directionalLightName, m_lights[j]->m_abstractLight->GetName()))
					isDefaultDirectional = CTrue;

				g_render.SetInstanceLight(m_lights[j], m_totalVisibleLights, isDefaultDirectional);
				m_totalVisibleLights++;
			}
		}
		return;
	}
	CBool skipCheck = CFalse;
	if (!GetIsAnimated() && !GetIsControlledByPhysX())
		skipCheck = CTrue;

	if (g_engineLights.size() == 0)
	{
		m_totalLights = 1.0f; //default point light attached to the camera
		return;
	}
	for (CUInt i = 0; i < 8; i++)
	{
		m_lights[i] = NULL;
		m_totalLights = 0;
	}
	CInt directional_light_index = 0;
	for (CUInt i = 0; i < g_engineLights.size(); i++)
	{
		if (g_engineLights[i]->m_abstractLight->GetType() == eLIGHTTYPE_DIRECTIONAL)
		{
			m_lights[directional_light_index] = g_engineLights[i];
			directional_light_index++;
			if (directional_light_index >= NR_DIR_LIGHTS)
				break;
		}
	}
	CInt point_light_index = 0;
	for (CUInt i = 0; i < g_engineLights.size(); i++)
	{
		if (g_engineLights[i]->m_abstractLight->GetType() == eLIGHTTYPE_POINT)
		{
			if (DoesLightIntersectsPrefab(m_minAABB, m_maxAABB, g_engineLights[i]->GetPosition(), g_engineLights[i]->GetRadius()))
			{
				if (skipCheck)
				{
					m_lights[point_light_index + directional_light_index] = g_engineLights[i];
					point_light_index++;
					if (point_light_index >= NR_POINT_LIGHTS)
						break;
				}
				else if (g_engineLights[i]->GetRunTimeVisible())
				{
					m_lights[point_light_index + directional_light_index] = g_engineLights[i];
					point_light_index++;
					if (point_light_index >= NR_POINT_LIGHTS)
						break;
				}
			}
		}
	}
	CInt spot_light_index = 0;
	for (CUInt i = 0; i < g_engineLights.size(); i++)
	{
		if (g_engineLights[i]->m_abstractLight->GetType() == eLIGHTTYPE_SPOT)
		{
			if (DoesLightIntersectsPrefab(m_minAABB, m_maxAABB, g_engineLights[i]->GetPosition(), g_engineLights[i]->GetRadius()))
			{
				if (skipCheck)
				{
					m_lights[spot_light_index + point_light_index + directional_light_index] = g_engineLights[i];
					spot_light_index++;
					if (spot_light_index >= NR_SPOT_LIGHTS)
						break;
				}
				else if (g_engineLights[i]->GetRunTimeVisible())
				{
					m_lights[spot_light_index + point_light_index + directional_light_index] = g_engineLights[i];
					spot_light_index++;
					if (spot_light_index >= NR_SPOT_LIGHTS)
						break;
				}
			}
		}
	}

	m_totalLights = directional_light_index + point_light_index + spot_light_index;
	//set all lights here
	for (CUInt j = 0; j < m_totalLights; j++)
	{
		if (m_lights[j])
		{
			CBool isDirectional = CFalse;
			CBool isDefaultDirectional = CFalse;
			if (m_lights[j]->m_abstractLight->GetType() == eLIGHTTYPE_DIRECTIONAL)
				isDirectional = CTrue;

			if (isDirectional && Cmp(g_shadowProperties.m_directionalLightName, m_lights[j]->m_abstractLight->GetName()))
				isDefaultDirectional = CTrue;

			g_render.SetInstanceLight(m_lights[j], j, isDefaultDirectional);
		}
	}
	m_totalVisibleLights = m_totalLights;
	m_lightCooked = CTrue;
}

CWater* CInstancePrefab::GetWater()
{
	return m_water;
}

CVoid CInstancePrefab::GenQueryIndex()
{
	glGenQueries(1, &m_queryIndex);
}

CVoid CInstancePrefab::SetRealTimeSceneCheckIsInFrustom(CBool check)
{
	m_realTimeSceneCheckIsInFrustom = check;
}

CVoid CInstancePrefab::SetElapsedTime(CFloat delta)
{
	m_elapsedTime += delta;
}

CFloat CInstancePrefab::GetElapsedTime()
{
	return (m_elapsedTime);
}

CVoid CInstancePrefab::ResetElapsedTime()
{
	m_elapsedTime = 0.0f;
}

CVoid CInstancePrefab::UpdateArrow(CBool readFromEditor)
{
	if (g_multipleView->IsPlayGameMode())
		return;
	if (m_nameIndex == g_selectedName || m_nameIndex == g_lastEngineObjectSelectedName)
	{
		g_tempLastEngineObjectSelectedName = m_nameIndex;
		if (g_currentTransformType == eCTranslate && g_transformObject)
		{
			if (g_mainCharacter && g_mainCharacter->GetInstancePrefab() && GetNameIndex() == g_mainCharacter->GetInstancePrefab()->GetNameIndex())
			{
				NxExtendedVec3 pos;
				pos.x = g_arrowPosition.x;
				pos.y = g_arrowPosition.y + (g_physXProperties.m_fCapsuleHeight * 0.5f) + g_physXProperties.m_fCapsuleRadius + g_physXProperties.m_fCharacterSkinWidth;
				pos.z = g_arrowPosition.z;

				g_multipleView->m_nx->gControllers->setPosition(pos);
				g_mainCharacter->SetPosition(g_arrowPosition);
			}
			m_translate.x = g_arrowPosition.x;
			m_translate.y = g_arrowPosition.y;
			m_translate.z = g_arrowPosition.z;
			UpdateBoundingBox();
			for (CUInt j = 0; j < g_instancePrefab.size(); j++)
			{
				g_instancePrefab[j]->SetLightCooked(CFalse);
			}
		}
		else if (g_currentTransformType == eCRotate && g_transformObject)
		{
			g_arrowPosition.x = m_translate.x;
			g_arrowPosition.y = m_translate.y;
			g_arrowPosition.z = m_translate.z;
			if (g_transformDirection == ZXTRANS || g_transformDirection == XTRANS)
			{
				if (g_currentInstancePrefab && g_mainCharacter && g_currentInstancePrefab == g_mainCharacter->GetInstancePrefab())
					return;
				if (readFromEditor)
					m_rotate.z = g_arrowRotate.x;
				else
					m_rotate.z -= g_arrowRotate.x;
				g_arrowRotate.x = g_arrowRotate.y = g_arrowRotate.z = 0.0f;
			}
			else if (g_transformDirection == YZTRANS || g_transformDirection == YTRANS)
			{
				if (g_currentInstancePrefab && g_mainCharacter && g_currentInstancePrefab == g_mainCharacter->GetInstancePrefab())
					return;

				if (readFromEditor)
					m_rotate.x = g_arrowRotate.z;
				else
					m_rotate.x += g_arrowRotate.z;
				g_arrowRotate.x = g_arrowRotate.y = g_arrowRotate.z = 0.0f;
			}
			else if (g_transformDirection == XYTRANS || g_transformDirection == ZTRANS)
			{
				
				if (readFromEditor)
					m_rotate.y = g_arrowRotate.y;
				else
				{
					m_rotate.y += g_arrowRotate.x;
				}
				g_arrowRotate.x = g_arrowRotate.y = g_arrowRotate.z = 0.0f;
			}
			UpdateBoundingBox();
			for (CUInt j = 0; j < g_instancePrefab.size(); j++)
			{
				g_instancePrefab[j]->SetLightCooked(CFalse);
			}
		}
		else if (g_currentTransformType == eCScale && g_transformObject)
		{
			g_arrowPosition.x = m_translate.x;
			g_arrowPosition.y = m_translate.y;
			g_arrowPosition.z = m_translate.z;

			if (g_transformDirection == FREETRANS)
			{
				CFloat size = g_arrowScale.Size();
				if (size > 0.0f)
				{
					if (g_arrowScale.x != 0)
					{
						g_arrowScale.z = g_arrowScale.y = g_arrowScale.x;
					}
					else if (g_arrowScale.y != 0)
					{
						g_arrowScale.z = g_arrowScale.x = g_arrowScale.y;
					}
					else if (g_arrowScale.z != 0)
					{
						g_arrowScale.x = g_arrowScale.y = g_arrowScale.z;
					}
				}
			}
			if (readFromEditor)
			{
				switch (g_transformDirection)
				{
				case XTRANS:
					m_scale.x = g_arrowScale.x;
					break;
				case YTRANS:
					m_scale.y = g_arrowScale.y;
					break;
				case ZTRANS:
					m_scale.z = g_arrowScale.z;
					break;
				}
			}
			else
				m_scale += g_arrowScale;

			if (m_scale.x <= 0.01f)
				m_scale.x = 0.01f;
			if (m_scale.y <= 0.01f)
				m_scale.y = 0.01f;
			if (m_scale.z <= 0.01f)
				m_scale.z = 0.01f;
			g_arrowScale.x = g_arrowScale.y = g_arrowScale.z = 0.0f;
			UpdateBoundingBox();
			for (CUInt j = 0; j < g_instancePrefab.size(); j++)
			{
				g_instancePrefab[j]->SetLightCooked(CFalse);
			}

			for (CUInt j = 0; j < g_instancePrefab.size(); j++)
			{
				if (g_instancePrefab[j]->GetScene(0) && g_instancePrefab[j]->GetScene(0)->CastShadow())
				{
					if (g_instancePrefab[j]->GetRadius() > g_maxInstancePrefabRadius)
						g_maxInstancePrefabRadius = g_instancePrefab[j]->GetRadius();
				}
			}

		}
		else if (!g_transformObject)
		{
			g_arrowPosition.x = m_translate.x;
			g_arrowPosition.y = m_translate.y;
			g_arrowPosition.z = m_translate.z;

			g_currentInstancePrefab = this;
			CBool updateBB = CFalse;
			for (CUInt i = 0; i < 3; i++)
			{
				if (GetPrefab()->GetHasLod(i))
				{
					CScene* scene = GetScene(i);
					if (scene->m_hasAnimation)
					{
						updateBB = CTrue;
						break;
					}
				}
			}
			if (!updateBB)
			{
				if (GetHasCollider())
				{
					CScene* scene = GetScene(3);
					if (scene->m_hasAnimation)
					{
						updateBB = CTrue;
					}
				}
			}

			if (updateBB)
				UpdateBoundingBox();

		}
		g_showArrow = CTrue;
	}

}

CVec3f CInstancePrefab::GetTranslate()
{
	return m_translate;
}

CVec4f CInstancePrefab::GetRotate()
{
	return m_rotate;
}

CVec3f CInstancePrefab::GetScale()
{
	return m_scale;
}

CVoid CInstancePrefab::SetName(CChar* name)
{
	Cpy(m_name, name);
}

CVoid CInstancePrefab::SetNameIndex()
{
	m_nameIndex = g_nameIndex++;
}

CChar* CInstancePrefab::GetName()
{
	return m_name;
}

CUInt CInstancePrefab::GetNameIndex()
{
	return m_nameIndex;
}

CVoid CInstancePrefab::SetPrefab(CPrefab* prefab)
{
	m_prefab = prefab;
}

CPrefab* CInstancePrefab::GetPrefab()
{
	return m_prefab;
}

CVoid CInstancePrefab::SetTranslate(CVec3f translate)
{
	m_translate = translate;
}

CVoid CInstancePrefab::SetRotate(CVec4f rotate)
{
	m_rotate = rotate;
}

CVoid CInstancePrefab::SetScale(CVec3f scale)
{
	m_scale = scale;
}

CVoid CInstancePrefab::SetVisible(CBool isVisible)
{
	m_isVisible = isVisible;
	UpdateBoundingBox();
	CalculateDistance();
	UpdateIsStaticOrAnimated();
}

CVoid CInstancePrefab::SetSceneVisible(CUInt index, CBool status)
{
	m_isSceneVisible[index] = status;
}

CVoid CInstancePrefab::SetIsTrigger(CBool isTrigger)
{
	m_isTrigger = isTrigger;
}

CVoid CInstancePrefab::SetRenderForQuery(CBool query)
{
	m_renderForQuery = query;
}

CBool CInstancePrefab::GetRenderForQuery()
{
	return m_renderForQuery;
}

CVoid CInstancePrefab::SetRenderForWaterQuery(CBool query)
{
	m_renderForWaterQuery = query;
}

CBool CInstancePrefab::GetRenderForWaterQuery()
{
	return m_renderForWaterQuery;
}

CBool CInstancePrefab::GetVisible()
{
	CBool RunTimeVisible = CFalse;

	if (g_currentCameraType == eCAMERA_DEFAULT_FREE_NO_PHYSX)
	{
		//if (GetDistanceFromCamera() < g_cameraProperties.m_freePerspectiveFCP + GetRadius()) RunTimeVisible = CTrue;
		if (m_isVisible)
			return CTrue;
		else
			return CFalse;
	}
	else if (g_currentCameraType == eCAMERA_COLLADA)
	{
		for (CUInt i = 0; i < g_importedCameraInstances.size(); i++)
		{
			for (CUInt j = 0; j < 3; j++)
			{
				if (GetPrefab() && GetPrefab()->GetHasLod(j))
				{
					CScene* scene = GetScene(j);
					if (!scene) continue;

					if (g_importedCameraInstances[i]->m_parent->GetScene() == scene)
						return CTrue;
				}
			}

		}
	}

	for (CUInt j = 2; j >= 0; j--)
	{
		if (GetPrefab() && GetPrefab()->GetHasLod(j))
		{
			CScene* scene = GetScene(j);
			if (!scene) continue;

			if (scene->m_alwaysVisible)
				RunTimeVisible = CTrue;

			break;
		}
	}
	if (!RunTimeVisible)
		if (GetDistanceFromCamera() < g_instancePrefabLODPercent.m_lod4ObjectCameraDistance + GetRadius()) RunTimeVisible = CTrue;

	if (m_isVisible && RunTimeVisible)
		return CTrue;
	else
		return CFalse;
}

CBool CInstancePrefab::GetIsTrigger()
{
	return m_isTrigger;
}

CBool CInstancePrefab::GetRealTimeSceneCheckIsInFrustom()
{
	return m_realTimeSceneCheckIsInFrustom;
}

CBool CInstancePrefab::GetSceneVisible(CUInt index)
{
	return 	m_isSceneVisible[index];
}

CFloat CInstancePrefab::GetDistanceFromCamera()
{
	return m_distanceFromCamera;
}

CVoid CInstancePrefab::SetScene(CUInt index, CScene* scene)
{
	m_scene[index] = scene;
}

CScene* CInstancePrefab::GetScene(CUInt index)
{
	return m_scene[index];
}

CVec3f CInstancePrefab::GetMinAABB()
{
	return m_minAABB;
}

CVec3f CInstancePrefab::GetMaxAABB()
{
	return m_maxAABB;
}

CVec3f CInstancePrefab::GetInverseMinAABB()
{
	return m_inverseMinAABB;
}

CVec3f CInstancePrefab::GetInverseMaxAABB()
{
	return m_inverseMaxAABB;
}

GLuint CInstancePrefab::GetQueryIndex()
{
	return m_queryIndex;
}

GLuint CInstancePrefab::GetWaterQueryIndex()
{
	return m_waterQueryIndex;
}

CVoid CInstancePrefab::GenWaterQueryIndex()
{
	glGenQueries(1, &m_waterQueryIndex);
}

CVoid CInstancePrefab::DeleteWaterQueryIndex()
{
	glDeleteQueries(1, &m_waterQueryIndex);
}

GLint CInstancePrefab::GetResult()
{
	return m_result;
}

CVec3f CInstancePrefab::GetCenter()
{
	return m_center;
}

CVoid CInstancePrefab::SetScript(CChar* enter)
{
	Cpy(m_script, enter);
}

CChar* CInstancePrefab::GetScript()
{
	return m_script;
}

CVoid CInstancePrefab::SetResult(GLint result)
{
	m_result = result;
}

CVoid CInstancePrefab::CalculateDistance()
{
	if (g_camera)
	{
		CFloat x = g_camera->m_perspectiveCameraPos.x - m_center.x;
		CFloat y = g_camera->m_perspectiveCameraPos.y - m_center.y;
		CFloat z = g_camera->m_perspectiveCameraPos.z - m_center.z;

		m_distanceFromCamera = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
	}
}

CVoid CInstancePrefab::UpdateBoundingBoxForWater(CFloat height)
{
	//Inverse Matrix:Begin//
	CVec4f transInverse(0.0f, height * 2.0f, 0.0f, 1.0f);
	//CVec4f rotInverse(0.0f, 0.0f, 0.0f, 0.0f);
	CVec4f scaleInverse(1.0f, -1.0f, 1.0f, 1.0f);

	CMatrixLoadIdentity(m_inverseInstanceMatrix);
	CMatrix4x4Translate(m_inverseInstanceMatrix, transInverse);
	//CMatrix4x4RotateAngleAxis(m_inverseInstanceMatrix, rotInverse);
	CMatrix4x4Scale(m_inverseInstanceMatrix, scaleInverse);

	CVec3f m_inverseMinAABBResult, m_inverseMaxAABBResult;
	CMatrixTransform(m_inverseInstanceMatrix, m_minAABB, m_inverseMinAABB);
	CMatrixTransform(m_inverseInstanceMatrix, m_maxAABB, m_inverseMaxAABB);

	//Inverse Matrix:End//
}

CVoid CInstancePrefab::UpdateBoundingBox(CBool init)
{
	m_minAABB.x = m_minAABB.y = m_minAABB.z = 100000000.0f;
	m_maxAABB.x = m_maxAABB.y = m_maxAABB.z = -100000000.0f;

	CVec4f trans(m_translate.x, m_translate.y, m_translate.z, 1.0f);
	CVec4f scale(m_scale.x, m_scale.y, m_scale.z, 1.0f);
	CVec4f rotx(1.0f, 0.0f, 0.0f, m_rotate.x);
	CVec4f roty(0.0f, 1.0f, 0.0f, m_rotate.y);
	CVec4f rotz(0.0f, 0.0f, 1.0f, m_rotate.z);
	CMatrixLoadIdentity(m_instanceMatrix);
	CMatrix4x4Translate(m_instanceMatrix, trans);
	CMatrix4x4RotateAngleAxis(m_instanceMatrix, rotx);
	CMatrix4x4RotateAngleAxis(m_instanceMatrix, roty);
	CMatrix4x4RotateAngleAxis(m_instanceMatrix, rotz);
	CMatrix4x4Scale(m_instanceMatrix, scale);

	g_currentInstancePrefab = this;

	for (CUInt i = 0; i < 4; i++)
	{
		CBool condition = CFalse;
		if (i < 3)
		{
			if (GetPrefab()->GetHasLod(i))
				condition = CTrue;
		}
		else
		{
			if (GetHasCollider())
				condition = CTrue;
		}
		if (condition)
		{
			CScene* scene = GetScene(i);
			if (init)
			{
				if (scene)
				{
					if (scene->m_controllers.size() == 0)
					{
						scene->m_sceneRoot->SetLocalMatrix(&m_instanceMatrix);
					}
					g_render.SetScene(scene);
					scene->Update(0.00001);
				}
			}
			else if (scene && scene->m_isTransformable)
			{
				if (scene->m_controllers.size() == 0)
				{
					scene->m_sceneRoot->SetLocalMatrix(&m_instanceMatrix);
				}
			}
		}
	}

	CPrefab* prefab = GetPrefab();
	CScene* scene = NULL;
	std::vector <CInstanceGeometry*> geo_physx;
	CInt InstanceGeoSize = 0;

	for (CUInt i = 0; i < 4; i++)
	{
		if (i < 3)
		{
			if (prefab && prefab->GetHasLod(i))
				scene = GetScene(i);
		}
		else if (prefab && GetHasCollider())
		{
			scene = GetScene(i);
		}

		if (!scene) continue;

		for (CUInt j = 0; j < scene->m_instanceGeometries.size(); j++)
		{
			CGeometry * geometry = scene->m_instanceGeometries[j]->m_abstractGeometry;

			if ((!geometry->m_hasAnimation && scene->m_instanceGeometries[j]->m_hasPhysX && scene->m_instanceGeometries[j]->m_physXDensity > 0) && !init)
			{
				geo_physx.push_back(scene->m_instanceGeometries[j]);
			}
		}
	}

	scene = NULL;
	if (geo_physx.size())
	{
		for (CUInt l = 0; l < 4; l++)
		{
			if (l < 3)
			{
				if (prefab && prefab->GetHasLod(l))
					scene = GetScene(l);
			}
			else if (prefab && GetHasCollider())
			{
				scene = GetScene(l);
			}
			if (!scene) continue;

			for (CUInt i = 0; i < geo_physx.size(); i++)
			{
				for (CUInt j = 0; j < scene->m_instanceGeometries.size(); j++)
				{
					if (Cmp(geo_physx[i]->m_abstractGeometry->GetName(), scene->m_instanceGeometries[j]->m_abstractGeometry->GetName()))
					{
						if (scene->m_instanceGeometries[j]->m_hasPhysX && scene->m_instanceGeometries[j]->m_physXDensity > 0.0f)
							continue;
						if (scene->m_instanceGeometries[j]->m_abstractGeometry->m_hasAnimation)
							continue;

						scene->m_instanceGeometries[j]->m_renderWithPhysX = CTrue;
						CMatrix m;
						CMatrixCopy(geo_physx[i]->m_localToWorldMatrixControlledByPhysX, m);
						scene->m_instanceGeometries[j]->m_node->SetLocalToWorldMatrix(&m);
						g_render.SetScene(scene);
						scene->Update(0.0f, CFalse);
					}
				}
			}
		}
	}

	for (CUInt i = 0; i < 3; i++)
	{
		if (prefab && prefab->GetHasLod(i))
			scene = GetScene(i);

		if (!scene) continue;

		for (CUInt j = 0; j < scene->m_instanceGeometries.size(); j++)
		{
			CGeometry * geometry = scene->m_instanceGeometries[j]->m_abstractGeometry;

			if ((!geometry->m_hasAnimation && scene->m_instanceGeometries[j]->m_hasPhysX && scene->m_instanceGeometries[j]->m_physXDensity > 0) && !init)
			{
				if (scene->m_instanceGeometries[j]->m_minLocalToWorldAABBControlledByPhysX.x < m_minAABB.x)
					m_minAABB.x = scene->m_instanceGeometries[j]->m_minLocalToWorldAABBControlledByPhysX.x;
				if (scene->m_instanceGeometries[j]->m_minLocalToWorldAABBControlledByPhysX.y < m_minAABB.y)
					m_minAABB.y = scene->m_instanceGeometries[j]->m_minLocalToWorldAABBControlledByPhysX.y;
				if (scene->m_instanceGeometries[j]->m_minLocalToWorldAABBControlledByPhysX.z < m_minAABB.z)
					m_minAABB.z = scene->m_instanceGeometries[j]->m_minLocalToWorldAABBControlledByPhysX.z;

				if (scene->m_instanceGeometries[j]->m_maxLocalToWorldAABBControlledByPhysX.x > m_maxAABB.x)
					m_maxAABB.x = scene->m_instanceGeometries[j]->m_maxLocalToWorldAABBControlledByPhysX.x;
				if (scene->m_instanceGeometries[j]->m_maxLocalToWorldAABBControlledByPhysX.y > m_maxAABB.y)
					m_maxAABB.y = scene->m_instanceGeometries[j]->m_maxLocalToWorldAABBControlledByPhysX.y;
				if (scene->m_instanceGeometries[j]->m_maxLocalToWorldAABBControlledByPhysX.z > m_maxAABB.z)
					m_maxAABB.z = scene->m_instanceGeometries[j]->m_maxLocalToWorldAABBControlledByPhysX.z;
			}
			else
			{
				if (scene->m_instanceGeometries[j]->m_minLocalToWorldAABB.x < m_minAABB.x)
					m_minAABB.x = scene->m_instanceGeometries[j]->m_minLocalToWorldAABB.x;
				if (scene->m_instanceGeometries[j]->m_minLocalToWorldAABB.y < m_minAABB.y)
					m_minAABB.y = scene->m_instanceGeometries[j]->m_minLocalToWorldAABB.y;
				if (scene->m_instanceGeometries[j]->m_minLocalToWorldAABB.z < m_minAABB.z)
					m_minAABB.z = scene->m_instanceGeometries[j]->m_minLocalToWorldAABB.z;

				if (scene->m_instanceGeometries[j]->m_maxLocalToWorldAABB.x > m_maxAABB.x)
					m_maxAABB.x = scene->m_instanceGeometries[j]->m_maxLocalToWorldAABB.x;
				if (scene->m_instanceGeometries[j]->m_maxLocalToWorldAABB.y > m_maxAABB.y)
					m_maxAABB.y = scene->m_instanceGeometries[j]->m_maxLocalToWorldAABB.y;
				if (scene->m_instanceGeometries[j]->m_maxLocalToWorldAABB.z > m_maxAABB.z)
					m_maxAABB.z = scene->m_instanceGeometries[j]->m_maxLocalToWorldAABB.z;
			}
			InstanceGeoSize++;
		}

	}

	if (InstanceGeoSize == 0)
	{
		m_minAABB.x = m_maxAABB.x = 0.0f;
		m_minAABB.y = m_maxAABB.y = 0.0f;
		m_minAABB.z = m_maxAABB.z = 0.0f;
	}
	m_center = (m_minAABB + m_maxAABB) * 0.5f;
	CFloat x, y, z;
	x = fabs(m_maxAABB.x - m_minAABB.x) / 2.f;
	y = fabs(m_maxAABB.y - m_minAABB.y) / 2.f;
	z = fabs(m_maxAABB.z - m_minAABB.z) / 2.f;
	m_radius = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));

	m_boundingBox[0].x = m_minAABB.x; m_boundingBox[0].y = m_minAABB.y; m_boundingBox[0].z = m_minAABB.z;
	m_boundingBox[1].x = m_maxAABB.x; m_boundingBox[1].y = m_minAABB.y; m_boundingBox[1].z = m_maxAABB.z;
	m_boundingBox[2].x = m_maxAABB.x; m_boundingBox[2].y = m_minAABB.y; m_boundingBox[2].z = m_minAABB.z;
	m_boundingBox[3].x = m_minAABB.x; m_boundingBox[3].y = m_minAABB.y; m_boundingBox[3].z = m_maxAABB.z;
	m_boundingBox[4].x = m_maxAABB.x; m_boundingBox[4].y = m_maxAABB.y; m_boundingBox[4].z = m_minAABB.z;
	m_boundingBox[5].x = m_minAABB.x; m_boundingBox[5].y = m_maxAABB.y; m_boundingBox[5].z = m_minAABB.z;
	m_boundingBox[6].x = m_minAABB.x; m_boundingBox[6].y = m_maxAABB.y; m_boundingBox[6].z = m_maxAABB.z;
	m_boundingBox[7].x = m_maxAABB.x; m_boundingBox[7].y = m_maxAABB.y; m_boundingBox[7].z = m_maxAABB.z;

	if (m_water)
		UpdateBoundingBoxForWater(m_water->GetHeight());
	geo_physx.clear();
}

CFloat CInstancePrefab::GetRadius()
{
	return m_radius;
}

CVoid CInstancePrefab::UpdateIsStaticOrAnimated()
{
	if (m_prefab == NULL) return;
	for (CUInt i = 0; i < 4; i++)
	{
		CBool condition = CFalse;
		if (i < 3)
		{
			if ( GetPrefab()->GetHasLod(i) )
				condition = CTrue;
		}
		else if ( GetHasCollider() )
		{
			condition = CTrue;
		}

		if (condition)
		{
			CScene* scene = GetScene(i);
			if (!scene) continue;
			if (!scene->m_isTrigger)
			{
				for (CUInt j = 0; j < scene->m_instanceGeometries.size(); j++)
				{
					if (scene->m_instanceGeometries[j]->GetHasPhysXActor() && scene->m_instanceGeometries[j]->GetPhysXActorDensity() > 0.0f)
						m_isControlledByPhysX = CTrue;
					if (scene->m_instanceGeometries[j]->m_abstractGeometry->m_hasAnimation)
						m_isAnimated = CTrue;

				}
			}
		}
	}
	if (!m_isControlledByPhysX && !m_isAnimated)
		m_isStatic = CTrue;
}

CVLOD::CVLOD()
{
	Cpy(m_name, "\n");
	m_isVisible = CFalse;
	m_numVertices = 0;
}

CChar* CInstancePrefab::GetScriptStringVariable(CChar* variableName)
{
	CChar *s = NULL;
	lua_getglobal(m_lua, variableName);
	if (!lua_isnil(m_lua, -1))
		s = _strdup(lua_tostring(m_lua, -1));
	else
		s = _strdup("");

	lua_pop(m_lua, 1);
	return s;
}

CBool CInstancePrefab::GetScriptBoolVariable(CChar* variableName)
{
	CInt value;
	CBool result;
	lua_getglobal(m_lua, variableName);
	value = lua_toboolean(m_lua, -1);
	if (value)
		result = CTrue;
	else
		result = CFalse;
	lua_pop(m_lua, 1);
	return result;
}

CInt CInstancePrefab::GetScriptIntVariable(CChar* variableName)
{
	CInt value;
	lua_getglobal(m_lua, variableName);
	value = lua_tointeger(m_lua, -1);
	lua_pop(m_lua, 1);
	return value;
}

CDouble CInstancePrefab::GetScriptDoubleVariable(CChar* variableName)
{
	CDouble value;
	lua_getglobal(m_lua, variableName);
	value = lua_tonumber(m_lua, -1);
	lua_pop(m_lua, 1);
	return value;
}

CVoid CInstancePrefab::SetScriptStringVariable(CChar* variableName, CChar* value)
{
	lua_pushstring(m_lua, value);
	lua_setglobal(m_lua, variableName);
}

CVoid CInstancePrefab::SetScriptBoolVariable(CChar* variableName, CBool value)
{
	lua_pushboolean(m_lua, value);
	lua_setglobal(m_lua, variableName);
}

CVoid CInstancePrefab::SetScriptIntVariable(CChar* variableName, CInt value)
{
	lua_pushinteger(m_lua, value);
	lua_setglobal(m_lua, variableName);
}

CVoid CInstancePrefab::SetScriptDoubleVariable(CChar* variableName, CDouble value)
{
	lua_pushnumber(m_lua, value);
	lua_setglobal(m_lua, variableName);
}

CVoid CInstancePrefab::AddPhysicsForce(CFloat forceX, CFloat forceY, CFloat forceZ, CFloat forcePower)
{
	std::vector<std::string> physics_actor;

	for (CUInt i = 0; i < 3; i++)
	{
		if (GetPrefab()->GetHasLod(i))
		{
			CScene* scene = GetScene(i);
			if (!scene) continue;
			if (!scene->m_isTrigger)
			{
				for (CUInt j = 0; j < scene->m_instanceGeometries.size(); j++)
				{
					if (scene->m_instanceGeometries[j]->GetHasPhysXActor())
					{
						if (scene->m_instanceGeometries[j]->m_physXDensity > 0.0f)
						{
							physics_actor.push_back(scene->m_instanceGeometries[j]->GetPhysXActorName());
						}
					}
				}
			}
		}
	}
	if (GetHasCollider())
	{
		CScene* scene = GetScene(3);
		for (CUInt j = 0; j < scene->m_instanceGeometries.size(); j++)
		{
			if (scene->m_instanceGeometries[j]->GetHasPhysXActor())
			{
				if (scene->m_instanceGeometries[j]->m_physXDensity > 0.0f)
				{
					physics_actor.push_back(scene->m_instanceGeometries[j]->GetPhysXActorName());
				}
			}
		}
	}

	for (CUInt i = 0; i < gPhysXscene->getNbActors(); i++)
	{
		for (CUInt j = 0; j < physics_actor.size(); j++)
		{
			if (gPhysXscene->getActors()[i]->getName() && Cmp(gPhysXscene->getActors()[i]->getName(), physics_actor[j].c_str()))
			{
				NxActor* currentActor = gPhysXscene->getActors()[i];

				NxVec3 forceDir(forceX, forceY, forceZ);

				g_multipleView->m_nx->ApplyForceToActor(currentActor, forceDir, forcePower);
			}
		}

	}

	physics_actor.clear();
}

CVoid CInstancePrefab::AddPhysicsTorque(CFloat torqueX, CFloat torqueY, CFloat torqueZ, CFloat torquePower)
{
	std::vector<std::string> physics_actor;

	for (CUInt i = 0; i < 3; i++)
	{
		if (GetPrefab()->GetHasLod(i))
		{
			CScene* scene = GetScene(i);
			if (!scene) continue;
			if (!scene->m_isTrigger)
			{
				for (CUInt j = 0; j < scene->m_instanceGeometries.size(); j++)
				{
					if (scene->m_instanceGeometries[j]->GetHasPhysXActor())
					{
						if (scene->m_instanceGeometries[j]->m_physXDensity > 0.0f)
						{
							physics_actor.push_back(scene->m_instanceGeometries[j]->GetPhysXActorName());
						}
					}
				}
			}
		}
	}
	if (GetHasCollider())
	{
		CScene* scene = GetScene(3);
		for (CUInt j = 0; j < scene->m_instanceGeometries.size(); j++)
		{
			if (scene->m_instanceGeometries[j]->GetHasPhysXActor())
			{
				if (scene->m_instanceGeometries[j]->m_physXDensity > 0.0f)
				{
					physics_actor.push_back(scene->m_instanceGeometries[j]->GetPhysXActorName());
				}
			}
		}
	}

	for (CUInt i = 0; i < gPhysXscene->getNbActors(); i++)
	{
		for (CUInt j = 0; j < physics_actor.size(); j++)
		{
			if (gPhysXscene->getActors()[i]->getName() && Cmp(gPhysXscene->getActors()[i]->getName(), physics_actor[j].c_str()))
			{
				NxActor* currentActor = gPhysXscene->getActors()[i];

				NxVec3 torqueDir(torqueX, torqueY, torqueZ);

				g_multipleView->m_nx->ApplyTorqueToActor(currentActor, torqueDir, torquePower);
			}
		}

	}

	physics_actor.clear();
}
