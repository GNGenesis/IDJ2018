#include "State.h"

State::State() {
	bg = Sprite();
	music.Open("assets/audio/stageState.ogg");
	music.Play();
	quitRequested = false;
}

State::~State() {
	music.Stop(0);
}

void State::LoadAssets() {
	bg.Open("assets/img/ocean.jpg");
}

void State::Update(float dt) {
	quitRequested = SDL_QuitRequested();
}

void State::Render() {
	bg.Render(0, 0);
}

bool State::QuitRequested() {
	return quitRequested;
}
