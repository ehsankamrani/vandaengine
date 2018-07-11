//  Copyright (C) 2008 Steven Katic 

#include "StdAfx.h"
#include "MouseTranslationController.h"
#include "VandaEngine1Dlg.h"

void CMouseTranslationController::SetPlaneOrientation(DWORD theTranslationConstraint )
{
	if(theTranslationConstraint == XTRANS )
	{
		plane.axesAlignment = XYTRANS;
		plane.Normal.x = 0.0f;
		plane.Normal.y = 0.0f;
		plane.Normal.z = 1.0f;

	}
	else if(theTranslationConstraint == YTRANS)
	{
		plane.axesAlignment = XYTRANS;
		plane.Normal.x = 0.0f;
		plane.Normal.y = 0.0f;
		plane.Normal.z = 1.0f;
	}
	else if(theTranslationConstraint == ZTRANS)
	{
		plane.axesAlignment = ZXTRANS;
		plane.Normal.x = 0.0f;
		plane.Normal.y = 1.0f;
		plane.Normal.z = 0.0f;
	}
	else if(theTranslationConstraint == ZXTRANS )
	{
		plane.axesAlignment = ZXTRANS;
		plane.Normal.x = 0.0f;
		plane.Normal.y = 1.0f;
		plane.Normal.z = 0.0f;
	}
	else if(theTranslationConstraint == YZTRANS)
	{
		plane.axesAlignment = YZTRANS;
		plane.Normal.x = 1.0f;
		plane.Normal.y = 0.0f;
		plane.Normal.z = 0.0f;
	}		
	else//if(theTranslationConstraint == XYTRANS 
	{
		plane.axesAlignment = XYTRANS;
		plane.Normal.x = 0.0f;
		plane.Normal.y = 0.0f;
		plane.Normal.z = 1.0f;
	}		
	//plane.Normal.Normalize();
}

void CMouseTranslationController::Update(int x2D, int y2D)
{
	CVec3f intersection = CVec3f( 0.0f, 0.0f, 0.0f );
	ray.Generate3DRay(x2D, y2D);
	ray.Intersects(plane,intersection);
	ApplyTranslationConstraint(intersection);
	plane.Position = position;
	if( firstFrame )
		displacement = CVec3f( 0.0f, 0.0f, 0.0f );
	else
		displacement = position - lastposition;		
	lastposition = position;
	firstFrame = CFalse;
}

void CMouseTranslationController::Initialize(int x2D, int y2D,DWORD theTranslationConstraint, CVec3f planePos)
{
	if( !g_useOldRenderingStyle )
	{
		glPushAttrib( GL_VIEWPORT_BIT );
		glViewport( 0, 0, g_width, g_height );
	}

	CVec3f convertVector;
	convertVector.x = planePos.x; convertVector.y = planePos.z; convertVector.z = planePos.y;
	init = CTrue;
	firstFrame = CTrue;
	ray.Generate3DRay(x2D, y2D);
	position = convertVector;
	lastposition = position;
	displacement = CVec3f(0.0f,0.0f,0.0f);
	plane.Position = convertVector;
	InitializePlane(theTranslationConstraint);
	if( !g_useOldRenderingStyle )
	{
		glPopAttrib();
	}
}
