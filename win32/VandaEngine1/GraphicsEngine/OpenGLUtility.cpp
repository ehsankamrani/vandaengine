//Copyright (C) 2022 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#include "stdafx.h"
#include "OpenGLUtility.h"

CVoid COpenGLUtility::InitGLEW()
{
	GLenum err = glewInit();
	if( err != GLEW_OK )
		MessageBox( NULL, _T("Couldn't initialize GLEW. Disabling extensions...\n"), _T( "VandaEngine Error" ), MB_OK );
	//else
	//	PrintInfo( _T("GLEW initialized successfully\n"), COLOR_WHITE );
}

CVoid COpenGLUtility::GetGLInfo()
{
	//CString m_strVendor =(char*)glGetString(GL_VENDOR);
	//CString m_strRenderer =(char*)glGetString(GL_RENDERER);
	//CString m_strVersion =(char*)glGetString(GL_VERSION);
	//CString m_strShadingVersion =(char*)glGetString(GL_SHADING_LANGUAGE_VERSION);

	//PrintInfo( "Detecting OpenGL information...\n", COLOR_RED_BLUE );
	//PrintInfo( "OpenGL Vendor: " + m_strVendor + "\n", COLOR_BLUE );
	//PrintInfo( "OpenGL Renderer: " + m_strRenderer + "\n", COLOR_BLUE);
	//PrintInfo( "OpenGL Version: " + m_strVersion + "\n", COLOR_BLUE );
	//PrintInfo( "OpenGL Shading Language Version: " + m_strShadingVersion + "\n", COLOR_BLUE );
}



CInt COpenGLUtility::WriteTGAFile( CChar *fileName, CInt16 CInt width, CInt16 CInt height, CUChar* imageData )
{
	CUChar byteSkip;
	CInt16 CInt shortSkip;
	CUChar imageType;
	CInt colorMode;
	CUChar colorSwap;
	CInt imageIdx;
	CUChar bitDepth;
	long imageSize;
	FILE *filePtr;

	filePtr = fopen( fileName, "wb" );
	if(!filePtr )
	{
		fclose( filePtr );
		return 0;
	}
	imageType = 2;
	bitDepth = 24;
	colorMode = 3;

	byteSkip = 0;
	shortSkip = 0;

	fwrite( &byteSkip, sizeof( CUChar ), 1, filePtr );
	fwrite( &byteSkip, sizeof( CUChar ), 1, filePtr );
	fwrite( &imageType, sizeof( CUChar ), 1, filePtr );
	fwrite( &shortSkip, sizeof( CInt16 CInt ), 1, filePtr );
	fwrite( &shortSkip, sizeof( CInt16 CInt ), 1, filePtr );
	fwrite( &byteSkip, sizeof( CUChar ), 1, filePtr );
	fwrite( &shortSkip, sizeof( CInt16 CInt ), 1, filePtr );
	fwrite( &shortSkip, sizeof( CInt16 CInt ), 1, filePtr );
	fwrite( &width, sizeof( CInt16 CInt ), 1, filePtr );
	fwrite( &height, sizeof( CInt16 CInt ), 1, filePtr );
	fwrite( &bitDepth, sizeof( CUChar ), 1, filePtr );
	fwrite( &byteSkip, sizeof( CUChar ), 1, filePtr );

	imageSize = width * height * colorMode;

	for( imageIdx = 0; imageIdx < imageSize; imageIdx += colorMode )
	{
		colorSwap = imageData[ imageIdx ];
		imageData[ imageIdx ] = imageData[ imageIdx + 2 ];
		imageData[ imageIdx + 2 ] = colorSwap;
	}

	fwrite( imageData, sizeof( CUChar ), imageSize, filePtr );
    
	fclose( filePtr );

	return 1;
}

CVoid COpenGLUtility::SaveScreenShot( CChar* fileName, CInt16 CInt width, CInt16 CInt height )
{
	CUChar* pImageData = (CUChar*)malloc(width * height * 3);
	memset(pImageData, 0, width * height * 3);
	glPixelStorei(GL_PACK_ALIGNMENT, 1);
	glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, pImageData);
	WriteTGAFile(fileName, width, height, pImageData);
	free(pImageData);
}

