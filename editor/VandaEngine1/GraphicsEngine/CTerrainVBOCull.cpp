////////////////////////////////////////////////////////////////////////////
///	\File "CTerrainVBOCull.cpp"
//
///	Author: Brian Story
//
///	Creation Date: 5/26/2005
//
///	Purpose: Implimentation of the CTerrainVBOCull class.
////////////////////////////////////////////////////////////////////////////


//Modified work: Copyright (C) 2022 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#include "stdafx.h"
#include "CTerrainVBOCull.h"
#include "..//VandaEngine1.h"
#include "Light.h"
#include <Utility.h>
//////////////////////////////////////////////////////////
///	Function: "buildBufferObjectVertexArrays"
//
///	FirstModified: 5/12/2005
//
///	\param None
//
///	Output: None
//
///	\return None
//
///	Purpose: Creates the VBO's for the heightmap.
//////////////////////////////////////////////////////////
void CTerrainVBOCull::buildBufferObjectVertexArrays(void)
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	glClientActiveTextureARB(GL_TEXTURE0_ARB);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glClientActiveTextureARB(GL_TEXTURE1_ARB);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glClientActiveTextureARB(GL_TEXTURE2_ARB);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glClientActiveTextureARB(GL_TEXTURE3_ARB);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glClientActiveTextureARB(GL_TEXTURE4_ARB);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glClientActiveTextureARB(GL_TEXTURE5_ARB);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);


	//generate tangent and bitangent vectors for normal map
	std::vector<CVec3f> verts;
	std::vector<CVec3f> tris;
	std::vector<CVec3f>norms;
	std::vector<CVec2f>tex_coords;

	for (int z = 0; z < Height; z++)
	{
		for (int x = 0; x < Width; x++)
		{
			float X = (x - (Width - 1) / 2.0f) * g_terrain->GetScaleWidth();
			float Z = (z - (Height - 1) / 2.0f) * g_terrain->GetScaleWidth();

			//vetices
			verts.push_back(CVec3f(X, data[x][z].y, Z));
			//normals
			CVec3f temp_normal(data[x][z].normal.x, data[x][z].normal.y, data[x][z].normal.z);
			norms.push_back(temp_normal);
			// Texture Coordinates.
			CVec2f temp_texture_uv(data[x][z].u, data[x][z].v);
			tex_coords.push_back(temp_texture_uv);

			if (x < Width - 1 && z < Height - 1)
			{
				CVec3f temp_tri1(x + (z * Width), x + ((z + 1) * Width), x + 1 + (z * Width));
				tris.push_back(temp_tri1);

				CVec3f temp_tri2(x + ((z + 1) * Width), x + 1 + ((z + 1) * Width), x + 1 + (z * Width));
				tris.push_back(temp_tri2);
			}

		}
	}

	//generate terrain physics
	if (g_terrain->GetCookPhysicsTriangles())
	{
		CChar path[MAX_NAME_SIZE];
		TCHAR TempFolderPath[MAX_NAME_SIZE];
		GetTempPath(MAX_NAME_SIZE, TempFolderPath);
		Cpy(path, TempFolderPath);
		Append(path, "Vanda");
		CreateWindowsDirectory(path);
		Append(path, "\\Terrain");
		CreateWindowsDirectory(path);

		CChar physicsPath[MAX_NAME_SIZE];
		Cpy(physicsPath, path);
		Append(physicsPath, "\\");
		g_terrain->SetPhysicsPath(physicsPath);

		for (int chunkZ = 0; chunkZ < int((float)(Height) / (float)(ChunkHeight - 1)); chunkZ++)
		{
			for (int chunkX = 0; chunkX < (int)((float)(Width) / (float)(ChunkWidth - 1)); chunkX++)
			{
				// Calculate the extents of the chunk.
				int startx = chunkX * (ChunkWidth - 1);
				int startz = chunkZ * (ChunkHeight - 1);
				int endx = startx + ChunkWidth;
				int endz = startz + ChunkHeight;

				std::vector<CFloat> vertices_temp;
				std::vector<CInt> triangles_temp;

				int zIndex = 0;
				int xIndex = 0;
				for (int z = startz; z < endz; z++)
				{
					for (int x = startx; x < endx; x++)
					{
						float X = (x - (Width - 1) / 2.0f) * g_terrain->GetScaleWidth();
						float Z = (z - (Height - 1) / 2.0f) * g_terrain->GetScaleWidth();

						//vertices
						vertices_temp.push_back(X);
						vertices_temp.push_back(data[x][z].y);
						vertices_temp.push_back(Z);

						if (x < endx - 1 && z < endz - 1)
						{
							triangles_temp.push_back(xIndex + (zIndex * ChunkWidth));
							triangles_temp.push_back(xIndex + ((zIndex + 1) * ChunkWidth));
							triangles_temp.push_back(xIndex + 1 + (zIndex * ChunkWidth));

							triangles_temp.push_back(xIndex + ((zIndex + 1) * ChunkWidth));
							triangles_temp.push_back(xIndex + 1 + ((zIndex + 1) * ChunkWidth));
							triangles_temp.push_back(xIndex + 1 + (zIndex * ChunkWidth));
						}
						xIndex++;
					}
					zIndex++;
					xIndex = 0;
				}
				CFloat* vertices = NULL;
				CInt* triangles = NULL;
				if (vertices_temp.size() > 0)
					vertices = &vertices_temp[0];
				if (triangles_temp.size() > 0)
					triangles = &triangles_temp[0];
				CChar chunkName[MAX_NAME_SIZE];
				sprintf(chunkName, "terrain_%d_%d", chunkX, chunkZ);

				CChar temp[MAX_NAME_SIZE];
				sprintf(temp, "\nGenerating Physics Pages: %s", chunkName);
				PrintInfo(temp);
				g_multipleView->m_nx->CookTriangleMesh((CInt)(vertices_temp.size() / 3), (CInt)(triangles_temp.size() / 3), vertices, triangles, path, chunkName);
				//g_multipleView->m_nx->CreateCookedTriangleMesh(CFalse, path, chunkName);
			}
			if (chunkZ % 5 == 0)
				ex_pVandaEngine1Dlg->UpdateWindow();
		}
	}

	CalculateTangentArray(verts.size(), tris.size(), &verts[0], &tris[0], &norms[0], &tex_coords[0]);

	// Create vertex list.
	if (bufferVertList > 0)
		glDeleteBuffers(1, &bufferVertList);
	glGenBuffers(1, &bufferVertList);

	// 'allocate' memory for the vertex list.
	glBindBuffer(GL_ARRAY_BUFFER_ARB, bufferVertList);
	glBufferData(GL_ARRAY_BUFFER_ARB, sizeof(GLfloat) * Height * Width * 16 + (sizeof(GLubyte) * Height * Width * 4), NULL, GL_STATIC_DRAW_ARB);

	// Calculate the offset in the array for the vertex, normal, and colors.
	vertOffset = 0;
	normalOffset = Height*Width * 3;
	textureCoordOffset = Height*Width * 6;
	tangentOffset = Height*Width * 8;
	bitangentOffset = Height*Width * 11;
	lightmapTexCoordOffset = Height*Width *14;
	colorOffset = Height*Width *16;


	// Copy data into the buffer objects.
	GLfloat *vertBuff = (GLfloat *)glMapBuffer(GL_ARRAY_BUFFER_ARB, GL_WRITE_ONLY_ARB);
	int currentIndex = 0;

	for (int z = 0; z < Height; z++)
	{
		for (int x = 0; x < Width; x++)
		{
			// Verticies.
			vertBuff[vertOffset] = ((float)x - (float)(Width - 1 ) / 2.0f) * g_terrain->GetScaleWidth();
			vertBuff[vertOffset + 1] = data[x][z].y;
			vertBuff[vertOffset + 2] = ((float)z - (float)(Height - 1) / 2.0f) * g_terrain->GetScaleWidth();

			vertOffset += 3;

			// Normals.
			vertBuff[normalOffset] = data[x][z].normal.x;
			vertBuff[normalOffset + 1] = data[x][z].normal.y;
			vertBuff[normalOffset + 2] = data[x][z].normal.z;
			normalOffset += 3;

			// Texture Coordinates.
			vertBuff[textureCoordOffset] = data[x][z].u;
			vertBuff[textureCoordOffset + 1] = data[x][z].v;
			textureCoordOffset += 2;

			// tangent Coordinates.
			vertBuff[tangentOffset] = m_tangents[x + (z * Width)].x;
			vertBuff[tangentOffset + 1] = m_tangents[x + (z * Width)].y;
			vertBuff[tangentOffset + 2] = m_tangents[x + (z * Width)].z;
			tangentOffset += 3;

			// bitangent Coordinates.
			vertBuff[bitangentOffset] = m_bNormals[x + (z * Width)].x;
			vertBuff[bitangentOffset + 1] = m_bNormals[x + (z * Width)].y;
			vertBuff[bitangentOffset + 2] = m_bNormals[x + (z * Width)].z;
			bitangentOffset += 3;

			// Lightmap texture Coordinates.
			vertBuff[lightmapTexCoordOffset] = data[x][z].lightU;
			vertBuff[lightmapTexCoordOffset + 1] = data[x][z].lightV;
			lightmapTexCoordOffset += 2;

			// Colors
			GLubyte *byteBuff = (GLubyte *)&vertBuff[colorOffset];
			byteBuff[0] = data[x][z].color.r;
			byteBuff[1] = data[x][z].color.g;
			byteBuff[2] = data[x][z].color.b;
			byteBuff[3] = data[x][z].color.a;
			colorOffset += 1;

		}
	}

	glUnmapBuffer(GL_ARRAY_BUFFER_ARB);

	vertOffset = 0;
	normalOffset = Height*Width * 3;
	textureCoordOffset = Height*Width * 6;
	tangentOffset = Height*Width * 8;
	bitangentOffset = Height*Width * 11;
	lightmapTexCoordOffset = Height*Width * 14;
	colorOffset = Height*Width * 16;

	// Calculate the triangle index lists for each chunk.
	for (int chunkZ = 0; chunkZ < int((float)(Height) / (float)(ChunkHeight - 1)); chunkZ++)
	{
		for (int chunkX = 0; chunkX < (int)((float)(Width) / (float)(ChunkWidth - 1)); chunkX++)
		{
			// Create the index buffer.
			if (chunkArray[chunkX][chunkZ].bufferTriList > 0)
				glDeleteBuffers(1, &chunkArray[chunkX][chunkZ].bufferTriList);
			glGenBuffers(1, &chunkArray[chunkX][chunkZ].bufferTriList);

			// 'allocate' memory for the buffer.
			numElements = ((ChunkHeight - 1) * (ChunkWidth * 2 + 2)) - 2;
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER_ARB, chunkArray[chunkX][chunkZ].bufferTriList);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER_ARB, sizeof(GLuint) * numElements, NULL, GL_STATIC_DRAW_ARB);


			// Fill triangle buffer.
			GLuint *triBuff = (GLuint *)glMapBuffer(GL_ELEMENT_ARRAY_BUFFER_ARB, GL_WRITE_ONLY_ARB);
			currentIndex = 0;

			// Calculate the extents of the chunk.
			int startx = chunkX * (ChunkWidth - 1);
			int startz = chunkZ * (ChunkHeight - 1);
			int endx = startx + ChunkWidth;
			int endz = startz + ChunkHeight;

			// Initialize the min and max values based on the first vertex.
			float maxX, maxY, maxZ;
			float minX, minY, minZ;

			maxX = (startx - (Width - 1) / 2.f) * g_terrain->GetScaleWidth();
			minX = (startx - (Width - 1) / 2.f) * g_terrain->GetScaleWidth();
			maxY = data[startx][startz].y;
			minY = data[startx][startz].y;
			maxZ = (startz - (Height - 1) / 2.f) * g_terrain->GetScaleWidth();
			minZ = (startz - (Height - 1) / 2.f) * g_terrain->GetScaleWidth();

			// Loop through the chunk extents and create the list.
			for (int z = startz; z < endz - 1; z++)
			{
				for (int x = startx; x < endx; x++)
				{
					float X = (x - (Width - 1) / 2.f) * g_terrain->GetScaleWidth();
					float Z = (z - (Height - 1) / 2.f) * g_terrain->GetScaleWidth();
					// Update the min and max values.
					maxX = maxX > X ? maxX : X;
					minX = minX < X ? minX : X;
					maxY = maxY > data[x][z].y ? maxY : data[x][z].y;
					minY = minY < data[x][z].y ? minY : data[x][z].y;
					maxZ = maxZ > Z ? maxZ : Z;
					minZ = minZ < Z ? minZ : Z;

					// Used for degenerate triangles.
					if (x == startx && z != startz)
						triBuff[currentIndex++] = x + (z * Width);

					triBuff[currentIndex++] = x + (z * Width);
					triBuff[currentIndex++] = x + ((z + 1) * Width);

					// Used for degenerate triangles.
					if (x == endx - 1 && z != endz - 2)
						triBuff[currentIndex++] = x + ((z + 1) * Width);
				}
			}

			glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER_ARB);

			// Assign the min and max values found.
			chunkArray[chunkX][chunkZ].maxX = maxX;
			chunkArray[chunkX][chunkZ].maxY = maxY;
			chunkArray[chunkX][chunkZ].maxZ = maxZ;
			chunkArray[chunkX][chunkZ].minX = minX;
			chunkArray[chunkX][chunkZ].minY = minY;
			chunkArray[chunkX][chunkZ].minZ = minZ;

			CVec3f min_box(minX, minY, minZ);
			CVec3f max_box(maxX, maxY, maxZ);
			chunkArray[chunkX][chunkZ].center = (min_box + max_box) * 0.5f;
			chunkArray[chunkX][chunkZ].radius = (max_box - chunkArray[chunkX][chunkZ].center).Size();
		}
	}
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

	glClientActiveTextureARB(GL_TEXTURE4_ARB);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	glClientActiveTextureARB(GL_TEXTURE5_ARB);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}


