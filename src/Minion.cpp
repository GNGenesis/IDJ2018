#include "Minion.h"
#include "Game.h"

#include "Sprite.h"
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
	//associated.AddComponent(new Sprite(associated, "assets/img/minion.png"));
}

Minion::~Minion() {

}

void Minion::Shoot(Vec2 pos) {
	float distance = associated.box.GetCenter().GetDS(pos);
	float angle = associated.box.GetCenter().GetAngle(pos);
	GameObject* go = new GameObject();
	go->AddComponent(new Bullet(*go, distance, angle, 600, 5, "assets/img/minionbullet2.png"));
	go->box.SetPos(associated.box.GetCenter()-Vec2(go->box.w/2, go->box.h/2));
	Game::GetInstance().GetState().AddObject(go);
}

void Minion::Update(float dt) {
	if(alienCenter.expired()) {
		associated.RequestDelete();
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
