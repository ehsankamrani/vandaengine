/*
* Copyright 2006 Sony Computer Entertainment Inc.
*
* Licensed under the MIT Open Source License, for details please see license.txt or the website
* http://www.opensource.org/licenses/mit-license.php
*
*/ 

#ifndef __domGlsl_param_type_h__
#define __domGlsl_param_type_h__

#include <dae/daeDocument.h>
#include <dom/domTypes.h>
#include <dom/domElements.h>

#include <dom/domGlsl_surface_type.h>
#include <dom/domGl_sampler1D.h>
#include <dom/domGl_sampler2D.h>
#include <dom/domGl_sampler3D.h>
#include <dom/domGl_samplerCUBE.h>
#include <dom/domGl_samplerRECT.h>
#include <dom/domGl_samplerDEPTH.h>
class DAE;

/**
 * A group that specifies the allowable types for GLSL profile parameters.
 */
class domGlsl_param_type : public daeElement
{
public:
	virtual COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::GLSL_PARAM_TYPE; }
	static daeInt ID() { return 363; }
	virtual daeInt typeID() const { return ID(); }
public:
	class domBool;

	typedef daeSmartRef<domBool> domBoolRef;
	typedef daeTArray<domBoolRef> domBool_Array;

	class domBool : public daeElement
	{
	public:
		virtual COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::BOOL; }
		static daeInt ID() { return 364; }
		virtual daeInt typeID() const { return ID(); }

	protected:  // Value
		/**
		 * The domGlsl_bool value of the text data of this element. 
		 */
		domGlsl_bool _value;

	public:	//Accessors and Mutators
		/**
		 * Gets the value of this element.
		 * @return a domGlsl_bool of the value.
		 */
		domGlsl_bool getValue() const { return _value; }
		/**
		 * Sets the _value of this element.
		 * @param val The new value for this element.
		 */
		void setValue( domGlsl_bool val ) { _value = val; }

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
		static daeInt ID() { return 365; }
		virtual daeInt typeID() const { return ID(); }

	protected:  // Value
		/**
		 * The domGlsl_bool2 value of the text data of this element. 
		 */
		domGlsl_bool2 _value;

	public:	//Accessors and Mutators
		/**
		 * Gets the _value array.
		 * @return Returns a domGlsl_bool2 reference of the _value array.
		 */
		domGlsl_bool2 &getValue() { return _value; }
		/**
		 * Gets the _value array.
		 * @return Returns a constant domGlsl_bool2 reference of the _value array.
		 */
		const domGlsl_bool2 &getValue() const { return _value; }
		/**
		 * Sets the _value array.
		 * @param val The new value for the _value array.
		 */
		void setValue( const domGlsl_bool2 &val ) { _value = val; }

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
		static daeInt ID() { return 366; }
		virtual daeInt typeID() const { return ID(); }

	protected:  // Value
		/**
		 * The domGlsl_bool3 value of the text data of this element. 
		 */
		domGlsl_bool3 _value;

	public:	//Accessors and Mutators
		/**
		 * Gets the _value array.
		 * @return Returns a domGlsl_bool3 reference of the _value array.
		 */
		domGlsl_bool3 &getValue() { return _value; }
		/**
		 * Gets the _value array.
		 * @return Returns a constant domGlsl_bool3 reference of the _value array.
		 */
		const domGlsl_bool3 &getValue() const { return _value; }
		/**
		 * Sets the _value array.
		 * @param val The new value for the _value array.
		 */
		void setValue( const domGlsl_bool3 &val ) { _value = val; }

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
		static daeInt ID() { return 367; }
		virtual daeInt typeID() const { return ID(); }

	protected:  // Value
		/**
		 * The domGlsl_bool4 value of the text data of this element. 
		 */
		domGlsl_bool4 _value;

	public:	//Accessors and Mutators
		/**
		 * Gets the _value array.
		 * @return Returns a domGlsl_bool4 reference of the _value array.
		 */
		domGlsl_bool4 &getValue() { return _value; }
		/**
		 * Gets the _value array.
		 * @return Returns a constant domGlsl_bool4 reference of the _value array.
		 */
		const domGlsl_bool4 &getValue() const { return _value; }
		/**
		 * Sets the _value array.
		 * @param val The new value for the _value array.
		 */
		void setValue( const domGlsl_bool4 &val ) { _value = val; }

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

	class domFloat;

	typedef daeSmartRef<domFloat> domFloatRef;
	typedef daeTArray<domFloatRef> domFloat_Array;

	class domFloat : public daeElement
	{
	public:
		virtual COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::FLOAT; }
		static daeInt ID() { return 368; }
		virtual daeInt typeID() const { return ID(); }

	protected:  // Value
		/**
		 * The domGlsl_float value of the text data of this element. 
		 */
		domGlsl_float _value;

	public:	//Accessors and Mutators
		/**
		 * Gets the value of this element.
		 * @return a domGlsl_float of the value.
		 */
		domGlsl_float getValue() const { return _value; }
		/**
		 * Sets the _value of this element.
		 * @param val The new value for this element.
		 */
		void setValue( domGlsl_float val ) { _value = val; }

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
		static daeInt ID() { return 369; }
		virtual daeInt typeID() const { return ID(); }

	protected:  // Value
		/**
		 * The domGlsl_float2 value of the text data of this element. 
		 */
		domGlsl_float2 _value;

	public:	//Accessors and Mutators
		/**
		 * Gets the _value array.
		 * @return Returns a domGlsl_float2 reference of the _value array.
		 */
		domGlsl_float2 &getValue() { return _value; }
		/**
		 * Gets the _value array.
		 * @return Returns a constant domGlsl_float2 reference of the _value array.
		 */
		const domGlsl_float2 &getValue() const { return _value; }
		/**
		 * Sets the _value array.
		 * @param val The new value for the _value array.
		 */
		void setValue( const domGlsl_float2 &val ) { _value = val; }

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
		static daeInt ID() { return 370; }
		virtual daeInt typeID() const { return ID(); }

	protected:  // Value
		/**
		 * The domGlsl_float3 value of the text data of this element. 
		 */
		domGlsl_float3 _value;

	public:	//Accessors and Mutators
		/**
		 * Gets the _value array.
		 * @return Returns a domGlsl_float3 reference of the _value array.
		 */
		domGlsl_float3 &getValue() { return _value; }
		/**
		 * Gets the _value array.
		 * @return Returns a constant domGlsl_float3 reference of the _value array.
		 */
		const domGlsl_float3 &getValue() const { return _value; }
		/**
		 * Sets the _value array.
		 * @param val The new value for the _value array.
		 */
		void setValue( const domGlsl_float3 &val ) { _value = val; }

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
		static daeInt ID() { return 371; }
		virtual daeInt typeID() const { return ID(); }

	protected:  // Value
		/**
		 * The domGlsl_float4 value of the text data of this element. 
		 */
		domGlsl_float4 _value;

	public:	//Accessors and Mutators
		/**
		 * Gets the _value array.
		 * @return Returns a domGlsl_float4 reference of the _value array.
		 */
		domGlsl_float4 &getValue() { return _value; }
		/**
		 * Gets the _value array.
		 * @return Returns a constant domGlsl_float4 reference of the _value array.
		 */
		const domGlsl_float4 &getValue() const { return _value; }
		/**
		 * Sets the _value array.
		 * @param val The new value for the _value array.
		 */
		void setValue( const domGlsl_float4 &val ) { _value = val; }

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

	class domFloat2x2;

	typedef daeSmartRef<domFloat2x2> domFloat2x2Ref;
	typedef daeTArray<domFloat2x2Ref> domFloat2x2_Array;

	class domFloat2x2 : public daeElement
	{
	public:
		virtual COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::FLOAT2X2; }
		static daeInt ID() { return 372; }
		virtual daeInt typeID() const { return ID(); }

	protected:  // Value
		/**
		 * The domGlsl_float2x2 value of the text data of this element. 
		 */
		domGlsl_float2x2 _value;

	public:	//Accessors and Mutators
		/**
		 * Gets the _value array.
		 * @return Returns a domGlsl_float2x2 reference of the _value array.
		 */
		domGlsl_float2x2 &getValue() { return _value; }
		/**
		 * Gets the _value array.
		 * @return Returns a constant domGlsl_float2x2 reference of the _value array.
		 */
		const domGlsl_float2x2 &getValue() const { return _value; }
		/**
		 * Sets the _value array.
		 * @param val The new value for the _value array.
		 */
		void setValue( const domGlsl_float2x2 &val ) { _value = val; }

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

	class domFloat3x3;

	typedef daeSmartRef<domFloat3x3> domFloat3x3Ref;
	typedef daeTArray<domFloat3x3Ref> domFloat3x3_Array;

	class domFloat3x3 : public daeElement
	{
	public:
		virtual COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::FLOAT3X3; }
		static daeInt ID() { return 373; }
		virtual daeInt typeID() const { return ID(); }

	protected:  // Value
		/**
		 * The domGlsl_float3x3 value of the text data of this element. 
		 */
		domGlsl_float3x3 _value;

	public:	//Accessors and Mutators
		/**
		 * Gets the _value array.
		 * @return Returns a domGlsl_float3x3 reference of the _value array.
		 */
		domGlsl_float3x3 &getValue() { return _value; }
		/**
		 * Gets the _value array.
		 * @return Returns a constant domGlsl_float3x3 reference of the _value array.
		 */
		const domGlsl_float3x3 &getValue() const { return _value; }
		/**
		 * Sets the _value array.
		 * @param val The new value for the _value array.
		 */
		void setValue( const domGlsl_float3x3 &val ) { _value = val; }

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

	class domFloat4x4;

	typedef daeSmartRef<domFloat4x4> domFloat4x4Ref;
	typedef daeTArray<domFloat4x4Ref> domFloat4x4_Array;

	class domFloat4x4 : public daeElement
	{
	public:
		virtual COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::FLOAT4X4; }
		static daeInt ID() { return 374; }
		virtual daeInt typeID() const { return ID(); }

	protected:  // Value
		/**
		 * The domGlsl_float4x4 value of the text data of this element. 
		 */
		domGlsl_float4x4 _value;

	public:	//Accessors and Mutators
		/**
		 * Gets the _value array.
		 * @return Returns a domGlsl_float4x4 reference of the _value array.
		 */
		domGlsl_float4x4 &getValue() { return _value; }
		/**
		 * Gets the _value array.
		 * @return Returns a constant domGlsl_float4x4 reference of the _value array.
		 */
		const domGlsl_float4x4 &getValue() const { return _value; }
		/**
		 * Sets the _value array.
		 * @param val The new value for the _value array.
		 */
		void setValue( const domGlsl_float4x4 &val ) { _value = val; }

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

	class domInt;

	typedef daeSmartRef<domInt> domIntRef;
	typedef daeTArray<domIntRef> domInt_Array;

	class domInt : public daeElement
	{
	public:
		virtual COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::INT; }
		static daeInt ID() { return 375; }
		virtual daeInt typeID() const { return ID(); }

	protected:  // Value
		/**
		 * The domGlsl_int value of the text data of this element. 
		 */
		domGlsl_int _value;

	public:	//Accessors and Mutators
		/**
		 * Gets the value of this element.
		 * @return a domGlsl_int of the value.
		 */
		domGlsl_int getValue() const { return _value; }
		/**
		 * Sets the _value of this element.
		 * @param val The new value for this element.
		 */
		void setValue( domGlsl_int val ) { _value = val; }

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
		static daeInt ID() { return 376; }
		virtual daeInt typeID() const { return ID(); }

	protected:  // Value
		/**
		 * The domGlsl_int2 value of the text data of this element. 
		 */
		domGlsl_int2 _value;

	public:	//Accessors and Mutators
		/**
		 * Gets the _value array.
		 * @return Returns a domGlsl_int2 reference of the _value array.
		 */
		domGlsl_int2 &getValue() { return _value; }
		/**
		 * Gets the _value array.
		 * @return Returns a constant domGlsl_int2 reference of the _value array.
		 */
		const domGlsl_int2 &getValue() const { return _value; }
		/**
		 * Sets the _value array.
		 * @param val The new value for the _value array.
		 */
		void setValue( const domGlsl_int2 &val ) { _value = val; }

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
		static daeInt ID() { return 377; }
		virtual daeInt typeID() const { return ID(); }

	protected:  // Value
		/**
		 * The domGlsl_int3 value of the text data of this element. 
		 */
		domGlsl_int3 _value;

	public:	//Accessors and Mutators
		/**
		 * Gets the _value array.
		 * @return Returns a domGlsl_int3 reference of the _value array.
		 */
		domGlsl_int3 &getValue() { return _value; }
		/**
		 * Gets the _value array.
		 * @return Returns a constant domGlsl_int3 reference of the _value array.
		 */
		const domGlsl_int3 &getValue() const { return _value; }
		/**
		 * Sets the _value array.
		 * @param val The new value for the _value array.
		 */
		void setValue( const domGlsl_int3 &val ) { _value = val; }

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
		static daeInt ID() { return 378; }
		virtual daeInt typeID() const { return ID(); }

	protected:  // Value
		/**
		 * The domGlsl_int4 value of the text data of this element. 
		 */
		domGlsl_int4 _value;

	public:	//Accessors and Mutators
		/**
		 * Gets the _value array.
		 * @return Returns a domGlsl_int4 reference of the _value array.
		 */
		domGlsl_int4 &getValue() { return _value; }
		/**
		 * Gets the _value array.
		 * @return Returns a constant domGlsl_int4 reference of the _value array.
		 */
		const domGlsl_int4 &getValue() const { return _value; }
		/**
		 * Sets the _value array.
		 * @param val The new value for the _value array.
		 */
		void setValue( const domGlsl_int4 &val ) { _value = val; }

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

	class domEnum;

	typedef daeSmartRef<domEnum> domEnumRef;
	typedef daeTArray<domEnumRef> domEnum_Array;

	class domEnum : public daeElement
	{
	public:
		virtual COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::ENUM; }
		static daeInt ID() { return 379; }
		virtual daeInt typeID() const { return ID(); }

	protected:  // Value
		/**
		 * The domGl_enumeration value of the text data of this element. 
		 */
		domGl_enumeration _value;

	public:	//Accessors and Mutators
		/**
		 * Gets the value of this element.
		 * @return a domGl_enumeration of the value.
		 */
		domGl_enumeration getValue() const { return _value; }
		/**
		 * Sets the _value of this element.
		 * @param val The new value for this element.
		 */
		void setValue( domGl_enumeration val ) { _value = val; }

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
	domFloatRef elemFloat;
	domFloat2Ref elemFloat2;
	domFloat3Ref elemFloat3;
	domFloat4Ref elemFloat4;
	domFloat2x2Ref elemFloat2x2;
	domFloat3x3Ref elemFloat3x3;
	domFloat4x4Ref elemFloat4x4;
	domIntRef elemInt;
	domInt2Ref elemInt2;
	domInt3Ref elemInt3;
	domInt4Ref elemInt4;
	domGlsl_surface_typeRef elemSurface;
	domGl_sampler1DRef elemSampler1D;
	domGl_sampler2DRef elemSampler2D;
	domGl_sampler3DRef elemSampler3D;
	domGl_samplerCUBERef elemSamplerCUBE;
	domGl_samplerRECTRef elemSamplerRECT;
	domGl_samplerDEPTHRef elemSamplerDEPTH;
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
	 * Gets the float2x2 element.
	 * @return a daeSmartRef to the float2x2 element.
	 */
	const domFloat2x2Ref getFloat2x2() const { return elemFloat2x2; }
	/**
	 * Gets the float3x3 element.
	 * @return a daeSmartRef to the float3x3 element.
	 */
	const domFloat3x3Ref getFloat3x3() const { return elemFloat3x3; }
	/**
	 * Gets the float4x4 element.
	 * @return a daeSmartRef to the float4x4 element.
	 */
	const domFloat4x4Ref getFloat4x4() const { return elemFloat4x4; }
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
	 * Gets the surface element.
	 * @return a daeSmartRef to the surface element.
	 */
	const domGlsl_surface_typeRef getSurface() const { return elemSurface; }
	/**
	 * Gets the sampler1D element.
	 * @return a daeSmartRef to the sampler1D element.
	 */
	const domGl_sampler1DRef getSampler1D() const { return elemSampler1D; }
	/**
	 * Gets the sampler2D element.
	 * @return a daeSmartRef to the sampler2D element.
	 */
	const domGl_sampler2DRef getSampler2D() const { return elemSampler2D; }
	/**
	 * Gets the sampler3D element.
	 * @return a daeSmartRef to the sampler3D element.
	 */
	const domGl_sampler3DRef getSampler3D() const { return elemSampler3D; }
	/**
	 * Gets the samplerCUBE element.
	 * @return a daeSmartRef to the samplerCUBE element.
	 */
	const domGl_samplerCUBERef getSamplerCUBE() const { return elemSamplerCUBE; }
	/**
	 * Gets the samplerRECT element.
	 * @return a daeSmartRef to the samplerRECT element.
	 */
	const domGl_samplerRECTRef getSamplerRECT() const { return elemSamplerRECT; }
	/**
	 * Gets the samplerDEPTH element.
	 * @return a daeSmartRef to the samplerDEPTH element.
	 */
	const domGl_samplerDEPTHRef getSamplerDEPTH() const { return elemSamplerDEPTH; }
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
	domGlsl_param_type(DAE& dae) : daeElement(dae), elemBool(), elemBool2(), elemBool3(), elemBool4(), elemFloat(), elemFloat2(), elemFloat3(), elemFloat4(), elemFloat2x2(), elemFloat3x3(), elemFloat4x4(), elemInt(), elemInt2(), elemInt3(), elemInt4(), elemSurface(), elemSampler1D(), elemSampler2D(), elemSampler3D(), elemSamplerCUBE(), elemSamplerRECT(), elemSamplerDEPTH(), elemEnum() {}
	/**
	 * Destructor
	 */
	virtual ~domGlsl_param_type() { daeElement::deleteCMDataArray(_CMData); }
	/**
	 * Overloaded assignment operator
	 */
	virtual domGlsl_param_type &operator=( const domGlsl_param_type &cpy ) { (void)cpy; return *this; }

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
