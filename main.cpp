#include "Game.h"
#include <time.h>

int main(int argc, char* args[]) {

	Game *game = new Game(1510, 800, false);
	game->run();
	delete game;

	return 0;
}