// ===============================================================================
//						     PHYSX SDK TRAINING PROGRAMS
//							   SHAPE DRAWING ROUTINES
//
//						   Written by Bob Schade, 12-15-05
// ===============================================================================

#ifndef DRAW3DSSHAPES_H
#define DRAW3DSSHAPES_H

class NxShape;
class Model_3DS;

void Draw3DSMesh(NxShape* shape, Model_3DS* model);
void Draw3DSMeshActor(NxActor *actor);


#endif  // DRAW3DSSHAPES_H
