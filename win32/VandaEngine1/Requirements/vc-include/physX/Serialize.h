/*----------------------------------------------------------------------------*\
|
|							NVIDIA PhysX Technology
|
|							     www.nvidia.com
|
\*----------------------------------------------------------------------------*/

#ifndef SERIALIZE
#define SERIALIZE

#include "NxPhysics.h"
#include "NxStream.h"

//Floating-point representation of an integer value.
#define FR(x)			((NxF32&)(x))


	void	saveChunk(NxI8 a, NxI8 b, NxI8 c, NxI8 d, NxStream& stream);
	void	readChunk(NxI8& a, NxI8& b, NxI8& c, NxI8& d, const NxStream& stream);

	NxU16	readWord(bool mismatch, const NxStream& stream);
	NxU32	readDword(bool mismatch, const NxStream& stream);
	NxF32	readFloat(bool mismatch, const NxStream& stream);

	void	writeWord(NxU16 value, bool mismatch, NxStream& stream);
	void	writeDword(NxU32 value, bool mismatch, NxStream& stream);
	void	writeFloat(NxF32 value, bool mismatch, NxStream& stream);

	bool	readFloatBuffer(NxF32* dest, NxU32 nbFloats, bool mismatch, const NxStream& stream);
	void	writeWordBuffer(const NxU16* src, NxU32 nb, bool mismatch, NxStream& stream);
	void	writeFloatBuffer(const NxF32* src, NxU32 nb, bool mismatch, NxStream& stream);

	bool	writeHeader(NxI8 a, NxI8 b, NxI8 c, NxI8 d, NxU32 version, bool mismatch, NxStream& stream);
	bool	readHeader(NxI8 hdr1, NxI8 hdr2, NxI8 hdr3, NxI8& a, NxI8& b, NxI8& c, NxI8& d, NxU32& version, bool& mismatch, const NxStream& stream);

	NX_INLINE char	littleEndian()	{ int i = 1; return *((char*)&i);	}

	NX_INLINE	NxU16 flip(const NxU16* v)
		{
		const NxU8* b = (const NxU8*)v;
		NxU16 f;
		NxU8* bf = (NxU8*)&f;
		bf[0] = b[1];
		bf[1] = b[0];
		return f;
		}

	NX_INLINE   NxU32 flip(const NxU32* v)
		{
		const NxU8* b = (const NxU8*)v;
		NxU32 f;
		NxU8* bf = (NxU8*)&f;
		bf[0] = b[3];
		bf[1] = b[2];
		bf[2] = b[1];
		bf[3] = b[0];
		return f;
		}


	NX_INLINE	NxF32 flip(const NxF32* v)
		{
		NxU32 d = flip((const NxU32*)v);
		return FR(d);
		}

	NX_INLINE	bool	readIntBuffer(NxU32* dest, NxU32 nbInts, bool mismatch, const NxStream& stream)
		{
		return readFloatBuffer((NxF32*)dest, nbInts, mismatch, stream);
		}

	NX_INLINE	void	writeIntBuffer(const NxU32* src, NxU32 nb, bool mismatch, NxStream& stream)
		{
		writeFloatBuffer((const NxF32*)src, nb, mismatch, stream);
		}

	NxU32 computeMaxIndex(const NxU32* indices, NxU32 nbIndices);
	void storeIndices(NxU32 maxIndex, NxU32 nbIndices, const NxU32* indices, NxStream& stream, bool platformMismatch);
	void readIndices(NxU32 maxIndex, NxU32 nbIndices, NxU32* indices, const NxStream& stream, bool platformMismatch);
	void readIndices(NxU32 maxIndex, NxU32 nbIndices, NxU16* indices, const NxStream& stream, bool platformMismatch);

#endif
