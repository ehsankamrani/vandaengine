// Simple class for rendering particles as point sprites with shaders

#ifndef PARTICLE_RENDERER_H
#define PARTICLE_RENDERER_H

#include <GL/glew.h>
#include "framebufferObject.h"
#include "GLSLProgram.h"

struct ParticleSDK;

class ParticleRenderer
{
public:
    ParticleRenderer();
    ~ParticleRenderer();

    enum DisplayMode
    {
        PARTICLE_POINTS,
        PARTICLE_SPHERES,
        PARTICLE_DENSITY,
        PARTICLE_SURFACE,
		PARTICLE_FOG,
        PARTICLE_SURFACE_CHROME,
        PARTICLE_SURFACE_NEW,
        PARTICLE_SURFACE_SOLID,		
    };

    enum BlendMode
    {
        BLEND_NONE,
        BLEND_ALPHA,
        BLEND_ADD,
    };

    void setMode(DisplayMode mode) { mDisplayMode = mode ; }

    void setNumParticles(unsigned int x) { mNumParticles = x; }
    void setPositionBuffer(float *buffer, unsigned int stride) { mPosBuffer = buffer; mPosStride = stride; }
    void setDensityBuffer(float *buffer, unsigned int stride) { mDensityBuffer = buffer; mDensityStride = stride; }
    void setVelocityBuffer(float *buffer, unsigned int stride) { mVelocityBuffer = buffer; mVelocityStride = stride; }

    void setParticleRadius(float x) { mParticleRadius = x; }
    void setParticleSurfaceScale(float x) { mParticleSurfaceScale = x; }    // amount to scale up particles for surface rendering
    void setWindowSize(int w, int h);
    void setFov(float fov) { mFov = fov; }
    void setColor(float r, float g, float b, float a=1.0);
    void setBlendMode(BlendMode mode) { mBlendMode = mode; }
    void setBlurPasses(int x) { mBlurPasses = x; }

    void setFluidColor(float r, float g, float b, float a=1.0) { setColor(mFluidColor, r, g, b, a); }
    void setFluidColorFalloff(float r, float g, float b, float a=1.0) { setColor(mFluidColorFalloff, r, g, b, a); }
    void setSprayColor(float r, float g, float b, float a=1.0) { setColor(mSprayColor, r, g, b, a); }
	void setFogColor(float r, float g, float b, float a=1.0) {setColor(mFogColor, r, g, b, a);}

    void setDensityThreshold(float x) { mDensityThreshold = x; }            // threshold below which particles are rendered as spray
    void setDensityScale(float x) { mDensityScale = x; }                    // scale for visualizing density
    void setDensityOffset(float x) { mDensityOffset = x; }

    void setLightDirection(float *v) { mLightDir[0] = v[0]; mLightDir[1] = v[1]; mLightDir[2] = v[2]; }

    void setCubemapTexture(GLuint tex) { mCubemapTex = tex; }

    void beginSceneRender();
    void endSceneRender();

    void render();

private:
    void setColor(GLfloat *c, float r, float g, float b, float a=1.0f);
    void drawPoints();
    void drawPointSprites(GLSLProgram *prog, float scale);
    void displaySurface(GLSLProgram *prog);
    void renderSurface();
    void renderSpray();

    GLuint createTexture(GLenum target, int w, int h, GLint internalformat, GLenum format);
    void createBuffers();

    void drawQuad(int texW, int texH);
    void blurDepth(bool vertical);
    void dilateDepth();

    DisplayMode         mDisplayMode;

    // particle data
    float*              mPosBuffer;
    unsigned int        mPosStride;
    float*              mDensityBuffer;
    unsigned int        mDensityStride;
    float*              mVelocityBuffer;
    unsigned int        mVelocityStride;

    // programs
    GLSLProgram         *mParticleSphereProg, *mParticleSurfaceProg, *mParticleThicknessProg, *mParticleFogProg;
    GLSLProgram         *mParticleDebugProg, *mParticleDensityProg, *mParticleSprayProg;
    GLSLProgram         *mBlurProg, *mDisplaySurfaceProg, *mDisplaySurfaceNewProg, *mDisplaySurfaceChromeProg, *mDisplaySurfaceSolidProg;
    GLSLProgram         *mTextureRectProg, *mDilateProg;

    unsigned int        mWindowW, mWindowH;
    float               mAspect, mInvFocalLen;
    float               mFov;

    unsigned int        mSubSample;
    unsigned int        mSubSampledW, mSubSampledH;

    unsigned int		mNumParticles;
    float               mParticleRadius;
    float               mParticleSurfaceScale;  // amount to scale up particle size for surface rendering

    float               mColor[4];
    float               mFluidColor[4];
    float               mFluidColorFalloff[4];
    float               mSprayColor[4];
	float				mFogColor[4];

    float               mLightDir[3];

    float               mDensityThreshold;
    float               mDensityScale;
    float               mDensityOffset;

    BlendMode           mBlendMode;
    unsigned int        mBlurPasses;
    bool                mRenderOffscreen;

    // fbo
    FramebufferObject * mFbo;
    GLuint              mColorTex[2], mDepthTex;
    GLuint              mColorTexLowRes[2];
    GLuint              mSceneTex, mSceneDepthTex;
    GLuint              mThicknessTex;
    unsigned int        mSrcTex;

    GLuint              mCubemapTex;
};

#endif