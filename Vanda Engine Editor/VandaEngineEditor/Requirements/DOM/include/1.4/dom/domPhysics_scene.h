/*
* Copyright 2006 Sony Computer Entertainment Inc.
*
* Licensed under the MIT Open Source License, for details please see license.txt or the website
* http://www.opensource.org/licenses/mit-license.php
*
*/ 

#ifndef __domPhysics_scene_h__
#define __domPhysics_scene_h__

#include <dae/daeDocument.h>
#include <dom/domTypes.h>
#include <dom/domElements.h>

#include <dom/domAsset.h>
#include <dom/domInstance_force_field.h>
#include <dom/domInstance_physics_model.h>
#include <dom/domTechnique.h>
#include <dom/domExtra.h>
#include <dom/domTargetableFloat3.h>
#include <dom/domTargetableFloat.h>
class DAE;

class domPhysics_scene : public daeElement
{
public:
	virtual COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::PHYSICS_SCENE; }
	static daeInt ID() { return 793; }
	virtual daeInt typeID() const { return ID(); }
public:
	class domTechnique_common;

	typedef daeSmartRef<domTechnique_common> domTechnique_commonRef;
	typedef daeTArray<domTechnique_commonRef> domTechnique_common_Array;

/**
 * The technique_common element specifies the physics_scene information for
 * the common profile  which all COLLADA implementations need to support.
 */
	class domTechnique_common : public daeElement
	{
	public:
		virtual COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::TECHNIQUE_COMMON; }
		static daeInt ID() { return 794; }
		virtual daeInt typeID() const { return ID(); }

	protected:  // Elements
/**
 * The gravity vector to use for the physics_scene. @see domGravity
 */
		domTargetableFloat3Ref elemGravity;
/**
 * The time_step for the physics_scene. @see domTime_step
 */
		domTargetableFloatRef elemTime_step;

	public:	//Accessors and Mutators
		/**
		 * Gets the gravity element.
		 * @return a daeSmartRef to the gravity element.
		 */
		const domTargetableFloat3Ref getGravity() const { return elemGravity; }
		/**
		 * Gets the time_step element.
		 * @return a daeSmartRef to the time_step element.
		 */
		const domTargetableFloatRef getTime_step() const { return elemTime_step; }
	protected:
		/**
		 * Constructor
		 */
		domTechnique_common(DAE& dae) : daeElement(dae), elemGravity(), elemTime_step() {}
		/**
		 * Destructor
		 */
		virtual ~domTechnique_common() {}
		/**
		 * Overloaded assignment operator
		 */
		virtual domTechnique_common &operator=( const domTechnique_common &cpy ) { (void)cpy; return *this; }

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


protected:  // Attributes
/**
 *  The id attribute is a text string containing the unique identifier of
 * this element.  This value must be unique within the instance document.
 * Optional attribute. 
 */
	xsID attrId;
/**
 *  The name attribute is the text string name of this element. Optional attribute.
 */
	xsNCName attrName;

protected:  // Elements
/**
 *  The physics_scene element may contain an asset element.  @see domAsset
 */
	domAssetRef elemAsset;
/**
 *  There may be any number of instance_force_field elements.  @see domInstance_force_field
 */
	domInstance_force_field_Array elemInstance_force_field_array;
/**
 *  There may be any number of instance_physics_model elements.  @see domInstance_physics_model
 */
	domInstance_physics_model_Array elemInstance_physics_model_array;
/**
 * The technique_common element specifies the physics_scene information for
 * the common profile  which all COLLADA implementations need to support.
 * @see domTechnique_common
 */
	domTechnique_commonRef elemTechnique_common;
/**
 *  This element may contain any number of non-common profile techniques.
 * @see domTechnique
 */
	domTechnique_Array elemTechnique_array;
/**
 *  The extra element may appear any number of times.  @see domExtra
 */
	domExtra_Array elemExtra_array;

public:	//Accessors and Mutators
	/**
	 * Gets the id attribute.
	 * @return Returns a xsID of the id attribute.
	 */
	xsID getId() const { return attrId; }
	/**
	 * Sets the id attribute.
	 * @param atId The new value for the id attribute.
	 */
	void setId( xsID atId ) { *(daeStringRef*)&attrId = atId; _validAttributeArray[0] = true; 
		if( _document != NULL ) _document->changeElementID( this, attrId );
	}

	/**
	 * Gets the name attribute.
	 * @return Returns a xsNCName of the name attribute.
	 */
	xsNCName getName() const { return attrName; }
	/**
	 * Sets the name attribute.
	 * @param atName The new value for the name attribute.
	 */
	void setName( xsNCName atName ) { *(daeStringRef*)&attrName = atName; _validAttributeArray[1] = true; }

	/**
	 * Gets the asset element.
	 * @return a daeSmartRef to the asset element.
	 */
	const domAssetRef getAsset() const { return elemAsset; }
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
	 * Gets the instance_physics_model element array.
	 * @return Returns a reference to the array of instance_physics_model elements.
	 */
	domInstance_physics_model_Array &getInstance_physics_model_array() { return elemInstance_physics_model_array; }
	/**
	 * Gets the instance_physics_model element array.
	 * @return Returns a constant reference to the array of instance_physics_model elements.
	 */
	const domInstance_physics_model_Array &getInstance_physics_model_array() const { return elemInstance_physics_model_array; }
	/**
	 * Gets the technique_common element.
	 * @return a daeSmartRef to the technique_common element.
	 */
	const domTechnique_commonRef getTechnique_common() const { return elemTechnique_common; }
	/**
	 * Gets the technique element array.
	 * @return Returns a reference to the array of technique elements.
	 */
	domTechnique_Array &getTechnique_array() { return elemTechnique_array; }
	/**
	 * Gets the technique element array.
	 * @return Returns a constant reference to the array of technique elements.
	 */
	const domTechnique_Array &getTechnique_array() const { return elemTechnique_array; }
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
	domPhysics_scene(DAE& dae) : daeElement(dae), attrId(), attrName(), elemAsset(), elemInstance_force_field_array(), elemInstance_physics_model_array(), elemTechnique_common(), elemTechnique_array(), elemExtra_array() {}
	/**
	 * Destructor
	 */
	virtual ~domPhysics_scene() {}
	/**
	 * Overloaded assignment operator
	 */
	virtual domPhysics_scene &operator=( const domPhysics_scene &cpy ) { (void)cpy; return *this; }

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