CVoid CTerrainVBOCull::SetLight(CVec3f minAABB, CVec3f maxAABB, chunk* chunkArray)
{
	chunkArray->m_totalVisibleLights = 0;
	if (chunkArray->m_lightCooked)
	{
		if (g_engineLights.size() == 0)
		{
			chunkArray->m_totalLights = 1.0f; //default point light attached to the camera
			return;
		}

		for (CUInt j = 0; j < chunkArray->m_totalLights; j++)
		{
			if (chunkArray->m_lights[j])
			{
				CBool isDirectional = CFalse;
				CBool isDefaultDirectional = CFalse;

				if (chunkArray->m_lights[j]->m_abstractLight->GetType() == eLIGHTTYPE_DIRECTIONAL)
					isDirectional = CTrue;
				else if (!chunkArray->m_lights[j]->GetRunTimeVisible()) //it's point or spot light
					continue;

				if (isDirectional && Cmp(g_shadowProperties.m_directionalLightName, chunkArray->m_lights[j]->m_abstractLight->GetName()))
					isDefaultDirectional = CTrue;
				g_render.SetInstanceLight(chunkArray->m_lights[j], chunkArray->m_totalVisibleLights, isDefaultDirectional);
				chunkArray->m_totalVisibleLights++;
			}
		}
		return;
	}

	if (g_engineLights.size() == 0)
	{
		chunkArray->m_totalLights = 1.0f; //default point light attached to the camera
		return;
	}
	for (CUInt i = 0; i < 8; i++)
	{
		chunkArray->m_lights[i] = NULL;
	}
	chunkArray->m_totalLights = 0;

	CInt directional_light_index = 0;
	for (CUInt i = 0; i < g_engineLights.size(); i++)
	{
		if (g_engineLights[i]->m_abstractLight->GetType() == eLIGHTTYPE_DIRECTIONAL)
		{
			chunkArray->m_lights[directional_light_index] = g_engineLights[i];
			directional_light_index++;
			if (directional_light_index >= NR_DIR_LIGHTS)
				break;
		}
	}
	CInt point_light_index = 0;
	for (CUInt i = 0; i < g_engineLights.size(); i++)
	{
		if (g_engineLights[i]->m_abstractLight->GetType() == eLIGHTTYPE_POINT)
		{
			if (DoesLightIntersectsChunk(minAABB, maxAABB, g_engineLights[i]->GetPosition(), g_engineLights[i]->GetRadius()))
			{
				chunkArray->m_lights[point_light_index + directional_light_index] = g_engineLights[i];
				point_light_index++;
				if (point_light_index >= NR_TERRAIN_POINT_LIGHTS)
					break;
			}
		}
	}
	CInt spot_light_index = 0;
	for (CUInt i = 0; i < g_engineLights.size(); i++)
	{
		if (g_engineLights[i]->m_abstractLight->GetType() == eLIGHTTYPE_SPOT)
		{
			if (DoesLightIntersectsChunk(minAABB, maxAABB, g_engineLights[i]->GetPosition(), g_engineLights[i]->GetRadius()))
			{
				chunkArray->m_lights[spot_light_index + point_light_index + directional_light_index] = g_engineLights[i];
				spot_light_index++;
				if (spot_light_index >= NR_TERRAIN_SPOT_LIGHTS)
					break;
			}
		}
	}

	chunkArray->m_totalLights = directional_light_index + point_light_index + spot_light_index;

	//set all lights here
	for (CUInt j = 0; j < chunkArray->m_totalLights; j++)
	{
		if (chunkArray->m_lights[j])
		{
			CBool isDirectional = CFalse;
			CBool isDefaultDirectional = CFalse;
			if (chunkArray->m_lights[j]->m_abstractLight->GetType() == eLIGHTTYPE_DIRECTIONAL)
				isDirectional = CTrue;
			if (isDirectional && Cmp(g_shadowProperties.m_directionalLightName, chunkArray->m_lights[j]->m_abstractLight->GetName()))
				isDefaultDirectional = CTrue;
			g_render.SetInstanceLight(chunkArray->m_lights[j], j, isDefaultDirectional);
		}
	}
	chunkArray->m_totalVisibleLights = chunkArray->m_totalLights;
	chunkArray->m_lightCooked = CTrue;
}

