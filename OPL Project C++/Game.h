#ifndef GAME_H
#define GAME_H

#include "Round.h"
#include "Serialization.h"

class Game
{

private:

	Round round;
	Serialization file;

public:

	Game();
	void startGame();
	void resumeGame();
};
#endif

