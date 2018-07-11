//Copyright (C) 2018 Ehsan Kamrani 
//This file is licensed and distributed under MIT license


#include "stdafx.h"
#include "texture.h"
#include "image.h"
#include "dds.h"
#include "..\common\utility.h"
#include "OpenGL.h"
//#include "targa.h" //advanced texture loader
//#include "imageLib.h"
#include <fstream>

CTexture::CTexture()
{
}

CTexture::~CTexture()
{
}

CInt32 CTexture::GetTextureType( CChar * name )
{
    if ( CmpIn( name, ".dds" ) || CmpIn( name, ".DDS" ) )
        return eTEXTURETYPE_TGA;
    if ( CmpIn( name, ".bmp" ) || CmpIn( name, ".bmp" ) )
        return eTEXTURETYPE_BMP; //it's no longer supported by my engine, bmp is not a good image format for game development
    return eTEXTURETYPE_UNKNOWN; //simply it means that the format is not targa!
}

CBool CTexture::SetTexture( CImage *texObj )
{
	if ((CInt) texObj->GetId() == -1 )
	{
		glDisable(GL_TEXTURE_2D);				
		return CFalse; 
	}
	else
	{
		// Enable Texture Mapping
		glEnable( GL_TEXTURE_2D );
		glBindTexture( GL_TEXTURE_2D, texObj->GetId() );
	}

	return CTrue; 
}

//CBool CTexture::LoadTargaTexture( CImage * texObj, CChar* name, CChar* sceneFileName ) 
//{
//	//attache the sceneFileName path( without the dea file ) to the texture name
//	CChar pathName[MAX_NAME_SIZE]; 
//
//	if( sceneFileName ) //To deal with Collada files.
//	{
//		CChar * texName = GetAfterPath( name ); //don't know if it's required? Maybe the name in collada file has no path
//		//strcpy( pathName , sceneFileName );
//		//CChar *removeExtra = GetAfterPath( pathName );
//		//removeExtra[0] = 0;
//		//strcat( pathName, texName );
//		CChar g_currentVSceneNameWithoutDot[MAX_NAME_SIZE];
//		Cpy( g_currentVSceneNameWithoutDot, g_currentVSceneName );
//		GetWithoutDot( g_currentVSceneNameWithoutDot );
//
//		sprintf( pathName, "%s%s%s%s", "assets/vscenes/", g_currentVSceneNameWithoutDot, "/Textures/", texName );
//	}
//	else //To load independent targa files(not specified in a collada file )
//		strcpy( pathName, name );
//
//	ILuint imageId;
//	ilGenImages(1, &imageId);
//	ilBindImage(imageId);
//
//	//PrintInfo( _T( "Reading Image : " ) );
//	//PrintInfo( _T( "'" ) + CString( pathName ) + _T("'\n"), COLOR_RED_BLUE );
//
//	// Read in the image file into DevIL.
//	if (!ilLoadImage(pathName)) {
//		// ERROR
//		ilDeleteImages(1, &imageId);
//	    MessageBox( NULL, _T("CTexture::LoadTargaTexture > Couldn't load the targa file\n"), _T( "VandaEngine Error"), MB_OK );
//		return false;
//	}
//	else {
//		texObj->SetWidth( ilGetInteger(IL_IMAGE_WIDTH) );
//		texObj->SetHeight( ilGetInteger(IL_IMAGE_HEIGHT) );
//
//		CUChar* imageData;
//		CInt imageSize;
//
//		imageSize = ilGetInteger(IL_IMAGE_WIDTH) * ilGetInteger(IL_IMAGE_HEIGHT) * ilGetInteger(IL_IMAGE_CHANNELS);
//		imageData = (CUChar*)malloc( imageSize );
//
//		if( ilGetInteger(IL_IMAGE_CHANNELS) == 3 )
//			texObj->SetFormat( TGA_TRUECOLOR_24 );
//		else if ( ilGetInteger(IL_IMAGE_CHANNELS) == 4 )
//			texObj->SetFormat( TGA_TRUECOLOR_32 );
//
//		memcpy( imageData , ilGetData() , imageSize );
//		texObj->SetImageData( imageData );
//		ilDeleteImages(1, &imageId);
//	}
//	CreateTargaTexture( texObj );
//
//	return CTrue;
//}
//
CBool CTexture::LoadDDSTexture( CImage * texObj, CChar* name, CChar* sceneFileName ) 
{
	//attache the sceneFileName path( without the dea file ) to the texture name
	CChar pathName[MAX_NAME_SIZE]; 

	if( sceneFileName ) //To deal with Collada files.
	{
		CChar * texName = GetAfterPath( name ); 
		//replace %20 with space using std::string
		std::string s(texName);
		size_t i = 0;
		for (;;) {
			i = s.find("%20", i);
			if (i == string::npos) {
				break;
			}
			s.replace(i, 3, " ");
		}
		strcpy(texName, s.c_str());

		sprintf( pathName, "%s%s", g_pathProperties.m_meshDiffuseTexturePath, texName );
	}
	else //To load independent dds files(not specified in a collada file )
		strcpy( pathName, name );
	ifstream file(pathName, ios::binary);

	if (! file)
	{
		CChar temp[MAX_NAME_SIZE];
		sprintf( temp, "%s%s%s", "CTexture::LoadDDSTexture > Couldn't open the DDS file '", pathName, "'" );
	    MessageBoxA( NULL, temp, "VandaEngine Error", MB_OK );
		return false;
	}

	CDDS *m_ddsImage = CNew( CDDS );

	if (! m_ddsImage->LoadFile(file))
	{
		CChar temp[MAX_NAME_SIZE];
		sprintf( temp, "%s%s%s", "CTexture::LoadDDSTexture > Couldn't load the DDS file '", pathName, "'" );
	    MessageBoxA( NULL, temp, "VandaEngine Error", MB_OK );
		return false;
	}
	texObj->SetWidth( (CInt32)m_ddsImage->GetWidth() );
	texObj->SetHeight( (CInt32)m_ddsImage->GetHeight() );
	if( m_ddsImage->m_alphaChannel)
		texObj->SetFormat(TGA_TRUECOLOR_32);
	else
		texObj->SetFormat(TGA_TRUECOLOR_24);
	CreateDDSTexture( texObj, m_ddsImage );
	return CTrue;
}


