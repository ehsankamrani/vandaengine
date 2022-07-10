/*
* Copyright 2006 Sony Computer Entertainment Inc.
*
* Licensed under the MIT Open Source License, for details please see license.txt or the website
* http://www.opensource.org/licenses/mit-license.php
*
*/ 

#ifndef __domAsset_h__
#define __domAsset_h__

#include <dae/daeDocument.h>
#include <dom/domTypes.h>
#include <dom/domElements.h>

class DAE;

/**
 * The asset element defines asset management information regarding its parent
 * element.
 */
class domAsset : public daeElement
{
public:
	virtual COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::ASSET; }
	static daeInt ID() { return 664; }
	virtual daeInt typeID() const { return ID(); }
public:
	class domContributor;

	typedef daeSmartRef<domContributor> domContributorRef;
	typedef daeTArray<domContributorRef> domContributor_Array;

/**
 * The contributor element defines authoring information for asset management
 */
	class domContributor : public daeElement
	{
	public:
		virtual COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::CONTRIBUTOR; }
		static daeInt ID() { return 665; }
		virtual daeInt typeID() const { return ID(); }
	public:
		class domAuthor;

		typedef daeSmartRef<domAuthor> domAuthorRef;
		typedef daeTArray<domAuthorRef> domAuthor_Array;

/**
 * The author element contains a string with the author's name. There may
 * be only one author element.
 */
		class domAuthor : public daeElement
		{
		public:
			virtual COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::AUTHOR; }
			static daeInt ID() { return 666; }
			virtual daeInt typeID() const { return ID(); }

		protected:  // Value
			/**
			 * The xsString value of the text data of this element. 
			 */
			xsString _value;

		public:	//Accessors and Mutators
			/**
			 * Gets the value of this element.
			 * @return Returns a xsString of the value.
			 */
			xsString getValue() const { return _value; }
			/**
			 * Sets the _value of this element.
			 * @param val The new value for this element.
			 */
			void setValue( xsString val ) { *(daeStringRef*)&_value = val; }

		protected:
			/**
			 * Constructor
			 */
			domAuthor(DAE& dae) : daeElement(dae), _value() {}
			/**
			 * Destructor
			 */
			virtual ~domAuthor() {}
			/**
			 * Overloaded assignment operator
			 */
			virtual domAuthor &operator=( const domAuthor &cpy ) { (void)cpy; return *this; }

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

		class domAuthoring_tool;

		typedef daeSmartRef<domAuthoring_tool> domAuthoring_toolRef;
		typedef daeTArray<domAuthoring_toolRef> domAuthoring_tool_Array;

/**
 * The authoring_tool element contains a string with the authoring tool's
 * name. There may be only one authoring_tool element.
 */
		class domAuthoring_tool : public daeElement
		{
		public:
			virtual COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::AUTHORING_TOOL; }
			static daeInt ID() { return 667; }
			virtual daeInt typeID() const { return ID(); }

		protected:  // Value
			/**
			 * The xsString value of the text data of this element. 
			 */
			xsString _value;

		public:	//Accessors and Mutators
			/**
			 * Gets the value of this element.
			 * @return Returns a xsString of the value.
			 */
			xsString getValue() const { return _value; }
			/**
			 * Sets the _value of this element.
			 * @param val The new value for this element.
			 */
			void setValue( xsString val ) { *(daeStringRef*)&_value = val; }

		protected:
			/**
			 * Constructor
			 */
			domAuthoring_tool(DAE& dae) : daeElement(dae), _value() {}
			/**
			 * Destructor
			 */
			virtual ~domAuthoring_tool() {}
			/**
			 * Overloaded assignment operator
			 */
			virtual domAuthoring_tool &operator=( const domAuthoring_tool &cpy ) { (void)cpy; return *this; }

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

		class domComments;

		typedef daeSmartRef<domComments> domCommentsRef;
		typedef daeTArray<domCommentsRef> domComments_Array;

