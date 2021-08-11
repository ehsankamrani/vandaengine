#ifndef TERRAINRENDER_H
#define TERRAINRENDER_H

	void renderTerrain(const TerrainData& terrain, bool addWireframe=true);
	void renderTerrainTriangles(const TerrainData& terrain, NxU32 nbTriangles, const NxU32* indices);

#endif
