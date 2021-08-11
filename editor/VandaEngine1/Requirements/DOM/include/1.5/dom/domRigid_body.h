#ifndef __domRigid_body_h__
#define __domRigid_body_h__

#include <dae/daeDocument.h>
#include <dom/domTypes.h>
#include <dom/domElements.h>

#include <dom/domTargetable_float.h>
#include <dom/domTranslate.h>
#include <dom/domRotate.h>
#include <dom/domTargetable_float3.h>
#include <dom/domInstance_physics_material.h>
#include <dom/domPhysics_material.h>
#include <dom/domInstance_geometry.h>
#include <dom/domPlane.h>
#include <dom/domBox.h>
#include <dom/domSphere.h>
#include <dom/domCylinder.h>
#include <dom/domCapsule.h>
#include <dom/domExtra.h>
#include <dom/domTechnique.h>
class DAE;

/**
 * This element allows for describing simulated bodies that do not deform.
 * These bodies may or may  not be connected by constraints (hinge, ball-joint
 * etc.).  Rigid-bodies, constraints etc. are  encapsulated in physics_model
 * elements to allow for instantiating complex models.
 */
class domRigid_body : public daeElement
{
public:
	virtual COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::RIGID_BODY; }
	static daeInt ID() { return 396; }
	virtual daeInt typeID() const { return ID(); }
public:
	class domTechnique_common;

	typedef daeSmartRef<domTechnique_common> domTechnique_commonRef;
	typedef daeTArray<domTechnique_commonRef> domTechnique_common_Array;

/**
 * The technique_common element specifies the rigid_body information for the
 * common profile which all  COLLADA implementations need to support.
 */
	class domTechnique_common : public daeElement
	{
	public:
		virtual COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::TECHNIQUE_COMMON; }
		static daeInt ID() { return 397; }
		virtual daeInt typeID() const { return ID(); }
	public:
		class domDynamic;

		typedef daeSmartRef<domDynamic> domDynamicRef;
		typedef daeTArray<domDynamicRef> domDynamic_Array;

/**
 * If false, the rigid_body is not moveable
 */
		class domDynamic : public daeElement
		{
		public:
			virtual COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::DYNAMIC; }
			static daeInt ID() { return 398; }
			virtual daeInt typeID() const { return ID(); }
		protected:  // Attribute
/**
 *  The sid attribute is a text string value containing the sub-identifier
 * of this element.  This value must be unique within the scope of the parent
 * element. Optional attribute. 
 */
			domSid attrSid;


		public:	//Accessors and Mutators
			/**
			 * Gets the sid attribute.
			 * @return Returns a domSid of the sid attribute.
			 */
			domSid getSid() const { return attrSid; }
			/**
			 * Sets the sid attribute.
			 * @param atSid The new value for the sid attribute.
			 */
			void setSid( domSid atSid ) { *(daeStringRef*)&attrSid = atSid; _validAttributeArray[0] = true; }

			/**
			 * Gets the value of this element.
			 * @return a xsBoolean of the value.
			 */
			xsBoolean& getValue() { return _value; }
			/**
			 * Sets the _value of this element.
			 * @param val The new value for this element.
			 */
			void setValue( const xsBoolean& val ) { _value = val; }

		protected:  // Value
			/**
			 * The xsBoolean value of the text data of this element. 
			 */
			xsBoolean _value;
		protected:
			/**
			 * Constructor
			 */
			domDynamic(DAE& dae) : daeElement(dae), attrSid(), _value() {}
			/**
			 * Destructor
			 */
			virtual ~domDynamic() {}
			/**
			 * Overloaded assignment operator
			 */
			virtual domDynamic &operator=( const domDynamic &cpy ) { (void)cpy; return *this; }

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

		class domMass_frame;

		typedef daeSmartRef<domMass_frame> domMass_frameRef;
		typedef daeTArray<domMass_frameRef> domMass_frame_Array;

