#include "Game.h"

int main(int argv, char** args) {
	Game game = Game::GetInstance();
	game.Run();
	printf("Thanks for playing!\n");
	return 0;
}
