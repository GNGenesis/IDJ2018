#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include "Rect.h"

#include <string>
#include <vector>
#include <memory>

class Component;

class GameObject {
private:
	std::vector<std::unique_ptr<Component>> components;
	bool isDead;

public:
	Rect box;

	GameObject();
	~GameObject();
	void AddComponent(Component* cpt);
	void RemoveComponent(Component* cpt);
	Component* GetComponent(std::string type);
	void RequestDelete();
	void Update(float dt) ;
	void Render(Vec2 cameraPos = Vec2());
	bool IsDead();
};

#endif /* GAMEOBJECT_H_ */
