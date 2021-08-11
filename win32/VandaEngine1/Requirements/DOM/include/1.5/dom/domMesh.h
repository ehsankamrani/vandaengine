#ifndef __domMesh_h__
#define __domMesh_h__

#include <dae/daeDocument.h>
#include <dom/domTypes.h>
#include <dom/domElements.h>

#include <dom/domSource.h>
#include <dom/domVertices.h>
#include <dom/domLines.h>
#include <dom/domLinestrips.h>
#include <dom/domPolygons.h>
#include <dom/domPolylist.h>
#include <dom/domTriangles.h>
#include <dom/domTrifans.h>
#include <dom/domTristrips.h>
#include <dom/domExtra.h>
class DAE;

/**
 * The mesh element contains vertex and primitive information sufficient to
 * describe basic geometric meshes.
 */
class domMesh : public daeElement
{
public:
	virtual COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::MESH; }
	static daeInt ID() { return 336; }
	virtual daeInt typeID() const { return ID(); }

protected:  // Elements
/**
 * The mesh element must contain one or more source elements. @see domSource
 */
	domSource_Array elemSource_array;
/**
 * The mesh element must contain one vertices element. @see domVertices
 */
	domVerticesRef elemVertices;
/**
 * The mesh element may contain any number of lines elements. @see domLines
 */
	domLines_Array elemLines_array;
/**
 * The mesh element may contain any number of linestrips elements. @see domLinestrips
 */
	domLinestrips_Array elemLinestrips_array;
/**
 * The mesh element may contain any number of polygons elements. @see domPolygons
 */
	domPolygons_Array elemPolygons_array;
/**
 * The mesh element may contain any number of polylist elements. @see domPolylist
 */
	domPolylist_Array elemPolylist_array;
/**
 * The mesh element may contain any number of triangles elements. @see domTriangles
 */
	domTriangles_Array elemTriangles_array;
/**
 * The mesh element may contain any number of trifans elements. @see domTrifans
 */
	domTrifans_Array elemTrifans_array;
/**
 * The mesh element may contain any number of tristrips elements. @see domTristrips
 */
	domTristrips_Array elemTristrips_array;
/**
 * The extra element may appear any number of times. @see domExtra
 */
	domExtra_Array elemExtra_array;
	/**
	 * Used to preserve order in elements that do not specify strict sequencing of sub-elements.
	 */
	daeElementRefArray _contents;
	/**
	 * Used to preserve order in elements that have a complex content model.
	 */
	daeUIntArray       _contentsOrder;

	/**
	 * Used to store information needed for some content model objects.
	 */
	daeTArray< daeCharArray * > _CMData;