void CTerrainVBOCull::SetLightCooked(CBool cook)
{
	for (int z = 0; z < Height / (ChunkHeight - 1); z++)
	{
		for (int x = 0; x < Width / (ChunkWidth - 1); x++)
		{
			chunkArray[x][z].SetLightCooked(cook);
		}
	}
}

void CTerrainVBOCull::calculateDistance(CVec3f center1, CVec3f center2, CFloat & distance)
{
	CFloat x = center2.x - center1.x;
	CFloat y = center2.y - center1.y;
	CFloat z = center2.z - center1.z;

	distance = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
}

//draw chunks for dynamic shadow
void CTerrainVBOCull::drawShadow()
{
	glUseProgram(0);
	glEnableClientState(GL_VERTEX_ARRAY);
	glDisable(GL_LIGHTING);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glScalef(0.1f, 0.1f, 0.1f);
	glBindBuffer(GL_ARRAY_BUFFER_ARB, bufferVertList);
	glVertexPointer(3, GL_FLOAT, 0, (float *)NULL + vertOffset);

	// Loop through the chunks.
	for (int z = 0; z < Height / (ChunkHeight - 1); z++)
	{
		for (int x = 0; x < Width / (ChunkWidth - 1); x++)
		{
			if (chunkArray[x][z].GetDistanceFromCamera() > g_shadowProperties.m_shadowFarClipPlane + chunkArray[x][z].GetRadius()) continue;

			// bind the buffer and draw the chunk.

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER_ARB, chunkArray[x][z].bufferTriList);
			glDrawElements(GL_TRIANGLE_STRIP, numElements, GL_UNSIGNED_INT, 0);

		}
	}
	glBindBuffer(GL_ARRAY_BUFFER_ARB, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER_ARB, 0);
	glPopMatrix();
	glDisableClientState(GL_VERTEX_ARRAY);
	glEnable(GL_LIGHTING);

}

