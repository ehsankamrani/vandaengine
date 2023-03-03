/*
* Copyright 2006 Sony Computer Entertainment Inc.
*
* Licensed under the MIT Open Source License, for details please see license.txt or the website
* http://www.opensource.org/licenses/mit-license.php
*
*/ 

#ifndef __domCOLLADA_h__
#define __domCOLLADA_h__

#include <dae/daeDocument.h>
#include <dom/domTypes.h>
#include <dom/domElements.h>

#include <dom/domAsset.h>
#include <dom/domLibrary_animations.h>
#include <dom/domLibrary_animation_clips.h>
#include <dom/domLibrary_cameras.h>
#include <dom/domLibrary_controllers.h>
#include <dom/domLibrary_geometries.h>
#include <dom/domLibrary_effects.h>
#include <dom/domLibrary_force_fields.h>
#include <dom/domLibrary_images.h>
#include <dom/domLibrary_lights.h>
#include <dom/domLibrary_materials.h>
#include <dom/domLibrary_nodes.h>
#include <dom/domLibrary_physics_materials.h>
#include <dom/domLibrary_physics_models.h>
#include <dom/domLibrary_physics_scenes.h>
#include <dom/domLibrary_visual_scenes.h>
#include <dom/domExtra.h>
#include <dom/domInstanceWithExtra.h>
class DAE;

/**
 * The COLLADA element declares the root of the document that comprises some
 * of the content  in the COLLADA schema.
 */
class domCOLLADA : public daeElement
{
public:
	virtual COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::COLLADA; }
	static daeInt ID() { return 602; }
	virtual daeInt typeID() const { return ID(); }
public:
	class domScene;

	typedef daeSmartRef<domScene> domSceneRef;
	typedef daeTArray<domSceneRef> domScene_Array;

/**
 * The scene embodies the entire set of information that can be visualized
 * from the  contents of a COLLADA resource. The scene element declares the
 * base of the scene  hierarchy or scene graph. The scene contains elements
 * that comprise much of the  visual and transformational information content
 * as created by the authoring tools.
 */
	class domScene : public daeElement
	{
	public:
		virtual COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::SCENE; }
		static daeInt ID() { return 603; }
		virtual daeInt typeID() const { return ID(); }

	protected:  // Elements
/**
 * The instance_physics_scene element declares the instantiation of a COLLADA
 * physics_scene resource. The instance_physics_scene element may appear any
 * number of times. @see domInstance_physics_scene
 */
		domInstanceWithExtra_Array elemInstance_physics_scene_array;
/**
 * The instance_visual_scene element declares the instantiation of a COLLADA
 * visual_scene resource. The instance_visual_scene element may only appear
 * once. @see domInstance_visual_scene
 */
		domInstanceWithExtraRef elemInstance_visual_scene;
/**
 *  The extra element may appear any number of times.  @see domExtra
 */
		domExtra_Array elemExtra_array;

	public:	//Accessors and Mutators
		/**
		 * Gets the instance_physics_scene element array.
		 * @return Returns a reference to the array of instance_physics_scene elements.
		 */
		domInstanceWithExtra_Array &getInstance_physics_scene_array() { return elemInstance_physics_scene_array; }
		/**
		 * Gets the instance_physics_scene element array.
		 * @return Returns a constant reference to the array of instance_physics_scene elements.
		 */
		const domInstanceWithExtra_Array &getInstance_physics_scene_array() const { return elemInstance_physics_scene_array; }
		/**
		 * Gets the instance_visual_scene element.
		 * @return a daeSmartRef to the instance_visual_scene element.
		 */
		const domInstanceWithExtraRef getInstance_visual_scene() const { return elemInstance_visual_scene; }
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
		domScene(DAE& dae) : daeElement(dae), elemInstance_physics_scene_array(), elemInstance_visual_scene(), elemExtra_array() {}
		/**
		 * Destructor
		 */
		virtual ~domScene() {}
		/**
		 * Overloaded assignment operator
		 */
		virtual domScene &operator=( const domScene &cpy ) { (void)cpy; return *this; }

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
	 * This element may specify its own xmlns.
	 */
	xsAnyURI attrXmlns;
/**
 *  The version attribute is the COLLADA schema revision with which the instance
 * document  conforms. Required Attribute. 
 */
	domVersionType attrVersion;
/**
 *  The xml:base attribute allows you to define the base URI for this COLLADA
 * document. See http://www.w3.org/TR/xmlbase/ for more information. 
 */
	xsAnyURI attrXml_base;

