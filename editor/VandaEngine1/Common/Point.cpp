//Copyright (C) 2020 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#include "stdafx.h"
#include "Point.h"

Point::Point()
{
	m_x = m_y = m_z = 0.0f;												// Initalize the x, y, z components to zero
}

Point::Point( CFloat X, CFloat Y, CFloat Z )
{
	m_x = X;
	m_y = Y;
	m_z = Z;
}

Point::~Point()
{

}

CVoid Point::operator =(Point p)
{
	m_x = p.m_x;														// Set this Point to = the Point passed in.
	m_y = p.m_y;
	m_z = p.m_z;
}

// Usually this operator get called when we scaled a vector to get
// a 3D Point IE  Point = unit_vector * 25.0f;
CVoid Point::operator =(CVector v)
{
	m_x = v.m_i;														// Set this Point to the vectors i component
	m_y = v.m_j;														// Set this Point to the vectors j component
	m_z = v.m_k;														// Set this Point to the vectors k component
}

// Subrtacts the components of two CPoints to get a vector.
CVector Point::operator -(Point p)
{
	CVector r;

	r.m_i = m_x - p.m_x;
	r.m_j = m_y - p.m_y;
	r.m_k = m_z - p.m_z;

	return(r);
}

// Technically your not supposed to be able to add 2 CPoints 
// together by mathmatical definations but I don't mind 
// bending the rules a little.
Point Point::operator +(Point p)
{
	Point r;

	r.m_x = m_x + p.m_x;
	r.m_y = m_y + p.m_y;
	r.m_z = m_z + p.m_z;

	return(r);
}

CVector Point::operator +( CVector v )
{
	CVector r;
	r.m_i = m_x + v.m_i;
	r.m_j = m_y + v.m_j;
	r.m_k = m_z + v.m_k;
	return(r);
}
// Technically your not supposed to be able to add 2 CPoints 
// together by mathmatical definations but I don't mind 
// bending the rules a little.
CVoid Point::operator +=(Point p)
{
	m_x += p.m_x;
	m_y += p.m_y;
	m_z += p.m_z;
}