void CTerrainVBOCull::CalculateTangentArray(CInt vertexCount, CInt triangleCount, CVec3f* meshVertices, CVec3f* meshTriangles, CVec3f* normals, CVec2f* texCoords)
{
	m_bNormals = CNewData(CVec3f, vertexCount);
	m_tangents = CNewData(CVec3f, vertexCount);

	CVec3f* tangentTemp = CNewData(CVec3f, vertexCount);

	for (CInt a = 0; a < triangleCount; a++)
	{
		CUInt i1 = meshTriangles[a].x;
		CUInt i2 = meshTriangles[a].y;
		CUInt i3 = meshTriangles[a].z;

		const CVec3f v1 = meshVertices[i1];
		const CVec3f v2 = meshVertices[i2];
		const CVec3f v3 = meshVertices[i3];

		const CVec2f w1 = texCoords[i1];
		const CVec2f w2 = texCoords[i2];
		const CVec2f w3 = texCoords[i3];

		float x1 = v2.x - v1.x;
		float x2 = v3.x - v1.x;
		float y1 = v2.y - v1.y;
		float y2 = v3.y - v1.y;
		float z1 = v2.z - v1.z;
		float z2 = v3.z - v1.z;

		float s1 = w2.x - w1.x;
		float s2 = w3.x - w1.x;
		float t1 = w2.y - w1.y;
		float t2 = w3.y - w1.y;

		float r = 1.0f / (s1 * t2 - s2 * t1);
		CVec3f sdir((t2 * x1 - t1 * x2) * r, (t2 * y1 - t1 * y2) * r,
			(t2 * z1 - t1 * z2) * r);

		tangentTemp[i1] += sdir;
		tangentTemp[i2] += sdir;
		tangentTemp[i3] += sdir;
	}

	for (CInt a = 0; a < vertexCount; a++)
	{
		const CVec3f& n = normals[a];
		const CVec3f& t = tangentTemp[a];
		CVec3f dotProduct;
		m_tangents[a] = (t - n * dotProduct.DotProduct(&n, &t)).Normalize();
		CVec3f crossProduct;
		m_bNormals[a] = crossProduct.CrossProduct(&n, &m_tangents[a]);
	}
	CDeleteData(tangentTemp);
}

