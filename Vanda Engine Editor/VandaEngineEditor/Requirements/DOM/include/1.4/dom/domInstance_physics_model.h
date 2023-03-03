/*
* Copyright 2006 Sony Computer Entertainment Inc.
*
* Licensed under the MIT Open Source License, for details please see license.txt or the website
* http://www.opensource.org/licenses/mit-license.php
*
*/ 

#ifndef __domInstance_physics_model_h__
#define __domInstance_physics_model_h__

#include <dae/daeDocument.h>
#include <dom/domTypes.h>
#include <dom/domElements.h>

#include <dom/domInstance_force_field.h>
#include <dom/domInstance_rigid_body.h>
#include <dom/domInstance_rigid_constraint.h>
#include <dom/domExtra.h>
class DAE;

/**
 * This element allows instancing physics model within another physics model,
 * or in a physics scene.
 */
class domInstance_physics_model : public daeElement
{
public:
	virtual COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::INSTANCE_PHYSICS_MODEL; }
	static daeInt ID() { return 702; }
	virtual daeInt typeID() const { return ID(); }
protected:  // Attributes
/**
 *  The url attribute refers to resource.  This may refer to a local resource
 * using a relative URL  fragment identifier that begins with the “#”
 * character. The url attribute may refer to an external  resource using an
 * absolute or relative URL. 
 */
	xsAnyURI attrUrl;
/**
 *  The sid attribute is a text string value containing the sub-identifier
 * of this element. This  value must be unique within the scope of the parent
 * element. Optional attribute. 
 */
	xsNCName attrSid;
/**
 *  The name attribute is the text string name of this element. Optional attribute.
 */
	xsNCName attrName;
/**
 *  The parent attribute points to the id of a node in the visual scene. This
 * allows a physics model  to be instantiated under a specific transform node,
 * which will dictate the initial position and  orientation, and could be
 * animated to influence kinematic rigid bodies. 
 */
	xsAnyURI attrParent;

protected:  // Elements
/**
 *  The instance_physics_model element may instance any number of force_field
 * elements.  @see domInstance_force_field
 */
	domInstance_force_field_Array elemInstance_force_field_array;
/**
 *  The instance_physics_model element may instance any number of rigid_body
 * elements.  @see domInstance_rigid_body
 */
	domInstance_rigid_body_Array elemInstance_rigid_body_array;
/**
 *  The instance_physics_model element may instance any number of rigid_constraint
 * elements.  @see domInstance_rigid_constraint
 */
	domInstance_rigid_constraint_Array elemInstance_rigid_constraint_array;
/**
 *  The extra element may appear any number of times.  @see domExtra
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
	void setUrl( const xsAnyURI &atUrl ) { attrUrl = atUrl; _validAttributeArray[0] = true; }
	/**
	 * Sets the url attribute.
	 * @param atUrl The new value for the url attribute.
	 */
	void setUrl( xsString atUrl ) { attrUrl = atUrl; _validAttributeArray[0] = true; }

	/**
	 * Gets the sid attribute.
	 * @return Returns a xsNCName of the sid attribute.
	 */
	xsNCName getSid() const { return attrSid; }
	/**
	 * Sets the sid attribute.
	 * @param atSid The new value for the sid attribute.
	 */
	void setSid( xsNCName atSid ) { *(daeStringRef*)&attrSid = atSid; _validAttributeArray[1] = true; }

	/**
	 * Gets the name attribute.
	 * @return Returns a xsNCName of the name attribute.
	 */
	xsNCName getName() const { return attrName; }
	/**
	 * Sets the name attribute.
	 * @param atName The new value for the name attribute.
	 */
	void setName( xsNCName atName ) { *(daeStringRef*)&attrName = atName; _validAttributeArray[2] = true; }

	/**
	 * Gets the parent attribute.
	 * @return Returns a xsAnyURI reference of the parent attribute.
	 */
	xsAnyURI &getParent() { return attrParent; }
	/**
	 * Gets the parent attribute.
	 * @return Returns a constant xsAnyURI reference of the parent attribute.
	 */
	const xsAnyURI &getParent() const { return attrParent; }
	/**
	 * Sets the parent attribute.
	 * @param atParent The new value for the parent attribute.
	 */
	void setParent( const xsAnyURI &atParent ) { attrParent = atParent; _validAttributeArray[3] = true; }
	/**
	 * Sets the parent attribute.
	 * @param atParent The new value for the parent attribute.
	 */
	void setParent( xsString atParent ) { attrParent = atParent; _validAttributeArray[3] = true; }

	/**
	 * Gets the instance_force_field element array.
	 * @return Returns a reference to the array of instance_force_field elements.
	 */
	domInstance_force_field_Array &getInstance_force_field_array() { return elemInstance_force_field_array; }
	/**
	 * Gets the instance_force_field element array.
	 * @return Returns a constant reference to the array of instance_force_field elements.
	 */
	const domInstance_force_field_Array &getInstance_force_field_array() const { return elemInstance_force_field_array; }
	/**
	 * Gets the instance_rigid_body element array.
	 * @return Returns a reference to the array of instance_rigid_body elements.
	 */
	domInstance_rigid_body_Array &getInstance_rigid_body_array() { return elemInstance_rigid_body_array; }
	/**
	 * Gets the instance_rigid_body element array.
	 * @return Returns a constant reference to the array of instance_rigid_body elements.
	 */
	const domInstance_rigid_body_Array &getInstance_rigid_body_array() const { return elemInstance_rigid_body_array; }
	/**
	 * Gets the instance_rigid_constraint element array.
	 * @return Returns a reference to the array of instance_rigid_constraint elements.
	 */
	domInstance_rigid_constraint_Array &getInstance_rigid_constraint_array() { return elemInstance_rigid_constraint_array; }
	/**
	 * Gets the instance_rigid_constraint element array.
	 * @return Returns a constant reference to the array of instance_rigid_constraint elements.
	 */
	const domInstance_rigid_constraint_Array &getInstance_rigid_constraint_array() const { return elemInstance_rigid_constraint_array; }
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
	domInstance_physics_model(DAE& dae) : daeElement(dae), attrUrl(dae, *this), attrSid(), attrName(), attrParent(dae, *this), elemInstance_force_field_array(), elemInstance_rigid_body_array(), elemInstance_rigid_constraint_array(), elemExtra_array() {}
	/**
	 * Destructor
	 */
	virtual ~domInstance_physics_model() {}
	/**
	 * Overloaded assignment operator
	 */
	virtual domInstance_physics_model &operator=( const domInstance_physics_model &cpy ) { (void)cpy; return *this; }

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
