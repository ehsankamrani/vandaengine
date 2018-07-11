/*
 * Copyright 2006 Sony Computer Entertainment Inc.
 *
 * Licensed under the SCEA Shared Source License, Version 1.0 (the "License"); you may not use this 
 * file except in compliance with the License. You may obtain a copy of the License at:
 * http://research.scea.com/scea_shared_source_license.html
 *
 * Unless required by applicable law or agreed to in writing, software distributed under the License 
 * is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or 
 * implied. See the License for the specific language governing permissions and limitations under the 
 * License. 
 */

#include "stdafx.h"
#include "matrix.h"

//PrintInfo in column major order
CVoid CMatrixPrint(CMatrix LMtx)
{
	CChar temp[MAX_NAME_SIZE];
	sprintf( temp, "%f,%f,%f,%f\n%f,%f,%f,%f\n%f,%f,%f,%f\n%f,%f,%f,%f\n",
		LMtx[M00], LMtx[M10], LMtx[M20], LMtx[M30],
		LMtx[M01], LMtx[M11], LMtx[M21], LMtx[M31],
		LMtx[M02], LMtx[M12], LMtx[M22], LMtx[M32],
		LMtx[M03], LMtx[M13], LMtx[M23], LMtx[M33]);
	//PrintInfo( temp );
}
//LDstMtx = ( LSrcMtx )T
CVoid CMatrixTranspose( const CMatrix LSrcMtx, CMatrix LDstMtx )
{
	CMatrix outMat;
	CMatrixCopy( LSrcMtx, outMat ); 
	
	LDstMtx[M00] = outMat[M00];
	LDstMtx[M01] = outMat[M10];
	LDstMtx[M02] = outMat[M20];
	LDstMtx[M03] = outMat[M30];
		
	LDstMtx[M10] = outMat[M01];
	LDstMtx[M11] = outMat[M11];
	LDstMtx[M12] = outMat[M21];
	LDstMtx[M13] = outMat[M31];

	LDstMtx[M20] = outMat[M02];
	LDstMtx[M21] = outMat[M12];
	LDstMtx[M22] = outMat[M22];
	LDstMtx[M23] = outMat[M32];

	LDstMtx[M30] = outMat[M03];
	LDstMtx[M31] = outMat[M13];
	LDstMtx[M32] = outMat[M23];
	LDstMtx[M33] = outMat[M33];
}

CVoid CMatrixTranspose3x4( const CMatrix LSrcMtx, CMatrix3x4 LDstMtx )
{
	CMatrix outMat;
	CMatrixCopy( LSrcMtx, outMat ); 
	
	LDstMtx[M00] = outMat[M00];
	LDstMtx[M01] = outMat[M10];
	LDstMtx[M02] = outMat[M20];
	LDstMtx[M03] = outMat[M30];
		
	LDstMtx[M10] = outMat[M01];
	LDstMtx[M11] = outMat[M11];
	LDstMtx[M12] = outMat[M21];
	LDstMtx[M13] = outMat[M31];

	LDstMtx[M20] = outMat[M02];
	LDstMtx[M21] = outMat[M12];
	LDstMtx[M22] = outMat[M22];
	LDstMtx[M23] = outMat[M32];
}