void CTerrainVBOCull::resetPhysXActors()
{
	for (int z = 0; z < Height / (ChunkHeight - 1); z++)
	{
		for (int x = 0; x < Width / (ChunkWidth - 1); x++)
		{
			chunkArray[x][z].SetActor(NULL);
			chunkArray[x][z].m_attachedActors.clear();
		}
	}
}
//////////////////////////////////////////////////////////
///	Function: "drawBufferObjectVertexArrays"
//
///	FirstModified: 5/12/2005
//
///	\param bool boundingBox		True if the bounding boxes are to be displayed.
//
///	Output: None
//
///	\return None
//
///	Purpose: Draws the VBO's for the heightmap.
//////////////////////////////////////////////////////////
void CTerrainVBOCull::draw()
{
	if (bufferVertList == 0)
		return;
	glMatrixMode(GL_MODELVIEW);
	CFloat lightMatrix[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, lightMatrix);
	glPushMatrix();
	//glTranslatef(-256.0, 0.0, -256.0);
	//glScalef(0.5f, 0.5f, 0.5f);

	CColor4f ambient(g_terrain->GetAmbientColor()[0], g_terrain->GetAmbientColor()[1], g_terrain->GetAmbientColor()[2], g_terrain->GetAmbientColor()[3]);
	CColor4f diffuse(g_terrain->GetDiffuseColor()[0], g_terrain->GetDiffuseColor()[1], g_terrain->GetDiffuseColor()[2], g_terrain->GetDiffuseColor()[3]);
	CColor4f specular(g_terrain->GetSpecularColor()[0], g_terrain->GetSpecularColor()[1], g_terrain->GetSpecularColor()[2], g_terrain->GetSpecularColor()[3]);
	CFloat	shininess = g_terrain->GetShininess();

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, (GLfloat*)&ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, (GLfloat*)&diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, (GLfloat*)&specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, (GLfloat)shininess);

	// Set up the vertex list.

	glBindBuffer(GL_ARRAY_BUFFER_ARB, bufferVertList);
	glVertexPointer(3, GL_FLOAT, 0, (float *)NULL + vertOffset);
	glNormalPointer(GL_FLOAT, 0, (float *)NULL + normalOffset);
	glColorPointer(4, GL_UNSIGNED_BYTE, 0, (float *)NULL + colorOffset);

	glClientActiveTextureARB(GL_TEXTURE0_ARB);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glTexCoordPointer(2, GL_FLOAT, 0, (float *)NULL + textureCoordOffset);

	glClientActiveTextureARB(GL_TEXTURE1_ARB);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glTexCoordPointer(2, GL_FLOAT, 0, (float *)NULL + textureCoordOffset);

	glClientActiveTextureARB(GL_TEXTURE2_ARB);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glTexCoordPointer(2, GL_FLOAT, 0, (float *)NULL + textureCoordOffset);

	glClientActiveTextureARB(GL_TEXTURE3_ARB);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glTexCoordPointer(2, GL_FLOAT, 0, (float *)NULL + lightmapTexCoordOffset);

	glClientActiveTextureARB(GL_TEXTURE4_ARB);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glTexCoordPointer(3, GL_FLOAT, 0, (float *)NULL + tangentOffset);

	glClientActiveTextureARB(GL_TEXTURE5_ARB);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glTexCoordPointer(3, GL_FLOAT, 0, (float *)NULL + bitangentOffset);


	CMatrix Matrix;

	if (m_updateMinMaxCenter)
	{
		//CVec4f trans(-256.0f, 0.0f, -256.0f, 1.0f);
		//CVec4f rot(0.0f, 1.0f, 0.0f, 0.0f);
		//CVec4f scale(0.5f, 0.5f, 0.5f, 1.0f);

		CMatrixLoadIdentity(Matrix);
		//CMatrix4x4Translate(Matrix, trans);
		//CMatrix4x4RotateAngleAxis(Matrix, rot);
		//CMatrix4x4Scale(Matrix, scale);
	}

	// Loop through the chunks.
	for (int z = 0; z < int(Height / (ChunkHeight - 1)); z++)
	{
		for (int x = 0; x < int(Width / (ChunkWidth - 1)); x++)
		{
			if (m_updateMinMaxCenter)
			{
				float maxX = chunkArray[x][z].maxX;
				float maxY = chunkArray[x][z].maxY;
				float maxZ = chunkArray[x][z].maxZ;
				float minX = chunkArray[x][z].minX;
				float minY = chunkArray[x][z].minY;
				float minZ = chunkArray[x][z].minZ;

				CVec3f min_box(minX, minY, minZ);
				CVec3f max_box(maxX, maxY, maxZ);

				CMatrixTransform(Matrix, min_box, chunkArray[x][z].min_t);
				CMatrixTransform(Matrix, max_box, chunkArray[x][z].max_t);

				chunkArray[x][z].center = (chunkArray[x][z].min_t + chunkArray[x][z].max_t) * 0.5f;
				chunkArray[x][z].radius = (chunkArray[x][z].max_t - chunkArray[x][z].center).Size() * 1.1f;
			}

			glPushMatrix();
			glLoadMatrixf(lightMatrix);
			SetLight(chunkArray[x][z].min_t, chunkArray[x][z].max_t, &chunkArray[x][z]);
			glPopMatrix();

			CInt num_point_lights = 0;
			CInt num_spot_lights = 0;
			CInt num_dir_lights = 0;
			//I support up to NR_DIR_LIGHTS directional light, up to NR_TERRAIN_POINT_LIGHTS point lights, and up to NR_TERRAIN_SPOT_LIGHTS spot lights for each chunk
			if (g_engineLights.size() == 0)
			{
				glUniform1f(glGetUniformLocation(g_shaderType, "point_light_radius[0]"), 1000000);
				glUniform1i(glGetUniformLocation(g_shaderType, "nr_dir_lights"), 0);
				glUniform1i(glGetUniformLocation(g_shaderType, "nr_point_lights"), 1);
				glUniform1i(glGetUniformLocation(g_shaderType, "nr_spot_lights"), 0);

			}
			else
			{
				for (CUInt i = 0; i < chunkArray[x][z].m_totalVisibleLights; i++)
				{
					CInstanceLight *instanceLight = chunkArray[x][z].m_lights[i];

					if (instanceLight->m_abstractLight->GetType() == eLIGHTTYPE_DIRECTIONAL)
					{
						if (Cmp(g_shadowProperties.m_directionalLightName, instanceLight->m_abstractLight->GetName()))
							glUniform1i(glGetUniformLocation(g_shaderType, "defaultDirLightIndex"), i);
						
						num_dir_lights++;
					}

					if (instanceLight->m_abstractLight->GetType() == eLIGHTTYPE_POINT)
					{
						num_point_lights++;
						if (num_point_lights == 1)
							glUniform1f(glGetUniformLocation(g_shaderType, "point_light_radius[0]"), instanceLight->GetRadius());
						//else if (num_point_lights == 2)
						//	glUniform1f(glGetUniformLocation(g_shaderType, "point_light_radius[1]"), instanceLight->GetRadius());
						//else if (num_point_lights == 3)
						//	glUniform1f(glGetUniformLocation(g_shaderType, "point_light_radius[2]"), instanceLight->GetRadius());
						//else if (num_point_lights == 4)
						//	glUniform1f(glGetUniformLocation(g_shaderType, "point_light_radius[3]"), instanceLight->GetRadius());
					}

					if (instanceLight->m_abstractLight->GetType() == eLIGHTTYPE_SPOT)
					{
						num_spot_lights++;
						if (num_spot_lights == 1)
							glUniform1f(glGetUniformLocation(g_shaderType, "spot_light_radius[0]"), instanceLight->GetRadius());
					}

				}
				glUniform1i(glGetUniformLocation(g_shaderType, "nr_dir_lights"), num_dir_lights);
				glUniform1i(glGetUniformLocation(g_shaderType, "nr_point_lights"), num_point_lights);
				glUniform1i(glGetUniformLocation(g_shaderType, "nr_spot_lights"), num_spot_lights);
			}

			if (!g_camera->m_cameraManager->IsSphereInFrustum(chunkArray[x][z].center.x, chunkArray[x][z].center.y, chunkArray[x][z].center.z, chunkArray[x][z].radius))
				continue;

			// bind the buffer and draw the chunk.

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER_ARB, chunkArray[x][z].bufferTriList);
			glDrawElements(GL_TRIANGLE_STRIP, numElements, GL_UNSIGNED_INT, 0);
		}
	}
	if (m_updateMinMaxCenter)
	{
		m_updateMinMaxCenter = CFalse;
	}

	glClientActiveTextureARB(GL_TEXTURE0_ARB);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	glClientActiveTextureARB(GL_TEXTURE1_ARB);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	glClientActiveTextureARB(GL_TEXTURE2_ARB);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	glClientActiveTextureARB(GL_TEXTURE3_ARB);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	glClientActiveTextureARB(GL_TEXTURE4_ARB);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	glClientActiveTextureARB(GL_TEXTURE5_ARB);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	glBindBuffer(GL_ARRAY_BUFFER_ARB, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER_ARB, 0);
	glUseProgram(0);
	glPopMatrix();
}

