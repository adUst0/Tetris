#include "Game.h"

int main(int argc, char **argv)
{
	Game game(GameMode::AI);
	game.start();

	return 0;
}
