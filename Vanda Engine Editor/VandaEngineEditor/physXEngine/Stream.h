// ===============================================================================
//						  NVIDIA PHYSX SDK TRAINING PROGRAMS
//							         USER STREAM
//
//						    Written by Bob Schade, 5-1-06
// ===============================================================================

#ifndef STREAM_H
#define STREAM_H

#include <PhysX/NxStream.h>
#include <stdio.h>

class UserStream : public NxStream
{
public:
								UserStream(const char* filename, CBool load);
	virtual						~UserStream();

	virtual		NxU8			readByte()								const;
	virtual		NxU16			readWord()								const;
	virtual		NxU32			readDword()								const;
	virtual		CFloat			readFloat()								const;
	virtual		CDouble			readDouble()							const;
	virtual		CVoid			readBuffer(CVoid* buffer, NxU32 size)	const;

	virtual		NxStream&		storeByte(NxU8 b);
	virtual		NxStream&		storeWord(NxU16 w);
	virtual		NxStream&		storeDword(NxU32 d);
	virtual		NxStream&		storeFloat(NxReal f);
	virtual		NxStream&		storeDouble(NxF64 f);
	virtual		NxStream&		storeBuffer(const CVoid* buffer, NxU32 size);

				FILE*			fp;
};

class MemoryWriteBuffer : public NxStream
{
	public:
								MemoryWriteBuffer();
	virtual						~MemoryWriteBuffer();

	virtual		NxU8			readByte()								const	{ NX_ASSERT(0);	return 0;	}
	virtual		NxU16			readWord()								const	{ NX_ASSERT(0);	return 0;	}
	virtual		NxU32			readDword()								const	{ NX_ASSERT(0);	return 0;	}
	virtual		CFloat			readFloat()								const	{ NX_ASSERT(0);	return 0.0f;}
	virtual		CDouble			readDouble()							const	{ NX_ASSERT(0);	return 0.0;	}
	virtual		CVoid			readBuffer(CVoid* /*buffer*/, NxU32 /*size*/)	const	{ NX_ASSERT(0);				}

	virtual		NxStream&		storeByte(NxU8 b);
	virtual		NxStream&		storeWord(NxU16 w);
	virtual		NxStream&		storeDword(NxU32 d);
	virtual		NxStream&		storeFloat(NxReal f);
	virtual		NxStream&		storeDouble(NxF64 f);
	virtual		NxStream&		storeBuffer(const CVoid* buffer, NxU32 size);

				NxU32			currentSize;
				NxU32			maxSize;
				NxU8*			data;
};

class MemoryReadBuffer : public NxStream
{
	public:
								MemoryReadBuffer(const NxU8* data);
	virtual						~MemoryReadBuffer();

	virtual		NxU8			readByte()								const;
	virtual		NxU16			readWord()								const;
	virtual		NxU32			readDword()								const;
	virtual		CFloat			readFloat()								const;
	virtual		CDouble			readDouble()							const;
	virtual		CVoid			readBuffer(CVoid* buffer, NxU32 size)	const;

	virtual		NxStream&		storeByte(NxU8 /*b*/)							{ NX_ASSERT(0);	return *this;	}
	virtual		NxStream&		storeWord(NxU16 /*w*/)							{ NX_ASSERT(0);	return *this;	}
	virtual		NxStream&		storeDword(NxU32 /*d*/)							{ NX_ASSERT(0);	return *this;	}
	virtual		NxStream&		storeFloat(NxReal /*f*/)						{ NX_ASSERT(0);	return *this;	}
	virtual		NxStream&		storeDouble(NxF64 /*f*/)						{ NX_ASSERT(0);	return *this;	}
	virtual		NxStream&		storeBuffer(const CVoid* /*buffer*/, NxU32 /*size*/)	{ NX_ASSERT(0);	return *this;	}

	mutable		const NxU8*		buffer;
};

#endif  // STREAM_H