/**
 * Defines the center and orientation of mass of the rigid-body relative to
 * the local origin of the  "root" shape.This makes the off-diagonal elements
 * of the inertia tensor (products of inertia) all  0 and allows us to just
 * store the diagonal elements (moments of inertia).
 */
		class domMass_frame : public daeElement
		{
		public:
			virtual COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::MASS_FRAME; }
			static daeInt ID() { return 399; }
			virtual daeInt typeID() const { return ID(); }

		protected:  // Elements
			domTranslate_Array elemTranslate_array;
			domRotate_Array elemRotate_array;
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
			 * Gets the translate element array.
			 * @return Returns a reference to the array of translate elements.
			 */
			domTranslate_Array &getTranslate_array() { return elemTranslate_array; }
			/**
			 * Gets the translate element array.
			 * @return Returns a constant reference to the array of translate elements.
			 */
			const domTranslate_Array &getTranslate_array() const { return elemTranslate_array; }
			/**
			 * Gets the rotate element array.
			 * @return Returns a reference to the array of rotate elements.
			 */
			domRotate_Array &getRotate_array() { return elemRotate_array; }
			/**
			 * Gets the rotate element array.
			 * @return Returns a constant reference to the array of rotate elements.
			 */
			const domRotate_Array &getRotate_array() const { return elemRotate_array; }
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
			domMass_frame(DAE& dae) : daeElement(dae), elemTranslate_array(), elemRotate_array() {}
			/**
			 * Destructor
			 */
			virtual ~domMass_frame() { daeElement::deleteCMDataArray(_CMData); }
			/**
			 * Overloaded assignment operator
			 */
			virtual domMass_frame &operator=( const domMass_frame &cpy ) { (void)cpy; return *this; }

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

		class domShape;

		typedef daeSmartRef<domShape> domShapeRef;
		typedef daeTArray<domShapeRef> domShape_Array;

/**
 * This element allows for describing components of a rigid_body.
 */
		class domShape : public daeElement
		{
		public:
			virtual COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::SHAPE; }
			static daeInt ID() { return 400; }
			virtual daeInt typeID() const { return ID(); }
		public:
			class domHollow;

			typedef daeSmartRef<domHollow> domHollowRef;
			typedef daeTArray<domHollowRef> domHollow_Array;

/**
 * If true, the mass is distributed along the surface of the shape
 */
			class domHollow : public daeElement
			{
			public:
				virtual COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::HOLLOW; }
				static daeInt ID() { return 401; }
				virtual daeInt typeID() const { return ID(); }
			protected:  // Attribute
/**
 *  The sid attribute is a text string value containing the sub-identifier
 * of this element.  This value must be unique within the scope of the parent
 * element. Optional attribute. 
 */
				domSid attrSid;


			public:	//Accessors and Mutators
				/**
				 * Gets the sid attribute.
				 * @return Returns a domSid of the sid attribute.
				 */
				domSid getSid() const { return attrSid; }
				/**
				 * Sets the sid attribute.
				 * @param atSid The new value for the sid attribute.
				 */
				void setSid( domSid atSid ) { *(daeStringRef*)&attrSid = atSid; _validAttributeArray[0] = true; }

				/**
				 * Gets the value of this element.
				 * @return a xsBoolean of the value.
				 */
				xsBoolean& getValue() { return _value; }
				/**
				 * Sets the _value of this element.
				 * @param val The new value for this element.
				 */
				void setValue( const xsBoolean& val ) { _value = val; }

			protected:  // Value
				/**
				 * The xsBoolean value of the text data of this element. 
				 */
				xsBoolean _value;
			protected:
				/**
				 * Constructor
				 */
				domHollow(DAE& dae) : daeElement(dae), attrSid(), _value() {}
				/**
				 * Destructor
				 */
				virtual ~domHollow() {}
				/**
				 * Overloaded assignment operator
				 */
				virtual domHollow &operator=( const domHollow &cpy ) { (void)cpy; return *this; }

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
 * If true, the mass is distributed along the surface of the shape @see domHollow
 */
			domHollowRef elemHollow;
/**
 * The mass of the shape. @see domMass
 */
			domTargetable_floatRef elemMass;
/**
 * The density of the shape. @see domDensity
 */
			domTargetable_floatRef elemDensity;
/**
 * References a physics_material for the shape. @see domInstance_physics_material
 */
			domInstance_physics_materialRef elemInstance_physics_material;
/**
 * Defines a physics_material for the shape. @see domPhysics_material
 */
			domPhysics_materialRef elemPhysics_material;
