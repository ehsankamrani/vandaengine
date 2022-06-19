//Copyright (C) 2022 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#include "stdafx.h"
#include "staticSound.h"
#include "../VandaEngine1Win32.h"
//CVoid CStaticSound::RenderIcon( CBool selectionMode )
//{
//	if( selectionMode )
//		glPushName( m_nameIndex );
//	g_glUtil.Billboarding( m_fStaticSoundPos[0], m_fStaticSoundPos[1], m_fStaticSoundPos[2], g_soundImg->GetId(), 0.5f, 0.5f );
//	if( selectionMode )
//		glPopName();
//}
CStaticSound::~CStaticSound()
{
	if (m_buffer)
	{
		alSourceStop(m_source->GetSource());
		alSourcei(m_source->GetSource(), AL_BUFFER, AL_NONE);

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
}
