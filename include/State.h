#ifndef STATE_H_
#define STATE_H_

#include "GameObject.h"
#include "Sprite.h"
#include "Sound.h"
#include "Face.h"
#include "Music.h"

#include <vector>
#include <memory>

class State {
private:
	bool quitRequested;
	std::vector<std::unique_ptr<GameObject>> objectArray;
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
