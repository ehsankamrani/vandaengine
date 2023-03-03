// ===============================================================================
//						  NVIDIA PHYSX SDK TRAINING PROGRAMS
//							       USER ALLOCATOR
//
//						    Written by Bob Schade, 5-1-06
// ===============================================================================

#ifndef USERALLOCATOR_H
#define USERALLOCATOR_H

#include <physX/NxUserAllocator.h>
class UserAllocator : public NxUserAllocator
{
public:
						UserAllocator();
	virtual				~UserAllocator();

			CVoid		reset();

			CVoid*		malloc(NxU32 size);
			CVoid*		malloc(NxU32 size, NxMemoryType type);
			CVoid*		mallocDEBUG(NxU32 size, const char* file, CInt line);
			CVoid*		mallocDEBUG(NxU32 size, const char* file, CInt line, const char* className, NxMemoryType type);
			CVoid*		realloc(CVoid* memory, NxU32 size);
			CVoid		free(CVoid* memory);

			NxU32*		mMemBlockList;
			NxU32		mMemBlockListSize;
			NxU32		mMemBlockFirstFree;
			NxU32		mMemBlockUsed;

			NxI32		mNbAllocatedBytes;
			NxI32		mHighWaterMark;
			NxI32		mTotalNbAllocs;
			NxI32		mNbAllocs;
			NxI32		mNbReallocs;
};

#endif  // USERALLOCATOR_H
