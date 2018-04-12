#include "State.h"

#include <stdlib.h>
#include <time.h>

State::State() : music("assets/audio/stageState.ogg") {
	objectArray = std::vector<std::unique_ptr<GameObject>>();
	quitRequested = false;
	
	GameObject* bg = new GameObject();
	Component* bgs = new Sprite(*bg, "assets/img/ocean.jpg");
	bg->AddComponent(bgs);
	objectArray.emplace_back(bg);
	
	GameObject* map = new GameObject();
	TileSet* set = new TileSet(*map, "assets/img/tileSet.png",64,64);
	Component* tileMap = new TileMap(*map, set, "assets/map/tileMap.txt");
	map->AddComponent(tileMap);
	objectArray.emplace_back(map);
	
	music.Play();

	srand(time(NULL));
}

State::~State() {
	objectArray.clear();
	delete set;
	music.Stop(0);
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

void State::Input() {
	SDL_Event event;
	int mouseX, mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);

	while(SDL_PollEvent(&event)) {
		if(event.type == SDL_QUIT)
			quitRequested = true;
		
		if(event.type == SDL_MOUSEBUTTONDOWN) {
			for(int i = objectArray.size()-1; i >= 0; i--) {
				GameObject* go = (GameObject*) objectArray[i].get();
				if(go->box.Contains((float)mouseX, (float)mouseY)) {
					Face* face = (Face*) go->GetComponent("Face");
					if(face) {
						if(!face->IsDead()) {
							face->Damage(std::rand()%10 + 10);
							break;
						}
					}
				}
			}
		}
		if(event.type == SDL_KEYDOWN) {
			if(event.key.keysym.sym == SDLK_ESCAPE) {
				quitRequested = true;
			}else{
				Vec2 objPos = Vec2(mouseX, mouseY) + Vec2::Project(200, std::rand()%360);
				AddObject(objPos.x, objPos.y);
			}
		}
	}
}

void State::Update(float dt) {
	Input();
	for(auto& i: objectArray)
		i->Update(dt);
	for(int i = objectArray.size()-1; i >= 0; i--)
		if(objectArray[i]->IsDead())
			objectArray.erase(objectArray.begin()+i);
}

void State::Render() {
	for(auto& i: objectArray)
		i->Render();
}

bool State::QuitRequested() {
	return quitRequested;
}