protected:  // Elements
/**
 *  The COLLADA element must contain an asset element.  @see domAsset
 */
	domAssetRef elemAsset;
/**
 *  The COLLADA element may contain any number of library_animations elements.
 * @see domLibrary_animations
 */
	domLibrary_animations_Array elemLibrary_animations_array;
/**
 *  The COLLADA element may contain any number of library_animation_clips
 * elements.  @see domLibrary_animation_clips
 */
	domLibrary_animation_clips_Array elemLibrary_animation_clips_array;
/**
 *  The COLLADA element may contain any number of library_cameras elements.
 * @see domLibrary_cameras
 */
	domLibrary_cameras_Array elemLibrary_cameras_array;
/**
 *  The COLLADA element may contain any number of library_controllerss elements.
 * @see domLibrary_controllers
 */
	domLibrary_controllers_Array elemLibrary_controllers_array;
/**
 *  The COLLADA element may contain any number of library_geometriess elements.
 * @see domLibrary_geometries
 */
	domLibrary_geometries_Array elemLibrary_geometries_array;
/**
 *  The COLLADA element may contain any number of library_effects elements.
 * @see domLibrary_effects
 */
	domLibrary_effects_Array elemLibrary_effects_array;
/**
 *  The COLLADA element may contain any number of library_force_fields elements.
 * @see domLibrary_force_fields
 */
	domLibrary_force_fields_Array elemLibrary_force_fields_array;
/**
 *  The COLLADA element may contain any number of library_images elements.
 * @see domLibrary_images
 */
	domLibrary_images_Array elemLibrary_images_array;
/**
 *  The COLLADA element may contain any number of library_lights elements.
 * @see domLibrary_lights
 */
	domLibrary_lights_Array elemLibrary_lights_array;
/**
 *  The COLLADA element may contain any number of library_materials elements.
 * @see domLibrary_materials
 */
	domLibrary_materials_Array elemLibrary_materials_array;
/**
 *  The COLLADA element may contain any number of library_nodes elements.
 * @see domLibrary_nodes
 */
	domLibrary_nodes_Array elemLibrary_nodes_array;
/**
 *  The COLLADA element may contain any number of library_materials elements.
 * @see domLibrary_physics_materials
 */
	domLibrary_physics_materials_Array elemLibrary_physics_materials_array;
/**
 *  The COLLADA element may contain any number of library_physics_models elements.
 * @see domLibrary_physics_models
 */
	domLibrary_physics_models_Array elemLibrary_physics_models_array;
/**
 *  The COLLADA element may contain any number of library_physics_scenes elements.
 * @see domLibrary_physics_scenes
 */
	domLibrary_physics_scenes_Array elemLibrary_physics_scenes_array;
/**
 *  The COLLADA element may contain any number of library_visual_scenes elements.
 * @see domLibrary_visual_scenes
 */
	domLibrary_visual_scenes_Array elemLibrary_visual_scenes_array;
