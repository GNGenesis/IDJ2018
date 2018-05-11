#ifndef ALIEN_H_
#define ALIEN_H_

#include "Component.h"
#include "Timer.h"

#include <string>
#include <vector>
#include <memory>

class Alien : public Component {
private:
	int hp;
	Vec2 speed;
	int nMinions;
	std::vector<std::weak_ptr<GameObject>> minionArray;

	enum AlienState { RESTING, MOVING };
	AlienState state;
	Timer restTimer;
	float restTime;
	Vec2 destination;

public:
	static int alienCount;

	Alien(GameObject& associated, int nMinions);
	~Alien();
	void Start();
	void Damage(int damage);
	void Update(float dt);
	void Render();
	void NotifyCollision(GameObject& other);
	bool Is(std::string type);
};

#endif /* ALIEN_H_ */
