#pragma once
#include "Defines.h"
#include <vector>
#include <set>
#include <map>
#include "../GraphicsEngine/opengl.h"


class CScene;
class CPrefab;
class CWater;
class CInstanceLight;

struct CVLOD
{
	CChar m_name[MAX_NAME_SIZE]; //level of detail name = external_dae_file_lod[i].dae
	CBool m_isVisible; //is this lod visible?
	CInt m_numVertices; //number of vertices of this lod

	CVLOD();
};

class CInstancePrefab
{
public:
	CInstancePrefab();
	~CInstancePrefab();
	CVoid GenQueryIndex();
	CVoid GenWaterQueryIndex();
	CVoid DeleteWaterQueryIndex();
	CVec3f m_boundingBox[8];
	CInstanceLight* m_lights[8];
private:
	CChar m_name[MAX_NAME_SIZE];
	CPrefab* m_prefab;
	CVec3f m_translate;
	CVec4f m_rotate;
	CVec3f m_scale;
	CBool m_isVisible;
	CBool m_isSceneVisible[3];
	CScene* m_scene[4]; //Up to 3 LODs, one PhysX collider
	CBool m_hasCollider;
	CUInt m_nameIndex;
	CVec3f m_minAABB;
	CVec3f m_maxAABB;
	CVec3f m_inverseMinAABB;
	CVec3f m_inverseMaxAABB;
	CMatrix m_instanceMatrix;
	CMatrix m_inverseInstanceMatrix;
	GLuint m_queryIndex;
	GLuint m_waterQueryIndex;
	CFloat m_elapsedTime;
	CVec3f m_center;
	CFloat m_distanceFromCamera;
	CFloat m_radius;
	GLint m_result;
	CChar m_enterScript[MAX_NAME_SIZE];
	CChar m_exitScript[MAX_NAME_SIZE];
	CChar m_tempScriptPath[MAX_NAME_SIZE];
	CChar m_tempCurrentScriptPath[MAX_NAME_SIZE];
	CBool m_isTrigger;
	CBool m_renderForQuery;
	CBool m_renderForWaterQuery;
	CBool m_realTimeSceneCheckIsInFrustom;
	CWater* m_water;
	CBool m_isControlledByPhysX;
	CBool m_isAnimated;
	CBool m_isStatic;
	CUInt m_totalLights;
	CUInt m_totalVisibleLights;
	CBool m_lightCooked;
	CBool m_castShadow;

public:
	CVoid SetName(CChar* name);
	CVoid SetNameIndex();
	CVoid SetTranslate(CVec3f translate);
	CVoid SetRotate(CVec4f rotate);
	CVoid SetScale(CVec3f scale);
	CVoid SetPrefab(CPrefab* prefab);
	CVoid SetVisible(CBool isVisible);
	CVoid SetSceneVisible(CUInt index, CBool content);
	CVoid SetScene(CUInt index, CScene* scene);
	CVoid SetElapsedTime(CFloat delta);
	CVoid SetResult(GLint result);
	CVoid SetEnterScript(CChar* enter);
	CVoid SetExitScript(CChar* exit);
	CVoid SetIsTrigger(CBool isTrigger);
	CVoid SetRenderForQuery(CBool query);
	CVoid SetRenderForWaterQuery(CBool query);
	CVoid SetRealTimeSceneCheckIsInFrustom(CBool check);
	CVoid SetWater(CWater* water);
	CVoid SetLight();
	CBool GetLightCooked() { return m_lightCooked; }
	CVoid SetLightCooked(CBool set) { m_lightCooked = set; }
	inline CFloat squared(float v);
	CBool DoesLightIntersectsPrefab(CVec3f C1, CVec3f C2, CVec3f S, float R);
	CBool CastShadow() { return m_castShadow; }

