#ifndef ACTORPICKING_H
#define ACTORPICKING_H

#include "Actors.h"
#include "Joints.h"

#ifdef USE_NX_DOUBLE_BUFFERED
#include "NxdActor.h"
#endif

void LetGoActor();
bool PickActor(int x, int y);
void MoveActor(int x, int y);
void ViewProject(NxVec3 &v, int &xi, int &yi, float &depth);
void ViewUnProject(int xi, int yi, float depth, NxVec3 &v);

#endif //ACTORPICKING_H
