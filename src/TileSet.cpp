#include "TileSet.h"

TileSet::TileSet(GameObject& associated, std::string file, int tileWidth, int tileHeight) {
	tileSet = new Sprite(associated, file);
	TileSet::tileWidth = tileWidth;
	TileSet::tileHeight = tileHeight;
	rows = tileSet->GetHeight()/tileHeight;
	columns = tileSet->GetWidth()/tileWidth;
}

TileSet::~TileSet() {
	printf("Here1\n");
	delete tileSet;
	printf("Here3\n");
}

void TileSet::RenderTile(int index, int x, int y) {
	if(rows*columns > index) {
		tileSet->SetClip(tileWidth*(index%columns), tileHeight*(index/columns), tileWidth, tileHeight);
		tileSet->Render(x, y);
	}
}

int TileSet::GetTileWidth() {
	return tileWidth;
}

int TileSet::GetTileHeight() {
	return tileHeight;
}
