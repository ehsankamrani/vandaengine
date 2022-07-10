#ifndef __domLight_h__
#define __domLight_h__

#include <dae/daeDocument.h>
#include <dom/domTypes.h>
#include <dom/domElements.h>

#include <dom/domAsset.h>
#include <dom/domTargetable_float3.h>
#include <dom/domTargetable_float.h>
#include <dom/domTechnique.h>
#include <dom/domExtra.h>
class DAE;

/**
 * The light element declares a light source that illuminates the scene. Light
 * sources have many different properties and radiate light in many different
 * patterns and  frequencies.
 */
class domLight : public daeElement
{
public:
	virtual COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::LIGHT; }
	static daeInt ID() { return 92; }
	virtual daeInt typeID() const { return ID(); }
public:
	class domTechnique_common;

	typedef daeSmartRef<domTechnique_common> domTechnique_commonRef;
	typedef daeTArray<domTechnique_commonRef> domTechnique_common_Array;

/**
 * The technique_common element specifies the light information for the common
 * profile which all  COLLADA implementations need to support.
 */
	class domTechnique_common : public daeElement
	{
	public:
		virtual COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::TECHNIQUE_COMMON; }
		static daeInt ID() { return 93; }
		virtual daeInt typeID() const { return ID(); }
	public:
		class domAmbient;

		typedef daeSmartRef<domAmbient> domAmbientRef;
		typedef daeTArray<domAmbientRef> domAmbient_Array;

/**
 * The ambient element declares the parameters required to describe an ambient
 * light source.   An ambient light is one that lights everything evenly,
 * regardless of location or orientation.
 */
		class domAmbient : public daeElement
		{
		public:
			virtual COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::AMBIENT; }
			static daeInt ID() { return 94; }
			virtual daeInt typeID() const { return ID(); }

		protected:  // Element
/**
 * The color element contains three floating point numbers specifying the
 * color of the light. The color element must occur exactly once. @see domColor
 */
			domTargetable_float3Ref elemColor;

		public:	//Accessors and Mutators
			/**
			 * Gets the color element.
			 * @return a daeSmartRef to the color element.
			 */
			const domTargetable_float3Ref getColor() const { return elemColor; }
		protected:
			/**
			 * Constructor
			 */
			domAmbient(DAE& dae) : daeElement(dae), elemColor() {}
			/**
			 * Destructor
			 */
			virtual ~domAmbient() {}
			/**
			 * Overloaded assignment operator
			 */
			virtual domAmbient &operator=( const domAmbient &cpy ) { (void)cpy; return *this; }

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

		class domDirectional;

		typedef daeSmartRef<domDirectional> domDirectionalRef;
		typedef daeTArray<domDirectionalRef> domDirectional_Array;

/**
 * The directional element declares the parameters required to describe a
 * directional light source.   A directional light is one that lights everything
 * from the same direction, regardless of location.   The light's default
 * direction vector in local coordinates is [0,0,-1], pointing down the -Z
 * axis.  The actual direction of the light is defined by the transform of
 * the node where the light is  instantiated.
 */
		class domDirectional : public daeElement
		{
		public:
			virtual COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::DIRECTIONAL; }
			static daeInt ID() { return 95; }
			virtual daeInt typeID() const { return ID(); }

		protected:  // Element
/**
 * The color element contains three floating point numbers specifying the
 * color of the light. The color element must occur exactly once. @see domColor
 */
			domTargetable_float3Ref elemColor;

		public:	//Accessors and Mutators
			/**
			 * Gets the color element.
			 * @return a daeSmartRef to the color element.
			 */
			const domTargetable_float3Ref getColor() const { return elemColor; }
		protected:
			/**
			 * Constructor
			 */
			domDirectional(DAE& dae) : daeElement(dae), elemColor() {}
			/**
			 * Destructor
			 */
			virtual ~domDirectional() {}
			/**
			 * Overloaded assignment operator
			 */
			virtual domDirectional &operator=( const domDirectional &cpy ) { (void)cpy; return *this; }

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

		class domPoint;

		typedef daeSmartRef<domPoint> domPointRef;
		typedef daeTArray<domPointRef> domPoint_Array;

