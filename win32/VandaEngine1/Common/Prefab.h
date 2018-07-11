#pragma once
#include "Defines.h"
#include <vector>
#include <set>
#include <map>
#include "../GraphicsEngine/opengl.h"

class CScene;
class CPrefab;

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
private:
	CChar m_name[MAX_NAME_SIZE];
	CPrefab* m_prefab;
	CVec3f m_translate;
	CVec4f m_rotate;
	CVec3f m_scale;
	CBool m_isVisible;
	CBool m_isSceneVisible[3];
	CScene* m_scene[3]; //Up to 3 LODs
	CUInt m_nameIndex;
	CVec3f m_minAABB;
	CVec3f m_maxAABB;
	CMatrix m_instanceMatrix;
	GLuint m_queryIndex;
	CFloat m_elapsedTime;
	CVec3f m_center;
	CFloat m_distanceFromCamera;
	CFloat m_radius;
	GLint m_result;
	CChar m_enterScript[MAX_NAME_SIZE];
	CChar m_exitScript[MAX_NAME_SIZE];
	CBool m_isTrigger;

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

	CVoid ResetElapsedTime();
	CScene* GetScene(CUInt index);
	CVec3f GetMinAABB();
	CVec3f GetMaxAABB();
	GLuint GetQueryIndex();
	GLint GetResult();

	CChar* GetName();
	CUInt GetNameIndex();
	CPrefab* GetPrefab();
	CVec3f GetTranslate();
	CVec4f GetRotate();
	CVec3f GetScale();
	CBool GetVisible();
	CFloat GetElapsedTime();
	CBool GetSceneVisible(CUInt index);
	CFloat GetDistanceFromCamera();
	CBool GetIsTrigger();
	inline CMatrix *GetInstanceMatrix(){ return &m_instanceMatrix; }

	CVoid UpdateBoundingBox(CBool init = CTrue);
	CVoid UpdateArrow(CBool readFromEditor = CFalse);
	CVoid CalculateDistance();
	CFloat GetRadius();
	CVec3f GetCenter();
	CChar* GetEnterScript();
	CChar* GetExitScript();
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

