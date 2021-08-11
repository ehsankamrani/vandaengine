#ifndef __domInstance_geometry_h__
#define __domInstance_geometry_h__

#include <dae/daeDocument.h>
#include <dom/domTypes.h>
#include <dom/domElements.h>

#include <dom/domBind_material.h>
#include <dom/domExtra.h>
class DAE;

/**
 * The instance_geometry element declares the instantiation of a COLLADA geometry
 * resource.
 */
class domInstance_geometry : public daeElement
{
public:
	virtual COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::INSTANCE_GEOMETRY; }
	static daeInt ID() { return 110; }
	virtual daeInt typeID() const { return ID(); }
protected:  // Attributes
/**
 *  The url attribute refers to resource.  This may refer to a local resource
 * using a relative URL  fragment identifier that begins with the "#" character.
 * The url attribute may refer to an external  resource using an absolute
 * or relative URL. 
 */
	xsAnyURI attrUrl;
/**
 *  The sid attribute is a text string value containing the sub-identifier
 * of this element. This  value must be unique within the scope of the parent
 * element. Optional attribute. 
 */
	domSid attrSid;
/**
 *  The name attribute is the text string name of this element. Optional attribute.
 */
	xsToken attrName;

protected:  // Elements
/**
 * Bind a specific material to a piece of geometry, binding varying and uniform
 * parameters at the  same time. @see domBind_material
 */
	domBind_materialRef elemBind_material;
/**
 * The extra element may appear any number of times. @see domExtra
 */
	domExtra_Array elemExtra_array;

public:	//Accessors and Mutators
	/**
	 * Gets the url attribute.
	 * @return Returns a xsAnyURI reference of the url attribute.
	 */
	xsAnyURI &getUrl() { return attrUrl; }
	/**
	 * Gets the url attribute.
	 * @return Returns a constant xsAnyURI reference of the url attribute.
	 */
	const xsAnyURI &getUrl() const { return attrUrl; }
	/**
	 * Sets the url attribute.
	 * @param atUrl The new value for the url attribute.
	 */
	void setUrl( const xsAnyURI &atUrl ) { attrUrl = atUrl; }
	/**
	 * Sets the url attribute.
	 * @param atUrl The new value for the url attribute.
	 */
	void setUrl( xsString atUrl ) { attrUrl = atUrl; }

	/**
	 * Gets the sid attribute.
	 * @return Returns a domSid of the sid attribute.
	 */
	domSid getSid() const { return attrSid; }
	/**
	 * Sets the sid attribute.
	 * @param atSid The new value for the sid attribute.
	 */
	void setSid( domSid atSid ) { *(daeStringRef*)&attrSid = atSid;}

	/**
	 * Gets the name attribute.
	 * @return Returns a xsToken of the name attribute.
	 */
	xsToken getName() const { return attrName; }
	/**
	 * Sets the name attribute.
	 * @param atName The new value for the name attribute.
	 */
	void setName( xsToken atName ) { *(daeStringRef*)&attrName = atName;}

	/**
	 * Gets the bind_material element.
	 * @return a daeSmartRef to the bind_material element.
	 */
	const domBind_materialRef getBind_material() const { return elemBind_material; }
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
protected:
	/**
	 * Constructor
	 */
	domInstance_geometry(DAE& dae) : daeElement(dae), attrUrl(dae, *this), attrSid(), attrName(), elemBind_material(), elemExtra_array() {}
	/**
	 * Destructor
	 */
	virtual ~domInstance_geometry() {}
	/**
	 * Overloaded assignment operator
	 */
	virtual domInstance_geometry &operator=( const domInstance_geometry &cpy ) { (void)cpy; return *this; }

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
