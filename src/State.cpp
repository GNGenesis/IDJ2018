#include "State.h"
#include "InputManager.h"
#include "Camera.h"

#include "Sprite.h"
#include "Sound.h"
#include "TileMap.h"
#include "CameraFollower.h"

#include "Alien.h"

#include <stdlib.h>
#include <time.h>

State::State() : music("assets/audio/stageState.ogg") {
	started = false;
	quitRequested = false;

	bg = new GameObject();
	map = new GameObject();
	set = new TileSet(*map, "assets/img/tileset.png", 64, 64);

	bg->AddComponent(new Sprite(*bg, "assets/img/ocean.jpg"));
	bg->AddComponent(new CameraFollower(*bg));
	bg->box = Rect();

	map->AddComponent(new TileMap(*map, set, "assets/map/tileMap.txt"));
	map->box = Rect();

	GameObject* go = new GameObject();
	go->AddComponent(new Alien(*go, 8));
	go->box.SetPos(512-go->box.w/2, 300-go->box.h/2);
	AddObject(go);

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

	for(unsigned i = 0; i < objectArray.size(); i++)
		if(objectArray[i]->IsActive())
			objectArray[i]->Update(dt);

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
