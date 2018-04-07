#include "Music.h"

Music::Music() {
	music = nullptr;
}

Music::Music(std::string file) : Music() {
	Open(file);
}

Music::~Music() {
	if(IsOpen())
		Mix_FreeMusic(music);
}

void Music::Open(std::string file) {
	music = Mix_LoadMUS(file.c_str());
	if(!IsOpen()) {
		printf("Mix_LoadMUS failed: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
}

void Music::Play(int times) {
	if(Mix_PlayMusic(music, times) == -1) {
		printf("Mix_PlayedMusic failed: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
}

void Music::Stop(int msToStop) {
	if(!Mix_FadeOutMusic(msToStop)) {
		printf("Mix_FadeOutMusic failed: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
}

bool Music::IsOpen() {
	return (!music) ? false : true;
}
