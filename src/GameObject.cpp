#include "GameObject.h"
#include "Component.h"

GameObject::GameObject() {
	started = false;
	active = true;
	isDead = false;
	box = Rect();
	rotation = 0;
}

GameObject::~GameObject() {
	components.clear();
}

void GameObject::Start() {
	for(unsigned i = 0; i < components.size(); i++)
		components[i]->Start();
	started = true;
}

void GameObject::AddComponent(Component* cpt) {
	components.emplace_back(cpt);
	if(started)
		cpt->Start();
}

void GameObject::AddComponentAsFirst(Component* cpt) {
	components.emplace(components.begin(), cpt);
	if(started)
		cpt->Start();
}

void GameObject::RemoveComponent(Component* cpt) {
	for(int i = components.size()-1; i >= 0; i--)
		if(components[i].get() == cpt)
			components.erase(components.begin()+i);
}

Component* GameObject::GetComponent(std::string type) {
	for(unsigned i = 0; i < components.size(); i++)
		if(components[i]->Is(type))
			return components[i].get();
	return nullptr;
}

void GameObject::RequestDelete() {
	isDead = true;
}

void GameObject::Update(float dt) {
	for(unsigned i = 0; i < components.size(); i++)
		if(components[i]->IsActive())
			components[i]->Update(dt);
}

void GameObject::Render() {
	for(unsigned i = 0; i < components.size(); i++)
		if(components[i]->IsActive())
			components[i]->Render();
}

void GameObject::NotifyCollision(GameObject& other) {
	for(unsigned i = 0; i < components.size(); i++)
		if(components[i]->IsActive())
			components[i]->NotifyCollision(other);
}

void GameObject::Activate() {
	active = true;
}

void GameObject::Deactivate() {
	active = false;
}

bool GameObject::IsActive() {
	return active;
}

bool GameObject::IsDead() {
	return isDead;
}