/**
 * The comments element contains a string with comments from this contributor.
 * There may be only one comments element.
 */
		class domComments : public daeElement
		{
		public:
			virtual COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::COMMENTS; }
			static daeInt ID() { return 668; }
			virtual daeInt typeID() const { return ID(); }

		protected:  // Value
			/**
			 * The xsString value of the text data of this element. 
			 */
			xsString _value;

		public:	//Accessors and Mutators
			/**
			 * Gets the value of this element.
			 * @return Returns a xsString of the value.
			 */
			xsString getValue() const { return _value; }
			/**
			 * Sets the _value of this element.
			 * @param val The new value for this element.
			 */
			void setValue( xsString val ) { *(daeStringRef*)&_value = val; }

		protected:
			/**
			 * Constructor
			 */
			domComments(DAE& dae) : daeElement(dae), _value() {}
			/**
			 * Destructor
			 */
			virtual ~domComments() {}
			/**
			 * Overloaded assignment operator
			 */
			virtual domComments &operator=( const domComments &cpy ) { (void)cpy; return *this; }

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

		class domCopyright;

		typedef daeSmartRef<domCopyright> domCopyrightRef;
		typedef daeTArray<domCopyrightRef> domCopyright_Array;

/**
 * The copyright element contains a string with copyright information. There
 * may be only one copyright element.
 */
		class domCopyright : public daeElement
		{
		public:
			virtual COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::COPYRIGHT; }
			static daeInt ID() { return 669; }
			virtual daeInt typeID() const { return ID(); }

		protected:  // Value
			/**
			 * The xsString value of the text data of this element. 
			 */
			xsString _value;

		public:	//Accessors and Mutators
			/**
			 * Gets the value of this element.
			 * @return Returns a xsString of the value.
			 */
			xsString getValue() const { return _value; }
			/**
			 * Sets the _value of this element.
			 * @param val The new value for this element.
			 */
			void setValue( xsString val ) { *(daeStringRef*)&_value = val; }

		protected:
			/**
			 * Constructor
			 */
			domCopyright(DAE& dae) : daeElement(dae), _value() {}
			/**
			 * Destructor
			 */
			virtual ~domCopyright() {}
			/**
			 * Overloaded assignment operator
			 */
			virtual domCopyright &operator=( const domCopyright &cpy ) { (void)cpy; return *this; }

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

		class domSource_data;

		typedef daeSmartRef<domSource_data> domSource_dataRef;
		typedef daeTArray<domSource_dataRef> domSource_data_Array;

/**
 * The source_data element contains a URI reference to the source data used
 * for this asset. There may be only one source_data element.
 */
		class domSource_data : public daeElement
		{
		public:
			virtual COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::SOURCE_DATA; }
			static daeInt ID() { return 670; }
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
			domSource_data(DAE& dae) : daeElement(dae), _value(dae, *this) {}
			/**
			 * Destructor
			 */
			virtual ~domSource_data() {}
			/**
			 * Overloaded assignment operator
			 */
			virtual domSource_data &operator=( const domSource_data &cpy ) { (void)cpy; return *this; }

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
 * The author element contains a string with the author's name. There may
 * be only one author element. @see domAuthor
 */
		domAuthorRef elemAuthor;
/**
 * The authoring_tool element contains a string with the authoring tool's
 * name. There may be only one authoring_tool element. @see domAuthoring_tool
 */
		domAuthoring_toolRef elemAuthoring_tool;
/**
 * The comments element contains a string with comments from this contributor.
 * There may be only one comments element. @see domComments
 */
		domCommentsRef elemComments;
/**
 * The copyright element contains a string with copyright information. There
 * may be only one copyright element. @see domCopyright
 */
		domCopyrightRef elemCopyright;
