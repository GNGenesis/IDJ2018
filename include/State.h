#ifndef STATE_H_
#define STATE_H_

#include "GameObject.h"
#include "Music.h"
#include "TileSet.h"

#include <vector>
#include <memory>

class State {
private:
	std::vector<std::shared_ptr<GameObject>> objectArray;
	bool started;
	bool quitRequested;
	GameObject* bg;
	GameObject* map;
	TileSet* set;
	Music music;

public:
	State();
	~State();
	void Start();
	std::weak_ptr<GameObject> AddObject(GameObject* go);
	std::weak_ptr<GameObject> GetObjectPtr(GameObject* go);
	void LoadAssets();
	void Update(float dt);
	void Render();
	bool QuitRequested();
};

#endif /* STATE_H_ */
