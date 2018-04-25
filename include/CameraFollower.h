#ifndef CAMERAFOLLOWER_H_
#define CAMERAFOLLOWER_H_

#include "Component.h"

#include <string>

class CameraFollower : public Component {
public:
	CameraFollower(GameObject& associated);
	~CameraFollower();
	void Update(float dt);
	void Render(Vec2 cameraPos);
	bool Is(std::string type);
};

#endif /* CAMERAFOLLOWER_H_ */