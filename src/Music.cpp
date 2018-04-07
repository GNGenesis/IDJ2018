#include "Music.h"

Music::Music() {
	music = nullptr;
}

Music::Music(std::string file) {
	music = nullptr;
	Open(file);
}

Music::~Music() {
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
	Mix_PlayMusic(music, times);
}

void Music::Stop(int msToStop) {
	Mix_FadeOutMusic(msToStop);
}

bool Music::IsOpen() {
	return (!music) ? false : true;
}
