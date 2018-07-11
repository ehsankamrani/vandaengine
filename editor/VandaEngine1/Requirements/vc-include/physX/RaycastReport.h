// ===============================================================================
//						     PHYSX SDK TRAINING PROGRAMS
//			                       RAYCAST REPORT
//
//						   Written by Bob Schade, 12-15-05
// ===============================================================================

#ifndef RAYCASTREPORT_H
#define RAYCASTREPORT_H

#include "UserData.h"

class RaycastPoint
{
public:
	RaycastPoint(const NxVec3& _p, const NxVec3& _color)
	{
		p = _p;
		color = _color;
	}

	NxVec3	p;
	NxVec3	color;
};

class RaycastLine
{
public:
	RaycastLine(const NxVec3& _p0, const NxVec3& _p1, const NxVec3& _color)
	{
		p0 = _p0;
		p1 = _p1;
		color = _color;
	}

	NxVec3	p0;
	NxVec3	p1;
	NxVec3	color;
};

class RaycastTriangle
{
public:
	RaycastTriangle(const NxVec3& _p0, const NxVec3& _p1, const NxVec3& _p2, const NxVec3& _color)
	{
		p0 = _p0;
		p1 = _p1;
		p2 = _p2;
		color = _color;
	}

	NxVec3	p0;
	NxVec3	p1;
	NxVec3	p2;
	NxVec3	color;
};

typedef NxArray<RaycastPoint> RaycastPointsArray;
typedef NxArray<RaycastLine> RaycastLinesArray;
typedef NxArray<RaycastTriangle> RaycastTrisArray;

// Raycast globals
RaycastPointsArray rpArray;
RaycastLinesArray rlArray;
RaycastTrisArray rtArray;

class RaycastReport : public NxUserRaycastReport
{
public:
	virtual bool onHit(const NxRaycastHit& hit)
	{
		ActorUserData* ud = (ActorUserData *)hit.shape->getActor().userData;
		ud->flags |= UD_HIT_BY_RAYCAST;	 // Mark as hit

		const NxVec3& worldImpact = hit.worldImpact;

		RaycastPoint rp(worldImpact, NxVec3(1,0,0));
		rpArray.pushBack(rp);

		// Light up the hit polygon on a convex mesh shape
		NxConvexShape* cmShape = hit.shape->isConvexMesh();
		if (cmShape) 
		{
			NxU32 verts[3];
			NxVec3 pos[3];
			NxConvexMesh& cm = cmShape->getConvexMesh();
			NxConvexMeshDesc cmDesc;

			ShapeUserData* sud = (ShapeUserData*)(cmShape->userData);

			if (sud && sud->mesh)
			{
				cmDesc = *(NxConvexMeshDesc*)(sud->mesh);

				const char* idx = (const char*)cmDesc.triangles;
				idx += hit.faceID*cmDesc.triangleStrideBytes;

			    verts[0] = ((NxU32*)idx)[0];
			    verts[1] = ((NxU32*)idx)[1];
			    verts[2] = ((NxU32*)idx)[2];				

				const char* vtx = (const char*)cmDesc.points;
		
				pos[0] = *(NxVec3*)(vtx + cmDesc.pointStrideBytes*verts[0]);
				pos[1] = *(NxVec3*)(vtx + cmDesc.pointStrideBytes*verts[1]);
				pos[2] = *(NxVec3*)(vtx + cmDesc.pointStrideBytes*verts[2]);
			}
			else
			{
			    cm.saveToDesc(cmDesc);

			    const NxU8* triPtr = (const NxU8*)cmDesc.triangles;
			    triPtr += hit.faceID*cmDesc.triangleStrideBytes;

			    verts[0] = ((NxU32*)triPtr)[0];
			    verts[1] = ((NxU32*)triPtr)[1];
			    verts[2] = ((NxU32*)triPtr)[2];

			    const NxVec3* vertPtr = (const NxVec3*)cmDesc.points;

			    pos[0] = ((NxVec3*)vertPtr)[verts[0]];
			    pos[1] = ((NxVec3*)vertPtr)[verts[1]];
			    pos[2] = ((NxVec3*)vertPtr)[verts[2]];
			}

			NxMat34 shapePose = hit.shape->getGlobalPose();

			RaycastTriangle rt(shapePose*pos[0], shapePose*pos[1], shapePose*pos[2], NxVec3(0,1,0));
			rtArray.pushBack(rt);
		}

		// Light up the hit polygon on a triangle mesh shape
		NxTriangleMeshShape* tmShape = hit.shape->isTriangleMesh();
		if (tmShape) 
		{
			NxU32 verts[3];
			NxVec3 pos[3];
			NxTriangleMesh& tm = tmShape->getTriangleMesh();
			NxTriangleMeshDesc tmDesc;

			ShapeUserData* sud = (ShapeUserData*)(tmShape->userData);

			if (sud && sud->mesh)
			{
				tmDesc = *(NxTriangleMeshDesc*)(sud->mesh);

				const char* idx = (const char*)tmDesc.triangles;
				idx += hit.faceID*tmDesc.triangleStrideBytes;

			    verts[0] = ((NxU32*)idx)[0];
			    verts[1] = ((NxU32*)idx)[1];
			    verts[2] = ((NxU32*)idx)[2];				

				const char* vtx = (const char*)tmDesc.points;
		
				pos[0] = *(NxVec3*)(vtx + tmDesc.pointStrideBytes*verts[0]);
				pos[1] = *(NxVec3*)(vtx + tmDesc.pointStrideBytes*verts[1]);
				pos[2] = *(NxVec3*)(vtx + tmDesc.pointStrideBytes*verts[2]);
			}
			else
			{
			    tm.saveToDesc(tmDesc);

			    const NxU8* triPtr = (const NxU8*)tmDesc.triangles;
			    triPtr += hit.faceID*tmDesc.triangleStrideBytes;

			    verts[0] = ((NxU32*)triPtr)[0];
			    verts[1] = ((NxU32*)triPtr)[1];
			    verts[2] = ((NxU32*)triPtr)[2];

			    const NxVec3* vertPtr = (const NxVec3*)tmDesc.points;

			    pos[0] = ((NxVec3*)vertPtr)[verts[0]];
			    pos[1] = ((NxVec3*)vertPtr)[verts[1]];
			    pos[2] = ((NxVec3*)vertPtr)[verts[2]];
			}

			NxMat34 shapePose = hit.shape->getGlobalPose();

			RaycastTriangle rt(shapePose*pos[0], shapePose*pos[1], shapePose*pos[2], NxVec3(0,1,0));
			rtArray.pushBack(rt);
		}

		return true;
	}

} gRaycastReport;

#endif  // RAYCASTREPORT_H