/**
 * The source_data element contains a URI reference to the source data used
 * for this asset. There may be only one source_data element. @see domSource_data
 */
		domSource_dataRef elemSource_data;

	public:	//Accessors and Mutators
		/**
		 * Gets the author element.
		 * @return a daeSmartRef to the author element.
		 */
		const domAuthorRef getAuthor() const { return elemAuthor; }
		/**
		 * Gets the authoring_tool element.
		 * @return a daeSmartRef to the authoring_tool element.
		 */
		const domAuthoring_toolRef getAuthoring_tool() const { return elemAuthoring_tool; }
		/**
		 * Gets the comments element.
		 * @return a daeSmartRef to the comments element.
		 */
		const domCommentsRef getComments() const { return elemComments; }
		/**
		 * Gets the copyright element.
		 * @return a daeSmartRef to the copyright element.
		 */
		const domCopyrightRef getCopyright() const { return elemCopyright; }
		/**
		 * Gets the source_data element.
		 * @return a daeSmartRef to the source_data element.
		 */
		const domSource_dataRef getSource_data() const { return elemSource_data; }
	protected:
		/**
		 * Constructor
		 */
		domContributor(DAE& dae) : daeElement(dae), elemAuthor(), elemAuthoring_tool(), elemComments(), elemCopyright(), elemSource_data() {}
		/**
		 * Destructor
		 */
		virtual ~domContributor() {}
		/**
		 * Overloaded assignment operator
		 */
		virtual domContributor &operator=( const domContributor &cpy ) { (void)cpy; return *this; }

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

	class domCreated;

	typedef daeSmartRef<domCreated> domCreatedRef;
	typedef daeTArray<domCreatedRef> domCreated_Array;

/**
 * The created element contains the date and time that the parent element
 * was created and is  represented in an ISO 8601 format.  The created element
 * may appear zero or one time.
 */
	class domCreated : public daeElement
	{
	public:
		virtual COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::CREATED; }
		static daeInt ID() { return 671; }
		virtual daeInt typeID() const { return ID(); }

	protected:  // Value
		/**
		 * The xsDateTime value of the text data of this element. 
		 */
		xsDateTime _value;

	public:	//Accessors and Mutators
		/**
		 * Gets the value of this element.
		 * @return Returns a xsDateTime of the value.
		 */
		xsDateTime getValue() const { return _value; }
		/**
		 * Sets the _value of this element.
		 * @param val The new value for this element.
		 */
		void setValue( xsDateTime val ) { *(daeStringRef*)&_value = val; }

	protected:
		/**
		 * Constructor
		 */
		domCreated(DAE& dae) : daeElement(dae), _value() {}
		/**
		 * Destructor
		 */
		virtual ~domCreated() {}
		/**
		 * Overloaded assignment operator
		 */
		virtual domCreated &operator=( const domCreated &cpy ) { (void)cpy; return *this; }

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

	class domKeywords;

	typedef daeSmartRef<domKeywords> domKeywordsRef;
	typedef daeTArray<domKeywordsRef> domKeywords_Array;

/**
 * The keywords element contains a list of words used as search criteria for
 * the parent element.  The keywords element may appear zero or more times.
 */
	class domKeywords : public daeElement
	{
	public:
		virtual COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::KEYWORDS; }
		static daeInt ID() { return 672; }
		virtual daeInt typeID() const { return ID(); }

	protected:  // Value
		/**
		 * The xsString value of the text data of this element. 
		 */
		xsString _value;

	public:	//Accessors and Mutators
		/**
		 * Gets the value of this element.
		 * @return Returns a xsString of the value.
		 */
		xsString getValue() const { return _value; }
		/**
		 * Sets the _value of this element.
		 * @param val The new value for this element.
		 */
		void setValue( xsString val ) { *(daeStringRef*)&_value = val; }

	protected:
		/**
		 * Constructor
		 */
		domKeywords(DAE& dae) : daeElement(dae), _value() {}
		/**
		 * Destructor
		 */
		virtual ~domKeywords() {}
		/**
		 * Overloaded assignment operator
		 */
		virtual domKeywords &operator=( const domKeywords &cpy ) { (void)cpy; return *this; }

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

	class domModified;

	typedef daeSmartRef<domModified> domModifiedRef;
	typedef daeTArray<domModifiedRef> domModified_Array;