GLvoid COpenGLUtility::DrawQuad( CFloat* p )
{    
	glBegin( GL_QUADS );
	   for( CInt loop = 0; loop < 4; loop++ )
	   {
		   glTexCoord2f( p[loop*5], p[loop*5+1] );
		   glVertex3f( p[loop*5+2], p[loop*5+3], p[loop*5+4] );
	   }
    glEnd();
}

GLvoid COpenGLUtility::DrawSimpleBox(CVec3f min, CVec3f max)
{
	// cube ///////////////////////////////////////////////////////////////////////
	//    v6----- v5
	//   /|      /|
	//  v1------v0|
	//  | |     | |
	//  | |v7---|-|v4
	//  |/      |/
	//  v2------v3

	// vertex coords array for glDrawArrays() =====================================
	// A cube has 6 sides and each side has 2 triangles, therefore, a cube consists
	// of 36 vertices (6 sides * 2 tris * 3 vertices = 36 vertices). And, each
	// vertex is 3 components (x,y,z) of floats, therefore, the size of vertex
	// array is 108 floats (36 * 3 = 108).
	GLfloat vertices[] = {
		max.x, max.y, max.z, min.x, max.y, max.z, min.x, min.y, max.z,      // v0-v1-v2 (front)
		min.x, min.y, max.z, max.x, min.y, max.z, max.x, max.y, max.z,      // v2-v3-v0

		max.x, max.y, max.z, max.x, min.y, max.z, max.x, min.y, min.z,      // v0-v3-v4 (right)
		max.x, min.y, min.z, max.x, max.y, min.z, max.x, max.y, max.z,      // v4-v5-v0

		max.x, max.y, max.z, max.x, max.y, min.z, min.x, max.y, min.z,      // v0-v5-v6 (top)
		min.x, max.y, min.z, min.x, max.y, max.z, max.x, max.y, max.z,      // v6-v1-v0

		min.x, max.y, max.z, min.x, max.y, min.z, min.x, min.y, min.z,      // v1-v6-v7 (left)
		min.x, min.y, min.z, min.x, min.y, max.z, min.x, max.y, max.z,      // v7-v2-v1

		min.x, min.y, min.z, max.x, min.y, min.z, max.x, min.y, max.z,      // v7-v4-v3 (bottom)
		max.x, min.y, max.z, min.x, min.y, max.z, min.x, min.y, min.z,      // v3-v2-v7

		max.x, min.y, min.z, min.x, min.y, min.z, min.x, max.y, min.z,      // v4-v7-v6 (back)
		min.x, max.y, min.z, max.x, max.y, min.z, max.x, min.y, min.z };    // v6-v5-v4

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vertices);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glDisableClientState(GL_VERTEX_ARRAY);  // disable vertex arrays
}

GLvoid COpenGLUtility::StencilPattern( CInt n, CFloat* pArray, COpenGLShape type, CInt bit )
{
    glDepthMask( GL_FALSE );

	// disable modification of all color components
    glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);

    // enable stencil testing
    glEnable(GL_STENCIL_TEST);
	// setup the stencil buffer for a function reference value
    glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);
    glStencilFunc(GL_ALWAYS, 1, 1);

	switch( type )
	{
	case eOPENGLSHAPE_POLYGON:
		{
			glBegin( GL_POLYGON );
			for( CInt loop = 0; loop < n; loop++ )
				glVertex3f( pArray[loop*3], pArray[loop*3+1], pArray[loop*3+2] );
			glEnd();
		}break;
	case eOPENGLSHAPE_QUAD:
		{
			glBegin( GL_QUADS );
			for( CInt loop = 0; loop < n; loop++ )
				glVertex3f( pArray[loop*3], pArray[loop*3+1], pArray[loop*3+2] );
			glEnd();
		}break;
	default:
		{
			glBegin( GL_POLYGON );
			for( CInt loop = 0; loop < n; loop++ )
				glVertex3f( pArray[loop*3], pArray[loop*3+1], pArray[loop*3+2] );
			glEnd();
		}break;
	}
    // enable modification of all color components
    glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);

	// enable depth testing
    glDepthMask( GL_TRUE );

    // make it so we can only render where the stencil buffer is equal to 1
    glStencilFunc( GL_EQUAL, bit, 1 ); // bit = 0 or 1
    glStencilOp( GL_KEEP, GL_KEEP, GL_KEEP );
}


