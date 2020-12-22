//Copyright (C) 2020 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#include "StdAfx.h"
#include "ShadowMap.h"
#include "scene.h"
#include "..\VandaEngine1.h"

CShadowMap::CShadowMap(void)
{
	switch (g_shadowProperties.m_shadowResolution)
	{
	case eSHADOW_1024:
		depth_size = 1024;
		break;
	case eSHADOW_2048:
		depth_size = 2048;
		break;
	case eSHADOW_4096:
		depth_size = 4096;
		break;
	default:
		break;
	}

	split_weight = g_shadowProperties.m_shadowSplitWeight;

	switch (g_shadowProperties.m_shadowSplits)
	{
	case eSHADOW_1_SPLIT:
		cur_num_splits = 1;
		break;
	case eSHADOW_2_SPLITS:
		cur_num_splits = 2;
		break;
	case eSHADOW_3_SPLITS:
		cur_num_splits = 3;
		break;
	case eSHADOW_4_SPLITS:
		cur_num_splits = 4;
		break;
	default:
		break;
	}

	Init();
}

CShadowMap::~CShadowMap(void)
{
	Release();
}

CBool CShadowMap::Init()
{
	if (g_render.UsingFBOs() && g_render.UsingShader())
	{
		BSphere[0].center = vec3f(-256, 0.0, -256);
		BSphere[1].center = vec3f(-256, 0.0, 256);
		BSphere[2].center = vec3f(256, 0.0, 256);
		BSphere[3].center = vec3f(256, 0.0, -256);
		BSphere[0].radius = 50.0f;
		BSphere[1].radius = 50.0f;
		BSphere[2].radius = 50.0f;
		BSphere[3].radius = 50.0f;

		glGenFramebuffersEXT(1, &depth_fb);
		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, depth_fb);
		glDrawBuffer(GL_NONE);
		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);

		glGenTextures(1, &depth_tex_ar);

		glBindTexture(GL_TEXTURE_2D_ARRAY_EXT, depth_tex_ar);
		glTexImage3D(GL_TEXTURE_2D_ARRAY_EXT, 0, GL_DEPTH_COMPONENT24, depth_size, depth_size, MAX_SPLITS, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_2D_ARRAY_EXT, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D_ARRAY_EXT, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		GLfloat borderColor[4] = { 1 - g_shadowProperties.m_intensity, 1 - g_shadowProperties.m_intensity, 1 - g_shadowProperties.m_intensity, 1.0f };
		glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
		glTexParameteri(GL_TEXTURE_2D_ARRAY_EXT, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D_ARRAY_EXT, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D_ARRAY_EXT, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);

		for (int i = 0; i<MAX_SPLITS; i++)
		{
			// note that fov is in radians here and in OpenGL it is in degrees.
			// the 0.2f factor is important because we might get artifacts at
			// the screen borders.
			f[i].fov = DEG_TO_RAD(54.0f) + 0.2f;
			f[i].ratio = (double)g_width / (double)g_height;
		}
		return CTrue;
	}
	return CFalse;
}

CVoid CShadowMap::Release()
{
	glDeleteTextures(1, &depth_tex_ar);
	glDeleteFramebuffersEXT(1, &depth_fb);
}

