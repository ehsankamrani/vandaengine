/*
* Copyright 2006 Sony Computer Entertainment Inc.
*
* Licensed under the MIT Open Source License, for details please see license.txt or the website
* http://www.opensource.org/licenses/mit-license.php
*
*/ 
#ifndef __domAny_h__
#define __domAny_h__

#include <dae/daeElement.h>
#include <dae/daeMetaElement.h>
#include <dae/daeArray.h>
#include <dae/daeURI.h>
#include <dae/daeIDRef.h>
#include <dom/domTypes.h>

/**
 * The domAny class allows for weakly typed xml elements.  This class is used anywhere in the 
 * COLLADA schema where an xs:any element appears. The content and type information for a domAny
 * object is generated at runtime.
 */
class domAny : public daeElement
{
	friend class domAnyAttribute;
protected:  // Attribute
	/**
	 * The array of daeStrings to hold attribute data for this element.
	 */
	daeTArray<daeString> attrs;
	/**
	 * The domString value of the text data of this element. 
	 */
	daeString _value;
	/**
	 * Used to preserve order in elements that do not specify strict sequencing of sub-elements.
	 */
	daeElementRefArray _contents;
	/**
	 * Used to preserve order in elements that have a complex content model.
	 */
	daeUIntArray       _contentsOrder;

public:
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

	/**
	 * Gets the number of attributes this element has.
	 * @return Returns the number of attributes on this element.
	 */
	daeUInt getAttributeCount() const { return (daeUInt)_meta->getMetaAttributes().getCount(); }
	/**
	 * Gets an attribute's name.
	 * @param index The index into the attribute list.
	 * @return Returns the attribute's name.
	 */
	daeString getAttributeName( daeUInt index ) const { return _meta->getMetaAttributes()[index]->getName(); }
	/**
	 * Gets an attribute's value.
	 * @param index The index into the attribute list.
	 * @return Returns the attribute's value as a string.
	 */
	daeString getAttributeValue( daeUInt index ) const { return attrs[ index ]; }
	/**
	 * Gets the value of this element.
	 * @return Returns a daeString of the value.
	 */
	daeString getValue() const { return _value; }
	/**
	 * Sets the _value of this element.
	 * @param val The new value for this element.
	 */
	void setValue( daeString val ) { *(daeStringRef*)&_value = val; }

	/**
	 * Gets the element type.
	 * @return Returns the COLLADA_TYPE::TypeEnum value corresponding to this element's type.
	 */
	virtual COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::ANY; }

	static daeInt ID() { return colladaTypeCount()-1; }
	virtual daeInt typeID() const { return colladaTypeCount()-1; }

protected:
	/**
	 * Constructor
	 */
	domAny() : _value() {}
	/**
	 * Destructor
	 */
	virtual ~domAny();
	/**
	 * Copy Constructor
	 */
	domAny( const domAny &cpy ) : daeElement() { (void)cpy; }
	/**
	 * Overloaded assignment operator
	 */
	virtual domAny &operator=( const domAny &cpy ) { (void)cpy; return *this; }

public: //METHODS
	/**
	 * Override of the Base class method. Creates and registers an attribute field with its meta 
	 * and assigns its value as the <tt><i> attrValue </i></tt> String.
	 * @param attrName Attribute to set.
	 * @param attrValue String-based value to apply to the attribute.
	 * @return Returns true if the attribute was created and the value was set, false otherwise.
	 */
	virtual DLLSPEC daeBool setAttribute(daeString attrName, daeString attrValue);

public: // STATIC METHODS
	/**
	 * Creates an instance of this class and returns a daeElementRef referencing it.
	 * @return a daeElementRef referencing an instance of this object.
	 */
	static DLLSPEC daeElementRef create(DAE& dae);
	/**
	 * Creates a daeMetaElement object that describes this element in the meta object reflection framework.
	 * @return A daeMetaElement describing this COLLADA element.
	 * @remarks Unlike other dom* elements, domAny will always create a new daeMetaElement when this 
	 *          function is called. 
	 */
	static DLLSPEC daeMetaElement* registerElement(DAE& dae);

};

typedef daeSmartRef<domAny> domAnyRef;
typedef daeTArray<domAnyRef> domAny_Array;

#endif

