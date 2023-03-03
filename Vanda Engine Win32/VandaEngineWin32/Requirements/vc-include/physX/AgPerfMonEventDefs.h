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

// This file is used to define a list of AgPerfMon events.
//
// This file is included exclusively by AgPerfMonEventSrcAPI.h
// and by AgPerfMonEventSrcAPI.cpp, for the purpose of building
// an enumeration (enum xx) and an array of strings ()
// that contain the list of events.
//
// This file should only contain event definitions, using the
// DEFINE_EVENT macro.  E.g.:
//
//     DEFINE_EVENT(sample_name_1)
//     DEFINE_EVENT(sample_name_2)
//     DEFINE_EVENT(sample_name_3)


// Statistics from the fluid mesh packet cooker
DEFINE_EVENT(meshCuisineNumUniqCell)
DEFINE_EVENT(meshCuisineNumUniqTri)
DEFINE_EVENT(meshCuisineNumBigCells54)
DEFINE_EVENT(meshCuisinePacketSizeBytes)
DEFINE_EVENT(statsSubsetOnly)

DEFINE_EVENT(NgPrSyncGPUClock)
DEFINE_EVENT(NgPrGatherGPUEvents)

DEFINE_EVENT(NgPrDeformableUberBatcherHostWork)
DEFINE_EVENT(NgPrDeformableUberBatcherCudaWork)

DEFINE_EVENT(NgPrDeformablePackParticleData)
DEFINE_EVENT(NgPrDeformableUnpackParticleData)

DEFINE_EVENT(NgPrDeformablePressure)

DEFINE_EVENT(NgPrDeformableUpdate)

DEFINE_EVENT(NgPrDeformableSelfCollision)

DEFINE_EVENT(NgPrDeformableCollision)
DEFINE_EVENT(NgPrDeformableCollisionAllocBuffers)
DEFINE_EVENT(NgPrDeformableCollisionAdjustPrimitiveOffsets)
DEFINE_EVENT(NgPrDeformableCollisionComputeTriangleAABBs)	
DEFINE_EVENT(NgPrDeformableCollisionAggregateData)
DEFINE_EVENT(NgPrDeformableCollisionSendParticleData)
DEFINE_EVENT(NgPrDeformableCollisionSendShapeData)
DEFINE_EVENT(NgPrDeformableCollisionSendTriangleData)
DEFINE_EVENT(NgPrDeformableCollisionSendConvexPlaneData)
DEFINE_EVENT(NgPrDeformableCollisionSendBlockControls)
DEFINE_EVENT(NgPrDeformableCollisionInitialization)
DEFINE_EVENT(NgPrDeformableCollisionDetectionPlane)
DEFINE_EVENT(NgPrDeformableCollisionDetectionBox)
DEFINE_EVENT(NgPrDeformableCollisionDetectionCapsule)
DEFINE_EVENT(NgPrDeformableCollisionDetectionConvex)
DEFINE_EVENT(NgPrDeformableCollisionDetectionMesh)
DEFINE_EVENT(NgPrDeformableCollisionDetectionAll)
DEFINE_EVENT(NgPrDeformableCollisionResponse)

DEFINE_EVENT(NgPrDeformableSolver)
DEFINE_EVENT(NgPrDeformableCooker)
DEFINE_EVENT(NgPrDeformableSolverInit)
DEFINE_EVENT(NgPrDeformableSolverIteration)
DEFINE_EVENT(NgPrDeformableReceiveParticleData)
DEFINE_EVENT(NgPrDeformableDMAImpulses)
DEFINE_EVENT(NgPrDeformableDMANormals)

DEFINE_EVENT(NgPrFluidUberBatcherHostWork)
DEFINE_EVENT(NgPrFluidUberBatcherCudaWork)

DEFINE_EVENT(NgPrFluidSphSortParticles)
DEFINE_EVENT(NgPrFluidSphCalcHashEvent)
DEFINE_EVENT(NgPrFluidSphRadixSort)
DEFINE_EVENT(NgPrFluidSphRadixSortStep)
DEFINE_EVENT(NgPrFluidSphReorder)
DEFINE_EVENT(NgPrFluidSphMemset)
DEFINE_EVENT(NgPrFluidSphFindCellstart)
DEFINE_EVENT(NgPrFluidSphCalcDensity)
DEFINE_EVENT(NgPrFluidSphCalcForce)