//LDstMtx = LMtx1 * LMtx2
CVoid CMatrixMult(const CMatrix LMtx1, const CMatrix LMtx2, CMatrix LDstMtx)
{
	CFloat	LM1_00, LM1_01, LM1_02, LM1_03,
			LM1_10, LM1_11, LM1_12, LM1_13,
			LM1_20, LM1_21, LM1_22, LM1_23,
			LM1_30, LM1_31, LM1_32, LM1_33,
			LM2_00, LM2_01, LM2_02, LM2_03,
			LM2_10, LM2_11, LM2_12, LM2_13,
			LM2_20, LM2_21, LM2_22, LM2_23,
			LM2_30, LM2_31, LM2_32, LM2_33;


	LM1_00 = LMtx1[M00];LM1_01 = LMtx1[M01];LM1_02 = LMtx1[M02];LM1_03 = LMtx1[M03];
	LM1_10 = LMtx1[M10];LM1_11 = LMtx1[M11];LM1_12 = LMtx1[M12];LM1_13 = LMtx1[M13];
	LM1_20 = LMtx1[M20];LM1_21 = LMtx1[M21];LM1_22 = LMtx1[M22];LM1_23 = LMtx1[M23];
	LM1_30 = LMtx1[M30];LM1_31 = LMtx1[M31];LM1_32 = LMtx1[M32];LM1_33 = LMtx1[M33];

	LM2_00 = LMtx2[M00];LM2_01 = LMtx2[M01];LM2_02 = LMtx2[M02];LM2_03 = LMtx2[M03];
	LM2_10 = LMtx2[M10];LM2_11 = LMtx2[M11];LM2_12 = LMtx2[M12];LM2_13 = LMtx2[M13];
	LM2_20 = LMtx2[M20];LM2_21 = LMtx2[M21];LM2_22 = LMtx2[M22];LM2_23 = LMtx2[M23];
	LM2_30 = LMtx2[M30];LM2_31 = LMtx2[M31];LM2_32 = LMtx2[M32];LM2_33 = LMtx2[M33];

	LDstMtx[M00] = LM1_00*LM2_00 + LM1_01*LM2_10 + LM1_02*LM2_20 + LM1_03*LM2_30;
	LDstMtx[M01] = LM1_00*LM2_01 + LM1_01*LM2_11 + LM1_02*LM2_21 + LM1_03*LM2_31;
	LDstMtx[M02] = LM1_00*LM2_02 + LM1_01*LM2_12 + LM1_02*LM2_22 + LM1_03*LM2_32;
	LDstMtx[M03] = LM1_00*LM2_03 + LM1_01*LM2_13 + LM1_02*LM2_23 + LM1_03*LM2_33;

	LDstMtx[M10] = LM1_10*LM2_00 + LM1_11*LM2_10 + LM1_12*LM2_20 + LM1_13*LM2_30;
	LDstMtx[M11] = LM1_10*LM2_01 + LM1_11*LM2_11 + LM1_12*LM2_21 + LM1_13*LM2_31;
	LDstMtx[M12] = LM1_10*LM2_02 + LM1_11*LM2_12 + LM1_12*LM2_22 + LM1_13*LM2_32;
	LDstMtx[M13] = LM1_10*LM2_03 + LM1_11*LM2_13 + LM1_12*LM2_23 + LM1_13*LM2_33;

	LDstMtx[M20] = LM1_20*LM2_00 + LM1_21*LM2_10 + LM1_22*LM2_20 + LM1_23*LM2_30;
	LDstMtx[M21] = LM1_20*LM2_01 + LM1_21*LM2_11 + LM1_22*LM2_21 + LM1_23*LM2_31;
	LDstMtx[M22] = LM1_20*LM2_02 + LM1_21*LM2_12 + LM1_22*LM2_22 + LM1_23*LM2_32;
	LDstMtx[M23] = LM1_20*LM2_03 + LM1_21*LM2_13 + LM1_22*LM2_23 + LM1_23*LM2_33;

	LDstMtx[M30] = LM1_30*LM2_00 + LM1_31*LM2_10 + LM1_32*LM2_20 + LM1_33*LM2_30;
	LDstMtx[M31] = LM1_30*LM2_01 + LM1_31*LM2_11 + LM1_32*LM2_21 + LM1_33*LM2_31;
	LDstMtx[M32] = LM1_30*LM2_02 + LM1_31*LM2_12 + LM1_32*LM2_22 + LM1_33*LM2_32;
	LDstMtx[M33] = LM1_30*LM2_03 + LM1_31*LM2_13 + LM1_32*LM2_23 + LM1_33*LM2_33;
}
//LDestMtx = LSrcMtx * LDestMtx
CVoid CMatrix4x4Mult(CMatrix LSrcMtx, CMatrix LDestMtx)
{
	CFloat	L00, L01, L02, L03, L10, L11, L12, L13,
			L20, L21, L22, L23, L30, L31, L32, L33;

	L00 = LDestMtx[M00];
	L10 = LDestMtx[M10];
	L20 = LDestMtx[M20];
	L30 = LDestMtx[M30];
	LDestMtx[M00] = LSrcMtx[M00]*L00+LSrcMtx[M01]*L10+LSrcMtx[M02]*L20+LSrcMtx[M03]*L30;
	LDestMtx[M10] = LSrcMtx[M10]*L00+LSrcMtx[M11]*L10+LSrcMtx[M12]*L20+LSrcMtx[M13]*L30;
	LDestMtx[M20] = LSrcMtx[M20]*L00+LSrcMtx[M21]*L10+LSrcMtx[M22]*L20+LSrcMtx[M23]*L30;
	LDestMtx[M30] = LSrcMtx[M30]*L00+LSrcMtx[M31]*L10+LSrcMtx[M32]*L20+LSrcMtx[M33]*L30;

	L01 = LDestMtx[M01];
	L11 = LDestMtx[M11];
	L21 = LDestMtx[M21];
	L31 = LDestMtx[M31];
	LDestMtx[M01] = LSrcMtx[M00]*L01+LSrcMtx[M01]*L11+LSrcMtx[M02]*L21+LSrcMtx[M03]*L31;
	LDestMtx[M11] = LSrcMtx[M10]*L01+LSrcMtx[M11]*L11+LSrcMtx[M12]*L21+LSrcMtx[M13]*L31;
	LDestMtx[M21] = LSrcMtx[M20]*L01+LSrcMtx[M21]*L11+LSrcMtx[M22]*L21+LSrcMtx[M23]*L31;
	LDestMtx[M31] = LSrcMtx[M30]*L01+LSrcMtx[M31]*L11+LSrcMtx[M32]*L21+LSrcMtx[M33]*L31;
	
	L02 = LDestMtx[M02];
	L12 = LDestMtx[M12];
	L22 = LDestMtx[M22];
	L32 = LDestMtx[M32];
	LDestMtx[M02] = LSrcMtx[M00]*L02+LSrcMtx[M01]*L12+LSrcMtx[M02]*L22+LSrcMtx[M03]*L32;
	LDestMtx[M12] = LSrcMtx[M10]*L02+LSrcMtx[M11]*L12+LSrcMtx[M12]*L22+LSrcMtx[M13]*L32;
	LDestMtx[M22] = LSrcMtx[M20]*L02+LSrcMtx[M21]*L12+LSrcMtx[M22]*L22+LSrcMtx[M23]*L32;
	LDestMtx[M32] = LSrcMtx[M30]*L02+LSrcMtx[M31]*L12+LSrcMtx[M32]*L22+LSrcMtx[M33]*L32;
	
	L03 = LDestMtx[M03];
	L13 = LDestMtx[M13];
	L23 = LDestMtx[M23];
	L33 = LDestMtx[M33];
	LDestMtx[M03] = LSrcMtx[M00]*L03+LSrcMtx[M01]*L13+LSrcMtx[M02]*L23+LSrcMtx[M03]*L33;
	LDestMtx[M13] = LSrcMtx[M10]*L03+LSrcMtx[M11]*L13+LSrcMtx[M12]*L23+LSrcMtx[M13]*L33;
	LDestMtx[M23] = LSrcMtx[M20]*L03+LSrcMtx[M21]*L13+LSrcMtx[M22]*L23+LSrcMtx[M23]*L33;
	LDestMtx[M33] = LSrcMtx[M30]*L03+LSrcMtx[M31]*L13+LSrcMtx[M32]*L23+LSrcMtx[M33]*L33;
}