/**
 * The point element declares the parameters required to describe a point
 * light source.  A point light  source radiates light in all directions from
 * a known location in space. The intensity of a point  light source is attenuated
 * as the distance to the light source increases. The position of the light
 * is defined by the transform of the node in which it is instantiated.
 */
		class domPoint : public daeElement
		{
		public:
			virtual COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::POINT; }
			static daeInt ID() { return 96; }
			virtual daeInt typeID() const { return ID(); }

		protected:  // Elements
/**
 * The color element contains three floating point numbers specifying the
 * color of the light. The color element must occur exactly once. @see domColor
 */
			domTargetable_float3Ref elemColor;
/**
 * The constant_attenuation is used to calculate the total attenuation of
 * this light given a distance.  The equation used is A = constant_attenuation
 * + Dist*linear_attenuation + Dist^2*quadratic_attenuation. @see domConstant_attenuation
 */
			domTargetable_floatRef elemConstant_attenuation;
/**
 * The linear_attenuation is used to calculate the total attenuation of this
 * light given a distance.  The equation used is A = constant_attenuation
 * + Dist*linear_attenuation + Dist^2*quadratic_attenuation. @see domLinear_attenuation
 */
			domTargetable_floatRef elemLinear_attenuation;
/**
 * The quadratic_attenuation is used to calculate the total attenuation of
 * this light given a distance.  The equation used is A = constant_attenuation
 * + Dist*linear_attenuation + Dist^2*quadratic_attenuation. @see domQuadratic_attenuation
 */
			domTargetable_floatRef elemQuadratic_attenuation;

		public:	//Accessors and Mutators
			/**
			 * Gets the color element.
			 * @return a daeSmartRef to the color element.
			 */
			const domTargetable_float3Ref getColor() const { return elemColor; }
			/**
			 * Gets the constant_attenuation element.
			 * @return a daeSmartRef to the constant_attenuation element.
			 */
			const domTargetable_floatRef getConstant_attenuation() const { return elemConstant_attenuation; }
			/**
			 * Gets the linear_attenuation element.
			 * @return a daeSmartRef to the linear_attenuation element.
			 */
			const domTargetable_floatRef getLinear_attenuation() const { return elemLinear_attenuation; }
			/**
			 * Gets the quadratic_attenuation element.
			 * @return a daeSmartRef to the quadratic_attenuation element.
			 */
			const domTargetable_floatRef getQuadratic_attenuation() const { return elemQuadratic_attenuation; }
		protected:
			/**
			 * Constructor
			 */
			domPoint(DAE& dae) : daeElement(dae), elemColor(), elemConstant_attenuation(), elemLinear_attenuation(), elemQuadratic_attenuation() {}
			/**
			 * Destructor
			 */
			virtual ~domPoint() {}
			/**
			 * Overloaded assignment operator
			 */
			virtual domPoint &operator=( const domPoint &cpy ) { (void)cpy; return *this; }

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

		class domSpot;

		typedef daeSmartRef<domSpot> domSpotRef;
		typedef daeTArray<domSpotRef> domSpot_Array;

/**
 * The spot element declares the parameters required to describe a spot light
 * source.  A spot light  source radiates light in one direction from a known
 * location in space. The light radiates from  the spot light source in a
 * cone shape. The intensity of the light is attenuated as the radiation 
 * angle increases away from the direction of the light source. The intensity
 * of a spot light source  is also attenuated as the distance to the light
 * source increases. The position of the light is  defined by the transform
 * of the node in which it is instantiated. The light's default direction
 * vector in local coordinates is [0,0,-1], pointing down the -Z axis. The
 * actual direction of the  light is defined by the transform of the node
 * where the light is instantiated.
 */
		class domSpot : public daeElement
		{
		public:
			virtual COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::SPOT; }
			static daeInt ID() { return 97; }
			virtual daeInt typeID() const { return ID(); }

		protected:  // Elements
