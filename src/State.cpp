#include "State.h"
#include "InputManager.h"
#include "Camera.h"

#include "Sprite.h"
#include "Sound.h"
#include "Face.h"
#include "TileMap.h"
#include "CameraFollower.h"

#include <stdlib.h>
#include <time.h>

State::State() : music("assets/audio/stageState.ogg") {
	quitRequested = false;

	bg = new GameObject();
	map = new GameObject();
	set = new TileSet(*map, "assets/img/tileSet.png", 64, 64);

	bg->AddComponent(new Sprite(*bg, "assets/img/ocean.jpg"));
	bg->AddComponent(new CameraFollower(*bg));
	bg->box = Rect();

	map->AddComponent(new TileMap(*map, set, "assets/map/tileMap.txt"));
	map->box = Rect();

	music.Play();

	srand(time(NULL));
}

State::~State() {
	delete set;
	delete map;
	delete bg;
	objectArray.clear();
}

void State::AddObject(int mouseX, int mouseY) {
	GameObject* go = new GameObject();
	Sprite* sprite = new Sprite(*go, "assets/img/penguinface.png");
	go->AddComponent(sprite);
	go->AddComponent(new Sound(*go, "assets/audio/boom.wav"));
	go->AddComponent(new Face(*go));
	objectArray.emplace_back(go);
	go->box = Rect(mouseX-sprite->GetWidth()/2, mouseY-sprite->GetHeight()/2,
				   sprite->GetWidth(), sprite->GetHeight());
}

void State::LoadAssets() {

}

void State::Update(float dt) {
	quitRequested = InputManager::GetInstance().QuitRequested();

	Camera::Update(dt);
	bg->Update(dt);
	map->Update(dt);
	
	if(InputManager::GetInstance().KeyPress(SPACE_KEY)) {
		Vec2 objPos = InputManager::GetInstance().GetMousePos()+Vec2::Project(200, std::rand()%360);
		AddObject(objPos.x, objPos.y);
	}
	
	if(InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON)) {
		for(int i = objectArray.size()-1; i >= 0; i--) {
			if(objectArray[i]->box.Contains(InputManager::GetInstance().GetMousePos())) {
				Face* face = (Face*) objectArray[i]->GetComponent("Face");
				if(face) {
					if(!face->IsDead()) {
						face->Damage(10+std::rand()%10);
						break;
					}
				}
			}
		}
	}

	if(InputManager::GetInstance().MousePress(RIGHT_MOUSE_BUTTON)) {
		for(int i = objectArray.size()-1; i >= 0; i--) {
			if(objectArray[i]->box.Contains(InputManager::GetInstance().GetMousePos())) {
				Face* face = (Face*) objectArray[i]->GetComponent("Face");
				if(face) {
					if(!face->IsDead()) {
						Camera::Follow(objectArray[i].get());
						break;
					}
				}
			}
		}
	}
	
	for(auto& i: objectArray)
		i->Update(dt);
	
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
	
	bg->Render(Camera::pos);
	tileMap->RenderLayer(0, Camera::pos.x, Camera::pos.y);
	for(auto& i: objectArray)
		i->Render(Camera::pos);
	tileMap->RenderLayer(1, Camera::pos.x*1.5, Camera::pos.y*1.5);
}

bool State::QuitRequested() {
	return quitRequested;
}
