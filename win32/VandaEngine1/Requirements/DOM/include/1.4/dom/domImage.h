/*
* Copyright 2006 Sony Computer Entertainment Inc.
*
* Licensed under the MIT Open Source License, for details please see license.txt or the website
* http://www.opensource.org/licenses/mit-license.php
*
*/ 

#ifndef __domImage_h__
#define __domImage_h__

#include <dae/daeDocument.h>
#include <dom/domTypes.h>
#include <dom/domElements.h>

#include <dom/domAsset.h>
#include <dom/domExtra.h>
class DAE;

/**
 * The image element declares the storage for the graphical representation
 * of an object.  The image element best describes raster image data, but
 * can conceivably handle other  forms of imagery. The image elements allows
 * for specifying an external image file with  the init_from element or embed
 * image data with the data element.
 */
class domImage : public daeElement
{
public:
	virtual COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::IMAGE; }
	static daeInt ID() { return 635; }
	virtual daeInt typeID() const { return ID(); }
public:
	class domData;

	typedef daeSmartRef<domData> domDataRef;
	typedef daeTArray<domDataRef> domData_Array;

/**
 * The data child element contains a sequence of hexadecimal encoded  binary
 * octets representing  the embedded image data.
 */
	class domData : public daeElement
	{
	public:
		virtual COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::DATA; }
		static daeInt ID() { return 636; }
		virtual daeInt typeID() const { return ID(); }

	protected:  // Value
		/**
		 * The domListOfHexBinary value of the text data of this element. 
		 */
		domListOfHexBinary _value;

	public:	//Accessors and Mutators
		/**
		 * Gets the _value array.
		 * @return Returns a domListOfHexBinary reference of the _value array.
		 */
		domListOfHexBinary &getValue() { return _value; }
		/**
		 * Gets the _value array.
		 * @return Returns a constant domListOfHexBinary reference of the _value array.
		 */
		const domListOfHexBinary &getValue() const { return _value; }
		/**
		 * Sets the _value array.
		 * @param val The new value for the _value array.
		 */
		void setValue( const domListOfHexBinary &val ) { _value = val; }

	protected:
		/**
		 * Constructor
		 */
		domData(DAE& dae) : daeElement(dae), _value() {}
		/**
		 * Destructor
		 */
		virtual ~domData() {}
		/**
		 * Overloaded assignment operator
		 */
		virtual domData &operator=( const domData &cpy ) { (void)cpy; return *this; }

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

	class domInit_from;

	typedef daeSmartRef<domInit_from> domInit_fromRef;
	typedef daeTArray<domInit_fromRef> domInit_from_Array;

/**
 * The init_from element allows you to specify an external image file to use
 * for the image element.
 */
	class domInit_from : public daeElement
	{
	public:
		virtual COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::INIT_FROM; }
		static daeInt ID() { return 637; }
		virtual daeInt typeID() const { return ID(); }

	protected:  // Value
		/**
		 * The xsAnyURI value of the text data of this element. 
		 */
		xsAnyURI _value;

	public:	//Accessors and Mutators
		/**
		 * Gets the value of this element.
		 * @return Returns a xsAnyURI of the value.
		 */
		xsAnyURI &getValue() { return _value; }
		/**
		 * Gets the value of this element.
		 * @return Returns a constant xsAnyURI of the value.
		 */
		const xsAnyURI &getValue() const { return _value; }
		/**
		 * Sets the _value of this element.
		 * @param val The new value for this element.
		 */
		void setValue( const xsAnyURI &val ) { _value = val; }
		/**
		 * Sets the _value of this element.
		 * @param val The new value for this element.
		 */
		void setValue( xsString val ) { _value = val; }

	protected:
		/**
		 * Constructor
		 */
		domInit_from(DAE& dae) : daeElement(dae), _value(dae, *this) {}
		/**
		 * Destructor
		 */
		virtual ~domInit_from() {}
		/**
		 * Overloaded assignment operator
		 */
		virtual domInit_from &operator=( const domInit_from &cpy ) { (void)cpy; return *this; }

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
 * this element. This value  must be unique within the instance document.
 * Optional attribute. 
 */
	xsID attrId;
