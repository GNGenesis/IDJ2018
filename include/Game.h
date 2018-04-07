#ifndef GAME_H_
#define GAME_H_

#define INCLUDE_SDL
#include "SDL_include.h"

#include "State.h"

#include <string>

class Game {
private:
	static Game* instance;
	SDL_Window* window;
	SDL_Renderer* renderer;
	State* state;

	Game(std::string title, int width, int height);

public:
	~Game();
	static Game& GetInstance();
	SDL_Renderer* GetRenderer();
	State& GetState();
	void Run();
};

#endif /* GAME_H_ */