	CVoid ResetElapsedTime();
	CScene* GetScene(CUInt index);
	CVec3f GetMinAABB();
	CVec3f GetMaxAABB();
	CVec3f GetInverseMinAABB();
	CVec3f GetInverseMaxAABB();
	GLuint GetQueryIndex();
	GLuint GetWaterQueryIndex();
	GLint GetResult();
	CBool GetRenderForQuery();
	CBool GetRenderForWaterQuery();
	CWater* GetWater();
	CUInt GetTotalLights() { return m_totalVisibleLights; }
	CChar* GetName();
	CUInt GetNameIndex();
	CPrefab* GetPrefab();
	CVec3f GetTranslate();
	CVec4f GetRotate();
	CVec3f GetScale();
	CBool GetVisible();
	CBool GetVisible2() { return m_isVisible; }
	CFloat GetElapsedTime();
	CBool GetSceneVisible(CUInt index);
	CFloat GetDistanceFromCamera();
	CBool GetIsTrigger();
	CBool GetRealTimeSceneCheckIsInFrustom();
	inline CMatrix *GetInstanceMatrix(){ return &m_instanceMatrix; }
	CBool GetIsControlledByPhysX() { return m_isControlledByPhysX; }
	CBool GetIsAnimated() { return m_isAnimated; }
	CBool GetIsStatic() { return m_isStatic; }

	CVoid UpdateBoundingBox(CBool init = CTrue);
	CVoid UpdateBoundingBoxForWater(CFloat height);
	CVoid UpdateArrow(CBool readFromEditor = CFalse);
	CVoid CalculateDistance();
	CFloat GetRadius();
	CVec3f GetCenter();
	CChar* GetEnterScript();
	CChar* GetExitScript();
	CVoid UpdateIsStaticOrAnimated();

	CVoid SetTempScriptPath(CChar* path) { Cpy(m_tempScriptPath, path); }
	CVoid SetTempCurrentScriptPath(CChar* path) { Cpy(m_tempCurrentScriptPath, path); }

	CChar* GetTempScriptPath() { return m_tempScriptPath; }
	CChar* GetTempCurrentScriptPath() { return m_tempCurrentScriptPath; }

	CVoid SetHasCollider(CBool set) { m_hasCollider = set; }
	CBool GetHasCollider() { return m_hasCollider; }

	CVoid SetIsControlledByPhysX(CBool set) { m_isControlledByPhysX = set; }
	CVoid SetIsAnimated(CBool set) { m_isAnimated = set; }
	CVoid SetIsStatic(CBool set) { m_isStatic = set; }
	CVoid SetTotalLights(CBool set) { m_totalLights = set; }
	CVoid SetCastShadow(CBool set) { m_castShadow = set; }

};

class CPrefab
{
public:
	CPrefab();
	~CPrefab();
private:
	CChar m_name[MAX_NAME_SIZE]; //prefab name
	CChar m_packageName[MAX_NAME_SIZE]; //prefab name
	CChar m_prefabName[MAX_NAME_SIZE]; //prefab name

	CVLOD* m_lod[3]; //up to 3 LODs
	CBool m_hasLod[3];
	std::vector <CInstancePrefab*> m_instance;
	CInstancePrefab* m_currentInstance;
	CUInt m_instanceIndex;
public:
	CVoid SetName(CChar* name);
	CVoid SetPackageName(CChar* name);
	CVoid SetPrefabName(CChar* name);
	CVoid SetHasLod(CUInt index);
	CVoid SetInstance(CInstancePrefab* instance);
	CVoid SetCurrentInstance(CInstancePrefab* instance);

	CVoid RemoveInstance(CUInt index);

	CChar* GetName();
	CChar* GetPackageName();
	CChar* GetPrefabName();
	CBool GetHasLod(CUInt index);
	CUInt GetNumInstances();
	CUInt GetInstanceIndex();
	CInstancePrefab* GetInstance(CUInt index);
	CInstancePrefab* GetCurrentInstance();
	CVLOD* GetLOD(CInt index);
};

