// ====================================================================================
//
//                                    NVIDIA PHYSX
//
// Content: Converter tool for cooked mesh files to substitute classic collision trees
//          with non-recursive, i.e., stackless collision trees
//
// Comment: Works for convex and non-convex mesh files
//
// Author:  Michael Sauter
//
// ====================================================================================

#ifndef MESH_CONVERTER_H
#define MESH_CONVERTER_H


#include <stdio.h>

#include "NxPhysics.h"
#include "NxCooking.h"

#include "CookedMeshReader.h"

#include "Stream.h"
#include "FileAndDirUtil.h"


int main(int argc, char** argv);

#endif  // MESH_CONVERTER_H