CVoid CShadowMap::RegenerateDepthTex(GLuint depth_size)
{
	glDeleteTextures(1, &depth_tex_ar);
	glGenTextures(1, &depth_tex_ar);

	glBindTexture(GL_TEXTURE_2D_ARRAY_EXT, depth_tex_ar);
	glTexImage3D(GL_TEXTURE_2D_ARRAY_EXT, 0, GL_DEPTH_COMPONENT24, depth_size, depth_size, MAX_SPLITS, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D_ARRAY_EXT, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D_ARRAY_EXT, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	GLfloat borderColor[4] = { 1 - g_shadowProperties.m_intensity, 1 - g_shadowProperties.m_intensity, 1 - g_shadowProperties.m_intensity, 1.0f };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
	glTexParameteri(GL_TEXTURE_2D_ARRAY_EXT, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D_ARRAY_EXT, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D_ARRAY_EXT, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
}


// Compute the 8 corner points of the current view frustum
void CShadowMap::UpdateFrustumPoints(frustum &f, vec3f &center, vec3f &view_dir)
{
	vec3f up(0.0f, 1.0f, 0.0f);
	view_dir = normalize(view_dir);
	vec3f right = cross(view_dir, up);

	vec3f fc = center + view_dir*f.fard;
	vec3f nc = center + view_dir*f.neard;

	right = normalize(right);
	up = normalize(cross(right, view_dir));

	// these heights and widths are half the heights and widths of
	// the near and far plane rectangles
	float near_height = tan(f.fov / 2.0f) * f.neard;
	float near_width = near_height * f.ratio;
	float far_height = tan(f.fov / 2.0f) * f.fard;
	float far_width = far_height * f.ratio;

	f.point[0] = nc - up*near_height - right*near_width;
	f.point[1] = nc + up*near_height - right*near_width;
	f.point[2] = nc + up*near_height + right*near_width;
	f.point[3] = nc - up*near_height + right*near_width;

	f.point[4] = fc - up*far_height - right*far_width;
	f.point[5] = fc + up*far_height - right*far_width;
	f.point[6] = fc + up*far_height + right*far_width;
	f.point[7] = fc - up*far_height + right*far_width;
}


// updateSplitDist computes the near and far distances for every frustum slice
// in camera eye space - that is, at what distance does a slice start and end
void CShadowMap::UpdateSplitDist(frustum f[MAX_SPLITS], float nd, float fd)
{
	float lambda = split_weight;
	float ratio = fd / nd;
	f[0].neard = nd;

	for (int i = 1; i<cur_num_splits; i++)
	{
		float si = i / (float)cur_num_splits;

		f[i].neard = lambda*(nd*powf(ratio, si)) + (1 - lambda)*(nd + (fd - nd)*si);
		f[i - 1].fard = f[i].neard * 1.005f;
	}
	f[cur_num_splits - 1].fard = fd;
}

// this function builds a projection matrix for rendering from the shadow's POV.
// First, it computes the appropriate z-range and sets an orthogonal projection.
// Then, it translates and scales it, so that it exactly captures the bounding box
// of the current frustum slice
float CShadowMap::ApplyCropMatrix(frustum &f, vec3f cam_pos)
{
	float shad_modelview[16];
	float shad_proj[16];
	float shad_crop[16];
	float shad_mvp[16];
	float maxX = -2000.0f;
	float maxY = -2000.0f;
	float maxZ;
	float minX = 2000.0f;
	float minY = 2000.0f;
	float minZ;

	matrix4<float> nv_mvp;
	vec4f transf;

	// find the z-range of the current frustum as seen from the light
	// in order to increase precision
	glGetFloatv(GL_MODELVIEW_MATRIX, shad_modelview);
	nv_mvp.set_value(shad_modelview);

	// note that only the z-component is needed and thus
	// the multiplication can be simplified
	// transf.z = shad_modelview[2] * f.point[0].x + shad_modelview[6] * f.point[0].y + shad_modelview[10] * f.point[0].z + shad_modelview[14];
	transf = nv_mvp*vec4f(f.point[0], 1.0f);
	minZ = g_octree->m_minAABB.y /*transf.z*/;
	maxZ = g_octree->m_maxAABB.y /*transf.z*/;
	for (int i = 1; i<8; i++)
	{
		transf = nv_mvp*vec4f(f.point[i], 1.0f);
		if (transf.z > maxZ) maxZ = transf.z;
		if (transf.z < minZ) minZ = transf.z;
	}
	//make sure all relevant shadow casters are included
	//note that these here are dummy objects at the edges of our scene

	BSphere[0].center = cam_pos + vec3f(-g_shadowProperties.m_shadowFarClipPlane, 0.0, -g_shadowProperties.m_shadowFarClipPlane);
	BSphere[1].center = cam_pos + vec3f(-g_shadowProperties.m_shadowFarClipPlane, 0.0, g_shadowProperties.m_shadowFarClipPlane);
	BSphere[2].center = cam_pos + vec3f(g_shadowProperties.m_shadowFarClipPlane, 0.0, g_shadowProperties.m_shadowFarClipPlane);
	BSphere[3].center = cam_pos + vec3f(g_shadowProperties.m_shadowFarClipPlane, 0.0, -g_shadowProperties.m_shadowFarClipPlane);

	BSphere[0].radius = g_maxInstancePrefabRadius;
	BSphere[1].radius = g_maxInstancePrefabRadius;
	BSphere[2].radius = g_maxInstancePrefabRadius;
	BSphere[3].radius = g_maxInstancePrefabRadius;

	for (int i = 0; i<NUM_OBJECTS; i++)
	{
		transf = nv_mvp*vec4f(BSphere[i].center, 1.0f);
		if (transf.z + BSphere[i].radius > maxZ) maxZ = transf.z + BSphere[i].radius;
		//if(transf.z - BSphere[i].radius < minZ) minZ = transf.z - BSphere[i].radius;
	}

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// set the projection matrix with the new z-bounds
	// note the inversion because the light looks at the neg. z axis
	// gluPerspective(LIGHT_FOV, 1.0, maxZ, minZ); // for point lights
	glOrtho(-1.0, 1.0, -1.0, 1.0, -maxZ, -minZ);
	glGetFloatv(GL_PROJECTION_MATRIX, shad_proj);
	glPushMatrix();
	glMultMatrixf(shad_modelview);
	glGetFloatv(GL_PROJECTION_MATRIX, shad_mvp);
	glPopMatrix();

	// find the extends of the frustum slice as projected in light's homogeneous coordinates
	nv_mvp.set_value(shad_mvp);
	for (int i = 0; i<8; i++)
	{
		transf = nv_mvp*vec4f(f.point[i], 1.0f);

		transf.x /= transf.w;
		transf.y /= transf.w;

		if (transf.x > maxX) maxX = transf.x;
		if (transf.x < minX) minX = transf.x;
		if (transf.y > maxY) maxY = transf.y;
		if (transf.y < minY) minY = transf.y;
	}

	float scaleX = 2.0f / (maxX - minX);
	float scaleY = 2.0f / (maxY - minY);
	float offsetX = -0.5f*(maxX + minX)*scaleX;
	float offsetY = -0.5f*(maxY + minY)*scaleY;

	// apply a crop matrix to modify the projection matrix we got from glOrtho.
	nv_mvp.make_identity();
	nv_mvp.element(0, 0) = scaleX;
	nv_mvp.element(1, 1) = scaleY;
	nv_mvp.element(0, 3) = offsetX;
	nv_mvp.element(1, 3) = offsetY;
	transpose(nv_mvp);
	nv_mvp.get_value(shad_crop);
	glLoadMatrixf(shad_crop);
	glMultMatrixf(shad_proj);
	return minZ;
}

void CShadowMap::UpdateFOV()
{
	CFloat fov;
	if (g_currentCameraType == eCAMERA_DEFAULT_FREE_NO_PHYSX)
	{
		fov = g_render.GetDefaultInstanceCamera()->m_abstractCamera->GetAngle();
	}
	else if (g_currentCameraType == eCAMERA_COLLADA)
	{
		if (g_cameraProperties.m_readDAECameraFOVFromFile)
			fov = g_render.GetActiveInstanceCamera()->m_abstractCamera->GetYFov();
		else
			fov = g_cameraProperties.m_daeCameraFOV;
	}
	else if (g_currentCameraType == eCAMERA_PHYSX)
	{
		fov = g_camera->m_cameraManager->GetAngle();
	}
	else if (g_currentCameraType == eCAMERA_ENGINE)
	{
		fov = g_render.GetActiveInstanceCamera()->m_abstractCamera->GetAngle();
	}

	for (int i = 0; i<MAX_SPLITS; i++)
	{
		f[i].fov = DEG_TO_RAD(fov) + 0.2f;
	}
}

// here all shadow map textures and their corresponding matrices are created
void CShadowMap::MakeShadowMap(float cam_pos[3], float cam_view[3], float light_dir[4])
{
	glUseProgram(0);
	g_render.m_useShader = CFalse;
	g_renderShadow = CTrue;
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glPushAttrib(GL_VIEWPORT_BIT | GL_ENABLE_BIT);

	float shad_modelview[16];
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	// since the shadow maps have only a depth channel, we don't need color computation
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	gluLookAt(0, 0, 0, -light_dir[0], -light_dir[1], -light_dir[2], 0.0f, 1.0f, 0.0f);
	glGetFloatv(GL_MODELVIEW_MATRIX, shad_modelview);

	// redirect rendering to the depth texture
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, depth_fb);
	// and render only to the shadowmap
	glViewport(0, 0, depth_size, depth_size);
	// offset the geometry slightly to prevent z-fighting
	// note that this introduces some light-leakage artifacts
	//glPolygonOffset(1.0f, 2.0f);
	//glEnable(GL_POLYGON_OFFSET_FILL);
	//glCullFace( GL_FRONT );
	// I assume that our objects are closed, so I don't disable face culling.
	//glDisable(GL_CULL_FACE);

	// compute the z-distances for each split as seen in camera space
	UpdateSplitDist(f, g_shadowProperties.m_shadowNearClipPlane, g_shadowProperties.m_shadowFarClipPlane);

	UpdateFOV();

	// for all shadow maps:
	for (int i = 0; i<cur_num_splits; i++)
	{
		// compute the camera frustum slice boundary points in world space
		UpdateFrustumPoints(f[i], vec3f(cam_pos), vec3f(cam_view));

		// adjust the view frustum of the light, so that it encloses the camera frustum slice fully.
		// note that this function sets the projection matrix as it sees best fit
		// minZ is just for optimization to cull trees that do not affect the shadows
		float minZ = ApplyCropMatrix(f[i], vec3f(cam_pos));
		// make the current depth map a rendering target
		glFramebufferTextureLayerEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, depth_tex_ar, 0, i);

		// clear the depth texture from last time
		glClear(GL_DEPTH_BUFFER_BIT);
		for (CUInt j = 0; j < g_instancePrefab.size(); j++)
		{
			if (g_instancePrefab[j]->GetScene(0) && g_instancePrefab[j]->GetScene(0)->CastShadow())
			{
				g_currentInstancePrefab = g_instancePrefab[j];
				CPrefab* prefab = g_instancePrefab[j]->GetPrefab();
				CScene* scene = NULL;

				if (prefab)
				{
					//manage LOD here
					if (!g_currentInstancePrefab->GetVisible()) continue;
					if (g_currentInstancePrefab->GetDistanceFromCamera() > g_shadowProperties.m_shadowFarClipPlane + g_currentInstancePrefab->GetRadius()) continue;

					for (CUInt k = 0; k < 3; k++)
					{
						if (prefab->GetHasLod(k) && g_currentInstancePrefab->GetSceneVisible(k))
						{
							scene = g_currentInstancePrefab->GetScene(k);
							break;
						}
					}
					if (!scene)
					{
						//if instance is outside the frustom
						if (!g_currentInstancePrefab->GetRenderForQuery())
						{
							//if prefab instance is outside frustom, it may still cast shadows. 
							//select LOD 1 or 2 based on camera distance from camera.
							//Note that we don't have access to occlusion culling for objects outside the frustom
							if (g_currentInstancePrefab->GetDistanceFromCamera() > g_instancePrefabLODPercent.m_lod1MinObjectCameraDistance + g_currentInstancePrefab->GetRadius())
							{
								//select scene 2. If scene 2 is not available, select scene 1 instead
								if (prefab->GetHasLod(2))
								{
									scene = g_currentInstancePrefab->GetScene(2);
								}
								if (!scene)
								{
									if (prefab->GetHasLod(1))
										scene = g_currentInstancePrefab->GetScene(1);
								}
							}
							else
							{
								//select scene 1
								if (prefab->GetHasLod(1))
									scene = g_currentInstancePrefab->GetScene(1);
							}
						}
					}
				} //if prefab
				if (!scene)
					continue;
				else
					g_render.SetScene(scene);

				if (!g_render.GetScene()->m_isTrigger)
				{
					g_render.GetScene()->Render(CFalse, NULL, CTrue);

					g_render.ModelViewMatrix();
					g_render.PushMatrix();
					g_render.MultMatrix(*(g_instancePrefab[j]->GetInstanceMatrix()));
					g_render.GetScene()->RenderAnimatedModels(CFalse, CTrue);
					g_render.PopMatrix();

					g_render.GetScene()->RenderAnimatedModels(CFalse, CFalse);

					g_render.GetScene()->RenderModelsControlledByPhysX(CFalse);

				}
			} //if

		} //for

		//render terrain here
		//g_multipleView->m_terrain.drawShadow();

		glMatrixMode(GL_PROJECTION);
		// store the product of all shadow matries for later
		glMultMatrixf(shad_modelview);
		glGetFloatv(GL_PROJECTION_MATRIX, shad_cpm[i]);
	}
	g_renderShadow = CFalse;

	glDisable(GL_POLYGON_OFFSET_FILL);
	glCullFace(GL_BACK);

	glPopAttrib();
	if (!g_useOldRenderingStyle && g_multipleView->m_multiSample && g_options.m_numSamples && g_options.m_enableFBO)
		g_render.BindForWriting(g_multipleView->m_mFboID);
	else if (!g_useOldRenderingStyle && g_options.m_enableFBO)
		g_render.BindForWriting(g_multipleView->m_fboID);
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	g_render.m_useShader = CTrue;
}

