//Copyright (C) 2018 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#pragma once
#include "Vector.h"

class Point  
{
public:
	Point();
	Point( CFloat x, CFloat y, CFloat z );
	~Point();

	CVoid operator+=(Point p);
	Point operator+(Point p);
	CVector operator-(Point p);
	CVoid operator =(CVector v);
    CVector operator +( CVector v );
	CVoid operator =(Point p);

	CFloat m_z;
	CFloat m_y;
	CFloat m_x;
};

