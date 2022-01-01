////////////////////////////////////////////////////////////////////////////
///	\File "CTerrainTexture.cpp"
//
///	Author: Brian Story
//
///	Creation Date: 5/27/2005
//
///	Purpose: Implimentation of the CTerrainTexture class.
////////////////////////////////////////////////////////////////////////////

//Modified work: Copyright (C) 2022 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#include "stdafx.h"
#include "CTerrainTexture.h"
#include <algorithm>
#include <stdio.h>
#include <assert.h>
#include <io.h>
#include <math.h>
#include "OpenGL.h"
#include "Texture.h"
#include "..//Main.h"
using namespace std;

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
void CTerrainTexture::createTextureCoords(void)
{
	float xcoord = 0.0f;
	float zcoord = 0.0f;

	// The texture coordinates increase along the x and z value by the
	// x and z steps, which we get by dividing the number of times we
	// want the texture to tile along the x and z axis by the width and
	// height of the heightmap.
	float xstep = (float)TextureTileAmount/(float)Width;
	float zstep = (float)TextureTileAmount/(float)Height;

	// Loop through each point and calculate the texture coordinates.
	for (int z = 0; z < Height; z++)
	{
		xcoord = 0.0f;
		for (int x = 0; x < Width; x++)
		{			
			data[x][z].u = xcoord;
			data[x][z].v = zcoord;

			xcoord += xstep;
		}
		zcoord += zstep;
	}

	// Create texture coords for lighting.
	for (int z = 0; z < Height; z++)
	{
		for (int x = 0; x < Width; x++)
		{			
			data[x][z].lightU = (float)x/(float)Width;
			data[x][z].lightV = (float)z/(float)Height;
		}
	}
}


