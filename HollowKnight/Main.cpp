#include "Game.h"

using namespace std;

int main()
{
	locale::global(locale(""));
	srand(static_cast<unsigned>(time(nullptr)));

	Game _game;
	_game.Launch();

	return 0;
}