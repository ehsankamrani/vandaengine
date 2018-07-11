//Copyright (C) 2018 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#include "stdafx.h"
#include "lightModel.h"

GLvoid CLightModel::SetGlobalAmbient( GLfloat* ambient )
{
	glLightModelfv( GL_LIGHT_MODEL_AMBIENT, ambient );
}

GLvoid CLightModel::EnableLocalViewer()
{
	glLightModeli( GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE );
}

GLvoid CLightModel::DisableLocalViewer()
{
	glLightModeli( GL_LIGHT_MODEL_LOCAL_VIEWER, GL_FALSE );
}

GLvoid CLightModel::EnableTwoSide()
{
	glLightModeli( GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE );
}

GLvoid CLightModel::DisableTwoSide()
{
	glLightModeli( GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE );
}

GLvoid CLightModel::EnableSeparateSpecular()
{
	glLightModeli( GL_LIGHT_MODEL_COLOR_CONTROL, GL_SEPARATE_SPECULAR_COLOR );
}

GLvoid CLightModel::DisableSepatrateSpecular()
{
	glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL, GL_SINGLE_COLOR );
}

GLvoid CLightModel::Reset()
{
	GLfloat ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	glLightModelfv( GL_LIGHT_MODEL_AMBIENT, ambient );
	glLightModeli( GL_LIGHT_MODEL_LOCAL_VIEWER, GL_FALSE );
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE );
	glLightModeli( GL_LIGHT_MODEL_COLOR_CONTROL, GL_SINGLE_COLOR );
}