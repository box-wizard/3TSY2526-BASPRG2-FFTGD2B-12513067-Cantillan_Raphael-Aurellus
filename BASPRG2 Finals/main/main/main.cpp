#include <iostream>
#include <ctime>
#include <cstdlib>
#include "GameCombat.h"
using namespace std;

int main()
{
	srand(time(NULL));

	GameCombat game;

	game.Initialize();
	game.Run();

	return 0;
}