/**
 * The modified element contains the date and time that the parent element
 * was last modified and  represented in an ISO 8601 format. The modified
 * element may appear zero or one time.
 */
	class domModified : public daeElement
	{
	public:
		virtual COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::MODIFIED; }
		static daeInt ID() { return 673; }
		virtual daeInt typeID() const { return ID(); }

	protected:  // Value
		/**
		 * The xsDateTime value of the text data of this element. 
		 */
		xsDateTime _value;

	public:	//Accessors and Mutators
		/**
		 * Gets the value of this element.
		 * @return Returns a xsDateTime of the value.
		 */
		xsDateTime getValue() const { return _value; }
		/**
		 * Sets the _value of this element.
		 * @param val The new value for this element.
		 */
		void setValue( xsDateTime val ) { *(daeStringRef*)&_value = val; }

	protected:
		/**
		 * Constructor
		 */
		domModified(DAE& dae) : daeElement(dae), _value() {}
		/**
		 * Destructor
		 */
		virtual ~domModified() {}
		/**
		 * Overloaded assignment operator
		 */
		virtual domModified &operator=( const domModified &cpy ) { (void)cpy; return *this; }

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

	class domRevision;

	typedef daeSmartRef<domRevision> domRevisionRef;
	typedef daeTArray<domRevisionRef> domRevision_Array;

/**
 * The revision element contains the revision information for the parent element.
 * The revision  element may appear zero or one time.
 */
	class domRevision : public daeElement
	{
	public:
		virtual COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::REVISION; }
		static daeInt ID() { return 674; }
		virtual daeInt typeID() const { return ID(); }

	protected:  // Value
		/**
		 * The xsString value of the text data of this element. 
		 */
		xsString _value;

	public:	//Accessors and Mutators
		/**
		 * Gets the value of this element.
		 * @return Returns a xsString of the value.
		 */
		xsString getValue() const { return _value; }
		/**
		 * Sets the _value of this element.
		 * @param val The new value for this element.
		 */
		void setValue( xsString val ) { *(daeStringRef*)&_value = val; }

	protected:
		/**
		 * Constructor
		 */
		domRevision(DAE& dae) : daeElement(dae), _value() {}
		/**
		 * Destructor
		 */
		virtual ~domRevision() {}
		/**
		 * Overloaded assignment operator
		 */
		virtual domRevision &operator=( const domRevision &cpy ) { (void)cpy; return *this; }

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

	class domSubject;

	typedef daeSmartRef<domSubject> domSubjectRef;
	typedef daeTArray<domSubjectRef> domSubject_Array;

/**
 * The subject element contains a description of the topical subject of the
 * parent element. The  subject element may appear zero or one time.
 */
	class domSubject : public daeElement
	{
	public:
		virtual COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::SUBJECT; }
		static daeInt ID() { return 675; }
		virtual daeInt typeID() const { return ID(); }

	protected:  // Value
		/**
		 * The xsString value of the text data of this element. 
		 */
		xsString _value;

	public:	//Accessors and Mutators
		/**
		 * Gets the value of this element.
		 * @return Returns a xsString of the value.
		 */
		xsString getValue() const { return _value; }
		/**
		 * Sets the _value of this element.
		 * @param val The new value for this element.
		 */
		void setValue( xsString val ) { *(daeStringRef*)&_value = val; }

	protected:
		/**
		 * Constructor
		 */
		domSubject(DAE& dae) : daeElement(dae), _value() {}
		/**
		 * Destructor
		 */
		virtual ~domSubject() {}
		/**
		 * Overloaded assignment operator
		 */
		virtual domSubject &operator=( const domSubject &cpy ) { (void)cpy; return *this; }

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

	class domTitle;

	typedef daeSmartRef<domTitle> domTitleRef;
	typedef daeTArray<domTitleRef> domTitle_Array;

