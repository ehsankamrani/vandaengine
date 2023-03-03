/*
* Copyright 2006 Sony Computer Entertainment Inc.
*
* Licensed under the MIT Open Source License, for details please see license.txt or the website
* http://www.opensource.org/licenses/mit-license.php
*
*/ 

#ifndef __domGles_texcombiner_command_type_h__
#define __domGles_texcombiner_command_type_h__

#include <dae/daeDocument.h>
#include <dom/domTypes.h>
#include <dom/domElements.h>

#include <dom/domGles_texture_constant_type.h>
#include <dom/domGles_texcombiner_commandRGB_type.h>
#include <dom/domGles_texcombiner_commandAlpha_type.h>
class DAE;

class domGles_texcombiner_command_type_complexType 
{

protected:  // Elements
	domGles_texture_constant_typeRef elemConstant;
	domGles_texcombiner_commandRGB_typeRef elemRGB;
	domGles_texcombiner_commandAlpha_typeRef elemAlpha;

public:	//Accessors and Mutators
	/**
	 * Gets the constant element.
	 * @return a daeSmartRef to the constant element.
	 */
	const domGles_texture_constant_typeRef getConstant() const { return elemConstant; }
	/**
	 * Gets the RGB element.
	 * @return a daeSmartRef to the RGB element.
	 */
	const domGles_texcombiner_commandRGB_typeRef getRGB() const { return elemRGB; }
	/**
	 * Gets the alpha element.
	 * @return a daeSmartRef to the alpha element.
	 */
	const domGles_texcombiner_commandAlpha_typeRef getAlpha() const { return elemAlpha; }
protected:
	/**
	 * Constructor
	 */
	domGles_texcombiner_command_type_complexType(DAE& dae, daeElement* elt) : elemConstant(), elemRGB(), elemAlpha() {}
	/**
	 * Destructor
	 */
	virtual ~domGles_texcombiner_command_type_complexType() {}
	/**
	 * Overloaded assignment operator
	 */
	virtual domGles_texcombiner_command_type_complexType &operator=( const domGles_texcombiner_command_type_complexType &cpy ) { (void)cpy; return *this; }
};

/**
 * An element of type domGles_texcombiner_command_type_complexType.
 */
class domGles_texcombiner_command_type : public daeElement, public domGles_texcombiner_command_type_complexType
{
public:
	virtual COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::GLES_TEXCOMBINER_COMMAND_TYPE; }
	static daeInt ID() { return 151; }
	virtual daeInt typeID() const { return ID(); }
protected:
	/**
	 * Constructor
	 */
	domGles_texcombiner_command_type(DAE& dae) : daeElement(dae), domGles_texcombiner_command_type_complexType(dae, this) {}
	/**
	 * Destructor
	 */
	virtual ~domGles_texcombiner_command_type() {}
	/**
	 * Overloaded assignment operator
	 */
	virtual domGles_texcombiner_command_type &operator=( const domGles_texcombiner_command_type &cpy ) { (void)cpy; return *this; }

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