public:	//Accessors and Mutators
	/**
	 * Gets the source element array.
	 * @return Returns a reference to the array of source elements.
	 */
	domSource_Array &getSource_array() { return elemSource_array; }
	/**
	 * Gets the source element array.
	 * @return Returns a constant reference to the array of source elements.
	 */
	const domSource_Array &getSource_array() const { return elemSource_array; }
	/**
	 * Gets the vertices element.
	 * @return a daeSmartRef to the vertices element.
	 */
	const domVerticesRef getVertices() const { return elemVertices; }
	/**
	 * Gets the lines element array.
	 * @return Returns a reference to the array of lines elements.
	 */
	domLines_Array &getLines_array() { return elemLines_array; }
	/**
	 * Gets the lines element array.
	 * @return Returns a constant reference to the array of lines elements.
	 */
	const domLines_Array &getLines_array() const { return elemLines_array; }
	/**
	 * Gets the linestrips element array.
	 * @return Returns a reference to the array of linestrips elements.
	 */
	domLinestrips_Array &getLinestrips_array() { return elemLinestrips_array; }
	/**
	 * Gets the linestrips element array.
	 * @return Returns a constant reference to the array of linestrips elements.
	 */
	const domLinestrips_Array &getLinestrips_array() const { return elemLinestrips_array; }
	/**
	 * Gets the polygons element array.
	 * @return Returns a reference to the array of polygons elements.
	 */
	domPolygons_Array &getPolygons_array() { return elemPolygons_array; }
	/**
	 * Gets the polygons element array.
	 * @return Returns a constant reference to the array of polygons elements.
	 */
	const domPolygons_Array &getPolygons_array() const { return elemPolygons_array; }
	/**
	 * Gets the polylist element array.
	 * @return Returns a reference to the array of polylist elements.
	 */
	domPolylist_Array &getPolylist_array() { return elemPolylist_array; }
	/**
	 * Gets the polylist element array.
	 * @return Returns a constant reference to the array of polylist elements.
	 */
	const domPolylist_Array &getPolylist_array() const { return elemPolylist_array; }
	/**
	 * Gets the triangles element array.
	 * @return Returns a reference to the array of triangles elements.
	 */
	domTriangles_Array &getTriangles_array() { return elemTriangles_array; }
	/**
	 * Gets the triangles element array.
	 * @return Returns a constant reference to the array of triangles elements.
	 */
	const domTriangles_Array &getTriangles_array() const { return elemTriangles_array; }
	/**
	 * Gets the trifans element array.
	 * @return Returns a reference to the array of trifans elements.
	 */
	domTrifans_Array &getTrifans_array() { return elemTrifans_array; }
	/**
	 * Gets the trifans element array.
	 * @return Returns a constant reference to the array of trifans elements.
	 */
	const domTrifans_Array &getTrifans_array() const { return elemTrifans_array; }
	/**
	 * Gets the tristrips element array.
	 * @return Returns a reference to the array of tristrips elements.
	 */
	domTristrips_Array &getTristrips_array() { return elemTristrips_array; }
	/**
	 * Gets the tristrips element array.
	 * @return Returns a constant reference to the array of tristrips elements.
	 */
	const domTristrips_Array &getTristrips_array() const { return elemTristrips_array; }
	/**
	 * Gets the extra element array.
	 * @return Returns a reference to the array of extra elements.
	 */
	domExtra_Array &getExtra_array() { return elemExtra_array; }
	/**
	 * Gets the extra element array.
	 * @return Returns a constant reference to the array of extra elements.
	 */
	const domExtra_Array &getExtra_array() const { return elemExtra_array; }
	/**
	 * Gets the _contents array.
	 * @return Returns a reference to the _contents element array.
	 */
	daeElementRefArray &getContents() { return _contents; }
	/**
	 * Gets the _contents array.
	 * @return Returns a constant reference to the _contents element array.
	 */
	const daeElementRefArray &getContents() const { return _contents; }

protected:
	/**
	 * Constructor
	 */
	domMesh(DAE& dae) : daeElement(dae), elemSource_array(), elemVertices(), elemLines_array(), elemLinestrips_array(), elemPolygons_array(), elemPolylist_array(), elemTriangles_array(), elemTrifans_array(), elemTristrips_array(), elemExtra_array() {}
	/**
	 * Destructor
	 */
	virtual ~domMesh() { daeElement::deleteCMDataArray(_CMData); }
	/**
	 * Overloaded assignment operator
	 */
	virtual domMesh &operator=( const domMesh &cpy ) { (void)cpy; return *this; }

public: // STATIC METHODS
	/**
	 * Creates an instance of this class and returns a daeElementRef referencing it.
	 * @return a daeElementRef referencing an instance of this object.
	 */
	static DLLSPEC daeElementRef create(DAE& dae);
	/**
	 * Creates a daeMetaElement object that describes this element in the meta object reflection framework.
	 * If a daeMetaElement already exists it will return that instead of creating a new one. 
	 * @return A daeMetaElement describing this COLLADA element.
	 */
	static DLLSPEC daeMetaElement* registerElement(DAE& dae);
};


#endif
