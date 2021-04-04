//Copyright (C) 2021 Ehsan Kamrani 
//This file is licensed and distributed under MIT license
#ifndef __NX_DEBUG_RENDERER_H
#define __NX_DEBUG_RENDERER_H

#define NOMINMAX
#include <windows.h>
#include <physx/NxDebugRenderable.h>
#include "../GraphicsEngine/OpenGL.h"

class NxDebugRenderable;

class DebugRenderer
{
public:
	CVoid renderData(const NxDebugRenderable& data) const;
};

#endif