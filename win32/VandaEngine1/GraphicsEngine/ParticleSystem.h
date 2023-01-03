//Copyright (C) 2023 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#pragma once

#include "pAPI.h"
#include "Opengl.h"
#include "image.h"
#include "texture.h"
#include "OpenGLUtility.h"
using namespace PAPI;
class CParticleSystem
{
public:
	CParticleSystem(CUInt numParticles, CChar* textureName );
	~CParticleSystem();
	CVoid Render();
private:
	CVoid GenerateGroup( CUInt numParticles);
	CVoid DeleteGroup();
	CVoid GenerateTexture( CChar* textureName );
	CVoid DeleteTexture();

	ParticleContext_t m_p;
	CInt m_particleHandle;
	CImage* m_textureImg;
	CBool m_init;
	CChar m_strImg[MAX_NAME_SIZE];
	COpenGLUtility m_glUtil;
	void DrawGroupAsQuadSprites( CBool constColor = CFalse, CBool constSize = CFalse);
	void WaterEffect();
};