GLvoid COpenGLUtility::Billboarding( CFloat p1, CFloat p2, CFloat p3, GLuint texID, CFloat sizex, CFloat sizey, CFloat r, CFloat g, CFloat b )
{
	glPushAttrib( GL_ENABLE_BIT | GL_CURRENT_BIT );
	glUseProgram(0);
	glEnable( GL_ALPHA_TEST );
	glAlphaFunc( GL_GREATER, 0 );

	glEnable( GL_BLEND );
	glDisable( GL_LIGHTING );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	CFloat mat[16];
	glGetFloatv( GL_MODELVIEW_MATRIX, mat );

	CVector right( mat[0], mat[4], mat[8] );
	CVector up( mat[1], mat[5], mat[9] );
	CVector p( p1, p2, p3 );

	glColor3f( r, g, b );
	glActiveTexture( GL_TEXTURE0 );
	glMatrixMode( GL_TEXTURE );
	glLoadIdentity();
	glEnable( GL_TEXTURE_2D );
	CVector temp;
	glBindTexture( GL_TEXTURE_2D, texID );
	glMatrixMode( GL_MODELVIEW );
	glBegin( GL_QUADS );
	glTexCoord2f( 0.0f, 0.0f );
	CVector tempRight = right * sizex;
	CVector tempUp = up * sizey;
	temp = p + ( tempRight + tempUp ) * -1.0;
	glVertex3f( temp.m_i, temp.m_j, temp.m_k );
	glTexCoord2f( 1.0f, 0.0f );
	temp = p + ( tempRight - tempUp );
	glVertex3f( temp.m_i, temp.m_j, temp.m_k );
	glTexCoord2f( 1.0f, 1.0f );
	temp = p + (tempRight + tempUp );
	glVertex3f( temp.m_i, temp.m_j, temp.m_k );
	glTexCoord2f( 0.0f, 1.0f );
	temp = p + ( tempUp - tempRight );
	glVertex3f( temp.m_i, temp.m_j, temp.m_k );
	glEnd();

	glPopAttrib();
}

GLvoid COpenGLUtility::BillboardingWithUserVectors( CFloat centerX, CFloat centerY, CFloat centerZ, 
		GLuint texID, CFloat sizeX, CFloat sizeY,  CVector& up,  CVector& right )
{
	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

	right.Magnitude();
	right.Normalize();
	up.Magnitude();
	up.Normalize();
	CVector rightVec( right.m_i, right.m_j, right.m_k );
	CVector upVec( up.m_i, up.m_j, up.m_k );
	CVector p( centerX, centerY, centerZ );

	glEnable( GL_TEXTURE_2D );
	CVector temp;
	glBindTexture( GL_TEXTURE_2D, texID );
	glBegin( GL_QUADS );
	glTexCoord2f( 0.0f, 0.0f );
	CVector tempRight = rightVec * sizeX;
	CVector tempUp = upVec * sizeY;
	temp = p + ( tempRight + tempUp ) * - 1.0;
	glVertex3f( temp.m_i, temp.m_j, temp.m_k );
	glTexCoord2f( 1.0f, 0.0f );
	temp = p + ( tempRight - tempUp );
	glVertex3f( temp.m_i, temp.m_j, temp.m_k );
	glTexCoord2f( 1.0f, 1.0f );
	temp = p + (tempRight + tempUp );
	glVertex3f( temp.m_i, temp.m_j, temp.m_k );
	glTexCoord2f( 0.0f, 1.0f );
	temp = p + ( tempUp - tempRight );
	glVertex3f( temp.m_i, temp.m_j, temp.m_k );
	glEnd();
	glDisable( GL_TEXTURE_2D );
	glDisable( GL_BLEND );
}

GLvoid COpenGLUtility::DrawSquare(CVec3f pos1, CVec3f pos2, CVec3f pos3, CVec3f pos4)
{
	glUseProgram(0);
	glPushAttrib(GL_ENABLE_BIT);
	glDisable(GL_LIGHTING);                               //No need to compute lighting in selection mode
	glDisable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);											// Draw A Quad
	glVertex3f(pos1.x, pos1.y, pos1.z);					// Top Right Of The Quad (Top)
	glVertex3f(pos2.x, pos2.y, pos2.z);					// Top Left Of The Quad (Top)
	glVertex3f(pos3.x, pos3.y, pos3.z);					// Bottom Left Of The Quad (Top)
	glVertex3f(pos4.x, pos4.y, pos4.z);
	glEnd();													// Done Drawing The Quad
	glPopAttrib();
}

