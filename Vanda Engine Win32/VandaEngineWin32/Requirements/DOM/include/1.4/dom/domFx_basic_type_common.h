/*
* Copyright 2006 Sony Computer Entertainment Inc.
*
* Licensed under the MIT Open Source License, for details please see license.txt or the website
* http://www.opensource.org/licenses/mit-license.php
*
*/ 

#ifndef __domFx_basic_type_common_h__
#define __domFx_basic_type_common_h__

#include <dae/daeDocument.h>
#include <dom/domTypes.h>
#include <dom/domElements.h>

#include <dom/domFx_surface_common.h>
#include <dom/domFx_sampler1D_common.h>
#include <dom/domFx_sampler2D_common.h>
#include <dom/domFx_sampler3D_common.h>
#include <dom/domFx_samplerCUBE_common.h>
#include <dom/domFx_samplerRECT_common.h>
#include <dom/domFx_samplerDEPTH_common.h>
class DAE;

/**
 * A group that specifies the allowable types for effect scoped parameters.
 */
class domFx_basic_type_common : public daeElement
{
public:
	virtual COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::FX_BASIC_TYPE_COMMON; }
	static daeInt ID() { return 188; }
	virtual daeInt typeID() const { return ID(); }
public:
	class domBool;

	typedef daeSmartRef<domBool> domBoolRef;
	typedef daeTArray<domBoolRef> domBool_Array;

	class domBool : public daeElement
	{
	public:
		virtual COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::BOOL; }
		static daeInt ID() { return 189; }
		virtual daeInt typeID() const { return ID(); }

	protected:  // Value
		/**
		 * The ::domBool value of the text data of this element. 
		 */
		::domBool _value;

	public:	//Accessors and Mutators
		/**
		 * Gets the value of this element.
		 * @return a ::domBool of the value.
		 */
		::domBool getValue() const { return _value; }
		/**
		 * Sets the _value of this element.
		 * @param val The new value for this element.
		 */
		void setValue( ::domBool val ) { _value = val; }

	protected:
		/**
		 * Constructor
		 */
		domBool(DAE& dae) : daeElement(dae), _value() {}
		/**
		 * Destructor
		 */
		virtual ~domBool() {}
		/**
		 * Overloaded assignment operator
		 */
		virtual domBool &operator=( const domBool &cpy ) { (void)cpy; return *this; }

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

	class domBool2;

	typedef daeSmartRef<domBool2> domBool2Ref;
	typedef daeTArray<domBool2Ref> domBool2_Array;

	class domBool2 : public daeElement
	{
	public:
		virtual COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::BOOL2; }
		static daeInt ID() { return 190; }
		virtual daeInt typeID() const { return ID(); }

	protected:  // Value
		/**
		 * The ::domBool2 value of the text data of this element. 
		 */
		::domBool2 _value;

	public:	//Accessors and Mutators
		/**
		 * Gets the _value array.
		 * @return Returns a ::domBool2 reference of the _value array.
		 */
		::domBool2 &getValue() { return _value; }
		/**
		 * Gets the _value array.
		 * @return Returns a constant ::domBool2 reference of the _value array.
		 */
		const ::domBool2 &getValue() const { return _value; }
		/**
		 * Sets the _value array.
		 * @param val The new value for the _value array.
		 */
		void setValue( const ::domBool2 &val ) { _value = val; }

	protected:
		/**
		 * Constructor
		 */
		domBool2(DAE& dae) : daeElement(dae), _value() {}
		/**
		 * Destructor
		 */
		virtual ~domBool2() {}
		/**
		 * Overloaded assignment operator
		 */
		virtual domBool2 &operator=( const domBool2 &cpy ) { (void)cpy; return *this; }

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

	class domBool3;

	typedef daeSmartRef<domBool3> domBool3Ref;
	typedef daeTArray<domBool3Ref> domBool3_Array;

	class domBool3 : public daeElement
	{
	public:
		virtual COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::BOOL3; }
		static daeInt ID() { return 191; }
		virtual daeInt typeID() const { return ID(); }

	protected:  // Value
		/**
		 * The ::domBool3 value of the text data of this element. 
		 */
		::domBool3 _value;

	public:	//Accessors and Mutators
		/**
		 * Gets the _value array.
		 * @return Returns a ::domBool3 reference of the _value array.
		 */
		::domBool3 &getValue() { return _value; }
		/**
		 * Gets the _value array.
		 * @return Returns a constant ::domBool3 reference of the _value array.
		 */
		const ::domBool3 &getValue() const { return _value; }
		/**
		 * Sets the _value array.
		 * @param val The new value for the _value array.
		 */
		void setValue( const ::domBool3 &val ) { _value = val; }

	protected:
		/**
		 * Constructor
		 */
		domBool3(DAE& dae) : daeElement(dae), _value() {}
		/**
		 * Destructor
		 */
		virtual ~domBool3() {}
		/**
		 * Overloaded assignment operator
		 */
		virtual domBool3 &operator=( const domBool3 &cpy ) { (void)cpy; return *this; }

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

	class domBool4;

	typedef daeSmartRef<domBool4> domBool4Ref;
	typedef daeTArray<domBool4Ref> domBool4_Array;

	class domBool4 : public daeElement
	{
	public:
		virtual COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::BOOL4; }
		static daeInt ID() { return 192; }
		virtual daeInt typeID() const { return ID(); }

	protected:  // Value
		/**
		 * The ::domBool4 value of the text data of this element. 
		 */
		::domBool4 _value;

	public:	//Accessors and Mutators
		/**
		 * Gets the _value array.
		 * @return Returns a ::domBool4 reference of the _value array.
		 */
		::domBool4 &getValue() { return _value; }
		/**
		 * Gets the _value array.
		 * @return Returns a constant ::domBool4 reference of the _value array.
		 */
		const ::domBool4 &getValue() const { return _value; }
		/**
		 * Sets the _value array.
		 * @param val The new value for the _value array.
		 */
		void setValue( const ::domBool4 &val ) { _value = val; }

	protected:
		/**
		 * Constructor
		 */
		domBool4(DAE& dae) : daeElement(dae), _value() {}
		/**
		 * Destructor
		 */
		virtual ~domBool4() {}
		/**
		 * Overloaded assignment operator
		 */
		virtual domBool4 &operator=( const domBool4 &cpy ) { (void)cpy; return *this; }

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

	class domInt;

	typedef daeSmartRef<domInt> domIntRef;
	typedef daeTArray<domIntRef> domInt_Array;

	class domInt : public daeElement
	{
	public:
		virtual COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::INT; }
		static daeInt ID() { return 193; }
		virtual daeInt typeID() const { return ID(); }

	protected:  // Value
		/**
		 * The ::domInt value of the text data of this element. 
		 */
		::domInt _value;

	public:	//Accessors and Mutators
		/**
		 * Gets the value of this element.
		 * @return a ::domInt of the value.
		 */
		::domInt getValue() const { return _value; }
		/**
		 * Sets the _value of this element.
		 * @param val The new value for this element.
		 */
		void setValue( ::domInt val ) { _value = val; }

	protected:
		/**
		 * Constructor
		 */
		domInt(DAE& dae) : daeElement(dae), _value() {}
		/**
		 * Destructor
		 */
		virtual ~domInt() {}
		/**
		 * Overloaded assignment operator
		 */
		virtual domInt &operator=( const domInt &cpy ) { (void)cpy; return *this; }

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

	class domInt2;

	typedef daeSmartRef<domInt2> domInt2Ref;
	typedef daeTArray<domInt2Ref> domInt2_Array;

	class domInt2 : public daeElement
	{
	public:
		virtual COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::INT2; }
		static daeInt ID() { return 194; }
		virtual daeInt typeID() const { return ID(); }

	protected:  // Value
		/**
		 * The ::domInt2 value of the text data of this element. 
		 */
		::domInt2 _value;

	public:	//Accessors and Mutators
		/**
		 * Gets the _value array.
		 * @return Returns a ::domInt2 reference of the _value array.
		 */
		::domInt2 &getValue() { return _value; }
		/**
		 * Gets the _value array.
		 * @return Returns a constant ::domInt2 reference of the _value array.
		 */
		const ::domInt2 &getValue() const { return _value; }
		/**
		 * Sets the _value array.
		 * @param val The new value for the _value array.
		 */
		void setValue( const ::domInt2 &val ) { _value = val; }

	protected:
		/**
		 * Constructor
		 */
		domInt2(DAE& dae) : daeElement(dae), _value() {}
		/**
		 * Destructor
		 */
		virtual ~domInt2() {}
		/**
		 * Overloaded assignment operator
		 */
		virtual domInt2 &operator=( const domInt2 &cpy ) { (void)cpy; return *this; }

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

	class domInt3;

	typedef daeSmartRef<domInt3> domInt3Ref;
	typedef daeTArray<domInt3Ref> domInt3_Array;

	class domInt3 : public daeElement
	{
	public:
		virtual COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::INT3; }
		static daeInt ID() { return 195; }
		virtual daeInt typeID() const { return ID(); }

	protected:  // Value
		/**
		 * The ::domInt3 value of the text data of this element. 
		 */
		::domInt3 _value;

	public:	//Accessors and Mutators
		/**
		 * Gets the _value array.
		 * @return Returns a ::domInt3 reference of the _value array.
		 */
		::domInt3 &getValue() { return _value; }
		/**
		 * Gets the _value array.
		 * @return Returns a constant ::domInt3 reference of the _value array.
		 */
		const ::domInt3 &getValue() const { return _value; }
		/**
		 * Sets the _value array.
		 * @param val The new value for the _value array.
		 */
		void setValue( const ::domInt3 &val ) { _value = val; }

	protected:
		/**
		 * Constructor
		 */
		domInt3(DAE& dae) : daeElement(dae), _value() {}
		/**
		 * Destructor
		 */
		virtual ~domInt3() {}
		/**
		 * Overloaded assignment operator
		 */
		virtual domInt3 &operator=( const domInt3 &cpy ) { (void)cpy; return *this; }

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

	class domInt4;

	typedef daeSmartRef<domInt4> domInt4Ref;
	typedef daeTArray<domInt4Ref> domInt4_Array;

	class domInt4 : public daeElement
	{
	public:
		virtual COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::INT4; }
		static daeInt ID() { return 196; }
		virtual daeInt typeID() const { return ID(); }

	protected:  // Value
		/**
		 * The ::domInt4 value of the text data of this element. 
		 */
		::domInt4 _value;

	public:	//Accessors and Mutators
		/**
		 * Gets the _value array.
		 * @return Returns a ::domInt4 reference of the _value array.
		 */
		::domInt4 &getValue() { return _value; }
		/**
		 * Gets the _value array.
		 * @return Returns a constant ::domInt4 reference of the _value array.
		 */
		const ::domInt4 &getValue() const { return _value; }
		/**
		 * Sets the _value array.
		 * @param val The new value for the _value array.
		 */
		void setValue( const ::domInt4 &val ) { _value = val; }

	protected:
		/**
		 * Constructor
		 */
		domInt4(DAE& dae) : daeElement(dae), _value() {}
		/**
		 * Destructor
		 */
		virtual ~domInt4() {}
		/**
		 * Overloaded assignment operator
		 */
		virtual domInt4 &operator=( const domInt4 &cpy ) { (void)cpy; return *this; }

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

	class domFloat;

	typedef daeSmartRef<domFloat> domFloatRef;
	typedef daeTArray<domFloatRef> domFloat_Array;

	class domFloat : public daeElement
	{
	public:
		virtual COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::FLOAT; }
		static daeInt ID() { return 197; }
		virtual daeInt typeID() const { return ID(); }

	protected:  // Value
		/**
		 * The ::domFloat value of the text data of this element. 
		 */
		::domFloat _value;

	public:	//Accessors and Mutators
		/**
		 * Gets the value of this element.
		 * @return a ::domFloat of the value.
		 */
		::domFloat getValue() const { return _value; }
		/**
		 * Sets the _value of this element.
		 * @param val The new value for this element.
		 */
		void setValue( ::domFloat val ) { _value = val; }

	protected:
		/**
		 * Constructor
		 */
		domFloat(DAE& dae) : daeElement(dae), _value() {}
		/**
		 * Destructor
		 */
		virtual ~domFloat() {}
		/**
		 * Overloaded assignment operator
		 */
		virtual domFloat &operator=( const domFloat &cpy ) { (void)cpy; return *this; }

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

	class domFloat2;

	typedef daeSmartRef<domFloat2> domFloat2Ref;
	typedef daeTArray<domFloat2Ref> domFloat2_Array;

	class domFloat2 : public daeElement
	{
	public:
		virtual COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::FLOAT2; }
		static daeInt ID() { return 198; }
		virtual daeInt typeID() const { return ID(); }

	protected:  // Value
		/**
		 * The ::domFloat2 value of the text data of this element. 
		 */
		::domFloat2 _value;

	public:	//Accessors and Mutators
		/**
		 * Gets the _value array.
		 * @return Returns a ::domFloat2 reference of the _value array.
		 */
		::domFloat2 &getValue() { return _value; }
		/**
		 * Gets the _value array.
		 * @return Returns a constant ::domFloat2 reference of the _value array.
		 */
		const ::domFloat2 &getValue() const { return _value; }
		/**
		 * Sets the _value array.
		 * @param val The new value for the _value array.
		 */
		void setValue( const ::domFloat2 &val ) { _value = val; }

	protected:
		/**
		 * Constructor
		 */
		domFloat2(DAE& dae) : daeElement(dae), _value() {}
		/**
		 * Destructor
		 */
		virtual ~domFloat2() {}
		/**
		 * Overloaded assignment operator
		 */
		virtual domFloat2 &operator=( const domFloat2 &cpy ) { (void)cpy; return *this; }

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

	class domFloat3;

	typedef daeSmartRef<domFloat3> domFloat3Ref;
	typedef daeTArray<domFloat3Ref> domFloat3_Array;

	class domFloat3 : public daeElement
	{
	public:
		virtual COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::FLOAT3; }
		static daeInt ID() { return 199; }
		virtual daeInt typeID() const { return ID(); }

	protected:  // Value
		/**
		 * The ::domFloat3 value of the text data of this element. 
		 */
		::domFloat3 _value;

	public:	//Accessors and Mutators
		/**
		 * Gets the _value array.
		 * @return Returns a ::domFloat3 reference of the _value array.
		 */
		::domFloat3 &getValue() { return _value; }
		/**
		 * Gets the _value array.
		 * @return Returns a constant ::domFloat3 reference of the _value array.
		 */
		const ::domFloat3 &getValue() const { return _value; }
		/**
		 * Sets the _value array.
		 * @param val The new value for the _value array.
		 */
		void setValue( const ::domFloat3 &val ) { _value = val; }

	protected:
		/**
		 * Constructor
		 */
		domFloat3(DAE& dae) : daeElement(dae), _value() {}
		/**
		 * Destructor
		 */
		virtual ~domFloat3() {}
		/**
		 * Overloaded assignment operator
		 */
		virtual domFloat3 &operator=( const domFloat3 &cpy ) { (void)cpy; return *this; }

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

	class domFloat4;

	typedef daeSmartRef<domFloat4> domFloat4Ref;
	typedef daeTArray<domFloat4Ref> domFloat4_Array;

	class domFloat4 : public daeElement
	{
	public:
		virtual COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::FLOAT4; }
		static daeInt ID() { return 200; }
		virtual daeInt typeID() const { return ID(); }

	protected:  // Value
		/**
		 * The ::domFloat4 value of the text data of this element. 
		 */
		::domFloat4 _value;

	public:	//Accessors and Mutators
		/**
		 * Gets the _value array.
		 * @return Returns a ::domFloat4 reference of the _value array.
		 */
		::domFloat4 &getValue() { return _value; }
		/**
		 * Gets the _value array.
		 * @return Returns a constant ::domFloat4 reference of the _value array.
		 */
		const ::domFloat4 &getValue() const { return _value; }
		/**
		 * Sets the _value array.
		 * @param val The new value for the _value array.
		 */
		void setValue( const ::domFloat4 &val ) { _value = val; }

	protected:
		/**
		 * Constructor
		 */
		domFloat4(DAE& dae) : daeElement(dae), _value() {}
		/**
		 * Destructor
		 */
		virtual ~domFloat4() {}
		/**
		 * Overloaded assignment operator
		 */
		virtual domFloat4 &operator=( const domFloat4 &cpy ) { (void)cpy; return *this; }

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

	class domFloat1x1;

	typedef daeSmartRef<domFloat1x1> domFloat1x1Ref;
	typedef daeTArray<domFloat1x1Ref> domFloat1x1_Array;

	class domFloat1x1 : public daeElement
	{
	public:
		virtual COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::FLOAT1X1; }
		static daeInt ID() { return 201; }
		virtual daeInt typeID() const { return ID(); }

	protected:  // Value
		/**
		 * The ::domFloat value of the text data of this element. 
		 */
		::domFloat _value;

	public:	//Accessors and Mutators
		/**
		 * Gets the value of this element.
		 * @return a ::domFloat of the value.
		 */
		::domFloat getValue() const { return _value; }
		/**
		 * Sets the _value of this element.
		 * @param val The new value for this element.
		 */
		void setValue( ::domFloat val ) { _value = val; }

	protected:
		/**
		 * Constructor
		 */
		domFloat1x1(DAE& dae) : daeElement(dae), _value() {}
		/**
		 * Destructor
		 */
		virtual ~domFloat1x1() {}
		/**
		 * Overloaded assignment operator
		 */
		virtual domFloat1x1 &operator=( const domFloat1x1 &cpy ) { (void)cpy; return *this; }

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

	class domFloat1x2;

	typedef daeSmartRef<domFloat1x2> domFloat1x2Ref;
	typedef daeTArray<domFloat1x2Ref> domFloat1x2_Array;

	class domFloat1x2 : public daeElement
	{
	public:
		virtual COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::FLOAT1X2; }
		static daeInt ID() { return 202; }
		virtual daeInt typeID() const { return ID(); }

	protected:  // Value
		/**
		 * The ::domFloat2 value of the text data of this element. 
		 */
		::domFloat2 _value;

	public:	//Accessors and Mutators
		/**
		 * Gets the _value array.
		 * @return Returns a ::domFloat2 reference of the _value array.
		 */
		::domFloat2 &getValue() { return _value; }
		/**
		 * Gets the _value array.
		 * @return Returns a constant ::domFloat2 reference of the _value array.
		 */
		const ::domFloat2 &getValue() const { return _value; }
		/**
		 * Sets the _value array.
		 * @param val The new value for the _value array.
		 */
		void setValue( const ::domFloat2 &val ) { _value = val; }

	protected:
		/**
		 * Constructor
		 */
		domFloat1x2(DAE& dae) : daeElement(dae), _value() {}
		/**
		 * Destructor
		 */
		virtual ~domFloat1x2() {}
		/**
		 * Overloaded assignment operator
		 */
		virtual domFloat1x2 &operator=( const domFloat1x2 &cpy ) { (void)cpy; return *this; }

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

	class domFloat1x3;

	typedef daeSmartRef<domFloat1x3> domFloat1x3Ref;
	typedef daeTArray<domFloat1x3Ref> domFloat1x3_Array;

	class domFloat1x3 : public daeElement
	{
	public:
		virtual COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::FLOAT1X3; }
		static daeInt ID() { return 203; }
		virtual daeInt typeID() const { return ID(); }

	protected:  // Value
		/**
		 * The ::domFloat3 value of the text data of this element. 
		 */
		::domFloat3 _value;

	public:	//Accessors and Mutators
		/**
		 * Gets the _value array.
		 * @return Returns a ::domFloat3 reference of the _value array.
		 */
		::domFloat3 &getValue() { return _value; }
		/**
		 * Gets the _value array.
		 * @return Returns a constant ::domFloat3 reference of the _value array.
		 */
		const ::domFloat3 &getValue() const { return _value; }
		/**
		 * Sets the _value array.
		 * @param val The new value for the _value array.
		 */
		void setValue( const ::domFloat3 &val ) { _value = val; }

	protected:
		/**
		 * Constructor
		 */
		domFloat1x3(DAE& dae) : daeElement(dae), _value() {}
		/**
		 * Destructor
		 */
		virtual ~domFloat1x3() {}
		/**
		 * Overloaded assignment operator
		 */
		virtual domFloat1x3 &operator=( const domFloat1x3 &cpy ) { (void)cpy; return *this; }

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

	class domFloat1x4;

	typedef daeSmartRef<domFloat1x4> domFloat1x4Ref;
	typedef daeTArray<domFloat1x4Ref> domFloat1x4_Array;

	class domFloat1x4 : public daeElement
	{
	public:
		virtual COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::FLOAT1X4; }
		static daeInt ID() { return 204; }
		virtual daeInt typeID() const { return ID(); }

	protected:  // Value
		/**
		 * The ::domFloat4 value of the text data of this element. 
		 */
		::domFloat4 _value;

	public:	//Accessors and Mutators
		/**
		 * Gets the _value array.
		 * @return Returns a ::domFloat4 reference of the _value array.
		 */
		::domFloat4 &getValue() { return _value; }
		/**
		 * Gets the _value array.
		 * @return Returns a constant ::domFloat4 reference of the _value array.
		 */
		const ::domFloat4 &getValue() const { return _value; }
		/**
		 * Sets the _value array.
		 * @param val The new value for the _value array.
		 */
		void setValue( const ::domFloat4 &val ) { _value = val; }

	protected:
		/**
		 * Constructor
		 */
		domFloat1x4(DAE& dae) : daeElement(dae), _value() {}
		/**
		 * Destructor
		 */
		virtual ~domFloat1x4() {}
		/**
		 * Overloaded assignment operator
		 */
		virtual domFloat1x4 &operator=( const domFloat1x4 &cpy ) { (void)cpy; return *this; }

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

	class domFloat2x1;

	typedef daeSmartRef<domFloat2x1> domFloat2x1Ref;
	typedef daeTArray<domFloat2x1Ref> domFloat2x1_Array;

	class domFloat2x1 : public daeElement
	{
	public:
		virtual COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::FLOAT2X1; }
		static daeInt ID() { return 205; }
		virtual daeInt typeID() const { return ID(); }

	protected:  // Value
		/**
		 * The ::domFloat2 value of the text data of this element. 
		 */
		::domFloat2 _value;

	public:	//Accessors and Mutators
		/**
		 * Gets the _value array.
		 * @return Returns a ::domFloat2 reference of the _value array.
		 */
		::domFloat2 &getValue() { return _value; }
		/**
		 * Gets the _value array.
		 * @return Returns a constant ::domFloat2 reference of the _value array.
		 */
		const ::domFloat2 &getValue() const { return _value; }
		/**
		 * Sets the _value array.
		 * @param val The new value for the _value array.
		 */
		void setValue( const ::domFloat2 &val ) { _value = val; }

	protected:
		/**
		 * Constructor
		 */
		domFloat2x1(DAE& dae) : daeElement(dae), _value() {}
		/**
		 * Destructor
		 */
		virtual ~domFloat2x1() {}
		/**
		 * Overloaded assignment operator
		 */
		virtual domFloat2x1 &operator=( const domFloat2x1 &cpy ) { (void)cpy; return *this; }

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

	class domFloat2x2;

	typedef daeSmartRef<domFloat2x2> domFloat2x2Ref;
	typedef daeTArray<domFloat2x2Ref> domFloat2x2_Array;

	class domFloat2x2 : public daeElement
	{
	public:
		virtual COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::FLOAT2X2; }
		static daeInt ID() { return 206; }
		virtual daeInt typeID() const { return ID(); }

	protected:  // Value
		/**
		 * The ::domFloat2x2 value of the text data of this element. 
		 */
		::domFloat2x2 _value;

	public:	//Accessors and Mutators
		/**
		 * Gets the _value array.
		 * @return Returns a ::domFloat2x2 reference of the _value array.
		 */
		::domFloat2x2 &getValue() { return _value; }
		/**
		 * Gets the _value array.
		 * @return Returns a constant ::domFloat2x2 reference of the _value array.
		 */
		const ::domFloat2x2 &getValue() const { return _value; }
		/**
		 * Sets the _value array.
		 * @param val The new value for the _value array.
		 */
		void setValue( const ::domFloat2x2 &val ) { _value = val; }

	protected:
		/**
		 * Constructor
		 */
		domFloat2x2(DAE& dae) : daeElement(dae), _value() {}
		/**
		 * Destructor
		 */
		virtual ~domFloat2x2() {}
		/**
		 * Overloaded assignment operator
		 */
		virtual domFloat2x2 &operator=( const domFloat2x2 &cpy ) { (void)cpy; return *this; }

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

	class domFloat2x3;

	typedef daeSmartRef<domFloat2x3> domFloat2x3Ref;
	typedef daeTArray<domFloat2x3Ref> domFloat2x3_Array;

	class domFloat2x3 : public daeElement
	{
	public:
		virtual COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::FLOAT2X3; }
		static daeInt ID() { return 207; }
		virtual daeInt typeID() const { return ID(); }

	protected:  // Value
		/**
		 * The ::domFloat2x3 value of the text data of this element. 
		 */
		::domFloat2x3 _value;

	public:	//Accessors and Mutators
		/**
		 * Gets the _value array.
		 * @return Returns a ::domFloat2x3 reference of the _value array.
		 */
		::domFloat2x3 &getValue() { return _value; }
		/**
		 * Gets the _value array.
		 * @return Returns a constant ::domFloat2x3 reference of the _value array.
		 */
		const ::domFloat2x3 &getValue() const { return _value; }
		/**
		 * Sets the _value array.
		 * @param val The new value for the _value array.
		 */
		void setValue( const ::domFloat2x3 &val ) { _value = val; }

	protected:
		/**
		 * Constructor
		 */
		domFloat2x3(DAE& dae) : daeElement(dae), _value() {}
		/**
		 * Destructor
		 */
		virtual ~domFloat2x3() {}
		/**
		 * Overloaded assignment operator
		 */
		virtual domFloat2x3 &operator=( const domFloat2x3 &cpy ) { (void)cpy; return *this; }

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

	class domFloat2x4;

	typedef daeSmartRef<domFloat2x4> domFloat2x4Ref;
	typedef daeTArray<domFloat2x4Ref> domFloat2x4_Array;

	class domFloat2x4 : public daeElement
	{
	public:
		virtual COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::FLOAT2X4; }
		static daeInt ID() { return 208; }
		virtual daeInt typeID() const { return ID(); }

	protected:  // Value
		/**
		 * The ::domFloat2x4 value of the text data of this element. 
		 */
		::domFloat2x4 _value;

	public:	//Accessors and Mutators
		/**
		 * Gets the _value array.
		 * @return Returns a ::domFloat2x4 reference of the _value array.
		 */
		::domFloat2x4 &getValue() { return _value; }
		/**
		 * Gets the _value array.
		 * @return Returns a constant ::domFloat2x4 reference of the _value array.
		 */
		const ::domFloat2x4 &getValue() const { return _value; }
		/**
		 * Sets the _value array.
		 * @param val The new value for the _value array.
		 */
		void setValue( const ::domFloat2x4 &val ) { _value = val; }

	protected:
		/**
		 * Constructor
		 */
		domFloat2x4(DAE& dae) : daeElement(dae), _value() {}
		/**
		 * Destructor
		 */
		virtual ~domFloat2x4() {}
		/**
		 * Overloaded assignment operator
		 */
		virtual domFloat2x4 &operator=( const domFloat2x4 &cpy ) { (void)cpy; return *this; }

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

	class domFloat3x1;

	typedef daeSmartRef<domFloat3x1> domFloat3x1Ref;
	typedef daeTArray<domFloat3x1Ref> domFloat3x1_Array;

	class domFloat3x1 : public daeElement
	{
	public:
		virtual COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::FLOAT3X1; }
		static daeInt ID() { return 209; }
		virtual daeInt typeID() const { return ID(); }

	protected:  // Value
		/**
		 * The ::domFloat3 value of the text data of this element. 
		 */
		::domFloat3 _value;

	public:	//Accessors and Mutators
		/**
		 * Gets the _value array.
		 * @return Returns a ::domFloat3 reference of the _value array.
		 */
		::domFloat3 &getValue() { return _value; }
		/**
		 * Gets the _value array.
		 * @return Returns a constant ::domFloat3 reference of the _value array.
		 */
		const ::domFloat3 &getValue() const { return _value; }
		/**
		 * Sets the _value array.
		 * @param val The new value for the _value array.
		 */
		void setValue( const ::domFloat3 &val ) { _value = val; }

	protected:
		/**
		 * Constructor
		 */
		domFloat3x1(DAE& dae) : daeElement(dae), _value() {}
		/**
		 * Destructor
		 */
		virtual ~domFloat3x1() {}
		/**
		 * Overloaded assignment operator
		 */
		virtual domFloat3x1 &operator=( const domFloat3x1 &cpy ) { (void)cpy; return *this; }

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

	class domFloat3x2;

	typedef daeSmartRef<domFloat3x2> domFloat3x2Ref;
	typedef daeTArray<domFloat3x2Ref> domFloat3x2_Array;

	class domFloat3x2 : public daeElement
	{
	public:
		virtual COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::FLOAT3X2; }
		static daeInt ID() { return 210; }
		virtual daeInt typeID() const { return ID(); }

	protected:  // Value
		/**
		 * The ::domFloat3x2 value of the text data of this element. 
		 */
		::domFloat3x2 _value;

	public:	//Accessors and Mutators
		/**
		 * Gets the _value array.
		 * @return Returns a ::domFloat3x2 reference of the _value array.
		 */
		::domFloat3x2 &getValue() { return _value; }
		/**
		 * Gets the _value array.
		 * @return Returns a constant ::domFloat3x2 reference of the _value array.
		 */
		const ::domFloat3x2 &getValue() const { return _value; }
		/**
		 * Sets the _value array.
		 * @param val The new value for the _value array.
		 */
		void setValue( const ::domFloat3x2 &val ) { _value = val; }

	protected:
		/**
		 * Constructor
		 */
		domFloat3x2(DAE& dae) : daeElement(dae), _value() {}
		/**
		 * Destructor
		 */
		virtual ~domFloat3x2() {}
		/**
		 * Overloaded assignment operator
		 */
		virtual domFloat3x2 &operator=( const domFloat3x2 &cpy ) { (void)cpy; return *this; }

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

	class domFloat3x3;

	typedef daeSmartRef<domFloat3x3> domFloat3x3Ref;
	typedef daeTArray<domFloat3x3Ref> domFloat3x3_Array;

	class domFloat3x3 : public daeElement
	{
	public:
		virtual COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::FLOAT3X3; }
		static daeInt ID() { return 211; }
		virtual daeInt typeID() const { return ID(); }

	protected:  // Value
		/**
		 * The ::domFloat3x3 value of the text data of this element. 
		 */
		::domFloat3x3 _value;

	public:	//Accessors and Mutators
		/**
		 * Gets the _value array.
		 * @return Returns a ::domFloat3x3 reference of the _value array.
		 */
		::domFloat3x3 &getValue() { return _value; }
		/**
		 * Gets the _value array.
		 * @return Returns a constant ::domFloat3x3 reference of the _value array.
		 */
		const ::domFloat3x3 &getValue() const { return _value; }
		/**
		 * Sets the _value array.
		 * @param val The new value for the _value array.
		 */
		void setValue( const ::domFloat3x3 &val ) { _value = val; }

	protected:
		/**
		 * Constructor
		 */
		domFloat3x3(DAE& dae) : daeElement(dae), _value() {}
		/**
		 * Destructor
		 */
		virtual ~domFloat3x3() {}
		/**
		 * Overloaded assignment operator
		 */
		virtual domFloat3x3 &operator=( const domFloat3x3 &cpy ) { (void)cpy; return *this; }

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

	class domFloat3x4;

	typedef daeSmartRef<domFloat3x4> domFloat3x4Ref;
	typedef daeTArray<domFloat3x4Ref> domFloat3x4_Array;

	class domFloat3x4 : public daeElement
	{
	public:
		virtual COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::FLOAT3X4; }
		static daeInt ID() { return 212; }
		virtual daeInt typeID() const { return ID(); }

	protected:  // Value
		/**
		 * The ::domFloat3x4 value of the text data of this element. 
		 */
		::domFloat3x4 _value;

	public:	//Accessors and Mutators
		/**
		 * Gets the _value array.
		 * @return Returns a ::domFloat3x4 reference of the _value array.
		 */
		::domFloat3x4 &getValue() { return _value; }
		/**
		 * Gets the _value array.
		 * @return Returns a constant ::domFloat3x4 reference of the _value array.
		 */
		const ::domFloat3x4 &getValue() const { return _value; }
		/**
		 * Sets the _value array.
		 * @param val The new value for the _value array.
		 */
		void setValue( const ::domFloat3x4 &val ) { _value = val; }

	protected:
		/**
		 * Constructor
		 */
		domFloat3x4(DAE& dae) : daeElement(dae), _value() {}
		/**
		 * Destructor
		 */
		virtual ~domFloat3x4() {}
		/**
		 * Overloaded assignment operator
		 */
		virtual domFloat3x4 &operator=( const domFloat3x4 &cpy ) { (void)cpy; return *this; }

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

	class domFloat4x1;

	typedef daeSmartRef<domFloat4x1> domFloat4x1Ref;
	typedef daeTArray<domFloat4x1Ref> domFloat4x1_Array;

	class domFloat4x1 : public daeElement
	{
	public:
		virtual COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::FLOAT4X1; }
		static daeInt ID() { return 213; }
		virtual daeInt typeID() const { return ID(); }

	protected:  // Value
		/**
		 * The ::domFloat4 value of the text data of this element. 
		 */
		::domFloat4 _value;

	public:	//Accessors and Mutators
		/**
		 * Gets the _value array.
		 * @return Returns a ::domFloat4 reference of the _value array.
		 */
		::domFloat4 &getValue() { return _value; }
		/**
		 * Gets the _value array.
		 * @return Returns a constant ::domFloat4 reference of the _value array.
		 */
		const ::domFloat4 &getValue() const { return _value; }
		/**
		 * Sets the _value array.
		 * @param val The new value for the _value array.
		 */
		void setValue( const ::domFloat4 &val ) { _value = val; }

	protected:
		/**
		 * Constructor
		 */
		domFloat4x1(DAE& dae) : daeElement(dae), _value() {}
		/**
		 * Destructor
		 */
		virtual ~domFloat4x1() {}
		/**
		 * Overloaded assignment operator
		 */
		virtual domFloat4x1 &operator=( const domFloat4x1 &cpy ) { (void)cpy; return *this; }

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

	class domFloat4x2;

	typedef daeSmartRef<domFloat4x2> domFloat4x2Ref;
	typedef daeTArray<domFloat4x2Ref> domFloat4x2_Array;

	class domFloat4x2 : public daeElement
	{
	public:
		virtual COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::FLOAT4X2; }
		static daeInt ID() { return 214; }
		virtual daeInt typeID() const { return ID(); }

	protected:  // Value
		/**
		 * The ::domFloat4x2 value of the text data of this element. 
		 */
		::domFloat4x2 _value;

	public:	//Accessors and Mutators
		/**
		 * Gets the _value array.
		 * @return Returns a ::domFloat4x2 reference of the _value array.
		 */
		::domFloat4x2 &getValue() { return _value; }
		/**
		 * Gets the _value array.
		 * @return Returns a constant ::domFloat4x2 reference of the _value array.
		 */
		const ::domFloat4x2 &getValue() const { return _value; }
		/**
		 * Sets the _value array.
		 * @param val The new value for the _value array.
		 */
		void setValue( const ::domFloat4x2 &val ) { _value = val; }

	protected:
		/**
		 * Constructor
		 */
		domFloat4x2(DAE& dae) : daeElement(dae), _value() {}
		/**
		 * Destructor
		 */
		virtual ~domFloat4x2() {}
		/**
		 * Overloaded assignment operator
		 */
		virtual domFloat4x2 &operator=( const domFloat4x2 &cpy ) { (void)cpy; return *this; }

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

	class domFloat4x3;

	typedef daeSmartRef<domFloat4x3> domFloat4x3Ref;
	typedef daeTArray<domFloat4x3Ref> domFloat4x3_Array;

	class domFloat4x3 : public daeElement
	{
	public:
		virtual COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::FLOAT4X3; }
		static daeInt ID() { return 215; }
		virtual daeInt typeID() const { return ID(); }

	protected:  // Value
		/**
		 * The ::domFloat4x3 value of the text data of this element. 
		 */
		::domFloat4x3 _value;

	public:	//Accessors and Mutators
		/**
		 * Gets the _value array.
		 * @return Returns a ::domFloat4x3 reference of the _value array.
		 */
		::domFloat4x3 &getValue() { return _value; }
		/**
		 * Gets the _value array.
		 * @return Returns a constant ::domFloat4x3 reference of the _value array.
		 */
		const ::domFloat4x3 &getValue() const { return _value; }
		/**
		 * Sets the _value array.
		 * @param val The new value for the _value array.
		 */
		void setValue( const ::domFloat4x3 &val ) { _value = val; }

	protected:
		/**
		 * Constructor
		 */
		domFloat4x3(DAE& dae) : daeElement(dae), _value() {}
		/**
		 * Destructor
		 */
		virtual ~domFloat4x3() {}
		/**
		 * Overloaded assignment operator
		 */
		virtual domFloat4x3 &operator=( const domFloat4x3 &cpy ) { (void)cpy; return *this; }

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

	class domFloat4x4;

	typedef daeSmartRef<domFloat4x4> domFloat4x4Ref;
	typedef daeTArray<domFloat4x4Ref> domFloat4x4_Array;

	class domFloat4x4 : public daeElement
	{
	public:
		virtual COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::FLOAT4X4; }
		static daeInt ID() { return 216; }
		virtual daeInt typeID() const { return ID(); }

	protected:  // Value
		/**
		 * The ::domFloat4x4 value of the text data of this element. 
		 */
		::domFloat4x4 _value;

	public:	//Accessors and Mutators
		/**
		 * Gets the _value array.
		 * @return Returns a ::domFloat4x4 reference of the _value array.
		 */
		::domFloat4x4 &getValue() { return _value; }
		/**
		 * Gets the _value array.
		 * @return Returns a constant ::domFloat4x4 reference of the _value array.
		 */
		const ::domFloat4x4 &getValue() const { return _value; }
		/**
		 * Sets the _value array.
		 * @param val The new value for the _value array.
		 */
		void setValue( const ::domFloat4x4 &val ) { _value = val; }

	protected:
		/**
		 * Constructor
		 */
		domFloat4x4(DAE& dae) : daeElement(dae), _value() {}
		/**
		 * Destructor
		 */
		virtual ~domFloat4x4() {}
		/**
		 * Overloaded assignment operator
		 */
		virtual domFloat4x4 &operator=( const domFloat4x4 &cpy ) { (void)cpy; return *this; }

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

	class domEnum;

	typedef daeSmartRef<domEnum> domEnumRef;
	typedef daeTArray<domEnumRef> domEnum_Array;

	class domEnum : public daeElement
	{
	public:
		virtual COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::ENUM; }
		static daeInt ID() { return 217; }
		virtual daeInt typeID() const { return ID(); }

	protected:  // Value
		/**
		 * The xsString value of the text data of this element. 
		 */
		xsString _value;

	public:	//Accessors and Mutators
		/**
		 * Gets the value of this element.
		 * @return Returns a xsString of the value.
		 */
		xsString getValue() const { return _value; }
		/**
		 * Sets the _value of this element.
		 * @param val The new value for this element.
		 */
		void setValue( xsString val ) { *(daeStringRef*)&_value = val; }

	protected:
		/**
		 * Constructor
		 */
		domEnum(DAE& dae) : daeElement(dae), _value() {}
		/**
		 * Destructor
		 */
		virtual ~domEnum() {}
		/**
		 * Overloaded assignment operator
		 */
		virtual domEnum &operator=( const domEnum &cpy ) { (void)cpy; return *this; }

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
	domBoolRef elemBool;
	domBool2Ref elemBool2;
	domBool3Ref elemBool3;
	domBool4Ref elemBool4;
	domIntRef elemInt;
	domInt2Ref elemInt2;
	domInt3Ref elemInt3;
	domInt4Ref elemInt4;
	domFloatRef elemFloat;
	domFloat2Ref elemFloat2;
	domFloat3Ref elemFloat3;
	domFloat4Ref elemFloat4;
	domFloat1x1Ref elemFloat1x1;
	domFloat1x2Ref elemFloat1x2;
	domFloat1x3Ref elemFloat1x3;
	domFloat1x4Ref elemFloat1x4;
	domFloat2x1Ref elemFloat2x1;
	domFloat2x2Ref elemFloat2x2;
	domFloat2x3Ref elemFloat2x3;
	domFloat2x4Ref elemFloat2x4;
	domFloat3x1Ref elemFloat3x1;
	domFloat3x2Ref elemFloat3x2;
	domFloat3x3Ref elemFloat3x3;
	domFloat3x4Ref elemFloat3x4;
	domFloat4x1Ref elemFloat4x1;
	domFloat4x2Ref elemFloat4x2;
	domFloat4x3Ref elemFloat4x3;
	domFloat4x4Ref elemFloat4x4;
	domFx_surface_commonRef elemSurface;
	domFx_sampler1D_commonRef elemSampler1D;
	domFx_sampler2D_commonRef elemSampler2D;
	domFx_sampler3D_commonRef elemSampler3D;
	domFx_samplerCUBE_commonRef elemSamplerCUBE;
	domFx_samplerRECT_commonRef elemSamplerRECT;
	domFx_samplerDEPTH_commonRef elemSamplerDEPTH;
	domEnumRef elemEnum;
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
	 * Gets the bool element.
	 * @return a daeSmartRef to the bool element.
	 */
	const domBoolRef getBool() const { return elemBool; }
	/**
	 * Gets the bool2 element.
	 * @return a daeSmartRef to the bool2 element.
	 */
	const domBool2Ref getBool2() const { return elemBool2; }
	/**
	 * Gets the bool3 element.
	 * @return a daeSmartRef to the bool3 element.
	 */
	const domBool3Ref getBool3() const { return elemBool3; }
	/**
	 * Gets the bool4 element.
	 * @return a daeSmartRef to the bool4 element.
	 */
	const domBool4Ref getBool4() const { return elemBool4; }
	/**
	 * Gets the int element.
	 * @return a daeSmartRef to the int element.
	 */
	const domIntRef getInt() const { return elemInt; }
	/**
	 * Gets the int2 element.
	 * @return a daeSmartRef to the int2 element.
	 */
	const domInt2Ref getInt2() const { return elemInt2; }
	/**
	 * Gets the int3 element.
	 * @return a daeSmartRef to the int3 element.
	 */
	const domInt3Ref getInt3() const { return elemInt3; }
	/**
	 * Gets the int4 element.
	 * @return a daeSmartRef to the int4 element.
	 */
	const domInt4Ref getInt4() const { return elemInt4; }
	/**
	 * Gets the float element.
	 * @return a daeSmartRef to the float element.
	 */
	const domFloatRef getFloat() const { return elemFloat; }
	/**
	 * Gets the float2 element.
	 * @return a daeSmartRef to the float2 element.
	 */
	const domFloat2Ref getFloat2() const { return elemFloat2; }
	/**
	 * Gets the float3 element.
	 * @return a daeSmartRef to the float3 element.
	 */
	const domFloat3Ref getFloat3() const { return elemFloat3; }
	/**
	 * Gets the float4 element.
	 * @return a daeSmartRef to the float4 element.
	 */
	const domFloat4Ref getFloat4() const { return elemFloat4; }
	/**
	 * Gets the float1x1 element.
	 * @return a daeSmartRef to the float1x1 element.
	 */
	const domFloat1x1Ref getFloat1x1() const { return elemFloat1x1; }
	/**
	 * Gets the float1x2 element.
	 * @return a daeSmartRef to the float1x2 element.
	 */
	const domFloat1x2Ref getFloat1x2() const { return elemFloat1x2; }
	/**
	 * Gets the float1x3 element.
	 * @return a daeSmartRef to the float1x3 element.
	 */
	const domFloat1x3Ref getFloat1x3() const { return elemFloat1x3; }
	/**
	 * Gets the float1x4 element.
	 * @return a daeSmartRef to the float1x4 element.
	 */
	const domFloat1x4Ref getFloat1x4() const { return elemFloat1x4; }
	/**
	 * Gets the float2x1 element.
	 * @return a daeSmartRef to the float2x1 element.
	 */
	const domFloat2x1Ref getFloat2x1() const { return elemFloat2x1; }
	/**
	 * Gets the float2x2 element.
	 * @return a daeSmartRef to the float2x2 element.
	 */
	const domFloat2x2Ref getFloat2x2() const { return elemFloat2x2; }
	/**
	 * Gets the float2x3 element.
	 * @return a daeSmartRef to the float2x3 element.
	 */
	const domFloat2x3Ref getFloat2x3() const { return elemFloat2x3; }
	/**
	 * Gets the float2x4 element.
	 * @return a daeSmartRef to the float2x4 element.
	 */
	const domFloat2x4Ref getFloat2x4() const { return elemFloat2x4; }
	/**
	 * Gets the float3x1 element.
	 * @return a daeSmartRef to the float3x1 element.
	 */
	const domFloat3x1Ref getFloat3x1() const { return elemFloat3x1; }
	/**
	 * Gets the float3x2 element.
	 * @return a daeSmartRef to the float3x2 element.
	 */
	const domFloat3x2Ref getFloat3x2() const { return elemFloat3x2; }
	/**
	 * Gets the float3x3 element.
	 * @return a daeSmartRef to the float3x3 element.
	 */
	const domFloat3x3Ref getFloat3x3() const { return elemFloat3x3; }
	/**
	 * Gets the float3x4 element.
	 * @return a daeSmartRef to the float3x4 element.
	 */
	const domFloat3x4Ref getFloat3x4() const { return elemFloat3x4; }
	/**
	 * Gets the float4x1 element.
	 * @return a daeSmartRef to the float4x1 element.
	 */
	const domFloat4x1Ref getFloat4x1() const { return elemFloat4x1; }
	/**
	 * Gets the float4x2 element.
	 * @return a daeSmartRef to the float4x2 element.
	 */
	const domFloat4x2Ref getFloat4x2() const { return elemFloat4x2; }
	/**
	 * Gets the float4x3 element.
	 * @return a daeSmartRef to the float4x3 element.
	 */
	const domFloat4x3Ref getFloat4x3() const { return elemFloat4x3; }
	/**
	 * Gets the float4x4 element.
	 * @return a daeSmartRef to the float4x4 element.
	 */
	const domFloat4x4Ref getFloat4x4() const { return elemFloat4x4; }
	/**
	 * Gets the surface element.
	 * @return a daeSmartRef to the surface element.
	 */
	const domFx_surface_commonRef getSurface() const { return elemSurface; }
	/**
	 * Gets the sampler1D element.
	 * @return a daeSmartRef to the sampler1D element.
	 */
	const domFx_sampler1D_commonRef getSampler1D() const { return elemSampler1D; }
	/**
	 * Gets the sampler2D element.
	 * @return a daeSmartRef to the sampler2D element.
	 */
	const domFx_sampler2D_commonRef getSampler2D() const { return elemSampler2D; }
	/**
	 * Gets the sampler3D element.
	 * @return a daeSmartRef to the sampler3D element.
	 */
	const domFx_sampler3D_commonRef getSampler3D() const { return elemSampler3D; }
	/**
	 * Gets the samplerCUBE element.
	 * @return a daeSmartRef to the samplerCUBE element.
	 */
	const domFx_samplerCUBE_commonRef getSamplerCUBE() const { return elemSamplerCUBE; }
	/**
	 * Gets the samplerRECT element.
	 * @return a daeSmartRef to the samplerRECT element.
	 */
	const domFx_samplerRECT_commonRef getSamplerRECT() const { return elemSamplerRECT; }
	/**
	 * Gets the samplerDEPTH element.
	 * @return a daeSmartRef to the samplerDEPTH element.
	 */
	const domFx_samplerDEPTH_commonRef getSamplerDEPTH() const { return elemSamplerDEPTH; }
	/**
	 * Gets the enum element.
	 * @return a daeSmartRef to the enum element.
	 */
	const domEnumRef getEnum() const { return elemEnum; }
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
	domFx_basic_type_common(DAE& dae) : daeElement(dae), elemBool(), elemBool2(), elemBool3(), elemBool4(), elemInt(), elemInt2(), elemInt3(), elemInt4(), elemFloat(), elemFloat2(), elemFloat3(), elemFloat4(), elemFloat1x1(), elemFloat1x2(), elemFloat1x3(), elemFloat1x4(), elemFloat2x1(), elemFloat2x2(), elemFloat2x3(), elemFloat2x4(), elemFloat3x1(), elemFloat3x2(), elemFloat3x3(), elemFloat3x4(), elemFloat4x1(), elemFloat4x2(), elemFloat4x3(), elemFloat4x4(), elemSurface(), elemSampler1D(), elemSampler2D(), elemSampler3D(), elemSamplerCUBE(), elemSamplerRECT(), elemSamplerDEPTH(), elemEnum() {}
	/**
	 * Destructor
	 */
	virtual ~domFx_basic_type_common() { daeElement::deleteCMDataArray(_CMData); }
	/**
	 * Overloaded assignment operator
	 */
	virtual domFx_basic_type_common &operator=( const domFx_basic_type_common &cpy ) { (void)cpy; return *this; }

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
