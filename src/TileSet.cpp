#include "TileSet.h"

TileSet::TileSet(GameObject& associated, std::string file, int tileWidth, int tileHeight) : tileSet(associated, file) {
	TileSet::tileWidth = tileWidth;
	TileSet::tileHeight = tileHeight;
	rows = tileSet.GetHeight()/tileHeight;
	columns = tileSet.GetWidth()/tileWidth;
}

TileSet::~TileSet() {

}

void TileSet::RenderTile(int index, int x, int y) {
	if(index < rows*columns) {
		tileSet.SetClip(tileWidth*(index%columns), tileHeight*(index/columns), tileWidth, tileHeight);
		tileSet.Render(x, y);
	}
}

int TileSet::GetTileWidth() {
	return tileWidth;
}

int TileSet::GetTileHeight() {
	return tileHeight;
}