DEFINE_EVENT(NgPrFluidCollision)
DEFINE_EVENT(NgPrFluidCollisionAllocArrays)
DEFINE_EVENT(NgPrFluidCollisionFinalMemcpy)
DEFINE_EVENT(NgPrFluidCollisionShapeConverter)
DEFINE_EVENT(NgPrFluidCollisionDynamicShapes)
DEFINE_EVENT(NgPrFluidCollisionDynamicResponse)
DEFINE_EVENT(NgPrFluidCollisionStaticShapes)
DEFINE_EVENT(NgPrFluidCollisionTriangleWorkUnits)
DEFINE_EVENT(NgPrFluidCollisionTriangles)
DEFINE_EVENT(NgPrFluidCollisionStaticResponse)
DEFINE_EVENT(NgPrFluidCollisionFinalize)
DEFINE_EVENT(NgPrFluidCollisionUpdateShapePtrsConvex)
DEFINE_EVENT(NgPrFluidCollisionCreateShapeWorkUnits)
DEFINE_EVENT(NgPrFluidCollisionConstructArrays)
DEFINE_EVENT(NgPrFluidCollisionMemcpyParticles)
DEFINE_EVENT(NgPrFluidCollisionReorderToPackets)
DEFINE_EVENT(NgPrFluidCollisionMemcpyConstraints)
DEFINE_EVENT(NgPrFluidCollisionConstraints)
DEFINE_EVENT(NgPrFluidCollisionAllocWorkUnitArrays)

DEFINE_EVENT(NgPrFluidUpdateParticles)
DEFINE_EVENT(NgPrFluidCreatePacketHash)
DEFINE_EVENT(NgPrFluidRemoveParticles)
DEFINE_EVENT(NgPrFluidReorderToPackets)
DEFINE_EVENT(NgPrFluidCreateReorderIndexTable)
DEFINE_EVENT(NgPrFluidPackParticleData)
DEFINE_EVENT(NgPrFluidUnpackParticleData)

DEFINE_EVENT(NgPrFluidPipelineDeleteBatch)
DEFINE_EVENT(NgPrFluidPipelineCreateBatch)
DEFINE_EVENT(NgPrFluidPipelineIdle)

DEFINE_EVENT(NgPrUnitTestFrame)

DEFINE_EVENT(FluidParticleDemoFrameStart)
DEFINE_EVENT(FluidParticleDemoFrameStop)
DEFINE_EVENT(FluidParticleDemoFrame)
DEFINE_EVENT(FluidParticleDemoRunPhysics)
DEFINE_EVENT(FluidParticleDemoDisplayText)
DEFINE_EVENT(FluidParticleDemoRenderScene)
DEFINE_EVENT(FluidParticleDemoRenderTerrain)
DEFINE_EVENT(FluidParticleDemoRenderFluid)
DEFINE_EVENT(FluidParticleDemoRenderShadows)

DEFINE_EVENT(NgPrCpuHeapSize)
DEFINE_EVENT(NgPrGpuHeapSize)
DEFINE_EVENT(NgPrCpuHeapAllocatedTotal)
DEFINE_EVENT(NgPrGpuHeapAllocatedTotal)
DEFINE_EVENT(NgPrCpuHeapMaxAllocated)
DEFINE_EVENT(NgPrGpuHeapMaxAllocated)
DEFINE_EVENT(NgPrCpuHeapInternalFragmentation)
DEFINE_EVENT(NgPrGpuHeapInternalFragmentation)
DEFINE_EVENT(NgPrCpuHeapMaxInternalFragmentation)
DEFINE_EVENT(NgPrGpuHeapMaxInternalFragmentation)
DEFINE_EVENT(NgPrCpuHeapNumEntries)
DEFINE_EVENT(NgPrGpuHeapNumEntries)

DEFINE_EVENT(NgPrGpuMeshCacheSize)
DEFINE_EVENT(NgPrGpuMeshCacheAllocatedTotal)
DEFINE_EVENT(NgPrGpuMeshCacheMaxAllocated)
DEFINE_EVENT(NgPrGpuMeshCacheInternalFragmentation)
DEFINE_EVENT(NgPrGpuMeshCacheMaxInternalFragmentation)
DEFINE_EVENT(NgPrGpuMeshCacheNumEntries)

