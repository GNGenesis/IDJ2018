#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include "Rect.h"

#include <string>
#include <vector>
#include <memory>

class Component;

class GameObject {
private:
	bool isDead;
	std::vector<std::unique_ptr<Component>> components;

public:
	Rect box;

	GameObject();
	~GameObject();
	void AddComponent(Component* cpt);
	void RemoveComponent(Component* cpt);
	Component* GetComponent(std::string type);
	void RequestDelete();
	void Update(float dt) ;
	void Render();
	bool IsDead();
};

#endif /* GAMEOBJECT_H_ */
