//Copyright (C) 2022 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#include "stdafx.h"
#include "3DSound.h"
#include "../VandaEngine1Win32.h"
//CVoid C3DSound::RenderIcon( CBool selectionMode )
//{
//	if( selectionMode )
//		glPushName( m_nameIndex );
//	g_glUtil.Billboarding( m_f3DSoundPos[0], m_f3DSoundPos[1], m_f3DSoundPos[2], g_soundImg->GetId(), 0.5f, 0.5f );
//	if( selectionMode )
//		glPopName();
//}
C3DSound::~C3DSound()
{
	if (m_buffer)
	{
		alSourceStop(m_source->GetSource());
		alSourcei(m_source->GetSource(), AL_BUFFER, AL_NONE);

		CInt counter = 0;
		for (CUInt i = 0; i < g_engine3DSounds.size(); i++)
		{
			if (g_engine3DSounds[i] && g_engine3DSounds[i]->GetSoundBuffer())
			{
				if (ICmp(m_buffer->GetName(), g_engine3DSounds[i]->GetSoundBuffer()->GetName()))
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
