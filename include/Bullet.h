#ifndef BULLET_H_
#define BULLET_H_

#include "Component.h"

#include <string>

class Bullet : public Component {
private:
	Vec2 speed;
	int damage;
	float distanceLeft;

public:
	Bullet(GameObject& associated, float maxDistance, float angle, float speed, int damage, std::string sprite);
	~Bullet();
	void Update(float dt);
	void Render();
	bool Is(std::string type);
	int GetDamage();
};

#endif /* BULLET_H_ */