CVoid CMatrix4x4Mult(CMatrix LSrcMtx, CMatrix LDstMtx, CFloat multiplier)
{
	LDstMtx[M00] = LSrcMtx[M00] *multiplier;
	LDstMtx[M10] = LSrcMtx[M10] * multiplier;
	LDstMtx[M20] = LSrcMtx[M20] *multiplier;
	LDstMtx[M30] = LSrcMtx[M30] * multiplier;

	LDstMtx[M01] = LSrcMtx[M01] * multiplier;
	LDstMtx[M11] = LSrcMtx[M11] * multiplier;
	LDstMtx[M21] = LSrcMtx[M21] * multiplier;
	LDstMtx[M31] = LSrcMtx[M31] * multiplier;
	
	LDstMtx[M02] = LSrcMtx[M02] * multiplier;
	LDstMtx[M12] = LSrcMtx[M12] * multiplier;
	LDstMtx[M22] = LSrcMtx[M22] * multiplier;
	LDstMtx[M32] = LSrcMtx[M32] * multiplier;
	
	LDstMtx[M03] = LSrcMtx[M03] * multiplier;
	LDstMtx[M13] = LSrcMtx[M13] * multiplier;
	LDstMtx[M23] = LSrcMtx[M23] * multiplier;
	LDstMtx[M33] = LSrcMtx[M33] * multiplier;
}
//LDestMtx = LSrcParMtx * LSrcChildMtx
CVoid CMatrixConcat(const CMatrix LSrcParMtx, const CMatrix LSrcChildMtx, CMatrix LDestMtx)
{
	CFloat	L00, L01, L02, L03, L10, L11, L12, L13,
			L20, L21, L22, L23, L30, L31, L32, L33;

	L00 = LSrcChildMtx[M00];L01 = LSrcChildMtx[M01];L02 = LSrcChildMtx[M02];L03 = LSrcChildMtx[M03];
	L10 = LSrcChildMtx[M10];L11 = LSrcChildMtx[M11];L12 = LSrcChildMtx[M12];L13 = LSrcChildMtx[M13];
	L20 = LSrcChildMtx[M20];L21 = LSrcChildMtx[M21];L22 = LSrcChildMtx[M22];L23 = LSrcChildMtx[M23];
	L30 = LSrcChildMtx[M30];L31 = LSrcChildMtx[M31];L32 = LSrcChildMtx[M32];L33 = LSrcChildMtx[M33];

	LDestMtx[M00] = LSrcParMtx[M00]*L00+LSrcParMtx[M01]*L10+LSrcParMtx[M02]*L20+LSrcParMtx[M03]*L30;
	LDestMtx[M01] = LSrcParMtx[M00]*L01+LSrcParMtx[M01]*L11+LSrcParMtx[M02]*L21+LSrcParMtx[M03]*L31;
	LDestMtx[M02] = LSrcParMtx[M00]*L02+LSrcParMtx[M01]*L12+LSrcParMtx[M02]*L22+LSrcParMtx[M03]*L32;
	LDestMtx[M03] = LSrcParMtx[M00]*L03+LSrcParMtx[M01]*L13+LSrcParMtx[M02]*L23+LSrcParMtx[M03]*L33;

	LDestMtx[M10] = LSrcParMtx[M10]*L00+LSrcParMtx[M11]*L10+LSrcParMtx[M12]*L20+LSrcParMtx[M13]*L30;
	LDestMtx[M11] = LSrcParMtx[M10]*L01+LSrcParMtx[M11]*L11+LSrcParMtx[M12]*L21+LSrcParMtx[M13]*L31;
	LDestMtx[M12] = LSrcParMtx[M10]*L02+LSrcParMtx[M11]*L12+LSrcParMtx[M12]*L22+LSrcParMtx[M13]*L32;
	LDestMtx[M13] = LSrcParMtx[M10]*L03+LSrcParMtx[M11]*L13+LSrcParMtx[M12]*L23+LSrcParMtx[M13]*L33;

	LDestMtx[M20] = LSrcParMtx[M20]*L00+LSrcParMtx[M21]*L10+LSrcParMtx[M22]*L20+LSrcParMtx[M23]*L30;
	LDestMtx[M21] = LSrcParMtx[M20]*L01+LSrcParMtx[M21]*L11+LSrcParMtx[M22]*L21+LSrcParMtx[M23]*L31;
	LDestMtx[M22] = LSrcParMtx[M20]*L02+LSrcParMtx[M21]*L12+LSrcParMtx[M22]*L22+LSrcParMtx[M23]*L32;
	LDestMtx[M23] = LSrcParMtx[M20]*L03+LSrcParMtx[M21]*L13+LSrcParMtx[M22]*L23+LSrcParMtx[M23]*L33;

	LDestMtx[M30] = LSrcParMtx[M30]*L00+LSrcParMtx[M31]*L10+LSrcParMtx[M32]*L20+LSrcParMtx[M33]*L30;
	LDestMtx[M31] = LSrcParMtx[M30]*L01+LSrcParMtx[M31]*L11+LSrcParMtx[M32]*L21+LSrcParMtx[M33]*L31;
	LDestMtx[M32] = LSrcParMtx[M30]*L02+LSrcParMtx[M31]*L12+LSrcParMtx[M32]*L22+LSrcParMtx[M33]*L32;
	LDestMtx[M33] = LSrcParMtx[M30]*L03+LSrcParMtx[M31]*L13+LSrcParMtx[M32]*L23+LSrcParMtx[M33]*L33;
}