/**
 * The title element contains the title information for the parent element.
 * The title element may  appear zero or one time.
 */
	class domTitle : public daeElement
	{
	public:
		virtual COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::TITLE; }
		static daeInt ID() { return 676; }
		virtual daeInt typeID() const { return ID(); }

	protected:  // Value
		/**
		 * The xsString value of the text data of this element. 
		 */
		xsString _value;

	public:	//Accessors and Mutators
		/**
		 * Gets the value of this element.
		 * @return Returns a xsString of the value.
		 */
		xsString getValue() const { return _value; }
		/**
		 * Sets the _value of this element.
		 * @param val The new value for this element.
		 */
		void setValue( xsString val ) { *(daeStringRef*)&_value = val; }

	protected:
		/**
		 * Constructor
		 */
		domTitle(DAE& dae) : daeElement(dae), _value() {}
		/**
		 * Destructor
		 */
		virtual ~domTitle() {}
		/**
		 * Overloaded assignment operator
		 */
		virtual domTitle &operator=( const domTitle &cpy ) { (void)cpy; return *this; }

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

	class domUnit;

	typedef daeSmartRef<domUnit> domUnitRef;
	typedef daeTArray<domUnitRef> domUnit_Array;

/**
 * The unit element contains descriptive information about unit of measure.
 * It has attributes for  the name of the unit and the measurement with respect
 * to the meter. The unit element may appear  zero or one time.
 */
	class domUnit : public daeElement
	{
	public:
		virtual COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::UNIT; }
		static daeInt ID() { return 677; }
		virtual daeInt typeID() const { return ID(); }
	protected:  // Attributes
/**
 *  The meter attribute specifies the measurement with respect to the meter.
 * The default  value for the meter attribute is “1.0”. 
 */
		domFloat attrMeter;
/**
 *  The name attribute specifies the name of the unit. The default value for
 * the name  attribute is “meter”. 
 */
		xsNMTOKEN attrName;


	public:	//Accessors and Mutators
		/**
		 * Gets the meter attribute.
		 * @return Returns a domFloat of the meter attribute.
		 */
		domFloat getMeter() const { return attrMeter; }
		/**
		 * Sets the meter attribute.
		 * @param atMeter The new value for the meter attribute.
		 */
		void setMeter( domFloat atMeter ) { attrMeter = atMeter; _validAttributeArray[0] = true; }

		/**
		 * Gets the name attribute.
		 * @return Returns a xsNMTOKEN of the name attribute.
		 */
		xsNMTOKEN getName() const { return attrName; }
		/**
		 * Sets the name attribute.
		 * @param atName The new value for the name attribute.
		 */
		void setName( xsNMTOKEN atName ) { *(daeStringRef*)&attrName = atName; _validAttributeArray[1] = true; }

	protected:
		/**
		 * Constructor
		 */
		domUnit(DAE& dae) : daeElement(dae), attrMeter(), attrName() {}
		/**
		 * Destructor
		 */
		virtual ~domUnit() {}
		/**
		 * Overloaded assignment operator
		 */
		virtual domUnit &operator=( const domUnit &cpy ) { (void)cpy; return *this; }

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

	class domUp_axis;

	typedef daeSmartRef<domUp_axis> domUp_axisRef;
	typedef daeTArray<domUp_axisRef> domUp_axis_Array;

