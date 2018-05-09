#ifndef MINION_H_
#define MINION_H_

#include "Component.h"

#include <string>
#include <memory>

class Minion : public Component {
private:
	std::weak_ptr<GameObject> alienCenter;
	float arc;

public:
	Minion(GameObject& associated, GameObject& alienCenter, float arcOffsetDeg);
	~Minion();
	void Shoot(Vec2 target);
	void Update(float dt);
	void Render();
	bool Is(std::string type);
};

#endif /* MINION_H_ */
