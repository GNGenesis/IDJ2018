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
	bool started;
	bool active;
	bool isDead;

public:
	Rect box;
	float rotation;

	GameObject();
	~GameObject();
	void Start();
	void AddComponent(Component* cpt);
	void RemoveComponent(Component* cpt);
	Component* GetComponent(std::string type);
	void RequestDelete();
	void Update(float dt) ;
	void Render();
	void Activate();
	void Deactivate();
	bool IsActive();
	bool IsDead();
};

#endif /* GAMEOBJECT_H_ */
