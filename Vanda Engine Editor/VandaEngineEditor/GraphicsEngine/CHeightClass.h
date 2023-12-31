// height_class.h: interface for the height_class class.
//
//////////////////////////////////////////////////////////////////////

//Modified work: Copyright (C) 2024 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#ifndef _CHEIGHTCLASS_H_
#define _CHEIGHTCLASS_H_

#include <ctime>
#include "OpenGL.h"
#include <gl/glu.h>
#include "Image.h"
#include "Defines.h"


// Vector struct.
struct SVector
{
	float x, y, z;
};

// Color struct.
struct SColor
{
	GLubyte r, g, b, a;
};


// Height data struct.
struct heightData
{
	float y;				// Height at this location.
	SVector normal;			// Normal at this location.
	SColor color;			// The color at this location.
	float u, v;				// Texture coordinates at this location.
	float lightU, lightV;	// Texture coordinates for the lightmap.
	float horizon;			// Slope of the horizon at this location.
};


class CHeightClass  
{
	/////////////////////
	// Private Members //
	/////////////////////

	private:

		// Seed used to create this heightmap.
		int rand_seed;

		// Max and min radius for the hills.
		int radmin;
		int radmax;
		

		// The width and height of the heightmap.
		int Width = 513;
		int Height = 513;

	
		// The heightmap data.
		heightData **heights;		

		// A texture used to display the heightmap to the screen.
		GLuint heightmapTexture;

		CImage* image;
		////////////////////////////////
		//  Private Member Functions  //
		////////////////////////////////
					  
		//////////////////////////////////////////////////////////
		//	Function: "addHill"
		//
		//	First Modified: 07/22/2002
		//
		//	Input: None
		//
		//	Output: None
		//
		//	Returns: None
		//
		//	Purpose: Raises a hill on the heightmap.
		//////////////////////////////////////////////////////////
		void addHill(void);


		//////////////////////////////////////////////////////////
		//	Function: "normalize"
		//
		//	First Modified:  07/22/2002
		//
		//	Input: None
		//
		//	Output: None
		//
		//	Returns: None
		//
		//	Purpose: Normalizes the heights in the heightmap.
		//////////////////////////////////////////////////////////
		void normalize(void);


		//////////////////////////////////////////////////////////
		//	Function: "flaten"
		//
		//	First Modified: 07/22/2002
		//
		//	Input: None
		//
		//	Output: None
		//
		//	Returns: None
		//
		//	Purpose: Flatens the heightmap slightly by squaring the
		//			 normalized height values.
		//////////////////////////////////////////////////////////
		void flaten(void);


		//////////////////////////////////////////////////////////
		//	Function: "scale"
		//
		//	First Modified: 07/24/2002
		//
		//	Input: int value		Scaling value.
		//
		//	Output: None
		//
		//	Returns: None
		//
		//	Purpose: Scales the terrains height values.
		//////////////////////////////////////////////////////////
		void scale(int value);


		//////////////////////////////////////////////////////////
		//	Function: "smooth"
		//
		//	First Modified: 07/23/2002
		//
		//	Input: None
		//
		//	Output: None
		//
		//	Returns: None
		//
		//	Purpose: Smooths the terrain by averaging near heights.
		//////////////////////////////////////////////////////////
		void smooth(void);


		//////////////////////////////////////////////////////////
		//	Function: "createNormals"
		//
		//	First Modified: 07/22/2002
		//
		//	Input: None
		//
		//	Output: None
		//
		//	Returns: None
		//
		//	Purpose: Creates vertex normals for the heights in the heightmap.
		//////////////////////////////////////////////////////////
		void createNormals(void);


		//////////////////////////////////////////////////////////
		///	Function: "diamond"
		//
		///	FirstModified: 9/02/2005
		//
		///	\param int ulx			The upper left x value of this diamond.
		//		   int ulz			The upper left z value of this diamond.
		//		   int width		The width of this diamond.
		//		   int randValue	The random value to adjust the average height by.
		//
		///	Output: None
		//
		///	\return None
		//
		///	Purpose: The diamond step of the diamond square algorithm.
		//////////////////////////////////////////////////////////
		void diamond(int ulx, int ulz, int width, int randValue);


		//////////////////////////////////////////////////////////
		///	Function: "square"
		//
		///	FirstModified: 9/02/2005
		//
		///	\param int ulx			The upper left x value of this square.
		//		   int ulz			The upper left z value of this square.
		//		   int width		The width of this diamond.
		//		   int randValue	The random value to adjust the average height by.
		//
		///	Output: None
		//
		///	\return None
		//
		///	Purpose: The square step of the diamond square algorithm.
		//////////////////////////////////////////////////////////
		void square(int ulx, int ulz, int width, int randValue);


