/*----------------------------------------------------------------------
    This Software and Related Documentation are Proprietary to NVIDIA
    Corporation

    Copyright 2010 NVIDIA Corporation
    Unpublished -
    All Rights Reserved Under the Copyright Laws of the United States.

    Restricted Rights Legend:  Use, Duplication, or Disclosure by
    the Government is Subject to Restrictions as Set Forth in
    Paragraph (c)(1)(ii) of the Rights in Technical Data and
    Computer Software Clause at DFARS 252.227-7013.  NVIDIA
    Corporation
-----------------------------------------------------------------------*/

// This file is used to define a list of AgPerfMon GPU events.
//
// This file is included exclusively by AgPerfMonGPUEventSrcAPI.h
// and by AgPerfMonGPUEventSrcAPI.cpp, for the purpose of building
// an enumeration (enum xx) and an array of strings ()
// that contain the list of events.
//
// This file should only contain event definitions, using the
// GPU_DEFINE_EVENT macro.  E.g.:
//
//     DEFINE_EVENT(cudakernelEvent1)
//     DEFINE_EVENT(cudaDMAEvent1)

DEFINE_GPU_EVENT(cudaDMAEvent1)
DEFINE_GPU_EVENT(cudakernelEvent1)
DEFINE_GPU_EVENT(cudakernelMemsetEvent)

DEFINE_GPU_EVENT(cudakernelMoveToDevice)
DEFINE_GPU_EVENT(cudakernelMoveToHost)

DEFINE_GPU_EVENT(cudakernelFluidCalcDensity)
DEFINE_GPU_EVENT(cudakernelFluidCalcForce)
DEFINE_GPU_EVENT(cudakernelFluidCalcHash)
DEFINE_GPU_EVENT(cudakernelFluidRadixSort)
DEFINE_GPU_EVENT(cudakernelFluidReorder)
DEFINE_GPU_EVENT(cudakernelFluidMemset)
DEFINE_GPU_EVENT(cudakernelFluidFindCellstart)
DEFINE_GPU_EVENT(cudakernelFluidSimpleParticles)

DEFINE_GPU_EVENT(cudakernelFluidConvexShapes)
DEFINE_GPU_EVENT(cudakernelFluidBoxShapes)
DEFINE_GPU_EVENT(cudakernelFluidCapsuleShapes)
DEFINE_GPU_EVENT(cudakernelFluidCollisionTriangles)
DEFINE_GPU_EVENT(cudakernelFluidCollisionFinalize)
DEFINE_GPU_EVENT(cudakernelFluidDynamicResponse)
DEFINE_GPU_EVENT(cudakernelFluidStaticResponse)
DEFINE_GPU_EVENT(cudakernelFluidCollisionConstraints)

DEFINE_GPU_EVENT(cudainternalFluidCalcDensity)
DEFINE_GPU_EVENT(cudainternalFluidCalcForce)
DEFINE_GPU_EVENT(cudainternalFluidCalcHash)
DEFINE_GPU_EVENT(cudainternalFluidRadixSort)
DEFINE_GPU_EVENT(cudainternalFluidReorder)
DEFINE_GPU_EVENT(cudainternalFluidMemset)
DEFINE_GPU_EVENT(cudainternalFluidFindCellstart)
DEFINE_GPU_EVENT(cudainternalFluidSimpleParticles)

DEFINE_GPU_EVENT(cudainternalFluidConvexShapes)
DEFINE_GPU_EVENT(cudainternalFluidBoxShapes)
DEFINE_GPU_EVENT(cudainternalFluidCapsuleShapes)
DEFINE_GPU_EVENT(cudainternalFluidCollisionTriangles)
DEFINE_GPU_EVENT(cudainternalFluidCollisionFinalize)
DEFINE_GPU_EVENT(cudainternalFluidDynamicResponse)
DEFINE_GPU_EVENT(cudainternalFluidStaticResponse)
DEFINE_GPU_EVENT(cudainternalFluidCollisionConstraints)

DEFINE_GPU_EVENT(cudakernelPxgRadixSortStep)

DEFINE_GPU_EVENT(cudakernelDeformableUpdate)

DEFINE_GPU_EVENT(cudakernelDeformablePressureCalcNormalVolume)
DEFINE_GPU_EVENT(cudakernelDeformablePressureReduceVolumeNormMag)
DEFINE_GPU_EVENT(cudakernelDeformablePressureProjection)

DEFINE_GPU_EVENT(cudakernelDeformableSelfCollisionCreateHash)
DEFINE_GPU_EVENT(cudakernelDeformableSelfCollisionRadixSort)
DEFINE_GPU_EVENT(cudakernelDeformableSelfCollisionReorder)
DEFINE_GPU_EVENT(cudakernelDeformableSelfCollisionFindCellStart)
DEFINE_GPU_EVENT(cudakernelDeformableSelfCollisionCompareParticles)

