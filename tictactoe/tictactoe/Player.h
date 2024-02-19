#pragma once

#include <string>
#include "Board.h"

class Player {
public:
	// contructor
	Player(char playerName[28], char playerMark);

	// destructor 
	~Player();

	// void makeMove();

	void setOpponent(Player* player);

	void setBoard(Board* board);

private:
	char name[28];
	Board* board;
	Player* opponent;
	char mark;
};