/**
 * The color element contains three floating point numbers specifying the
 * color of the light. The color element must occur exactly once. @see domColor
 */
			domTargetable_float3Ref elemColor;
/**
 * The constant_attenuation is used to calculate the total attenuation of
 * this light given a distance.  The equation used is A = constant_attenuation
 * + Dist*linear_attenuation + Dist^2*quadratic_attenuation. @see domConstant_attenuation
 */
			domTargetable_floatRef elemConstant_attenuation;
/**
 * The linear_attenuation is used to calculate the total attenuation of this
 * light given a distance.  The equation used is A = constant_attenuation
 * + Dist*linear_attenuation + Dist^2*quadratic_attenuation. @see domLinear_attenuation
 */
			domTargetable_floatRef elemLinear_attenuation;
/**
 * The quadratic_attenuation is used to calculate the total attenuation of
 * this light given a distance.  The equation used is A = constant_attenuation
 * + Dist*linear_attenuation + Dist^2*quadratic_attenuation. @see domQuadratic_attenuation
 */
			domTargetable_floatRef elemQuadratic_attenuation;
/**
 * The falloff_angle is used to specify the amount of attenuation based on
 * the direction of the light. @see domFalloff_angle
 */
			domTargetable_floatRef elemFalloff_angle;
/**
 * The falloff_exponent is used to specify the amount of attenuation based
 * on the direction of the light. @see domFalloff_exponent
 */
			domTargetable_floatRef elemFalloff_exponent;

		public:	//Accessors and Mutators
			/**
			 * Gets the color element.
			 * @return a daeSmartRef to the color element.
			 */
			const domTargetable_float3Ref getColor() const { return elemColor; }
			/**
			 * Gets the constant_attenuation element.
			 * @return a daeSmartRef to the constant_attenuation element.
			 */
			const domTargetable_floatRef getConstant_attenuation() const { return elemConstant_attenuation; }
			/**
			 * Gets the linear_attenuation element.
			 * @return a daeSmartRef to the linear_attenuation element.
			 */
			const domTargetable_floatRef getLinear_attenuation() const { return elemLinear_attenuation; }
			/**
			 * Gets the quadratic_attenuation element.
			 * @return a daeSmartRef to the quadratic_attenuation element.
			 */
			const domTargetable_floatRef getQuadratic_attenuation() const { return elemQuadratic_attenuation; }
			/**
			 * Gets the falloff_angle element.
			 * @return a daeSmartRef to the falloff_angle element.
			 */
			const domTargetable_floatRef getFalloff_angle() const { return elemFalloff_angle; }
			/**
			 * Gets the falloff_exponent element.
			 * @return a daeSmartRef to the falloff_exponent element.
			 */
			const domTargetable_floatRef getFalloff_exponent() const { return elemFalloff_exponent; }
		protected:
			/**
			 * Constructor
			 */
			domSpot(DAE& dae) : daeElement(dae), elemColor(), elemConstant_attenuation(), elemLinear_attenuation(), elemQuadratic_attenuation(), elemFalloff_angle(), elemFalloff_exponent() {}
			/**
			 * Destructor
			 */
			virtual ~domSpot() {}
			/**
			 * Overloaded assignment operator
			 */
			virtual domSpot &operator=( const domSpot &cpy ) { (void)cpy; return *this; }

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
/**
 * The ambient element declares the parameters required to describe an ambient
 * light source.   An ambient light is one that lights everything evenly,
 * regardless of location or orientation. @see domAmbient
 */
		domAmbientRef elemAmbient;
