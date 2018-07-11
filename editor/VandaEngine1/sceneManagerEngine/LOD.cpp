/*
 *  Progressive Mesh type Polygon Reduction Algorithm
 *  by Stan Melax (c) 1998
 *  Permission to use any of this code wherever you want is granted..
 *  Although, please do acknowledge authorship if appropriate.
 *
 *  See the header file progmesh.h for a description of this module
 */
#include "stdafx.h"
#include "lod.h"
#include <stdio.h>  
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <windows.h>

/*
 *  For the polygon reduction algorithm we use data structures
 *  that contain a little bit more information than the usual
 *  indexed face set type of data structure.
 *  From a vertex we wish to be able to quickly get the
 *  neighboring faces and vertices.
 */
class CTriangle;
class CVertex;

class CTriangle {
  public:
	CVertex *         vertex[3]; // the 3 points that make this tri
	CVec3f           normal;    // unit vector othogonal to this face
	                 CTriangle(CVertex *v0,CVertex *v1,CVertex *v2, List<CTriangle*> &trianglesList);
	                 ~CTriangle();
	void             ComputeNormal();
	void             ReplaceVertex(CVertex *vold,CVertex *vnew);
	int              HasVertex(CVertex *v);
	List<CTriangle*> *tList;
};
class CVertex {
  public:
	CVec3f           position; // location of point in euclidean space
	int              id;       // place of vertex in original list
	List<CVertex *>   neighbor; // adjacent vertices
	List<CTriangle *> face;     // adjacent triangles
	float            objdist;  // cached cost of collapsing edge
	CVertex *         collapse; // candidate vertex for collapse
	                 CVertex(CVec3f v,int _id, List <CVertex*>&vertices);
	                 ~CVertex();
	void             RemoveIfNonNeighbor(CVertex *n);
	List<CVertex*> *vList;
	List<CVertex*> m_overlappedVertices;

};

CTriangle::CTriangle(CVertex *v0,CVertex *v1,CVertex *v2, List<CTriangle*> &trianglesList){
	assert(v0!=v1 && v1!=v2 && v2!=v0);
	vertex[0]=v0;
	vertex[1]=v1;
	vertex[2]=v2;
	ComputeNormal();
	trianglesList.Add(this);
	tList = &trianglesList;
	for(int i=0;i<3;i++) {
		vertex[i]->face.Add(this);
		for(int j=0;j<3;j++) if(i!=j) {
			vertex[i]->neighbor.AddUnique(vertex[j]);
		}
	}

}
CTriangle::~CTriangle(){
	int i;
	tList->Remove(this);

	for(i=0;i<3;i++) {
		if(vertex[i]) vertex[i]->face.Remove(this);
	}
	for(i=0;i<3;i++) {
		int i2 = (i+1)%3;
		if(!vertex[i] || !vertex[i2]) continue;
		vertex[i ]->RemoveIfNonNeighbor(vertex[i2]);
		vertex[i2]->RemoveIfNonNeighbor(vertex[i ]);
	}
}
int CTriangle::HasVertex(CVertex *v) {
	return (v==vertex[0] ||v==vertex[1] || v==vertex[2]);
}
void CTriangle::ComputeNormal(){
	CVec3f v0=vertex[0]->position;
	CVec3f v1=vertex[1]->position;
	CVec3f v2=vertex[2]->position;
	CVec3f crossProduct;
	normal = crossProduct.CrossProduct(&(v1-v0),&(v2-v1));
	if(normal.Size() == 0)return;
	normal.Normalize();
}
void CTriangle::ReplaceVertex(CVertex *vold,CVertex *vnew) {
	assert(vold && vnew);
	assert(vold==vertex[0] || vold==vertex[1] || vold==vertex[2]);
	assert(vnew!=vertex[0] && vnew!=vertex[1] && vnew!=vertex[2]);
	if(vold==vertex[0]){
		vertex[0]=vnew;
	}
	else if(vold==vertex[1]){
		vertex[1]=vnew;
	}
	else {
		assert(vold==vertex[2]);
		vertex[2]=vnew;
	}
	int i;
	vold->face.Remove(this);
	assert(!vnew->face.Contains(this));
	vnew->face.Add(this);
	for(i=0;i<3;i++) {
		vold->RemoveIfNonNeighbor(vertex[i]);
		vertex[i]->RemoveIfNonNeighbor(vold);
	}
	for(i=0;i<3;i++) {
		assert(vertex[i]->face.Contains(this)==1);
		for(int j=0;j<3;j++) if(i!=j) {
			vertex[i]->neighbor.AddUnique(vertex[j]);
		}
	}
	ComputeNormal();
}

CVertex::CVertex(CVec3f v,int _id, List<CVertex*> &verticesList) {
	position =v;
	id=_id;
	verticesList.Add(this);
	vList = &verticesList;
}

