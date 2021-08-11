// ===============================================================================
//						  NVIDIA PHYSX SDK TRAINING PROGRAMS
//						    HEIGHTFIELD CREATION METHODS
//
//						    Written by Bob Schade, 5-1-06
// ===============================================================================

#ifndef HEIGHTFIELD_H
#define HEIGHTFIELD_H

NxActor* CreateHeightfield(const NxVec3& pos, int index, NxReal step);
void RenderHeightfield();

#endif  // HEIGHTFIELD_H