/**
 * Instances a geometry to use to define this shape. @see domInstance_geometry
 */
			domInstance_geometryRef elemInstance_geometry;
/**
 * Defines a plane to use for this shape. @see domPlane
 */
			domPlaneRef elemPlane;
/**
 * Defines a box to use for this shape. @see domBox
 */
			domBoxRef elemBox;
/**
 * Defines a sphere to use for this shape. @see domSphere
 */
			domSphereRef elemSphere;
/**
 * Defines a cyliner to use for this shape. @see domCylinder
 */
			domCylinderRef elemCylinder;
/**
 * Defines a capsule to use for this shape. @see domCapsule
 */
			domCapsuleRef elemCapsule;
/**
 * Allows a tranformation for the shape. @see domTranslate
 */
			domTranslate_Array elemTranslate_array;
/**
 * Allows a tranformation for the shape. @see domRotate
 */
			domRotate_Array elemRotate_array;
/**
 * The extra element may appear any number of times. @see domExtra
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
			 * Gets the hollow element.
			 * @return a daeSmartRef to the hollow element.
			 */
			const domHollowRef getHollow() const { return elemHollow; }
			/**
			 * Gets the mass element.
			 * @return a daeSmartRef to the mass element.
			 */
			const domTargetable_floatRef getMass() const { return elemMass; }
			/**
			 * Gets the density element.
			 * @return a daeSmartRef to the density element.
			 */
			const domTargetable_floatRef getDensity() const { return elemDensity; }
			/**
			 * Gets the instance_physics_material element.
			 * @return a daeSmartRef to the instance_physics_material element.
			 */
			const domInstance_physics_materialRef getInstance_physics_material() const { return elemInstance_physics_material; }
			/**
			 * Gets the physics_material element.
			 * @return a daeSmartRef to the physics_material element.
			 */
			const domPhysics_materialRef getPhysics_material() const { return elemPhysics_material; }
			/**
			 * Gets the instance_geometry element.
			 * @return a daeSmartRef to the instance_geometry element.
			 */
			const domInstance_geometryRef getInstance_geometry() const { return elemInstance_geometry; }
			/**
			 * Gets the plane element.
			 * @return a daeSmartRef to the plane element.
			 */
			const domPlaneRef getPlane() const { return elemPlane; }
			/**
			 * Gets the box element.
			 * @return a daeSmartRef to the box element.
			 */
			const domBoxRef getBox() const { return elemBox; }
			/**
			 * Gets the sphere element.
			 * @return a daeSmartRef to the sphere element.
			 */
			const domSphereRef getSphere() const { return elemSphere; }
			/**
			 * Gets the cylinder element.
			 * @return a daeSmartRef to the cylinder element.
			 */
			const domCylinderRef getCylinder() const { return elemCylinder; }
			/**
			 * Gets the capsule element.
			 * @return a daeSmartRef to the capsule element.
			 */
			const domCapsuleRef getCapsule() const { return elemCapsule; }
			/**
			 * Gets the translate element array.
			 * @return Returns a reference to the array of translate elements.
			 */
			domTranslate_Array &getTranslate_array() { return elemTranslate_array; }
			/**
			 * Gets the translate element array.
			 * @return Returns a constant reference to the array of translate elements.
			 */
			const domTranslate_Array &getTranslate_array() const { return elemTranslate_array; }
			/**
			 * Gets the rotate element array.
			 * @return Returns a reference to the array of rotate elements.
			 */
			domRotate_Array &getRotate_array() { return elemRotate_array; }
			/**
			 * Gets the rotate element array.
			 * @return Returns a constant reference to the array of rotate elements.
			 */
			const domRotate_Array &getRotate_array() const { return elemRotate_array; }
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
			domShape(DAE& dae) : daeElement(dae), elemHollow(), elemMass(), elemDensity(), elemInstance_physics_material(), elemPhysics_material(), elemInstance_geometry(), elemPlane(), elemBox(), elemSphere(), elemCylinder(), elemCapsule(), elemTranslate_array(), elemRotate_array(), elemExtra_array() {}
			/**
			 * Destructor
			 */
			virtual ~domShape() { daeElement::deleteCMDataArray(_CMData); }
			/**
			 * Overloaded assignment operator
			 */
			virtual domShape &operator=( const domShape &cpy ) { (void)cpy; return *this; }

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
 * If false, the rigid_body is not moveable @see domDynamic
 */
		domDynamicRef elemDynamic;