GLvoid COpenGLUtility::DrawCWBoxWithQuads( CVector &min, CVector &max )
{
	glUseProgram(0);
	glPushAttrib( GL_ENABLE_BIT );
	glDisable( GL_LIGHTING );                               //No need to compute lighting in selection mode
	glDisable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);											// Draw A Quad
	glVertex3f( min.m_i, max.m_j, min.m_k );					// Top Right Of The Quad (Top)
	glVertex3f( min.m_i, max.m_j, max.m_k );					// Top Left Of The Quad (Top)
	glVertex3f( max.m_i, max.m_j, max.m_k );					// Bottom Left Of The Quad (Top)
	glVertex3f( max.m_i, max.m_j, min.m_k );					// Bottom Right Of The Quad (Top)

	glVertex3f( max.m_i, min.m_j, max.m_k );					// Top Right Of The Quad (Bottom)
	glVertex3f( min.m_i, min.m_j, max.m_k );					// Top Left Of The Quad (Bottom)
	glVertex3f( min.m_i, min.m_j, min.m_k );					// Bottom Left Of The Quad (Bottom)
	glVertex3f( max.m_i, min.m_j, min.m_k );					// Bottom Right Of The Quad (Bottom)

	glVertex3f( max.m_i, max.m_j, max.m_k );					// Top Right Of The Quad (Front)
	glVertex3f( min.m_i, max.m_j, max.m_k );					// Top Left Of The Quad (Front)
	glVertex3f( min.m_i, min.m_j, max.m_k );					// Bottom Left Of The Quad (Front)
	glVertex3f( max.m_i, min.m_j, max.m_k );					// Bottom Right Of The Quad (Front)

	glVertex3f( max.m_i, min.m_j, min.m_k );					// Top Right Of The Quad (Back)
	glVertex3f( min.m_i, min.m_j, min.m_k );					// Top Left Of The Quad (Back)
	glVertex3f( min.m_i, max.m_j, min.m_k );					// Bottom Left Of The Quad (Back)
	glVertex3f( max.m_i, max.m_j, min.m_k );					// Bottom Right Of The Quad (Back)

	glVertex3f( min.m_i, max.m_j, max.m_k );					// Top Right Of The Quad (Left)
	glVertex3f( min.m_i, max.m_j, min.m_k );					// Top Left Of The Quad (Left)
	glVertex3f( min.m_i, min.m_j, min.m_k );					// Bottom Left Of The Quad (Left)
	glVertex3f( min.m_i, min.m_j, max.m_k );					// Bottom Right Of The Quad (Left)

	glVertex3f( max.m_i, max.m_j, min.m_k );					// Top Right Of The Quad (Right)
	glVertex3f( max.m_i, max.m_j, max.m_k );					// Top Left Of The Quad (Right)
	glVertex3f( max.m_i, min.m_j, max.m_k );					// Bottom Left Of The Quad (Right)
	glVertex3f( max.m_i, min.m_j, min.m_k );					// Bottom Right Of The Quad (Right)

	glEnd();													// Done Drawing The Quad
	
	glPopAttrib();
}

