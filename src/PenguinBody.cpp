#include "PenguinBody.h"
#include "Game.h"
#include "InputManager.h"

#include "Sprite.h"
#include "Sound.h"
#include "Collider.h"
#include "PenguinCannon.h"
#include "Bullet.h"

PenguinBody* PenguinBody::player;

PenguinBody::PenguinBody(GameObject& associated) : Component(associated) {
	hp = 10;
	linearSpeed = 0;
	angle = 0;
	if(player)
		player->associated.RequestDelete();
	player = this;

	associated.AddComponent(new Sprite(associated, "assets/img/penguin.png"));
	associated.AddComponent(new Collider(associated));
}

PenguinBody::~PenguinBody() {
	if(player == this)
		player = nullptr;
}

void PenguinBody::Start() {
	GameObject* go = new GameObject();
	go->AddComponent(new PenguinCannon(*go, Game::GetInstance().GetState().GetObjectPtr(&associated)));
	pcannon = Game::GetInstance().GetState().AddObject(go);
}

void PenguinBody::Damage(int damage) {
	hp -= damage;
	if(hp < 1) {
		associated.RequestDelete();
		GameObject* go = new GameObject();
		go->AddComponent(new Sprite(*go, "assets/img/penguindeath.png", 5, 0.15, false, 1.5));
		Sound* sound = new Sound(*go, "assets/audio/boom.wav");
		sound->Play();
		go->AddComponent(sound);
		go->box.SetCenter(associated.box.GetCenter());
		go->rotation = rand()%360;
		Game::GetInstance().GetState().AddObject(go);
	}
}

void PenguinBody::Update(float dt) {
	if(InputManager::IsKeyDown(SDLK_w)) {
		linearSpeed += 100*dt;
		if(linearSpeed > 400)
			linearSpeed = 400;
	}
	if(InputManager::IsKeyDown(SDLK_a)) {
		angle -= 180*dt;
	}
	if(InputManager::IsKeyDown(SDLK_s)) {
		linearSpeed -= 100*dt;
		if(linearSpeed < -200)
			linearSpeed = -200;
	}
	if(InputManager::IsKeyDown(SDLK_d)) {
		angle += 180*dt;
	}
	if(InputManager::IsKeyDown(SPACE_KEY)) {
		if(linearSpeed > 0) {
			if(linearSpeed-100*dt < 0)	
				linearSpeed = 0;
			else
				linearSpeed -= 100*dt;
		}else{
			if(linearSpeed+100*dt > 0)	
				linearSpeed = 0;
			else
				linearSpeed += 100*dt;
		}
	}
	if(InputManager::IsMouseDown(LEFT_MOUSE_BUTTON)) {
		PenguinCannon* cannon = (PenguinCannon*) pcannon.lock()->GetComponent("PenguinCannon");
		cannon->Shoot();
	}

	speed.x = Vec2::Cos(angle)*linearSpeed;
	speed.y = Vec2::Sin(angle)*linearSpeed;
	associated.rotation = angle;
	associated.box.SetPos(associated.box.GetPos()+speed*dt);
	
	if(associated.box.x < 0)
		associated.box.x = 0;
	else if(associated.box.x+associated.box.w > 1408)
		associated.box.x = 1408-associated.box.w;
	
	if(associated.box.y < 0)
		associated.box.y = 0;
	else if(associated.box.y+associated.box.h > 1280)
		associated.box.y = 1280-associated.box.h;
}

void PenguinBody::Render() {

}

void PenguinBody::NotifyCollision(GameObject& other) {
	Bullet* bullet = (Bullet*) other.GetComponent("Bullet");
	if(bullet)
		if(!bullet->IsOwner("PenguinBody"))
			Damage(bullet->GetDamage());
}

bool PenguinBody::Is(std::string type) {
	return (type == "PenguinBody");
}

Vec2 PenguinBody::GetPlayerCenter() {
	return associated.box.GetCenter();
}
