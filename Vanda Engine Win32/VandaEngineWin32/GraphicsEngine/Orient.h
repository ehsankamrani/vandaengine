//Original Work: Copyright 2006 Sony Computer Entertainment Inc.
//Modified Work: Copyright (C) 2024 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#pragma once 
#include "matrix.h"
#include "transform.h"
#include <vector>

#include <boost/serialization/vector.hpp>
#include <boost/serialization/map.hpp> 
#include <boost/serialization/string.hpp> 

#include <iostream>
#include <sstream>
class COrient
{
protected:	
	std::vector<std::vector<CTransform *>> m_transforms;
	std::vector<CTransform *> m_sumTransforms;
	std::vector<CFloat> m_sumWeights;

	CBool m_updateLocalMatrix;					// LocalMatrix needs updating (initialize or update due to animations
	CMatrix m_localMatrix;						// Matrix version of just the transforms in this node
	CMatrix	m_localToWorldMatrix;				// Full local to world matrix for this node
	CMatrix	m_inverseLocalToWorldMatrix;
	CMatrix	m_inverseTransposeLocalToWorldMatrix;
	CMatrix	m_inverseBindMatrix; 
	CMatrix	m_combinedSkinMatrix; 

	//When true it causes an update of m_combinedSkinMatrix but unless
	//SetLocalToWorldMatrix is called (and it never is) this will always be true.
	CBool m_updateLocalToWorldMatrix; 

private:
	friend class boost::serialization::access;

	template <typename Archive>
	void serialize(Archive &ar, const unsigned int version)
	{
		ar & m_transforms;
		ar & m_sumTransforms;
		ar & m_sumWeights;
		ar & m_updateLocalMatrix;					// LocalMatrix needs updating (initialize or update due to animations
		ar & m_localMatrix;						// Matrix version of just the transforms in this node
		ar & m_localToWorldMatrix;				// Full local to world matrix for this node
		ar & m_inverseLocalToWorldMatrix;
		ar & m_inverseTransposeLocalToWorldMatrix;
		ar & m_inverseBindMatrix;
		ar & m_combinedSkinMatrix;
		ar & m_updateLocalToWorldMatrix;
	}

public:
	COrient();
	~COrient();
protected:
	inline CFloat *GetSkinMatrix() {return (CFloat *)m_combinedSkinMatrix;} 	
	
public:

	CMatrix* SetLocalToWorldMatrix(CMatrix * m) 
	{
		memcpy(&m_localToWorldMatrix, m, sizeof(CMatrix));
		m_updateLocalMatrix = CFalse;
		m_updateLocalToWorldMatrix = CFalse;
		return &m_localToWorldMatrix;
	};
	CMatrix* SetLocalMatrix(CMatrix * m)
	{
		memcpy(&m_localMatrix, m, sizeof(CMatrix));
		m_updateLocalMatrix = CFalse;
		return &m_localMatrix;
	};

	inline CMatrix *GetLocalToWorldMatrix(){ return &m_localToWorldMatrix; } 
	inline CMatrix *GetInverseLocalToWorldMatrix(){ return &m_inverseLocalToWorldMatrix; } 
	inline CMatrix *GetInverseTransposeLocalToWorldMatrix(){ return &m_inverseTransposeLocalToWorldMatrix; } 
	inline CMatrix *GetInverseBindMatrix(){ return &m_inverseBindMatrix; }

	inline  CVoid SetUpdateLocalMatrix(CBool b) { m_updateLocalMatrix = (CBool) b;};
	inline  CVoid SetUpdateLocalToWorldMatrix(CBool b) { m_updateLocalToWorldMatrix = (CBool) b;};

};