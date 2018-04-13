#include "GameObject.h"
#include "Component.h"

GameObject::GameObject() {
	components = std::vector<std::unique_ptr<Component>>();
	isDead = false;
	box = Rect();
}

GameObject::~GameObject() {
	components.clear();
}

void GameObject::AddComponent(Component* cpt) {
	components.emplace_back(cpt);
}

void GameObject::RemoveComponent(Component* cpt) {
	for(int i = components.size()-1; i >= 0; i--)
		if(components[i].get() == cpt)
			components.erase(components.begin()+i);
}

Component* GameObject::GetComponent(std::string type) {
	for(auto& i: components)
		if(i->Is(type))
			return i.get();
	return nullptr;
}

void GameObject::RequestDelete() {
	isDead = true;
}

void GameObject::Update(float dt) {
	for(auto& i: components)
		i->Update(dt);
}

void GameObject::Render() {
	for(auto& i: components)
		i->Render();
}

bool GameObject::IsDead() {
	return isDead;
}
