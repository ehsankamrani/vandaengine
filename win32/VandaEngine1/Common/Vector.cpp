//Copyright (C) 2020 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#include "stdafx.h"
#include "Vector.h"
#include <math.h>
CVector::CVector()
{
	m_i = m_j = m_k = m_Mag = 0.0f;
}

CVector::CVector( CFloat i, CFloat j, CFloat k )
{
	m_i = i;
	m_j = j;
	m_k = k;
}

CVector::~CVector()
{

}

// Scale the VECTOR times some number
CVoid CVector::operator *= ( CFloat scalar )
{
	m_i *= scalar;
	m_j *= scalar;
	m_k *= scalar;
}

// Computes the magnitude and saves it in m_Mag also returns the 
// Magnitude
CFloat CVector::Magnitude()
{
	CFloat result; 
	
	result = CFloat(sqrt( m_i * m_i + m_j * m_j + m_k * m_k));
	m_Mag = result;
	return( result );
}

// Makes the VECTOR unit length.
CVoid CVector::Normalize()
{
	if(m_Mag != 0.0f)
	{
		m_i /= m_Mag;
		m_j /= m_Mag;
		m_k /= m_Mag;

		Magnitude();
	}
}

// Multiply this VECTOR times another and return the result
CVector CVector::operator * ( CFloat scalar )
{
	CVector r;

	r.m_i = m_i * scalar;
	r.m_j = m_j * scalar;
	r.m_k = m_k * scalar;

	return(r);
}

// Add this VECTOR to another and return the result
CVector CVector::operator + ( CVector v )
{
	CVector r;

	r.m_i = m_i + v.m_i;
	r.m_j = m_j + v.m_j;
	r.m_k = m_k + v.m_k;

	return(r);
}

CVector CVector::operator - ( CVector v )
{
	CVector r;

	r.m_i = m_i - v.m_i;
	r.m_j = m_j - v.m_j;
	r.m_k = m_k - v.m_k;

	return(r);
}

// Assign this VECTOR to the VECTOR passed in.
CVoid CVector::operator = ( CVector v )
{
	m_i = v.m_i;
	m_j = v.m_j;
	m_k = v.m_k;
	m_Mag = v.m_Mag;
}

//Cross Product
CVector CVector::operator ^ ( CVector v )
{
	CVector temp;
	temp.m_i = m_j * v.m_k - m_k * v.m_j;
	temp.m_j = m_k * v.m_i - m_i * v.m_k;
	temp.m_k = m_i * v.m_j - m_j * v.m_i;
	return(temp);
}

//Dot Product
const CFloat CVector::operator % ( CVector v )
{
	return ( m_i * v.m_i + m_j * v.m_j + m_k * v.m_k );
}