GLvoid COpenGLUtility::DrawCWBoxWithLines( CVector &min, CVector &max, CVector color )
{
	glUseProgram(0);
	glPushAttrib( GL_CURRENT_BIT | GL_ENABLE_BIT | GL_LINE_BIT );
    glDisable( GL_BLEND );
	glDisable( GL_FOG );
	glDisable( GL_LIGHTING );
	glDisable( GL_TEXTURE_2D );
	glColor4f( color.m_i, color.m_j, color.m_k, 0.0f );
	glLineWidth( 1.0f );
	
	glBegin( GL_LINE_LOOP );
	glVertex3f( max.m_i, max.m_j, min.m_k );					// Top Right Of The Quad (Top)
	glVertex3f( min.m_i, max.m_j, min.m_k );					// Top Left Of The Quad (Top)
	glVertex3f( min.m_i, max.m_j, max.m_k );					// Bottom Left Of The Quad (Top)
	glVertex3f( max.m_i, max.m_j, max.m_k );					// Bottom Right Of The Quad (Top)
	glEnd();

	glBegin( GL_LINE_LOOP );
	glVertex3f( max.m_i, min.m_j, max.m_k );					// Top Right Of The Quad (Bottom)
	glVertex3f( min.m_i, min.m_j, max.m_k );					// Top Left Of The Quad (Bottom)
	glVertex3f( min.m_i, min.m_j, min.m_k );					// Bottom Left Of The Quad (Bottom)
	glVertex3f( max.m_i, min.m_j, min.m_k );					// Bottom Right Of The Quad (Bottom)
	glEnd();

	glBegin( GL_LINE_LOOP );
	glVertex3f( max.m_i, max.m_j, max.m_k );					// Top Right Of The Quad (Front)
	glVertex3f( min.m_i, max.m_j, max.m_k );					// Top Left Of The Quad (Front)
	glVertex3f( min.m_i, min.m_j, max.m_k );					// Bottom Left Of The Quad (Front)
	glVertex3f( max.m_i, min.m_j, max.m_k );					// Bottom Right Of The Quad (Front)
	glEnd();
	
	glBegin( GL_LINE_LOOP );
	glVertex3f( max.m_i, min.m_j, min.m_k );					// Top Right Of The Quad (Back)
	glVertex3f( min.m_i, min.m_j, min.m_k );					// Top Left Of The Quad (Back)
	glVertex3f( min.m_i, max.m_j, min.m_k );					// Bottom Left Of The Quad (Back)
	glVertex3f( max.m_i, max.m_j, min.m_k );					// Bottom Right Of The Quad (Back)
	glEnd();
	glPopAttrib();

}


