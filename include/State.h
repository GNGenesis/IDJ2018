#ifndef STATE_H_
#define STATE_H_

#include "Sprite.h"
#include "Music.h"

class State {
private:
	Sprite bg;
	Music music;
	bool quitRequested;

public:
	State();
	~State();
	void LoadAssets();
	void Input();
	void Update(float dt = 0);
	void Render();
	bool QuitRequested();
};

#endif /* STATE_H_ */