CBool CTerrainVBOCull::DoesLightIntersectsChunk(CVec3f C1, CVec3f C2, CVec3f S, CFloat R)
{
	CFloat dist_squared = R * R;
	/* assume C1 and C2 are element-wise sorted, if not, do that now */
	if (S.x < C1.x) dist_squared -= squared(S.x - C1.x);
	else if (S.x > C2.x) dist_squared -= squared(S.x - C2.x);
	if (S.y < C1.y) dist_squared -= squared(S.y - C1.y);
	else if (S.y > C2.y) dist_squared -= squared(S.y - C2.y);
	if (S.z< C1.z) dist_squared -= squared(S.z - C1.z);
	else if (S.z > C2.z) dist_squared -= squared(S.z - C2.z);
	return dist_squared > 0;
}

CVoid CTerrainVBOCull::ManagePhysXTriangleActorForCharacterController(CInt x, CInt z)
{
	if (g_multipleView->IsPlayGameMode())
	{
		for (CUInt k = 0; k < gPhysXscene->getNbActors(); k++)
		{
			//Start Of Load/Unload PhysX Actors
			if (gPhysXscene->getActors()[k]->isDynamic() && !gPhysXscene->getActors()[k]->isSleeping())
			{
				if (!gPhysXscene->getActors()[k]->getName()) //character controller
				{
					CChar actorName[MAX_NAME_SIZE];
					Cpy(actorName, "MainCharacterController");
					NxActor* currentActor = gPhysXscene->getActors()[k];

					//get the distance from Chunk center to PhysX actor center
					CFloat distance;
					CVec3f ActorPos(gPhysXscene->getActors()[k]->getGlobalPosition().x, gPhysXscene->getActors()[k]->getGlobalPosition().y, gPhysXscene->getActors()[k]->getGlobalPosition().z);
					calculateDistance(chunkArray[x][z].center, ActorPos, distance);

					CFloat radius;
					if (g_mainCharacter)
					{
						radius = g_mainCharacter->GetInstancePrefab()->GetRadius();

					}
					else
					{
						radius = g_physXProperties.m_fCapsuleRadius;
					}
					if (distance < chunkArray[x][z].radius + (5.0f * radius))
					{
						if (chunkArray[x][z].m_attachedActors.size() == 0)
						{
							chunkArray[x][z].m_attachedActors.push_back(actorName);

							//Load Chunk PhysX 
							sprintf(chunkArray[x][z].m_chunkName, "terrain_%d_%d", x, z);

							CPhysXMaterial physicsMaterial;

							NxActor* actor = g_multipleView->m_nx->CreateCookedTriangleMesh(CFalse, g_terrain->GetPhysicsPath(), chunkArray[x][z].m_chunkName, physicsMaterial);
							chunkArray[x][z].SetActor(actor);
						}
						else
						{
							CBool foundTarget = false;
							for (CUInt i = 0; i < chunkArray[x][z].m_attachedActors.size(); i++)
							{
								if (Cmp(chunkArray[x][z].m_attachedActors[i].c_str(), actorName))
								{
									foundTarget = CTrue;
									break;
								}
							}
							if (!foundTarget)
							{
								chunkArray[x][z].m_attachedActors.push_back(actorName);
							}
						}
					}
					else
					{
						if (chunkArray[x][z].m_attachedActors.size() > 0)
						{
							for (CUInt i = 0; i < chunkArray[x][z].m_attachedActors.size(); i++)
							{
								if (Cmp(chunkArray[x][z].m_attachedActors[i].c_str(), actorName))
								{
									chunkArray[x][z].m_attachedActors.erase(chunkArray[x][z].m_attachedActors.begin() + i);
									break;
								}
							}
							if (chunkArray[x][z].m_attachedActors.size() == 0)
							{
								gPhysXscene->releaseActor(*chunkArray[x][z].GetActor());
								chunkArray[x][z].SetActor(NULL);
							}
						}
					}
					break;
				}
			}
		}
	}

}

