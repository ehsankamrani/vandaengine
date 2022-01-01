//Copyright (C) 2022 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#include "stdafx.h"
#include "staticSound.h"
#include "../VandaEngine1Dlg.h"
#include "../graphicsEngine/scene.h"
CVoid CStaticSound::RenderIcon(CBool selectionMode)
{
	if (selectionMode)
	{
		glPushName(m_nameIndex);
	}
	if (!selectionMode)
	{
		if (m_nameIndex == g_selectedName || m_nameIndex == g_lastEngineObjectSelectedName)
		{
			g_tempLastEngineObjectSelectedName = m_nameIndex;
			if (g_transformObject)
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
			g_glUtil.Billboarding(m_fStaticSoundPos[0], m_fStaticSoundPos[1], m_fStaticSoundPos[2], g_soundImg->GetId(), 1.0f, 1.0f, 1.0, 0.0, 0.0);

			m_source->SetSoundPosition(m_fStaticSoundPos);
			g_showArrow = CTrue;
		}
		else
			g_glUtil.Billboarding(m_fStaticSoundPos[0], m_fStaticSoundPos[1], m_fStaticSoundPos[2], g_soundImg->GetId(), 1.0f, 1.0f);
	}
	else
		g_glUtil.Billboarding(m_fStaticSoundPos[0], m_fStaticSoundPos[1], m_fStaticSoundPos[2], g_soundImg->GetId(), 1.0f, 1.0f);
	if (selectionMode)
		glPopName();
}

CStaticSound::~CStaticSound()
{
	alSourceStop(m_source->GetSource());
	alSourcei(m_source->GetSource(), AL_BUFFER, AL_NONE);

	if (m_buffer)
	{
		CInt counter = 0;
		for (CUInt i = 0; i < g_engineStaticSounds.size(); i++)
		{
			if (g_engineStaticSounds[i] && g_engineStaticSounds[i]->GetSoundBuffer())
			{
				if (ICmp(m_buffer->GetName(), g_engineStaticSounds[i]->GetSoundBuffer()->GetName()))
				{
					counter++;
				}
			}
		}
		if (counter <= 1)
		{
			CInt index;
			for (CUInt i = 0; i < g_soundBuffers.size(); i++)
			{
				if (g_soundBuffers[i])
				{
					if (ICmp(m_buffer->GetName(), g_soundBuffers[i]->GetName()))
					{
						index = i;
						break;
					}
				}
			}

			CDelete(m_buffer);
			g_soundBuffers.erase(g_soundBuffers.begin() + index);
		}
	}
	CDelete(m_source);
	m_VSceneList.clear();
}
