//Copyright (C) 2018 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#include "stdafx.h"
#include "NxDebugRenderer.h"

NX_INLINE CVoid setupColor(NxU32 color)
{
	NxF32 Blue	= NxF32((color)&0xff)/255.0f;
	NxF32 Green	= NxF32((color>>8)&0xff)/255.0f;
	NxF32 Red	= NxF32((color>>16)&0xff)/255.0f;
	glColor3f(Red, Green, Blue);
}

CVoid DebugRenderer::renderData(const NxDebugRenderable& data) const
{
	glUseProgram(0);
	glPushAttrib( GL_ENABLE_BIT | GL_CURRENT_BIT );
	glDisable(GL_LIGHTING);
	glDisable( GL_TEXTURE_2D );
	glEnable( GL_CULL_FACE );
	glLineWidth(1.0f);
	glMatrixMode(GL_MODELVIEW);

	// Render points	
	NxU32 NbPoints = data.getNbPoints();
	if(NbPoints)
	{
		const NxDebugPoint* Points = data.getPoints();

		glBegin(GL_POINTS);
		while(NbPoints--)
		{
			setupColor(Points->color);
			glVertex3fv(&Points->p.x);
			Points++;
		}
		glEnd();
	}

	// Render lines
	NxU32 NbLines = data.getNbLines();
	if(NbLines)
	{
		const NxDebugLine* Lines = data.getLines();

		glBegin(GL_LINES);
		while(NbLines--)
		{
			setupColor(Lines->color);
			glVertex3fv(&Lines->p0.x);
			glVertex3fv(&Lines->p1.x);
			Lines++;
		}
		glEnd();
	}

	// Render triangles
	NxU32 NbTris = data.getNbTriangles();
	if(NbTris)
	{
		const NxDebugTriangle* Triangles = data.getTriangles();

		glBegin(GL_TRIANGLES);
		while(NbTris--)
		{
			setupColor(Triangles->color);
			glVertex3fv(&Triangles->p0.x);
			glVertex3fv(&Triangles->p1.x);
			glVertex3fv(&Triangles->p2.x);
			Triangles++;
		}
		glEnd();
	}
	glPopAttrib();


}