/**
 *  The name attribute is the text string name of this element. Optional attribute.
 */
	xsNCName attrName;
/**
 *  The format attribute is a text string value that indicates the image format.
 * Optional attribute. 
 */
	xsToken attrFormat;
/**
 *  The height attribute is an integer value that indicates the height of
 * the image in pixel  units. Optional attribute. 
 */
	domUint attrHeight;
/**
 *  The width attribute is an integer value that indicates the width of the
 * image in pixel units.  Optional attribute. 
 */
	domUint attrWidth;
/**
 *  The depth attribute is an integer value that indicates the depth of the
 * image in pixel units.  A 2-D image has a depth of 1, which is also the
 * default value. Optional attribute. 
 */
	domUint attrDepth;

protected:  // Elements
/**
 *  The image element may contain an asset element.  @see domAsset
 */
	domAssetRef elemAsset;
/**
 * The data child element contains a sequence of hexadecimal encoded  binary
 * octets representing  the embedded image data. @see domData
 */
	domDataRef elemData;
/**
 * The init_from element allows you to specify an external image file to use
 * for the image element. @see domInit_from
 */
	domInit_fromRef elemInit_from;
/**
 *  The extra element may appear any number of times.  @see domExtra
 */
	domExtra_Array elemExtra_array;
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
	 * Gets the format attribute.
	 * @return Returns a xsToken of the format attribute.
	 */
	xsToken getFormat() const { return attrFormat; }
	/**
	 * Sets the format attribute.
	 * @param atFormat The new value for the format attribute.
	 */
	void setFormat( xsToken atFormat ) { *(daeStringRef*)&attrFormat = atFormat; _validAttributeArray[2] = true; }

	/**
	 * Gets the height attribute.
	 * @return Returns a domUint of the height attribute.
	 */
	domUint getHeight() const { return attrHeight; }
	/**
	 * Sets the height attribute.
	 * @param atHeight The new value for the height attribute.
	 */
	void setHeight( domUint atHeight ) { attrHeight = atHeight; _validAttributeArray[3] = true; }

	/**
	 * Gets the width attribute.
	 * @return Returns a domUint of the width attribute.
	 */
	domUint getWidth() const { return attrWidth; }
	/**
	 * Sets the width attribute.
	 * @param atWidth The new value for the width attribute.
	 */
	void setWidth( domUint atWidth ) { attrWidth = atWidth; _validAttributeArray[4] = true; }

	/**
	 * Gets the depth attribute.
	 * @return Returns a domUint of the depth attribute.
	 */
	domUint getDepth() const { return attrDepth; }
	/**
	 * Sets the depth attribute.
	 * @param atDepth The new value for the depth attribute.
	 */
	void setDepth( domUint atDepth ) { attrDepth = atDepth; _validAttributeArray[5] = true; }

	/**
	 * Gets the asset element.
	 * @return a daeSmartRef to the asset element.
	 */
	const domAssetRef getAsset() const { return elemAsset; }
	/**
	 * Gets the data element.
	 * @return a daeSmartRef to the data element.
	 */
	const domDataRef getData() const { return elemData; }
	/**
	 * Gets the init_from element.
	 * @return a daeSmartRef to the init_from element.
	 */
	const domInit_fromRef getInit_from() const { return elemInit_from; }
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
	domImage(DAE& dae) : daeElement(dae), attrId(), attrName(), attrFormat(), attrHeight(), attrWidth(), attrDepth(), elemAsset(), elemData(), elemInit_from(), elemExtra_array() {}
	/**
	 * Destructor
	 */
	virtual ~domImage() { daeElement::deleteCMDataArray(_CMData); }
	/**
	 * Overloaded assignment operator
	 */
	virtual domImage &operator=( const domImage &cpy ) { (void)cpy; return *this; }

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
