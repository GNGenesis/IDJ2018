#ifndef PENGUINCANNON_H_
#define PENGUINCANNON_H_

#include "Component.h"
#include "Timer.h"

#include <string>

class PenguinCannon : public Component {
private:
	float angle;
	Timer cooldown;
	std::weak_ptr<GameObject> pbody;

public:
	PenguinCannon(GameObject& associated, std::weak_ptr<GameObject> penguinBody);
	~PenguinCannon();
	void Shoot();
	void Update(float dt);
	void Render();
	bool Is(std::string type);
};

#endif /* PENGUINCANNON_H_ */
