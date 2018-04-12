#include "TileMap.h"

#include <fstream>

TileMap::TileMap(GameObject& associated, TileSet* tileSet, std::string file) : Component(associated) {
	TileMap::tileSet = tileSet;
	tileMatrix = std::vector<std::vector<std::vector<int>>>();
	Load(file);
}

TileMap::~TileMap() {
	for(int k = mapDepth-1; k >= 0; k--) {
		for(int j = mapHeight-1; j >= 0; j--)
			tileMatrix[k][j].clear();
		tileMatrix[k].clear();
	}
	tileMatrix.clear();
}

void TileMap::Load(std::string file) {
	std::ifstream fileReader("assets/map/tileMap.txt", std::ios::in);
	if(fileReader.good()) {
		int x;
		char s;
		fileReader >> mapWidth >> s >> mapHeight >> s >> mapDepth >> s;
		for(int k = 0; k < mapDepth; k++) {
			tileMatrix.emplace_back(std::vector<std::vector<int>>());
			for(int j = 0; j < mapHeight; j++) {
				tileMatrix[k].emplace_back(std::vector<int>());
				for(int i = 0; i < mapWidth; i++) {
					fileReader >> x >> s;
					tileMatrix[k][j].emplace_back(x-1);
				}
			}
		}
	}else{
		printf("Unable to read %s", file.c_str());
	}
	fileReader.close();
}

void TileMap::SetTileSet(TileSet* tileSet) {
	TileMap::tileSet = tileSet;
}

void TileMap::Update(float dt) {
	
}

void TileMap::Render() {
	for(int i = tileMatrix.size()-1; i >= 0 ; i--)
		RenderLayer(i);
}

void TileMap::RenderLayer(int layer, int cameraX, int cameraY) {
	for(int j = 0; j < tileMatrix[layer].size(); j++)
		for(int i = 0; i < tileMatrix[layer][j].size(); i++)
			tileSet->RenderTile(tileMatrix[layer][j][i], i*tileSet->GetTileWidth(), j*tileSet->GetTileHeight());
}

bool TileMap::Is(std::string type) {
	return (type == "TileMap");
}

int TileMap::At(int x, int y, int z) {
	return tileMatrix[z][y][x];
}

int TileMap::GetWidth() {
	return mapWidth;
}

int TileMap::GetHeight() {
	return mapHeight;
}

int TileMap::GetDepth() {
	return mapDepth;
}