CBool CTexture::CreateTargaTexture( CImage * texObj )
{	
	CUInt32 tId = 0; 
	glGenTextures(1, &tId );

	// Create Nearest Filtered Texture
	glBindTexture( GL_TEXTURE_2D, tId );
	glPixelStorei( GL_UNPACK_ALIGNMENT, 4 );
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_MODULATE); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
	glTexParameteri( GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE ); 
	glHint(GL_GENERATE_MIPMAP_HINT, GL_NICEST );

	GLfloat m_anisotropy;

	if( g_options.m_anisotropy != 0 )
	{
		if(  GLEW_EXT_texture_filter_anisotropic )
		{
			switch( g_options.m_anisotropy )
			{
			case 2:
				m_anisotropy = 2.f;
				break;
			case 4:
				m_anisotropy = 4.f;
				break;
			case 8:
				m_anisotropy = 8.f;
				break;
			case 16:
				m_anisotropy = 16.f;
				break;
			}
			GLfloat m_maxAnisotropy;
			glGetFloatv( GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &m_maxAnisotropy );
			if( m_anisotropy > m_maxAnisotropy )
				m_anisotropy = m_maxAnisotropy;
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, m_anisotropy);
		}
	}


	//PrintInfo( _T( "Creating Texture...\n" ) ); 
	// get texImage 
	if	( texObj->GetFormat() == 3 )
	{
		//gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, texObj->GetWidth(), texObj->GetHeight(), 
		//	GL_BGR_EXT, GL_UNSIGNED_BYTE, texObj->GetImageData() );
		glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB,texObj->GetWidth(), texObj->GetHeight(), 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, texObj->GetImageData() ); 
	}
	else if ( texObj->GetFormat() == 4 )
	{
		//gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, texObj->GetWidth(), texObj->GetHeight(), 
		//	GL_BGRA_EXT, GL_UNSIGNED_BYTE, texObj->GetImageData() );
		glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA,texObj->GetWidth(), texObj->GetHeight(), 0, GL_BGRA_EXT, GL_UNSIGNED_BYTE, texObj->GetImageData() ); 
	}

	//PrintInfo( _T( "Texture Created Successfully\n"), COLOR_WHITE ); 
	texObj->SetId( tId ); 

	texObj->Destroy(); //we no longer need the data in client memory
	glBindTexture( GL_TEXTURE_2D, 0 );
	return CTrue; 
}

CBool CTexture::CreateDDSTexture( CImage * texObj, CDDS * ddsImg )
{	
	CUInt32 tId = 0; 
	glGenTextures(1, &tId );

	// Create Nearest Filtered Texture
	glBindTexture( GL_TEXTURE_2D, tId );
	glPixelStorei( GL_UNPACK_ALIGNMENT, 4 );
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_MODULATE); 
	glTexParameteri( GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE ); 
	glHint(GL_GENERATE_MIPMAP_HINT, GL_NICEST );

	//read the anisotropic data from the file
	GLfloat m_anisotropy;

	if( g_options.m_anisotropy != 0 )
	{
		if(  GLEW_EXT_texture_filter_anisotropic )
		{
			switch( g_options.m_anisotropy )
			{
			case 2:
				m_anisotropy = 2.f;
				break;
			case 4:
				m_anisotropy = 4.f;
				break;
			case 8:
				m_anisotropy = 8.f;
				break;
			case 16:
				m_anisotropy = 16.f;
				break;
			}
			GLfloat m_maxAnisotropy;
			glGetFloatv( GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &m_maxAnisotropy );
			if( m_anisotropy > m_maxAnisotropy )
				m_anisotropy = m_maxAnisotropy;
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, m_anisotropy);
		}
	}

	//PrintInfo( _T( "Creating Texture...\n" ) ); 

	if ((! ddsImg->VerticalFlip()) || (! ddsImg->UploadTexture()))
		return false;
	CDelete( ddsImg );

	//PrintInfo( _T( "Texture Created Successfully\n"), COLOR_WHITE ); 

	texObj->SetId( tId ); 
	glBindTexture( GL_TEXTURE_2D, 0 );

	return CTrue; 
}

CBool CTexture::DeleteTexture( CImage * texObj )
{
	CUInt32 tId = texObj->GetId();
	if ( tId != -1 )
	{
		glDeleteTextures( 1, &tId );
		texObj->SetId( -1 ); 
		return CTrue;
	}
	return CFalse;
}  