#include "Minion.h"
#include "Game.h"

#include "Sprite.h"
#include "Sound.h"
#include "Bullet.h"

#include <stdlib.h>
#include <time.h>

Minion::Minion(GameObject& associated, GameObject& alienCenter, float arcOffsetDeg) : Component(associated) {
	Minion::alienCenter = Game::GetInstance().GetState().GetObjectPtr(&alienCenter);
	arc = arcOffsetDeg;

	Sprite* sp = new Sprite(associated, "assets/img/minion.png");
	float scale = 1 + (float)(rand()%501)/1000;
	sp->SetScale(Vec2(scale, scale));
	associated.AddComponent(sp);
}

Minion::~Minion() {

}

void Minion::Shoot(Vec2 pos) {
	float distance = associated.box.GetCenter().GetDS(pos);
	float angle = associated.box.GetCenter().GetAngle(pos);
	GameObject* go = new GameObject();
	Sprite* sprite = new Sprite(*go, "assets/img/minionbullet2.png", 3, 0.33, true);
	sprite->SetScale(Vec2(2, 2));
	go->AddComponentAsFirst(new Bullet(*go, sprite, "Alien", distance, angle, 800, 1));
	go->box.SetCenter(associated.box.GetCenter());
	Game::GetInstance().GetState().AddObject(go);
}

void Minion::Update(float dt) {
	if(alienCenter.expired()) {
		associated.RequestDelete();
		GameObject* go = new GameObject();
		go->AddComponent(new Sprite(*go, "assets/img/miniondeath.png", 4, 0.15, false, 1.5));
		Sound* sound = new Sound(*go, "assets/audio/boom.wav");
		sound->Play();
		go->AddComponent(sound);
		go->box.SetCenter(associated.box.GetCenter());
		go->rotation = rand()%360;
		Game::GetInstance().GetState().AddObject(go);
	}else{
		arc += 60*dt;
		associated.rotation = arc-90;
		associated.box.x = alienCenter.lock()->box.GetCenter().x+(200*Vec2::Cos(arc))-(associated.box.w/2);
		associated.box.y = alienCenter.lock()->box.GetCenter().y+(200*Vec2::Sin(arc))-(associated.box.h/2);
	}
}

void Minion::Render() {

}

bool Minion::Is(std::string type) {
	return (type == "Minion");
}
