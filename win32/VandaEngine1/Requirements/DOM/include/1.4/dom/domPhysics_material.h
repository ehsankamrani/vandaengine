/*
* Copyright 2006 Sony Computer Entertainment Inc.
*
* Licensed under the MIT Open Source License, for details please see license.txt or the website
* http://www.opensource.org/licenses/mit-license.php
*
*/ 

#ifndef __domPhysics_material_h__
#define __domPhysics_material_h__

#include <dae/daeDocument.h>
#include <dom/domTypes.h>
#include <dom/domElements.h>

#include <dom/domAsset.h>
#include <dom/domTechnique.h>
#include <dom/domExtra.h>
#include <dom/domTargetableFloat.h>
class DAE;

/**
 * This element defines the physical properties of an object. It contains
 * a technique/profile with  parameters. The COMMON profile defines the built-in
 * names, such as static_friction.
 */
class domPhysics_material : public daeElement
{
public:
	virtual COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::PHYSICS_MATERIAL; }
	static daeInt ID() { return 791; }
	virtual daeInt typeID() const { return ID(); }
public:
	class domTechnique_common;

	typedef daeSmartRef<domTechnique_common> domTechnique_commonRef;
	typedef daeTArray<domTechnique_commonRef> domTechnique_common_Array;

/**
 * The technique_common element specifies the physics_material information
 * for the common profile  which all COLLADA implementations need to support.
 */
	class domTechnique_common : public daeElement
	{
	public:
		virtual COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::TECHNIQUE_COMMON; }
		static daeInt ID() { return 792; }
		virtual daeInt typeID() const { return ID(); }

	protected:  // Elements
/**
 * Dynamic friction coefficient @see domDynamic_friction
 */
		domTargetableFloatRef elemDynamic_friction;
/**
 * The proportion of the kinetic energy preserved in the impact (typically
 * ranges from 0.0 to 1.0) @see domRestitution
 */
		domTargetableFloatRef elemRestitution;
/**
 * Static friction coefficient @see domStatic_friction
 */
		domTargetableFloatRef elemStatic_friction;

	public:	//Accessors and Mutators
		/**
		 * Gets the dynamic_friction element.
		 * @return a daeSmartRef to the dynamic_friction element.
		 */
		const domTargetableFloatRef getDynamic_friction() const { return elemDynamic_friction; }
		/**
		 * Gets the restitution element.
		 * @return a daeSmartRef to the restitution element.
		 */
		const domTargetableFloatRef getRestitution() const { return elemRestitution; }
		/**
		 * Gets the static_friction element.
		 * @return a daeSmartRef to the static_friction element.
		 */
		const domTargetableFloatRef getStatic_friction() const { return elemStatic_friction; }
	protected:
		/**
		 * Constructor
		 */
		domTechnique_common(DAE& dae) : daeElement(dae), elemDynamic_friction(), elemRestitution(), elemStatic_friction() {}
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
 *  The physics_material element may contain an asset element.  @see domAsset
 */
	domAssetRef elemAsset;
/**
 * The technique_common element specifies the physics_material information
 * for the common profile  which all COLLADA implementations need to support.
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
	domPhysics_material(DAE& dae) : daeElement(dae), attrId(), attrName(), elemAsset(), elemTechnique_common(), elemTechnique_array(), elemExtra_array() {}
	/**
	 * Destructor
	 */
	virtual ~domPhysics_material() {}
	/**
	 * Overloaded assignment operator
	 */
	virtual domPhysics_material &operator=( const domPhysics_material &cpy ) { (void)cpy; return *this; }

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
