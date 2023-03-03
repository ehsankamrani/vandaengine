/*
* Copyright 2006 Sony Computer Entertainment Inc.
*
* Licensed under the MIT Open Source License, for details please see license.txt or the website
* http://www.opensource.org/licenses/mit-license.php
*
*/ 

#ifndef __domSource_h__
#define __domSource_h__

#include <dae/daeDocument.h>
#include <dom/domTypes.h>
#include <dom/domElements.h>

#include <dom/domAsset.h>
#include <dom/domIDREF_array.h>
#include <dom/domName_array.h>
#include <dom/domBool_array.h>
#include <dom/domFloat_array.h>
#include <dom/domInt_array.h>
#include <dom/domTechnique.h>
#include <dom/domAccessor.h>
class DAE;

/**
 * The source element declares a data repository that provides values according
 * to the semantics of an  input element that refers to it.
 */
class domSource : public daeElement
{
public:
	virtual COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::SOURCE; }
	static daeInt ID() { return 611; }
	virtual daeInt typeID() const { return ID(); }
public:
	class domTechnique_common;

	typedef daeSmartRef<domTechnique_common> domTechnique_commonRef;
	typedef daeTArray<domTechnique_commonRef> domTechnique_common_Array;

/**
 * The technique common specifies the common method for accessing this source
 * element's data.
 */
	class domTechnique_common : public daeElement
	{
	public:
		virtual COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::TECHNIQUE_COMMON; }
		static daeInt ID() { return 612; }
		virtual daeInt typeID() const { return ID(); }

	protected:  // Element
/**
 *  The source's technique_common must have one and only one accessor.  @see
 * domAccessor
 */
		domAccessorRef elemAccessor;

	public:	//Accessors and Mutators
		/**
		 * Gets the accessor element.
		 * @return a daeSmartRef to the accessor element.
		 */
		const domAccessorRef getAccessor() const { return elemAccessor; }
	protected:
		/**
		 * Constructor
		 */
		domTechnique_common(DAE& dae) : daeElement(dae), elemAccessor() {}
		/**
		 * Destructor
		 */
		virtual ~domTechnique_common() {}
		/**
		 * Overloaded assignment operator
		 */
		virtual domTechnique_common &operator=( const domTechnique_common &cpy ) { (void)cpy; return *this; }

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
 * this element.  This value must be unique within the instance document.
 * Required attribute. 
 */
	xsID attrId;
/**
 *  The name attribute is the text string name of this element. Optional attribute.
 */
	xsNCName attrName;

protected:  // Elements
/**
 *  The source element may contain an asset element.  @see domAsset
 */
	domAssetRef elemAsset;
/**
 *  The source element may contain an IDREF_array.  @see domIDREF_array
 */
	domIDREF_arrayRef elemIDREF_array;
/**
 *  The source element may contain a Name_array.  @see domName_array
 */
	domName_arrayRef elemName_array;
/**
 *  The source element may contain a bool_array.  @see domBool_array
 */
	domBool_arrayRef elemBool_array;
/**
 *  The source element may contain a float_array.  @see domFloat_array
 */
	domFloat_arrayRef elemFloat_array;
/**
 *  The source element may contain an int_array.  @see domInt_array
 */
	domInt_arrayRef elemInt_array;
/**
 * The technique common specifies the common method for accessing this source
 * element's data. @see domTechnique_common
 */
	domTechnique_commonRef elemTechnique_common;
/**
 *  This element may contain any number of non-common profile techniques.
 * @see domTechnique
 */
	domTechnique_Array elemTechnique_array;
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
	 * Gets the asset element.
	 * @return a daeSmartRef to the asset element.
	 */
	const domAssetRef getAsset() const { return elemAsset; }
	/**
	 * Gets the IDREF_array element.
	 * @return a daeSmartRef to the IDREF_array element.
	 */
	const domIDREF_arrayRef getIDREF_array() const { return elemIDREF_array; }
	/**
	 * Gets the Name_array element.
	 * @return a daeSmartRef to the Name_array element.
	 */
	const domName_arrayRef getName_array() const { return elemName_array; }
	/**
	 * Gets the bool_array element.
	 * @return a daeSmartRef to the bool_array element.
	 */
	const domBool_arrayRef getBool_array() const { return elemBool_array; }
	/**
	 * Gets the float_array element.
	 * @return a daeSmartRef to the float_array element.
	 */
	const domFloat_arrayRef getFloat_array() const { return elemFloat_array; }
	/**
	 * Gets the int_array element.
	 * @return a daeSmartRef to the int_array element.
	 */
	const domInt_arrayRef getInt_array() const { return elemInt_array; }
	/**
	 * Gets the technique_common element.
	 * @return a daeSmartRef to the technique_common element.
	 */
	const domTechnique_commonRef getTechnique_common() const { return elemTechnique_common; }
	/**
	 * Gets the technique element array.
	 * @return Returns a reference to the array of technique elements.
	 */
	domTechnique_Array &getTechnique_array() { return elemTechnique_array; }
	/**
	 * Gets the technique element array.
	 * @return Returns a constant reference to the array of technique elements.
	 */
	const domTechnique_Array &getTechnique_array() const { return elemTechnique_array; }
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
	domSource(DAE& dae) : daeElement(dae), attrId(), attrName(), elemAsset(), elemIDREF_array(), elemName_array(), elemBool_array(), elemFloat_array(), elemInt_array(), elemTechnique_common(), elemTechnique_array() {}
	/**
	 * Destructor
	 */
	virtual ~domSource() { daeElement::deleteCMDataArray(_CMData); }
	/**
	 * Overloaded assignment operator
	 */
	virtual domSource &operator=( const domSource &cpy ) { (void)cpy; return *this; }

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
