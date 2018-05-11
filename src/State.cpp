#include "State.h"
#include "InputManager.h"
#include "Camera.h"
#include "Collision.h"

#include "Sprite.h"
#include "Sound.h"
#include "Collider.h"
#include "CameraFollower.h"
#include "TileMap.h"

#include "Alien.h"
#include "PenguinBody.h"

#include <stdlib.h>
#include <time.h>

State::State() : music("assets/audio/stageState.ogg") {
	started = false;
	quitRequested = false;

	bg = new GameObject();
	map = new GameObject();
	set = new TileSet(*map, "assets/img/tileset.png", 64, 64);

	//Background
	bg->AddComponent(new Sprite(*bg, "assets/img/ocean.jpg"));
	bg->AddComponent(new CameraFollower(*bg));
	bg->box = Rect();

	//TileMap
	map->AddComponent(new TileMap(*map, set, "assets/map/tileMap.txt"));
	map->box = Rect();

	//Alien
	GameObject* go = new GameObject();
	go->AddComponentAsFirst(new Alien(*go, 2+rand()%11));
	go->box.SetCenter(rand()%1409, rand()%1280);
	AddObject(go);

	//Player: Penguin
	go = new GameObject();
	go->AddComponentAsFirst(new PenguinBody(*go));
	go->box.SetCenter(704, 640);
	AddObject(go);
	
	Camera::Follow(go);

	music.Play();

	srand(time(NULL));
}

State::~State() {
	delete set;
	delete map;
	delete bg;
	objectArray.clear();
}

void State::Start() {
	LoadAssets();
	for(unsigned i = 0; i < objectArray.size(); i++)
		objectArray[i]->Start();
	started = true;
}

std::weak_ptr<GameObject> State::AddObject(GameObject* go) {
	std::shared_ptr<GameObject> shared = std::shared_ptr<GameObject>(go);
	objectArray.push_back(shared);
	if(started)
		shared->Start();
	return shared;
}

std::weak_ptr<GameObject> State::GetObjectPtr(GameObject* go) {
	for(unsigned i = 0; i < objectArray.size(); i++)
		if(objectArray[i].get() == go)
			return objectArray[i];
	return std::weak_ptr<GameObject>();
}

void State::LoadAssets() {

}

void State::Update(float dt) {
	quitRequested = InputManager::QuitRequested();
	if(InputManager::KeyPress(ESCAPE_KEY))
		quitRequested = true;

	Camera::Update(dt);
	bg->Update(dt);
	map->Update(dt);

	if(InputManager::KeyPress(SDLK_z)) {
		GameObject* go = new GameObject();
		go->AddComponentAsFirst(new Alien(*go, 2+rand()%11));
		go->box.SetCenter(rand()%1409, rand()%1280);
		AddObject(go);
	}
	if(InputManager::KeyPress(SDLK_x)) {
		GameObject* go = new GameObject();
		go->AddComponentAsFirst(new PenguinBody(*go));
		go->box.SetCenter(704, 640);
		AddObject(go);
		
		Camera::Follow(go);
	}
	if(InputManager::KeyPress(SDLK_c)) {
		if(PenguinBody::player)
			PenguinBody::player->Damage(10);
	}

	for(unsigned i = 0; i < objectArray.size(); i++)
		if(objectArray[i]->IsActive())
			objectArray[i]->Update(dt);

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

	for(int i = objectArray.size()-1; i >= 0; i--) {
		if(objectArray[i]->IsDead()) {
			if(Camera::GetFocus() == objectArray[i].get())
				Camera::Unfollow();
			objectArray.erase(objectArray.begin()+i);
		}
	}
}

void State::Render() {
	TileMap* tileMap = (TileMap*) map->GetComponent("TileMap");
	
	bg->Render();
	tileMap->RenderLayer(0, Camera::pos.x, Camera::pos.y);
	for(unsigned i = 0; i < objectArray.size(); i++)
		if(objectArray[i]->IsActive())
			objectArray[i]->Render();
	tileMap->RenderLayer(1, Camera::pos.x*1.5, Camera::pos.y*1.5);
}

bool State::QuitRequested() {
	return quitRequested;
}