/**
 * The scene embodies the entire set of information that can be visualized
 * from the  contents of a COLLADA resource. The scene element declares the
 * base of the scene  hierarchy or scene graph. The scene contains elements
 * that comprise much of the  visual and transformational information content
 * as created by the authoring tools. @see domScene
 */
	domSceneRef elemScene;
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
	 * Gets the xmlns attribute.
	 * @return Returns a xsAnyURI reference of the xmlns attribute.
	 */
	xsAnyURI &getXmlns() { return attrXmlns; }
	/**
	 * Gets the xmlns attribute.
	 * @return Returns a constant xsAnyURI reference of the xmlns attribute.
	 */
	const xsAnyURI &getXmlns() const { return attrXmlns; }
	/**
	 * Sets the xmlns attribute.
	 * @param xmlns The new value for the xmlns attribute.
	 */
	void setXmlns( const xsAnyURI &xmlns ) { attrXmlns = xmlns;
	 _validAttributeArray[0] = true; }

	/**
	 * Gets the version attribute.
	 * @return Returns a domVersionType of the version attribute.
	 */
	domVersionType getVersion() const { return attrVersion; }
	/**
	 * Sets the version attribute.
	 * @param atVersion The new value for the version attribute.
	 */
	void setVersion( domVersionType atVersion ) { attrVersion = atVersion; _validAttributeArray[1] = true; }

	/**
	 * Gets the xml_base attribute.
	 * @return Returns a xsAnyURI reference of the xml_base attribute.
	 */
	xsAnyURI &getXml_base() { return attrXml_base; }
	/**
	 * Gets the xml_base attribute.
	 * @return Returns a constant xsAnyURI reference of the xml_base attribute.
	 */
	const xsAnyURI &getXml_base() const { return attrXml_base; }
	/**
	 * Sets the xml_base attribute.
	 * @param atXml_base The new value for the xml_base attribute.
	 */
	void setXml_base( const xsAnyURI &atXml_base ) { attrXml_base = atXml_base; _validAttributeArray[2] = true; }
	/**
	 * Sets the xml_base attribute.
	 * @param atXml_base The new value for the xml_base attribute.
	 */
	void setXml_base( xsString atXml_base ) { attrXml_base = atXml_base; _validAttributeArray[2] = true; }

	/**
	 * Gets the asset element.
	 * @return a daeSmartRef to the asset element.
	 */
	const domAssetRef getAsset() const { return elemAsset; }
	/**
	 * Gets the library_animations element array.
	 * @return Returns a reference to the array of library_animations elements.
	 */
	domLibrary_animations_Array &getLibrary_animations_array() { return elemLibrary_animations_array; }
	/**
	 * Gets the library_animations element array.
	 * @return Returns a constant reference to the array of library_animations elements.
	 */
	const domLibrary_animations_Array &getLibrary_animations_array() const { return elemLibrary_animations_array; }
	/**
	 * Gets the library_animation_clips element array.
	 * @return Returns a reference to the array of library_animation_clips elements.
	 */
	domLibrary_animation_clips_Array &getLibrary_animation_clips_array() { return elemLibrary_animation_clips_array; }
	/**
	 * Gets the library_animation_clips element array.
	 * @return Returns a constant reference to the array of library_animation_clips elements.
	 */
	const domLibrary_animation_clips_Array &getLibrary_animation_clips_array() const { return elemLibrary_animation_clips_array; }
	/**
	 * Gets the library_cameras element array.
	 * @return Returns a reference to the array of library_cameras elements.
	 */
	domLibrary_cameras_Array &getLibrary_cameras_array() { return elemLibrary_cameras_array; }
	/**
	 * Gets the library_cameras element array.
	 * @return Returns a constant reference to the array of library_cameras elements.
	 */
	const domLibrary_cameras_Array &getLibrary_cameras_array() const { return elemLibrary_cameras_array; }
	/**
	 * Gets the library_controllers element array.
	 * @return Returns a reference to the array of library_controllers elements.
	 */
	domLibrary_controllers_Array &getLibrary_controllers_array() { return elemLibrary_controllers_array; }
	/**
	 * Gets the library_controllers element array.
	 * @return Returns a constant reference to the array of library_controllers elements.
	 */
	const domLibrary_controllers_Array &getLibrary_controllers_array() const { return elemLibrary_controllers_array; }
	/**
	 * Gets the library_geometries element array.
	 * @return Returns a reference to the array of library_geometries elements.
	 */
	domLibrary_geometries_Array &getLibrary_geometries_array() { return elemLibrary_geometries_array; }
	/**
	 * Gets the library_geometries element array.
	 * @return Returns a constant reference to the array of library_geometries elements.
	 */
	const domLibrary_geometries_Array &getLibrary_geometries_array() const { return elemLibrary_geometries_array; }
	/**
	 * Gets the library_effects element array.
	 * @return Returns a reference to the array of library_effects elements.
	 */
	domLibrary_effects_Array &getLibrary_effects_array() { return elemLibrary_effects_array; }
	/**
	 * Gets the library_effects element array.
	 * @return Returns a constant reference to the array of library_effects elements.
	 */
	const domLibrary_effects_Array &getLibrary_effects_array() const { return elemLibrary_effects_array; }
	/**
	 * Gets the library_force_fields element array.
	 * @return Returns a reference to the array of library_force_fields elements.
	 */
	domLibrary_force_fields_Array &getLibrary_force_fields_array() { return elemLibrary_force_fields_array; }
	/**
	 * Gets the library_force_fields element array.
	 * @return Returns a constant reference to the array of library_force_fields elements.
	 */
	const domLibrary_force_fields_Array &getLibrary_force_fields_array() const { return elemLibrary_force_fields_array; }
	/**
	 * Gets the library_images element array.
	 * @return Returns a reference to the array of library_images elements.
	 */
	domLibrary_images_Array &getLibrary_images_array() { return elemLibrary_images_array; }
	/**
	 * Gets the library_images element array.
	 * @return Returns a constant reference to the array of library_images elements.
	 */
	const domLibrary_images_Array &getLibrary_images_array() const { return elemLibrary_images_array; }
	/**
	 * Gets the library_lights element array.
	 * @return Returns a reference to the array of library_lights elements.
	 */
	domLibrary_lights_Array &getLibrary_lights_array() { return elemLibrary_lights_array; }
	/**
	 * Gets the library_lights element array.
	 * @return Returns a constant reference to the array of library_lights elements.
	 */
	const domLibrary_lights_Array &getLibrary_lights_array() const { return elemLibrary_lights_array; }
	/**
	 * Gets the library_materials element array.
	 * @return Returns a reference to the array of library_materials elements.
	 */
	domLibrary_materials_Array &getLibrary_materials_array() { return elemLibrary_materials_array; }
	/**
	 * Gets the library_materials element array.
	 * @return Returns a constant reference to the array of library_materials elements.
	 */
	const domLibrary_materials_Array &getLibrary_materials_array() const { return elemLibrary_materials_array; }
	/**
	 * Gets the library_nodes element array.
	 * @return Returns a reference to the array of library_nodes elements.
	 */
	domLibrary_nodes_Array &getLibrary_nodes_array() { return elemLibrary_nodes_array; }
	/**
	 * Gets the library_nodes element array.
	 * @return Returns a constant reference to the array of library_nodes elements.
	 */
	const domLibrary_nodes_Array &getLibrary_nodes_array() const { return elemLibrary_nodes_array; }
	/**
	 * Gets the library_physics_materials element array.
	 * @return Returns a reference to the array of library_physics_materials elements.
	 */
	domLibrary_physics_materials_Array &getLibrary_physics_materials_array() { return elemLibrary_physics_materials_array; }
	/**
	 * Gets the library_physics_materials element array.
	 * @return Returns a constant reference to the array of library_physics_materials elements.
	 */
	const domLibrary_physics_materials_Array &getLibrary_physics_materials_array() const { return elemLibrary_physics_materials_array; }
	/**
	 * Gets the library_physics_models element array.
	 * @return Returns a reference to the array of library_physics_models elements.
	 */
	domLibrary_physics_models_Array &getLibrary_physics_models_array() { return elemLibrary_physics_models_array; }
	/**
	 * Gets the library_physics_models element array.
	 * @return Returns a constant reference to the array of library_physics_models elements.
	 */
	const domLibrary_physics_models_Array &getLibrary_physics_models_array() const { return elemLibrary_physics_models_array; }
	/**
	 * Gets the library_physics_scenes element array.
	 * @return Returns a reference to the array of library_physics_scenes elements.
	 */
	domLibrary_physics_scenes_Array &getLibrary_physics_scenes_array() { return elemLibrary_physics_scenes_array; }
	/**
	 * Gets the library_physics_scenes element array.
	 * @return Returns a constant reference to the array of library_physics_scenes elements.
	 */
	const domLibrary_physics_scenes_Array &getLibrary_physics_scenes_array() const { return elemLibrary_physics_scenes_array; }
	/**
	 * Gets the library_visual_scenes element array.
	 * @return Returns a reference to the array of library_visual_scenes elements.
	 */
	domLibrary_visual_scenes_Array &getLibrary_visual_scenes_array() { return elemLibrary_visual_scenes_array; }
	/**
	 * Gets the library_visual_scenes element array.
	 * @return Returns a constant reference to the array of library_visual_scenes elements.
	 */
	const domLibrary_visual_scenes_Array &getLibrary_visual_scenes_array() const { return elemLibrary_visual_scenes_array; }
	/**
	 * Gets the scene element.
	 * @return a daeSmartRef to the scene element.
	 */
	const domSceneRef getScene() const { return elemScene; }
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
	domCOLLADA(DAE& dae) : daeElement(dae), attrXmlns(dae, *this), attrVersion(), attrXml_base(dae, *this), elemAsset(), elemLibrary_animations_array(), elemLibrary_animation_clips_array(), elemLibrary_cameras_array(), elemLibrary_controllers_array(), elemLibrary_geometries_array(), elemLibrary_effects_array(), elemLibrary_force_fields_array(), elemLibrary_images_array(), elemLibrary_lights_array(), elemLibrary_materials_array(), elemLibrary_nodes_array(), elemLibrary_physics_materials_array(), elemLibrary_physics_models_array(), elemLibrary_physics_scenes_array(), elemLibrary_visual_scenes_array(), elemScene(), elemExtra_array() {}
	/**
	 * Destructor
	 */
	virtual ~domCOLLADA() { daeElement::deleteCMDataArray(_CMData); }
	/**
	 * Overloaded assignment operator
	 */
	virtual domCOLLADA &operator=( const domCOLLADA &cpy ) { (void)cpy; return *this; }

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
