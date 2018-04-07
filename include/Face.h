#ifndef FACE_H_
#define FACE_H_

#include "Component.h"

#include <string>

class Face : public Component {
private:
	int hitpoints;

public:
	Face(GameObject& associated);
	~Face();
	void Damage(int damage);
	void Update(float dt);
	void Render();
	bool Is(std::string type);
	bool IsDead();
};

#endif /* FACE_H_ */