DEFINE_GPU_EVENT(cudakernelDeformableCollisionInitialization)
DEFINE_GPU_EVENT(cudakernelDeformableCollisionDetectionPlane)
DEFINE_GPU_EVENT(cudakernelDeformableCollisionDetectionBox)
DEFINE_GPU_EVENT(cudakernelDeformableCollisionDetectionCapsule)
DEFINE_GPU_EVENT(cudakernelDeformableCollisionDetectionConvex)
DEFINE_GPU_EVENT(cudakernelDeformableCollisionDetectionMesh)
DEFINE_GPU_EVENT(cudakernelDeformableCollisionResponse)
DEFINE_GPU_EVENT(cudakernelDeformableUberCollision)

DEFINE_GPU_EVENT(cudakernelDeformableSolverConstToDevice)
DEFINE_GPU_EVENT(cudakernelDeformableInitSolver)
DEFINE_GPU_EVENT(cudakernelDeformablePacketSolver)
DEFINE_GPU_EVENT(cudakernelDeformableParticleSolver)
DEFINE_GPU_EVENT(cudakernelDeformablePack)
DEFINE_GPU_EVENT(cudakernelDeformableUberSolver)
DEFINE_GPU_EVENT(cudakernelDeformableSolverInterleave)
DEFINE_GPU_EVENT(cudakernelDeformableCalLinVelAngVel)
DEFINE_GPU_EVENT(cudakernelDeformableCalNormals)

DEFINE_GPU_EVENT(cudainternalDeformableUpdate)

DEFINE_GPU_EVENT(cudainternalDeformablePressureCalcNormalVolume)
DEFINE_GPU_EVENT(cudainternalDeformablePressureReduceVolumeNormMag)
DEFINE_GPU_EVENT(cudainternalDeformablePressureProjection)

DEFINE_GPU_EVENT(cudainternalDeformableSelfCollisionCreateHash)
DEFINE_GPU_EVENT(cudainternalDeformableSelfCollisionReorder)
DEFINE_GPU_EVENT(cudainternalDeformableSelfCollisionFindCellStart)
DEFINE_GPU_EVENT(cudainternalDeformableSelfCollisionCompareParticles)

DEFINE_GPU_EVENT(cudainternalDeformableCollisionInitialization)
DEFINE_GPU_EVENT(cudainternalDeformableCollisionDetection)
DEFINE_GPU_EVENT(cudainternalDeformableCollisionResponse)
DEFINE_GPU_EVENT(cudainternalDeformableUberCollision)

DEFINE_GPU_EVENT(cudainternalDeformableUberSolver)
DEFINE_GPU_EVENT(cudainternalDeformableInitSolver)
DEFINE_GPU_EVENT(cudainternalDeformablePack)
DEFINE_GPU_EVENT(cudainternalDeformableParticleSolver)
DEFINE_GPU_EVENT(cudainternalDeformablePacketSolver)

DEFINE_GPU_EVENT(cudakernelFluidCountNeighbors)
DEFINE_GPU_EVENT(cudakernelFluidPrefixSum)
DEFINE_GPU_EVENT(cudakernelFluidNeighborList)
DEFINE_GPU_EVENT(cudakernelFluidCalcDensity2)
DEFINE_GPU_EVENT(cudakernelFluidAggrDensity)
DEFINE_GPU_EVENT(cudakernelFluidCalcForce2)
DEFINE_GPU_EVENT(cudakernelFluidAggrForce)
DEFINE_GPU_EVENT(cudainternalFluidCountNeighbors)
DEFINE_GPU_EVENT(cudainternalFluidPrefixSum)
DEFINE_GPU_EVENT(cudainternalFluidNeighborList)
DEFINE_GPU_EVENT(cudainternalFluidCalcDensity2)
DEFINE_GPU_EVENT(cudainternalFluidAggrDensity)
DEFINE_GPU_EVENT(cudainternalFluidCalcForce2)
DEFINE_GPU_EVENT(cudainternalFluidAggrForce)

DEFINE_GPU_EVENT(cudakernelTransformParticles)
DEFINE_GPU_EVENT(cudakernelCountSphereSphereContacts)
DEFINE_GPU_EVENT(cudakernelMakeSphereSphereContacts)
DEFINE_GPU_EVENT(cudakernelCountSpherePlaneContacts)
DEFINE_GPU_EVENT(cudakernelMakeSpherePlaneContacts)
DEFINE_GPU_EVENT(cudakernelCountSphereMeshContacts)
DEFINE_GPU_EVENT(cudakernelMakeSphereMeshContacts)

DEFINE_GPU_EVENT(cudakernelScan)
DEFINE_GPU_EVENT(cudakernelintegrateAtomPoses)
DEFINE_GPU_EVENT(cudakernelintegrateAtomAccelerations)
DEFINE_GPU_EVENT(cudakernelGenerateConstraints)
DEFINE_GPU_EVENT(cudakernelSolve)
DEFINE_GPU_EVENT(cudakernelDecideConstraintOrder)
DEFINE_GPU_EVENT(cudakernelReorderConstraints)

DEFINE_GPU_EVENT(cudakernelMakeSphereConvexContacts)