DEFINE_EVENT(NgPrGpuHeapAllocatedUnassigned)
DEFINE_EVENT(NgPrGpuHeapAllocatedFluid)
DEFINE_EVENT(NgPrGpuHeapAllocatedDeformable)
DEFINE_EVENT(NgPrGpuHeapAllocatedGpuUtils)
DEFINE_EVENT(NgPrGpuHeapMaxAllocatedUnassigned)
DEFINE_EVENT(NgPrGpuHeapMaxAllocatedFluid)
DEFINE_EVENT(NgPrGpuHeapMaxAllocatedDeformable)
DEFINE_EVENT(NgPrGpuHeapMaxAllocatedGpuUtils)
DEFINE_EVENT(NgPrGpuMeshCacheAllocatedFluid)
DEFINE_EVENT(NgPrGpuMeshCacheMaxAllocatedFluid)

DEFINE_EVENT(NgPrCpuHeapAllocatedUnassigned)
DEFINE_EVENT(NgPrCpuHeapAllocatedFluid)
DEFINE_EVENT(NgPrCpuHeapAllocatedDeformable)
DEFINE_EVENT(NgPrCpuHeapAllocatedGpuUtils)
DEFINE_EVENT(NgPrCpuHeapMaxAllocatedUnassigned)
DEFINE_EVENT(NgPrCpuHeapMaxAllocatedFluid)
DEFINE_EVENT(NgPrCpuHeapMaxAllocatedDeformable)
DEFINE_EVENT(NgPrCpuHeapMaxAllocatedGpuUtils)

DEFINE_EVENT(NgPrRBsolveCompressedContact)
DEFINE_EVENT(NgPrRBconvertToSOA)
DEFINE_EVENT(NgPrRBdecideConstraintOrder)
DEFINE_EVENT(NgPrRBconvertToAOS)

DEFINE_EVENT(GetUpdatesFromPhysX)
DEFINE_EVENT(simAddActor)
DEFINE_EVENT(simDeleteActor)
DEFINE_EVENT(simAddShape)
DEFINE_EVENT(simDeleteShape)

DEFINE_EVENT(GetUpdatesFromApiThread)
DEFINE_EVENT(GrbCreateParticlesFromRigidBodies)
DEFINE_EVENT(ConvertActorsToSOA)
DEFINE_EVENT(FindSphereSphereContacts)
DEFINE_EVENT(FindSpherePlaneContacts)
DEFINE_EVENT(FindSphereMeshContacts)
DEFINE_EVENT(CountSphereMeshContacts)
DEFINE_EVENT(MakeSphereMeshContacts)
DEFINE_EVENT(IntegrateAtomAccelerations)
DEFINE_EVENT(GenerateConstraints)
DEFINE_EVENT(SortConstraints)
DEFINE_EVENT(SolveSOA)
DEFINE_EVENT(IntegrateAtomPoses)
DEFINE_EVENT(ConvertActorsToAOS)
DEFINE_EVENT(GrbSortParticles)
DEFINE_EVENT(GrbCountSphereSphereContacts)
DEFINE_EVENT(GrbFindContactStarts)
DEFINE_EVENT(GrbMakeSphereSphereContacts)
DEFINE_EVENT(SolveCompressedContact)
DEFINE_EVENT(PrbRadixSort)
DEFINE_EVENT(ConvertContactsToAOS)
DEFINE_EVENT(CalcForceFields)
DEFINE_EVENT(simulate)
DEFINE_EVENT(fetchResults)
DEFINE_EVENT(GoThroughConstraints)
DEFINE_EVENT(ReadTransform)
DEFINE_EVENT(WaitForResults)
DEFINE_EVENT(RrbActor_massFromParticles)
DEFINE_EVENT(PrbConvexShape_makeParticleRep)
DEFINE_EVENT(PrbFindSphereConvexContacts)
DEFINE_EVENT(PrbCalculateConvexAABBs)
DEFINE_EVENT(PrbCalculateBodyAABBs)
DEFINE_EVENT(PrbBroadphase)

DEFINE_EVENT(Sample_RunPhysics)
DEFINE_EVENT(Sample_RenderCallBack)
DEFINE_EVENT(Sample_RenderScene)
DEFINE_EVENT(Sample_RenderTerrain)
DEFINE_EVENT(Sample_GlutSwapBuffers)