/**
 * The up_axis element contains descriptive information about coordinate system
 * of the geometric  data. All coordinates are right-handed by definition.
 * This element specifies which axis is  considered up. The default is the
 * Y-axis. The up_axis element may appear zero or one time.
 */
	class domUp_axis : public daeElement
	{
	public:
		virtual COLLADA_TYPE::TypeEnum getElementType() const { return COLLADA_TYPE::UP_AXIS; }
		static daeInt ID() { return 678; }
		virtual daeInt typeID() const { return ID(); }

	protected:  // Value
		/**
		 * The domUpAxisType value of the text data of this element. 
		 */
		domUpAxisType _value;

	public:	//Accessors and Mutators
		/**
		 * Gets the value of this element.
		 * @return a domUpAxisType of the value.
		 */
		domUpAxisType getValue() const { return _value; }
		/**
		 * Sets the _value of this element.
		 * @param val The new value for this element.
		 */
		void setValue( domUpAxisType val ) { _value = val; }

	protected:
		/**
		 * Constructor
		 */
		domUp_axis(DAE& dae) : daeElement(dae), _value() {}
		/**
		 * Destructor
		 */
		virtual ~domUp_axis() {}
		/**
		 * Overloaded assignment operator
		 */
		virtual domUp_axis &operator=( const domUp_axis &cpy ) { (void)cpy; return *this; }

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
 * The contributor element defines authoring information for asset management
 * @see domContributor
 */
	domContributor_Array elemContributor_array;
/**
 * The created element contains the date and time that the parent element
 * was created and is  represented in an ISO 8601 format.  The created element
 * may appear zero or one time. @see domCreated
 */
	domCreatedRef elemCreated;
/**
 * The keywords element contains a list of words used as search criteria for
 * the parent element.  The keywords element may appear zero or more times.
 * @see domKeywords
 */
	domKeywordsRef elemKeywords;
/**
 * The modified element contains the date and time that the parent element
 * was last modified and  represented in an ISO 8601 format. The modified
 * element may appear zero or one time. @see domModified
 */
	domModifiedRef elemModified;
/**
 * The revision element contains the revision information for the parent element.
 * The revision  element may appear zero or one time. @see domRevision
 */
	domRevisionRef elemRevision;
/**
 * The subject element contains a description of the topical subject of the
 * parent element. The  subject element may appear zero or one time. @see
 * domSubject
 */
	domSubjectRef elemSubject;
/**
 * The title element contains the title information for the parent element.
 * The title element may  appear zero or one time. @see domTitle
 */
	domTitleRef elemTitle;
/**
 * The unit element contains descriptive information about unit of measure.
 * It has attributes for  the name of the unit and the measurement with respect
 * to the meter. The unit element may appear  zero or one time. @see domUnit
 */
	domUnitRef elemUnit;
/**
 * The up_axis element contains descriptive information about coordinate system
 * of the geometric  data. All coordinates are right-handed by definition.
 * This element specifies which axis is  considered up. The default is the
 * Y-axis. The up_axis element may appear zero or one time. @see domUp_axis
 */
	domUp_axisRef elemUp_axis;

public:	//Accessors and Mutators
	/**
	 * Gets the contributor element array.
	 * @return Returns a reference to the array of contributor elements.
	 */
	domContributor_Array &getContributor_array() { return elemContributor_array; }
	/**
	 * Gets the contributor element array.
	 * @return Returns a constant reference to the array of contributor elements.
	 */
	const domContributor_Array &getContributor_array() const { return elemContributor_array; }
	/**
	 * Gets the created element.
	 * @return a daeSmartRef to the created element.
	 */
	const domCreatedRef getCreated() const { return elemCreated; }
	/**
	 * Gets the keywords element.
	 * @return a daeSmartRef to the keywords element.
	 */
	const domKeywordsRef getKeywords() const { return elemKeywords; }
	/**
	 * Gets the modified element.
	 * @return a daeSmartRef to the modified element.
	 */
	const domModifiedRef getModified() const { return elemModified; }
	/**
	 * Gets the revision element.
	 * @return a daeSmartRef to the revision element.
	 */
	const domRevisionRef getRevision() const { return elemRevision; }
	/**
	 * Gets the subject element.
	 * @return a daeSmartRef to the subject element.
	 */
	const domSubjectRef getSubject() const { return elemSubject; }
	/**
	 * Gets the title element.
	 * @return a daeSmartRef to the title element.
	 */
	const domTitleRef getTitle() const { return elemTitle; }
	/**
	 * Gets the unit element.
	 * @return a daeSmartRef to the unit element.
	 */
	const domUnitRef getUnit() const { return elemUnit; }
	/**
	 * Gets the up_axis element.
	 * @return a daeSmartRef to the up_axis element.
	 */
	const domUp_axisRef getUp_axis() const { return elemUp_axis; }
protected:
	/**
	 * Constructor
	 */
	domAsset(DAE& dae) : daeElement(dae), elemContributor_array(), elemCreated(), elemKeywords(), elemModified(), elemRevision(), elemSubject(), elemTitle(), elemUnit(), elemUp_axis() {}
	/**
	 * Destructor
	 */
	virtual ~domAsset() {}
	/**
	 * Overloaded assignment operator
	 */
	virtual domAsset &operator=( const domAsset &cpy ) { (void)cpy; return *this; }

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
