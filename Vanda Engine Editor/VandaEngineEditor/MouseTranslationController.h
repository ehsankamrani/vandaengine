//  Copyright (C) 2008 Steven Katic 

#pragma once
#include <windows.h>
#include "common/utility.h"


class CMouseTranslationController
{
public:
	CRay ray;
	CPlane plane;
	CVec3f position;				// the resulting translation position
	DWORD translationConstraint;	// The plane or axis that translation is constrained to

	CVec3f displacement;
	CVec3f lastposition;
	CBool init;
	CBool firstFrame;
	void CreatePlane()
	{
		CVec3f pt = CVec3f(0.0f,0.0f,0.0f);
		CVec3f normXY = CVec3f(0.0f,1.0f,0.0f);
		plane = CPlane(normXY,pt,ZXTRANS);		
	}

	void CreateRay(int x2D, int y2D)
	{
		ray.Generate3DRay(x2D, y2D);
	}	

	void SetPlaneOrientation(DWORD theTranslationConstraint );
	
	void InitializePlane(DWORD theTranslationConstaint)
	{
		// Check for the special case when the viewing plane is orthogonal to the virtual plane
		// and re-align the virtual plane to be in a parallel axis alignment to it. 
					
		GLdouble modelview[16];
		glGetDoublev(GL_MODELVIEW_MATRIX, modelview);

		DWORD newPlaneAlignment = theTranslationConstaint;
		DWORD newTranslationContraint = theTranslationConstaint;
		
		if((modelview[6] <  1.0f+EPSILON && modelview[6] >  1.0f-EPSILON)	// top view
		|| (modelview[6] < -1.0f+EPSILON && modelview[6] > -1.0f-EPSILON))	// bottom view
		{
			if(theTranslationConstaint == ZXTRANS || theTranslationConstaint == XTRANS)
			{
				newPlaneAlignment = XYTRANS;
				newTranslationContraint = XTRANS;
			}
			else if(theTranslationConstaint == YZTRANS || theTranslationConstaint == YTRANS)
			{
				newPlaneAlignment = XYTRANS;
				newTranslationContraint = YTRANS;
			}
		}
		else if((modelview[6] <  0.0f+EPSILON && modelview[6] >  0.0f-EPSILON))//No pitch front/back/right/left
		{
			if((modelview[8] <= 0.7071f && modelview[8] >= -0.7071f)) //front or back view
			{
				if(theTranslationConstaint == XYTRANS || theTranslationConstaint == XTRANS)
				{
					newPlaneAlignment = ZXTRANS;
					newTranslationContraint = XTRANS;
				}
				else if(theTranslationConstaint == YZTRANS || theTranslationConstaint == ZTRANS)
				{
					newPlaneAlignment = ZXTRANS;
					newTranslationContraint = ZTRANS;
				}
			}
			else if((modelview[8] <= -0.7071f || modelview[8] >= 0.7071f))// left view // right view
			{
				if(theTranslationConstaint == XYTRANS || theTranslationConstaint == YTRANS)
				{
					newPlaneAlignment = YZTRANS;
					newTranslationContraint = YTRANS;
				}
				else if(theTranslationConstaint == ZXTRANS || theTranslationConstaint == ZTRANS)
				{
					newPlaneAlignment = YZTRANS;
					newTranslationContraint = ZTRANS;
				}				
			}
			
		}

		SetPlaneOrientation(newPlaneAlignment);				
		translationConstraint = newTranslationContraint;

	}	
	
	void ApplyTranslationConstraint(CVec3f intersectPos)
	{
		if(translationConstraint == XTRANS )
		{
			position.x = intersectPos.x;
		}
		else if(translationConstraint == YTRANS )
		{
			position.y = intersectPos.y;
		}
		else if(translationConstraint == ZTRANS )
		{
			position.z = intersectPos.z;
		}
		else
		{
			position.x = intersectPos.x;
			position.z = intersectPos.z;
			position.y = intersectPos.y;
		}
	}

public:
	CBool Initialized() { return init; }
	CMouseTranslationController(void)
	{
		translationConstraint = XYTRANS;
		position = CVec3f(0.0f,0.0f,0.0f);		
		CreatePlane();	
		displacement = CVec3f(0.0f,0.0f,0.0f);
		lastposition = CVec3f(0.0f,0.0f,0.0f);
		init = CFalse;
	}

	CVoid Finish() { init = CFalse; }
	void Initialize(int x2D, int y2D,DWORD theTranslationConstraint, CVec3f planePos);

	void Update(int x2D, int y2D);
	CVec3f GetDisplacement()
	{
		CVec3f temp;
		//if( displacement.Size() > 0 )
		//{
		//	displacement.Normalize();
		//}
		temp.x = displacement.x;
		temp.y = displacement.z;
		temp.z = displacement.y;
		return temp;
	}

	void DrawPlane()
	{
		if(translationConstraint == XYTRANS || translationConstraint == ZXTRANS || translationConstraint == YZTRANS)
		{	
			plane.DrawNormal();
			plane.Draw();			
		}
	}	
};
