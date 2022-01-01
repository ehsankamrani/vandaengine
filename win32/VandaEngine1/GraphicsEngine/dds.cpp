//Copyright (C) 2022 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#include "stdafx.h"
#include "dds.h"

#include <ddraw.h>		// DirectX's DirectDraw Surfaces (needs up-to-date DirectX SDK)

#include "dxtctool.h"

bool CDDS::LoadFile(std::istream & File)
{
	// Verify the type of file.
	char FileCode[4];
	if (! File.read(FileCode, 4))
		return false;
	if (strncmp(FileCode, "DDS ", 4) != 0)
		return false;
   
	// Get the surface descriptor.
	DDSURFACEDESC2 DDrawSD;
	if (! File.read((char *) &DDrawSD, sizeof(DDrawSD)))
		return false;

	// Set the attributes.
	switch(DDrawSD.ddpfPixelFormat.dwFourCC)
	{
	case FOURCC_DXT1:
		m_format = GL_COMPRESSED_RGB_S3TC_DXT1_EXT;
		m_alphaChannel = CFalse;
		m_blockSize = 8;
		break;
	case FOURCC_DXT3:
		m_format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
		m_alphaChannel = CTrue;
		m_blockSize = 16;
		break;
	case FOURCC_DXT5:
		m_format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
		m_alphaChannel = CTrue;
		m_blockSize = 16;
		break;
	default:
		return false;
	}

	m_width = DDrawSD.dwWidth;
	m_height = DDrawSD.dwHeight;
	m_nbMipmaps = DDrawSD.dwMipMapCount;

	if (m_nbMipmaps == 0)
		m_nbMipmaps = 1;

	// Check that the given dimentions are 2^x, 2^y
	if (! OpenGLSize())
		return false;

	// How big is it going to be including all mipmaps?
	size_t BufSize = 0;
	size_t Width = m_width;
	size_t Height = m_height;

	for (size_t i = 0; (i < m_nbMipmaps) && ((Width != 0) || (Height != 0)); ++i) {

		BufSize += ((Width + 3) / 4) * ((Height + 3) / 4) * m_blockSize;

		if ((i == 0) && (BufSize != DDrawSD.dwLinearSize))
			return false;

		if ((Width /= 2) == 0) Width = 1;
		if ((Height /= 2) == 0) Height = 1;
	}

	// Allocate pixels memory.
	m_pixels.resize(BufSize);

	// Read pixels.
	if (! File.read((char *) &m_pixels[0], std::streamsize(BufSize)))
		return false;

	return true;	
}



bool CDDS::UploadTexture() const
{
	if (m_pixels.empty())
		return false;

	// Missing mipmaps won't be a problem anymore.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, GLint(m_nbMipmaps) - 1);

	// Upload each mipmaps
	size_t Offset = 0;
	size_t Width = m_width;
	size_t Height = m_height;

	for (size_t i = 0; (i < m_nbMipmaps) && ((Width != 0) || (Height != 0)); ++i) {

		size_t BufSize = ((Width + 3) / 4) * ((Height + 3) / 4) * m_blockSize;

		glCompressedTexImage2D(GL_TEXTURE_2D, GLint(i), m_format, GLsizei(Width), GLsizei(Height), 0, GLsizei(BufSize), &m_pixels[Offset]);

		Offset += BufSize;
		if ((Width /= 2) == 0) Width = 1;
		if ((Height /= 2) == 0) Height = 1;
	}
	
	return true;
}



bool CDDS::VerticalFlip()
{
	size_t Offset = 0;
	size_t Width = m_width;
	size_t Height = m_height;

	for (size_t i = 0; (i < m_nbMipmaps) && ((Width != 0) || (Height != 0)); ++i, Width /= 2, Height /= 2) {
		if (Width == 0) Width = 1;
		if (Height == 0) Height = 1;

		if (! dxtc_tool::VerticalFlip(Width, Height, m_format, &m_pixels[Offset]))
			return false;

		Offset += ((Width + 3) / 4) * ((Height + 3) / 4) * m_blockSize;
	}

	return true;
}



bool CDDS::OpenGLSize() const
{
	size_t Width = m_width;
	size_t Height = m_height;
	size_t TotalTrueBits = 0;

	if ((Width == 0) || (Height == 0))
		return false;

	for (; (Width % 2) == 0; Width /= 2);
	for (; (Height % 2) == 0; Height /= 2);

	if ((Width != 1) || (Height != 1))
		return false;
	else
		return true;
}