//Copyright (C) 2020 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#pragma once
//#include "cg.h"
#include "matrix.h"
#include "camera.h"
#include "opengl.h"
#include "effect.h"
#include "material.h"
#include "light.h"
#include "camera.h"
class CScene;
class CInstanceLight;
class CInstanceCamera;
class CRender
{
public:
	CVoid Init();
	CBool InitCg();
	CBool CheckForCgError();
	CBool CRender::DisableCgProfiles();
	CVoid DisableCg();
	CBool DestroyCg();
	CVoid Destroy();
	// Set the pointer to the active camera instance
	inline CVoid  SetActiveInstanceCamera(CInstanceCamera *inst){m_activeInstanceCamera = inst;}
	// Get a pointer to the active camera instance
	inline CInstanceCamera* GetActiveInstanceCamera(){return m_activeInstanceCamera;}
	inline CInstanceCamera* GetDefaultInstanceCamera() { return m_defaultInstanceCamera;}
	//Set the scene 
	CVoid SetScene(CScene * c) { m_scene = c;}
	CVoid SetSelectedScene( CScene * c ) { m_selectedScene = c; }

	//CGprofile m_cgVertexProfile, m_cgFragmentProfile;
	//CGcontext m_cgContext; 
	CBool m_cgInitialized;
	CScene *m_scene; 
	CScene *m_selectedScene;
	CMaterial * m_currentMaterial;
	CInstanceCamera *m_activeInstanceCamera;
	CInstanceCamera *m_defaultInstanceCamera;  // Pointer to the default camera instance in the scene
	CMatrix m_currentLocalToWorldMatrix;

	//GLSL variables
	GLuint m_shaderProgram;
	GLuint m_waterShaderProgram;
	GLuint m_shader_normalProgram;
	GLuint m_waterProgram;
	GLuint m_blurProgram;
	GLuint m_glowProgram;
	GLuint m_dofProgram[4];

	GLuint m_shad_single_hl_prog;
	GLuint m_shad_single_prog ;
	GLuint m_shad_multi_prog ;
	GLuint m_shad_multi_noleak_prog ;
    GLuint m_shad_pcf_prog;
    GLuint m_shad_pcf_trilin_prog;
    GLuint m_shad_pcf_4tap_prog;
    GLuint m_shad_pcf_8tap_prog;
    GLuint m_shad_pcf_gaussian_prog;

	GLuint m_terrain_shad_single_prog;
	GLuint m_terrain_shad_multi_prog;
	GLuint m_terrain_shad_multi_noleak_prog;
	GLuint m_terrain_shad_pcf_prog;
	GLuint m_terrain_shad_pcf_trilin_prog;
	GLuint m_terrain_shad_pcf_4tap_prog;
	GLuint m_terrain_shad_pcf_8tap_prog;
	GLuint m_terrain_shad_pcf_gaussian_prog;

	//+ normal map
	GLuint m_shad_single_hl_normal_prog;
	GLuint m_shad_single_normal_prog;
	GLuint m_shad_multi_normal_prog;
	GLuint m_shad_multi_noleak_normal_prog;
	GLuint m_shad_pcf_normal_prog;
	GLuint m_shad_pcf_trilin_normal_prog;
	GLuint m_shad_pcf_4tap_normal_prog;
	GLuint m_shad_pcf_8tap_normal_prog;
	GLuint m_shad_pcf_gaussian_normal_prog;

	GLuint m_shad_view_depth;

	GLuint m_blendTexturesProgram;
	GLuint m_fogBlurProgram;
	GLuint m_waterFogBlurProgram;
	GLuint m_terrainProgram;

	CBool m_useVBOs;  //deprecate; Moved to COptions::m_enableVBO
	CBool m_VBOsAvailable; 

	CBool m_useFBOs; //deprecate; Moved to COptions::m_enableFBO
	CBool m_FBOsAvailable;

	CBool m_shaderAvailable;
	CBool m_shadowShaderAvailable;
	CBool m_useShader;

	CBool m_useBloom;
	CBool m_useDynamicShadowMap;
	CBool m_useWaterReflection; //It specifies the reflection of objects on the water