/**
 * The total mass of the rigid-body @see domMass
 */
		domTargetable_floatRef elemMass;
/**
 * Defines the center and orientation of mass of the rigid-body relative to
 * the local origin of the  "root" shape.This makes the off-diagonal elements
 * of the inertia tensor (products of inertia) all  0 and allows us to just
 * store the diagonal elements (moments of inertia). @see domMass_frame
 */
		domMass_frameRef elemMass_frame;
/**
 * float3 - The diagonal elements of the inertia tensor (moments of inertia),
 * which is represented  in the local frame of the center of mass. See above.
 * @see domInertia
 */
		domTargetable_float3Ref elemInertia;
/**
 * References a physics_material for the rigid_body. @see domInstance_physics_material
 */
		domInstance_physics_materialRef elemInstance_physics_material;
/**
 * Defines a physics_material for the rigid_body. @see domPhysics_material
 */
		domPhysics_materialRef elemPhysics_material;
/**
 * This element allows for describing components of a rigid_body. @see domShape
 */
		domShape_Array elemShape_array;
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
		 * Gets the dynamic element.
		 * @return a daeSmartRef to the dynamic element.
		 */
		const domDynamicRef getDynamic() const { return elemDynamic; }
		/**
		 * Gets the mass element.
		 * @return a daeSmartRef to the mass element.
		 */
		const domTargetable_floatRef getMass() const { return elemMass; }
		/**
		 * Gets the mass_frame element.
		 * @return a daeSmartRef to the mass_frame element.
		 */
		const domMass_frameRef getMass_frame() const { return elemMass_frame; }
		/**
		 * Gets the inertia element.
		 * @return a daeSmartRef to the inertia element.
		 */
		const domTargetable_float3Ref getInertia() const { return elemInertia; }
		/**
		 * Gets the instance_physics_material element.
		 * @return a daeSmartRef to the instance_physics_material element.
		 */
		const domInstance_physics_materialRef getInstance_physics_material() const { return elemInstance_physics_material; }
		/**
		 * Gets the physics_material element.
		 * @return a daeSmartRef to the physics_material element.
		 */
		const domPhysics_materialRef getPhysics_material() const { return elemPhysics_material; }
		/**
		 * Gets the shape element array.
		 * @return Returns a reference to the array of shape elements.
		 */
		domShape_Array &getShape_array() { return elemShape_array; }
		/**
		 * Gets the shape element array.
		 * @return Returns a constant reference to the array of shape elements.
		 */
		const domShape_Array &getShape_array() const { return elemShape_array; }
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
		domTechnique_common(DAE& dae) : daeElement(dae), elemDynamic(), elemMass(), elemMass_frame(), elemInertia(), elemInstance_physics_material(), elemPhysics_material(), elemShape_array() {}
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
	xsID attrId;
/**
 *  The sid attribute is a text string value containing the sub-identifier
 * of this element. This  value must be unique within the scope of the parent
 * element. Optional attribute. 
 */
	domSid attrSid;
/**
 *  The name attribute is the text string name of this element. Optional attribute.
 */
	xsToken attrName;

protected:  // Elements
/**
 * The technique_common element specifies the rigid_body information for the
 * common profile which all  COLLADA implementations need to support. @see
 * domTechnique_common
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
	 * Gets the sid attribute.
	 * @return Returns a domSid of the sid attribute.
	 */
	domSid getSid() const { return attrSid; }
	/**
	 * Sets the sid attribute.
	 * @param atSid The new value for the sid attribute.
	 */
	void setSid( domSid atSid ) { *(daeStringRef*)&attrSid = atSid;}

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
	domRigid_body(DAE& dae) : daeElement(dae), attrId(), attrSid(), attrName(), elemTechnique_common(), elemTechnique_array(), elemExtra_array() {}
	/**
	 * Destructor
	 */
	virtual ~domRigid_body() {}
	/**
	 * Overloaded assignment operator
	 */
	virtual domRigid_body &operator=( const domRigid_body &cpy ) { (void)cpy; return *this; }

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
