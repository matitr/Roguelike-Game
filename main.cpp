#include "Game.h"
#include <time.h>

int main(int argc, char* args[]) {

	srand(time(NULL));
	Game *game = new Game("Game", 610, 610, false);
	game->run();
	delete game;

	return 0;
}