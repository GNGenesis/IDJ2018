#include "StageState.h"
#include "Game.h"
#include "GameData.h"
#include "InputManager.h"
#include "Camera.h"
#include "Collision.h"

#include "EndState.h"

#include "Sprite.h"
#include "Sound.h"
#include "Text.h"
#include "Collider.h"
#include "CameraFollower.h"
#include "TileMap.h"

#include "Alien.h"
#include "PenguinBody.h"

StageState::StageState() : State(), backgroundMusic("assets/audio/stageState.ogg") {
	bg = new GameObject();
	map = new GameObject();
	set = new TileSet(*map, "assets/img/tileset.png", 64, 64);

	//Background
	bg->AddComponent(new Sprite(*bg, "assets/img/ocean.jpg"));
	bg->AddComponent(new CameraFollower(*bg));
	bg->box.SetSize(Vec2());

	//TileMap
	map->AddComponent(new TileMap(*map, set, "assets/map/tileMap.txt"));
	map->box = Rect();

	//Alien
	for(int i = 0; i < 3; i++) {
		GameObject* go = new GameObject();
		go->AddComponentAsFirst(new Alien(*go, 2+rand()%11));
		go->box.SetCenter(rand()%1409, rand()%1280);
		AddObject(go);
	}

	//Player: Penguin
	GameObject* go = new GameObject();
	go->AddComponentAsFirst(new PenguinBody(*go));
	go->box.SetCenter(704, 640);
	AddObject(go);
	
	Camera::Follow(go);

	backgroundMusic.Play();
}

StageState::~StageState() {
	delete set;
	delete map;
	delete bg;
}

void StageState::LoadAssets() {

}

void StageState::Start() {
	LoadAssets();
	bg->Start();
	map->Start();
	StartArray();
	started = true;
}

void StageState::Pause() {
	for(unsigned i = 0; i < objectArray.size(); i++) {
		Sound* sound = (Sound*) objectArray[i]->GetComponent("Sound");
		if(sound)
			sound->Stop();
	}
}

void StageState::Resume() {
	backgroundMusic.Play();
	objectArray.clear();

	//Alien
	for(int i = 0; i < 3; i++) {
		GameObject* go = new GameObject();
		go->AddComponentAsFirst(new Alien(*go, 2+rand()%11));
		go->box.SetCenter(rand()%1409, rand()%1280);
		AddObject(go);
	}

	//Player: Penguin
	GameObject* go = new GameObject();
	go->AddComponentAsFirst(new PenguinBody(*go));
	go->box.SetCenter(704, 640);
	AddObject(go);

	Camera::Follow(go);
}

void StageState::CollisionCheck() {
	for(unsigned i = 0; i < objectArray.size(); i++) {
		for(unsigned j = i+1; j < objectArray.size(); j++) {
			if(objectArray[i]->IsActive() && objectArray[j]->IsActive()) {
				Collider* objA = (Collider*) objectArray[i]->GetComponent("Collider");
				Collider* objB = (Collider*) objectArray[j]->GetComponent("Collider");
				if(objA && objB) {
					if(Collision::IsColliding(objA->box, objB->box, objA->rotation, objB->rotation)) {
						objectArray[i]->NotifyCollision(*objectArray[j]);
						objectArray[j]->NotifyCollision(*objectArray[i]);
					}
				}
			}
		}
	}
}

void StageState::DeletionCheck() {
	for(int i = objectArray.size()-1; i >= 0; i--) {
		if(objectArray[i]->IsDead()) {
			if(Camera::GetFocus() == objectArray[i].get())
				Camera::Unfollow();
			objectArray.erase(objectArray.begin()+i);
		}
	}
}

void StageState::Update(float dt) {
	quitRequested = InputManager::QuitRequested();
	if(InputManager::KeyPress(ESCAPE_KEY))
		popRequested = true;

	if(InputManager::KeyPress(SDLK_z)) {
		GameObject* go = new GameObject();
		go->AddComponentAsFirst(new PenguinBody(*go));
		go->box.SetCenter(704, 640);
		AddObject(go);
		
		Camera::Follow(go);
	}
	if(InputManager::KeyPress(SDLK_x)) {
		if(PenguinBody::player)
			PenguinBody::player->Damage(10);
	}
	if(InputManager::KeyPress(SDLK_c)) {
		GameObject* go = new GameObject();
		go->AddComponentAsFirst(new Alien(*go, 2+rand()%11));
		go->box.SetCenter(rand()%1409, rand()%1280);
		AddObject(go);
	}
	if(InputManager::KeyPress(SDLK_v)) {
		for(unsigned i = 0; i < objectArray.size(); i++) {
			Alien* alien = (Alien*) objectArray[i]->GetComponent("Alien");
			if(alien)
				alien->Damage(10);
		}
	}

	if(bg->IsActive())
		bg->Update(dt);
	if(map->IsActive())
		map->Update(dt);
	UpdateArray(dt);
	CollisionCheck();
	DeletionCheck();

	if(!PenguinBody::player) {
		GameData::playerVictory = false;
		Game::GetInstance().Push(new EndState());
	}
	else if(Alien::alienCount < 1) {
		GameData::playerVictory = true;
		Game::GetInstance().Push(new EndState());
	}
}

void StageState::Render() {
	TileMap* tileMap = (TileMap*) map->GetComponent("TileMap");
	
	if(bg->IsActive())
		bg->Render();
	if(map->IsActive())
		tileMap->RenderLayer(0, Camera::pos.x, Camera::pos.y);
	RenderArray();
	if(map->IsActive())
		tileMap->RenderLayer(1, Camera::pos.x*1.5, Camera::pos.y*1.5);
}
