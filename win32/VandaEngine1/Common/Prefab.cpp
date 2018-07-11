#include "stdafx.h"
#include "Utility.h"
#include "Prefab.h"
#include "../GraphicsEngine/scene.h"
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

	for (CUInt i = 0; i < 3; i++)
		m_scene[i] = NULL;
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
	Cpy(m_enterScript, "\n");
	Cpy(m_exitScript, "\n");
}

CInstancePrefab::~CInstancePrefab()
{
	glDeleteQueries(1, &m_queryIndex);
}

CVoid CInstancePrefab::GenQueryIndex()
{
	glGenQueries(1, &m_queryIndex);
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
	//if (m_nameIndex == g_selectedName || m_nameIndex == g_lastEngineObjectSelectedName)
	//{
	//	g_tempLastEngineObjectSelectedName = m_nameIndex;
	//	if (g_currentTransformType == eCTranslate && g_transformObject)
	//	{
	//		m_translate.x = g_arrowPosition.x;
	//		m_translate.y = g_arrowPosition.y;
	//		m_translate.z = g_arrowPosition.z;
	//		UpdateBoundingBox();
	//	}
	//	else if (g_currentTransformType == eCRotate && g_transformObject)
	//	{
	//		g_arrowPosition.x = m_translate.x;
	//		g_arrowPosition.y = m_translate.y;
	//		g_arrowPosition.z = m_translate.z;
	//		if (g_transformDirection == XTRANS)
	//		{
	//			if (g_arrowRotate.x > 0.0f)
	//				m_rotate.z -= 1.0f;
	//			else if (g_arrowRotate.x < 0.0f)
	//				m_rotate.z += 1.0f;
	//			g_arrowRotate.x = g_arrowRotate.y = g_arrowRotate.z = 0.0f;
	//		}
	//		else if (g_transformDirection == YTRANS)
	//		{
	//			if (g_arrowRotate.z > 0.0f)
	//				m_rotate.x += 1.0f;
	//			else if (g_arrowRotate.z < 0.0f)
	//				m_rotate.x -= 1.0f;
	//			g_arrowRotate.x = g_arrowRotate.y = g_arrowRotate.z = 0.0f;
	//		}
	//		else if (g_transformDirection == ZTRANS)
	//		{
	//			if (g_arrowRotate.y > 0.0f)
	//				m_rotate.y += 1.0f;
	//			else if (g_arrowRotate.y < 0.0f)
	//				m_rotate.y -= 1.0f;
	//			g_arrowRotate.y = g_arrowRotate.y = g_arrowRotate.z = 0.0f;
	//		}
	//		UpdateBoundingBox();
	//	}
	//	else if (g_currentTransformType == eCScale && g_transformObject)
	//	{
	//		g_arrowPosition.x = m_translate.x;
	//		g_arrowPosition.y = m_translate.y;
	//		g_arrowPosition.z = m_translate.z;

	//		m_scale += g_arrowScale * 0.3f;
	//		if (m_scale.x <= 0 || m_scale.y <= 0 || m_scale.z <= 0)
	//			return;
	//		g_arrowScale.x = g_arrowScale.y = g_arrowScale.z = 0.0f;
	//		UpdateBoundingBox();

	//	}
	//	else if (!g_transformObject)
	//	{
	//		g_arrowPosition.x = m_translate.x;
	//		g_arrowPosition.y = m_translate.y;
	//		g_arrowPosition.z = m_translate.z;

	//		g_currentInstancePrefab = this;
	//		CBool updateBB = CFalse;
	//		for (CUInt i = 0; i < 3; i++)
	//		{
	//			if (GetPrefab()->GetHasLod(i))
	//			{
	//				CScene* scene = GetScene(i);
	//				if (scene->m_hasAnimation)
	//				{
	//					updateBB = CTrue;
	//					break;
	//				}
	//			}
	//		}
	//		if (updateBB)
	//			UpdateBoundingBox();

	//	}

	//	g_showArrow = CTrue;
	//}

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
}

CVoid CInstancePrefab::SetSceneVisible(CUInt index, CBool status)
{
	m_isSceneVisible[index] = status;
}

CVoid CInstancePrefab::SetIsTrigger(CBool isTrigger)
{
	m_isTrigger = isTrigger;
}

CBool CInstancePrefab::GetVisible()
{
	return m_isVisible;
}