CVoid CTerrainVBOCull::ManagePhysXTriangleActorsForPrefabInstance(CInt x, CInt z)
{
	if (g_multipleView->IsPlayGameMode())
	{
		for (CUInt p = 0; p < g_instancePrefab.size(); p++)
		{
			if (!g_instancePrefab[p]->GetIsControlledByPhysX()) continue;

			for (CUInt i = 0; i < 4; i++)
			{
				CBool checkState = CFalse;
				if (i < 3)
				{
					if (g_instancePrefab[p]->GetPrefab()->GetHasLod(i))
						checkState = CTrue;
				}
				else
				{
					if (g_instancePrefab[p]->GetHasCollider())
						checkState = CTrue;
				}
				if (checkState)
				{
					CScene* scene = g_instancePrefab[p]->GetScene(i);
					if (!scene) continue;
					if (!scene->m_isTrigger)
					{
						for (CUInt j = 0; j < scene->m_instanceGeometries.size(); j++)
						{
							if (scene->m_instanceGeometries[j]->GetHasPhysXActor() && scene->m_instanceGeometries[j]->GetPhysXActorDensity() > 0.0f)
							{
								for (CUInt k = 0; k < gPhysXscene->getNbActors(); k++)
								{
									CBool foundActorTarget = CFalse;
									//Start Of Load/Unload PhysX Actors
									if (gPhysXscene->getActors()[k]->isDynamic() && !gPhysXscene->getActors()[k]->isSleeping())
									{
										CChar actorName[MAX_NAME_SIZE];
										if (!gPhysXscene->getActors()[k]->getName()) continue; //main character
										Cpy(actorName, gPhysXscene->getActors()[k]->getName());
										if (Cmp(scene->m_instanceGeometries[j]->GetPhysXActorName(), actorName))
										{
											foundActorTarget = CTrue;
											NxActor* currentActor = gPhysXscene->getActors()[k];

											//get the distance from Chunk center to PhysX actor center
											CFloat distance;
											CVec3f ActorPos(g_instancePrefab[p]->GetCenter().x, g_instancePrefab[p]->GetCenter().y, g_instancePrefab[p]->GetCenter().z);
											calculateDistance(chunkArray[x][z].center, ActorPos, distance);
											if (distance < chunkArray[x][z].radius + (5.0f * g_instancePrefab[p]->GetRadius()))
											{
												if (chunkArray[x][z].m_attachedActors.size() == 0)
												{
													chunkArray[x][z].m_attachedActors.push_back(actorName);

													//Load Chunk PhysX 
													sprintf(chunkArray[x][z].m_chunkName, "terrain_%d_%d", x, z);

													CPhysXMaterial physicsMaterial;

													NxActor* actor = g_multipleView->m_nx->CreateCookedTriangleMesh(CFalse, g_terrain->GetPhysicsPath(), chunkArray[x][z].m_chunkName, physicsMaterial);
													chunkArray[x][z].SetActor(actor);
												}
												else
												{
													CBool foundTarget = false;
													for (CUInt i = 0; i < chunkArray[x][z].m_attachedActors.size(); i++)
													{
														if (Cmp(chunkArray[x][z].m_attachedActors[i].c_str(), actorName))
														{
															foundTarget = CTrue;
															break;
														}
													}
													if (!foundTarget)
													{
														chunkArray[x][z].m_attachedActors.push_back(actorName);
													}
												}
											}
											else
											{
												if (chunkArray[x][z].m_attachedActors.size() > 0)
												{
													for (CUInt i = 0; i < chunkArray[x][z].m_attachedActors.size(); i++)
													{
														if (Cmp(chunkArray[x][z].m_attachedActors[i].c_str(), actorName))
														{
															chunkArray[x][z].m_attachedActors.erase(chunkArray[x][z].m_attachedActors.begin() + i);
															break;
														}
													}
													if (chunkArray[x][z].m_attachedActors.size() == 0)
													{
														gPhysXscene->releaseActor(*chunkArray[x][z].GetActor());
														chunkArray[x][z].SetActor(NULL);
													}
												}
											}
										}
									}
									if (foundActorTarget)
										break;
									//End of Load/Unload
								}
							}
						}
					}
				}
			}
		}
	}

}