/**
 * The directional element declares the parameters required to describe a
 * directional light source.   A directional light is one that lights everything
 * from the same direction, regardless of location.   The light's default
 * direction vector in local coordinates is [0,0,-1], pointing down the -Z
 * axis.  The actual direction of the light is defined by the transform of
 * the node where the light is  instantiated. @see domDirectional
 */
		domDirectionalRef elemDirectional;
/**
 * The point element declares the parameters required to describe a point
 * light source.  A point light  source radiates light in all directions from
 * a known location in space. The intensity of a point  light source is attenuated
 * as the distance to the light source increases. The position of the light
 * is defined by the transform of the node in which it is instantiated. @see
 * domPoint
 */
		domPointRef elemPoint;
/**
 * The spot element declares the parameters required to describe a spot light
 * source.  A spot light  source radiates light in one direction from a known
 * location in space. The light radiates from  the spot light source in a
 * cone shape. The intensity of the light is attenuated as the radiation 
 * angle increases away from the direction of the light source. The intensity
 * of a spot light source  is also attenuated as the distance to the light
 * source increases. The position of the light is  defined by the transform
 * of the node in which it is instantiated. The light's default direction
 * vector in local coordinates is [0,0,-1], pointing down the -Z axis. The
 * actual direction of the  light is defined by the transform of the node
 * where the light is instantiated. @see domSpot
 */
		domSpotRef elemSpot;
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
		 * Gets the ambient element.
		 * @return a daeSmartRef to the ambient element.
		 */
		const domAmbientRef getAmbient() const { return elemAmbient; }
		/**
		 * Gets the directional element.
		 * @return a daeSmartRef to the directional element.
		 */
		const domDirectionalRef getDirectional() const { return elemDirectional; }
		/**
		 * Gets the point element.
		 * @return a daeSmartRef to the point element.
		 */
		const domPointRef getPoint() const { return elemPoint; }
		/**
		 * Gets the spot element.
		 * @return a daeSmartRef to the spot element.
		 */
		const domSpotRef getSpot() const { return elemSpot; }
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
		domTechnique_common(DAE& dae) : daeElement(dae), elemAmbient(), elemDirectional(), elemPoint(), elemSpot() {}
		/**
		 * Destructor
		 */
		virtual ~domTechnique_common() { daeElement::deleteCMDataArray(_CMData); }
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
 * Optional attribute. 
 */
	xsID attrId;
/**
 *  The name attribute is the text string name of this element. Optional attribute.
 */
	xsToken attrName;

protected:  // Elements
/**
 * The light element may contain an asset element. @see domAsset
 */
	domAssetRef elemAsset;
/**
 * The technique_common element specifies the light information for the common
 * profile which all  COLLADA implementations need to support. @see domTechnique_common
 */
	domTechnique_commonRef elemTechnique_common;
/**
 * This element may contain any number of non-common profile techniques. @see
 * domTechnique
 */
	domTechnique_Array elemTechnique_array;
/**
 * The extra element may appear any number of times. @see domExtra
 */
	domExtra_Array elemExtra_array;

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
	void setId( xsID atId ) { *(daeStringRef*)&attrId = atId;
		if( _document != NULL ) _document->changeElementID( this, attrId );
	}

	/**
	 * Gets the name attribute.
	 * @return Returns a xsToken of the name attribute.
	 */
	xsToken getName() const { return attrName; }
	/**
	 * Sets the name attribute.
	 * @param atName The new value for the name attribute.
	 */
	void setName( xsToken atName ) { *(daeStringRef*)&attrName = atName;}

	/**
	 * Gets the asset element.
	 * @return a daeSmartRef to the asset element.
	 */
	const domAssetRef getAsset() const { return elemAsset; }
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
	domLight(DAE& dae) : daeElement(dae), attrId(), attrName(), elemAsset(), elemTechnique_common(), elemTechnique_array(), elemExtra_array() {}
	/**
	 * Destructor
	 */
	virtual ~domLight() {}
	/**
	 * Overloaded assignment operator
	 */
	virtual domLight &operator=( const domLight &cpy ) { (void)cpy; return *this; }

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