CVoid CQuaternionToMatrix(CQuat * LQ, CFloat * LMatrix)
{
	CFloat	LS, LXS, LYS, LZS, LWX, LWY, LWZ, LXX, LXY, LXZ, LYY, LYZ, LZZ;

	LS = 2.0f/(LQ->x*LQ->x+LQ->y*LQ->y+LQ->z*LQ->z+LQ->w*LQ->w);

	LXS = LQ->x*LS;LYS = LQ->y*LS;LZS = LQ->z*LS;
	LWX = LQ->w*LXS;LWY = LQ->w*LYS;LWZ = LQ->w*LZS;
	LXX = LQ->x*LXS;LXY = LQ->x*LYS;LXZ = LQ->x*LZS;
	LYY = LQ->y*LYS;LYZ = LQ->y*LZS;LZZ = LQ->z*LZS;

	LMatrix[M00] = 1.0f-(LYY+LZZ);
	LMatrix[M01] = LXY+LWZ;
	LMatrix[M02] = LXZ-LWY;

	LMatrix[M10] = LXY-LWZ;
	LMatrix[M11] = 1.0f-(LXX+LZZ);
	LMatrix[M12] = LYZ+LWX;

	LMatrix[M20] = LXZ+LWY;
	LMatrix[M21] = LYZ-LWX;
	LMatrix[M22] = 1.0f-(LXX+LYY);

	LMatrix[M03] = 0.0f;
	LMatrix[M13] = 0.0f;
	LMatrix[M23] = 0.0f;
	LMatrix[M30] = 0.0f;
	LMatrix[M31] = 0.0;
	LMatrix[M32] = 0.0;
	LMatrix[M33] = 1.0f;
}

