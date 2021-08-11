/*
* Copyright 2006 Sony Computer Entertainment Inc.
*
* Licensed under the MIT Open Source License, for details please see license.txt or the website
* http://www.opensource.org/licenses/mit-license.php
*
*/ 

#ifndef __domCg_samplerCUBE_h__
#define __domCg_samplerCUBE_h__

#include <dae/daeDocument.h>
#include <dom/domTypes.h>
#include <dom/domElements.h>

#include <dom/domFx_samplerCUBE_common.h>
class DAE;

class domCg_samplerCUBE_complexType  : public domFx_samplerCUBE_common_complexType
{

protected:
	/**
	 * Constructor
	 */
	domCg_samplerCUBE_complexType(DAE& dae, daeElement* elt) : domFx_samplerCUBE_common_complexType(dae, elt) {}
	/**
	 * Destructor
	 */
	virtual ~domCg_samplerCUBE_complexType() {}
	/**
	 * Overloaded assignment operator
	 */
	virtual domCg_samplerCUBE_complexType &operator=( const domCg_samplerCUBE_complexType &cpy ) { (void)cpy; return *this; }
};

/**
 * An element of type domCg_samplerCUBE_complexType.
 */
class domCg_samplerCUBE : public daeElement, public domCg_samplerCUBE_complexType
{
public:
	virtual COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::CG_SAMPLERCUBE; }
	static daeInt ID() { return 130; }
	virtual daeInt typeID() const { return ID(); }
protected:
	/**
	 * Constructor
	 */
	domCg_samplerCUBE(DAE& dae) : daeElement(dae), domCg_samplerCUBE_complexType(dae, this) {}
	/**
	 * Destructor
	 */
	virtual ~domCg_samplerCUBE() {}
	/**
	 * Overloaded assignment operator
	 */
	virtual domCg_samplerCUBE &operator=( const domCg_samplerCUBE &cpy ) { (void)cpy; return *this; }

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
