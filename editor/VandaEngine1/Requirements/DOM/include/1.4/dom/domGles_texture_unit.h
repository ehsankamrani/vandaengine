/*
* Copyright 2006 Sony Computer Entertainment Inc.
*
* Licensed under the MIT Open Source License, for details please see license.txt or the website
* http://www.opensource.org/licenses/mit-license.php
*
*/ 

#ifndef __domGles_texture_unit_h__
#define __domGles_texture_unit_h__

#include <dae/daeDocument.h>
#include <dom/domTypes.h>
#include <dom/domElements.h>

#include <dom/domExtra.h>
class DAE;

class domGles_texture_unit_complexType 
{
public:
	class domSurface;

	typedef daeSmartRef<domSurface> domSurfaceRef;
	typedef daeTArray<domSurfaceRef> domSurface_Array;

	class domSurface : public daeElement
	{
	public:
		virtual COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::SURFACE; }
		static daeInt ID() { return 153; }
		virtual daeInt typeID() const { return ID(); }

	protected:  // Value
		/**
		 * The xsNCName value of the text data of this element. 
		 */
		xsNCName _value;

	public:	//Accessors and Mutators
		/**
		 * Gets the value of this element.
		 * @return Returns a xsNCName of the value.
		 */
		xsNCName getValue() const { return _value; }
		/**
		 * Sets the _value of this element.
		 * @param val The new value for this element.
		 */
		void setValue( xsNCName val ) { *(daeStringRef*)&_value = val; }

	protected:
		/**
		 * Constructor
		 */
		domSurface(DAE& dae) : daeElement(dae), _value() {}
		/**
		 * Destructor
		 */
		virtual ~domSurface() {}
		/**
		 * Overloaded assignment operator
		 */
		virtual domSurface &operator=( const domSurface &cpy ) { (void)cpy; return *this; }

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

	class domSampler_state;

	typedef daeSmartRef<domSampler_state> domSampler_stateRef;
	typedef daeTArray<domSampler_stateRef> domSampler_state_Array;

	class domSampler_state : public daeElement
	{
	public:
		virtual COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::SAMPLER_STATE; }
		static daeInt ID() { return 154; }
		virtual daeInt typeID() const { return ID(); }

	protected:  // Value
		/**
		 * The xsNCName value of the text data of this element. 
		 */
		xsNCName _value;

	public:	//Accessors and Mutators
		/**
		 * Gets the value of this element.
		 * @return Returns a xsNCName of the value.
		 */
		xsNCName getValue() const { return _value; }
		/**
		 * Sets the _value of this element.
		 * @param val The new value for this element.
		 */
		void setValue( xsNCName val ) { *(daeStringRef*)&_value = val; }

	protected:
		/**
		 * Constructor
		 */
		domSampler_state(DAE& dae) : daeElement(dae), _value() {}
		/**
		 * Destructor
		 */
		virtual ~domSampler_state() {}
		/**
		 * Overloaded assignment operator
		 */
		virtual domSampler_state &operator=( const domSampler_state &cpy ) { (void)cpy; return *this; }

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

	class domTexcoord;

	typedef daeSmartRef<domTexcoord> domTexcoordRef;
	typedef daeTArray<domTexcoordRef> domTexcoord_Array;

	class domTexcoord : public daeElement
	{
	public:
		virtual COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::TEXCOORD; }
		static daeInt ID() { return 155; }
		virtual daeInt typeID() const { return ID(); }
	protected:  // Attribute
		xsNCName attrSemantic;


	public:	//Accessors and Mutators
		/**
		 * Gets the semantic attribute.
		 * @return Returns a xsNCName of the semantic attribute.
		 */
		xsNCName getSemantic() const { return attrSemantic; }
		/**
		 * Sets the semantic attribute.
		 * @param atSemantic The new value for the semantic attribute.
		 */
		void setSemantic( xsNCName atSemantic ) { *(daeStringRef*)&attrSemantic = atSemantic; _validAttributeArray[0] = true; }

	protected:
		/**
		 * Constructor
		 */
		domTexcoord(DAE& dae) : daeElement(dae), attrSemantic() {}
		/**
		 * Destructor
		 */
		virtual ~domTexcoord() {}
		/**
		 * Overloaded assignment operator
		 */
		virtual domTexcoord &operator=( const domTexcoord &cpy ) { (void)cpy; return *this; }

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


protected:  // Attribute
/**
 *  The sid attribute is a text string value containing the sub-identifier
 * of this element.  This value must be unique within the scope of the parent
 * element. Optional attribute. 
 */
	xsNCName attrSid;

protected:  // Elements
	domSurfaceRef elemSurface;
	domSampler_stateRef elemSampler_state;
	domTexcoordRef elemTexcoord;
	domExtra_Array elemExtra_array;

public:	//Accessors and Mutators
	/**
	 * Gets the sid attribute.
	 * @return Returns a xsNCName of the sid attribute.
	 */
	xsNCName getSid() const { return attrSid; }
	/**
	 * Sets the sid attribute.
	 * @param atSid The new value for the sid attribute.
	 */
	void setSid( xsNCName atSid ) { *(daeStringRef*)&attrSid = atSid;}

	/**
	 * Gets the surface element.
	 * @return a daeSmartRef to the surface element.
	 */
	const domSurfaceRef getSurface() const { return elemSurface; }
	/**
	 * Gets the sampler_state element.
	 * @return a daeSmartRef to the sampler_state element.
	 */
	const domSampler_stateRef getSampler_state() const { return elemSampler_state; }
	/**
	 * Gets the texcoord element.
	 * @return a daeSmartRef to the texcoord element.
	 */
	const domTexcoordRef getTexcoord() const { return elemTexcoord; }
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
	domGles_texture_unit_complexType(DAE& dae, daeElement* elt) : attrSid(), elemSurface(), elemSampler_state(), elemTexcoord(), elemExtra_array() {}
	/**
	 * Destructor
	 */
	virtual ~domGles_texture_unit_complexType() {}
	/**
	 * Overloaded assignment operator
	 */
	virtual domGles_texture_unit_complexType &operator=( const domGles_texture_unit_complexType &cpy ) { (void)cpy; return *this; }
};

/**
 * An element of type domGles_texture_unit_complexType.
 */
class domGles_texture_unit : public daeElement, public domGles_texture_unit_complexType
{
public:
	virtual COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::GLES_TEXTURE_UNIT; }
	static daeInt ID() { return 156; }
	virtual daeInt typeID() const { return ID(); }

public:	//Accessors and Mutators
	/**
	 * Gets the sid attribute.
	 * @return Returns a xsNCName of the sid attribute.
	 */
	xsNCName getSid() const { return attrSid; }
	/**
	 * Sets the sid attribute.
	 * @param atSid The new value for the sid attribute.
	 */
	void setSid( xsNCName atSid ) { *(daeStringRef*)&attrSid = atSid; _validAttributeArray[0] = true; }

protected:
	/**
	 * Constructor
	 */
	domGles_texture_unit(DAE& dae) : daeElement(dae), domGles_texture_unit_complexType(dae, this) {}
	/**
	 * Destructor
	 */
	virtual ~domGles_texture_unit() {}
	/**
	 * Overloaded assignment operator
	 */
	virtual domGles_texture_unit &operator=( const domGles_texture_unit &cpy ) { (void)cpy; return *this; }

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
