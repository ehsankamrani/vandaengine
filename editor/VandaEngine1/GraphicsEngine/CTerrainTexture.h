////////////////////////////////////////////////////////////////////////////
///	\File "CTerrainTexture.h"
//
///	Author: Brian Story
//
///	Creation Date: 5/27/2005
//
///	Purpose: Definition of the CTerrainTexture class.
////////////////////////////////////////////////////////////////////////////





#ifndef _CTERRAINTEXTURE_H_
#define _CTERRAINTEXTURE_H_


#include "CHeightClass.h"
#include "OpenGL.h"
#include "../common/defines.h"
#include "../GraphicsEngine/Image.h"

///////////////////////////////////
//
///	Class CTerrainTexture
//
///	Created: 5/27/2005
///
///////////////////////////////////

class CTerrainTexture
{
	/////////////////////
	// Private Members //
	/////////////////////

	private:
		CImage* m_bottomImg;
		CImage* m_bottomNormalImg;
		CImage* m_slopeImg;
		CImage* m_slopeNormalImg;
		CImage* m_topImg;
		CImage* m_topNormalImg;

		CImage* m_heightImg;

		// The width and height of the heightmap.
		int Width = 513;
		int Height = 513;


		// How many times we want the textures to be tiled over a chunk.
		int TextureTileAmount = 20;


		// Height data.
		heightData **data;


		// Number of textures.
		enum{MaxTextures = 3};

		// Our texture objects.		
		int groundTextures[MaxTextures];

		// Holds which texture we have in each unit.
		GLuint unita, unitb, unitc;

		// The width and height of our lightmap texture.
		enum {LightmapTextureWidth = 256, LightmapTextureHeight = 256};

		// Holds the heightmap texture.
		GLuint lightmapTexture;


		//////////////////////////////////////////////////////////
		///	Function: "createTextureCoords"
		//
		///	FirstModified: 9/27/2005
		//
		///	\param None
		//
		///	Output: None
		//
		///	\return None
		//
		///	Purpose: Creates texture coordinates for each point in the heightmap.
		//////////////////////////////////////////////////////////
		void createTextureCoords(void);


		//////////////////////////////////////////////////////////
		///	Function: "createHorizonMap"
		//
		///	FirstModified: 9/28/2005
		//
		///	\param None
		//
		///	Output: None
		//
		///	\return None
		//
		///	Purpose: Sets the horizon slope at each point in the heightmap.
		//////////////////////////////////////////////////////////
		void createHorizonMap(void);


		//////////////////////////////////////////////////////////
		///	Function: "createColors"
		//
		///	FirstModified: 9/27/2005
		//
		///	\param None
		//
		///	Output: None
		//
		///	\return None
		//
		///	Purpose: Sets the vertex color for each point in the heightmap.
		//////////////////////////////////////////////////////////
		void createColors(void);

	////////////////////
	// Public Members //
	////////////////////

	public:


	/////////////////
	// Constructor //
	/////////////////

		//////////////////////////////////////////////////////////
		///	Function: CTerrainTexture
		//
		///	FirstModified: 5/27/2005
		//
		///	\param	None
		//
		///	Output:	None
		//
		///	\return None
		//
		///	Purpose: Constructor for the class
		//////////////////////////////////////////////////////////
		CTerrainTexture(void)
		{
			// Initialize our textures.
			for (int i = 0; i < MaxTextures; i++)
			{
				groundTextures[i] = 0;
			}

			// Start the texture units with default textures.
			unita = 0;
			unitb = 2;
			unitc = 1;
		}


	////////////////
	// Destructor //
	////////////////

		//////////////////////////////////////////////////////////
		///	Function: ~CTerrainTexture
		//
		///	FirstModified: 5/27/2005
		//
		///	\param	None
		//
		///	Output:	None
		//
		///	\return None
		//
		///	Purpose: Destructor for the class
		//////////////////////////////////////////////////////////
		virtual ~CTerrainTexture(void)
		{
			CDelete(m_bottomImg);
			CDelete(m_bottomNormalImg);
			CDelete(m_slopeImg);
			CDelete(m_slopeNormalImg);
			CDelete(m_topImg);
			CDelete(m_topNormalImg);
		}

		//////////////////////////////////////////////////////////
		///	Function: "createLightmap"
		//
		///	FirstModified: 5/12/2005
		//
		///	\param float lightX		X position of the light.
		///	\param float lightY		Y position of the light.
		///	\param float lightZ		Z position of the light.
		//
		///	Output: None
		//
		///	\return None
		//
		///	Purpose: Creates a lightmap from the given light position.
		//////////////////////////////////////////////////////////
		void createLightmap(float lightX, float lightY, float lightZ);

		//////////////////////////////////////////////////////////
		///	Function: "changeTexture"
		//
		///	FirstModified: 9/27/2005
		//
		///	\param int target		The texture unit to change textures for.
		//
		///	Output: None
		//
		///	\return None
		//
		///	Purpose: Changes the texture in the given texture unit by looping
		//			 through the available textures loaded by this class.
		//////////////////////////////////////////////////////////

		void changeTexture(int target);

		//////////////////////////////////////////////////////////
		///	Function: "init"
		//
		///	FirstModified: 5/27/2005
		//
		///	\param heightData ***heights	The heightmap data this class will texture.
		//
		///	Output: None
		//
		///	\return None
		//
		///	Purpose: Initializes this texture class.
		//////////////////////////////////////////////////////////
		void init(heightData ***heights);
		//////////////////////////////////////////////////////////
		///	Function: "enableTextures"
		//
		///	FirstModified: 9/27/2005
		//
		///	\param None
		//
		///	Output: None
		//
		///	\return None
		//
		///	Purpose: Set up and enable the texture units to texture the heightmap.
		//////////////////////////////////////////////////////////
		void enableTextures(void);


		//////////////////////////////////////////////////////////
		///	Function: "disableTextures"
		//
		///	FirstModified: 9/27/2005
		//
		///	\param None
		//
		///	Output: None
		//
		///	\return None
		//
		///	Purpose: Disable the texture units.
		//////////////////////////////////////////////////////////
		void disableTextures(void);
};

#endif