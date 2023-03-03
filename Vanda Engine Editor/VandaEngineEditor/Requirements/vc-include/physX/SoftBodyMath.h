#ifndef SOFT_BODY_MATH_H

#define SOFT_BODY_MATH_H

#include <NxQuat.h>
#include <NxVec3.h>


namespace SOFTBODY
{

bool  SBM_rayIntersectsTriangle(const float *point,const float *direction,const float *v0,const float *v1,const float *v2,float &t);
float SBM_computeBoundingSphere(unsigned int vcount,const float *points,float *center);
float SBM_computeSphereVolume(float r);
bool  SBM_rayIntersectsSphere(const float *point,const float *direction,const float *center,float radius,float &t);


}; // END OF SOFTBODY NAMESPACE

#endif
