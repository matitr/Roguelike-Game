#include "Game.h"
#include <time.h>

int main(int argc, char* args[]) {

	srand(time(NULL));
	Game *game = new Game("Game", 1610, 1010, false);
	game->run();
	delete game;

	return 0;
}