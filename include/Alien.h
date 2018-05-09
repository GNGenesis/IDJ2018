#ifndef ALIEN_H_
#define ALIEN_H_

#include "Component.h"

#include <string>
#include <vector>
#include <queue>
#include <memory>

class Alien : public Component {
private:
	class Action {
	public:
		enum ActionType {MOVE, SHOOT};
		ActionType type;
		Vec2 pos;

		Action(ActionType type, float x, float y);
	};

	int hp;
	Vec2 speed;
	int nMinions;
	std::queue<Action> taskQueue;
	std::vector<std::weak_ptr<GameObject>> minionArray;

public:
	Alien(GameObject& associated, int nMinions);
	~Alien();
	void Start();
	void Update(float dt);
	void Render();
	bool Is(std::string type);
};

#endif /* ALIEN_H_ */
