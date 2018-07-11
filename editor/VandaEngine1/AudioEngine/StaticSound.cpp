//Copyright (C) 2018 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#include "stdafx.h"
#include "staticSound.h"
#include "../VandaEngine1Dlg.h"
#include "../graphicsEngine/scene.h"
CVoid CStaticSound::RenderIcon( CBool selectionMode )
{
	if( selectionMode )
	{
		glPushName( m_nameIndex );
	}
	if( !selectionMode )
	{
		if( m_nameIndex == g_selectedName || m_nameIndex == g_lastEngineObjectSelectedName )
		{
			g_tempLastEngineObjectSelectedName = m_nameIndex;
			if( g_transformObject )
			{
				m_fStaticSoundPos[0] = g_arrowPosition.x; 
				m_fStaticSoundPos[1] = g_arrowPosition.y; 
				m_fStaticSoundPos[2] = g_arrowPosition.z; 
			}
			else
			{
				g_arrowPosition.x = m_fStaticSoundPos[0]; 
				g_arrowPosition.y = m_fStaticSoundPos[1]; 
				g_arrowPosition.z = m_fStaticSoundPos[2]; 
			}
			g_glUtil.Billboarding( m_fStaticSoundPos[0], m_fStaticSoundPos[1], m_fStaticSoundPos[2], g_soundImg->GetId(), 0.5f, 0.5f, 1.0, 0.0, 0.0 );

			m_source->SetSoundPosition( m_fStaticSoundPos );	
			g_showArrow = CTrue;
		}
		else
			g_glUtil.Billboarding( m_fStaticSoundPos[0], m_fStaticSoundPos[1], m_fStaticSoundPos[2], g_soundImg->GetId(), 0.5f, 0.5f );
	}
	else
		g_glUtil.Billboarding( m_fStaticSoundPos[0], m_fStaticSoundPos[1], m_fStaticSoundPos[2], g_soundImg->GetId(), 0.5f, 0.5f );
	if( selectionMode )
		glPopName();
}
