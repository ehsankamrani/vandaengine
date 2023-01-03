//Copyright (C) 2023 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#include "stdafx.h"
#include "particleSystem.h"

CParticleSystem::CParticleSystem(CUInt numParticles, CChar* textureName )
{
	m_textureImg = CNew( CImage );
	GenerateGroup( numParticles );
	GenerateTexture( textureName );
	m_init = CTrue;
}

CParticleSystem::~CParticleSystem()
{
	if( m_init )
	{
		DeleteTexture();
		DeleteGroup();
	}
}

CVoid CParticleSystem::GenerateGroup(CUInt numParticles)
{
	m_particleHandle = m_p.GenParticleGroups(1, numParticles);
}

CVoid CParticleSystem::DeleteGroup()
{
	m_p.DeleteParticleGroups( m_particleHandle );
}

CVoid CParticleSystem::GenerateTexture( CChar* fileName )
{
	Cpy( m_strImg, fileName );
	GetWithoutDot( m_strImg );
	CChar* name = GetAfterPath( m_strImg );
	CTexture::DeleteTexture( m_textureImg );

	CChar m_strTemp[MAX_NAME_SIZE];
	sprintf( m_strTemp, "%s%s", m_strImg, ".dds" );

	sprintf( m_strImg, "Assets/particle/%s", m_strTemp );

	if(!CTexture::LoadDDSTexture( m_textureImg, m_strImg, NULL ) )
		MessageBox( NULL, _T(" CParticleSystem::GenerateTexture>Couldn't load the texture"), _T("VandaEngine Error"), MB_OK );

	m_textureImg->SetFileName( m_strTemp );
}

CVoid CParticleSystem::DeleteTexture()
{
	CDelete(m_textureImg);
}

CVoid CParticleSystem::Render()
{
	glUseProgram(0);
    m_p.CurrentGroup(m_particleHandle);
	WaterEffect();
	DrawGroupAsQuadSprites(false, true);
}

void CParticleSystem::WaterEffect()
{
	m_p.TimeStep( g_elapsedTime * 10.0f );
    m_p.Velocity(PDSphere(pVec(0, 0, 0), 0.2));
    m_p.Color(PDBox(pVec(0, 0, 0), pVec(1.0, 0.5, 0.5)));
    m_p.Size(1.5);
    m_p.StartingAge(0);


    m_p.Source(100 / 100, PDSphere(pVec(0, 0, 0), 6));

    // Orbit about the origin.
    m_p.OrbitPoint(pVec(0, 0, 0), 0.05, 1.5);

    m_p.Move(true, false);

    // Keep orbits from being too eccentric.
    m_p.Sink(true, PDSphere(pVec(0.0, 0.0, 0.0), 1.0));
    m_p.Sink(false, PDSphere(pVec(0.0, 0.0, 0.0), 8.0));
}

// Draw each particle as a screen-aligned quad with texture.
void CParticleSystem::DrawGroupAsQuadSprites( CBool constColor, CBool constSize )
{
	glPushAttrib( GL_CURRENT_BIT );
    CInt cnt = (CInt)m_p.GetGroupCount();

    if(cnt < 1)
	{
		glPopAttrib();
        return;
	}

    pVec *ppos = new pVec[cnt];
    float *color = constColor ? NULL : CNewData(CFloat, cnt * 4 );
    pVec *size = constSize ? NULL : CNewData( pVec,cnt );
	float *age = CNewData( CFloat, cnt );
    m_p.GetParticles(0, cnt, (float *)ppos, color, NULL, (float *)size,(float *) age);

    for(int i = 0; i < cnt; i++)
    {
        pVec &p = ppos[i];
        if(!constColor)
            glColor4f(color[i*4], color[i*4 + 1], color[i*4 + 2], color[i*4 + 3]);
        if(!constSize)
			m_glUtil.Billboarding( p.x(), p.y(), p.z(), m_textureImg->GetId(), size[i].x(), size[i].y() ); 
		else
			m_glUtil.Billboarding(p.x(), p.y(), p.z(), m_textureImg->GetId(), 0.01f, 0.01f ); 
	}

    CDeleteData( ppos );
    CDeleteData( color );
    CDeleteData( size );
	CDeleteData( age );
	glPopAttrib();
}
