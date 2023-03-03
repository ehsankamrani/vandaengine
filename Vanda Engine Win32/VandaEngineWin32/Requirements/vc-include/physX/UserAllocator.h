#ifndef USERALLOCATOR_H
#define USERALLOCATOR_H

#include "SampleMutex.h"

class UserAllocator : public NxUserAllocator
	{
	public:
							UserAllocator();
		virtual				~UserAllocator();

				void		reset();

				void*		malloc(size_t size);
				void*		malloc(size_t size, NxMemoryType type);
				void*		mallocDEBUG(size_t size, const char* file, int line);
				void*		mallocDEBUG(size_t size, const char* file, int line, const char* className, NxMemoryType type);
				void*		realloc(void* memory, size_t size);
				void		free(void* memory);

				size_t*		mMemBlockList;
				NxU32		mMemBlockListSize;
				NxU32		mMemBlockFirstFree;
				NxU32		mMemBlockUsed;

				NxI32		mNbAllocatedBytes;
				NxI32		mHighWaterMark;
				NxI32		mTotalNbAllocs;
				NxI32		mNbAllocs;
				NxI32		mNbReallocs;
				
				SampleMutex mAllocatorLock;

	};

#endif
