
#include "Player.h"
#include "Board.h"


Player::Player(char playerName[28], char playerMark)
	: mark(playerMark), board(nullptr), opponent(nullptr) {
	strcpy_s(name, playerName); 

};

Player::~Player() {}; 

void Player::setOpponent(Player* opp) {
	opponent = opp;
}

void Player::setBoard(Board* b) {
	board = b;
}

