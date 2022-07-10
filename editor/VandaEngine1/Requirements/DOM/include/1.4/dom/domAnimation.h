/*
* Copyright 2006 Sony Computer Entertainment Inc.
*
* Licensed under the MIT Open Source License, for details please see license.txt or the website
* http://www.opensource.org/licenses/mit-license.php
*
*/ 

#ifndef __domAnimation_h__
#define __domAnimation_h__

#include <dae/daeDocument.h>
#include <dom/domTypes.h>
#include <dom/domElements.h>

#include <dom/domAsset.h>
#include <dom/domSource.h>
#include <dom/domSampler.h>
#include <dom/domChannel.h>
#include <dom/domAnimation.h>
#include <dom/domExtra.h>
class DAE;

/**
 * The animation element categorizes the declaration of animation information.
 * The animation  hierarchy contains elements that describe the animation’s
 * key-frame data and sampler functions,  ordered in such a way to group together
 * animations that should be executed together.
 */
class domAnimation : public daeElement
{
public:
	virtual COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::ANIMATION; }
	static daeInt ID() { return 651; }
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

protected:  // Elements
/**
 *  The animation element may contain an asset element.  @see domAsset
 */
	domAssetRef elemAsset;
/**
 *  The animation element may contain any number of source elements.  @see
 * domSource
 */
	domSource_Array elemSource_array;
/**
 *  The animation element may contain any number of sampler elements.  @see
 * domSampler
 */
	domSampler_Array elemSampler_array;
/**
 *  The animation element may contain any number of channel elements.  @see
 * domChannel
 */
	domChannel_Array elemChannel_array;
/**
 *  The animation may be hierarchical and may contain any number of other
 * animation elements.  @see domAnimation
 */
	domAnimation_Array elemAnimation_array;
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
	 * Gets the asset element.
	 * @return a daeSmartRef to the asset element.
	 */
	const domAssetRef getAsset() const { return elemAsset; }
	/**
	 * Gets the source element array.
	 * @return Returns a reference to the array of source elements.
	 */
	domSource_Array &getSource_array() { return elemSource_array; }
	/**
	 * Gets the source element array.
	 * @return Returns a constant reference to the array of source elements.
	 */
	const domSource_Array &getSource_array() const { return elemSource_array; }
	/**
	 * Gets the sampler element array.
	 * @return Returns a reference to the array of sampler elements.
	 */
	domSampler_Array &getSampler_array() { return elemSampler_array; }
	/**
	 * Gets the sampler element array.
	 * @return Returns a constant reference to the array of sampler elements.
	 */
	const domSampler_Array &getSampler_array() const { return elemSampler_array; }
	/**
	 * Gets the channel element array.
	 * @return Returns a reference to the array of channel elements.
	 */
	domChannel_Array &getChannel_array() { return elemChannel_array; }
	/**
	 * Gets the channel element array.
	 * @return Returns a constant reference to the array of channel elements.
	 */
	const domChannel_Array &getChannel_array() const { return elemChannel_array; }
	/**
	 * Gets the animation element array.
	 * @return Returns a reference to the array of animation elements.
	 */
	domAnimation_Array &getAnimation_array() { return elemAnimation_array; }
	/**
	 * Gets the animation element array.
	 * @return Returns a constant reference to the array of animation elements.
	 */
	const domAnimation_Array &getAnimation_array() const { return elemAnimation_array; }
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
	domAnimation(DAE& dae) : daeElement(dae), attrId(), attrName(), elemAsset(), elemSource_array(), elemSampler_array(), elemChannel_array(), elemAnimation_array(), elemExtra_array() {}
	/**
	 * Destructor
	 */
	virtual ~domAnimation() { daeElement::deleteCMDataArray(_CMData); }
	/**
	 * Overloaded assignment operator
	 */
	virtual domAnimation &operator=( const domAnimation &cpy ) { (void)cpy; return *this; }

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
