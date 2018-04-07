#include "Sprite.h"
#include "Game.h"

Sprite::Sprite() {
	texture = nullptr;
	width = 0;
	height = 0;
}

Sprite::Sprite(std::string file) {
	texture = nullptr;
	width = 0;
	height = 0;
	Open(file);
}

Sprite::~Sprite() {
	SDL_DestroyTexture(texture);
	clipRect.~SDL_Rect();
	width = 0;
	height = 0;
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
}

void Sprite::SetClip(int x, int y, int w, int h) {
	clipRect.x = x;
	clipRect.y = y;
	clipRect.w = w;
	clipRect.h = h;
}

void Sprite::Render(int x, int y) {
	SDL_Rect dstRect = SDL_Rect();
	dstRect.x = x;
	dstRect.y = y;
	dstRect.w = clipRect.w;
	dstRect.h = clipRect.h;
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), texture, &clipRect, &dstRect);
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
