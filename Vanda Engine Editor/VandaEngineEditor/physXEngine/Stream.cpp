// ===============================================================================
//						  NVIDIA PHYSX SDK TRAINING PROGRAMS
//							         USER STREAM
//
//						    Written by Bob Schade, 5-1-06
// ===============================================================================

#include "stdafx.h"
#include <stdio.h>
#include <PhysX/NxPhysics.h>
#include "Stream.h"

UserStream::UserStream(const char* filename, CBool load) : fp(NULL)
{
	fp = fopen(filename, load ? "rb" : "wb");
}

UserStream::~UserStream()
{
	if(fp)	fclose(fp);
}

// Loading API
NxU8 UserStream::readByte() const
{
	NxU8 b;
	size_t r = fread(&b, sizeof(NxU8), 1, fp);
	NX_ASSERT(r);
	return b;
}

NxU16 UserStream::readWord() const
{
	NxU16 w;
	size_t r = fread(&w, sizeof(NxU16), 1, fp);
	NX_ASSERT(r);
	return w;
}

NxU32 UserStream::readDword() const
{
	NxU32 d;
	size_t r = fread(&d, sizeof(NxU32), 1, fp);
	NX_ASSERT(r);
	return d;
}

CFloat UserStream::readFloat() const
{
	NxReal f;
	size_t r = fread(&f, sizeof(NxReal), 1, fp);
	NX_ASSERT(r);
	return f;
}

CDouble UserStream::readDouble() const
{
	NxF64 f;
	size_t r = fread(&f, sizeof(NxF64), 1, fp);
	NX_ASSERT(r);
	return f;
}

CVoid UserStream::readBuffer(CVoid* buffer, NxU32 size)	const
{
	size_t w = fread(buffer, size, 1, fp);
	NX_ASSERT(w);
}

// Saving API
NxStream& UserStream::storeByte(NxU8 b)
{
	size_t w = fwrite(&b, sizeof(NxU8), 1, fp);
	NX_ASSERT(w);
	return *this;
}

NxStream& UserStream::storeWord(NxU16 w)
{
	size_t ww = fwrite(&w, sizeof(NxU16), 1, fp);
	NX_ASSERT(ww);
	return *this;
}

NxStream& UserStream::storeDword(NxU32 d)
{
	size_t w = fwrite(&d, sizeof(NxU32), 1, fp);
	NX_ASSERT(w);
	return *this;
}

NxStream& UserStream::storeFloat(NxReal f)
{
	size_t w = fwrite(&f, sizeof(NxReal), 1, fp);
	NX_ASSERT(w);
	return *this;
}

NxStream& UserStream::storeDouble(NxF64 f)
{
	size_t w = fwrite(&f, sizeof(NxF64), 1, fp);
	NX_ASSERT(w);
	return *this;
}

NxStream& UserStream::storeBuffer(const CVoid* buffer, NxU32 size)
{
	size_t w = fwrite(buffer, size, 1, fp);
	NX_ASSERT(w);
	return *this;
}



MemoryWriteBuffer::MemoryWriteBuffer() : currentSize(0), maxSize(0), data(NULL)
{
}

MemoryWriteBuffer::~MemoryWriteBuffer()
{
	NxGetPhysicsSDKAllocator()->free(data);
}

NxStream& MemoryWriteBuffer::storeByte(NxU8 b)
{
	storeBuffer(&b, sizeof(NxU8));
	return *this;
}

NxStream& MemoryWriteBuffer::storeWord(NxU16 w)
{
	storeBuffer(&w, sizeof(NxU16));
	return *this;
}

NxStream& MemoryWriteBuffer::storeDword(NxU32 d)
{
	storeBuffer(&d, sizeof(NxU32));
	return *this;
}

NxStream& MemoryWriteBuffer::storeFloat(NxReal f)
{
	storeBuffer(&f, sizeof(NxReal));
	return *this;
}

NxStream& MemoryWriteBuffer::storeDouble(NxF64 f)
{
	storeBuffer(&f, sizeof(NxF64));
	return *this;
}

NxStream& MemoryWriteBuffer::storeBuffer(const CVoid* buffer, NxU32 size)
{
	NxU32 expectedSize = currentSize + size;
	if(expectedSize > maxSize)
	{
		maxSize = expectedSize + 4096;

		NxU8* newData = (NxU8*)NxGetPhysicsSDKAllocator()->malloc(maxSize, NX_MEMORY_PERSISTENT);
		if(data)
		{
			memcpy(newData, data, currentSize);
			NxGetPhysicsSDKAllocator()->free(data);
		}
		data = newData;
	}
	memcpy(data+currentSize, buffer, size);
	currentSize += size;
	return *this;
}

MemoryReadBuffer::MemoryReadBuffer(const NxU8* data) : buffer(data)
{
}

MemoryReadBuffer::~MemoryReadBuffer()
{
	// We don't own the data => no delete
}

NxU8 MemoryReadBuffer::readByte() const
{
	NxU8 b;
	memcpy(&b, buffer, sizeof(NxU8));
	buffer += sizeof(NxU8);
	return b;
}

NxU16 MemoryReadBuffer::readWord() const
{
	NxU16 w;
	memcpy(&w, buffer, sizeof(NxU16));
	buffer += sizeof(NxU16);
	return w;
}

NxU32 MemoryReadBuffer::readDword() const
{
	NxU32 d;
	memcpy(&d, buffer, sizeof(NxU32));
	buffer += sizeof(NxU32);
	return d;
}

CFloat MemoryReadBuffer::readFloat() const
{
	CFloat f;
	memcpy(&f, buffer, sizeof(CFloat));
	buffer += sizeof(CFloat);
	return f;
}

CDouble MemoryReadBuffer::readDouble() const
{
	CDouble f;
	memcpy(&f, buffer, sizeof(CDouble));
	buffer += sizeof(CDouble);
	return f;
}

CVoid MemoryReadBuffer::readBuffer(CVoid* dest, NxU32 size) const
{
	memcpy(dest, buffer, size);
	buffer += size;
}
