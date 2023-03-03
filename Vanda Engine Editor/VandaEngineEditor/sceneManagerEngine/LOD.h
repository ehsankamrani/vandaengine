/*
 *  Progressive Mesh type Polygon Reduction Algorithm
 *  by Stan Melax (c) 1998
 *
 *  The function ProgressiveMesh() takes a model in an "indexed face 
 *  set" sort of way.  i.e. list of vertices and list of triangles.
 *  The function then does the polygon reduction algorithm
 *  internally and reduces the model all the way down to 0
 *  vertices and then returns the order in which the
 *  vertices are collapsed and to which neighbor each vertex
 *  is collapsed to.  More specifically the returned "permutation"
 *  indicates how to reorder your vertices so you can render
 *  an object by using the first n vertices (for the n 
 *  vertex version).  After permuting your vertices, the
 *  map list indicates to which vertex each vertex is collapsed to.
 */

#pragma once

#include "../common/utility.h"
#include "../common/list.h"
#include "../graphicsEngine/geometry.h"
class tridata {
  public:
	int	v[3];  // indices to vertex list
	// texture and vertex normal info removed for this demo
};

class CVertex;
class CTriangle;

class CLOD
{
public:
	CLOD();
	~CLOD();
	float ComputeEdgeCollapseCost(CVertex *u,CVertex *v);
	void ComputeEdgeCostAtVertex(CVertex *v);
	void ComputeAllEdgeCollapseCosts();
	void Collapse(CVertex *u,CVertex *v);
	void AddVertex(CGeometry* geometry);
	void AddFaces(CGeometry* geometry);
	CVertex * MinimumCostEdge();
	void ProgressiveMesh(CGeometry* geometry, List<int> &permutation );
	void PermuteVertices(CGeometry* geometry, List<int> &permutation);
	CVoid SetAlgorithm( CPhysXAlgorithm algorithm ) { m_algorithm = algorithm; }
	List<CVertex *>   vertices;
	List<CTriangle *> triangles;
	CPhysXAlgorithm m_algorithm;
};