	inline CVoid SetCurrentLMMat( CMatrix mat ) { CMatrixCopy( mat, m_currentLocalToWorldMatrix ); }
	inline CBool UsingVBOs(){ return m_VBOsAvailable; }
	inline CBool UsingFBOs(){ return m_FBOsAvailable; }
	inline CBool UsingShader(){ return m_shaderAvailable; }
	inline CBool UsingShadowShader(){ return m_shadowShaderAvailable; }
	inline CScene *GetScene(){ return m_scene; } 
	inline CScene *GetSelectedScene() { return m_selectedScene; }
	inline CVoid SetCurrentMaterial( CMaterial * mtrl ){ m_currentMaterial = mtrl; }
	inline CMaterial* GetCurrentMaterial(){ return m_currentMaterial; }
	inline CBool UsingCg(){ return m_cgInitialized; }
	
	CBool ParsePublishFile( CStringW strFileName );
	std::string m_savedFile;
	//GLSL
	GLuint LinkShaders(GLuint vertShader, GLuint fragShader);
	GLuint CompileShader(GLenum type, const GLchar *pszSource, GLint length);
	GLuint LoadShaderProgram(const char *pszFilename, std::string &infoLog);
	CVoid ReadTextFile(const char *pszFilename, std::string &buffer);

	CBool SetInstanceLight( CInstanceLight * lightInstance, CInt lightNumber, CBool markDefaultDirectionalLight = CTrue  );
	void DrawSphere( GLdouble radius, GLint slices, GLint stacks, CFloat* Pos, CFloat* color ); //I use this function to draw the light postion
	GLvoid DrawSolidSphere(GLdouble radius, GLint slices, GLint stacks, CFloat* pos, CFloat* diffuseColor);
	void DrawCube( GLdouble size, CFloat* pos );

	CBool BindForReading(CUInt fboId);
	CBool BindForWriting(CUInt fboId);

	CVoid SetMaterialFromCOLLADA( CMaterial * mat, CBool isSelected, CBool hasDiffuse );
	CVoid SetMaterialFromGameEngine(CFloat* ambient, CFloat* diffuse, CFloat* specular, CFloat* emission, CFloat shininess, CFloat transparency, CBool isSelected);

	CBool SetTexture( CImage * texObj, CBool hasDiffuse );

	CUInt GenerateVBO();
	CBool CopyVBOData(CUInt type, CUInt vboID, CVoid * data, CInt size );
	CBool CopyVBOSubData( CUInt type, CUInt vboId, CVoid * data, CUInt offset, CInt size );
	CBool BindVBO(CUInt type, CUInt vboUID );
	CVoid FreeVBO( CUInt vboUID ); 
	CBool SupportForVBOs();

	//frame buffer and render buffer functions
	CUInt GenerateFBO();
	CBool BindFBO( CUInt fboUID );
	CVoid FreeFBO( CUInt fboUID ); 
	CBool SupportForFBOs();
	CVoid Attach2DTextureToFBOColor( CUInt textureId, CInt colorBufferId = 0 );
	CVoid AttachRenderBufferToFBOColor( CUInt m_rbColorID, CInt colorBufferId = 0 );

	CUInt GenerateRenderBuffer();
	CBool BindRenderBuffer( CUInt renderBufferId );
	CVoid RenderbufferStorage( CUInt width, CUInt height );
	CVoid RenderbufferDepthStorageMultisample( CInt numSamples, CUInt width, CUInt height );
	CVoid RenderbufferColorStorageMultisample( CInt numSamples, CInt type, CUInt width, CUInt height );
	CVoid AttachDepthToFBO( CUInt renderBufferId );
	CVoid FreeRenderBuffer( CUInt rbId );

	CVoid LoadMatrix( CFloat * mat );
	CVoid MultMatrix( CFloat * mat );
	CVoid PushMatrix();
	CVoid PopMatrix();
	CVoid ProjectionMatrix();
	CVoid ModelViewMatrix();
	CVoid IdentityMatrix();
};

extern CRender g_render; 