CVertex::~CVertex(){
	assert(face.num==0);
	while(neighbor.num) {
		neighbor[0]->neighbor.Remove(this);
		neighbor.Remove(neighbor[0]);
	}
	vList->Remove(this);
}
void CVertex::RemoveIfNonNeighbor(CVertex *n) {
	// removes n from neighbor list if n isn't a neighbor.
	if(!neighbor.Contains(n)) return;
	for(int i=0;i<face.num;i++) {
		if(face[i]->HasVertex(n)) return;
	}
	neighbor.Remove(n);
}


float CLOD::ComputeEdgeCollapseCost(CVertex *u,CVertex *v) {
	// if we collapse edge uv by moving u to v then how 
	// much different will the model change, i.e. how much "error".
	// Texture, vertex normal, and border vertex code was removed
	// to keep this demo as simple as possible.
	// The method of determining cost was designed in order 
	// to exploit small and coplanar regions for
	// effective polygon reduction.
	// Is is possible to add some checks here to see if "folds"
	// would be generated.  i.e. normal of a remaining face gets
	// flipped.  I never seemed to run into this problem and
	// therefore never added code to detect this case.
	int i;
	float edgelength = (v->position - u->position).Size();
	float curvature=0;

	// find the "sides" triangles that are on the edge uv
	List<CTriangle *> sides;
	CFloat index = 0.0;

	for(i=0;i<u->face.num;i++) {
		if(u->face[i]->HasVertex(v)){

			sides.Add(u->face[i]);
		}
	}
	// use the triangle facing most away from the sides 
	// to determine our curvature term
	for(i=0;i<u->face.num;i++) {
		float mincurv=1; // curve for face i and closer side to it
		for(int j=0;j<sides.num;j++) {
			// use dot product of face normals. '^' defined in vector
			CVec3f dot;
			float dotprod = dot.DotProduct(&(u->face[i]->normal), &(sides[j]->normal));

			mincurv = Min(mincurv,(1-dotprod)/2.0f);
		}
		curvature = Max(curvature,mincurv);
	}
	// the more coplanar the lower the curvature term  
	CFloat length;
	if( m_algorithm == eLOD_LENGTH_CURVATURE )
		length = edgelength  * curvature;
	else if( m_algorithm == eLOD_LENGTH )
		length = edgelength;
	return length;
}

CLOD::CLOD()
{

}

CLOD::~CLOD()
{
}

void CLOD::ComputeEdgeCostAtVertex(CVertex *v) {
	// compute the edge collapse cost for all edges that start
	// from vertex v.  Since we are only interested in reducing
	// the object by selecting the min cost edge at each step, we
	// only cache the cost of the least cost edge at this vertex
	// (in member variable collapse) as well as the value of the 
	// cost (in member variable objdist).
	if(v->neighbor.num==0) {
		// v doesn't have neighbors so it costs nothing to collapse
		v->collapse=NULL;
		v->objdist=-0.01f;
		return;
	}
	v->objdist = 1000000;
	v->collapse=NULL;
	// search all neighboring edges for "least cost" edge
	for(int i=0;i<v->neighbor.num;i++) {
		float dist;
		dist = ComputeEdgeCollapseCost(v,v->neighbor[i]);
		if(dist<v->objdist) {
			v->collapse=v->neighbor[i];  // candidate for edge collapse
			v->objdist=dist;             // cost of the collapse
		}
	}
}
void CLOD::ComputeAllEdgeCollapseCosts() {
	// For all the edges, compute the difference it would make
	// to the model if it was collapsed.  The least of these
	// per vertex is cached in each vertex object.
	for(int i=0;i<vertices.num;i++) {
		ComputeEdgeCostAtVertex(vertices[i]);
	}
}

void CLOD::Collapse(CVertex *u,CVertex *v){
	// Collapse the edge uv by moving vertex u onto v
	// Actually remove tris on uv, then update tris that
	// have u to have v, and then remove u.
	if(!v) {
		// u is a vertex all by itself so just delete it
		delete u;
		return;
	}
	int i;
	List<CVertex *>tmp;
	// make tmp a list of all the neighbors of u
	for(i=0;i<u->neighbor.num;i++) {
		tmp.Add(u->neighbor[i]);
	}
	// delete triangles on edge uv:
	for(i=u->face.num-1;i>=0;i--) {
		if(u->face[i]->HasVertex(v)) {
			delete(u->face[i]);
		}
	}
	// update remaining triangles to have v instead of u
	for(i=u->face.num-1;i>=0;i--) {
		u->face[i]->ReplaceVertex(u,v);
	}
	delete u; 
	// recompute the edge collapse costs for neighboring vertices
	for(i=0;i<tmp.num;i++) {
		ComputeEdgeCostAtVertex(tmp[i]);
	}
}

