#define INCLUDE_SDL_MIXER
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_TTF

#include "Game.h"
#include "Resources.h"
#include "InputManager.h"

Game* Game::instance = nullptr;

Game::Game(std::string title, int width, int height) {
	if(instance) {
		printf("Multiple Instances\n");
		exit(EXIT_FAILURE);
	}else{
		instance = this;
	}

	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER)) {
		printf("SDL_Init failed\n");
		exit(EXIT_FAILURE);
	}

	if(!IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF)) {
		printf("IMG_Init failed: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	if(!Mix_Init(MIX_INIT_OGG)) {
		printf("Mix_Init failed: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024)) {
		printf("Mix_OpenAudio failed: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	Mix_AllocateChannels(32);

	if(TTF_Init()) {
		printf("TTF_Init failed: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
	if(!window) {
		printf("SDL_CreateWindow failed: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if(!renderer) {
		printf("SDL_CreateRenderer failed: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	state = new State();
}

Game::~Game() {
	delete state;
	Resources::ClearImages();
	Resources::ClearMusics();
	Resources::ClearSounds();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	TTF_Quit();
	Mix_CloseAudio();
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
	printf("We have cleaned it all up now, you can go already.");
}

Game& Game::GetInstance() {
	if(!instance)
		new Game("Gabriel Nazareno Halabi 15/0010290", 1024, 600);
	return *instance;
}

SDL_Renderer* Game::GetRenderer() {
	return renderer;
}

State& Game::GetState() {
	return *state;
}

void Game::CalculateDeltaTime() {
	dt = SDL_GetTicks() - frameStart;
	frameStart = frameStart + dt;
}

float Game::GetDeltaTime() {
	return dt/1000;
}

void Game::Run() {
	state->Start();
	while(!state->QuitRequested()) {
		CalculateDeltaTime();
		if(SDL_RenderClear(renderer))
			printf("SDL_RenderClear failed: %s\n", SDL_GetError());
		InputManager::Update();
		state->Update(GetDeltaTime());
		state->Render();
		SDL_RenderPresent(renderer);
		SDL_Delay(33);
	}
	printf("Game Over.\n");
}
