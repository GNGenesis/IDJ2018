#include "Sprite.h"
#include "Game.h"

Sprite::Sprite(GameObject& associated) : Component(associated) {
	texture = nullptr;
	on = true;
	width = 0;
	height = 0;
}

Sprite::Sprite(GameObject& associated, std::string file) : Sprite(associated) {
	Open(file);
}

Sprite::~Sprite() {
	if(IsOpen())
		SDL_DestroyTexture(texture);
	clipRect.~SDL_Rect();
}

void Sprite::Open(std::string file) {
	if(IsOpen())
		SDL_DestroyTexture(texture);
	texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());
	if(!IsOpen()) {
		printf("IMG_LoadTexture failed: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
	SetClip(0, 0, width, height);
	associated.box.w = width;
	associated.box.h = height;
}

void Sprite::SetClip(int x, int y, int w, int h) {
	clipRect.x = x;
	clipRect.y = y;
	clipRect.w = w;
	clipRect.h = h;
}

void Sprite::Toggle() {
	on = !on;
}

void Sprite::Update(float dt) {
	
}

void Sprite::Render() {
	if(on) {
		SDL_Rect dstRect = SDL_Rect();
		dstRect.x = associated.box.x;
		dstRect.y = associated.box.y;
		dstRect.w = clipRect.w;
		dstRect.h = clipRect.h;
		SDL_RenderCopy(Game::GetInstance().GetRenderer(), texture, &clipRect, &dstRect);
	}
}

bool Sprite::Is(std::string type) {
	return (type == "Sprite");
}

int Sprite::GetWidth() {
	return width;
}

int Sprite::GetHeight() {
	return height;
}

bool Sprite::IsOpen() {
	return (!texture) ? false : true;
}

bool Sprite::IsOn() {
	return on;
}
