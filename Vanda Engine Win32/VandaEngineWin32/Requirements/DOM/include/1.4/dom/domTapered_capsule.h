/*
* Copyright 2006 Sony Computer Entertainment Inc.
*
* Licensed under the MIT Open Source License, for details please see license.txt or the website
* http://www.opensource.org/licenses/mit-license.php
*
*/ 

#ifndef __domTapered_capsule_h__
#define __domTapered_capsule_h__

#include <dae/daeDocument.h>
#include <dom/domTypes.h>
#include <dom/domElements.h>

#include <dom/domExtra.h>
class DAE;

/**
 * A tapered capsule primitive that is centered on, and aligned with, the
 * local Y axis.
 */
class domTapered_capsule : public daeElement
{
public:
	virtual COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::TAPERED_CAPSULE; }
	static daeInt ID() { return 785; }
	virtual daeInt typeID() const { return ID(); }
public:
	class domHeight;

	typedef daeSmartRef<domHeight> domHeightRef;
	typedef daeTArray<domHeightRef> domHeight_Array;

/**
 * A float value that represents the length of the line segment connecting
 * the centers of the  capping hemispheres.
 */
	class domHeight : public daeElement
	{
	public:
		virtual COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::HEIGHT; }
		static daeInt ID() { return 786; }
		virtual daeInt typeID() const { return ID(); }

	protected:  // Value
		/**
		 * The domFloat value of the text data of this element. 
		 */
		domFloat _value;

	public:	//Accessors and Mutators
		/**
		 * Gets the value of this element.
		 * @return a domFloat of the value.
		 */
		domFloat getValue() const { return _value; }
		/**
		 * Sets the _value of this element.
		 * @param val The new value for this element.
		 */
		void setValue( domFloat val ) { _value = val; }

	protected:
		/**
		 * Constructor
		 */
		domHeight(DAE& dae) : daeElement(dae), _value() {}
		/**
		 * Destructor
		 */
		virtual ~domHeight() {}
		/**
		 * Overloaded assignment operator
		 */
		virtual domHeight &operator=( const domHeight &cpy ) { (void)cpy; return *this; }

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

	class domRadius1;

	typedef daeSmartRef<domRadius1> domRadius1Ref;
	typedef daeTArray<domRadius1Ref> domRadius1_Array;

/**
 * Two float values that represent the radii of the tapered capsule at the
 * positive (height/2)  Y value.Both ends of the tapered capsule may be elliptical.
 */
	class domRadius1 : public daeElement
	{
	public:
		virtual COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::RADIUS1; }
		static daeInt ID() { return 787; }
		virtual daeInt typeID() const { return ID(); }

	protected:  // Value
		/**
		 * The domFloat2 value of the text data of this element. 
		 */
		domFloat2 _value;

	public:	//Accessors and Mutators
		/**
		 * Gets the _value array.
		 * @return Returns a domFloat2 reference of the _value array.
		 */
		domFloat2 &getValue() { return _value; }
		/**
		 * Gets the _value array.
		 * @return Returns a constant domFloat2 reference of the _value array.
		 */
		const domFloat2 &getValue() const { return _value; }
		/**
		 * Sets the _value array.
		 * @param val The new value for the _value array.
		 */
		void setValue( const domFloat2 &val ) { _value = val; }

	protected:
		/**
		 * Constructor
		 */
		domRadius1(DAE& dae) : daeElement(dae), _value() {}
		/**
		 * Destructor
		 */
		virtual ~domRadius1() {}
		/**
		 * Overloaded assignment operator
		 */
		virtual domRadius1 &operator=( const domRadius1 &cpy ) { (void)cpy; return *this; }

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

	class domRadius2;

	typedef daeSmartRef<domRadius2> domRadius2Ref;
	typedef daeTArray<domRadius2Ref> domRadius2_Array;

/**
 * Two float values that represent the radii of the tapered capsule at the
 * negative (height/2)  Y value.Both ends of the tapered capsule may be elliptical.
 */
	class domRadius2 : public daeElement
	{
	public:
		virtual COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::RADIUS2; }
		static daeInt ID() { return 788; }
		virtual daeInt typeID() const { return ID(); }

	protected:  // Value
		/**
		 * The domFloat2 value of the text data of this element. 
		 */
		domFloat2 _value;

	public:	//Accessors and Mutators
		/**
		 * Gets the _value array.
		 * @return Returns a domFloat2 reference of the _value array.
		 */
		domFloat2 &getValue() { return _value; }
		/**
		 * Gets the _value array.
		 * @return Returns a constant domFloat2 reference of the _value array.
		 */
		const domFloat2 &getValue() const { return _value; }
		/**
		 * Sets the _value array.
		 * @param val The new value for the _value array.
		 */
		void setValue( const domFloat2 &val ) { _value = val; }

	protected:
		/**
		 * Constructor
		 */
		domRadius2(DAE& dae) : daeElement(dae), _value() {}
		/**
		 * Destructor
		 */
		virtual ~domRadius2() {}
		/**
		 * Overloaded assignment operator
		 */
		virtual domRadius2 &operator=( const domRadius2 &cpy ) { (void)cpy; return *this; }

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



protected:  // Elements
/**
 * A float value that represents the length of the line segment connecting
 * the centers of the  capping hemispheres. @see domHeight
 */
	domHeightRef elemHeight;
/**
 * Two float values that represent the radii of the tapered capsule at the
 * positive (height/2)  Y value.Both ends of the tapered capsule may be elliptical.
 * @see domRadius1
 */
	domRadius1Ref elemRadius1;
/**
 * Two float values that represent the radii of the tapered capsule at the
 * negative (height/2)  Y value.Both ends of the tapered capsule may be elliptical.
 * @see domRadius2
 */
	domRadius2Ref elemRadius2;
/**
 *  The extra element may appear any number of times.  @see domExtra
 */
	domExtra_Array elemExtra_array;

public:	//Accessors and Mutators
	/**
	 * Gets the height element.
	 * @return a daeSmartRef to the height element.
	 */
	const domHeightRef getHeight() const { return elemHeight; }
	/**
	 * Gets the radius1 element.
	 * @return a daeSmartRef to the radius1 element.
	 */
	const domRadius1Ref getRadius1() const { return elemRadius1; }
	/**
	 * Gets the radius2 element.
	 * @return a daeSmartRef to the radius2 element.
	 */
	const domRadius2Ref getRadius2() const { return elemRadius2; }
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
	domTapered_capsule(DAE& dae) : daeElement(dae), elemHeight(), elemRadius1(), elemRadius2(), elemExtra_array() {}
	/**
	 * Destructor
	 */
	virtual ~domTapered_capsule() {}
	/**
	 * Overloaded assignment operator
	 */
	virtual domTapered_capsule &operator=( const domTapered_capsule &cpy ) { (void)cpy; return *this; }

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
