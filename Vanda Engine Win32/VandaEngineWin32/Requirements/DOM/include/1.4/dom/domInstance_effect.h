/*
* Copyright 2006 Sony Computer Entertainment Inc.
*
* Licensed under the MIT Open Source License, for details please see license.txt or the website
* http://www.opensource.org/licenses/mit-license.php
*
*/ 

#ifndef __domInstance_effect_h__
#define __domInstance_effect_h__

#include <dae/daeDocument.h>
#include <dom/domTypes.h>
#include <dom/domElements.h>

#include <dom/domExtra.h>
#include <dom/domFx_basic_type_common.h>
class DAE;

/**
 * The instance_effect element declares the instantiation of a COLLADA effect
 * resource.
 */
class domInstance_effect : public daeElement
{
public:
	virtual COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::INSTANCE_EFFECT; }
	static daeInt ID() { return 691; }
	virtual daeInt typeID() const { return ID(); }
public:
	class domTechnique_hint;

	typedef daeSmartRef<domTechnique_hint> domTechnique_hintRef;
	typedef daeTArray<domTechnique_hintRef> domTechnique_hint_Array;

/**
 * Add a hint for a platform of which technique to use in this effect.
 */
	class domTechnique_hint : public daeElement
	{
	public:
		virtual COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::TECHNIQUE_HINT; }
		static daeInt ID() { return 692; }
		virtual daeInt typeID() const { return ID(); }
	protected:  // Attributes
/**
 *  A platform defines a string that specifies which platform this is hint
 * is aimed for. 
 */
		xsNCName attrPlatform;
/**
 *  A profile defines a string that specifies which API profile this is hint
 * is aimed for. 
 */
		xsNCName attrProfile;
/**
 *  A reference to the technique to use for the specified platform. 
 */
		xsNCName attrRef;


	public:	//Accessors and Mutators
		/**
		 * Gets the platform attribute.
		 * @return Returns a xsNCName of the platform attribute.
		 */
		xsNCName getPlatform() const { return attrPlatform; }
		/**
		 * Sets the platform attribute.
		 * @param atPlatform The new value for the platform attribute.
		 */
		void setPlatform( xsNCName atPlatform ) { *(daeStringRef*)&attrPlatform = atPlatform; _validAttributeArray[0] = true; }

		/**
		 * Gets the profile attribute.
		 * @return Returns a xsNCName of the profile attribute.
		 */
		xsNCName getProfile() const { return attrProfile; }
		/**
		 * Sets the profile attribute.
		 * @param atProfile The new value for the profile attribute.
		 */
		void setProfile( xsNCName atProfile ) { *(daeStringRef*)&attrProfile = atProfile; _validAttributeArray[1] = true; }

		/**
		 * Gets the ref attribute.
		 * @return Returns a xsNCName of the ref attribute.
		 */
		xsNCName getRef() const { return attrRef; }
		/**
		 * Sets the ref attribute.
		 * @param atRef The new value for the ref attribute.
		 */
		void setRef( xsNCName atRef ) { *(daeStringRef*)&attrRef = atRef; _validAttributeArray[2] = true; }

	protected:
		/**
		 * Constructor
		 */
		domTechnique_hint(DAE& dae) : daeElement(dae), attrPlatform(), attrProfile(), attrRef() {}
		/**
		 * Destructor
		 */
		virtual ~domTechnique_hint() {}
		/**
		 * Overloaded assignment operator
		 */
		virtual domTechnique_hint &operator=( const domTechnique_hint &cpy ) { (void)cpy; return *this; }

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

	class domSetparam;

	typedef daeSmartRef<domSetparam> domSetparamRef;
	typedef daeTArray<domSetparamRef> domSetparam_Array;

/**
 * Assigns a new value to a previously defined parameter
 */
	class domSetparam : public daeElement
	{
	public:
		virtual COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::SETPARAM; }
		static daeInt ID() { return 693; }
		virtual daeInt typeID() const { return ID(); }
	protected:  // Attribute
		xsToken attrRef;

	protected:  // Element
		domFx_basic_type_commonRef elemFx_basic_type_common;

	public:	//Accessors and Mutators
		/**
		 * Gets the ref attribute.
		 * @return Returns a xsToken of the ref attribute.
		 */
		xsToken getRef() const { return attrRef; }
		/**
		 * Sets the ref attribute.
		 * @param atRef The new value for the ref attribute.
		 */
		void setRef( xsToken atRef ) { *(daeStringRef*)&attrRef = atRef; _validAttributeArray[0] = true; }

		/**
		 * Gets the fx_basic_type_common element.
		 * @return a daeSmartRef to the fx_basic_type_common element.
		 */
		const domFx_basic_type_commonRef getFx_basic_type_common() const { return elemFx_basic_type_common; }
	protected:
		/**
		 * Constructor
		 */
		domSetparam(DAE& dae) : daeElement(dae), attrRef(), elemFx_basic_type_common() {}
		/**
		 * Destructor
		 */
		virtual ~domSetparam() {}
		/**
		 * Overloaded assignment operator
		 */
		virtual domSetparam &operator=( const domSetparam &cpy ) { (void)cpy; return *this; }

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

protected:  // Elements
/**
 * Add a hint for a platform of which technique to use in this effect. @see
 * domTechnique_hint
 */
	domTechnique_hint_Array elemTechnique_hint_array;
/**
 * Assigns a new value to a previously defined parameter @see domSetparam
 */
	domSetparam_Array elemSetparam_array;
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
	 * Gets the technique_hint element array.
	 * @return Returns a reference to the array of technique_hint elements.
	 */
	domTechnique_hint_Array &getTechnique_hint_array() { return elemTechnique_hint_array; }
	/**
	 * Gets the technique_hint element array.
	 * @return Returns a constant reference to the array of technique_hint elements.
	 */
	const domTechnique_hint_Array &getTechnique_hint_array() const { return elemTechnique_hint_array; }
	/**
	 * Gets the setparam element array.
	 * @return Returns a reference to the array of setparam elements.
	 */
	domSetparam_Array &getSetparam_array() { return elemSetparam_array; }
	/**
	 * Gets the setparam element array.
	 * @return Returns a constant reference to the array of setparam elements.
	 */
	const domSetparam_Array &getSetparam_array() const { return elemSetparam_array; }
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
	domInstance_effect(DAE& dae) : daeElement(dae), attrUrl(dae, *this), attrSid(), attrName(), elemTechnique_hint_array(), elemSetparam_array(), elemExtra_array() {}
	/**
	 * Destructor
	 */
	virtual ~domInstance_effect() {}
	/**
	 * Overloaded assignment operator
	 */
	virtual domInstance_effect &operator=( const domInstance_effect &cpy ) { (void)cpy; return *this; }

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
