/*
* Copyright 2006 Sony Computer Entertainment Inc.
*
* Licensed under the MIT Open Source License, for details please see license.txt or the website
* http://www.opensource.org/licenses/mit-license.php
*
*/ 

#ifndef __domSpline_h__
#define __domSpline_h__

#include <dae/daeDocument.h>
#include <dom/domTypes.h>
#include <dom/domElements.h>

#include <dom/domSource.h>
#include <dom/domExtra.h>
#include <dom/domInputLocal.h>
class DAE;

/**
 * The spline element contains control vertex information sufficient to describe
 * basic splines.
 */
class domSpline : public daeElement
{
public:
	virtual COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::SPLINE; }
	static daeInt ID() { return 615; }
	virtual daeInt typeID() const { return ID(); }
public:
	class domControl_vertices;

	typedef daeSmartRef<domControl_vertices> domControl_verticesRef;
	typedef daeTArray<domControl_verticesRef> domControl_vertices_Array;

/**
 * The control vertices element  must occur  exactly one time. It is used
 * to describe the CVs of the spline.
 */
	class domControl_vertices : public daeElement
	{
	public:
		virtual COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::CONTROL_VERTICES; }
		static daeInt ID() { return 616; }
		virtual daeInt typeID() const { return ID(); }

	protected:  // Elements
/**
 * The input element must occur at least one time. These inputs are local
 * inputs. @see domInput
 */
		domInputLocal_Array elemInput_array;
/**
 *  The extra element may appear any number of times.  @see domExtra
 */
		domExtra_Array elemExtra_array;

	public:	//Accessors and Mutators
		/**
		 * Gets the input element array.
		 * @return Returns a reference to the array of input elements.
		 */
		domInputLocal_Array &getInput_array() { return elemInput_array; }
		/**
		 * Gets the input element array.
		 * @return Returns a constant reference to the array of input elements.
		 */
		const domInputLocal_Array &getInput_array() const { return elemInput_array; }
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
		domControl_vertices(DAE& dae) : daeElement(dae), elemInput_array(), elemExtra_array() {}
		/**
		 * Destructor
		 */
		virtual ~domControl_vertices() {}
		/**
		 * Overloaded assignment operator
		 */
		virtual domControl_vertices &operator=( const domControl_vertices &cpy ) { (void)cpy; return *this; }

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


protected:  // Attribute
	domBool attrClosed;

protected:  // Elements
/**
 *  The mesh element must contain one or more source elements.  @see domSource
 */
	domSource_Array elemSource_array;
/**
 * The control vertices element  must occur  exactly one time. It is used
 * to describe the CVs of the spline. @see domControl_vertices
 */
	domControl_verticesRef elemControl_vertices;
/**
 *  The extra element may appear any number of times.  @see domExtra
 */
	domExtra_Array elemExtra_array;

public:	//Accessors and Mutators
	/**
	 * Gets the closed attribute.
	 * @return Returns a domBool of the closed attribute.
	 */
	domBool getClosed() const { return attrClosed; }
	/**
	 * Sets the closed attribute.
	 * @param atClosed The new value for the closed attribute.
	 */
	void setClosed( domBool atClosed ) { attrClosed = atClosed; _validAttributeArray[0] = true; }

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
	 * Gets the control_vertices element.
	 * @return a daeSmartRef to the control_vertices element.
	 */
	const domControl_verticesRef getControl_vertices() const { return elemControl_vertices; }
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
	domSpline(DAE& dae) : daeElement(dae), attrClosed(), elemSource_array(), elemControl_vertices(), elemExtra_array() {}
	/**
	 * Destructor
	 */
	virtual ~domSpline() {}
	/**
	 * Overloaded assignment operator
	 */
	virtual domSpline &operator=( const domSpline &cpy ) { (void)cpy; return *this; }

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
