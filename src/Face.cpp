#include "Face.h"
#include "InputManager.h"

#include "Sprite.h"
#include "Sound.h"

//#include <stdlib.h>
//#include <time.h>

Face::Face(GameObject& associated) : Component(associated) {
	hitpoints = 30;
}

Face::~Face() {

}

void Face::Damage(int damage) {
	hitpoints -= damage;
	if(IsDead()) {
		Sprite* sprite = (Sprite*) associated.GetComponent("Sprite");
		sprite->Toggle();
		Sound* sound = (Sound*) associated.GetComponent("Sound");
		sound->Play();
	}
}

void Face::Update(float dt) {
	if(IsDead()) {
		Sound* sound = (Sound*) associated.GetComponent("Sound");
		if(!sound->IsPlaying())
			associated.RequestDelete();
	}
}

void Face::Render(Vec2 cameraPos) {

}

bool Face::Is(std::string type) {
	return (type == "Face");
}

bool Face::IsDead() {
	return (hitpoints < 1);
}
