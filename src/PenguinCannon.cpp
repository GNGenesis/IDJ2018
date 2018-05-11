#include "PenguinCannon.h"
#include "Game.h"
#include "InputManager.h"

#include "Sprite.h"
#include "Bullet.h"

PenguinCannon::PenguinCannon(GameObject& associated, std::weak_ptr<GameObject> penguinBody) : Component(associated) {
	angle = 0;
	cooldown = Timer();
	pbody = penguinBody;

	associated.AddComponent(new Sprite(associated, "assets/img/cubngun.png"));
}

PenguinCannon::~PenguinCannon() {

}

void PenguinCannon::Shoot() {
	if(cooldown.Get() > 0.5) {
		GameObject* go = new GameObject();
		Sprite* sprite = new Sprite(*go, "assets/img/penguinbullet.png", 4, 0.33, false);
		sprite->SetScale(Vec2(1, 1));
		go->AddComponentAsFirst(new Bullet(*go, sprite, "PenguinBody", 1000, angle, 800, 1));
		go->box.SetCenter(associated.box.GetCenter()+Vec2(Vec2::Cos(angle)*associated.box.w/2, Vec2::Sin(angle)*associated.box.w/2));
		Game::GetInstance().GetState().AddObject(go);
		cooldown.Restart();
	}
}

void PenguinCannon::Update(float dt) {
	if(pbody.expired()) {
		associated.RequestDelete();
	}else{
		cooldown.Update(dt);
		associated.box.SetCenter(pbody.lock()->box.GetCenter());
		angle = associated.box.GetCenter().GetAngle(InputManager::GetMousePos());
		associated.rotation = angle;
	}
}

void PenguinCannon::Render() {

}

bool PenguinCannon::Is(std::string type) {
	return (type == "PenguinCannon");
}
