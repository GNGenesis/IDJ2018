#ifndef STATE_H_
#define STATE_H_

#include "GameObject.h"
#include "Music.h"
#include "Sprite.h"
#include "Sound.h"
#include "Face.h"
#include "TileMap.h"
#include "TileSet.h"

#include <vector>
#include <memory>

class State {
private:
	std::vector<std::unique_ptr<GameObject>> objectArray;
	bool quitRequested;
	GameObject* bg;
	GameObject* map;
	TileSet* set;
	Music music;

public:
	State();
	~State();
	void AddObject(int mouseX, int mouseY);
	void LoadAssets();
	void Input();
	void Update(float dt = 0);
	void Render();
	bool QuitRequested();
};

#endif /* STATE_H_ */