GLvoid COpenGLUtility::DrawCCWBox( CVector &min, CVector &max, CBool boundingBox, CBool selectionMode )
{
	if( boundingBox )
	{
		glPushAttrib( GL_CURRENT_BIT | GL_ENABLE_BIT );
        glDisable( GL_BLEND );
		glDisable( GL_FOG );
		glDisable( GL_LIGHTING );
		glDisable( GL_TEXTURE_2D );
		glLineWidth( 2.0f );
		glColor3f( 1.0f, 1.0f, 1.0f );

		glBegin( GL_LINE_LOOP );
		glVertex3f( max.m_i, max.m_j, min.m_k );					// Top Right Of The Quad (Top)
		glVertex3f( max.m_i, max.m_j, max.m_k );					// Bottom Right Of The Quad (Top)
		glVertex3f( min.m_i, max.m_j, max.m_k );					// Bottom Left Of The Quad (Top)
		glVertex3f( min.m_i, max.m_j, min.m_k );					// Top Left Of The Quad (Top)
        glEnd();
		glBegin( GL_LINE_LOOP );
		glVertex3f( max.m_i, min.m_j, max.m_k );					// Top Right Of The Quad (Bottom)
		glVertex3f( max.m_i, min.m_j, min.m_k );					// Bottom Right Of The Quad (Bottom)
		glVertex3f( min.m_i, min.m_j, min.m_k );					// Bottom Left Of The Quad (Bottom)
		glVertex3f( min.m_i, min.m_j, max.m_k );					// Top Left Of The Quad (Bottom)
        glEnd();
		glBegin( GL_LINE_LOOP );
		glVertex3f( max.m_i, max.m_j, max.m_k );					// Top Right Of The Quad (Front)
		glVertex3f( max.m_i, min.m_j, max.m_k );					// Bottom Right Of The Quad (Front)
		glVertex3f( min.m_i, min.m_j, max.m_k );					// Bottom Left Of The Quad (Front)
		glVertex3f( min.m_i, max.m_j, max.m_k );					// Top Left Of The Quad (Front)
        glEnd();
		glBegin( GL_LINE_LOOP );
		glVertex3f( max.m_i, min.m_j, min.m_k );					// Top Right Of The Quad (Back)
		glVertex3f( max.m_i, max.m_j, min.m_k );					// Bottom Right Of The Quad (Back)
		glVertex3f( min.m_i, max.m_j, min.m_k );					// Bottom Left Of The Quad (Back)
		glVertex3f( min.m_i, min.m_j, min.m_k );					// Top Left Of The Quad (Back)
        glEnd();
		glBegin( GL_LINE_LOOP );
		glVertex3f( min.m_i, max.m_j, max.m_k );					// Top Right Of The Quad (Left)
		glVertex3f( min.m_i, min.m_j, max.m_k );					// Bottom Right Of The Quad (Left)
		glVertex3f( min.m_i, min.m_j, min.m_k );					// Bottom Left Of The Quad (Left)
		glVertex3f( min.m_i, max.m_j, min.m_k );					// Top Left Of The Quad (Left)
        glEnd();
		glBegin( GL_LINE_LOOP );
		glVertex3f( max.m_i, max.m_j, min.m_k );					// Top Right Of The Quad (Right)
		glVertex3f( max.m_i, min.m_j, min.m_k );					// Bottom Right Of The Quad (Right)
		glVertex3f( max.m_i, min.m_j, max.m_k );					// Bottom Left Of The Quad (Right)
		glVertex3f( max.m_i, max.m_j, max.m_k );					// Top Left Of The Quad (Right)
		glEnd();											// Done Drawing The Quad
		glPopAttrib();
	}
	else
	{
		if( selectionMode )
		{
			glPushAttrib( GL_CURRENT_BIT );
			glDisable( GL_LIGHTING );                               //No need to compute lighting in selection mode
		}
		glBegin(GL_QUADS);								// Draw A Quad

		glVertex3f( max.m_i, max.m_j, min.m_k );					// Top Right Of The Quad (Top)
		glVertex3f( max.m_i, max.m_j, max.m_k );					// Bottom Right Of The Quad (Top)
		glVertex3f( min.m_i, max.m_j, max.m_k );					// Bottom Left Of The Quad (Top)
		glVertex3f( min.m_i, max.m_j, min.m_k );					// Top Left Of The Quad (Top)

		glVertex3f( max.m_i, min.m_j, max.m_k );					// Top Right Of The Quad (Bottom)
		glVertex3f( max.m_i, min.m_j, min.m_k );					// Bottom Right Of The Quad (Bottom)
		glVertex3f( min.m_i, min.m_j, min.m_k );					// Bottom Left Of The Quad (Bottom)
		glVertex3f( min.m_i, min.m_j, max.m_k );					// Top Left Of The Quad (Bottom)

		glVertex3f( max.m_i, max.m_j, max.m_k );					// Top Right Of The Quad (Front)
		glVertex3f( max.m_i, min.m_j, max.m_k );					// Bottom Right Of The Quad (Front)
		glVertex3f( min.m_i, min.m_j, max.m_k );					// Bottom Left Of The Quad (Front)
		glVertex3f( min.m_i, max.m_j, max.m_k );					// Top Left Of The Quad (Front)

		glVertex3f( max.m_i, min.m_j, min.m_k );					// Top Right Of The Quad (Back)
		glVertex3f( max.m_i, max.m_j, min.m_k );					// Bottom Right Of The Quad (Back)
		glVertex3f( min.m_i, max.m_j, min.m_k );					// Bottom Left Of The Quad (Back)
		glVertex3f( min.m_i, min.m_j, min.m_k );					// Top Left Of The Quad (Back)

		glVertex3f( min.m_i, max.m_j, max.m_k );					// Top Right Of The Quad (Left)
		glVertex3f( min.m_i, min.m_j, max.m_k );					// Bottom Right Of The Quad (Left)
		glVertex3f( min.m_i, min.m_j, min.m_k );					// Bottom Left Of The Quad (Left)
		glVertex3f( min.m_i, max.m_j, min.m_k );					// Top Left Of The Quad (Left)

		glVertex3f( max.m_i, max.m_j, min.m_k );					// Top Right Of The Quad (Right)
		glVertex3f( max.m_i, min.m_j, min.m_k );					// Bottom Right Of The Quad (Right)
		glVertex3f( max.m_i, min.m_j, max.m_k );					// Bottom Left Of The Quad (Right)
		glVertex3f( max.m_i, max.m_j, max.m_k );					// Top Left Of The Quad (Right)
		glEnd();											// Done Drawing The Quad
		if( selectionMode )
			glPopAttrib();
	}
}
