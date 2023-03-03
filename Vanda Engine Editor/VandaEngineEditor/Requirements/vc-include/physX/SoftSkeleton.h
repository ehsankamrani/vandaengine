#ifndef SOFT_SKELETON_H

#define SOFT_SKELETON_H

namespace NXU
{
class NxuSkeleton;
};

class NxActor;

namespace SOFTBODY
{

class SoftSkeleton;

// create a bone mapping skeleton between a list of actors and the bones in a graphics skeleton.
SoftSkeleton * createSoftSkeleton(unsigned int acount,NxActor **alist,NXU::NxuSkeleton *skeleton);
const float ** getTransforms(SoftSkeleton *sk); // synchronizes the actors with	graphics skeleton and rebuilds the graphics transforms.
void           releaseSoftSkeleton(SoftSkeleton *sk);
void           debugRender(SoftSkeleton *sk);

}; // end of namespace

#endif
