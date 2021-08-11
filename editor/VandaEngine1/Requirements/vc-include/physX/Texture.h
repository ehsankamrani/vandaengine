#ifndef _SG_TEXTURE_H__
#define _SG_TEXTURE_H__
/*----------------------------------------------------------------------------*\
|
|						    NVIDIA PhysX Technology
|
|							     www.nvidia.com
|
\*----------------------------------------------------------------------------*/

#include <string>

namespace SceneGraph
	{

class Texture
/*-------------------------------*\
| this is basically an image preprocessed
| to be suitable for rendering.
| wheather its bump, etc is spacified
| not here but in material.
\*-------------------------------*/
	{
	public:
	Texture();
	~Texture();

	void load(const char * fileName, bool filter = true);
	void activate();
	void create(bool filter = true);
	void destroy();
	inline unsigned int getDispListNum() {return DispListNum;}

	std::string name;
	unsigned int DispListNum;

	unsigned int width;
	unsigned int height;

	float originalAspect;
	};
	};
#endif //__TEXTURE_H__
//NVIDIACOPYRIGHTBEGIN
///////////////////////////////////////////////////////////////////////////
// Copyright © 2010 NVIDIA Corporation.
// All rights reserved. www.nvidia.com
///////////////////////////////////////////////////////////////////////////
//NVIDIACOPYRIGHTEND
	