CVoid CQuaternionToMatrix(CVec4f * LQ, CFloat * LMatrix)
{
	CFloat	LS, LXS, LYS, LZS, LWX, LWY, LWZ, LXX, LXY, LXZ, LYY, LYZ, LZZ;

	LS = 2.0f/(LQ->x*LQ->x+LQ->y*LQ->y+LQ->z*LQ->z+LQ->w*LQ->w);

	LXS = LQ->x*LS;
	LYS = LQ->y*LS;
	LZS = LQ->z*LS;

	LWX = LQ->w*LXS;
	LWY = LQ->w*LYS;
	LWZ = LQ->w*LZS;

	LXX = LQ->x*LXS;
	LXY = LQ->x*LYS;
	LXZ = LQ->x*LZS;
	LYY = LQ->y*LYS;
	LYZ = LQ->y*LZS;
	LZZ = LQ->z*LZS;

	LMatrix[M00] = 1.0f-(LYY+LZZ);
	LMatrix[M01] = LXY+LWZ;
	LMatrix[M02] = LXZ-LWY;

	LMatrix[M10] = LXY-LWZ;
	LMatrix[M11] = 1.0f-(LXX+LZZ);
	LMatrix[M12] = LYZ+LWX;

	LMatrix[M20] = LXZ+LWY;
	LMatrix[M21] = LYZ-LWX;
	LMatrix[M22] = 1.0f-(LXX+LYY);

	LMatrix[M03] = 0.0f;
	LMatrix[M13] = 0.0f;
	LMatrix[M23] = 0.0f;
	LMatrix[M30] = 0.0f;
	LMatrix[M31] = 0.0;
	LMatrix[M32] = 0.0;
	LMatrix[M33] = 1.0f;
}

void CMatrixTranslate(CMatrix LMatrix, CFloat LX, CFloat LY, CFloat LZ)
{
	CFloat	LDX, LDY, LDZ;

	LDX = LX*LMatrix[M00]+LY*LMatrix[M10]+LZ*LMatrix[M20];
	LDY = LX*LMatrix[M01]+LY*LMatrix[M11]+LZ*LMatrix[M21];
	LDZ = LX*LMatrix[M02]+LY*LMatrix[M12]+LZ*LMatrix[M22];

	LMatrix[M30] += LDX;
	LMatrix[M31] += LDY;
	LMatrix[M32] += LDZ;
}
//LMatrix = LRotMatrix * LMatrix
CVoid CMatrix4x4RotateAngleAxis(CMatrix LMatrix, CFloat LAxisX, CFloat LAxisY, CFloat LAxisZ, CFloat LAngle)
{
	CMatrix	LRotMatrix;
	CVec4f	LQuaternion;
	CFloat	LAngleSin = (CFloat)sin(LAngle*0.5f*DEGREES_TO_RADIANS),
			LAngleCos = (CFloat)cos(LAngle*0.5f*DEGREES_TO_RADIANS);


	CMatrixLoadIdentity(LRotMatrix);
	LQuaternion.x = LAxisX*LAngleSin;
	LQuaternion.y = LAxisY*LAngleSin;
	LQuaternion.z = LAxisZ*LAngleSin;
	LQuaternion.w = LAngleCos;
	CQuaternionToMatrix(&LQuaternion, LRotMatrix);

	CMatrix4x4Mult(LRotMatrix, LMatrix);
}

