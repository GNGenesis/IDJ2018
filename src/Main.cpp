#include "Game.h"

int main(int argv, char** args) {
	Game game = Game::GetInstance();
	game.Run();
	return 0;
}
