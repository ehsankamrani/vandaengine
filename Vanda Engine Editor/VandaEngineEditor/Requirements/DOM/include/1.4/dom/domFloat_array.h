/*
* Copyright 2006 Sony Computer Entertainment Inc.
*
* Licensed under the MIT Open Source License, for details please see license.txt or the website
* http://www.opensource.org/licenses/mit-license.php
*
*/ 

#ifndef __domFloat_array_h__
#define __domFloat_array_h__

#include <dae/daeDocument.h>
#include <dom/domTypes.h>
#include <dom/domElements.h>

class DAE;

/**
 * The float_array element declares the storage for a homogenous array of
 * floating point values.
 */
class domFloat_array : public daeElement
{
public:
	virtual COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::FLOAT_ARRAY; }
	static daeInt ID() { return 607; }
	virtual daeInt typeID() const { return ID(); }
protected:  // Attributes
/**
 *  The id attribute is a text string containing the unique identifier of
 * this element. This value  must be unique within the instance document.
 * Optional attribute. 
 */
	xsID attrId;
/**
 *  The name attribute is the text string name of this element. Optional attribute.
 */
	xsNCName attrName;
/**
 *  The count attribute indicates the number of values in the array. Required
 * attribute. 
 */
	domUint attrCount;
/**
 *  The digits attribute indicates the number of significant decimal digits
 * of the float values that  can be contained in the array. The default value
 * is 6. Optional attribute. 
 */
	xsShort attrDigits;
/**
 *  The magnitude attribute indicates the largest exponent of the float values
 * that can be contained  in the array. The default value is 38. Optional
 * attribute. 
 */
	xsShort attrMagnitude;

protected:  // Value
	/**
	 * The domListOfFloats value of the text data of this element. 
	 */
	domListOfFloats _value;

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
	 * Gets the count attribute.
	 * @return Returns a domUint of the count attribute.
	 */
	domUint getCount() const { return attrCount; }
	/**
	 * Sets the count attribute.
	 * @param atCount The new value for the count attribute.
	 */
	void setCount( domUint atCount ) { attrCount = atCount; _validAttributeArray[2] = true; }

	/**
	 * Gets the digits attribute.
	 * @return Returns a xsShort of the digits attribute.
	 */
	xsShort getDigits() const { return attrDigits; }
	/**
	 * Sets the digits attribute.
	 * @param atDigits The new value for the digits attribute.
	 */
	void setDigits( xsShort atDigits ) { attrDigits = atDigits; _validAttributeArray[3] = true; }

	/**
	 * Gets the magnitude attribute.
	 * @return Returns a xsShort of the magnitude attribute.
	 */
	xsShort getMagnitude() const { return attrMagnitude; }
	/**
	 * Sets the magnitude attribute.
	 * @param atMagnitude The new value for the magnitude attribute.
	 */
	void setMagnitude( xsShort atMagnitude ) { attrMagnitude = atMagnitude; _validAttributeArray[4] = true; }

	/**
	 * Gets the _value array.
	 * @return Returns a domListOfFloats reference of the _value array.
	 */
	domListOfFloats &getValue() { return _value; }
	/**
	 * Gets the _value array.
	 * @return Returns a constant domListOfFloats reference of the _value array.
	 */
	const domListOfFloats &getValue() const { return _value; }
	/**
	 * Sets the _value array.
	 * @param val The new value for the _value array.
	 */
	void setValue( const domListOfFloats &val ) { _value = val; }

protected:
	/**
	 * Constructor
	 */
	domFloat_array(DAE& dae) : daeElement(dae), attrId(), attrName(), attrCount(), attrDigits(), attrMagnitude(), _value() {}
	/**
	 * Destructor
	 */
	virtual ~domFloat_array() {}
	/**
	 * Overloaded assignment operator
	 */
	virtual domFloat_array &operator=( const domFloat_array &cpy ) { (void)cpy; return *this; }

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