		//////////////////////////////////////////////////////////
		///	Function: "createImage"
		//
		///	FirstModified: 9/02/2005
		//
		///	\param None
		//
		///	Output: None
		//
		///	\return None
		//
		///	Purpose: Creates a texture from the current heightmap.
		//////////////////////////////////////////////////////////
		void createImage(void);


  
	////////////////////
	// Public Members //
	////////////////////

	public:

		// These enumerations are used to decide which type of heightmap to create.
		enum {Hill = 0, FaultLine = 1, Midpoint = 2, Image = 3};


		/////////////////
		// Constructor //
		/////////////////

		//////////////////////////////////////////////////////////
		//	Function: "CHeightClass"
		//
		//	LastModified: 07/22/2002
		//
		//	Input: None
		//
		//	Output: None
		//
		//	Returns: None
		//
		//	Purpose: Constructor 
		//////////////////////////////////////////////////////////
		CHeightClass(void)
		{
			heights = NULL;
			heightmapTexture = 0;
			image = CNew(CImage);
		};



		////////////////
		// Destructor //
		////////////////

		//////////////////////////////////////////////////////////
		//	Function: "~CHeightClass" 
		//
		//	LastModified: 07/22/2002
		//
		//	Input: None
		//
		//	Output: None
		//
		//	Returns: None
		//
		//	Purpose: Destructor
		//////////////////////////////////////////////////////////
		virtual ~CHeightClass()
		{
			if (heights)
			{
				for (int i = 0; i < Width; i++)
					delete [] heights[i];

				delete [] heights;
			}
			CDelete(image);
		};



		
		/////////////////////////////
		// Public Member Functions //
		/////////////////////////////

		//////////////////////////////////////////////////////////
		//	Function: "createHeightmapHill"
		//
		///	FirstModified: 9/02/2005
		//
		//	Input: int rmin		Minimum radius.
		//		   int rmax		Maximum radius.
		//		   int seed		The random number generator seed.
		//
		//	Output: None
		//
		//	Returns: None
		//
		//	Purpose: Creates a heightmap using the hill algorithm.
		//////////////////////////////////////////////////////////
		void createHeightmapHill(int rmin = 5, int rmax = 25, int seed = time(0));


		//////////////////////////////////////////////////////////
		//	Function: "createHeightmapFaultLine"
		//
		//	First Modified: 07/23/2002
		//
		//	Input: int seed		The random number generator seed.
		//
		//	Output: None
		//
		//	Returns: None
		//
		//	Purpose: Creates a heightmap using the fault line algorithm.
		//////////////////////////////////////////////////////////
		void createHeightmapFaultLine(int seed = time(0));

		//////////////////////////////////////////////////////////
		//	Function: "createHeightmapFromImage"
		//
		///	FirstModified: 9/02/2005
		//
		//	Input: Image Path
		//
		//	Output: None
		//
		//	Returns: None
		//
		//	Purpose: Creates a heightmap from image
		//////////////////////////////////////////////////////////
		void createHeightmapFromImage(CChar* ImagePath);

		//////////////////////////////////////////////////////////
		//	Function: "createHeightmapMidpoint"
		//
		///	FirstModified: 9/02/2005
		//
		//	Input: int seed		The random number generator seed.
		//
		//	Output: None
		//
		//	Returns: None
		//
		//	Purpose: Creates a heightmap using midpoint displacement.
		//////////////////////////////////////////////////////////
		void createHeightmapMidpoint(int seed = time(0));


		//////////////////////////////////////////////////////////
		///	Function: "createHeightmap"
		//
		///	FirstModified: 9/02/2005
		//
		///	\param int type			The method to use when creating the heightmap.
		//
		///	Output: None
		//
		///	\return None
		//
		///	Purpose: Creates a heightmap using the given method.
		//////////////////////////////////////////////////////////
		void createHeightmap(int type, CChar* imagePath = NULL);


		//////////////////////////////////////////////////////////
		///	Function: "draw"
		//
		///	FirstModified: 9/02/2005
		//
		///	\param int sWidth			The current screen width.
		//		   int sHeight			The current screen height.
		//
		///	Output: None
		//
		///	\return None
		//
		///	Purpose: Display the heightmap as a 2d black and white image.
		//////////////////////////////////////////////////////////	 
		void draw(int sWidth, int sHeight);


		//////////////////////////////////////////////////////////
		//	Function: "getHeight"
		//
		//	FirstModified: 09/02/2005
		//
		//	Input: None
		//
		//	Output: None
		//
		//	Returns: A pointer to the heightmap data.
		//
		//	Purpose: Accessor for the heightmap data.
		//////////////////////////////////////////////////////////
		heightData ***getHeightData(void)
		{
			return &heights;
		}

};

#endif // _HEIGHT_CLASS_H_