//////////////////////////////////////////////////////////
///	Function: "createHorizonMap"
//
///	FirstModified: 5/12/2005
//
///	\param None
//
///	Output: None
//
///	\return None
//
///	Purpose: Sets the horizon slope at each point in the heightmap.
//////////////////////////////////////////////////////////
void CTerrainTexture::createHorizonMap(void)
{
	// This function will create a horizon map for the heightmap.  A
	// horizon map is a set of numbers defining the position of the 
	// horizon in a number of directions from each point in the heightmap.
	//
	// This horizon map will just include one direction: Negative X.  This
	// will allow for shadows to be cast if the light source is on the -X
	// side of the heightmap.

	// Loop through each value in the heightmap.
	for (int z = 0; z < Height; z++)
	{
		for (int x = 0; x < Width; x++)
		{
			float maxSlope = 0;

			// Calculate the slope of the line between this point and every
			// point to the -x of this point.  The largest slope will be
			// the value we save.
			for (int i = x; i >= 0; i--)
			{
				float slope = 0;
				
				// Calculate the slope at this point.
				if (i == x)
					slope = 0;
				else
					slope = float(data[i][z].y - data[x][z].y) / (i - x);
				
				// Negate the slope calculated since we're moving in the -x direction.
				slope = slope * -1;
				
				// If the calculated slope is larger, save it.
				maxSlope = slope > maxSlope ? slope : maxSlope;
			}
			// Record the largest slope found.
			data[x][z].horizon = maxSlope;
		}
	}
}


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
void CTerrainTexture::createColors(void)
{
	for (int y = 0; y < Height; y++)
	{
		for (int x = 0; x < Width; x++)
		{
			float slope = data[x][y].normal.y;

			// Calculate our color values.
			GLubyte color = 255 - GLubyte(255 * std::max < CFloat > (0, std::min<CFloat>(1, ((data[x][y].y/* - 10*/) / g_terrain->GetTopStartHeight()))));
			GLubyte alpha = 255 - GLubyte(255 * std::max< CFloat >(0, (std::min< CFloat >(1, ((1 - slope/* - .1f*/) / g_terrain->GetSlopeFactor())))));

			// Assign the color value to this point.
			data[x][y].color.r = color;
			data[x][y].color.g = color;
			data[x][y].color.b = color;
			data[x][y].color.a = alpha;
		}
	}
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
void CTerrainTexture::createLightmap(float lightX, float lightY, float lightZ)
{
	// Create a normalized vector from the light position.
	double len = sqrt(lightX*lightX + lightY*lightY + lightZ*lightZ);

	float lightingX = float(lightX / len);
	float lightingY = float(lightY / len);
	float lightingZ = float(lightZ / len);


	// Since the lightmap is most likely not the same size as the heightmap,
	// we divide the width and height by the lightmaps width and height to
	// figure out how often we need to sample normal and horizon information
	// to create the texture.
	float xstep = (float)Width / LightmapTextureWidth;
	float ystep = (float)Height / LightmapTextureHeight;
	   

	// Allocate memory for our texture data.
	GLubyte *lightmap;
	lightmap = new GLubyte[LightmapTextureWidth*LightmapTextureHeight];


	// Loop through each value of our *Lightmap*, calculating a light value
	// using a sample point found through our xstep and ystep.
	int actualX, actualZ;
	for (int y = 0; y < LightmapTextureHeight; y++)
	{
		// Calculate the z value of our sample point.
		actualZ = int(y*ystep);
		
		for (int x = 0; x < LightmapTextureWidth; x++)
		{
			// Calculate the x value of our sample point.
			actualX = int(x*xstep);
			float slope = 999999999;
			float slope2 = 999999999;

			if (lightX - actualX != 0)
			{
				// Calculate the slope to the top of the light source.
				slope  = float((lightY        - data[actualX][actualZ].y)) / (lightX - actualX) * -1;
				
				// Calculate the slope to the bottom of the light source.
				slope2 = float(((lightY + 25) - data[actualX][actualZ].y)) / (lightX - actualX) * -1;
			}

			// Calculate a shadow value between 100 and 255  (255 is full light,
			// and 100 is full shadow.  This keeps the it from getting too dark).
			//
			// If the bottom of the light source is above the horizon, use full
			// light.  If not, calculate a value between 100 and 255 based on the
			// amount of the light source showing.
			int shadow = slope2 > data[actualX][actualZ].horizon ? 255 : (100 + 155 * std::max< CFloat >(0, std::min< CFloat >(1, (slope2 - slope) / (data[actualX][actualZ].horizon - slope))));
			// Calculate the lightmap value by calculating the light value using
			// the formula in the red book and combining it with the shadow value.
			lightmap[y*LightmapTextureWidth + x] = std::max< CFloat >(0, lightingX*data[actualX][actualZ].normal.x +
														lightingY*data[actualX][actualZ].normal.y  +
														lightingZ*data[actualX][actualZ].normal.z) * 
														shadow;								 												
		}
	}


	// Create a texture object for the lightmap.
	if (lightmapTexture > 0)
		glDeleteTextures(1, &lightmapTexture);
	glGenTextures(1, &lightmapTexture);


	// Create the lightmap using the data created above.
	glBindTexture(GL_TEXTURE_2D, lightmapTexture);
	glTexImage2D(GL_TEXTURE_2D, 0,  1, 
									LightmapTextureWidth, 
									LightmapTextureHeight,
									0,
									GL_LUMINANCE,
									GL_UNSIGNED_BYTE,
									lightmap);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Set up the wrap.
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_CLAMP);

	// Delete the lightmap data.
	delete [] lightmap;
}


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
void CTerrainTexture::enableTextures(void)
{
	// Lighting effects are calculated before the textures are blended,
	// so lighting wouldn't do us any good.
	// The first texture is placed, ignoring the vertex color.
	glActiveTextureARB(GL_TEXTURE0_ARB);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, groundTextures[unita]);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	// The second texture and the previous texture are combined based
	// on the vertex color.			
	glActiveTextureARB(GL_TEXTURE1_ARB);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, groundTextures[unitb]);

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE_ARB);
	glTexEnvi(GL_TEXTURE_ENV, GL_COMBINE_RGB_ARB, GL_INTERPOLATE_ARB);

	glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE0_RGB_ARB, GL_PREVIOUS_ARB);
	glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND0_RGB_ARB, GL_SRC_COLOR);

	glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE1_RGB_ARB, GL_TEXTURE);
	glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND1_RGB_ARB, GL_SRC_COLOR);

	glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE2_RGB_ARB, GL_PRIMARY_COLOR_ARB);
	glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND2_RGB_ARB, GL_SRC_COLOR);

	// The third texture and the previous result are combined based
	// on the vertex alpha value.
	glActiveTextureARB(GL_TEXTURE2_ARB);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, groundTextures[unitc]);

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE_ARB);
	glTexEnvi(GL_TEXTURE_ENV, GL_COMBINE_RGB_ARB, GL_INTERPOLATE_ARB);

	glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE0_RGB_ARB, GL_PREVIOUS_ARB);
	glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND0_RGB_ARB, GL_SRC_COLOR);

	glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE1_RGB_ARB, GL_TEXTURE);
	glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND1_RGB_ARB, GL_SRC_COLOR);

	glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE2_RGB_ARB, GL_PRIMARY_COLOR_ARB);
	glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND2_RGB_ARB, GL_SRC_ALPHA);


	// The fourth texture, the lightmap, is modulated with the
	// previous texture.
	glActiveTextureARB(GL_TEXTURE3_ARB);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, lightmapTexture);

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	//normal maps
	glActiveTextureARB(GL_TEXTURE4_ARB);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m_bottomNormalImg->GetId());

	glActiveTextureARB(GL_TEXTURE5_ARB);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m_slopeNormalImg->GetId());

	glActiveTextureARB(GL_TEXTURE6_ARB);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m_topNormalImg->GetId());


	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	glDisable(GL_LIGHTING);
}


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
void CTerrainTexture::disableTextures(void)
{
	//normal maps
	glActiveTextureARB(GL_TEXTURE6_ARB);
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);

	glActiveTextureARB(GL_TEXTURE5_ARB);
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);

	glActiveTextureARB(GL_TEXTURE4_ARB);
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);

	// Disable the texture units.
	glActiveTextureARB(GL_TEXTURE3_ARB);
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);

	glActiveTextureARB(GL_TEXTURE2_ARB);
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);

	glActiveTextureARB(GL_TEXTURE1_ARB);
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);

	glActiveTextureARB(GL_TEXTURE0_ARB);
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_LIGHTING);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);

	glClientActiveTextureARB(GL_TEXTURE0_ARB);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	glClientActiveTextureARB(GL_TEXTURE1_ARB);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	glClientActiveTextureARB(GL_TEXTURE2_ARB);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	glClientActiveTextureARB(GL_TEXTURE3_ARB);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);


}

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
void CTerrainTexture::init(heightData ***heights)
{
	m_bottomImg = CNew(CImage);
	m_bottomNormalImg = CNew(CImage);
	m_slopeImg = CNew(CImage);
	m_slopeNormalImg = CNew(CImage);
	m_topImg = CNew(CImage);
	m_topNormalImg = CNew(CImage);
	// Load our textures.
	if (groundTextures[0] == 0)
	{
		CTexture::LoadDDSTexture(m_bottomImg, g_terrain->GetBottomTexturePath(), NULL);
		CTexture::LoadDDSTexture(m_bottomNormalImg, g_terrain->GetBottomNormalMapPath(), NULL);
		CTexture::LoadDDSTexture(m_slopeImg, g_terrain->GetSlopeTexturePath(), NULL);
		CTexture::LoadDDSTexture(m_slopeNormalImg, g_terrain->GetSlopeNormalMapPath(), NULL);
		CTexture::LoadDDSTexture(m_topImg, g_terrain->GetTopTexturePath(), NULL);
		CTexture::LoadDDSTexture(m_topNormalImg, g_terrain->GetTopNormalMapPath(), NULL);

		groundTextures[0] = m_bottomImg->GetId();
		groundTextures[1] = m_slopeImg->GetId();
		groundTextures[2] = m_topImg->GetId();
	}


	// Save a copy of the heightmap data.
	data = *heights;

	// Create the texture coordinates.
	createTextureCoords();

	// Set the vertex colors which will be used to blend textures.
	createColors();

	// Create the horizon map.
	createHorizonMap();


	/////////////////////////////
	// Set up the texture combiners to blend our textures.
	/////////////////////////////


	// The first texture is placed, ignoring the vertex color.
	glActiveTextureARB(GL_TEXTURE0_ARB);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);


	// The second texture and the previous texture are combined based
	// on the vertex color.			
	glActiveTextureARB(GL_TEXTURE1_ARB);
	glEnable(GL_TEXTURE_2D);

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE_ARB);
	glTexEnvi(GL_TEXTURE_ENV, GL_COMBINE_RGB_ARB, GL_INTERPOLATE_ARB);

	glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE0_RGB_ARB, GL_PREVIOUS_ARB);
	glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND0_RGB_ARB, GL_SRC_COLOR);

	glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE1_RGB_ARB, GL_TEXTURE);
	glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND1_RGB_ARB, GL_SRC_COLOR);

	glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE2_RGB_ARB, GL_PRIMARY_COLOR_ARB);
	glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND2_RGB_ARB, GL_SRC_COLOR);

	glDisable(GL_TEXTURE_2D);


	// The third texture and the previous result are combined based
	// on the vertex alpha value.
	glActiveTextureARB(GL_TEXTURE2_ARB);
	glEnable(GL_TEXTURE_2D);

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE_ARB);
	glTexEnvi(GL_TEXTURE_ENV, GL_COMBINE_RGB_ARB, GL_INTERPOLATE_ARB);

	glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE0_RGB_ARB, GL_PREVIOUS_ARB);
	glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND0_RGB_ARB, GL_SRC_COLOR);

	glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE1_RGB_ARB, GL_TEXTURE);
	glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND1_RGB_ARB, GL_SRC_COLOR);

	glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE2_RGB_ARB, GL_PRIMARY_COLOR_ARB);
	glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND2_RGB_ARB, GL_SRC_ALPHA);

	glDisable(GL_TEXTURE_2D);


	// The fourth texture, the lightmap, is modulated with the
	// previous texture.
	glActiveTextureARB(GL_TEXTURE3_ARB);
	glEnable(GL_TEXTURE_2D);

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glDisable(GL_TEXTURE_2D);
}


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
void CTerrainTexture::changeTexture(int target)
{
	switch (target)
	{
	case GL_TEXTURE0_ARB:
	{
		unita++;
		if (unita == MaxTextures)
			unita = 0;
		glActiveTextureARB(GL_TEXTURE0_ARB);
		glBindTexture(GL_TEXTURE_2D, groundTextures[unita]);
	}
	break;
	case GL_TEXTURE1_ARB:
	{
		unitb++;
		if (unitb == MaxTextures)
			unitb = 0;
		glActiveTextureARB(GL_TEXTURE1_ARB);
		glBindTexture(GL_TEXTURE_2D, groundTextures[unitb]);
	}
	break;
	case GL_TEXTURE2_ARB:
	{
		unitc++;
		if (unitc == MaxTextures)
			unitc = 0;
		glActiveTextureARB(GL_TEXTURE2_ARB);
		glBindTexture(GL_TEXTURE_2D, groundTextures[unitc]);
	}
	break;
	}
}
