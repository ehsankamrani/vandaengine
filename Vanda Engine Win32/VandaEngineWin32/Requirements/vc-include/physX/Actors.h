
#ifndef ACTORS_H
#define ACTORS_H

#include "NxPhysics.h"

NxActor* CreateGroundPlane(NxReal d = 0);
NxActor* CreateGroundPlane2();
NxActor* CreateBox(const NxVec3& pos, const NxVec3& boxDim, const NxReal density);
NxActor* CreateBox2(const NxVec3& pos, const NxVec3& boxDim, const NxReal density);
NxActor* CreateBoxOriented(const NxVec3& pos, const NxQuat& orientation, const NxVec3& boxDim, const NxReal density);
NxActor* CreateSphere(const NxVec3& pos, const NxReal radius, const NxReal density);
NxActor* CreateCapsule(const NxVec3& pos, const NxReal height, const NxReal radius, const NxReal density);

NxActor* CreateHalfPyramid(const NxVec3& pos, const NxVec3& boxDim, const NxReal density);
NxActor* CreatePyramid(const NxVec3& pos, const NxVec3& boxDim, const NxReal density);
NxActor* CreateDownWedge(const NxVec3& pos, const NxVec3& boxDim, const NxReal density);

NxActor* CreateConvexObjectComputeHull(const NxVec3& pos, const NxVec3& boxDim, const NxReal density);
NxActor* CreateConvexObjectSupplyHull(const NxVec3& pos, const NxVec3& boxDim, const NxReal density);
NxActor* CreateConcaveObject(const NxVec3& pos, const NxVec3& boxDim, const NxReal density);

NxActor* CreateBunny(const NxVec3& pos, NxTriangleMesh* triangleMesh, const NxReal density);

NxActor** CreateStack(const NxVec3& pos, const NxVec3& stackDim, const NxVec3& boxDim, NxReal density);
NxActor** CreateTower(const NxVec3& pos, const int heightBoxes, const NxVec3& boxDim, NxReal density);

NxQuat AnglesToQuat(const NxVec3& angles);
NxActor* CreateBoxGear(const NxVec3& pos, const NxReal minRadius, const NxReal maxRadius, const NxReal height, const NxU32 numTeeth, const NxReal density);
NxActor* CreateWheel(const NxVec3& pos, const NxReal minRadius, const NxReal maxRadius, const NxReal height, const NxU32 numTeeth, const NxReal density);
NxActor* CreateFrame(const NxVec3& pos, const NxReal density);
NxActor* CreateStep(const NxVec3& pos, const NxVec3& boxDim, const NxReal density);

void SetActorGroup(NxActor *actor, NxCollisionGroup group);
void SetActorMaterial(NxActor *actor, NxMaterialIndex index);

NxActor* CreateChassis(const NxVec3& pos, const NxVec3& boxDim, const NxReal density);
NxActor* CreateTurret(const NxVec3& pos, const NxVec3& boxDim, const NxReal density);
NxActor* CreateCannon(const NxVec3& pos, const NxVec3& boxDim, const NxReal density);

NxActor* CreateBlade(const NxVec3& pos, const NxVec3& boxDim, const NxReal mass);
NxActor* CreateBall(const NxVec3& pos, const NxReal radius, const NxReal mass);

#endif  // ACTORS_H