void CLOD::AddVertex(CGeometry* geometry){
	for(CUInt i=0;i<geometry->m_physx_points.size();i++) {
		CVertex *v = new CVertex(*(geometry->m_physx_points[i]),i, vertices);
	}
}
void CLOD::AddFaces(CGeometry* geometry){
	for(CUInt i=0;i<geometry->m_groups.size();i++)
	{
		CTriangles* triangle =  geometry->m_physx_triangles[i];
		for (CUInt a = 0; a < triangle->m_count; a++)
		{
		    CUInt i1 = triangle->m_indexes[a*3];
		    CUInt i2 = triangle->m_indexes[1+ a*3];
		    CUInt i3 = triangle->m_indexes[2+ a*3];
			CTriangle *t=new CTriangle(
				vertices[i1],
				vertices[i2],
				vertices[i3], 
				triangles);
		}
	}
}

CVertex * CLOD::MinimumCostEdge(){
	// Find the edge that when collapsed will affect model the least.
	// This funtion actually returns a CVertex, the second vertex
	// of the edge (collapse candidate) is stored in the vertex data.
	// Serious optimization opportunity here: this function currently
	// does a sequential search through an unsorted list :-(
	// Our algorithm could be O(n*lg(n)) instead of O(n*n)
	CVertex *mn=vertices[0];
	for(int i=0;i<vertices.num;i++) {
		if(vertices[i]->objdist < mn->objdist) {
			mn = vertices[i];
		}
	}
	return mn;
}

void CLOD::ProgressiveMesh(CGeometry* geometry, List<int> &permutation)
{
	AddVertex(geometry);  // put input data into our data structures
	AddFaces(geometry);
	ComputeAllEdgeCollapseCosts(); // cache all edge collapse costs
	permutation.SetSize(vertices.num);  // allocate space
	geometry->m_collapseMap.SetSize(vertices.num);          // allocate space
	// reduce the object down to nothing:
	while(vertices.num > 0) {
		// get the next vertex to collapse
		CVertex *mn = MinimumCostEdge();
		// keep track of this vertex, i.e. the collapse ordering
		permutation[mn->id]=vertices.num-1;
		// keep track of vertex to which we collapse to
		geometry->m_collapseMap[vertices.num-1] = (mn->collapse)?mn->collapse->id:-1;
		// Collapse this edge
		Collapse(mn,mn->collapse);
	}
	// reorder the map list based on the collapse ordering
	for(int i=0;i<geometry->m_collapseMap.num;i++) {
		geometry->m_collapseMap[i] = (geometry->m_collapseMap[i]==-1)?0:permutation[geometry->m_collapseMap[i]];
	}
	// The caller of this function should reorder their vertices
	// according to the returned "permutation".
}

void CLOD::PermuteVertices(CGeometry* geometry, List<int> &permutation) {
	// rearrange the vertex list 
	List<CVec3f> temp_list;
	//List<CVec3f> temp_list_normal;
	//List<CVec2f> temp_list_texCoord0;
	//List<CVec2f> temp_list_texCoord1;
	//List<CVec3f> temp_list_tangent;
	//List<CVec3f> temp_list_bnormal;

	CUInt i;
	assert(permutation.num==geometry->m_physx_points.size());
	for(i=0;i<geometry->m_physx_points.size();i++) {
		temp_list.Add(*(geometry->m_physx_points[i]));
		//temp_list_normal.Add(geometry->m_normals[i]);

		//if( geometry->m_texCoords[0] )
		//	temp_list_texCoord0.Add( geometry->m_texCoords[0][i]);
		//if( geometry->m_texCoords[1] )
		//	temp_list_texCoord1.Add( geometry->m_texCoords[1][i]);

		//if( geometry->m_tangents )
		//	temp_list_tangent.Add(geometry->m_tangents[i]);
		//if( geometry->m_bNormals )
		//	temp_list_bnormal.Add(geometry->m_bNormals[i]);
	}
	for(i=0;i<geometry->m_physx_points.size();i++) {
		*(geometry->m_physx_points[permutation[i]])=temp_list[i];
		//geometry->m_normals[permutation[i]] = temp_list_normal[i];

		//if( geometry->m_texCoords[0] )
		//	geometry->m_texCoords[0][permutation[i]]= temp_list_texCoord0[i];
		//if( geometry->m_texCoords[1] )
		//	geometry->m_texCoords[1][permutation[i]]= temp_list_texCoord1[i];

		//if( geometry->m_tangents )
		//	geometry->m_tangents[permutation[i]] = temp_list_tangent[i];
		//if( geometry->m_bNormals )
		//	geometry->m_bNormals[permutation[i]] = temp_list_bnormal[i];

	}
	// update the changes in the entries in the triangle list
	for(CUInt i=0;i<geometry->m_groups.size();i++)
	{
		CTriangles* triangle =  geometry->m_physx_triangles[i];
		for (CUInt a = 0; a < triangle->m_count; a++)
		{
		    triangle->m_indexes[a*3] = permutation[triangle->m_indexes[a*3] ];
		    triangle->m_indexes[1+ a*3] = permutation[triangle->m_indexes[1+ a*3] ];
		    triangle->m_indexes[2+ a*3] = permutation[triangle->m_indexes[2+ a*3] ];
		}
	}
}
