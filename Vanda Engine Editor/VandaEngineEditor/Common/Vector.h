//Copyright (C) 2023 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#pragma once


class CVector  
{
public:
	CVector();
	CVector( CFloat I, CFloat J, CFloat K );
	virtual ~CVector();

public:
	CVoid operator = (CVector v);            
	CVector operator + (CVector v);           //Add
	CVector operator - (CVector v);           //Subtract
	CVector operator *(CFloat scalar);     
	CVector operator ^ ( CVector v );  //Cross Product
	const CFloat operator % ( CVector v );  //Dot product
	CVoid operator *= (CFloat scalar);

	CVoid Normalize(CVoid);
	CFloat Magnitude(CVoid);

	CFloat m_k;
	CFloat m_j;
	CFloat m_i;
	CFloat m_Mag;
};
