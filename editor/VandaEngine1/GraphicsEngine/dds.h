//Copyright (C) 2018 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#pragma once

#include "opengl.h"

class CDDS
{
public:
	CDDS() : m_width(0), m_height(0), m_blockSize(0), m_nbMipmaps(0), m_format(0), m_alphaChannel(CFalse) { }
	~CDDS() { Clear(); }
	bool LoadFile(std::istream & File);
	bool UploadTexture() const;
	bool VerticalFlip();
	size_t GetWidth() {return m_width;}
	size_t GetHeight() {return m_height;}
	CVoid Clear() { m_pixels.clear(); }
	CBool m_alphaChannel;

private:
	bool OpenGLSize() const;

	size_t m_width;
	size_t m_height;
	size_t m_blockSize;
	size_t m_nbMipmaps;
	GLenum m_format;
	std::vector<__int8> m_pixels;
};