CVoid CTerrainVBOCull::DrawBoundingBox()
{
	// Loop through the chunks.
	for (int z = 0; z < int(Height / (ChunkHeight - 1)); z++)
	{
		for (int x = 0; x < int(Width / (ChunkWidth - 1)); x++)
		{
			if (!g_camera->m_cameraManager->IsSphereInFrustum(chunkArray[x][z].center.x, chunkArray[x][z].center.y, chunkArray[x][z].center.z, chunkArray[x][z].radius))
				continue;

			glUseProgram(0);
			glPushAttrib(GL_CURRENT_BIT | GL_ENABLE_BIT | GL_LINE_BIT);
			glDisable(GL_BLEND);
			glDisable(GL_FOG);
			glDisable(GL_LIGHTING);
			glDisable(GL_TEXTURE_2D);
			glDisable(GL_MULTISAMPLE);
			glLineWidth(0.5f);

			float maxX = chunkArray[x][z].maxX;
			float maxY = chunkArray[x][z].maxY;
			float maxZ = chunkArray[x][z].maxZ;
			float minX = chunkArray[x][z].minX;
			float minY = chunkArray[x][z].minY;
			float minZ = chunkArray[x][z].minZ;

			glColor4f(1.0f, 1.0f, 0.0f, 0.0f);
			glBegin(GL_LINES);
			glVertex3f(maxX, maxY, maxZ);
			glVertex3f(minX, maxY, maxZ);
			glVertex3f(minX, maxY, maxZ);
			glVertex3f(minX, maxY, minZ);

			glVertex3f(minX, maxY, minZ);
			glVertex3f(maxX, maxY, minZ);
			glVertex3f(maxX, maxY, minZ);
			glVertex3f(maxX, maxY, maxZ);

			glVertex3f(maxX, minY, maxZ);
			glVertex3f(minX, minY, maxZ);
			glVertex3f(minX, minY, maxZ);
			glVertex3f(minX, minY, minZ);

			glVertex3f(minX, minY, minZ);
			glVertex3f(maxX, minY, minZ);
			glVertex3f(maxX, minY, minZ);
			glVertex3f(maxX, minY, maxZ);

			glVertex3f(maxX, maxY, maxZ);
			glVertex3f(maxX, minY, maxZ);
			glVertex3f(maxX, maxY, minZ);
			glVertex3f(maxX, minY, minZ);

			glVertex3f(minX, maxY, minZ);
			glVertex3f(minX, minY, minZ);
			glVertex3f(minX, maxY, maxZ);
			glVertex3f(minX, minY, maxZ);

			glEnd();
			glPopAttrib();
		}
	}
}

CVoid CTerrainVBOCull::ManagePhysics()
{
	for (int z = 0; z < int(Height / (ChunkHeight - 1)); z++)
	{
		for (int x = 0; x < int(Width / (ChunkWidth - 1)); x++)
		{
			//Load/Unload Terrain PhysX Triangle Meshes Here:
			ManagePhysXTriangleActorsForPrefabInstance(x, z);
			ManagePhysXTriangleActorForCharacterController(x, z);
		}
	}
}