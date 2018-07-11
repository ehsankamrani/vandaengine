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

#pragma once
#include "../common/utility.h"
#include <string.h>

inline CVoid CMatrixLoadIdentity(CMatrix LDstMtx)
{
	LDstMtx[M00] = 1.0;LDstMtx[M01] = 0.0;LDstMtx[M02] = 0.0;LDstMtx[M03] = 0.0;
	LDstMtx[M10] = 0.0;LDstMtx[M11] = 1.0;LDstMtx[M12] = 0.0;LDstMtx[M13] = 0.0;
	LDstMtx[M20] = 0.0;LDstMtx[M21] = 0.0;LDstMtx[M22] = 1.0;LDstMtx[M23] = 0.0;
	LDstMtx[M30] = 0.0;LDstMtx[M31] = 0.0;LDstMtx[M32] = 0.0;LDstMtx[M33] = 1.0;
}

inline CVoid CMatrixCopy( const CMatrix LSrcMtx, CMatrix LDstMtx)
{
	memcpy(LDstMtx, LSrcMtx, sizeof(CMatrix));
}

CVoid CMatrixRotateTranslate(CMatrix LMatrix, CVec4f RotX, CVec4f RotY, CVec4f RotZ, CVec3f Trans );
CVoid CMatrix3x4Invert(CMatrix LM, CMatrix LMI);
CVoid CMatrix3x3TransformVV( CMatrix mMatrix,  
							CFloat mXIn, CFloat mYIn, CFloat mZIn, 
							CFloat &mXOut, CFloat &mYOut, CFloat &mZOut);
CVoid CMatrixTranspose( const CMatrix LSrcMtx, CMatrix LDstMtx );
CVoid CMatrixTranspose3x4( const CMatrix LSrcMtx, CMatrix3x4 LDstMtx );
CVoid CMatrixToQuat( const CMatrix rotMat, CQuat & RotQuat ); 

inline CVoid CMatrixTransform( CMatrix Matrix, const CVec3f & v, CVec3f & tv)
{
	tv.x = v.x*Matrix[M00] + v.y*Matrix[M10] + v.z*Matrix[M20] + Matrix[M30];
	tv.y = v.x*Matrix[M01] + v.y*Matrix[M11] + v.z*Matrix[M21] + Matrix[M31];
	tv.z = v.x*Matrix[M02] + v.y*Matrix[M12] + v.z*Matrix[M22] + Matrix[M32];
}

inline CVoid CMatrixRotate( CMatrix Matrix, const CVec3f & v, CVec3f & tv)
{
	tv.x = v.x*Matrix[M00] + v.y*Matrix[M10] + v.z*Matrix[M20];
	tv.y = v.x*Matrix[M01] + v.y*Matrix[M11] + v.z*Matrix[M21];
	tv.z = v.x*Matrix[M02] + v.y*Matrix[M12] + v.z*Matrix[M22];
}

inline CVoid CMatrix3x4TransformSkin( CMatrix Matrix, const CVec3f & v, CVec3f & tv)
{
	tv.x = v.x*Matrix[M00] + v.y*Matrix[M10] + v.z*Matrix[M20] + Matrix[M30];
	tv.y = v.x*Matrix[M01] + v.y*Matrix[M11] + v.z*Matrix[M21] + Matrix[M31];
	tv.z = v.x*Matrix[M02] + v.y*Matrix[M12] + v.z*Matrix[M22] + Matrix[M32];
}

inline CVoid CMatrix3x4RotateSkin( CMatrix Matrix, const CVec3f & v, CVec3f & tv)
{
	tv.x = v.x*Matrix[M00] + v.y*Matrix[M10] + v.z*Matrix[M20];
	tv.y = v.x*Matrix[M01] + v.y*Matrix[M11] + v.z*Matrix[M21];
	tv.z = v.x*Matrix[M02] + v.y*Matrix[M12] + v.z*Matrix[M22];
}


CVoid CMatrix4x4RotateAngleAxis(CMatrix LMatrix, CFloat LAxisX, CFloat LAxisY, CFloat LAxisZ, CFloat LAngle);

CVoid CMatrix4x4RotateAngleAxis(CMatrix LMatrix, CVec4f AxisRot);
CVoid CMatrix4x4Translate(CMatrix LMatrix, CVec4f Trans);
CVoid CMatrix4x4Scale(CMatrix LMatrix, CVec4f Scale); 

CVoid CMatrixMult( const CMatrix LMtx1, const CMatrix LMtx2, CMatrix LDstMtx);
CVoid CMatrix4x4Mult(CMatrix LSrcMtx, CMatrix LDestMtx);
CVoid CMatrix4x4Mult(CMatrix LSrcMtx, CMatrix LDstMtx, CFloat multiplier);
CVoid CMatrixTranslate(CMatrix LMatrix, CFloat LX, CFloat LY, CFloat LZ);
CVoid CQuaternionToMatrix(CQuat * LQ, CFloat * LMatrix);