CBool CInstancePrefab::GetIsTrigger()
{
	return m_isTrigger;
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

GLuint CInstancePrefab::GetQueryIndex()
{
	return m_queryIndex;
}

GLint CInstancePrefab::GetResult()
{
	return m_result;
}

CVoid CInstancePrefab::SetResult(GLint result)
{
	m_result = result;
}

CVoid CInstancePrefab::CalculateDistance()
{
	CFloat x = g_camera->m_perspectiveCameraPos.x - m_center.x;
	CFloat y = g_camera->m_perspectiveCameraPos.y - m_center.y;
	CFloat z = g_camera->m_perspectiveCameraPos.z - m_center.z;

	m_distanceFromCamera = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
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
	for (CUInt i = 0; i < 3; i++)
	{
		if (GetPrefab()->GetHasLod(i))
		{

			CScene* scene = GetScene(i);
			if (init)
			{
				if (scene->m_controllers.size() == 0)
				{
					scene->m_sceneRoot->SetLocalMatrix(&m_instanceMatrix);
				}
				g_render.SetScene(scene);
				scene->Update(0.00001, CTrue);
			}
		}
	}
	CPrefab* prefab = GetPrefab();
	CScene* scene = NULL;
	if (prefab && prefab->GetHasLod(0))
		scene = GetScene(0); //I assume that all scenes use the same bounding box
	if (!scene) return;

	std::vector <CInstanceGeometry*> geo_physx;
	for (CUInt j = 0; j < scene->m_instanceGeometries.size(); j++)
	{
		CGeometry * geometry = scene->m_instanceGeometries[j]->m_abstractGeometry;

		if (!geometry->m_hasAnimation && scene->m_instanceGeometries[j]->m_hasPhysX && scene->m_instanceGeometries[j]->m_physXDensity > 0)
		{
			geo_physx.push_back(scene->m_instanceGeometries[j]);
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
	}

	m_center = (m_minAABB + m_maxAABB) * 0.5f;
	CFloat x, y, z;
	x = fabs(m_maxAABB.x - m_minAABB.x) / 2.f;
	y = fabs(m_maxAABB.y - m_minAABB.y) / 2.f;
	z = fabs(m_maxAABB.z - m_minAABB.z) / 2.f;
	m_radius = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));

	if (geo_physx.size())
	{
		if (prefab->GetHasLod(1))
			scene = GetScene(1);
		for (CUInt i = 0; i < geo_physx.size(); i++)
		{
			for (CUInt j = 0; j < scene->m_instanceGeometries.size(); j++)
			{
				if (Cmp(geo_physx[i]->m_abstractGeometry->GetName(), scene->m_instanceGeometries[j]->m_abstractGeometry->GetName()))
				{
					scene->m_instanceGeometries[j]->m_renderWithPhysX = CTrue;
					CMatrix m;
					CMatrixCopy(geo_physx[i]->m_localToWorldMatrixControlledByPhysX, m);
					scene->m_instanceGeometries[j]->m_node->SetLocalToWorldMatrix(&m);
					g_render.SetScene(scene);
					scene->Update(0.0f, CFalse, CFalse);
				}
			}
		}

		if (prefab->GetHasLod(2))
			scene = GetScene(2);
		for (CUInt i = 0; i < geo_physx.size(); i++)
		{
			for (CUInt j = 0; j < scene->m_instanceGeometries.size(); j++)
			{
				if (Cmp(geo_physx[i]->m_abstractGeometry->GetName(), scene->m_instanceGeometries[j]->m_abstractGeometry->GetName()))
				{
					scene->m_instanceGeometries[j]->m_renderWithPhysX = CTrue;
					CMatrix m;
					CMatrixCopy(geo_physx[i]->m_localToWorldMatrixControlledByPhysX, m);
					scene->m_instanceGeometries[j]->m_node->SetLocalToWorldMatrix(&m);
					g_render.SetScene(scene);
					scene->Update(0.0f, CFalse, CFalse);
				}
			}
		}
	}
	geo_physx.clear();

}

CFloat CInstancePrefab::GetRadius()
{
	return m_radius;
}

CVoid CInstancePrefab::SetEnterScript(CChar* enter)
{
	Cpy(m_enterScript, enter);
}

CVoid CInstancePrefab::SetExitScript(CChar* exit)
{
	Cpy(m_exitScript, exit);
}

CChar* CInstancePrefab::GetEnterScript()
{
	return m_enterScript;
}

CChar* CInstancePrefab::GetExitScript()
{
	return m_exitScript;
}

CVec3f CInstancePrefab::GetCenter()
{
	return m_center;
}

CVLOD::CVLOD()
{
	Cpy(m_name, "\n");
	m_isVisible = CFalse;
	m_numVertices = 0;
}