CVoid CMatrix4x4RotateAngleAxis(CMatrix LMatrix, CVec4f AxisRot)
{
	CMatrix	LRotMatrix;
	CVec4f	LQuaternion;

	// Build the rotation matix based off of the axis rotation passed in 
	CFloat	LAngleSin = (CFloat)sin(AxisRot.w*0.5f*DEGREES_TO_RADIANS),
			LAngleCos = (CFloat)cos(AxisRot.w*0.5f*DEGREES_TO_RADIANS);


	CMatrixLoadIdentity(LRotMatrix);
	LQuaternion.x = AxisRot.x*LAngleSin;
	LQuaternion.y = AxisRot.y*LAngleSin;
	LQuaternion.z = AxisRot.z*LAngleSin;
	LQuaternion.w = LAngleCos;
	CQuaternionToMatrix(&LQuaternion, LRotMatrix);

	// concate to previously passed in matrix 
	CMatrix4x4Mult(LRotMatrix, LMatrix);
}

//LMatrix = TMatrix * LMatrix
CVoid CMatrix4x4Translate(CMatrix LMatrix, CVec4f translate)
{
	CMatrix	TMatrix;
	
	// Build the translation matrix 
	CMatrixLoadIdentity(TMatrix);
	TMatrix[M30] = translate.x; 
	TMatrix[M31] = translate.y; 
	TMatrix[M32] = translate.z;

	// concatinate to previously passed in matrix 
	CMatrix4x4Mult(TMatrix, LMatrix);
}

//LMatrix = SMatrix * LMatrix
CVoid CMatrix4x4Scale(CMatrix LMatrix, CVec4f scale)
{
	CMatrix	SMatrix;
	
	// Build the translation matrix 
	CMatrixLoadIdentity(SMatrix);
	SMatrix[M00] = scale.x; 
	SMatrix[M11] = scale.y; 
	SMatrix[M22] = scale.z;

	// concatinate to previously passed in matrix 
	CMatrix4x4Mult(SMatrix, LMatrix);
}

CVoid CMatrix3x4Invert(CMatrix LM, CMatrix LMI)
{
	//Because this doesn't copy over the last column of the source to the dest, if the output matrix
	//isn't initialized it may turn out a bogus 4x4 matrix, should this function set that column?

	CFloat LM00 = LM[M00], LM01 = LM[M01], LM02 = LM[M02],	// Use temporary storage, in case LM == LMI
		LM10 = LM[M10], LM11 = LM[M11], LM12 = LM[M12],
		LM20 = LM[M20], LM21 = LM[M21], LM22 = LM[M22],
		LInvD = 1.0f / (LM22*LM11*LM00 - LM22*LM10*LM01 - LM21*LM12*LM00 + LM21*LM10*LM02 + LM20*LM12*LM01 - LM20*LM11*LM02);

	LMI[M00] =  (LM22*LM11 - LM21*LM12) * LInvD;
	LMI[M01] = (-LM22*LM01 + LM21*LM02) * LInvD;
	LMI[M02] =  (LM12*LM01 - LM11*LM02) * LInvD;
	LMI[M10] = (-LM22*LM10 + LM20*LM12) * LInvD;
	LMI[M11] =  (LM22*LM00 - LM20*LM02) * LInvD;
	LMI[M12] = (-LM12*LM00 + LM10*LM02) * LInvD;
	LMI[M20] =  (LM21*LM10 - LM20*LM11) * LInvD;
	LMI[M21] = (-LM21*LM00 + LM20*LM01) * LInvD;
	LMI[M22] =  (LM11*LM00 - LM10*LM01) * LInvD;

	CMatrix3x3TransformVV(LMI,  -LM[M30], -LM[M31], -LM[M32],  LMI[M30], LMI[M31], LMI[M32]);
}

CVoid CMatrix3x3TransformVV( CMatrix mMatrix,  CFloat mXIn, CFloat mYIn, CFloat mZIn, CFloat &mXOut, CFloat &mYOut, CFloat &mZOut)
{
	CFloat	mX = mXIn, mY = mYIn, mZ = mZIn;
	mXOut = mX*(mMatrix)[M00] + mY*(mMatrix)[M10] + mZ*(mMatrix)[M20];
	mYOut = mX*(mMatrix)[M01] + mY*(mMatrix)[M11] + mZ*(mMatrix)[M21];
	mZOut = mX*(mMatrix)[M02] + mY*(mMatrix)[M12] + mZ*(mMatrix)[M22];
}