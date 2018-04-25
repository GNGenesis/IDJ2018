#ifndef COMPONENT_H_
#define COMPONENT_H_

#include "GameObject.h"

#include <string>

class Component {
protected:
	GameObject& associated;

public:
	Component(GameObject& associated);
	virtual ~Component();
	virtual void Update(float dt) = 0;
	virtual void Render(Vec2 cameraPos) = 0;
	virtual bool Is(std::string type) = 0;
};

#endif /* COMPONENT_H_ */