void CShadowMap::ShowDepthTex()
{
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
	int loc;
	glPushAttrib(GL_VIEWPORT_BIT | GL_DEPTH_BUFFER_BIT | GL_ENABLE_BIT);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
	glDisable(GL_CULL_FACE);
	glUseProgram(g_render.m_shad_view_depth);
	glUniform1i(glGetUniformLocation(g_render.m_shad_view_depth, "tex"), 0);
	loc = glGetUniformLocation(g_render.m_shad_view_depth, "layer");
	for (int i = 0; i<cur_num_splits; i++)
	{
		if (!g_menu.m_justPerspective)
			glViewport(g_height * 0.205 *i, 0, g_height * 0.2, g_height * 0.2);
		else
			glViewport(g_height * 0.305 *i, 0, g_height * 0.3, g_height * 0.3);
		glBindTexture(GL_TEXTURE_2D_ARRAY_EXT, depth_tex_ar);
		glTexParameteri(GL_TEXTURE_2D_ARRAY_EXT, GL_TEXTURE_COMPARE_MODE, GL_NONE);
		glUniform1f(loc, (float)i);
		glBegin(GL_QUADS);
		glVertex3f(-1.0f, -1.0f, 0.0f);
		glVertex3f(1.0f, -1.0f, 0.0f);
		glVertex3f(1.0f, 1.0f, 0.0f);
		glVertex3f(-1.0f, 1.0f, 0.0f);
		glEnd();

	}
	glUseProgram(0);
	glPopAttrib();
}
