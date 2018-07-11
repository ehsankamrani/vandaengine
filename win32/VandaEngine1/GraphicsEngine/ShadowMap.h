//Copyright (C) 2018 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#pragma once
#include "OpenGL.h"
#include <math.h>
#include <nvMath.h>
using namespace nv;
#define MAX_SPLITS 4
#define NUM_OBJECTS 4
struct frustum
{
	float neard;
	float fard;
	float fov;
	float ratio;
	vec3f point[8];
};
struct BoundingSphere
{
	vec3f center;
	float radius;
};

class CShadowMap
{
public:
	CShadowMap();
public:
	~CShadowMap();
public:
	CBool Init();
	CVoid Release();
	CVoid RegenerateDepthTex(GLuint depth_size);
	void UpdateFrustumPoints(frustum &f, vec3f &center, vec3f &view_dir);
	void UpdateSplitDist(frustum f[MAX_SPLITS], float nd, float fd);
	float ApplyCropMatrix(frustum &f);
	void MakeShadowMap( float cam_pos[3], float cam_view[3], float light_dir[4] );
	void ShowDepthTex();

	GLuint depth_fb, depth_rb;
	GLuint depth_tex_ar;
	frustum f[MAX_SPLITS];
	CInt depth_size;
	float split_weight;
	int cur_num_splits;
	float shad_cpm[MAX_SPLITS][16];
	BoundingSphere BSphere[NUM_OBJECTS];

};
